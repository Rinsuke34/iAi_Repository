/* 2024.12.21 駒沢風助 ファイル作成 */

#pragma once

/* データリスト */
#include "DataList_Input.h"
#include "DataList_Sound.h"

/* プロジェクトで使用する広域変数の宣言 */

/* 実行中クラス */
extern DataList_Input*	gpDataList_Input;	// プレイヤー入力管理クラス
extern DataList_Sound*	gpDataList_Sound;	// サウンド管理クラス

/* デバッグ用描写管理フラグ */
extern bool gbDrawShadowMapFlg;				// シャドウマップの描写
extern bool gbDrawLightMapFlg;				// ライトマップの描写
extern bool gbDrawLightMapDownScaleFlg;		// ライトマップ(縮小)の描写
extern bool gbDrawLightMapGaussFlg;			// ライトマップ(ぼかし)のハンドル
extern bool gbDrawCollisionFlg;				// コリジョン描写
extern bool gbDrawDeleteBackGroundFlg;		// バックグランド非表示
extern bool gbDrawInputTest;				// 入力テストの描写
extern bool gbDrawStopBloomFlg;				// 疑似発光の無効化フラグ