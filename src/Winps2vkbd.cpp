// Winps2vkbd.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "pch.h"
#include "framework.h"
#include "Winps2vkbd.h"
#include "CComPort.h"
#include <Dbt.h>    	// for DBT_DEVNODES_CHANGED
#include <winnls32.h>	// for WINNLSEnableIME()
#include <vector>
#include "CVkey.h"
#include "tdebug.h"
#include "DrawKey.h"
#include "CD2d.h"
#include <set>

#define MAX_LOADSTRING 100

// グローバル変数:
static HINSTANCE hInst;                                // 現在のインターフェイス
static WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
static WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

static HWND	g_hWnd = 0;
static bool	g_bFocus = false;
static CD2d *g_pD2d = nullptr;
static HHOOK g_hMyHook = 0;

static uint8_t g_LedState = 0;
static bool	g_Ps2PowerStatus = false;


struct KEY_STATE_SET
{
	bool bKC109[MAX_KC109KEYCODE + 1];
	bool bMSX[MAX_MSXKEYCODE + 1];
	KEY_STATE_SET()
	{
		ZeroClear();
	}
	void ZeroClear()
	{
		for( int t = 0; t < MAX_KC109KEYCODE+1; ++t)
			bKC109[t] = false;
		for( int t = 0; t < MAX_MSXKEYCODE+1; ++t)
			bMSX[t] = false;
		return;
	}
};
static KEY_STATE_SET g_DrawKeybordState;
static std::set<vkeycode_t> g_InputVKey;		// Windowsキーボード押下中の仮想キーコード
static std::set<kc109code_t> g_InputKC109Key;	// マウス操作による GUI-PS/2の押下中のキーコード
static std::set<msxcode_t> g_InputMSXKey;		// マウス操作による GUI-MSXの押下中のキーコード

static tstring	g_RequestComportName(_T(""));
static CComPort g_Com;
static CVkey g_VKey;

// 初期ウィンドウサイズ
static const int WINDOW_W		= 774;
static const int WINDOW_H_MSX	= 328;	// MSXキーボードのみ
static const int WINDOW_H_PC	= 570;	// PCキーボードも表示する

// 各キーボードの座標
static const int KBMSX_ORG_X = 4;
static const int KBMSX_ORG_Y = 50;
static const int KB109_ORG_X = 4;
static const int KB109_ORG_Y = 300;

/**
 * 再描画の要求
*/
inline void REDRAW(const HWND hWnd)
{
	InvalidateRect(hWnd, nullptr, false);
}

//
static LRESULT CALLBACK MyHookProc(int nCode, WPARAM wp, LPARAM lp)
{
    if (g_hWnd != 0 && nCode == HC_ACTION) {
        auto *pKbhs = reinterpret_cast<KBDLLHOOKSTRUCT *>(lp);
        PostMessage(g_hWnd, WMA_HOOKKEY, (WPARAM)pKbhs->vkCode, (LPARAM)pKbhs->flags);
    }
    return CallNextHookEx(g_hMyHook, nCode, wp, lp);
}

/** 
 * COMポートへPS/2キーコードを送信する
 */
static bool sendScnaCode(const KC109_SCANCODE *p, const bool bMark)
{
	if (p == nullptr)
		return false;
	if( bMark ){
		std::unique_ptr<uint8_t[]> pDt(NNEW uint8_t[p->lenPs2Mark + 1]);
		pDt[0] = 'S';
		for (int t = 0; t < p->lenPs2Mark; ++t)
			pDt[1 + t] = p->ps2Mark[t];
		g_Com.Send(pDt.get(), p->lenPs2Mark + 1);
	}else{
		std::unique_ptr<uint8_t[]> pDt(NNEW uint8_t[p->lenPs2Break + 1]);
		pDt[0] = 'S';
		for (int t = 0; t < p->lenPs2Break; ++t)
			pDt[1 + t] = p->ps2Break[t];
		g_Com.Send(pDt.get(), p->lenPs2Break + 1);
	}
	return true;
}

