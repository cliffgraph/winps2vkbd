﻿#pragma once
#include "pch.h"

typedef int vkeycode_t;	// Virtual Key Code
#define	MAX_VKEYCODE		(VK_OEM_CLEAR)	// 仮想キーコードの最大値

// 109Keybord keycode
enum kc109code_t
{
	KC109_NONE = 0,
	KC109_HANZEN = 1,
	KC109_BACK = 15,
	KC109_TAB = 16,
	KC109_ENTER = 43,
	KC109_PAUSE = 126,
	KC109_CAPITAL = 30,
	KC109_KANA = 133,
	KC109_ESCAPE = 110,
	KC109_CONVERT = 132,
	KC109_NONCONVERT = 131,
	KC109_SPACE = 61,
	KC109_PRIOR = 85,
	KC109_NEXT = 86,
	KC109_END = 81,
	KC109_HOME = 80,
	KC109_LEFT = 79,
	KC109_UP = 83,
	KC109_RIGHT = 89,
	KC109_DOWN = 84,
	KC109_SNAPSHOT = 124,
	KC109_INSERT = 75,
	KC109_DELETE = 76,
	KC109_0 = 11,
	KC109_1 = 2,
	KC109_2 = 3,
	KC109_3 = 4,
	KC109_4 = 5,
	KC109_5 = 6,
	KC109_6 = 7,
	KC109_7 = 8,
	KC109_8 = 9,
	KC109_9 = 10,
	KC109_A = 31,
	KC109_B = 50,
	KC109_C = 48,
	KC109_D = 33,
	KC109_E = 19,
	KC109_F = 34,
	KC109_G = 35,
	KC109_H = 36,
	KC109_I = 24,
	KC109_J = 37,
	KC109_K = 38,
	KC109_L = 39,
	KC109_M = 52,
	KC109_N = 51,
	KC109_O = 25,
	KC109_P = 26,
	KC109_Q = 17,
	KC109_R = 20,
	KC109_S = 32,
	KC109_T = 21,
	KC109_U = 23,
	KC109_V = 49,
	KC109_W = 18,
	KC109_X = 47,
	KC109_Y = 22,
	KC109_Z = 46,
	KC109_LWIN = 134,
	KC109_RWIN = 135,
	KC109_APPS = 136,
	KC109_NUMPAD0 = 99,
	KC109_NUMPAD1 = 93,
	KC109_NUMPAD2 = 98,
	KC109_NUMPAD3 = 103,
	KC109_NUMPAD4 = 92,
	KC109_NUMPAD5 = 97,
	KC109_NUMPAD6 = 102,
	KC109_NUMPAD7 = 91,
	KC109_NUMPAD8 = 96,
	KC109_NUMPAD9 = 101,
	KC109_NUMENTER =108,
	KC109_MULTIPLY = 100,
	KC109_ADD = 106,
	KC109_SUBTRACT = 105,
	KC109_DECIMAL = 104,
	KC109_DIVIDE = 95,
	KC109_F1 = 112,
	KC109_F2 = 113,
	KC109_F3 = 114,
	KC109_F4 = 115,
	KC109_F5 = 116,
	KC109_F6 = 117,
	KC109_F7 = 118,
	KC109_F8 = 119,
	KC109_F9 = 120,
	KC109_F10 = 121,
	KC109_F11 = 122,
	KC109_F12 = 123,
	KC109_NUMLOCK = 90,
	KC109_SCROLL = 125,
	KC109_LSHIFT = 44,
	KC109_RSHIFT = 57,
	KC109_LCONTROL = 58,
	KC109_RCONTROL = 64,
	KC109_LMENU = 60,		// L[Alt]
	KC109_RMENU = 62,		// R[Alt]
	KC109_OEM_1 = 41,		// [:*]
	KC109_OEM_PLUS = 40,
	KC109_OEM_COMMA = 53,
	KC109_OEM_MINUS = 12,
	KC109_OEM_PERIOD = 54,
	KC109_OEM_2 = 55,	// [/?]
	KC109_OEM_3 = 27,	// [@`]
	KC109_OEM_4 = 28,	// [[{]
	KC109_OEM_5 = 14,	// [\|]
	KC109_OEM_6 = 42,	// []}]
	KC109_OEM_7 = 13,	// [^~]
	KC109_OEM_102 = 56,	// 	[＼_]
	//
	KC109_SHIFT_SNAPSHOT = 137,
	KC109_SHIFT_SCROLL = 138,
	KC109_SHIFT_F9 = 139,
	KC109_SHIFT_F10 = 140,
	KC109_SHIFT_F11 = 141,
	KC109_SHIFT_F12 = 142,
};
#define	MAX_KC109KEYCODE	(KC109_SHIFT_F12)	// PS/2キーコードの最大値


