/* 2024.12.21 駒沢風助 ファイル作成 */

#include "DataList_Input.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* プレイヤー入力管理クラスの定義 */

// コンストラクタ
DataList_Input::DataList_Input() : DataListBase("DataList_Input")
{
	/* 名前空間の省略 */
	using namespace Struct_Json_Input;	// 入力管理用の定数、構造体

	/* 初期化 */
	/* 各キーコンフィグにデフォルトの設定を代入 */
	ConfigReset();

	/* Jsonファイルをロード */
	JsonDataLoad();
}

// デストラクタ
DataList_Input::~DataList_Input()
{
	/* すべてのキーコンフィグ情報を削除する */
	ConfigDelete();
}

// キーコンフィグを削除
void DataList_Input::ConfigDelete()
{
	/* すべてのキーコンフィグ情報を削除する */
	/* ジョイパッド */
	for (auto& Data : this->stConfigJoypad)
	{
		delete Data;	// メモリを開放する
	}
	this->stConfigJoypad.clear();

	/* キーボード＆マウス */
	for (auto& Data : this->stConfigKeyboardMouse)
	{
		delete Data;	// メモリを開放する
	}
	this->stConfigKeyboardMouse.clear();	// リストをクリア
}

// Jsonからデータをロード
void DataList_Input::JsonDataLoad()
{
	/* 名前空間の省略 */
	using namespace Struct_Json_Input;	// 入力管理用の定数、構造体

	/* Jsonファイルの読み込み */
	// キーコンフィグの設定されたJsonファイルを開く(無いならデフォルト設定で作成する)

	/* パスとファイル名の設定 */
	std::string FilePath		= "resource/SetupData/";	// 保存場所
	std::string jsonFileName	= "InputData.json";			// ファイル名

	/* ファイル展開 */
	std::ifstream inputFile(FilePath + jsonFileName);

	/* ファイルの展開が成功したか確認 */
	if (inputFile.is_open())
	{
		// ファイルが存在する場合
		/* キーコンフィグのデータを読み込む */
		nlohmann::json	json;
		inputFile >> json;

		/* キーコンフィグ取得 */
		// ※コントローラーとキーボード＆マウスのキーコンフィグがあるので2回取得する
		std::string ObjeName[2] = { "Joypad", "Keyboard_Mouse" };

		for (int i = 0; i < 2; i++)
		{
			/* ファイルの読み込み */
			nlohmann::json GetConfig = json.at(ObjeName[i]);

			/* キーコンフィグを読み込んだデータで更新する */
			// ※インデックス(i)「0：ジョイパッド、1：キーボード＆マウス」
			std::vector<Struct_Json_Input::CONFIG_INFO*>& configList =
				(i == 0) ? this->stConfigJoypad : this->stConfigKeyboardMouse;

			for (auto& config : configList)
			{
				/* Jsonでのゲーム操作の種類の名称取得 */
				std::string SearchName = GetControlName(config->iGameControl);

				/* 戻り値確認 */
				if (SearchName == "Error")
				{
					/* 戻り値が"Error"の場合はファイル破損の可能性があるので終了フラグを有効にする(仮) */
					gbEndFlg = true;
					return;
				}

				/* その名称に設定されている入力コードを取得しデータ更新 */
				// ※キーコンフィグの保存形式は下記のようになっている
				// ゲーム操作の種類 : [ 入力機器種類, 入力コード ]
				GetConfig.at(SearchName).at(0).get_to(config->iEquipmentType);
				GetConfig.at(SearchName).at(1).get_to(config->iInput);
			}
		}
	}
	else
	{
		/* 各キーコンフィグにデフォルトの設定を代入 */
		ConfigReset();
	}

	/* ファイルを閉じる */
	inputFile.close();
}