static bool sendScnaCodeMarkFromMsx(const msxcode_t msxCd, const bool bMark)
{
	if (msxCd == KCMSX_NONE)
		return false;
	const auto kc109Cd = g_VKey.GetKC109CodeFromMSX(msxCd);
	auto *p = g_VKey.GetScanCode(kc109Cd);
	if (p == nullptr)
		return false;
	return sendScnaCode(p, bMark);
}

static bool sendScnaCodeMarkFrom109(const kc109code_t kc109Cd, const bool bMark)
{
	if (kc109Cd == KC109_NONE)
		return false;
	auto *p = g_VKey.GetScanCode(kc109Cd);
	if (p == nullptr)
		return false;
	return sendScnaCode(p, bMark);
}

static void callCmdFromPs2(const uint8_t *pCmd, const int len)
{
	static const char *pSample = "PS2USB:0";
	
	// LED点灯
    if (pCmd[0] == 0xed && len == 2) {
        g_LedState = pCmd[1];
        REDRAW(g_hWnd);
    }
	// PS/2
	else if (memcmp(pSample, pCmd, strlen(pSample)) == 0 && len == 9) {
		g_Ps2PowerStatus = (pCmd[8] == '1') ? true : false;
		REDRAW(g_hWnd);
	}
	return;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINPS2VKBD);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(
	const HINSTANCE hInstance, const int nCmdShow, const std::vector<tstring> &args)
{
	if( args.size() == 1 )
		g_RequestComportName = args[0];

	hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する
	
	HWND hWnd = CreateWindowW(
        szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_W, WINDOW_H_MSX,
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    //
    g_hMyHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyHookProc, hInstance, 0);
    return TRUE;
}


static LRESULT handler_WM_CREATE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_hWnd = hWnd;

	// COM Port
	if( !g_RequestComportName.empty() ){
		if( g_Com.OpenPort(hWnd, g_RequestComportName) ) {
			g_Com.Send('I');    // 接続確認
			g_Ps2PowerStatus = false;
		}
	}
	// Direct2D
	g_pD2d = NNEW CD2d();
	g_pD2d->SetRenderTargetWindow(hWnd, 200, 100);
	// IME Disable
	WINNLSEnableIME(hWnd, false);
	return 0;
}

