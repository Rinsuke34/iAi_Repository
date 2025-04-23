/* 2024.12.08 駒沢風助 ファイル作成 */

#include "AppVariableDefine.h"

/* 広域変数の初期化 */

/* プログラム状態 */
bool gbEndFlg	= false;	// プログラム終了フラグ

/* フォント関連 */
int giFontHandle_Small					= 0;	// フォントハンドル(マキナス/通常サイズ)
int giFontHandle_Medium					= 0;	// フォントハンドル(マキナス/中サイズ)
int giFontHandle_Large					= 0;	// フォントハンドル(マキナス/大サイズ)
int giFontHandle_NotoSerifJP_Medium		= 0;	// フォントハンドル(のとせりふ/セリフテキスト用)
int giFontHandle_NotoSerifJP_SemiBold	= 0;	// フォントハンドル(のとせりふ/ネームタグ、オプション用)

/* プレイヤーの入力情報 */
Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;					// ジョイパッド
Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;				// キーボード＆マウス
bool										gbUseMouseFlg			= false;	// マウス使用フラグ(有効であるならばカーソルを描写＆中心固定解除)
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
bool gbDrawDatalistFlg		= false;		// データリストの描写
bool gbDrawFpsFlg			= true;			// フレームレートの描写

/* ローディング関連 */
bool gbNowLoadingFlg		= false;		// ロード中フラグ