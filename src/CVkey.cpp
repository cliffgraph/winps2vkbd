
#include "pch.h"
#include "CVkey.h"
#include "tchar.h"

// 参考：https://ameblo.jp/sgl00044/entry-12518292302.html
// 参考：http://hp.vector.co.jp/authors/VA037406/html/ps2interface.htm

// 109キースキャンコード（固定情報）
static const KC109_SCANCODE g_RawKc109ScanCodeTable[] = 
{
	{ KC109_HANZEN,				1, { 0x0e, },					2, { 0xf0, 0x0e, }					},
	{ KC109_BACK,				1, { 0x66, },					2, { 0xf0, 0x66, }					},
	{ KC109_TAB,				1, { 0x0d, },					2, { 0xf0, 0x0d, } 					},
	{ KC109_ENTER,				1, { 0x5a, },					2, { 0xf0, 0x5a, } 					},
	{ KC109_PAUSE,				3, { 0xe1, 0x14, 0x77, 0x00 },	5, { 0xe1, 0xf0, 0x14, 0xf0, 0x77}	},
	{ KC109_CAPITAL,			1, { 0x58, },					2, { 0xf0, 0x58, }					},
	{ KC109_KANA,				1, { 0x13, },					2, { 0xf0, 0x13, }					},
	{ KC109_ESCAPE,				1, { 0x76, },					2, { 0xf0, 0x76, }					},
	{ KC109_CONVERT,			1, { 0x64, },					2, { 0xf0, 0x64, }					},	// 変換
	{ KC109_NONCONVERT,			1, { 0x67, },					2, { 0xf0, 0x67, }					},	// 無変換
	{ KC109_SPACE,				1, { 0x29, },					2, { 0xf0, 0x29, } 					},
	{ KC109_PRIOR,				2, { 0xe0, 0x7d, },				3, { 0xe0, 0xf0, 0x7d, }			},	// page up
	{ KC109_NEXT,				2, { 0xe0, 0x7a, },				3, { 0xe0, 0xf0, 0x7a, }			},	// page down
	{ KC109_END,				2, { 0xe0, 0x69, },				3, { 0xe0, 0xf0, 0x69, }			},
	{ KC109_HOME,				2, { 0xe0, 0x6c, },				3, { 0xe0, 0xf0, 0x6c, }			},
	{ KC109_LEFT,				2, { 0xe0, 0x6b, },				3, { 0xe0, 0xf0, 0x6b, }			},
	{ KC109_UP,					2, { 0xe0, 0x75, },				3, { 0xe0, 0xf0, 0x75, }			},
	{ KC109_RIGHT,				2, { 0xe0, 0x74, },				3, { 0xe0, 0xf0, 0x74, }			},
	{ KC109_DOWN,				2, { 0xe0, 0x72, },				3, { 0xe0, 0xf0, 0x72, }			},
	{ KC109_SNAPSHOT,			4, { 0xe0, 0x12, 0xe0, 0x7c },	5, { 0xe0, 0xf0, 0x7c, 0xe0, 0x12}	},
	{ KC109_INSERT,				2, { 0xe0, 0x70, },				3, { 0xe0, 0xf0, 0x70, }			},
	{ KC109_DELETE,				2, { 0xe0, 0x71, },				3, { 0xe0, 0xf0, 0x71, }			},
	{ KC109_0,					1, { 0x45, },					2, { 0xf0, 0x45, }					},
	{ KC109_1,					1, { 0x16, },					2, { 0xf0, 0x16, }					},
	{ KC109_2,					1, { 0x1e, },					2, { 0xf0, 0x1e, }					},
	{ KC109_3,					1, { 0x26, },					2, { 0xf0, 0x26, }					},
	{ KC109_4,					1, { 0x25, },					2, { 0xf0, 0x25, }					},
	{ KC109_5,					1, { 0x2e, },					2, { 0xf0, 0x2e, }					},
	{ KC109_6,					1, { 0x36, },					2, { 0xf0, 0x36, }					},
	{ KC109_7,					1, { 0x3d, },					2, { 0xf0, 0x3d, }					},
	{ KC109_8,					1, { 0x3e, },					2, { 0xf0, 0x3e, }					},
	{ KC109_9,					1, { 0x46, },					2, { 0xf0, 0x46, }					},
	{ KC109_A,					1, { 0x1c, },					2, { 0xf0, 0x1c, }					},
	{ KC109_B,					1, { 0x32, },					2, { 0xf0, 0x32, }					},
	{ KC109_C,					1, { 0x21, },					2, { 0xf0, 0x21, }					},
	{ KC109_D,					1, { 0x23, },					2, { 0xf0, 0x23, }					},
	{ KC109_E,					1, { 0x24, },					2, { 0xf0, 0x24, }					},
	{ KC109_F,					1, { 0x2b, },					2, { 0xf0, 0x2b, }					},
	{ KC109_G,					1, { 0x34, },					2, { 0xf0, 0x34, }					},
	{ KC109_H,					1, { 0x33, },					2, { 0xf0, 0x33, }					},
	{ KC109_I,					1, { 0x43, },					2, { 0xf0, 0x43, }					},
	{ KC109_J,					1, { 0x3b, },					2, { 0xf0, 0x3b, }					},
	{ KC109_K,					1, { 0x42, },					2, { 0xf0, 0x42, }					},
	{ KC109_L,					1, { 0x4b, },					2, { 0xf0, 0x4b, }					},
	{ KC109_M,					1, { 0x3a, },					2, { 0xf0, 0x3a, }					},
	{ KC109_N,					1, { 0x31, },					2, { 0xf0, 0x31, }					},
	{ KC109_O,					1, { 0x44, },					2, { 0xf0, 0x44, }					},
	{ KC109_P,					1, { 0x4d, },					2, { 0xf0, 0x4d, }					},
	{ KC109_Q,					1, { 0x15, },					2, { 0xf0, 0x15, }					},
	{ KC109_R,					1, { 0x2d, },					2, { 0xf0, 0x2d, }					},
	{ KC109_S,					1, { 0x1b, },					2, { 0xf0, 0x1b, }					},
	{ KC109_T,					1, { 0x2c, },					2, { 0xf0, 0x2c, }					},
	{ KC109_U,					1, { 0x3c, },					2, { 0xf0, 0x3c, }					},
	{ KC109_V,					1, { 0x2a, },					2, { 0xf0, 0x2a, }					},
	{ KC109_W,					1, { 0x1d, },					2, { 0xf0, 0x1d, }					},
	{ KC109_X,					1, { 0x22, },					2, { 0xf0, 0x22, }					},
	{ KC109_Y,					1, { 0x35, },					2, { 0xf0, 0x35, }					},
	{ KC109_Z,					1, { 0x1a, },					2, { 0xf0, 0x1a, }					},
	{ KC109_LWIN,				2, { 0xe0, 0x1f, },				3, { 0xe0, 0xf0, 0x1f, }			},
	{ KC109_RWIN,				2, { 0xe0, 0x27, },				3, { 0xe0, 0xf0, 0x27, }			},
	{ KC109_APPS,				0, { 0xe0, 0x2f  },				3, { 0xe0, 0xf0, 0x2f, }			},
	{ KC109_NUMPAD0,			1, { 0x70, },					2, { 0xf0, 0x70, }					},
	{ KC109_NUMPAD1,			1, { 0x69, },					2, { 0xf0, 0x69, }					},
	{ KC109_NUMPAD2,			1, { 0x72, },					2, { 0xf0, 0x72, }					},
	{ KC109_NUMPAD3,			1, { 0x7a, },					2, { 0xf0, 0x7a, }					},
	{ KC109_NUMPAD4,			1, { 0x6b, },					2, { 0xf0, 0x6b, }					},
	{ KC109_NUMPAD5,			1, { 0x73, },					2, { 0xf0, 0x73, }					},
	{ KC109_NUMPAD6,			1, { 0x74, },					2, { 0xf0, 0x74, }					},
	{ KC109_NUMPAD7,			1, { 0x6c, },					2, { 0xf0, 0x6c, }					},
	{ KC109_NUMPAD8,			1, { 0x75, },					2, { 0xf0, 0x75, }					},
	{ KC109_NUMPAD9,			1, { 0x7d, },					2, { 0xf0, 0x7d, }					},
	{ KC109_NUMENTER,			2, { 0xe0, 0x5a, },				3, { 0xe0, 0xf0, 0x5a, },			},
	{ KC109_MULTIPLY,			1, { 0x7c, },					2, { 0xf0, 0x7c, }					},
	{ KC109_ADD,				1, { 0x79, },					2, { 0xf0, 0x79 } 					},
	{ KC109_SUBTRACT,			1, { 0x7b, },					2, { 0xf0, 0x7b, } 					},
	{ KC109_DECIMAL,			1, { 0x71, },					2, { 0xf0, 0x71, }					},
	{ KC109_DIVIDE,				2, { 0xe0, 0x4a },				3, { 0xe0, 0xf0, 0x4a, } 			},
	{ KC109_F1,					1, { 0x05, },					2, { 0xf0, 0x05, }					},
	{ KC109_F2,					1, { 0x06, },					2, { 0xf0, 0x06, }					},
	{ KC109_F3,					1, { 0x04, },					2, { 0xf0, 0x04, }					},
	{ KC109_F4,					1, { 0x0C, },					2, { 0xf0, 0x0C, }					},
	{ KC109_F5,					1, { 0x03, },					2, { 0xf0, 0x03, }					},
	{ KC109_F6,					1, { 0x0B, },					2, { 0xf0, 0x0B, }					},
	{ KC109_F7,					1, { 0x83, },					2, { 0xf0, 0x83, }					},
	{ KC109_F8,					1, { 0x0a, },					2, { 0xf0, 0x0a, }					},
	{ KC109_F9,					1, { 0x01, },					2, { 0xf0, 0x01, }					},
	{ KC109_F10,				1, { 0x09, },					2, { 0xf0, 0x09, }					},
	{ KC109_F11,				1, { 0x78, },					2, { 0xf0, 0x78, }					},
	{ KC109_F12,				1, { 0x07, },					2, { 0xf0, 0x07, }					},
	{ KC109_NUMLOCK,			1, { 0x77, },					2, { 0xf0, 0x77 }					},
	{ KC109_SCROLL,				1, { 0x7e, },					2, { 0xf0, 0x7e }					},
	{ KC109_LSHIFT,				1, { 0x12, },					2, { 0xf0, 0x12 }					},
	{ KC109_RSHIFT,				1, { 0x59, },					2, { 0xf0, 0x59 }					},
	{ KC109_LCONTROL,			1, { 0x14  },					2, { 0xf0, 0x14 }					},
	{ KC109_RCONTROL,			2, { 0xe0, 0x14, },				3, { 0xe0, 0xf0, 0x14 }				},
	{ KC109_LMENU,				1, { 0x11 },					2, { 0xf0, 0x11, }					},	// L-ALt
	{ KC109_RMENU,				2, { 0xe0, 0x11 },				3, { 0xe0, 0xf0, 0x11, }			},	// R-ALt
	{ KC109_OEM_1,				1, { 0x52  },					2, { 0xf0, 0x52 }					},	// [:*]
	{ KC109_OEM_PLUS,			1, { 0x4c, },					2, { 0xf0, 0x4c }					},
	{ KC109_OEM_COMMA,			1, { 0x41, },					2, { 0xf0, 0x41 }					},
	{ KC109_OEM_MINUS,			1, { 0x4e, },					2, { 0xf0, 0x4e }					},
	{ KC109_OEM_PERIOD,			1, { 0x49, },					2, { 0xf0, 0x49 }					},
	{ KC109_OEM_2,				1, { 0x4a  },					2, { 0xf0, 0x4a	}					},	// [/?]
	{ KC109_OEM_3,				1, { 0x54  },					2, { 0xf0, 0x54 }					},	// [@`]
	{ KC109_OEM_4,				1, { 0x5b, },					2, { 0xf0, 0x5b, }					},	// [[{]
	{ KC109_OEM_5,				1, { 0x6a, },					2, { 0xf0, 0x6a, }					},	// [\|]
	{ KC109_OEM_6,				1, { 0x5d, },					2, { 0xf0, 0x5d, }					},	// []}]
	{ KC109_OEM_7,				1, { 0x55, },					2, { 0xf0, 0x55, }					},	// [^~]
	{ KC109_OEM_102,			1, { 0x51, },					2, { 0xf0, 0x51, }					},	// 	[＼_]
	//
	{ KC109_SHIFT_SNAPSHOT,		5, { 0x12, 0xe0, 0x12, 0xe0, 0x7c }, 5, { 0xe0, 0xf0, 0x7c, 0xe0, 0x12, 0xf0, 0x12}	},	// [shift]+[PrtScr]
	{ KC109_SHIFT_SCROLL,		2, { 0x12, 0x7e, },				4, { 0xf0, 0x7e, 0xf0, 0x12 }		},	// [shift]+[ScrLk]
	{ KC109_SHIFT_F9,			2, { 0x12, 0x01, },				4, { 0xf0, 0x01, 0xf0, 0x12 }		},	// [shift]+[F9]	
	{ KC109_SHIFT_F10,			2, { 0x12, 0x09, },				4, { 0xf0, 0x09, 0xf0, 0x12 }		},	// [shift]+[F10]	
	{ KC109_SHIFT_F11,			2, { 0x12, 0x78, },				4, { 0xf0, 0x78, 0xf0, 0x12 }		},	// [shift]+[F11]	
	{ KC109_SHIFT_F12,			2, { 0x12, 0x07, },				4, { 0xf0, 0x07, 0xf0, 0x12 }		},	// [shift]+[F12]	
	//
	{ KC109_NONE,				0, { 0x00, },					0, { 0x00,}							},	// table of contents
};


