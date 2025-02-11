/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once

/* エディット関連の構造体や定数の宣言を行う */

/* エディット数 */
static const int	EDIT_MAX			= 3;	// 装備可能エディット数

/* エディットの種類 */
static const int	EDIT_TYPE_NORMAL	= 0;	// 通常
static const int	EDIT_TYPE_SPECIAL	= 1;	// 特殊
static const int	EDIT_TYPE_CURSE		= 2;	// 呪い

/* エディットのランク */
static const int	EDIT_RANK_CUPPER	= 0;	// 銅
static const int	EDIT_RANK_SILVER	= 1;	// 銀
static const int	EDIT_RANK_GOLD		= 2;	// 金

/* エディット効果 */
// 通常
static const int	EDIT_EFFECT_NORMAL_MOVE_SPEED_UP				= 0;	// 移動速度アップ
static const int	EDIT_EFFECT_NORMAL_GET_BLOOD_UP					= 1;	// ブラッド取得量アップ
static const int	EDIT_EFFECT_NORMAL_COMBO_DURATION_UP			= 2;	// コンボ継続時間アップ
static const int	EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION		= 3;	// 近接攻撃溜め時間減少
static const int	EDIT_EFFECT_NORMAL_JUMP_COUNT_UP				= 4;	// ジャンプ回数アップ
static const int	EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP			= 5;	// 空中居合攻撃回数アップ
static const int	EDIT_EFFECT_NORMAL_GET_KUNAI_UP					= 6;	// クナイ取得量アップ
static const int	EDIT_EFFECT_NORMAL_BARIER_COUNT_UP				= 7;	// バリア回数アップ
// 特殊
static const int	EDIT_EFFECT_SPECIAL_GLIDING						= 8;	// 滑空アクション追加
static const int	EDIT_EFFECT_SPECIAL_COUNTER						= 9;	// カウンターアクション追加
// 呪い
static const int	EDIT_EFFECT_CURCE_LIMIT_DASH_DODGE				= 10;	// ダッシュ、回避制限
static const int	EDIT_EFFECT_CURCE_LIMIT_HP_ONE					= 11;	// HP1制限
static const int	EDIT_EFFECT_CURCE_LIMIT_MELEE_CHARGE_CHANCEL	= 12;	// 居合キャンセル制限
// その他
static const int	EDIT_EFFECT_MAX									= 13;	// エディット効果の最大数
static const int	EDIT_EFFECT_NONE								= -1;	// なし

/* アップグレードフラグ */
static const bool	EDIT_UPGRADE_FLAG_NONE	= false;	// アップグレードなし
static const bool	EDIT_UPGRADE_FLAG_TRUE	= true;		// アップグレードあり

/* エディット用の構造体 */
struct EDIT_INFORMATION
{
	int			iEditType;		// エディットの種類
	int			iEditMinRank;	// エディットの最低ランク
	int			iEditMaxRank;	// エディットの最高ランク
	int			iEditEffect;	// エディットの効果
	bool		bEditUpgrade;	// アップグレードフラグ
	std::string	strEditName;	// エディット名
};

/* エディット一覧 */
static const std::array<EDIT_INFORMATION, EDIT_EFFECT_MAX> EDIT_LIST =
{ {
		// エディットの種類,	エディットの最低ランク,		エディットの最高ランク,		エディットの効果,								アップグレードフラグ,		エディット名
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_MOVE_SPEED_UP,				EDIT_UPGRADE_FLAG_TRUE,		"移動速度アップ"			},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_GET_BLOOD_UP,				EDIT_UPGRADE_FLAG_TRUE,		"ブラッド取得量アップ"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_COMBO_DURATION_UP,			EDIT_UPGRADE_FLAG_TRUE,		"コンボ継続時間アップ"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION,		EDIT_UPGRADE_FLAG_TRUE,		"近接攻撃ため時間減少"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_JUMP_COUNT_UP,				EDIT_UPGRADE_FLAG_TRUE,		"ジャンプ回数アップ"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP,			EDIT_UPGRADE_FLAG_TRUE,		"空中居合攻撃回数アップ"	},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_GET_KUNAI_UP,				EDIT_UPGRADE_FLAG_TRUE,		"クナイ取得量アップ"		},
		{ EDIT_TYPE_NORMAL,		EDIT_RANK_CUPPER,			EDIT_RANK_GOLD,				EDIT_EFFECT_NORMAL_BARIER_COUNT_UP,				EDIT_UPGRADE_FLAG_TRUE,		"バリア回数アップ"			},
		{ EDIT_TYPE_SPECIAL,	EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_SPECIAL_GLIDING,					EDIT_UPGRADE_FLAG_NONE,		"滑空アクション追加"		},
		{ EDIT_TYPE_SPECIAL,	EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_SPECIAL_COUNTER,					EDIT_UPGRADE_FLAG_NONE,		"カウンターアクション追加"	},
		{ EDIT_TYPE_CURSE,		EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_CURCE_LIMIT_DASH_DODGE,				EDIT_UPGRADE_FLAG_NONE,		"ダッシュ、回避制限"		},
		{ EDIT_TYPE_CURSE,		EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_CURCE_LIMIT_HP_ONE,					EDIT_UPGRADE_FLAG_NONE,		"HP1制限"					},
		{ EDIT_TYPE_CURSE,		EDIT_RANK_GOLD,				EDIT_RANK_GOLD,				EDIT_EFFECT_CURCE_LIMIT_MELEE_CHARGE_CHANCEL,	EDIT_UPGRADE_FLAG_NONE,		"居合キャンセル制限"		}
} };

