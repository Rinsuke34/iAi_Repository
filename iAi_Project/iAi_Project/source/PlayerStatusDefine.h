/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道 移動関連の定数追加 */
/* 2025.01.22 菊池雅道 攻撃関連の定数追加 */
/* 2025.02.03 菊池雅道 攻撃関連の定数追加 */
/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
/* 2025.02.10 菊池雅道 移動関連の定数追加 */
/* 2025.02.22 菊池雅道 移動関連の定数追加 */
/* 2025.02.26 菊池雅道 クールタイム関連の定数追加 */
/* 2025.02.26 菊池雅道 攻撃関連の定数追加 */
/* 2025.03.11 菊池雅道 モーション関連の定数追加 */
/* 2025.03.12 菊池雅道 スローモーション関連の定数追加 */
/* 2025.03.17 菊池雅道 移動関連の定数追加 */
/* 2025.03.18 駒沢風助 移動床ガタガタ対策 */
/* 2025.03.18 菊池雅道 クールタイム関連の定数追加 */
/* 2025.03.19 菊池雅道 定数追加 */

#pragma once
#include <string>

/* プレイヤー状態管理の構造体や定数の宣言を行う */

/* 能力値名称(json) */
const std::string	BASE_STATUS_NAME_MOVE_ACCELERATION			= "MoveAcceleration";		// プレイヤーの移動加速度
const std::string	BASE_STATUS_NAME_JUMP_SPEED					= "JumpSeepd";				// プレイヤーのジャンプ力
const std::string	BASE_STATUS_NAME_FALL_ACCELERATION			= "FallAcceleration";		// プレイヤーの落下加速度
const std::string	BASE_STATUS_NAME_FALL_SPEED_MAX				= "FallSpeed_Max";			// プレイヤーの最大落下速度
const std::string	BASE_STATUS_NAME_JUMP_COUNT_MAX				= "JumpCount_Max";			// プレイヤーのジャンプ回数(最大数)
const std::string	BASE_STATUS_NAME_DODGE_SPEED				= "DodgeSpeed";				// プレイヤーの回避速度															/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_DODGE_FRAME				= "DodgeFlame";				// プレイヤーの回避フレーム数													/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_KICKWALL_HORIZONTAL_SPEED	= "KickWallHorizontalSpeed";// プレイヤーの壁キック速度(水平成分)											/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_KICKWALL_VERTICAL_SPEED	= "KickWallVerticalSpeed";	// プレイヤーの壁キック速度(垂直成分)											/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_KICKWALL_FLAME				= "KickWallFlame";			// プレイヤーの壁キック継続フレーム数											/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STASUS_NAME_KICKWALL_INPUT_MAX_FLAME	= "KickWallInputMaxFlame";	// プレイヤーの壁キック入力猶予フレーム数										/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_MELEE_STRONG_CHANGE_CHARGE_FRAME	= "MeleeStrongChangeChargeFrame";	// プレイヤーの近距離攻撃(強)に切り替わるまでのフレーム数							/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_MELEE_STRONG_MAX_CHARGE_FRAME		= "MeleeStrongMaxChargeFrame";		// プレイヤーの近距離攻撃(強)の最大溜め時間											/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_MELEE_STRONG_MOVE_SCALE			= "MeleeStrongMoveScale";			// プレイヤーの近距離攻撃(強)の移動距離のスケール									/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_MELEE_STRONG_MOVE_SPEED			= "MeleeStrongMoveSpeed";			// プレイヤーの近距離攻撃(強)の移動速度												/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_MELEE_STRONG_CONTINUS_MAX_FRAME	= "MeleeStrongContinusMaxFrame";	// プレイヤーが近距離攻撃(強)で連続攻撃できる最大フレーム数							/* 2025.03.19 菊池雅道 定数追加 */
const std::string	BASE_STATUS_NAME_MELEE_STRONG_AIR_MAX_COUNT			= "MeleeStrongAirMaxCount";			// プレイヤーの空中での近距離攻撃(強)回数(※敵を攻撃していない場合の最大数)
const std::string	BASE_STATUS_NAME_ROCK_ON_RADIUS				= "RockOnRadius";			// ロックオン範囲の半径
const std::string	BASE_STATUS_NAME_HP_MAX						= "Hp_Max";					// プレイヤーの最大HP
const std::string	BASE_STATUS_NAME_INVINCIBLE_TIME_MAX		= "InvincibleTime_Max";		// プレイヤーの最大無敵時間
const std::string	BASE_STATUS_NAME_START_HAVE_KUNAI			= "StartHaveKunai";			// 初期状態で持っているクナイの個数
const std::string	BASE_STATUS_NAME_MAX_HAVE_KUNAI				= "MaxHaveKunai";			// 最大で持てるクナイの個数