// 仮想キーコード->仮想キーコード
static CONV_VKEY_VKEY g_VKeyVKeyTable[] = 
{
	// 仮想キーコード			仮想キーコード
	{ VK_CONTROL,				VK_LCONTROL,		},
	{ VK_MENU,					VK_LMENU,			},
	{ VK_SHIFT,					VK_LSHIFT,			},
	{ VK_RCONTROL,				VK_LCONTROL,		},
	{ VK_RMENU,					VK_LMENU,			},
	{ VK_RSHIFT,				VK_LSHIFT,			},
	{ 0x0000,					0x0000,				},
};

// 仮想キーコードに対する109キーコード
static PATCH_VKEY_KC109 g_VKeyKc109Table[] = 
{
	// 仮想キーコード			109キーコード
//	{ VK_RESERVED_0x00			KC109_NONE,			},
	{ VK_LBUTTON,				KC109_NONE,			},
	{ VK_RBUTTON,				KC109_NONE,			},
	{ VK_CANCEL,				KC109_NONE,			},
	{ VK_MBUTTON,				KC109_NONE,			},
	{ VK_XBUTTON1,				KC109_NONE,			},
	{ VK_XBUTTON2,				KC109_NONE,			},
//	{ VK_RESERVED_0x07,			KC109_NONE,			},
	{ VK_BACK,					KC109_BACK,			},
	{ VK_TAB,					KC109_TAB,			},
//	{ VK_RESERVED_0x0A,			KC109_NONE,			},
//	{ VK_RESERVED_0x0B,			KC109_NONE,			},
	{ VK_CLEAR,					KC109_NONE,			},
	{ VK_RETURN,				KC109_ENTER,		},
//	{ VK_RESERVED_0x0E,			KC109_NONE,			},
//	{ VK_RESERVED_0x0F,			KC109_NONE,			},
	{ VK_SHIFT,					KC109_NONE,			},
	{ VK_CONTROL,				KC109_NONE,			},
	{ VK_MENU,					KC109_NONE,			},
	{ VK_PAUSE,					KC109_PAUSE,		},
	{ VK_CAPITAL,				KC109_CAPITAL,		},
//	{ VK_KANA,					KC109_KANA,			},
//	{ VK_OEM_COPY,				KC109_KANA,			},		// VK_OEM_COPY = [カタカナ ひらがな] なぜかキーアップを樹徳できないのでこのキー対応しない
//	{ VK_RESERVED_0x16,			KC109_NONE,			},
	{ VK_JUNJA,					KC109_NONE,			},
	{ VK_FINAL,					KC109_NONE,			},
	{ VK_KANJI,					KC109_NONE,			},
//	{ VK_RESERVED_0x1A,			KC109_NONE,			},
	{ VK_ESCAPE,				KC109_ESCAPE,		},
	{ VK_CONVERT,				KC109_CONVERT,		},
	{ VK_NONCONVERT,			KC109_NONCONVERT,	},
	{ VK_ACCEPT,				KC109_NONE,			},
	{ VK_MODECHANGE,			KC109_NONE,			},
	{ VK_SPACE,					KC109_SPACE,		},
	{ VK_PRIOR,					KC109_PRIOR,		},
	{ VK_NEXT,					KC109_NEXT,			},
	{ VK_END,					KC109_END,			},
	{ VK_HOME,					KC109_HOME,			},
	{ VK_LEFT,					KC109_LEFT,			},
	{ VK_UP,					KC109_UP,			},
	{ VK_RIGHT,					KC109_RIGHT,		},
	{ VK_DOWN,					KC109_DOWN,			},
	{ VK_SELECT,				KC109_NONE,			},
	{ VK_PRINT,					KC109_NONE,			},
	{ VK_EXECUTE,				KC109_NONE,			},
	{ VK_SNAPSHOT,				KC109_SNAPSHOT,		},
	{ VK_INSERT,				KC109_INSERT,		},
	{ VK_DELETE,				KC109_DELETE,		},
	{ VK_HELP,					KC109_NONE,			},
	{ 0x30, /* VK_0 */			KC109_0,			},
	{ 0x31, /* VK_1 */			KC109_1,			},
	{ 0x32, /* VK_2 */			KC109_2,			},
	{ 0x33, /* VK_3 */			KC109_3,			},
	{ 0x34, /* VK_4 */			KC109_4,			},
	{ 0x35, /* VK_5 */			KC109_5,			},
	{ 0x36, /* VK_6 */			KC109_6,			},
	{ 0x37, /* VK_7 */			KC109_7,			},
	{ 0x38, /* VK_8 */			KC109_8,			},
	{ 0x39, /* VK_9 */			KC109_9,			},
//	{ VK_RESERVED_0x3A,			KC109_NONE,			},
//	{ VK_RESERVED_0x3B,			KC109_NONE,			},
//	{ VK_RESERVED_0x3C,			KC109_NONE,			},
//	{ VK_RESERVED_0x3D,			KC109_NONE,			},
//	{ VK_RESERVED_0x3E,			KC109_NONE,			},
//	{ VK_RESERVED_0x3F,			KC109_NONE,			},
//	{ VK_RESERVED_0x3G,			KC109_NONE,			},
	{ 0x41, /* VK_A */			KC109_A,			},
	{ 0x42, /* VK_B */			KC109_B,			},
	{ 0x43, /* VK_C */			KC109_C,			},
	{ 0x44, /* VK_D */			KC109_D,			},
	{ 0x45, /* VK_E */			KC109_E,			},
	{ 0x46, /* VK_F */			KC109_F,			},
	{ 0x47, /* VK_G */			KC109_G,			},
	{ 0x48, /* VK_H */			KC109_H,			},
	{ 0x49, /* VK_I */			KC109_I,			},
	{ 0x4A, /* VK_J */			KC109_J,			},
	{ 0x4B, /* VK_K */			KC109_K,			},
	{ 0x4C, /* VK_L */			KC109_L,			},
	{ 0x4D, /* VK_M */			KC109_M,			},
	{ 0x4E, /* VK_N */			KC109_N,			},
	{ 0x4F, /* VK_O */			KC109_O,			},
	{ 0x50, /* VK_P */			KC109_P,			},
	{ 0x51, /* VK_Q */			KC109_Q,			},
	{ 0x52, /* VK_R */			KC109_R,			},
	{ 0x53, /* VK_S */			KC109_S,			},
	{ 0x54, /* VK_T */			KC109_T,			},
	{ 0x55, /* VK_U */			KC109_U,			},
	{ 0x56, /* VK_V */			KC109_V,			},
	{ 0x57, /* VK_W */			KC109_W,			},
	{ 0x58, /* VK_X */			KC109_X,			},
	{ 0x59, /* VK_Y */			KC109_Y,			},
	{ 0x5A, /* VK_Z */			KC109_Z,			},
	{ VK_LWIN,					KC109_LWIN,			},
	{ VK_RWIN,					KC109_RWIN,			},
	{ VK_APPS,					KC109_APPS,			},
//	{ VK_RESERVED_0x5E,			KC109_NONE,			},
	{ VK_SLEEP,					KC109_NONE,			},
	{ VK_NUMPAD0,				KC109_NUMPAD0,		},
	{ VK_NUMPAD1,				KC109_NUMPAD1,		},
	{ VK_NUMPAD2,				KC109_NUMPAD2,		},
	{ VK_NUMPAD3,				KC109_NUMPAD3,		},
	{ VK_NUMPAD4,				KC109_NUMPAD4,		},
	{ VK_NUMPAD5,				KC109_NUMPAD5,		},
	{ VK_NUMPAD6,				KC109_NUMPAD6,		},
	{ VK_NUMPAD7,				KC109_NUMPAD7,		},
	{ VK_NUMPAD8,				KC109_NUMPAD8,		},
	{ VK_NUMPAD9,				KC109_NUMPAD9,		},
	{ VK_MULTIPLY,				KC109_MULTIPLY,		},
	{ VK_ADD,					KC109_ADD,			},
	{ VK_SEPARATOR,				KC109_NONE,			},
	{ VK_SUBTRACT,				KC109_SUBTRACT,		},
	{ VK_DECIMAL,				KC109_DECIMAL,		},
	{ VK_DIVIDE,				KC109_DIVIDE,		},
	{ VK_F1,					KC109_F1,			},
	{ VK_F2,					KC109_F2,			},
	{ VK_F3,					KC109_F3,			},
	{ VK_F4,					KC109_F4,			},
	{ VK_F5,					KC109_F5,			},
	{ VK_F6,					KC109_F6,			},
	{ VK_F7,					KC109_F7,			},
	{ VK_F8,					KC109_F8,			},
	{ VK_F9,					KC109_F9,			},
	{ VK_F10,					KC109_F10,			},
	{ VK_F11,					KC109_F11,			},
	{ VK_F12,					KC109_F12,			},
	{ VK_F13,					KC109_NONE,			},
	{ VK_F14,					KC109_NONE,			},
	{ VK_F15,					KC109_NONE,			},
	{ VK_F16,					KC109_NONE,			},
	{ VK_F17,					KC109_NONE,			},
	{ VK_F18,					KC109_NONE,			},
	{ VK_F19,					KC109_NONE,			},
	{ VK_F20,					KC109_NONE,			},
	{ VK_F21,					KC109_NONE,			},
	{ VK_F22,					KC109_NONE,			},
	{ VK_F23,					KC109_NONE,			},
	{ VK_F24,					KC109_NONE,			},
//	{ VK_RESERVED_0x88,			KC109_NONE,			},
//	{ VK_RESERVED_0x89,			KC109_NONE,			},
//	{ VK_RESERVED_0x8A,			KC109_NONE,			},
//	{ VK_RESERVED_0x8B,			KC109_NONE,			},
//	{ VK_RESERVED_0x8C,			KC109_NONE,			},
//	{ VK_RESERVED_0x8D,			KC109_NONE,			},
//	{ VK_RESERVED_0x8E,			KC109_NONE,			},
//	{ VK_RESERVED_0x8F,			KC109_NONE,			},
	{ VK_NUMLOCK,				KC109_NUMLOCK,		},
	{ VK_SCROLL,				KC109_SCROLL,		},
//	{ VK_RESERVED_0x92,			KC109_NONE,			},
//	{ VK_RESERVED_0x93,			KC109_NONE,			},
//	{ VK_RESERVED_0x94,			KC109_NONE,			},
//	{ VK_RESERVED_0x95,			KC109_NONE,			},
//	{ VK_RESERVED_0x96,			KC109_NONE,			},
//	{ VK_RESERVED_0x97,			KC109_NONE,			},
//	{ VK_RESERVED_0x98,			KC109_NONE,			},
//	{ VK_RESERVED_0x99,			KC109_NONE,			},
//	{ VK_RESERVED_0x9A,			KC109_NONE,			},
//	{ VK_RESERVED_0x9B,			KC109_NONE,			},
//	{ VK_RESERVED_0x9C,			KC109_NONE,			},
//	{ VK_RESERVED_0x9D,			KC109_NONE,			},
//	{ VK_RESERVED_0x9E,			KC109_NONE,			},
//	{ VK_RESERVED_0x9F,			KC109_NONE,			},
	{ VK_LSHIFT,				KC109_LSHIFT,		},
	{ VK_RSHIFT,				KC109_RSHIFT,		},
	{ VK_LCONTROL,				KC109_LCONTROL,		},
	{ VK_RCONTROL,				KC109_RCONTROL,		},
	{ VK_LMENU,					KC109_LMENU,		},
	{ VK_RMENU,					KC109_RMENU,		},
	{ VK_BROWSER_BACK,			KC109_NONE,			},
	{ VK_BROWSER_FORWARD,		KC109_NONE,			},
	{ VK_BROWSER_REFRESH,		KC109_NONE,			},
	{ VK_BROWSER_STOP,			KC109_NONE,			},
	{ VK_BROWSER_SEARCH,		KC109_NONE,			},
	{ VK_BROWSER_FAVORITES,		KC109_NONE,			},
	{ VK_BROWSER_HOME,			KC109_NONE,			},
	{ VK_VOLUME_MUTE,			KC109_NONE,			},
	{ VK_VOLUME_DOWN,			KC109_NONE,			},
	{ VK_VOLUME_UP,				KC109_NONE,			},
	{ VK_MEDIA_NEXT_TRACK,		KC109_NONE,			},
	{ VK_MEDIA_PREV_TRACK,		KC109_NONE,			},
	{ VK_MEDIA_STOP,			KC109_NONE,			},
	{ VK_MEDIA_PLAY_PAUSE,		KC109_NONE,			},
	{ VK_LAUNCH_MAIL,			KC109_NONE,			},
	{ VK_LAUNCH_MEDIA_SELECT,	KC109_NONE,			},
	{ VK_LAUNCH_APP1,			KC109_NONE,			},
	{ VK_LAUNCH_APP1,			KC109_NONE,			},
//	{ VK_RESERVED_0xB8,			KC109_NONE,			},
//	{ VK_RESERVED_0xB9,			KC109_NONE,			},
	{ VK_OEM_1,					KC109_OEM_1,		},
	{ VK_OEM_PLUS,				KC109_OEM_PLUS,		},
	{ VK_OEM_COMMA,				KC109_OEM_COMMA,	},
	{ VK_OEM_MINUS,				KC109_OEM_MINUS,	},
	{ VK_OEM_PERIOD,			KC109_OEM_PERIOD,	},
	{ VK_OEM_2,					KC109_OEM_2,		},
	{ VK_OEM_3,					KC109_OEM_3,		},
//	{ VK_RESERVED_0xC1,			KC109_NONE,			},
//	{ VK_RESERVED_0xC2,			KC109_NONE,			},
//	{ VK_RESERVED_0xC3,			KC109_NONE,			},
//	{ VK_RESERVED_0xC4,			KC109_NONE,			},
//	{ VK_RESERVED_0xC5,			KC109_NONE,			},
//	{ VK_RESERVED_0xC6,			KC109_NONE,			},
//	{ VK_RESERVED_0xC7,			KC109_NONE,			},
//	{ VK_RESERVED_0xC8,			KC109_NONE,			},
//	{ VK_RESERVED_0xC9,			KC109_NONE,			},
//	{ VK_RESERVED_0xCA,			KC109_NONE,			},
//	{ VK_RESERVED_0xCB,			KC109_NONE,			},
//	{ VK_RESERVED_0xCC,			KC109_NONE,			},
//	{ VK_RESERVED_0xCD,			KC109_NONE,			},
//	{ VK_RESERVED_0xCE,			KC109_NONE,			},
//	{ VK_RESERVED_0xCF,			KC109_NONE,			},
//	{ VK_RESERVED_0xD1,			KC109_NONE,			},
//	{ VK_RESERVED_0xD2,			KC109_NONE,			},
//	{ VK_RESERVED_0xD3,			KC109_NONE,			},
//	{ VK_RESERVED_0xD4,			KC109_NONE,			},
//	{ VK_RESERVED_0xD5,			KC109_NONE,			},
//	{ VK_RESERVED_0xD6,			KC109_NONE,			},
//	{ VK_RESERVED_0xD7,			KC109_NONE,			},
//	{ VK_RESERVED_0xD8,			KC109_NONE,			},
//	{ VK_RESERVED_0xD9,			KC109_NONE,			},
//	{ VK_RESERVED_0xDA,			KC109_NONE,			},
	{ VK_OEM_4,					KC109_OEM_4,		},
	{ VK_OEM_5,					KC109_OEM_5,		},
	{ VK_OEM_6,					KC109_OEM_6,		},
	{ VK_OEM_7,					KC109_OEM_7,		},
	{ VK_OEM_8,					KC109_NONE,			},
//	{ VK_RESERVED_0xE0,			KC109_NONE,			},
//	{ VK_RESERVED_0xE1,			KC109_NONE,			},
	{ VK_OEM_102,				KC109_OEM_102,		},
	{ VK_ICO_HELP,				KC109_NONE,			},
	{ VK_ICO_00,				KC109_NONE,			},
	{ VK_PROCESSKEY,			KC109_NONE,			},
	{ VK_ICO_CLEAR,				KC109_NONE,			},
	{ VK_PACKET,				KC109_NONE,			},
//	{ VK_RESERVED_0xE8,			KC109_NONE,			},
	{ VK_OEM_RESET,				KC109_NONE,			},
	{ VK_OEM_JUMP,				KC109_NONE,			},
	{ VK_OEM_PA1,				KC109_NONE,			},
	{ VK_OEM_PA2,				KC109_NONE,			},
	{ VK_OEM_PA3,				KC109_NONE,			},
	{ VK_OEM_WSCTRL,			KC109_NONE,			},
	{ VK_OEM_CUSEL,				KC109_NONE,			},
	{ VK_OEM_ATTN,				KC109_NONE,			},
	{ VK_OEM_FINISH,			KC109_NONE,			},
	{ VK_OEM_COPY,				KC109_NONE,			},
	{ VK_OEM_AUTO,				KC109_NONE,			},
	{ VK_OEM_ENLW,				KC109_NONE,			},
	{ VK_OEM_BACKTAB,			KC109_NONE,			},
	{ VK_ATTN,					KC109_NONE,			},
	{ VK_CRSEL,					KC109_NONE,			},
	{ VK_EXSEL,					KC109_NONE,			},
	{ VK_EREOF,					KC109_NONE,			},
	{ VK_PLAY,					KC109_NONE,			},
	{ VK_ZOOM,					KC109_NONE,			},
	{ VK_NONAME,				KC109_NONE,			},
	{ VK_PA1,					KC109_NONE,			},
	{ VK_OEM_CLEAR,				KC109_NONE,			},
//	{ VK_RESERVED_0xFF,			KC109_NONE,			},
	{ 0,						KC109_NONE,			},
};

