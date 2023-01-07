#pragma once 
#include "pch.h"
#include "CVkey.h"

class CD2d;
void DrawKC109Keyboard(CD2d &d2d, int baseX, int baseY, const CVkey &keys);
void DrawKC109Keyboard(CD2d &d2d, int baseX, int baseY, const CVkey &keys, const bool pStste[]);
void DrawKC109Indicator(CD2d &d2d, int baseX, int baseY, const uint8_t led);
void DrawMsxKeyboard(CD2d &d2d, int baseX, int baseY, const CVkey &keys, const bool pStste[]);
void DrawMsxIndicator(CD2d &d2d, int baseX, int baseY, const uint8_t led);