/* ファイルパス */
const std::string FILE_PATH_STATUS = "resource/SetupData/PlayerStatusData.json";

// 移動関係
static const float	PLAER_DASH_SPEED					= 20.0f;				// プレイヤーの走り（通常）の移動速度							/* 2025.01.09 菊池雅道 移動関連の定数追加 */
static const float	PLAYER_TURN_SPEED					= 0.2f;					// プレイヤーの方向転換の速度（範囲：0.0?1.0）				/* 2025.02.10 菊池雅道 移動関連の定数追加 */
static const float	PLAYER_TURN_LIMIT					= DX_PI_F * 2.0f;		// プレイヤーの回転角度制限(ラジアン)							/* 2025.02.10 菊池雅道 移動関連の定数追加 */	/* 2025.02.13 菊池雅道 定数修正 */
static const float	PLAYER_WALL_KICK_MOVE_FLAME			= 30.0f;				// プレイヤーの壁キックの移動フレーム数							/* 2025.02.22 菊池雅道 移動関連の定数追加 */
static const float	PLAYER_WALL_KICK_HORIZONTAL_SPEED	= 80.0f;				// プレイヤーの壁キックの速度(水平成分)							/* 2025.02.22 菊池雅道 移動関連の定数追加 */
static const float	PLAYER_WALL_KICK_VERTICAL_SPEED		= -30.0f;				// プレイヤーの壁キックの速度(垂直成分)							/* 2025.02.22 菊池雅道 移動関連の定数追加 */
static const int	PLAYER_WALL_KICK_INPUT_FLAME		= 20;					// プレイヤーの壁キックの入力猶予フレーム数						/* 2025.03.17 菊池雅道 移動関連の定数追加 */
static const float	PLAYER_PLATFORM_RAND_CORRECTION		= -10.f;				// プレイヤー着地時の床との補正距離(移動床上でガタガタする対策)	/* 2025.03.18 駒沢風助 移動床ガタガタ対策 */
static const int	PLAYER_JUMP_COOLTIME				= 10;					// プレイヤーのジャンプのクールタイム							/* 2025.03.18 菊池雅道 クールタイム関連の定数追加 */

// 回避関係
static const float	PLAYER_DODGE_SPEED					= 100.0f;				// プレイヤーの回避速度											/* 2025.01.09 菊池雅道 移動関連の定数追加 */
static const int	PLAYER_DODGE_IN_AIR_LIMIT			= 2;					// プレイヤーが空中で回避できる回数								/* 2025.01.09 菊池雅道 移動関連の定数追加 */
static const int	PLAYER_DODGE_FLAME					= 30;					// プレイヤーの回避のフレーム数									/* 2025.01.09 菊池雅道 移動関連の定数追加 */
static const int	PLAYER_DODGE_COOLTIME				= 30;					// プレイヤーの回避のクールタイム								/* 2025.02.26 菊池雅道 クールタイム関連の定数追加 */