static LRESULT handler_WM_COMMAND(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	// 選択されたメニューの解析:
	switch (wmId)
	{
		case IDM_ABOUT:
			INT_PTR CALLBACK DlgHdrAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, DlgHdrAbout);
			break;
		case ID_PS_COMSTT:
			INT_PTR CALLBACK DlgHdrComPortList(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgHdrComPortList);
			break;
		case ID_V_SHOW_PS2KBD:
			SetWindowPos(hWnd, 0, 0, 0, WINDOW_W, WINDOW_H_PC, SWP_NOZORDER|SWP_NOMOVE);
			break;
		case ID_V_HIDE_PS2KBD:
			SetWindowPos(hWnd, 0, 0, 0, WINDOW_W, WINDOW_H_MSX, SWP_NOZORDER|SWP_NOMOVE);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

static LRESULT handler_WM_PAINT(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// GDI
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);

	// キー押下状態からキーボード描画内容を決める
	g_DrawKeybordState.ZeroClear();
	for( auto vkeyCd : g_InputVKey ){
		const auto kc109Cd = g_VKey.GetKC109CodeFromVKey(vkeyCd);
		const auto msxCd = g_VKey.GetMsxCodeFromKC109(kc109Cd);
		g_DrawKeybordState.bKC109[kc109Cd] = true;
		g_DrawKeybordState.bMSX[msxCd] = true;
	}
	for( auto kc109Cd : g_InputKC109Key ){
		const auto msxCd = g_VKey.GetMsxCodeFromKC109(kc109Cd);
		g_DrawKeybordState.bMSX[msxCd] = true;
		g_DrawKeybordState.bKC109[kc109Cd] = true;
	}
	for( auto msxCd : g_InputMSXKey ){
		const auto kc109Cd = g_VKey.GetKC109CodeFromMSX(msxCd);
		g_DrawKeybordState.bMSX[msxCd] = true;
		g_DrawKeybordState.bKC109[kc109Cd] = true;
	}

	// Direct2D
	g_pD2d->BeginDraw();

	// フォーカス状態で背景色を変更して、操作可能な状態か見た目ですぐに判断できるようにする
	g_pD2d->Clear((g_bFocus) ? RGBREF(0xFFFFFF) : RGBREF(0x8080B0));

	// COM port & PS/2 power
	const TCHAR *pComm = (g_Com.IsOpend()) ? g_Com.GetPortName().c_str() : _T("COM NG");
	const DWORD commTextCol = (g_Com.IsOpend())?RGBREF(0x4040FF):RGBREF(0xFF04040);
	g_pD2d->Text(4, 2, CD2d::FONT::ARIAL_12, pComm, commTextCol);
	const TCHAR *pPow = (g_Ps2PowerStatus) ? _T("PS/2 OK") : _T("PS/2 NG");
	const DWORD powTextCol = (g_Ps2PowerStatus) ? RGBREF(0x4040FF) : RGBREF(0xFF04040);
	g_pD2d->Text(60, 2, CD2d::FONT::ARIAL_12, pPow, powTextCol);
	
	// MSXキーボードの描画
	g_pD2d->Text(KBMSX_ORG_X, KBMSX_ORG_Y-24.f, CD2d::FONT::ARIAL_12, _T("MSX keyboard"), RGBREF(0x000000), 0.6f);
	g_pD2d->RectPaint(KBMSX_ORG_X, KBMSX_ORG_Y-10, 768, 4, RGBREF(0x000000), 0.2f);
	DrawMsxKeyboard(*g_pD2d, KBMSX_ORG_X, KBMSX_ORG_Y, g_VKey, g_DrawKeybordState.bMSX);
	DrawMsxIndicator(*g_pD2d, KBMSX_ORG_X, KBMSX_ORG_Y, g_LedState);

	// PS/2キーボードの描画
	g_pD2d->Text(KB109_ORG_X, KB109_ORG_Y-24.f, CD2d::FONT::ARIAL_12, _T("PS/2 keyboard"), RGBREF(0x000000), 0.6f);
	g_pD2d->RectPaint(KB109_ORG_X, KB109_ORG_Y-10, 768, 4, RGBREF(0x000000), 0.2f);
	DrawKC109Keyboard(*g_pD2d, KB109_ORG_X, KB109_ORG_Y, g_VKey, g_DrawKeybordState.bKC109);
	DrawKC109Indicator(*g_pD2d, KB109_ORG_X, KB109_ORG_Y, g_LedState);

	g_pD2d->EndDraw();
	return 0;
}

static LRESULT handler_WM_DEVICECHANGE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case DBT_DEVICEARRIVAL:
		{
			if( g_Com.IsOpend() || g_RequestComportName.empty() )
				break;
			std::vector<COMM_NAMES> coms;
			CComPort::GetListupComs(&coms);
			bool bFound = false;
			for( auto c : coms ){
				if( c.ShortName == g_RequestComportName ){
					bFound = true;
					break;
				}
			}
			if( bFound && !g_RequestComportName.empty()){
				if( g_Com.OpenPort(hWnd, g_RequestComportName) ) {
					g_Com.Send('I');    // 接続確認
					g_Ps2PowerStatus = false;
					REDRAW(hWnd);
				}
			}
			break;
		}
		case DBT_DEVICEREMOVECOMPLETE:
		{
			const tstring &name = g_Com.GetPortName();
			if( !g_Com.IsOpend() || name.empty() )
				break;
			std::vector<COMM_NAMES> coms;
			CComPort::GetListupComs(&coms);
			bool bFound = false;
			for( auto c : coms ){
				if( c.ShortName == name ){
					bFound = true;
					break;
				}
			}
			if( !bFound ){
				g_Com.ClosePort();
				REDRAW(hWnd);
			}
			break;
		}
	}
	return 0;
}

static LRESULT handler_WM_DESTROY(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_Com.ClosePort();
	UnhookWindowsHookEx(g_hMyHook);
	if (g_pD2d != nullptr)
		g_pD2d->Release();
	NDELETE(g_pD2d);
	PostQuitMessage(0);
	return 0;
}

static LRESULT handler_WM_SIZE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pD2d != nullptr){
		RECT wcrect;
		GetClientRect(hWnd, &wcrect);
		g_pD2d->SetViewSize(wcrect.right - wcrect.left, wcrect.bottom - wcrect.top);
		REDRAW(hWnd);
	}
	return 0;
}

