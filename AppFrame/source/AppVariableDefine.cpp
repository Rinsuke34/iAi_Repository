/* 2024.12.08 駒沢風助 ファイル作成 */

#include "AppVariableDefine.h"

/* 広域変数の初期化 */

/* プログラム状態 */
bool gbEndFlg	= false;	// プログラム終了フラグ

/* フォント関連 */
int	giFontHandle_Normal	= 0;	// フォントハンドル(通常サイズ)
int giFonthandle_Big	= 0;	// フォントハンドル(大サイズ)

/* プレイヤーの入力情報 */
Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;					// ジョイパッド
Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;				// キーボード＆マウス
bool										gbUseMouseFlg			= true;		// マウス使用フラグ(有効であるならばカーソルを描写＆中心固定解除)
unsigned char								gucTriggerThreshold		= 0;		// トリガー入力の閾値

/* 実行中クラス */
Fps*			gpFps				= nullptr;	// fps固定用クラス
PlayerInput*	gpPlayerInput		= nullptr;	// プレイヤー入力取得クラス
SceneServer*	gpSceneServer		= nullptr;	// シーンサーバークラス
DataListServer* gpDataListServer	= nullptr;	// データリストサーバークラス

/* フレームレート関連 */
int	giNowFps	= 0;						// 現在のフレームレート

/* デバッグ用描写管理フラグ */
bool gbDrawSceneListFlg		= false;		// シーンリストの描写
bool gbDrawDatalistFlg		= true;			// データリストの描写
bool gbDrawFpsFlg			= false;		// フレームレートの描写

/* ローディング関連 */
bool gbNowLoadingFlg		= false;		// ロード中フラグ