// 109キーコードに対するMSXキーコード
static PATCH_KC109_MSX g_Kc109KeyMSXTable[] =
{
	{ KC109_BACK,			KCMSX_BACK,			},
	{ KC109_TAB,			KCMSX_TAB,			},
	{ KC109_ENTER,			KCMSX_RETURN,		},
	{ KC109_PAUSE,			KCMSX_NONE,			},
	{ KC109_CAPITAL,		KCMSX_CAPS,			},
	{ KC109_KANA,			KCMSX_KANA,			},
	{ KC109_ESCAPE,			KCMSX_ESC,			},
	{ KC109_CONVERT,		KCMSX_NONE,			},
	{ KC109_NONCONVERT,		KCMSX_NONE,			},
	{ KC109_SPACE,			KCMSX_SPACE,		},
	{ KC109_PRIOR,			KCMSX_MST_UP,		},
	{ KC109_NEXT,			KCMSX_MST_DN,		},
	{ KC109_END,			KCMSX_STOP,			},
	{ KC109_HOME,			KCMSX_CLSHOME,		},
	{ KC109_LEFT,			KCMSX_LEFT,			},
	{ KC109_UP,				KCMSX_UP,			},
	{ KC109_RIGHT,			KCMSX_RIGHT,		},
	{ KC109_DOWN,			KCMSX_DOWN,			},
	{ KC109_SNAPSHOT,		KCMSX_VIDEO,		},
	{ KC109_INSERT,			KCMSX_INSERT,		},
	{ KC109_DELETE,			KCMSX_DELETE,		},
	{ KC109_0,				KCMSX_0,			},
	{ KC109_1,				KCMSX_1,			},
	{ KC109_2,				KCMSX_2,			},
	{ KC109_3,				KCMSX_3,			},
	{ KC109_4,				KCMSX_4,			},
	{ KC109_5,				KCMSX_5,			},
	{ KC109_6,				KCMSX_6,			},
	{ KC109_7,				KCMSX_7,			},
	{ KC109_8,				KCMSX_8,			},
	{ KC109_9,				KCMSX_9,			},
	{ KC109_A,				KCMSX_A,			},
	{ KC109_B,				KCMSX_B,			},
	{ KC109_C,				KCMSX_C,			},
	{ KC109_D,				KCMSX_D,			},
	{ KC109_E,				KCMSX_E,			},
	{ KC109_F,				KCMSX_F,			},
	{ KC109_G,				KCMSX_G,			},
	{ KC109_H,				KCMSX_H,			},
	{ KC109_I,				KCMSX_I,			},
	{ KC109_J,				KCMSX_J,			},
	{ KC109_K,				KCMSX_K,			},
	{ KC109_L,				KCMSX_L,			},
	{ KC109_M,				KCMSX_M,			},
	{ KC109_N,				KCMSX_N,			},
	{ KC109_O,				KCMSX_O,			},
	{ KC109_P,				KCMSX_P,			},
	{ KC109_Q,				KCMSX_Q,			},
	{ KC109_R,				KCMSX_R,			},
	{ KC109_S,				KCMSX_S,			},
	{ KC109_T,				KCMSX_T,			},
	{ KC109_U,				KCMSX_U,			},
	{ KC109_V,				KCMSX_V,			},
	{ KC109_W,				KCMSX_W,			},
	{ KC109_X,				KCMSX_X,			},
	{ KC109_Y,				KCMSX_Y,			},
	{ KC109_Z,				KCMSX_Z,			},
	{ KC109_LWIN,			KCMSX_NONE,			},
	{ KC109_RWIN,			KCMSX_NONE,			},
	{ KC109_APPS,			KCMSX_NONE,			},
	{ KC109_NUMPAD0,		KCMSX_NUMPAD0,		},
	{ KC109_NUMPAD1,		KCMSX_NUMPAD1,		},
	{ KC109_NUMPAD2,		KCMSX_NUMPAD2,		},
	{ KC109_NUMPAD3,		KCMSX_NUMPAD3,		},
	{ KC109_NUMPAD4,		KCMSX_NUMPAD4,		},
	{ KC109_NUMPAD5,		KCMSX_NUMPAD5,		},
	{ KC109_NUMPAD6,		KCMSX_NUMPAD6,		},
	{ KC109_NUMPAD7,		KCMSX_NUMPAD7,		},
	{ KC109_NUMPAD8,		KCMSX_NUMPAD8,		},
	{ KC109_NUMPAD9,		KCMSX_NUMPAD9,		},
	{ KC109_NUMENTER,		KCMSX_RETURN,		},
	{ KC109_MULTIPLY,		KCMSX_MULTIPLY,		},
	{ KC109_ADD,			KCMSX_NUMADD,		},
	{ KC109_SUBTRACT,		KCMSX_NUMSUB,		},
	{ KC109_DECIMAL,		KCMSX_NUMPERIOD,	},
	{ KC109_DIVIDE,			KCMSX_NUMDIV,		},
	{ KC109_F1,				KCMSX_F6F1,			},
	{ KC109_F2,				KCMSX_F7F2,			},
	{ KC109_F3,				KCMSX_F8F3,			},
	{ KC109_F4,				KCMSX_F9F4,			},
	{ KC109_F5,				KCMSX_F10F5,		},
	{ KC109_F6,				KCMSX_GRAPH,		},
	{ KC109_F7,				KCMSX_KANA,			},
	{ KC109_F8,				KCMSX_SELECT,		},
	{ KC109_F9,				KCMSX_PSG_UP,		},
	{ KC109_F10,			KCMSX_FM_UP,		},
	{ KC109_F11,			KCMSX_SCC_UP,		},
	{ KC109_F12,			KCMSX_CPU,			},
	{ KC109_NUMLOCK,		KCMSX_NONE,			},
	{ KC109_SCROLL,			KCMSX_OPL3,			},
	{ KC109_LSHIFT,			KCMSX_SHIFT,		},
	{ KC109_RSHIFT,			KCMSX_SHIFT,		},
	{ KC109_LCONTROL,		KCMSX_CONTROL,		},
	{ KC109_RCONTROL,		KCMSX_CONTROL,		},
	{ KC109_LMENU,			KCMSX_GRAPH,		},
	{ KC109_RMENU,			KCMSX_GRAPH,		},
	{ KC109_OEM_1,			KCMSX_COLON,		},
	{ KC109_OEM_PLUS,		KCMSX_PLUS,			},
	{ KC109_OEM_COMMA,		KCMSX_COMMA,		},
	{ KC109_OEM_MINUS,		KCMSX_MINUS,		},
	{ KC109_OEM_PERIOD,		KCMSX_PERIOD,		},
	{ KC109_OEM_2,			KCMSX_SLASH,		},
	{ KC109_OEM_3,			KCMSX_AT,			},
	{ KC109_OEM_4,			KCMSX_SK,			},
	{ KC109_OEM_5,			KCMSX_YEN,			},
	{ KC109_OEM_6,			KCMSX_EK,			},
	{ KC109_OEM_7,			KCMSX_HAT,			},
	{ KC109_OEM_102,		KCMSX_BACKSLASH,	},
	{ KC109_NONE,			KCMSX_NONE,			},
	{ KC109_NONE,			KCMSX_PSG_UP,		},
	{ KC109_NONE,			KCMSX_PSG_DN,		},
	{ KC109_NONE,			KCMSX_FM_UP,		},
	{ KC109_NONE,			KCMSX_FM_DN,		},
	{ KC109_NONE,			KCMSX_SCC_UP,		},
	{ KC109_NONE,			KCMSX_SCC_DN,		},
	{ KC109_NONE,			KCMSX_MST_UP,		},
	{ KC109_NONE,			KCMSX_MST_DN,		},
	{ KC109_NONE,			KCMSX_CPU,			},
	{ KC109_NONE,			KCMSX_VIDEO,		},
	{ KC109_NONE,			KCMSX_OPL3,			},
	{ KC109_NONE,			KCMSX_SLOT1,		},
	{ KC109_NONE,			KCMSX_SLOT2,		},
};

