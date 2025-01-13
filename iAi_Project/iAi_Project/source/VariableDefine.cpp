/* 2024.12.22 駒沢風助 ファイル作成 */

#include "VariableDefine.h"

/* 広域変数の初期化 */

// 実行中クラス
DataList_Input* gpDataList_Input	= nullptr;	// プレイヤー入力管理クラス

/* デバッグ用描写管理フラグ */
bool gbDrawShadowMapFlg	= true;		// シャドウマップの描写
bool gbDrawLightMapFlg	= true;		// ライトマップの描写
