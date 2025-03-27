/* 2025.02.18 菊池雅道 ファイル作成 */

#pragma once

/* プレイヤーバレットで使用する定数の宣言を行う */

/* 近接攻撃(弱)関係 */
static const float	PLAYER_MELEE_WEAK_RADIUS	= 100.0f;			// 近接攻撃(弱)の攻撃範囲(半径)
static const float	PLAYER_MELEE_WEAK_DISTANCE	= 100.0f;			// 近接攻撃(弱)のバレットのプレイヤーからの距離

/* クナイ関連 */
static const float	KUNAI_RANGE				= 5000.0f;			// クナイの射程距離
static const float	WARP_KUNAI_SPEED		= 100.0f;			// ワープクナイの速度
static const float	EXPLOSION_KUNAI_SPEED	= 100.0f;			// 爆発クナイの速度
static const float	KUNAI_ATTACK_RADIUS		= 1000.0f;			// クナイの攻撃範囲(半径)
static const int	KUNAI_ATTACK_COUNT		= 20;				// クナイの攻撃持続時間(フレーム数)
