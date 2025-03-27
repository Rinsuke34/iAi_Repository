/* 2024.12.22 駒沢風助 ファイル作成 */

#include "VariableDefine.h"

/* 広域変数の初期化 */

/* 実行中クラス */
DataList_Input*	gpDataList_Input	= nullptr;	// プレイヤー入力管理クラス
DataList_Sound*	gpDataList_Sound	= nullptr;	// サウンド管理クラス

/* デバッグ用描写管理フラグ */
bool gbDrawShadowMapFlg				= false;		// シャドウマップの描写
bool gbDrawLightMapFlg				= false;		// ライトマップの描写
bool gbDrawLightMapDownScaleFlg		= false;		// ライトマップ(縮小)の描写
bool gbDrawLightMapGaussFlg			= false;		// ライトマップ(ぼかし)のハンドル
bool gbDrawCollisionFlg				= false;		// 全オブジェクトのコリジョン描写
bool gbDrawDeleteBackGroundFlg		= false;		// バックグランドオブジェクトの非表示
bool gbDrawInputTest				= false;		// 入力テストの描写

