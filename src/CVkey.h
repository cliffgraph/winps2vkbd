#pragma once 

#include "pch.h"
#include "KeyCode.h"
#include <map>

#define BLOCK_W (16)
#define BLOCK_H (16)

struct CONV_VKEY_VKEY
{
	vkeycode_t 	srcVKey;
	vkeycode_t 	destVKey;
};

struct PATCH_VKEY_KC109
{
	vkeycode_t 	winVKey;
	kc109code_t	ps109Key;
};

struct PATCH_KC109_MSX
{
	kc109code_t	ps109Key;
	msxcode_t	msxKey;
};

struct PATCH_MSX_KC109
{
	msxcode_t	msxKey;
	kc109code_t	ps109Key;
};

struct KC109_SCANCODE
{
	kc109code_t	kc109key;
	uint8_t	 lenPs2Mark;
	uint8_t	 ps2Mark[5];
	uint8_t	 lenPs2Break;
	uint8_t	 ps2Break[7];
};

struct KEY_LAYOUT
{
	int			bx, by, bw, bh;	// ブロック単位
	const TCHAR	*pCap;
};

struct KC109_KEY_LAYOUT
{
	kc109code_t	kc109key;
	KEY_LAYOUT	lay;
};

struct MSX_KEY_LAYOUT
{
	msxcode_t	msxKey;
	KEY_LAYOUT	lay;
};

class CVkey
{
private:
	// 一部仮想キーコード -> 仮想キーコード
	typedef std::map<uint16_t/*vkey*/,const CONV_VKEY_VKEY*> VKEYCONV_MAP;
	VKEYCONV_MAP m_ConvVkeyVkey;

	// 109キーコード -> スキャンコード（この対応は固定）
	typedef std::map<kc109code_t,const KC109_SCANCODE*> KC109SCANCODE_MAP;
	KC109SCANCODE_MAP m_Kc109ScanCode;

	// 仮想キーコード -> 109キーコード
	typedef std::map<uint16_t/*vkey*/,const PATCH_VKEY_KC109> VKEYKC109_MAP;
	VKEYKC109_MAP m_PatchVkeyKc109;

	// 109キーコード -> MSXキーコード
	typedef std::map<uint16_t/*vkey*/,const PATCH_KC109_MSX> KC109MSX_MAP;
	KC109MSX_MAP m_PatchKc109Msx;

	// MSXキーコード -> 109キーコード -> 
	typedef std::map<uint16_t/*vkey*/,const PATCH_MSX_KC109> MSXKC109_MAP;
	MSXKC109_MAP m_PatchMsxKc109;

public:
	CVkey();
	virtual ~CVkey();

public:
	// 一部の仮想キーコードを別の仮想キーコードに置き換える
	vkeycode_t GetVkeyFromVKey(const vkeycode_t vkey) const;
	// 仮想キーコードから対応する109キーコードを得る
	kc109code_t GetKC109CodeFromVKey(const vkeycode_t vkey) const;
	// MSXキーコードから対応する109キーコードを得る
	kc109code_t GetKC109CodeFromMSX(const msxcode_t msxCd) const;
	// 109キーコードから対応するMSXキーコードを得る
	msxcode_t GetMsxCodeFromKC109(const kc109code_t kc109Cd) const;
	// 109キーコードからPS/2スキャンコードを得る
	const KC109_SCANCODE *GetScanCode(const kc109code_t kc109Cd) const;

	// 109キーの座標
	int GetNumKC109KeyOfLayout() const;
	const KC109_KEY_LAYOUT *GetXYKC109(const int no) const;
	// MSXキーの座標
	int GetNumMsxKeyOfLayout() const;
	const MSX_KEY_LAYOUT *GetXYMSX(const int no) const;

	// 座標からキーコードを得る
	kc109code_t GetHitKey109(
		const int baseX, const int baseY, const int mouseX, const int mouseY) const;
	msxcode_t GetHitKeyMsx(
		const int baseX, const int baseY, const int mouseX, const int mouseY) const;
};