static LRESULT handler_WM_LBUTTONDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	bool bRect = false;
	const int mx = static_cast<int>(LOWORD(lParam));
	const int my = static_cast<int>(HIWORD(lParam));
	const auto msxCd = g_VKey.GetHitKeyMsx(KBMSX_ORG_X, KBMSX_ORG_Y, mx, my);
	if (msxCd != KCMSX_NONE){
		// MSXキーボードの押下
		const auto msxIt = g_InputMSXKey.find(msxCd);
		if ( msxIt == g_InputMSXKey.end()) {
			if( sendScnaCodeMarkFromMsx(msxCd, true/*mark*/)){
				g_InputMSXKey.insert(msxCd);
				bRect = true;
			}
		}
	}
	else{
		// PS/2キーボードの押下
		auto kc109Cd = g_VKey.GetHitKey109(KB109_ORG_X, KB109_ORG_Y, mx, my);
		if (kc109Cd != KC109_NONE){
			const auto kc109It = g_InputKC109Key.find(kc109Cd);
			if ( kc109It == g_InputKC109Key.end()) {
				if( sendScnaCodeMarkFrom109(kc109Cd, true/*mark*/)){
					g_InputKC109Key.insert(kc109Cd);
					bRect = true;
				}
			}
		}
	}
	if (bRect) {
		SetCapture(hWnd);
		REDRAW(hWnd);
	}
	return 0;
}

static bool releaseKeyMouse(const HWND hWnd)
{
	bool bRect = false;
	for (auto msxCd : g_InputMSXKey){
		if (sendScnaCodeMarkFromMsx(msxCd, false/*break*/)) {
			bRect = true;
		}
	}
	for (auto kc109Cd : g_InputKC109Key){
		if (sendScnaCodeMarkFrom109(kc109Cd, false/*break*/)){
			bRect = true;
		}
	}
	g_InputMSXKey.clear();
	g_InputKC109Key.clear();
	return bRect;
}

static LRESULT handler_WM_LBUTTONUP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ReleaseCapture();
	if (releaseKeyMouse(hWnd)) {
		REDRAW(hWnd);
	}
	return 0;
}

static LRESULT handler_WM_SETFOCUS(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_bFocus = true;
	REDRAW(hWnd);
	return 0;
}

static LRESULT handler_WM_KILLFOCUS(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_bFocus = false;
	REDRAW(hWnd);
	releaseKeyMouse(hWnd);
	return 0;
}

static LRESULT handler_WM_KEYDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// VKey -> KC109, MSX
	const vkeycode_t srcVKeyCd = static_cast<vkeycode_t>(wParam);
	const uint32_t flag = static_cast<uint32_t>(lParam);
	ML(_T("handler_WM_KEYDOWN %04x  lParam:%04X\n"), srcVKeyCd, flag);
	if( (flag & 0x40000000) != 0 )	// リピートによるWM_KEYDOWNメッセージは無視する
		return 0;
	const vkeycode_t vkeyCd = g_VKey.GetVkeyFromVKey(srcVKeyCd);
	const kc109code_t kc109Cd = g_VKey.GetKC109CodeFromVKey(vkeyCd);
	if (kc109Cd == KC109_NONE)
		return 0; 
	ML(_T("-- VKEY-DOWN:%04x\n"), vkeyCd);
	bool bChanged = false;
	auto *p = g_VKey.GetScanCode(kc109Cd);
	if( sendScnaCode(p, true) ){
		// 押下キーの記録
		g_InputVKey.insert(vkeyCd);
		bChanged = true;
	}
	if (bChanged) {
		REDRAW(hWnd);
	}
	return 0;
}