// MSX-Keybord keycode
enum msxcode_t
{
	KCMSX_NONE = 0,
	KCMSX_BACK = 62,
	KCMSX_TAB = 60,
	KCMSX_RETURN = 64,
	KCMSX_CAPS = 52,
	KCMSX_KANA = 53,
	KCMSX_ESC = 59,
	KCMSX_SPACE = 65,
	KCMSX_STOP = 61,
	KCMSX_CLSHOME = 66,
	KCMSX_LEFT = 69,
	KCMSX_UP = 70,
	KCMSX_RIGHT = 72,
	KCMSX_DOWN = 71,
	KCMSX_SELECT = 63,
	KCMSX_INSERT = 67,
	KCMSX_DELETE = 68,
	KCMSX_0 = 1,
	KCMSX_1 = 2,
	KCMSX_2 = 3,
	KCMSX_3 = 4,
	KCMSX_4 = 5,
	KCMSX_5 = 6,
	KCMSX_6 = 7,
	KCMSX_7 = 8,
	KCMSX_8 = 9,
	KCMSX_9 = 10,
	KCMSX_A = 23,
	KCMSX_B = 24,
	KCMSX_C = 25,
	KCMSX_D = 26,
	KCMSX_E = 27,
	KCMSX_F = 28,
	KCMSX_G = 29,
	KCMSX_H = 30,
	KCMSX_I = 31,
	KCMSX_J = 32,
	KCMSX_K = 33,
	KCMSX_L = 34,
	KCMSX_M = 35,
	KCMSX_N = 36,
	KCMSX_O = 37,
	KCMSX_P = 38,
	KCMSX_Q = 39,
	KCMSX_R = 40,
	KCMSX_S = 41,
	KCMSX_T = 42,
	KCMSX_U = 43,
	KCMSX_V = 44,
	KCMSX_W = 45,
	KCMSX_X = 46,
	KCMSX_Y = 47,
	KCMSX_Z = 48,
	KCMSX_NUMPAD0 = 76,
	KCMSX_NUMPAD1 = 77,
	KCMSX_NUMPAD2 = 78,
	KCMSX_NUMPAD3 = 79,
	KCMSX_NUMPAD4 = 80,
	KCMSX_NUMPAD5 = 81,
	KCMSX_NUMPAD6 = 82,
	KCMSX_NUMPAD7 = 83,
	KCMSX_NUMPAD8 = 84,
	KCMSX_NUMPAD9 = 85,
	KCMSX_MULTIPLY = 74,
	KCMSX_NUMADD = 75,
	KCMSX_NUMSUB = 86,
	KCMSX_NUMDIV = 73,
	KCMSX_NUMPERIOD = 88,
	KCMSX_NUMCOMMA = 89,
	KCMSX_F6F1 = 54,
	KCMSX_F7F2 = 55,
	KCMSX_F8F3 = 56,
	KCMSX_F9F4 = 57,
	KCMSX_F10F5 = 58,
	KCMSX_SHIFT = 49,
	KCMSX_CONTROL = 50,
	KCMSX_GRAPH = 51,
	KCMSX_MINUS = 11,
	KCMSX_HAT = 12,		// [^]
	KCMSX_YEN = 13,		// [\]
	KCMSX_AT = 14,		// [@]
	KCMSX_SK = 15,		// [[]
	KCMSX_PLUS = 16,
	KCMSX_COLON = 17,	//[:]
	KCMSX_EK = 18,		// []]
	KCMSX_COMMA = 19,
	KCMSX_PERIOD = 20,
	KCMSX_SLASH = 21,		//[/]
	KCMSX_BACKSLASH = 22,	//[_]
	KCMSX_PSG_UP = 100,
	KCMSX_PSG_DN = 101,
	KCMSX_FM_UP = 102,
	KCMSX_FM_DN = 103,
	KCMSX_SCC_UP = 104,
	KCMSX_SCC_DN = 105,
	KCMSX_MST_UP = 106,
	KCMSX_MST_DN = 107,
	KCMSX_CPU = 108,
	KCMSX_VIDEO = 109,
	KCMSX_OPL3 = 110,
	KCMSX_SLOT1 = 111,
	KCMSX_SLOT2 = 112,
};
#define	MAX_MSXKEYCODE		(KCMSX_SLOT2)	// MSXキーコードの最大値

