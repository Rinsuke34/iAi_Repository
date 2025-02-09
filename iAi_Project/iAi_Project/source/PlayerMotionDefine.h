/* 2025.02.07 駒沢風助 ファイル作成 */

#pragma once
#include <string>
#include <array>
#include <utility>

/* プレイヤーモーション関連の構造体や定数の宣言を行う */

/* プレイヤーモーションID */
// 移動系
static const int	MOTION_ID_MOVE_WAIT				= 0;	// 待機
static const int	MOTION_ID_MOVE_WALK				= 1;	// 歩行
static const int	MOTION_ID_MOVE_JUMP_START		= 2;	// ジャンプ(開始)
static const int	MOTION_ID_MOVE_JUMP_UP			= 3;	// ジャンプ(上昇)
static const int	MOTION_ID_MOVE_JUMP_DOWN		= 4;	// ジャンプ(下降)
static const int	MOTION_ID_MOVE_LAND				= 5;	// 着地
static const int	MOTION_ID_MOVE_DODGE			= 6;	// 回避
// 攻撃系
static const int	MOTION_ID_ATTACK_NONE			= 7;	// 無し(※攻撃系の入力がないときに使用)
static const int	MOTION_ID_ATTACK_WEAK			= 8;	// 弱攻撃
static const int	MOTION_ID_ATTACK_CHARGE			= 9;	// 溜め
static const int	MOTION_ID_ATTACK_STRONG			= 10;	// 強攻撃(発生中)
static const int	MOTION_ID_ATTACK_STRONG_END		= 11;	// 強攻撃(終了)
// 合計
static const int	MOTION_ID_MAX					= 12;	// モーションIDの最大数

/* プレイヤーモーション名 */
// 移動系
static const std::string	MOTION_MOVE_WAIT		=	"mot_move_wait";			// 待機
static const std::string	MOTION_MOVE_WALK		=	"mot_move_run";				// 歩行
static const std::string	MOTION_MOVE_JUMP_START	=	"mot_move_jump_f_start";	// ジャンプ(開始)
static const std::string	MOTION_MOVE_JUMP_UP		=	"mot_move_jump_f_uploop";	// ジャンプ(上昇)
static const std::string	MOTION_MOVE_JUMP_FALL	=	"mot_move_jump_fall_loop";	// ジャンプ(落下)
static const std::string	MOTION_MOVE_lAND		=	"mot_move_land";			// 着地
// 攻撃系
static const std::string	MOTION_CHARGE_STEP		=	"mot_attack_charge_stop";	// 強攻撃(移動中)
static const std::string	MOTION_CHARGE_LOOP		=	"mot_attack_charge_loop";	// 溜め中
static const std::string	MOTION_CHARGE_FINISH	=	"mot_attack_charge_finish";	// 強攻撃(完了)

/* プレイヤーモーション用の構造体 */
struct PLAYER_MOTION
{
	/* メンバ変数 */
	int		iMotionID;			// モーションID
	std::string	strMotionName;	// モーション名
	float	fMotion_MaxTime;	// モーションの総再生時間
	int		iNextMotionID;		// 次のモーションID(ループさせたい場合、元のモーションと同じ値を入力)
};

/* モーションIDとモーション名を統合した定数配列 */
static const std::array<PLAYER_MOTION, MOTION_ID_MAX> MOTION_LIST =
{ {
	// モーションID,				モーション名,			モーションの総再生時間,		次のモーションID
	{ MOTION_ID_MOVE_WAIT,			MOTION_MOVE_WAIT,		-1,							MOTION_ID_MOVE_WAIT},
	{ MOTION_ID_MOVE_WALK,			MOTION_MOVE_WALK,		-1,							MOTION_ID_MOVE_WALK},
	{ MOTION_ID_MOVE_JUMP_START,	MOTION_MOVE_JUMP_START,	-1,							MOTION_ID_MOVE_JUMP_UP},
	{ MOTION_ID_MOVE_JUMP_UP,		MOTION_MOVE_JUMP_UP,	-1,							MOTION_ID_MOVE_JUMP_UP},
	{ MOTION_ID_MOVE_JUMP_DOWN,		MOTION_MOVE_JUMP_FALL,	-1,							MOTION_ID_MOVE_JUMP_DOWN},
	{ MOTION_ID_MOVE_LAND,			MOTION_MOVE_lAND,		-1,							MOTION_ID_MOVE_WAIT},
	{ MOTION_ID_MOVE_DODGE,			"",						-1,							MOTION_ID_MOVE_DODGE},
	{ MOTION_ID_ATTACK_NONE,		"" ,					-1,							MOTION_ID_ATTACK_NONE},
	{ MOTION_ID_ATTACK_WEAK,		"" ,					-1,							MOTION_ID_ATTACK_NONE},
	{ MOTION_ID_ATTACK_CHARGE,		MOTION_CHARGE_LOOP ,	-1,							MOTION_ID_ATTACK_CHARGE},
	{ MOTION_ID_ATTACK_STRONG,		MOTION_CHARGE_STEP ,	-1,							MOTION_ID_ATTACK_STRONG},
	{ MOTION_ID_ATTACK_STRONG_END,	MOTION_CHARGE_FINISH,	-1,							MOTION_ID_ATTACK_NONE}
} };

