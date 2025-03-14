/* 2025.01.31 石川智也 ファイル作成 */

#pragma once

/* エネミーで使用する定数の宣言を行う */

static const int	ENEMY_X_DISTANCE		= 1000;		// エネミーのX軸の探知範囲
static const int	ENEMY_Y_DISTANCE		= 1000;		// エネミーのY軸の探知範囲
static const int	ENEMY_Z_DISTANCE		= 1000;		// エネミーのZ軸の探知範囲
static const int	ENEMY_DETONATION_RANGE	= 300;		// エネミーの起爆範囲
static const int	ENEMY_EXPLOSION_RANGE	= 500;		// エネミーの爆発範囲
static const int	ENEMY_X_ESCAPE_DISTANCE	= 600;		// エネミーのX軸の逃げる範囲
static const int	ENEMY_Z_ESCAPE_DISTANCE	= 600;		// エネミーのZ軸の逃げる範囲
static const int	ENEMY_ESCAPE_SPEED		= 20;		// エネミーの逃げる速度
static const int	ENEMY_CHASE_SPEED		= 20;		// エネミーの追う速度
static const int	ENEMY_NORMAL_BULLET_INTERVAL			= 250;		//ノーマルエネミーの弾の発射間隔
static const int	ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL	= 20;		//ノーマルエネミーの弾の誘導間隔
static const int	ENEMY_BEAM_INTERVAL = 650;			//ビームの発射間隔
static const int	ENEMY_MISSILE_INTERVAL = 100;		//ミサイルの発射間隔
static const float	ENEMY_GRAVITY_SREED = 1.0f;		// 重力の速度　Y軸の下方向なのでマイナスとする

/* ゴールオブジェクト */
static const int	ENEMY_GOAL_OBJECT_HEIGHT	= 160;		// ゴールオブジェクトの高さ			/* 2025.01.31 駒沢風助 ゴールオブジェクト修正 */