// インターフェイス入力取得
bool DataList_Input::bGetInterfaceInput(int iInputType, int iGetInputUI)
{
	// 引数
	// iInputType	: 確認したい入力タイプ
	// iGetInputUI	: 確認したい入力内容(UI操作系)
	// 戻り値
	// bool			: 確認対象の入力が行われているか(true:行われている、false:行われていない)

	/* ジョイパッド入力定義テーブル */
	int iPadInput[]			= { XINPUT_BUTTON_DPAD_UP, XINPUT_BUTTON_DPAD_DOWN, XINPUT_BUTTON_DPAD_LEFT, XINPUT_BUTTON_DPAD_RIGHT, XINPUT_BUTTON_A, XINPUT_BUTTON_B };

	/* キーボード入力定義テーブル */
	int iKeyboardInput[]	= { KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_Z, KEY_INPUT_X };

	/* 対象の入力が行われているか確認 */
	{
		/* ジョイパッド */
		if (gstJoypadInputData.cgInput[iInputType][iPadInput[iGetInputUI]] == TRUE)
		{
			// 入力されている場合
			return true;
		}
		
		/* キーボード＆マウス */
		if (gstKeyboardInputData.cgInput[iInputType][iKeyboardInput[iGetInputUI]] == TRUE)
		{
			// 入力されている場合
			return true;
		}
	}

	/* 入力されていないと判定 */
	return false;
}

// ゲームプレイ用入力取得(ジャンプ等のアクション)
bool DataList_Input::bGetGameInputAction(int iInputType, int iGetInputGame)
{
	// 引数
	// iInputType		: 確認したい入力タイプ
	// iGetInputGame	: 確認したい入力内容(操作の種類)
	// 戻り値
	// bool				: 確認対象の入力が行われているか(true:行われている、false:行われていない)

	/* 名前空間の省略 */
	using namespace Struct_Json_Input;	// 入力管理用の定数、構造体

	/* 対象操作の種類に登録されている入力コードを取得する */

	/* 必要情報の定義 */

	// どちらであるか判定用
	static const int JOYPAD			= 0;	// ジョイパッド
	static const int KEYBOARD_MOUSE	= 1;	// キーボード＆マウス

	// 取得した入力コードと入力機器の種類を格納する構造体
	struct INPUT_CHECK
	{
		int iInput;			// 入力コード
		int iEquipmentType;	// 入力機器の種類
		bool bSkipFlg;		// スキップフラグ
	};

	INPUT_CHECK stInputCheck[2];	// ジョイパッド、キーボード＆マウスの入力コードを格納する構造体

	/* ジョイパッドの確認 */
	/* 確認したい入力内容の入力コードと入力機器の種類を取得 */
	if (bGetInputCode(this->stConfigJoypad, stInputCheck[JOYPAD].iInput, stInputCheck[JOYPAD].iEquipmentType, iGetInputGame) == false)
	{
		// 取得できなかった場合
		stInputCheck[JOYPAD].bSkipFlg = true;
	}

	/* キーボード＆マウスの確認 */
	if (bGetInputCode(this->stConfigKeyboardMouse, stInputCheck[KEYBOARD_MOUSE].iInput, stInputCheck[KEYBOARD_MOUSE].iEquipmentType, iGetInputGame) == false)
	{
		// 取得できなかった場合
		stInputCheck[KEYBOARD_MOUSE].bSkipFlg = true;
	}

	/* 対象の入力が行われているか確認 */
	/* ジョイパッド */
	if (stInputCheck[JOYPAD].bSkipFlg != true)
	{
		switch (stInputCheck[JOYPAD].iEquipmentType)
		{
			/* ジョイパッド(ボタン) */
			case INPUT_EQUIPMENT_JOYPAD:
				if (gstJoypadInputData.cgInput[iInputType][stInputCheck[JOYPAD].iInput] == TRUE)
				{
					// 入力されている場合
					return true;
				}
				break;

			/* ジョイパッド(トリガー) */
			case INPUT_EQUIPMENT_JOYPAD_TRIGGER:
				switch (stInputCheck[JOYPAD].iInput)
				{
					/* 左トリガーの場合 */
					case XINPUT_TRIGGER_LEFT:
						if(gstJoypadInputData.bgTrigger[iInputType][INPUT_LEFT] == true)
						{
							// 入力されている場合
							return true;
						}
						break;

					/* 右トリガーの場合 */
					case XINPUT_TRIGGER_RIGHT:
						if (gstJoypadInputData.bgTrigger[iInputType][INPUT_RIGHT] == true)
						{
							// 入力されている場合
							return true;
						}
						break;
				}
			break;
		}
	}

	/* キーボード＆マウス */
	if (stInputCheck[KEYBOARD_MOUSE].bSkipFlg != true)
	{
		switch (stInputCheck[KEYBOARD_MOUSE].iEquipmentType)
		{
			/* キーボード */
			case INPUT_EQUIPMENT_KEYBOARD:
				if (gstKeyboardInputData.cgInput[iInputType][stInputCheck[KEYBOARD_MOUSE].iInput])
				{
					// 入力されている場合
					return true;
				}
				break;

			/* マウス */
			case INPUT_EQUIPMENT_MOUSE:
				if (gstKeyboardInputData.igInput[iInputType] & stInputCheck[KEYBOARD_MOUSE].iInput)
				{
					// 入力されている場合
					return true;
				}
				break;
		}
	}
	
	/* 入力されていないと判定 */
	return false;
}