static LRESULT handler_WM_SYSKEYDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// VKey -> KC109, MSX
	const vkeycode_t srcVKeyCd = static_cast<vkeycode_t>(wParam);
	ML(_T("handler_WM_SYSKEYDOWN %04x  lParam:%04X\n"), srcVKeyCd, (uint32_t)lParam);
	const vkeycode_t vkeyCd = g_VKey.GetVkeyFromVKey(srcVKeyCd);
	const kc109code_t kc109Cd = g_VKey.GetKC109CodeFromVKey(vkeyCd);
	if (kc109Cd == KC109_NONE)
		return 0; 
	ML(_T("-- VKEY-DOWN:%04x\n"), vkeyCd);
	bool bChanged = false;
	auto *p = g_VKey.GetScanCode(kc109Cd);
	if( sendScnaCode(p, true) ){
		// 押下キーの記録
		g_InputVKey.insert(vkeyCd);
		bChanged = true;
	}
	if (bChanged) {
		REDRAW(hWnd);
	}
	return 0;
}


static LRESULT handler_WMA_COMMRECVED(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static uint8_t cmd[20 + 1];
	static uint8_t cmdlen = 0, readlen = 0;
	uint8_t temp[20 + 1];
	size_t rsz = g_Com.Receive(temp, 20);
	ML(_T("len(%d), "), rsz);
	if (rsz == 0)
		return 0;
	for (size_t t = 0; t < rsz; ++t) {
		const uint8_t ch = temp[t];
		ML(_T("%02x,"), ch);
		if (readlen == 0) {
			readlen = ch;   // payload.
			cmdlen = 0;
		}
		else {
			cmd[cmdlen++] = ch;
			if (cmdlen == readlen) {
				ML(_T("len = %d, "), cmdlen);
				callCmdFromPs2(cmd, cmdlen);
				cmdlen = 0;
				readlen = 0;
			}
		}
	}
	ML(_T("\n"));
	return 0;
}

static LRESULT handler_WMA_HOOKKEY(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// VKey -> KC109, MSX
	const vkeycode_t srcVKeyCd = static_cast<vkeycode_t>(wParam);
	const auto flags = static_cast<DWORD>(lParam);
	ML(_T("handler_WMA_HOOKKEY %04x  %08X\n"), srcVKeyCd, flags);
	const vkeycode_t vkeyCd = g_VKey.GetVkeyFromVKey(srcVKeyCd);
	const kc109code_t kc109Cd = g_VKey.GetKC109CodeFromVKey(vkeyCd);
	if (kc109Cd == KC109_NONE)
		return 0; 
	bool bChanged = false;
	const bool bPush = ((flags & LLKHF_UP) == 0);
	if (!bPush) {
		ML(_T("-- VKEY-UP  :%04x\n"), vkeyCd);
		auto it = g_InputVKey.find(vkeyCd);
		if (it != g_InputVKey.end()) {
			// BreakコードをCOMポートに出力する
			auto* p = g_VKey.GetScanCode(kc109Cd);
			if (sendScnaCode(p, false)) {
				// 記録の削除
				g_InputVKey.erase(it);
				bChanged = true;
			}
		}
	}
	if (bChanged){
		REDRAW(hWnd);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
    switch (message)
    {
		case WM_CREATE:			result = handler_WM_CREATE(hWnd, message, wParam, lParam);		break;
		case WM_COMMAND:		result = handler_WM_COMMAND(hWnd, message, wParam, lParam);		break;
		case WM_PAINT:			result = handler_WM_PAINT(hWnd, message, wParam, lParam);		break;
		case WM_DEVICECHANGE:	result = handler_WM_DEVICECHANGE(hWnd, message, wParam, lParam);break;
		case WM_DESTROY:		result = handler_WM_DESTROY(hWnd, message, wParam, lParam);		break;
		case WM_SIZE:			result = handler_WM_SIZE(hWnd, message, wParam, lParam);		break;
		case WM_LBUTTONDOWN:	result = handler_WM_LBUTTONDOWN(hWnd, message, wParam, lParam);	break;
		case WM_LBUTTONUP:		result = handler_WM_LBUTTONUP(hWnd, message, wParam, lParam);	break;
		case WM_SETFOCUS:		result = handler_WM_SETFOCUS(hWnd, message, wParam, lParam);	break;
		case WM_KILLFOCUS:		result = handler_WM_KILLFOCUS(hWnd, message, wParam, lParam);	break;
		case WM_KEYDOWN:		result = handler_WM_KEYDOWN(hWnd, message, wParam, lParam);		break;
		case WM_SYSKEYDOWN:		result = handler_WM_SYSKEYDOWN(hWnd, message, wParam, lParam);	break;
		case WMA_COMMRECVED: 	result = handler_WMA_COMMRECVED(hWnd, message, wParam, lParam);	break;
		case WMA_HOOKKEY:		result = handler_WMA_HOOKKEY(hWnd, message, wParam, lParam);	break;
		default:				result = DefWindowProc(hWnd, message, wParam, lParam);			break;
    }
    return result;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK DlgHdrAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	static HFONT hFont = NULL;
	INT_PTR retc = FALSE;
    switch (message)
    {
		case WM_INITDIALOG:
		{
			hFont = CreateFont(
				24,0,0,0,0,0,0,0,
				DEFAULT_CHARSET/*SHIFTJIS_CHARSET*/,OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,
				_T("Arial Black"));
			HWND hWnd1 = GetDlgItem(hDlg, IDC_STATIC2);
			SendMessage( hWnd1, WM_SETFONT, (WPARAM)hFont, 0);
			retc = TRUE;
			break;
		}

	    case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
				DeleteObject(hFont);
				retc = TRUE;
			}
			break;
		}
    }
	return retc;
}

