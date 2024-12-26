/* 2024.12.08 駒沢風助 ファイル作成 */

#include "AppVariableDefine.h"

/* 広域変数の初期化 */

/* プログラム状態 */
bool gbEndFlg	= false;	// プログラム終了フラグ

/* プレイヤーの入力情報 */
Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;			// ジョイパッド
Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;		// キーボード＆マウス

/* 実行中クラス */
Fps*			gpFps				= nullptr;	// fps固定用クラス
PlayerInput*	gpPlayerInput		= nullptr;	// プレイヤー入力取得クラス
SceneServer*	gpSceneServer		= nullptr;	// シーンサーバークラス
DataListServer* gpDataListServer	= nullptr;	// データリストサーバークラス

/* フレームレート関連 */
int giNowFps	= 0;							// 現在のフレームレート

/* デバッグ用描写管理フラグ */
bool gbDrawSceneListFlg		= true;				// シーンリストの描写