// ゲームプレイ用入力取得(移動量)
float DataList_Input::fGetGameInputMove()
{
	// 戻り値
	// float	: 移動入力の強さ(0.f～1.f)

	float	fReturn = 0;

	/* キーボードで移動入力がされているか確認 */
	if (bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) ||
		bGetGameInputAction(INPUT_HOLD, GAME_BACK)	||
		bGetGameInputAction(INPUT_HOLD, GAME_RIGHT)	||
		bGetGameInputAction(INPUT_HOLD, GAME_LEFT)	)
	{
		// 入力されている場合
		/* 入力の強さを1(最大)で返す */
		fReturn = 1.f;
		return fReturn;
	}

	/* コントローラーで移動入力がされているか確認 */
	// ※±32767の範囲で出力されるので±1.0fに変換する
	VECTOR vecReturn = VGet(0.0f, 0.0f, 0.0f);
	vecReturn.x += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_LEFT]);
	vecReturn.z += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_LEFT]);

	/* 移動方向がある場合 */
	if (vecReturn.x != -0 || vecReturn.z != -0)
	{
		/* 各方向の値を±1以内に収める(キーボードとコントローラの同時入力対策) */
		vecReturn.x = PUBLIC_PROCESS::fClamp(vecReturn.x, 1.0f, -1.0f);
		vecReturn.z = PUBLIC_PROCESS::fClamp(vecReturn.z, 1.0f, -1.0f);
		
		/* 入力の大きさを取得 */
		fReturn = VSize(vecReturn);

		/* 2025.01.21 菊池雅道 処理追加 開始 */
		/* デッドゾーン */
		if (PUBLIC_PROCESS::bCheckInputDeadzone(fReturn, STICK_DEAD_ZONE))
		{
			// デッドゾーン範囲内であるならば
			/* 入力を無効化 */
			fReturn = 0;
		}
		/* 2025.01.21 菊池雅道 処理追加 終了 */
	}

	/* 移動方向を返す */
	return fReturn;
}