// MSXキーコードに対する109キーコード
static PATCH_MSX_KC109 g_MSXKeyKc109Table[] = 
{
	{ KCMSX_BACK,		KC109_BACK,				},
	{ KCMSX_TAB,		KC109_TAB,				},
	{ KCMSX_RETURN,		KC109_ENTER,			},
//	{ KCMSX_NONE,		KC109_PAUSE,			},
	{ KCMSX_CAPS,		KC109_CAPITAL,			},
	{ KCMSX_KANA,		KC109_KANA,				},
	{ KCMSX_ESC,		KC109_ESCAPE,			},
//	{ KCMSX_NONE,		KC109_CONVERT,			},
//	{ KCMSX_NONE,		KC109_NONCONVERT,		},
	{ KCMSX_SPACE,		KC109_SPACE,			},
	{ KCMSX_STOP,		KC109_END,				},
	{ KCMSX_CLSHOME,	KC109_HOME,				},
	{ KCMSX_LEFT,		KC109_LEFT,				},
	{ KCMSX_UP,			KC109_UP,				},
	{ KCMSX_RIGHT,		KC109_RIGHT,			},
	{ KCMSX_DOWN,		KC109_DOWN,				},
	{ KCMSX_INSERT,		KC109_INSERT,			},
	{ KCMSX_DELETE,		KC109_DELETE,			},
	{ KCMSX_0,			KC109_0,				},
	{ KCMSX_1,			KC109_1,				},
	{ KCMSX_2,			KC109_2,				},
	{ KCMSX_3,			KC109_3,				},
	{ KCMSX_4,			KC109_4,				},
	{ KCMSX_5,			KC109_5,				},
	{ KCMSX_6,			KC109_6,				},
	{ KCMSX_7,			KC109_7,				},
	{ KCMSX_8,			KC109_8,				},
	{ KCMSX_9,			KC109_9,				},
	{ KCMSX_A,			KC109_A,				},
	{ KCMSX_B,			KC109_B,				},
	{ KCMSX_C,			KC109_C,				},
	{ KCMSX_D,			KC109_D,				},
	{ KCMSX_E,			KC109_E,				},
	{ KCMSX_F,			KC109_F,				},
	{ KCMSX_G,			KC109_G,				},
	{ KCMSX_H,			KC109_H,				},
	{ KCMSX_I,			KC109_I,				},
	{ KCMSX_J,			KC109_J,				},
	{ KCMSX_K,			KC109_K,				},
	{ KCMSX_L,			KC109_L,				},
	{ KCMSX_M,			KC109_M,				},
	{ KCMSX_N,			KC109_N,				},
	{ KCMSX_O,			KC109_O,				},
	{ KCMSX_P,			KC109_P,				},
	{ KCMSX_Q,			KC109_Q,				},
	{ KCMSX_R,			KC109_R,				},
	{ KCMSX_S,			KC109_S,				},
	{ KCMSX_T,			KC109_T,				},
	{ KCMSX_U,			KC109_U,				},
	{ KCMSX_V,			KC109_V,				},
	{ KCMSX_W,			KC109_W,				},
	{ KCMSX_X,			KC109_X,				},
	{ KCMSX_Y,			KC109_Y,				},
	{ KCMSX_Z,			KC109_Z,				},
//	{ KCMSX_NONE,		KC109_LWIN,				},
//	{ KCMSX_NONE,		KC109_RWIN,				},
//	{ KCMSX_NONE,		KC109_APPS,				},
	{ KCMSX_NUMPAD0,	KC109_NUMPAD0,			},
	{ KCMSX_NUMPAD1,	KC109_NUMPAD1,			},
	{ KCMSX_NUMPAD2,	KC109_NUMPAD2,			},
	{ KCMSX_NUMPAD3,	KC109_NUMPAD3,			},
	{ KCMSX_NUMPAD4,	KC109_NUMPAD4,			},
	{ KCMSX_NUMPAD5,	KC109_NUMPAD5,			},
	{ KCMSX_NUMPAD6,	KC109_NUMPAD6,			},
	{ KCMSX_NUMPAD7,	KC109_NUMPAD7,			},
	{ KCMSX_NUMPAD8,	KC109_NUMPAD8,			},
	{ KCMSX_NUMPAD9,	KC109_NUMPAD9,			},
	{ KCMSX_MULTIPLY,	KC109_MULTIPLY,			},
	{ KCMSX_NUMADD,		KC109_ADD,				},
	{ KCMSX_NUMSUB,		KC109_SUBTRACT,			},
	{ KCMSX_NUMPERIOD,	KC109_DECIMAL,			},
	{ KCMSX_NUMCOMMA,	KC109_NONE,				},
	{ KCMSX_NUMDIV,		KC109_DIVIDE,			},
	{ KCMSX_F6F1,		KC109_F1,				},
	{ KCMSX_F7F2,		KC109_F2,				},
	{ KCMSX_F8F3,		KC109_F3,				},
	{ KCMSX_F9F4,		KC109_F4,				},
	{ KCMSX_F10F5,		KC109_F5,				},
	{ KCMSX_GRAPH,		KC109_F6,				},
	{ KCMSX_KANA,		KC109_F7,				},
	{ KCMSX_SELECT,		KC109_F8,				},
//	{ KCMSX_NONE,		KC109_NUMLOCK,			},
	{ KCMSX_SHIFT,		KC109_LSHIFT,			},
	{ KCMSX_SHIFT,		KC109_RSHIFT,			},
	{ KCMSX_CONTROL,	KC109_LCONTROL,			},
	{ KCMSX_CONTROL,	KC109_RCONTROL,			},
//	{ KCMSX_NONE,		KC109_RMENU,			},
	{ KCMSX_COLON,		KC109_OEM_1,			},
	{ KCMSX_PLUS,		KC109_OEM_PLUS,			},
	{ KCMSX_COMMA,		KC109_OEM_COMMA,		},
	{ KCMSX_MINUS,		KC109_OEM_MINUS,		},
	{ KCMSX_PERIOD,		KC109_OEM_PERIOD,		},
	{ KCMSX_SLASH,		KC109_OEM_2,			},
	{ KCMSX_AT,			KC109_OEM_3,			},
	{ KCMSX_SK,			KC109_OEM_4,			},
	{ KCMSX_YEN,		KC109_OEM_5,			},
	{ KCMSX_EK,			KC109_OEM_6,			},
	{ KCMSX_HAT,		KC109_OEM_7,			},
	{ KCMSX_BACKSLASH,	KC109_OEM_102,			},
//	{ KCMSX_NONE,		KC109_NONE,				},
	{ KCMSX_PSG_UP,		KC109_F9,				},
	{ KCMSX_PSG_DN,		KC109_SHIFT_F9,			},
	{ KCMSX_FM_UP,		KC109_F11,				},
	{ KCMSX_FM_DN,		KC109_SHIFT_F11,		},
	{ KCMSX_SCC_UP,		KC109_F10,				},
	{ KCMSX_SCC_DN,		KC109_SHIFT_F10,		},
	{ KCMSX_MST_UP,		KC109_PRIOR,			},
	{ KCMSX_MST_DN,		KC109_NEXT,				},
	{ KCMSX_CPU,		KC109_F12,				},
	{ KCMSX_VIDEO,		KC109_SNAPSHOT,			},
	{ KCMSX_OPL3,		KC109_SCROLL,			},
	{ KCMSX_SLOT1,		KC109_SHIFT_F12,		},
	{ KCMSX_SLOT2,		KC109_SHIFT_SCROLL,		},
	{ KCMSX_NONE,		KC109_NONE,				},
};

