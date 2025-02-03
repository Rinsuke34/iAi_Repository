/* 2024.12.22 駒沢風助 ファイル作成 */

#include "VariableDefine.h"

/* 広域変数の初期化 */

/* 実行中クラス */
DataList_Input*	gpDataList_Input	= nullptr;	// プレイヤー入力管理クラス
DataList_Sound*	gpDataList_Sound	= nullptr;	// サウンド管理クラス

/* ステージ関連 */
bool gbTutorialFlg					= false;	// チュートリアルフラグ

/* デバッグ用描写管理フラグ */
bool gbDrawShadowMapFlg				= true;		// シャドウマップの描写
bool gbDrawLightMapFlg				= true;		// ライトマップの描写
bool gbDrawLightMapDownScaleFlg		= true;		// ライトマップ(縮小)の描写
bool gbDrawLightMapGaussFlg			= true;		// ライトマップ(ぼかし)のハンドル
bool gbDrawCollisionFlg				= true;		// 全オブジェクトのコリジョン描写
bool gbDrawDeleteBackGroundFlg		= true;		// バックグランドオブジェクトの非表示