// COMポートリストのダイアログボックス
INT_PTR CALLBACK DlgHdrComPortList(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	static HFONT hFont = NULL;
	INT_PTR retc = FALSE;
    switch (message)
    {
		case WM_INITDIALOG:
		{
			const HWND hList = GetDlgItem(hDlg, IDC_LIST3);
			std::vector<COMM_NAMES> coms;
			CComPort::GetListupComs(&coms);
			int index = -1;
			for( int t = 0; t < static_cast<int>(coms.size()); ++t){
				auto &c = coms[t];
				SendMessage(
					hList, LB_INSERTSTRING,
					(WPARAM)(t), reinterpret_cast<LPARAM>(c.Name.c_str()));
				if (g_Com.IsOpend() && g_Com.GetPortName() == c.ShortName) {
					index = t;
				}
			}
			if( 0 <= index ) {
				// 選択カーソルを表示する
				SendMessage(hList, LB_SETCURSEL, index, 0);
			}
			retc = TRUE;
			break;
		}

	    case WM_COMMAND:
		{
			// [OK] もしくは ダブルクリック
			if (HIWORD(wParam) == LBN_DBLCLK || LOWORD(wParam) == IDOK) {
				const HWND hList = GetDlgItem(hDlg, IDC_LIST3);
				std::vector<COMM_NAMES> coms;
				CComPort::GetListupComs(&coms);
				if (!coms.empty()) {
					LRESULT index = SendMessage(hList, LB_GETCURSEL, 0, 0);
					if (index != LB_ERR) {
						g_Com.ClosePort();
						g_RequestComportName = coms[index].ShortName;
						if (g_Com.OpenPort(g_hWnd, g_RequestComportName)) {
							g_Com.Send('I');    // 接続確認
							g_Ps2PowerStatus = false;
						}
					}
					retc = TRUE;
				}
			}
			// [キャンセル]
			else if (LOWORD(wParam) == IDCANCEL) {
				retc = TRUE;
			}
			////
			if (retc){
				EndDialog(hDlg, LOWORD(wParam));
			}
			break;
		}
    }
	return retc;
}

static const std::vector<tstring> *getArgvs(const tstring &str)
{
	std::vector<tstring> *pList = NNEW std::vector<tstring>();

	const TCHAR sep1[] = { _T(" ;\n\r") };
	TCHAR *pToken = const_cast<TCHAR*>(str.c_str());
	TCHAR *pTokenLine, *pNextTolenLine = nullptr;
	pTokenLine = _tcstok_s(pToken, sep1, &pNextTolenLine);

	while (pTokenLine != nullptr)
	{
		pList->push_back(pTokenLine);
		pTokenLine = _tcstok_s(nullptr, sep1, &pNextTolenLine);
	}
	return pList;
}

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
#if !defined(NDEBUG) && defined(CHECK_LEAK_MEMORY)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINPS2VKBD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
	std::unique_ptr<const std::vector<tstring>> pArgs(getArgvs(lpCmdLine));
    if (!InitInstance(hInstance, nCmdShow, *pArgs))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINPS2VKBD));
    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}