/*
* 109キーボードのキー座標、キャプション
*/
static KC109_KEY_LAYOUT g_RawKc109KeyLayout[] =
{
	{ KC109_HANZEN,		{ 0,3,2,2,		_T("H/Z"),		}},
	{ KC109_BACK,		{ 28,3,2,2,		_T("BS"),		}},	
	{ KC109_TAB,		{ 0,5,2,2,		_T("TAB"),		}},	
	{ KC109_ENTER,		{ 26,5,4,4,		_T("ENT"),		}},	
	{ KC109_PAUSE,		{ 35,0,2,2,		_T("Pause"),	}},	
	{ KC109_CAPITAL,	{ 0,7,2,2,		_T("Caps"),		}},	
	{ KC109_KANA,		{ 20,11,2,2,	_T("Kana"),		}},	
	{ KC109_ESCAPE,		{ 0,0,2,2,		_T("Esc"),		}},	
	{ KC109_CONVERT,	{ 18,11,2,2,	_T("変"),		}},	
	{ KC109_NONCONVERT,	{ 7,11,2,2,		_T("無"),		}},	
	{ KC109_SPACE,		{ 9,11,9,2,		_T("SPACE"),	}},	
	{ KC109_PRIOR,		{ 35,3,2,2,		_T("PgUp"),		}},	
	{ KC109_NEXT,		{ 35,5,2,2,		_T("PgDn"),		}},
	{ KC109_END,		{ 33,5,2,2,		_T("End"),		}},	
	{ KC109_HOME,		{ 33,3,2,2,		_T("Home"),		}},	
	{ KC109_LEFT,		{ 31,11,2,2,	_T("←"),		}},	
	{ KC109_UP,			{ 33,9,2,2,		_T("↑"),		}},	
	{ KC109_RIGHT,		{ 35,11,2,2,	_T("→"),		}},	
	{ KC109_DOWN,		{ 33,11,2,2,	_T("↓"),		}},	
	{ KC109_SNAPSHOT,	{ 31,0,2,2,		_T("Print\nScrn"),		}},	
	{ KC109_INSERT,		{ 31,3,2,2,		_T("Ins"),		}},	
	{ KC109_DELETE,		{ 31,5,2,2,		_T("Del"),		}},	
	{ KC109_0,			{ 20,3,2,2,		_T("0"),		}},	
	{ KC109_1,			{ 2,3,2,2,		_T("1!"),		}},	
	{ KC109_2,			{ 4,3,2,2,		_T("2\""),		}},	
	{ KC109_3,			{ 6,3,2,2,		_T("3#"),		}},	
	{ KC109_4,			{ 8,3,2,2,		_T("4$"),		}},	
	{ KC109_5,			{ 10,3,2,2,		_T("5%"),		}},	
	{ KC109_6,			{ 12,3,2,2,		_T("6&"),		}},	
	{ KC109_7,			{ 14,3,2,2,		_T("7'"),		}},	
	{ KC109_8,			{ 16,3,2,2,		_T("8("),		}},	
	{ KC109_9,			{ 18,3,2,2,		_T("9)"),		}},	
	{ KC109_A,			{ 2,7,2,2,		_T("A"),		}},	
	{ KC109_B,			{ 12,9,2,2,		_T("B"),		}},
	{ KC109_C,			{ 8,9,2,2,		_T("C"),		}},	
	{ KC109_D,			{ 6,7,2,2,		_T("D"),		}},	
	{ KC109_E,			{ 6,5,2,2,		_T("E"),		}},	
	{ KC109_F,			{ 8,7,2,2,		_T("F"),		}},	
	{ KC109_G,			{ 10,7,2,2,		_T("G"),		}},	
	{ KC109_H,			{ 12,7,2,2,		_T("H"),		}},	
	{ KC109_I,			{ 16,5,2,2,		_T("I"),		}},	
	{ KC109_J,			{ 14,7,2,2,		_T("J"),		}},	
	{ KC109_K,			{ 16,7,2,2,		_T("K"),		}},	
	{ KC109_L,			{ 18,7,2,2,		_T("L"),		}},	
	{ KC109_M,			{ 16,9,2,2,		_T("M"),		}},	
	{ KC109_N,			{ 14,9,2,2,		_T("N"),		}},	
	{ KC109_O,			{ 18,5,2,2,		_T("O"),		}},	
	{ KC109_P,			{ 20,5,2,2,		_T("P"),		}},	
	{ KC109_Q,			{ 2,5,2,2,		_T("Q"),		}},	
	{ KC109_R,			{ 8,5,2,2,		_T("R"),		}},	
	{ KC109_S,			{ 4,7,2,2,		_T("S"),		}},	
	{ KC109_T,			{ 10,5,2,2,		_T("T"),		}},	
	{ KC109_U,			{ 14,5,2,2,		_T("U"),		}},	
	{ KC109_V,			{ 10,9,2,2,		_T("V"),		}},	
	{ KC109_W,			{ 4,5,2,2,		_T("W"),		}},	
	{ KC109_X,			{ 6,9,2,2,		_T("X"),		}},	
	{ KC109_Y,			{ 12,5,2,2,		_T("Y"),		}},	
	{ KC109_Z,			{ 4,9,2,2,		_T("Z"),		}},	
	{ KC109_LWIN,		{ 3,11,2,2,		_T("Win"),		}},	
	{ KC109_RWIN,		{ 24,11,2,2,	_T("Win"),		}},	
	{ KC109_APPS,		{ 26,11,2,2,	_T("App"),		}},	
	{ KC109_NUMPAD0,	{ 38,11,4,2,	_T("0"),		}},	
	{ KC109_NUMPAD1,	{ 38,9,2,2,		_T("1"),		}},		
	{ KC109_NUMPAD2,	{ 40,9,2,2,		_T("2"),		}},	
	{ KC109_NUMPAD3,	{ 42,9,2,2,		_T("3"),		}},	
	{ KC109_NUMPAD4,	{ 38,7,2,2,		_T("4"),		}},	
	{ KC109_NUMPAD5,	{ 40,7,2,2,		_T("5"),		}},	
	{ KC109_NUMPAD6,	{ 42,7,2,2,		_T("6"),		}},	
	{ KC109_NUMPAD7,	{ 38,5,2,2,		_T("7"),		}},	
	{ KC109_NUMPAD8,	{ 40,5,2,2,		_T("8"),		}},	
	{ KC109_NUMPAD9,	{ 42,5,2,2,		_T("9"),		}},	
	{ KC109_NUMENTER,	{ 44,9,2,4,		_T("Ent"),		}},	
	{ KC109_MULTIPLY,	{ 42,3,2,2,		_T("*"),		}},	
	{ KC109_ADD,		{ 44,5,2,4,		_T("+"),		}},	
	{ KC109_SUBTRACT,	{ 44,3,2,2,		_T("-"),		}},	
	{ KC109_DECIMAL,	{ 42,11,2,2,	_T("."),		}},	
	{ KC109_DIVIDE,		{ 40,3,2,2,		_T("/"),		}},	
	{ KC109_F1,			{ 4,0,2,2,		_T("F1"),		}},	
	{ KC109_F2,			{ 6,0,2,2,		_T("F2"),		}},	
	{ KC109_F3,			{ 8,0,2,2,		_T("F3"),		}},	
	{ KC109_F4,			{ 10,0,2,2,		_T("F4"),		}},	
	{ KC109_F5,			{ 13,0,2,2,		_T("F5"),		}},	
	{ KC109_F6,			{ 15,0,2,2,		_T("F6"),		}},		
	{ KC109_F7,			{ 17,0,2,2,		_T("F7"),		}},	
	{ KC109_F8,			{ 19,0,2,2,		_T("F8"),		}},	
	{ KC109_F9,			{ 22,0,2,2,		_T("F9"),		}},	
	{ KC109_F10,		{ 24,0,2,2,		_T("F10"),		}},	
	{ KC109_F11,		{ 26,0,2,2,		_T("F11"),		}},	
	{ KC109_F12,		{ 28,0,2,2,		_T("F12"),		}},	
	{ KC109_NUMLOCK,	{ 38,3,2,2,		_T("Num"),		}},	
	{ KC109_SCROLL,		{ 33,0,2,2,		_T("Scr\nLock"),	}},	
	{ KC109_LSHIFT,		{ 0,9,4,2,		_T("Shift"),	}},		
	{ KC109_RSHIFT,		{ 26,9,4,2,		_T("Shift"),	}},	
	{ KC109_LCONTROL,	{ 0,11,3,2,		_T("CTRL"),		}},	
	{ KC109_RCONTROL,	{ 28,11,2,2,	_T("CTRL"),		}},	
	{ KC109_LMENU,		{ 5,11,2,2,		_T("Alt"),		}},	// L[Alt]
	{ KC109_RMENU,		{ 22,11,2,2,	_T("Alt"),		}},	// R[Alt]
	{ KC109_OEM_1,		{ 22,7,2,2,		_T(":*"),		}},
	{ KC109_OEM_PLUS,	{ 20,7,2,2,		_T(";+"),		}},	
	{ KC109_OEM_COMMA,	{ 18,9,2,2,		_T(",<"),		}},	
	{ KC109_OEM_MINUS,	{ 22,3,2,2,		_T("-="),		}},	
	{ KC109_OEM_PERIOD,	{ 20,9,2,2,		_T(".>"),		}},	
	{ KC109_OEM_2,		{ 22,9,2,2,		_T("/?"),		}},	// [/?]
	{ KC109_OEM_3,		{ 22,5,2,2,		_T("@`"),		}},	// [@`]
	{ KC109_OEM_4,		{ 24,5,2,2,		_T("[{"),		}},	// [[{]
	{ KC109_OEM_5,		{ 26,3,2,2,		_T("\\|"),		}},	// [\|]
	{ KC109_OEM_6,		{ 24,7,2,2,		_T("]}"),		}},	// []}]
	{ KC109_OEM_7,		{ 24,3,2,2,		_T("^~"),		}},	// [^~]
	{ KC109_OEM_102,	{ 24,9,2,2,		_T("\\_"),		}},	// 	[＼_]
};


