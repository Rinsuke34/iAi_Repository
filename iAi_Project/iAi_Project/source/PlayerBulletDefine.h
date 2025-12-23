/* 2025.02.18 菊池雅道 ファイル作成 */

#pragma once

/* プレイヤーバレットで使用する定数の宣言を行う */

/* 近接攻撃(弱)関係 */
static const float	PLAYER_MELEE_WEAK_RADIUS	= 100.0f;			// 近接攻撃(弱)の攻撃範囲(半径)
static const float	PLAYER_MELEE_WEAK_DISTANCE	= 100.0f;			// 近接攻撃(弱)のバレットのプレイヤーからの距離
static const int	PLAYER_MELEE_WEAK_DELETE_COUNT = 30;			// 近接攻撃(弱)のバレットの削除カウント(フレーム数)

/* 近接攻撃(強)関係 */
static const int	PLAYER_MELEE_STRONG_DELETE_COUNT = 30;		// 近接攻撃(強)のバレットの削除カウント(フレーム数)

/* クナイ関連 */
static const float	KUNAI_RANGE						= 5000.0f;			// クナイの射程距離
static const float	WARP_KUNAI_SPEED				= 100.0f;			// ワープクナイの速度
static const float	EXPLOSION_KUNAI_SPEED			= 100.0f;			// 爆発クナイの速度
static const float	KUNAI_ATTACK_RADIUS				= 1000.0f;			// クナイの攻撃範囲(半径)
static const int	KUNAI_ATTACK_COUNT				= 20;				// クナイの攻撃持続時間(フレーム数)
static const float	KUNAI_WARP_RADIUS				= 50.0f;			// ワープクナイの高さ調整範囲
static const float	KUNAI_WARP_ADJUST_HEIGHT		= 3.0f;				// ワープクナイの高さ調整量(プレイヤーの身長の何倍か)
static const float	KUNAI_WARP_POSITION_Z_OFFSET	= 250.0f;			// ワープ位置のZ方向オフセット