// ゲームプレイ用入力取得(移動方向)
VECTOR DataList_Input::vecGetGameInputMoveDirection()
{
	// 戻り値
	// VECTOR	: 移動方向(詳細は下記参照)

	// ■戻り値の方向については下記の通りとする。
	//	・奥	: +Z
	//	・前	: -Z
	//	・右	: +X
	//	・左	: -X
	//	※Yは必ず0.0fとなる
	// ■X,Y,Zの値は-1.0f～1.0fの範囲とする。
	// ■コントローラー使用時はアナログ値から算出するため、1.fに届かない場合がある。
	// ■キーボードの場合は上下左右キーで算出するため出力は8方向のみ。
	// ■コントローラーとキーボードの同時入力があった場合は双方を足し合わせた値を返す。
	// ■コントローラーは左スティックの入力を使用する。

	VECTOR vecReturn = VGet(0.0f, 0.0f, 0.0f);

	/* コントローラーから移動方向を取得 */
	// ※±32767の範囲で出力されるので±1.0fに変換する
	vecReturn.x += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickX[INPUT_LEFT]);
	vecReturn.z += PUBLIC_PROCESS::fAnalogStickNorm(gstJoypadInputData.sAnalogStickY[INPUT_LEFT]);

	/* 2025.01.21 菊池雅道 処理追加 開始 */
	/* デッドゾーン */
	// X方向の入力
	if (PUBLIC_PROCESS::bCheckInputDeadzone(vecReturn.x, STICK_DEAD_ZONE))
	{
		// デッドゾーン範囲内であるならば
		/* 入力を無効化 */
		vecReturn.x = 0.f;
	}
	// Z方向の入力
	if (PUBLIC_PROCESS::bCheckInputDeadzone(vecReturn.z, STICK_DEAD_ZONE))
	{
		// デッドゾーン範囲内であるならば
		/* 入力を無効化 */
		vecReturn.z = 0.f;
	}
	/* 2025.01.21 菊池雅道 処理追加 終了 */

	/* キーボードから移動方向を取得 */
	/* 前進 */
	if (bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) == true)
	{
		vecReturn.z += 1.0f;
	}

	/* 後退 */
	if (bGetGameInputAction(INPUT_HOLD, GAME_BACK) == true)
	{
		vecReturn.z -= 1.0f;
	}

	/* 右移動 */
	if (bGetGameInputAction(INPUT_HOLD, GAME_RIGHT) == true)
	{
		vecReturn.x += 1.0f;
	}

	/* 左移動 */
	if (bGetGameInputAction(INPUT_HOLD, GAME_LEFT) == true)
	{
		vecReturn.x -= 1.0f;
	}

	/* 移動方向がある場合 */
	if (vecReturn.x != -0 || vecReturn.z != -0)
	{
		/* 移動方向を正規化 */
		vecReturn = VNorm(vecReturn);
	}

	/* 移動方向を返す */
	return vecReturn;
}

// ゲーム操作の種類から入力の名称を取得
std::string DataList_Input::GetControlName(int iGameControl)
{
	// 引数
	// iGameControl	: ゲーム操作の種類(InputDefineの「入力内容-ゲーム操作」参照)
	// 戻り値
	// std::string	: その操作の名称(見つからない場合は"Error"を返す)

	/* 名前空間の省略 */
	using namespace Struct_Json_Input;	// 入力管理用の定数、構造体

	/* 操作とJsonファイルでの名称の対応表 */
	Struct_Json_Input::CONFIG_JSON stConfig_Json_Operation[] =
	{
		/* 共通 */
		{	GAME_JUMP,		"Jump",		false	},
		{	GAME_ATTACK,	"Attack",	false	},
		{	GAME_AIM,		"Aim",		false	},
		{	GAME_RESET,		"Reset",	false	},
		{	GAME_DODGE,		"Dodge",	false	},
		/* キーボード＆マウスのみ */
		{	GAME_FORWARD,	"Forward",	true	},
		{	GAME_BACK,		"Back",		true	},
		{	GAME_LEFT,		"Left",		true	},
		{	GAME_RIGHT,		"Right",	true	},
		{	-1,									}
	};

	/* 入力の名称を取得 */
	for (int i = 0; stConfig_Json_Operation->iGameControl != -1; i++)
	{
		/* 指定のゲーム操作が見つかったら */
		if (stConfig_Json_Operation[i].iGameControl == iGameControl)
		{
			// 名前を返す
			return stConfig_Json_Operation[i].pcControlName;
		}
	}

	/* 見つからなかった場合 */
	return "Error";
}

