/* 2025.02.07 駒沢風助 ファイル作成 */

#pragma once
#include <string>

/* プレイヤーモーション関連の構造体や定数の宣言を行う */

/* プレイヤーモーションID */
// 移動系
static const int	MOTION_ID_MOVE_IDLE				= 0;	// 待機
static const int	MOTION_ID_MOVE_WALK				= 1;	// 歩行
static const int	MOTION_ID_MOVE_JUMP_START		= 2;	// ジャンプ(開始)
static const int	MOTION_ID_MOVE_JUMP_UP			= 3;	// ジャンプ(上昇)
static const int	MOTION_ID_MOVE_JUMP_DOWN		= 4;	// ジャンプ(下降)
static const int	MOTION_ID_MOVE_LAND				= 5;	// 着地
static const int	MOTION_ID_MOVE_DODGE			= 6;	// 回避
// 攻撃系
static const int	MOTION_ID_ATTACK_NONE			= 0;	// 無し(※攻撃系の入力がないときに使用)
static const int	MOTION_ID_ATTACK_WEAK			= 1;	// 弱攻撃
static const int	MOTION_ID_ATTACK_CHARGE			= 2;	// 溜め
static const int	MOTION_ID_ATTACK_STRONG			= 3;	// 強攻撃(発生中)
static const int	MOTION_ID_ATTACK_STRONG_END		= 4;	// 強攻撃(終了)

/* プレイヤーモーション名 */
// 移動系
static const std::string	MOTION_MOVE_RUN			=	"mot_move_run";				// 移動
static const std::string	MOTION_MOVE_JUMP_START	=	"mot_move_jump_f_start";	// ジャンプ(開始)
static const std::string	MOTION_MOVE_JUMP_UP		=	"mot_move_jump_f_uploop";	// ジャンプ(上昇)
static const std::string	MOTION_MOVE_JUMP_FALL	=	"mot_move_jump_fall_loop";	// ジャンプ(落下)
static const std::string	MOTION_MOVE_lAND		=	"mot_move_land";			// 着地
static const std::string	MOTION_MOVE_WAIT		=	"mot_move_wait";			// 待機
// 攻撃系
static const std::string	MOTION_CHARGE_STEP		=	"mot_attack_charge_stop";	// 強攻撃(移動中)
static const std::string	MOTION_CHARGE_LOOP		=	"mot_attack_charge_loop";	// 溜め中
static const std::string	MOTION_CHARGE_FINISH	=	"mot_attack_charge_finish";	// 強攻撃(完了)

