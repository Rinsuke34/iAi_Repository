/* 2024.02.10 石川智也 ファイル作成 */
/* 2024.03.10 駒沢風助 移動床追加 */

#pragma once

/* 消失床関連 */
static const int GIMMICK_DISAPPEAR_TIME					= 90;	// ギミックの消滅時間
static const int GIMMICK_TEXTURE_CHANGE_COUNT			= 90;	// テクスチャ変更カウント
static const int GIMMICK_TEXTURE_CHANGE_FIRST_COUNT		= 90;	// ギミックテクスチャ変更カウント
static const int GIMMICK_TEXTURE_CHANGE_SECOND_COUNT	= 90;	// ギミックテクスチャ変更カウント
static const int GIMMICK_SPAWN_COUNT					= 60;	// ギミックスポーンカウント
static const int GIMMICK_BLINK_TIME						= 10;	// 点滅時間

/* 移動床関連 */
static const float	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_SHORT			= 400.f;		// 移動床の移動距離(短)			/* 2024.03.10 駒沢風助 移動床追加 */
static const float	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_NORMAL			= 800.f;		// 移動床の移動距離(中)			/* 2024.03.10 駒沢風助 移動床追加 */
static const float	GIMMICK_MOVEFLOOR_MOVE_DISTANCE_LONG			= 1200.f;		// 移動床の移動距離(長)			/* 2024.03.10 駒沢風助 移動床追加 */
static const float	GIMMICK_MOVEFLOOR_MOVE_SPEED					= 5.f;			// 移動床の移動速度				/* 2024.03.10 駒沢風助 移動床追加 */
