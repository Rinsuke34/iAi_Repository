/* 2024.12.21 駒沢風助 ファイル作成 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "InputDefine.h"

/* プレイヤー入力管理クラスの宣言 */

// プレイヤー入力管理クラス
class DataList_Input : public DataListBase
{
	public:
		DataList_Input();				// コンストラクタ
		virtual ~DataList_Input();		// デストラクタ

		void	JsonDataLoad();			// Jsonからデータをロード

		/* インターフェイス用入力取得 */
		bool	bGetInterfaceInput(int iInputType, int iGetInputUI);		// インターフェイス入力取得

		/* ゲームプレイ用入力取得 */
		bool	bGetGameInputAction(int iInputType, int iGetInputGame);		// ゲームプレイ用入力取得(アクション)
		VECTOR	vecGetGameInputMove();										// ゲームプレイ用入力取得(移動量)
		VECTOR	vecGetGameInputAim();										// ゲームプレイ用入力取得(照準)

	private:
		/* キーコンフィグ情報 */
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigJoypad;			// ジョイパッド
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigKeyboardMouse;	// キーボード＆マウス

		/* キーコンフィグ用関数 */
		std::string	GetControlName(int iGameControl);		// ゲーム操作の種類から入力の名称を取得

		/* 関数 */
		void	ConfigReset();																																// キーコンフィグをリセット
		void	ConfigDelete();																																// キーコンフィグを削除
		bool	bGetInputCode(const std::vector<Struct_Json_Input::CONFIG_INFO*>& stConfig, int& iInputCode, int& iIquipmentType, int iTargetInputGame);	// キーコンフィグから入力コード取得

