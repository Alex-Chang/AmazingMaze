
// standard virtual keys
enum Keys
{
	LeftButton			=	1,
	RightButton			=	2,
	Cancel				=	3,
	MiddleButton		=	4,		// not contiguous with left & right button


#if(_WIN32_WINNT >= 0x0500)
	XBUTTON1			=	5,		// not contiguous with left & right button
	XBUTTON2			=	6,		// not contiguous with left & right button
#endif

									// 0x07 : unassigned
	VK_BACK				=	8,
	Tab					=	9,

									// 10 - 11 : reserved

	Clear				=	12,
	Return				=	13,

	Shift				=	16,
	Control				=	17,
	Menu				=	18,
	Pause				=	19,
	Capital				=	20,

	Kana				=	21,
	Hangeul				=	21,		// old name - should be here for compatibility
	Hangul				=	21,

	Junja				=	23,
	Final				=	24,
	Hanja				=	25,
	Kanji				=	25,

	Escape				=	27,

	Convert				=	28,
	NonConvert			=	29,
	Accept				=	30,
	ModeChange			=	31,

	Space				=	32,
	Prior				=	33,
	Next				=	34,
	End					=	35,
	Home				=	36,
	Left				=	37,
	Up					=	38,
	Right				=	39,
	Down				=	40,
	Select				=	41,
	Print				=	42,
	Execute				=	43,
	SnapShot			=	44,
	Insert				=	45,
	Delete				=	46,
	Help				=	47,

	Number0				=	48,
	Number1				=	49,
	Number2				=	50,
	Number3				=	51,
	Number4				=	52,
	Number5				=	53,
	Number6				=	54,
	Number7				=	55,
	Number8				=	56,
	Number9				=	57,

										// 64 - unassigned

	A					=	65,
	B					=	66,
	C					=	67,
	D					=	68,
	E					=	69,
	F					=	70,
	G					=	71,
	H					=	72,
	I					=	73,
	J					=	74,
	K					=	75,
	L					=	76,
	M					=	77,
	N					=	78,
	O					=	79,
	P					=	80,
	Q					=	81,
	R					=	82,
	S					=	83,
	T					=	84,
	U					=	85,
	V					=	86,
	W					=	87,
	X					=	88,
	Y					=	89,
	Z					=	90,

	LeftWin				=	91,
	RightWin			=	92,
	Apps				=	93,

										// 94 : reserved

	Sleep				=	95,

	NumPad0				=	96,
	NumPad1				=	97,
	NumPad2				=	98,
	NumPad3				=	99,
	NumPad4				=	100,
	NumPad5				=	101,
	NumPad6				=	102,
	NumPad7				=	103,
	NumPad8				=	104,
	NumPad9				=	105,
	Multiply			=	106,
	Add					=	107,
	Separator			=	108,
	Subtract			=	109,
	Decimal				=	110,
	Divide				=	111,
	F1					=	112,
	F2					=	113,
	F3					=	114,
	F4					=	115,
	F5					=	116,
	F6					=	117,
	F7					=	118,
	F8					=	119,
	F9					=	120,
	F10					=	121,
	F11					=	122,
	F12					=	123,
	F13					=	124,
	F14					=	125,
	F15					=	126,
	F16					=	127,
	F17					=	128,
	F18					=	129,
	F19					=	130,
	F20					=	131,
	F21					=	132,
	F22					=	133,
	F23					=	134,
	F24					=	135,

										// 136 - 143 unassigned

	NumLock				=	144,
	Scroll				=	145,

	// NEC PC-9800 keyboard definitions
	OemNecEqual			=	146,		// '=' key on numpad

/*
 * Fujitsu/OASYS kbd definitions
 */
	OEM_FJ_JISHO		=	146,		// 'Dictionary' key
	OEM_FJ_MASSHOU		=	147,		// 'Unregister word' key
	OEM_FJ_TOUROKU		=	148,		// 'Register word' key
	OEM_FJ_LOYA			=	149,		// 'Left OYAYUBI' key
	OEM_FJ_ROYA			=	150,		// 'Right OYAYUBI' key

										// 151 - 159 unassigned

	/*
	* VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
	* Used only as parameters to GetAsyncKeyState() and GetKeyState(). 
	* No other API or message will distinguish left and right keys in this way.
	*/
	LeftShift			=	160,
	RightShift			=	161,
	LeftControl			=	162,
	RightControl		=	163,
	LeftMenu			=	164,
	RightMenu			=	165,


#if(_WIN32_WINNT >= 0x0500)
	BrowserBack			=	166,
	BrowserForward		=	167,
	BrowserRefresh		=	168,
	BrowserStop			=	169,
	BrowserSearch		=	170,
	BrowserFavorites	=	171,
	BrowserHome			=	172,

	VolumeMute			=	173,
	VolumeDown			=	174,
	VolumeUp			=	175,
	MediaNextTrack		=	176,
	MediaPrevTrack		=	177,
	MediaStop			=	178,
	MediaPlayPause		=	179,
	LaunchMail			=	180,
	LaunchMediaSelect	=	181,
	LaunchApp1			=	182,
	LaunchApp2			=	183,

#endif /* _WIN32_WINNT >= 0x0500 */

										// 184 - 185 reserved

	OEM_1				=	186,		// ';:' for US
	OEM_Plus			=	187,		// '+' any country
	OEM_Comma			=	188,		// ',' any country
	OEM_Minus			=	189,		// '-' any country
	OEM_Period			=	190,		// '.' any country
	OEM_2				=	191,		// '/?' for US
	OEM_3				=	192,		// '`~' for US

										// 193 - 215 : reserved


										// 216 - 218 unassigned

	OEM_4				=	219,		// '[{' for US
	OEM_5				=	220,		// '\|' for US
	OEM_6				=	221,		// '\|' for US
	OEM_7				=	222,		// ']}' for US
	OEM_8				=	223,		// ''"' for US

										// 0xE0 : reserved

/*
 * Various extended or enhanced keyboards
 */
	OEM_AX				=	225,		// 'AX' key on Japanese AX kbd
	OEM_102				=	226,		// "<>" or "\|" on RT 102-key kbd.
	ICO_HELP			=	227,		// Help key on ICO
	ICO_00				=	228,		// 00 key on ICO

#if(WINVER >= 0x0400)
	ProcessKey			=	229,
#endif /* WINVER >= 0x0400 */

	ICO_CLEAR			=	230,


#if(_WIN32_WINNT >= 0x0500)
	Packet				=	231,
#endif /* _WIN32_WINNT >= 0x0500 */

										// 232 unassigned
/*
 * Nokia/Ericsson definitions
 */
	OEM_RESET			=	233,
	OEM_JUMP			=	234,
	OEM_PA1				=	235,
	OEM_PA2				=	236,
	OEM_PA3				=	237,
	OEM_WSCTRL			=	238,
	OEM_CUSEL			=	239,
	OEM_ATTN			=	240,
	OEM_FINISH			=	241,
	OEM_COPY			=	242,
	OEM_AUTO			=	243,
	OEM_ENLW			=	244,
	OEM_BACKTAB			=	245,

	ATTN				=	246,
	CRSEL				=	247,
	EXSEL				=	248,
	EREOF				=	249,
	PLAY				=	250,
	ZOOM				=	251,
	NONAME				=	252,
	PA1					=	253,
	OEM_CLEAR			=	254

										// 255 reserved
};