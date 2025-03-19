/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include <vector>
#include <thread>
#include <future>
#include "AppStructDefine.h"
#include "Fps.h"
#include "PlayerInput.h"
#include "SceneServer.h"
#include "DataListServer.h"

/* 広域変数の宣言 */

/* プログラム状態 */
extern bool gbEndFlg;	// プログラム終了フラグ

/* フォント関連 */
extern int giFontHandle_Small;					// フォントハンドル(マキナス/通常サイズ)
extern int giFontHandle_Medium;					// フォントハンドル(マキナス/中サイズ)
extern int giFontHandle_Large;					// フォントハンドル(マキナス/大サイズ)
extern int giFontHandle_NotoSerifJP_Medium;		// フォントハンドル(のとせりふ/セリフテキスト用)
extern int giFontHandle_NotoSerifJP_SemiBold;	// フォントハンドル(のとせりふ/ネームタグ、オプション用)

/* プレイヤーの入力情報 */
extern Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;			// ジョイパッド
extern Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;		// キーボード＆マウス
extern bool											gbUseMouseFlg;				// マウス使用フラグ(有効であるならばカーソルを描写＆中心固定解除)
extern unsigned char								gucTriggerThreshold;		// トリガー入力の閾値

/* 実行中クラス */
extern Fps* gpFps;								// fps固定用クラス
extern PlayerInput* gpPlayerInput;				// プレイヤー入力取得クラス
extern SceneServer* gpSceneServer;				// シーンサーバークラス
extern DataListServer* gpDataListServer;		// データリストサーバークラス

/* フレームレート関連 */
extern int giNowFps;							// 現在のフレームレート

/* デバッグ用描写管理フラグ */
extern bool gbDrawSceneListFlg;					// シーンリストの描写
extern bool	gbDrawDatalistFlg;					// プレイヤーステータスの描写
extern bool gbDrawFpsFlg;						// フレームレートの描写

/* ローディング関連 */
extern bool gbNowLoadingFlg;					// ロード中フラグ
