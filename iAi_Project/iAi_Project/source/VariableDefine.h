/* 2024.12.21 駒沢風助 ファイル作成 */

#pragma once

/* データリスト */
#include "DataList_Input.h"
#include "DataList_Sound.h"

/* プロジェクトで使用する広域変数の宣言 */

/* 実行中クラス */
extern DataList_Input*	gpDataList_Input;	// プレイヤー入力管理クラス
extern DataList_Sound*	gpDataList_Sound;	// サウンド管理クラス

/* ステージ関連 */
extern bool gbTutorialFlg;					// チュートリアルフラグ

/* デバッグ用描写管理フラグ */
extern bool gbDrawShadowMapFlg;				// シャドウマップの描写
extern bool gbDrawLightMapFlg;				// ライトマップの描写
extern bool gbDrawLightMapDownScaleFlg;		// ライトマップ(縮小)の描写
extern bool gbDrawLightMapGaussFlg;			// ライトマップ(ぼかし)のハンドル
extern bool gbDrawCollisionFlg;				// コリジョン描写
extern bool gbDrawDeleteBackGroundFlg;		// バックグランド非表示
extern bool gbDrawPlayerInputFlg;			// プレイヤー入力内容の描写