/*
* MSXキーボードのキー座標、キャプション
*/
static MSX_KEY_LAYOUT g_RawMsxKeyLayout[] =
{
	{ KCMSX_BACK,		{ 28,3,2,2,		_T("BS"),			}},
	{ KCMSX_TAB,		{ 0,5,2,2,		_T("TAB"),			}},
	{ KCMSX_RETURN,		{ 26,5,4,4,		_T("RETURN"),		}},
	{ KCMSX_CAPS,		{ 3,11,2,2,		_T("Caps"),			}},
	{ KCMSX_KANA,		{ 24,11,2,2,	_T("かな"),			}},
	{ KCMSX_ESC,		{ 0,3,2,2,		_T("ESC"),			}},
	{ KCMSX_SPACE,		{ 9,11,13,2,	_T("SPACE"),		}},
	{ KCMSX_STOP,		{ 14,0,3,2,		_T("STOP"),			}},
	{ KCMSX_CLSHOME,	{ 17,0,3,2,		_T("CLS\nHOME"),	}},
	{ KCMSX_LEFT,		{ 32,10,2,2,	_T("←"),			}},
	{ KCMSX_UP,			{ 34,9,2,2,		_T("↑"),			}},
	{ KCMSX_RIGHT,		{ 36,10,2,2,	_T("→"),			}},
	{ KCMSX_DOWN,		{ 34,11,2,2,	_T("↓"),			}},
	{ KCMSX_SELECT,		{ 21,0,3,2,		_T("SELECT"),		}},
	{ KCMSX_INSERT,		{ 24,0,3,2,		_T("INS"),			}},
	{ KCMSX_DELETE,		{ 27,0,3,2,		_T("DEL"),			}},
	{ KCMSX_0,			{ 20,3,2,2,		_T("0"),			}},
	{ KCMSX_1,			{ 2,3,2,2,		_T("1!"),			}},
	{ KCMSX_2,			{ 4,3,2,2,		_T("2\""),			}},
	{ KCMSX_3,			{ 6,3,2,2,		_T("3#"),			}},
	{ KCMSX_4,			{ 8,3,2,2,		_T("4$"),			}},
	{ KCMSX_5,			{ 10,3,2,2,		_T("5%"),			}},
	{ KCMSX_6,			{ 12,3,2,2,		_T("6&"),			}},
	{ KCMSX_7,			{ 14,3,2,2,		_T("7'"),			}},
	{ KCMSX_8,			{ 16,3,2,2,		_T("8("),			}},
	{ KCMSX_9,			{ 18,3,2,2,		_T("9)"),			}},
	{ KCMSX_A,			{ 2,7,2,2,		_T("A"),			}},		
	{ KCMSX_B,			{ 12,9,2,2,		_T("B"),			}},
	{ KCMSX_C,			{ 8,9,2,2,		_T("C"),			}},
	{ KCMSX_D,			{ 6,7,2,2,		_T("D"),			}},
	{ KCMSX_E,			{ 6,5,2,2,		_T("E"),			}},
	{ KCMSX_F,			{ 8,7,2,2,		_T("F"),			}},
	{ KCMSX_G,			{ 10,7,2,2,		_T("G"),			}},
	{ KCMSX_H,			{ 12,7,2,2,		_T("H"),			}},
	{ KCMSX_I,			{ 16,5,2,2,		_T("I"),			}},
	{ KCMSX_J,			{ 14,7,2,2,		_T("J"),			}},
	{ KCMSX_K,			{ 16,7,2,2,		_T("K"),			}},
	{ KCMSX_L,			{ 18,7,2,2,		_T("L"),			}},
	{ KCMSX_M,			{ 16,9,2,2,		_T("M"),			}},
	{ KCMSX_N,			{ 14,9,2,2,		_T("N"),			}},
	{ KCMSX_O,			{ 18,5,2,2,		_T("O"),			}},
	{ KCMSX_P,			{ 20,5,2,2,		_T("P"),			}},
	{ KCMSX_Q,			{ 2,5,2,2,		_T("Q"),			}},
	{ KCMSX_R,			{ 8,5,2,2,		_T("R"),			}},
	{ KCMSX_S,			{ 4,7,2,2,		_T("S"),			}},
	{ KCMSX_T,			{ 10,5,2,2,		_T("T"),			}},
	{ KCMSX_U,			{ 14,5,2,2,		_T("U"),			}},
	{ KCMSX_V,			{ 10,9,2,2,		_T("V"),			}},
	{ KCMSX_W,			{ 4,5,2,2,		_T("W"),			}},
	{ KCMSX_X,			{ 6,9,2,2,		_T("X"),			}},
	{ KCMSX_Y,			{ 12,5,2,2,		_T("Y"),			}},
	{ KCMSX_Z,			{ 4,9,2,2,		_T("Z"),			}},
	{ KCMSX_NUMPAD0,	{ 31,6,2,2,		_T("0"),			}},
	{ KCMSX_NUMPAD1,	{ 31,4,2,2,		_T("1"),			}},
	{ KCMSX_NUMPAD2,	{ 33,4,2,2,		_T("2"),			}},
	{ KCMSX_NUMPAD3,	{ 35,4,2,2,		_T("3"),			}},
	{ KCMSX_NUMPAD4,	{ 31,2,2,2,		_T("4"),			}},
	{ KCMSX_NUMPAD5,	{ 33,2,2,2,		_T("5"),			}},
	{ KCMSX_NUMPAD6,	{ 35,2,2,2,		_T("6"),			}},
	{ KCMSX_NUMPAD7,	{ 31,0,2,2,		_T("7"),			}},
	{ KCMSX_NUMPAD8,	{ 33,0,2,2,		_T("8"),			}},
	{ KCMSX_NUMPAD9,	{ 35,0,2,2,		_T("9"),			}},
	{ KCMSX_MULTIPLY,	{ 37,2,2,2,		_T("*"),			}},
	{ KCMSX_NUMADD,		{ 37,6,2,2,		_T("+"),			}},
	{ KCMSX_NUMSUB,		{ 37,4,2,2,		_T("-"),			}},
	{ KCMSX_NUMDIV,		{ 37,0,2,2,		_T("/"),			}},
	{ KCMSX_NUMPERIOD,	{ 33,6,2,2,		_T("."),			}},
	{ KCMSX_NUMCOMMA,	{ 35,6,2,2,		_T(","),			}},
	{ KCMSX_F6F1,		{ 0,0,2,2,		_T("F6\nF1"),		}},
	{ KCMSX_F7F2,		{ 2,0,2,2,		_T("F7\nF2"),		}},
	{ KCMSX_F8F3,		{ 4,0,2,2,		_T("F8\nF3"),		}},
	{ KCMSX_F9F4,		{ 6,0,2,2,		_T("F9\nF4"),		}},
	{ KCMSX_F10F5,		{ 8,0,2,2,		_T("F10\nF5"),		}},
	{ KCMSX_SHIFT,		{ 0,9,4,2,		_T("SHIFT"),		}},
	{ KCMSX_SHIFT,		{ 26,9,4,2,		_T("SHIFT"),		}},
	{ KCMSX_CONTROL,	{ 0,7,2,2,		_T("CTRL"),			}},
	{ KCMSX_GRAPH,		{ 5,11,2,2,		_T("GRA\nPH"),		}},
	{ KCMSX_MINUS,		{ 22,3,2,2,		_T("-="),			}},
	{ KCMSX_HAT,		{ 24,3,2,2,		_T("^~"),			}},
	{ KCMSX_YEN,		{ 26,3,2,2,		_T("\\|"),			}},
	{ KCMSX_AT,			{ 22,5,2,2,		_T("@`"),			}},
	{ KCMSX_SK,			{ 24,5,2,2,		_T("[{"),			}},
	{ KCMSX_PLUS,		{ 20,7,2,2,		_T(";+"),			}},
	{ KCMSX_COLON,		{ 22,7,2,2,		_T(":*"),			}},
	{ KCMSX_EK,			{ 24,7,2,2,		_T("]}"),			}},
	{ KCMSX_COMMA,		{ 18,9,2,2,		_T(",<"),			}},
	{ KCMSX_PERIOD,		{ 20,9,2,2,		_T(".>"),			}},
	{ KCMSX_SLASH,		{ 22,9,2,2,		_T("/?"),			}},
	{ KCMSX_BACKSLASH,	{ 24,9,2,2,		_T("\\_"),			}},
	{ KCMSX_PSG_UP,		{ 40,0,2,2,		_T("PSG\n↑"),		}},
	{ KCMSX_PSG_DN,		{ 42,0,2,2,		_T("PSG\n↓"),		}},
	{ KCMSX_FM_UP,		{ 40,2,2,2,		_T("FM\n↑"),		}},
	{ KCMSX_FM_DN,		{ 42,2,2,2,		_T("FM\n↓"),		}},
	{ KCMSX_SCC_UP,		{ 40,4,2,2,		_T("SCC\n↑"),		}},
	{ KCMSX_SCC_DN,		{ 42,4,2,2,		_T("SCC\n↓"),		}},
	{ KCMSX_MST_UP,		{ 40,6,2,2,		_T("MST\n↑"),		}},
	{ KCMSX_MST_DN,		{ 42,6,2,2,		_T("MST\n↓"),		}},
	{ KCMSX_CPU,		{ 45,0,2,2,		_T("CPU\nHz"),		}},
	{ KCMSX_VIDEO,		{ 45,2,2,2,		_T("VIDEO"),		}},
	{ KCMSX_OPL3,		{ 45,4,2,2,		_T("OPL3"),			}},
	{ KCMSX_SLOT1,		{ 45,6,2,2,		_T("Slot1\nConf"),	}},
	{ KCMSX_SLOT2,		{ 45,8,2,2,		_T("Slot2\nConf"),	}},
};

