/* 2024.12.21 駒沢風助 ファイル作成 */

#pragma once
#include "DataList_Input.h"

/* プロジェクトで使用する広域変数の宣言 */

extern DataList_Input* gpDataList_Input;	// プレイヤー入力管理クラス

/* デバッグ用描写管理フラグ */
extern bool gbDrawShadowMapFlg;					// シャドウマップの描写
extern bool gbDrawLightMapFlg;					// ライトマップの描写
extern bool gbDrawLightMapDownScaleFlg;			// ライトマップ(縮小)の描写
extern bool gpDrawLightMapGaussFlg;				// ライトマップ(ぼかし)のハンドル