// 攻撃関係
static const int	PLAYER_CHARGE_FINISH_FLAME			= 180;			// 近接攻撃中(強)の溜め完了フレーム数		/* 2025.01.29 菊池雅道 攻撃関連の定数追加 */
static const int	PLAYER_SEARCH_RANGE_AFTER_MELEE		= 2000;			// 近接攻撃中(強)後の索敵範囲			/* 2025.02.03 菊池雅道 攻撃関連の定数追加 */
static const int	MELEE_STRONG_PERFORMANCE_DESTROY_NUM = 3;			// 近接攻撃(強)でカメラ演出を行う連続破壊数							/* 2025.03.20 菊池雅道 攻撃関連の定数追加 */
static const int	PLAYER_MELEE_WEAK_COLLTIME			= 70;			// 近接攻撃(弱)のクールタイム										/* 2025.02.26 菊池雅道 クールタイム関連の定数追加 */
static const int	PLAYER_PROJECTILE_COLLTIME			= 60;			// 遠距離攻撃のクールタイム											/* 2025.02.26 菊池雅道 クールタイム関連の定数追加 */
static const int	INIT_ATTRIBUTES_COMBO_DURATION		= 60 * 3 * 2;	// コンボの持続時間

/* プレイヤー移動状態 */
// ※状態に応じて可能な行動が変わる
static const int	PLAYER_MOVESTATUS_EVENT					= 0;	// イベント状態(操作不可)			/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_MOVESTATUS_FREE					= 1;	// 自由状態							/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_MOVESTATUS_DODGING				= 2;	// 回避状態中						/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLYAER_MOVESTATUS_DEAD					= 3;	// 死亡状態(操作不可)

/* プレイヤー攻撃状態 */
// ※状態に応じて可能な行動が変わる
static const int	PLAYER_ATTACKSTATUS_EVENT				= 0;	// イベント状態(操作不可)			/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_ATTACKSTATUS_FREE				= 1;	// 自由状態							/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_ATTACKSTATUS_MELEE_POSTURE		= 2;	// 近接攻撃構え中					/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_ATTACKSTATUS_MELEE_WEEK			= 3;	// 近接攻撃中(弱)					/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_ATTACKSTATUS_MELEE_STRONG		= 4;	// 近接攻撃中(強)					/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE	= 5;	// 遠距離攻撃構え中					/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_ATTACKSTATUS_PROJECTILE			= 6;	// 遠距離攻撃中						/* 2025.02.05 菊池雅道 ステータス関連の定数修正 */
static const int	PLAYER_ATTACKSTATUS_DEAD				= 7;	// 死亡状態(操作不可)

/* プレイヤー処理用定数 */
static const float	PLAYER_HEIGHT							= 160.f;	// 高さ(当たり判定)
static const float	PLAYER_WIDE								= 15.f;		// 幅(当たり判定)
static const float	PLAYER_CLIMBED_HEIGHT					= 10.f;		// 歩きで登れる高さ
static const int	PLAYER_CHARGE_TO_STRONG_TIME			= 30;		// 近接攻撃が強攻撃に切り替わるまでのフレーム数
static const int	PLAYER_MOVE_COLLISION_UP				= 0;		// プレイヤーの移動用コリジョン上側
static const int	PLAYER_MOVE_COLLISION_DOWN				= 1;		// プレイヤーの移動用コリジョン下側
static const int	PLAYER_MOVE_COLLISION_MAX				= 2;		// プレイヤーの移動用コリジョン数
static const int	PLAYER_MELEE_STRONG_MOVESPEED			= 100;		// 近接攻撃(強)の移動速度
static const int	PLAYER_MELEE_CHARGE_MAX					= 180;		// 近接攻撃の最大溜め時間
static const int	PLAYER_JUNP_DOWN_MOTION_SWITCH_FRAME	= 10;		// 落下時ジャンプ下降モーションに切り替える際の猶予フレーム(意図しないモーション切り替えを防止するために使用)		/* 2025.03.11 菊池雅道 モーション関連の定数追加 */
static const int	PLAYER_SLOWMOTION_COUNT_MAX				= 120;		// スローモーションの最大フレーム数																	/* 2025.03.12 菊池雅道 スローモーション関連の定数追加 */

/* プレイヤー能力値リスト */
struct PLAYER_STATUS_LIST
{
	std::string	Name;		// 能力値名称(Jsonファイル)
	void*		pValue;		// 変数(※std::variantが使用出来ないので危険だがこの方法で関数を取得する)
	std::string	Type;		// データ型
};