CVkey::CVkey()
{
	for(int t = 0; g_VKeyVKeyTable[t].srcVKey != 0x0000; ++t ) {
		m_ConvVkeyVkey.insert(
			std::pair<uint16_t/*vkey*/,const CONV_VKEY_VKEY*>(
				g_VKeyVKeyTable[t].srcVKey, &g_VKeyVKeyTable[t]));
	}

	for(int t = 0; g_RawKc109ScanCodeTable[t].kc109key != KC109_NONE; ++t )
	{
		m_Kc109ScanCode[g_RawKc109ScanCodeTable[t].kc109key] = 
			&g_RawKc109ScanCodeTable[t];
	}

	for(int t = 0; g_VKeyKc109Table[t].winVKey != 0; ++t )
	{
		auto kc = g_VKeyKc109Table[t].ps109Key;
		if (kc != KC109_NONE) {
			m_PatchVkeyKc109.insert(
				std::pair<uint16_t, PATCH_VKEY_KC109>(
					g_VKeyKc109Table[t].winVKey, g_VKeyKc109Table[t]));
		}
	}			

	for (int t = 0; g_Kc109KeyMSXTable[t].ps109Key != KC109_NONE; ++t)
	{
		auto msx = g_Kc109KeyMSXTable[t].msxKey;
		if (msx != KCMSX_NONE){
			m_PatchKc109Msx.insert(
				std::pair<kc109code_t, PATCH_KC109_MSX>(
					g_Kc109KeyMSXTable[t].ps109Key, g_Kc109KeyMSXTable[t]));
		}
		
	}

	for(int t = 0; g_MSXKeyKc109Table[t].msxKey != KCMSX_NONE; ++t )
	{
		auto kc = g_MSXKeyKc109Table[t].ps109Key;
		if (kc != KC109_NONE) {
			m_PatchMsxKc109.insert(
				std::pair<msxcode_t, PATCH_MSX_KC109>(
					g_MSXKeyKc109Table[t].msxKey,g_MSXKeyKc109Table[t]));
		}
	}
	return;
}