		/* 以下、使うかもしれないのでバックアップとして取っておく */
		///* 入力コード一覧 */
		//Struct_Json_Input::INPUT_INFO stInputInfo[73] =
		//{
		//	/*	入力コード,			入力機器の種類,				入力の名称	*/
		//	/* ジョイパッド */
		//	{	PAD_INPUT_UP,		INPUT_EQUIPMENT_JOYPAD,		"上"			},	// 上ボタン
		//	{	PAD_INPUT_LEFT,		INPUT_EQUIPMENT_JOYPAD,		"左"			},	// 左ボタン
		//	{	PAD_INPUT_RIGHT,	INPUT_EQUIPMENT_JOYPAD,		"右"			},	// 右ボタン
		//	{	PAD_INPUT_DOWN,		INPUT_EQUIPMENT_JOYPAD,		"上"			},	// 下ボタン
		//	{	PAD_INPUT_A,		INPUT_EQUIPMENT_JOYPAD,		"A"				},	// Aボタン
		//	{	PAD_INPUT_B,		INPUT_EQUIPMENT_JOYPAD,		"B"				},	// Bボタン
		//	{	PAD_INPUT_C,		INPUT_EQUIPMENT_JOYPAD,		"C"				},	// Cボタン
		//	{	PAD_INPUT_X,		INPUT_EQUIPMENT_JOYPAD,		"X"				},	// Xボタン
		//	{	PAD_INPUT_Y,		INPUT_EQUIPMENT_JOYPAD,		"Y"				},	// Yボタン
		//	{	PAD_INPUT_Z,		INPUT_EQUIPMENT_JOYPAD,		"Z"				},	// Zボタン
		//	{	PAD_INPUT_L,		INPUT_EQUIPMENT_JOYPAD,		"L"				},	// Lボタン
		//	{	PAD_INPUT_R,		INPUT_EQUIPMENT_JOYPAD,		"R"				},	// Rボタン
		//	{	PAD_INPUT_START,	INPUT_EQUIPMENT_JOYPAD,		"START"			},	// スタートボタン
		//	{	PAD_INPUT_M,		INPUT_EQUIPMENT_JOYPAD,		"M"				},	// Mボタン
		//	/* キーボード */
		//	{	KEY_INPUT_BACK,		INPUT_EQUIPMENT_KEYBOARD,	"BACK"			},	// バックスペースキー
		//	{	KEY_INPUT_TAB,		INPUT_EQUIPMENT_KEYBOARD,	"TAB"			},	// タブキー
		//	{	KEY_INPUT_RETURN,	INPUT_EQUIPMENT_KEYBOARD,	"ENTER"			},	// エンターキー
		//	{	KEY_INPUT_LSHIFT,	INPUT_EQUIPMENT_KEYBOARD,	"L SHIFT"		},	// 左シフトキー
		//	{	KEY_INPUT_RSHIFT,	INPUT_EQUIPMENT_KEYBOARD,	"R SHIFT"		},	// 右シフトキー
		//	{	KEY_INPUT_LCONTROL,	INPUT_EQUIPMENT_KEYBOARD,	"L CONTROL"		},	// 左コントロールキー
		//	{	KEY_INPUT_RCONTROL,	INPUT_EQUIPMENT_KEYBOARD,	"R CONTROL"		},	// 右コントロールキー
		//	{	KEY_INPUT_ESCAPE,	INPUT_EQUIPMENT_KEYBOARD,	"ESCAPE"		},	// エスケープキー
		//	{	KEY_INPUT_SPACE,	INPUT_EQUIPMENT_KEYBOARD,	"SPACE"			},	// スペースキー
		//	{	KEY_INPUT_PGUP,		INPUT_EQUIPMENT_KEYBOARD,	"PAGE UP"		},	// ＰａｇｅＵＰキー
		//	{	KEY_INPUT_PGDN,		INPUT_EQUIPMENT_KEYBOARD,	"PAGE DOWN"		},	// ＰａｇｅＤｏｗｎキー
		//	{	KEY_INPUT_END,		INPUT_EQUIPMENT_KEYBOARD,	"END"			},	// エンドキー
		//	{	KEY_INPUT_HOME,		INPUT_EQUIPMENT_KEYBOARD,	"HOME"			},	// ホームキー
		//	{	KEY_INPUT_LEFT,		INPUT_EQUIPMENT_KEYBOARD,	"LEFT"			},	// 左キー
		//	{	KEY_INPUT_UP,		INPUT_EQUIPMENT_KEYBOARD,	"UP"			},	// 上キー
		//	{	KEY_INPUT_RIGHT,	INPUT_EQUIPMENT_KEYBOARD,	"RIGHT"			},	// 右キー
		//	{	KEY_INPUT_DOWN,		INPUT_EQUIPMENT_KEYBOARD,	"DOWN"			},	// 下キー
		//	{	KEY_INPUT_INSERT,	INPUT_EQUIPMENT_KEYBOARD,	"INSERT"		},	// インサートキー
		//	{	KEY_INPUT_DELETE,	INPUT_EQUIPMENT_KEYBOARD,	"DELETE"		},	// デリートキー
		//	{	KEY_INPUT_A,		INPUT_EQUIPMENT_KEYBOARD,	"A"				},	// Ａキー
		//	{	KEY_INPUT_B,		INPUT_EQUIPMENT_KEYBOARD,	"B"				},	// Ｂキー
		//	{	KEY_INPUT_C,		INPUT_EQUIPMENT_KEYBOARD,	"C"				},	// Ｃキー
		//	{	KEY_INPUT_D,		INPUT_EQUIPMENT_KEYBOARD,	"D"				},	// Ｄキー
		//	{	KEY_INPUT_E,		INPUT_EQUIPMENT_KEYBOARD,	"E"				},	// Ｅキー
		//	{	KEY_INPUT_F,		INPUT_EQUIPMENT_KEYBOARD,	"F"				},	// Ｆキー
		//	{	KEY_INPUT_G,		INPUT_EQUIPMENT_KEYBOARD,	"G"				},	// Ｇキー
		//	{	KEY_INPUT_H,		INPUT_EQUIPMENT_KEYBOARD,	"H"				},	// Ｈキー
		//	{	KEY_INPUT_I,		INPUT_EQUIPMENT_KEYBOARD,	"I"				},	// Ｉキー
		//	{	KEY_INPUT_J,		INPUT_EQUIPMENT_KEYBOARD,	"J"				},	// Ｊキー
		//	{	KEY_INPUT_K,		INPUT_EQUIPMENT_KEYBOARD,	"K"				},	// Ｋキー
		//	{	KEY_INPUT_L,		INPUT_EQUIPMENT_KEYBOARD,	"L"				},	// Ｌキー
		//	{	KEY_INPUT_M,		INPUT_EQUIPMENT_KEYBOARD,	"M"				},	// Ｍキー
		//	{	KEY_INPUT_N,		INPUT_EQUIPMENT_KEYBOARD,	"N"				},	// Ｎキー
		//	{	KEY_INPUT_O,		INPUT_EQUIPMENT_KEYBOARD,	"O"				},	// Ｏキー
		//	{	KEY_INPUT_P,		INPUT_EQUIPMENT_KEYBOARD,	"P"				},	// Ｐキー
		//	{	KEY_INPUT_Q,		INPUT_EQUIPMENT_KEYBOARD,	"Q"				},	// Ｑキー
		//	{	KEY_INPUT_R,		INPUT_EQUIPMENT_KEYBOARD,	"R"				},	// Ｒキー
		//	{	KEY_INPUT_S,		INPUT_EQUIPMENT_KEYBOARD,	"S"				},	// Ｓキー
		//	{	KEY_INPUT_T,		INPUT_EQUIPMENT_KEYBOARD,	"T"				},	// Ｔキー
		//	{	KEY_INPUT_U,		INPUT_EQUIPMENT_KEYBOARD,	"U"				},	// Ｕキー
		//	{	KEY_INPUT_V,		INPUT_EQUIPMENT_KEYBOARD,	"V"				},	// Ｖキー
		//	{	KEY_INPUT_W,		INPUT_EQUIPMENT_KEYBOARD,	"W"				},	// Ｗキー
		//	{	KEY_INPUT_X,		INPUT_EQUIPMENT_KEYBOARD,	"X"				},	// Ｘキー
		//	{	KEY_INPUT_Y,		INPUT_EQUIPMENT_KEYBOARD,	"Y"				},	// Ｙキー
		//	{	KEY_INPUT_Z,		INPUT_EQUIPMENT_KEYBOARD,	"Z"				},	// Ｚキー
		//	{	KEY_INPUT_0, 		INPUT_EQUIPMENT_KEYBOARD,	"0"				},	// ０キー
		//	{	KEY_INPUT_1,		INPUT_EQUIPMENT_KEYBOARD,	"1"				},	// １キー
		//	{	KEY_INPUT_2,		INPUT_EQUIPMENT_KEYBOARD,	"2"				},	// ２キー
		//	{	KEY_INPUT_3,		INPUT_EQUIPMENT_KEYBOARD,	"3"				},	// ３キー
		//	{	KEY_INPUT_4,		INPUT_EQUIPMENT_KEYBOARD,	"4"				},	// ４キー
		//	{	KEY_INPUT_5,		INPUT_EQUIPMENT_KEYBOARD,	"5"				},	// ５キー
		//	{	KEY_INPUT_6,		INPUT_EQUIPMENT_KEYBOARD,	"6"				},	// ６キー
		//	{	KEY_INPUT_7,		INPUT_EQUIPMENT_KEYBOARD,	"7"				},	// ７キー
		//	{	KEY_INPUT_8,		INPUT_EQUIPMENT_KEYBOARD,	"8"				},	// ８キー
		//	{	KEY_INPUT_9,		INPUT_EQUIPMENT_KEYBOARD,	"9"				},	// ９キー
		//	/* マウス */
		//	{	MOUSE_INPUT_LEFT,	INPUT_EQUIPMENT_MOUSE,		"左クリック"	},	// 左クリック
		//	{	MOUSE_INPUT_RIGHT,	INPUT_EQUIPMENT_MOUSE,		"右クリック"	},	// 右クリック
		//	{	MOUSE_INPUT_MIDDLE,	INPUT_EQUIPMENT_MOUSE,		"中央ボタン"	},	// 中央ボタン
		//	{	-1,					NULL,						NULL			}
		//};

		

		
	protected:
};