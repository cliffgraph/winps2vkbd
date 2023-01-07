#include "pch.h"
#include "DrawKey.h"
#include "CD2d.h"
#include "tdebug.h"

static void drawKey(
	CD2d &d2d, const KEY_LAYOUT &key,
	const int sx, const int sy,
	const bool bOn)
{
	auto x = static_cast<float>(sx + key.bx * BLOCK_W);
	auto y = static_cast<float>(sy + key.by * BLOCK_H);
	auto w = static_cast<float>(key.bw * BLOCK_W - 1);
	auto h = static_cast<float>(key.bh * BLOCK_H - 1);

	if (bOn) {
		d2d.RectPaint(x, y, w, h, 4.0f, RGBREF(0xF0A0A0));
		d2d.TextInRect(x, y, w, h, CD2d::FONT::ARIAL_10, key.pCap, RGBREF(0x600000));
	}
	else {
		d2d.Rect(x, y, w, h, 1.0f, 4.0f, RGBREF(0x101010));
		d2d.TextInRect(x, y, w, h, CD2d::FONT::ARIAL_10, key.pCap, RGBREF(0x000000));
	}
	return;
}

void DrawKC109Keyboard(CD2d &d2d, int baseX, int baseY, const CVkey &keys, const bool pStste[])
{
	const int num = keys.GetNumKC109KeyOfLayout();
	for( int t = 0; t < num; ++t)
	{
		const KC109_KEY_LAYOUT *pK = keys.GetXYKC109(t+1);
		if( pK == nullptr )
			continue;
		drawKey(d2d, pK->lay, baseX, baseY, pStste[pK->kc109key]);
	}
	return;
}

void DrawKC109Indicator(CD2d &d2d, int baseX, int baseY, const uint8_t led)
{
	const static KEY_LAYOUT caps = {38,1,3,1,_T("casp")};
	const static KEY_LAYOUT sclk = {41,1,3,1,_T("sclk")};
	const static KEY_LAYOUT num =  {44,1,3,1,_T("num")};
	drawKey(d2d, sclk, baseX, baseY, ((led&0x01)!=0));
	drawKey(d2d, num,  baseX, baseY, ((led&0x02)!=0));
	drawKey(d2d, caps, baseX, baseY, ((led&0x04)!= 0));
	return;
}

void DrawMsxIndicator(CD2d &d2d, int baseX, int baseY, const uint8_t led)
{
	const static KEY_LAYOUT caps = { 2,11,1,1,_T("")};	// caps
	const static KEY_LAYOUT num =  {23,11,1,1,_T("")};	// kana
	drawKey(d2d, num,  baseX, baseY, ((led&0x02)!=0));
	drawKey(d2d, caps, baseX, baseY, ((led&0x04) != 0));
	return;
}

void DrawMsxKeyboard(CD2d &d2d, int baseX, int baseY, const CVkey &keys, const bool pStste[])
{
	const int num = keys.GetNumMsxKeyOfLayout();
	for( int t = 0; t < num; ++t)
	{
		const MSX_KEY_LAYOUT *pK = keys.GetXYMSX(t+1);
		if( pK == nullptr )
			continue;
		drawKey(d2d, pK->lay, baseX, baseY, pStste[pK->msxKey]);
	}
	return;
}