CVkey::~CVkey()
{
	// do nothing
	return;
}

/**
 * 一部の仮想キーコードを別の仮想キーコードに置き換える
 */
vkeycode_t CVkey::GetVkeyFromVKey(const vkeycode_t vkeyCd) const
{
	auto it1 = m_ConvVkeyVkey.find(vkeyCd);
	if( it1 == m_ConvVkeyVkey.end() )
		return vkeyCd;
	const vkeycode_t destVKey = (it1->second)->destVKey;
	return destVKey;
}

/**
 * 仮想キーコードから対応する109キーコードを得る
 */
kc109code_t CVkey::GetKC109CodeFromVKey(const vkeycode_t vkeyCd) const
{
	auto it1 = m_PatchVkeyKc109.find(vkeyCd);
	if( it1 == m_PatchVkeyKc109.end() )
		return KC109_NONE;
	const kc109code_t kc109Cd = (it1->second).ps109Key;
	return kc109Cd;
}

/**
 * MSXキーコードから対応する109キーコードを得る
 */
kc109code_t CVkey::GetKC109CodeFromMSX(const msxcode_t msxCd) const
{
	auto it1 = m_PatchMsxKc109.find(msxCd);
	if( it1 == m_PatchMsxKc109.end() )
		return KC109_NONE;
	kc109code_t kc109 = (it1->second).ps109Key;
	return kc109;
}

/**
 * 109キーコードから対応するMSXキーコードを得る
 */
msxcode_t CVkey::GetMsxCodeFromKC109(const kc109code_t kc109Cd) const
{
	auto it = m_PatchKc109Msx.find(kc109Cd);
	if( it == m_PatchKc109Msx.end() )
		return KCMSX_NONE;
	const msxcode_t msxCd = (it->second).msxKey;
	return msxCd;
}

/**
 * 109キーコードからPS/2スキャンコードを得る
 */
const KC109_SCANCODE *CVkey::GetScanCode(const kc109code_t kc109Cd) const
{
	auto it = m_Kc109ScanCode.find(kc109Cd);
	if( it == m_Kc109ScanCode.end() )
		return nullptr;
	const KC109_SCANCODE *pScan = it->second;
	return pScan;
}



// 109キーの座標
int CVkey::GetNumKC109KeyOfLayout() const
{
	return static_cast<int>(sizeof(g_RawKc109KeyLayout) / sizeof(KC109_KEY_LAYOUT));
}

const KC109_KEY_LAYOUT *CVkey::GetXYKC109(const int no) const
{
	static const int NUM = static_cast<int>(sizeof(g_RawKc109KeyLayout) / sizeof(KC109_KEY_LAYOUT));
	if( no < 1 && NUM < no)
		return nullptr;
	return &g_RawKc109KeyLayout[no-1];
}

// MSXキーの座標
int CVkey::GetNumMsxKeyOfLayout() const
{
	return static_cast<int>(sizeof(g_RawMsxKeyLayout) / sizeof(KC109_KEY_LAYOUT));
}

const MSX_KEY_LAYOUT *CVkey::GetXYMSX(const int no) const
{
	static const int NUM = static_cast<int>(sizeof(g_RawMsxKeyLayout) / sizeof(MSX_KEY_LAYOUT));
	if( no < 1 && NUM < no)
		return nullptr;
	return &g_RawMsxKeyLayout[no-1];
}
            
			
kc109code_t CVkey::GetHitKey109(
	const int baseX, const int baseY, const int mouseX, const int mouseY) const
{
	static const int NUM = static_cast<int>(sizeof(g_RawKc109KeyLayout) / sizeof(KC109_KEY_LAYOUT));
	for (int t = 0; t < NUM; ++t)
	{
		auto &dt = g_RawKc109KeyLayout[t];
		const int kx = baseX + dt.lay.bx*BLOCK_W;
		const int ky = baseY + dt.lay.by*BLOCK_H;
		const int kw = dt.lay.bw*BLOCK_W;
		const int kh = dt.lay.bh*BLOCK_H;
		if( kx <= mouseX && mouseX <= kx+kw && ky <= mouseY && mouseY <= ky+kh )
			return dt.kc109key;
	}
	return KC109_NONE;
}

msxcode_t CVkey::GetHitKeyMsx(
	const int baseX, const int baseY, const int mouseX, const int mouseY) const
{
	static const int NUM = static_cast<int>(sizeof(g_RawMsxKeyLayout) / sizeof(MSX_KEY_LAYOUT));
	for (int t = 0; t < NUM; ++t)
	{
		auto &dt = g_RawMsxKeyLayout[t];
		const int kx = baseX + dt.lay.bx*BLOCK_W;
		const int ky = baseY + dt.lay.by*BLOCK_H;
		const int kw = dt.lay.bw*BLOCK_W;
		const int kh = dt.lay.bh*BLOCK_H;
		if( kx <= mouseX && mouseX <= kx+kw && ky <= mouseY && mouseY <= ky+kh )
			return dt.msxKey;
	}
	return KCMSX_NONE;
}
