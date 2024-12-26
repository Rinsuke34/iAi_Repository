/* 2024.12.08 駒沢風助 ファイル"仮"作成 */

#include "PlayerInput.h"
#include "AppConstantDefine.h"
#include "AppVariableDefine.h"

/* プレイヤーの入力取得クラスの定義 */

// コンストラクタ
PlayerInput::PlayerInput()
{
	/* 初期化 */
	gstJoypadInputData			= {};	// ジョイパッド
	gstKeyboardInputData		= {};	// キーボード＆マウス
}

// プレイヤーの入力取得
void PlayerInput::Input()
{
	/* ジョイパッドの入力取得 */
	InputJoypad();

	/* キーボード＆マウスの入力取得 */
	InputKeyboard();
}

// 入力取得_ジョイパッド
void PlayerInput::InputJoypad()
{
	/* ジョイパッド用の入力取得 */

	/* 前回の入力を保存 */
	Struct_Input::PLAYER_INPUT_JOYPAD pOldJoypadInput = gstJoypadInputData;

	/* ジョイパッド(1番)からのホールド入力情報を得る */
	gstJoypadInputData.igInput[INPUT_HOLD] = GetJoypadInputState(DX_INPUT_PAD1);

	/* トリガ入力情報の生成 */
	gstJoypadInputData.igInput[INPUT_TRG] = (gstJoypadInputData.igInput[INPUT_HOLD] ^ pOldJoypadInput.igInput[INPUT_HOLD]) & gstJoypadInputData.igInput[INPUT_HOLD];

	/* リリース入力情報の生成 */
	gstJoypadInputData.igInput[INPUT_REL] = (gstJoypadInputData.igInput[INPUT_HOLD] ^ pOldJoypadInput.igInput[INPUT_HOLD]) & pOldJoypadInput.igInput[INPUT_HOLD];

	/* 左アナログスティックの入力量を取得 */
	GetJoypadAnalogInput(&gstJoypadInputData.iXAnalog, &gstJoypadInputData.iYAnalog, DX_INPUT_PAD1);
}

// 入力取得_キーボード＆マウス
void PlayerInput::InputKeyboard()
{
	/* キーボード＆マウス用の入力取得 */

	/* 前回の入力を保存 */
	Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE pOldKeyboardInput = gstKeyboardInputData;

	/* キーボードからのホールド入力情報を得る */
	GetHitKeyStateAll(gstKeyboardInputData.cgInput[INPUT_HOLD]);
	
	for (int i = 0; i < 256; i++)
	{
		/* トリガ入力情報の生成 */
		gstKeyboardInputData.cgInput[INPUT_TRG][i] = (gstKeyboardInputData.cgInput[INPUT_HOLD][i] ^ pOldKeyboardInput.cgInput[INPUT_HOLD][i]) & gstKeyboardInputData.cgInput[INPUT_HOLD][i];

		/* リリース入力情報の生成 */
		gstKeyboardInputData.cgInput[INPUT_REL][i] = (gstKeyboardInputData.cgInput[INPUT_HOLD][i] ^ pOldKeyboardInput.cgInput[INPUT_HOLD][i]) & pOldKeyboardInput.cgInput[INPUT_HOLD][i];
	}

	/* マウスのホールド入力情報を得る */
	gstKeyboardInputData.igInput[INPUT_HOLD] = GetMouseInput();

	/* マウスのトリガ入力情報の生成 */
	gstKeyboardInputData.igInput[INPUT_TRG] = (gstKeyboardInputData.igInput[INPUT_HOLD] ^ pOldKeyboardInput.igInput[INPUT_HOLD]) & gstKeyboardInputData.igInput[INPUT_HOLD];

	/* マウスのリリース入力情報の生成 */
	gstKeyboardInputData.igInput[INPUT_REL] = (gstKeyboardInputData.igInput[INPUT_HOLD] ^ pOldKeyboardInput.igInput[INPUT_HOLD]) & pOldKeyboardInput.igInput[INPUT_HOLD];

	/* マウス座標取得 */
	int iMouseX, iMouseY;	// マウス座標
	GetMousePoint(&iMouseX, &iMouseY);

	/* マウス原点設定 */
	// ※マウス座標の中心を原点として移動量を取得する
	int iMouseOriginX = SCREEN_SIZE::WIDE	/ 2;
	int iMouseOriginY = SCREEN_SIZE::HEIGHT	/ 2;

	/* マウス移動量測定 */
	gstKeyboardInputData.iMouseMoveX = iMouseX - iMouseOriginX;
	gstKeyboardInputData.iMouseMoveY = iMouseY - iMouseOriginY;

	/* マウス座標リセット */
	SetMousePoint(iMouseOriginX, iMouseOriginY);

	// マウスカーソルを非表示にする
	SetMouseDispFlag(FALSE);
}