// キーコンフィグをリセット
void DataList_Input::ConfigReset()
{
	/* すべてのキーコンフィグをデフォルト設定に戻す */

	/* 名前空間の省略 */
	using namespace Struct_Json_Input;	// 入力管理用の定数、構造体

	/* キーコンフィグデフォルト(ジョイパッド) */
	Struct_Json_Input::CONFIG_INFO stConfig_Default_Joypad[] =
	{
		{	GAME_JUMP,		XINPUT_BUTTON_A,				INPUT_EQUIPMENT_JOYPAD			},	// ジャンプ
		{	GAME_ATTACK,	XINPUT_BUTTON_RIGHT_SHOULDER,	INPUT_EQUIPMENT_JOYPAD			},	// 攻撃
		{	GAME_AIM,		XINPUT_TRIGGER_LEFT,			INPUT_EQUIPMENT_JOYPAD_TRIGGER	},	// エイム(構え)
		{	GAME_RESET,		XINPUT_BUTTON_LEFT_SHOULDER,	INPUT_EQUIPMENT_JOYPAD			},	// カメラリセット
		{	GAME_DODGE,		XINPUT_BUTTON_B,				INPUT_EQUIPMENT_JOYPAD			},	// 回避
		{	-1,																				}
	};

	/* キーコンフィグデフォルト(キーボード＆マウス) */
	Struct_Json_Input::CONFIG_INFO stConfig_Default_Keyboard_Mouse[] =
	{
		{	GAME_FORWARD,	KEY_INPUT_W,			INPUT_EQUIPMENT_KEYBOARD	},	// 前進
		{	GAME_BACK,		KEY_INPUT_S,			INPUT_EQUIPMENT_KEYBOARD	},	// 後退
		{	GAME_LEFT,		KEY_INPUT_A,			INPUT_EQUIPMENT_KEYBOARD	},	// 左移動
		{	GAME_RIGHT,		KEY_INPUT_D,			INPUT_EQUIPMENT_KEYBOARD	},	// 右移動
		{	GAME_JUMP,		KEY_INPUT_SPACE,		INPUT_EQUIPMENT_KEYBOARD	},	// ジャンプ
		{	GAME_ATTACK,	MOUSE_INPUT_LEFT,		INPUT_EQUIPMENT_MOUSE		},	// 攻撃
		{	GAME_AIM,		MOUSE_INPUT_RIGHT,		INPUT_EQUIPMENT_MOUSE		},	// エイム(構え)
		{	GAME_RESET,		MOUSE_INPUT_MIDDLE,		INPUT_EQUIPMENT_MOUSE		},	// カメラリセット
		{	GAME_DODGE,		KEY_INPUT_LCONTROL,		INPUT_EQUIPMENT_KEYBOARD	},	// 回避
		{	-1,																	}
	};

	/* すべてのキーコンフィグ情報を削除する */
	ConfigDelete();

	/* 各キーコンフィグにデフォルトの設定を代入 */
	// ジョイパッド
	for (int i = 0; stConfig_Default_Joypad[i].iGameControl != -1; ++i)
	{
		stConfigJoypad.push_back(new CONFIG_INFO(stConfig_Default_Joypad[i]));
	}

	// キーボード＆マウス
	for (int i = 0; stConfig_Default_Keyboard_Mouse[i].iGameControl != -1; ++i)
	{
		stConfigKeyboardMouse.push_back(new CONFIG_INFO(stConfig_Default_Keyboard_Mouse[i]));
	}
}

// キーコンフィグから入力コード取得
bool DataList_Input::bGetInputCode(const std::vector<Struct_Json_Input::CONFIG_INFO*>& stConfig, int& iInputCode, int& iIquipmentType, int iTargetInputGame)
{
	// 引数
	// stConfig			: 確認したいキーコンフィグ(アドレス)
	// iInputCode		: 取得コード保存場所(アドレス)
	// iIquipmentType	: 取得入力機器保存場所(アドレス)
	// iTargetInputGame	: 確認したい入力内容(操作の種類)
	// 戻り値
	// bool				: 指定の入力内容が見つかったか(true:見つかった、false:見つからなかった)
	
	/* 対象のキーコンフィグから指定の入力内容の入力コードと入力機器を取得 */

	/* コンフィグリストから指定の入力内容を探す */
	for (const auto& config : stConfig)
	{
		/* 取得した入力内容が確認したい入力内容であるか確認 */
		if (config->iGameControl == iTargetInputGame)
		{
			// 確認したい入力内容である場合
			/* 入力コードと入力機器を返す */
			iInputCode		= config->iInput;
			iIquipmentType	= config->iEquipmentType;
			return true;
		}
	}

	/* 見つからなかった場合 */
	return false;
}
