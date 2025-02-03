/* 2025.02.03 石川智也 ファイル作成 */

#pragma once

/* エネミーで使用する定数の宣言を行う */

/* エネミー自爆型 */
static const int	ENEMY_NORMAL_DURATION_COUNT = 130;					//ノーマル弾の持続カウント
static const int	ENEMY_NORMAL_BULLET_COUNT = 120;					//ノーマル弾発射カウント
static const int	ENEMY_MISSILE_DURATION_COUNT = 350;					//ミサイル弾の持続カウント
static const int	ENEMY_MISSILE_BULLET_UP_COUNT = 345;				//ミサイル弾発射カウント
static const int	ENEMY_MISSILE_BULLET_DOWN_COUNT = 230;				//ミサイル弾打ち下げカウント
static const int	ENEMY_MISSILE_BULLET_GUIDANCE_COUNT = 190;			//ミサイル弾誘導カウント

static int iEnemyMissileDurationCount = ENEMY_MISSILE_DURATION_COUNT;	//ミサイル弾の持続カウント
static int iEnemyNormalDurationCount = ENEMY_NORMAL_DURATION_COUNT;		//ノーマル弾の持続カウント