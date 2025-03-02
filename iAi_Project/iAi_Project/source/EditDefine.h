/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once

/* エディット関連の構造体や定数の宣言を行う */

/* エディット数 */
static const int	EDIT_MAX			= 5;	// 装備可能エディット数
static const int	EDIT_UPGRADE_MAX	= 5;	// エディットの強化項目数

/* エディットの種類 */
static const int	EDIT_TYPE_NORMAL	= 0;	// 通常
static const int	EDIT_TYPE_SPECIAL	= 1;	// 特殊
static const int	EDIT_TYPE_CURSE		= 2;	// 呪い

/* エディットのランク(フレーム) */
static const int	EDIT_RANK_NONE		= 0;	// ランクなし(エディット無し)
static const int	EDIT_RANK_CUPPER	= 1;	// 銅
static const int	EDIT_RANK_SILVER	= 2;	// 銀
static const int	EDIT_RANK_GOLD		= 3;	// 金
static const int	EDIT_RANK_MAX		= 4;	// ランクの最大数

/* エディット効果 */
static const int	EDIT_EFFECT_NONE								= 0;	// なし
// 通常
static const int	EDIT_EFFECT_NORMAL_MOVE_SPEED_UP				= 1;	// 移動速度アップ
static const int	EDIT_EFFECT_NORMAL_GET_BLOOD_UP					= 2;	// ブラッド取得量アップ
static const int	EDIT_EFFECT_NORMAL_COMBO_DURATION_UP			= 3;	// コンボ継続時間アップ
static const int	EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION		= 4;	// 近接攻撃溜め時間減少
static const int	EDIT_EFFECT_NORMAL_JUMP_COUNT_UP				= 5;	// ジャンプ回数アップ
static const int	EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP			= 6;	// 空中居合攻撃回数アップ
static const int	EDIT_EFFECT_NORMAL_GET_KUNAI_UP					= 7;	// クナイ取得量アップ
static const int	EDIT_EFFECT_NORMAL_BARIER_COUNT_UP				= 8;	// バリア回数アップ
// 特殊
static const int	EDIT_EFFECT_SPECIAL_GLIDING						= 9;	// 滑空アクション追加
static const int	EDIT_EFFECT_SPECIAL_COUNTER						= 10;	// カウンターアクション追加
// 呪い
static const int	EDIT_EFFECT_CURCE_LIMIT_DASH_DODGE				= 11;	// ダッシュ、回避制限
static const int	EDIT_EFFECT_CURCE_LIMIT_HP_ONE					= 12;	// HP1制限
static const int	EDIT_EFFECT_CURCE_LIMIT_MELEE_CHARGE_CHANCEL	= 13;	// 居合キャンセル制限
// その他
static const int	EDIT_EFFECT_MAX									= 14;	// エディット効果の最大数

/* エディット情報用の構造体 */
struct EDIT_DATA
{
	int			iEditRank;				// エディットのランク
	int			iEditEffect;			// エディットの効果
	int			iEditCost;				// エディットの価格(新規、ホールド中のエディットで使用)
};

/* 名称管理用構造体 */
struct EDIT_NAME
{
	std::string	strName;		// 名称(日本語)
	std::string strEngName;		// 名称(英語)
	std::string	strGrName;		// 画像名
};

/* エディットランク(フレーム)名称 */
static const std::array<EDIT_NAME, EDIT_RANK_MAX> EDIT_RANK_NAME =
{ {
	// 名称(日本語),	名称(英語),	画像名
	{ "なし",			"None",		"Test_Edit/Frame/EditFrame_None" },
	{ "銅",				"Cupper",	"Test_Edit/Frame/EditFrame_Cupper" },
	{ "銀",				"Silver",	"Test_Edit/Frame/EditFrame_Silver" },
	{ "金",				"Gold",		"Test_Edit/Frame/EditFrame_Gold" }
} };

static const std::array<EDIT_NAME, EDIT_EFFECT_MAX> EDIT_EFFECT_NAME =
{ {
	// 名称(日本語),				名称(英語),					画像名
	{ "なし",						"None",						"Test_Edit/Effect/NoImage" },
	{ "移動速度アップ",				"MoveSpeedUp",				"Test_Edit/Effect/Edit_SpeedUp" },
	{ "ブラッド取得量アップ",		"GetBloodUp",				"Test_Edit/Effect/Edit_BloodUp" },
	{ "コンボ継続時間アップ",		"ComboDurationUp",			"Test_Edit/Effect/Edit_ComboUp" },
	{ "近接攻撃ため時間減少",		"MeleeChargeReduction",		"Test_Edit/Effect/Edit_ChargeSpeedUp" },
	{ "ジャンプ回数アップ",			"JumpCountUp",				"Test_Edit/Effect/Edit_JumpAdd" },
	{ "空中居合攻撃回数アップ",		"AirMeleeCountUp",			"Test_Edit/Effect/Edit_KunaiKeep" },
	{ "クナイ取得量アップ",			"GetKunaiUp",				"Test_Edit/Effect/Edit_KunaiAdd" },
	{ "バリア回数アップ",			"BarierCountUp",			"Test_Edit/Effect/Edit_BarrierAdd" },
	{ "滑空アクション追加",			"Gliding",					"Test_Edit/Effect/NoImage" },
	{ "カウンターアクション追加",	"Counter",					"Test_Edit/Effect/NoImage" },
	{ "ダッシュ、回避制限",			"LimitDashDodge",			"Test_Edit/Effect/NoImage" },
	{ "HP1制限",					"LimitHpOne",				"Test_Edit/Effect/NoImage" },
	{ "居合キャンセル制限",			"LimitMeleeChargeChancel",	"Test_Edit/Effect/NoImage" }
} };

/* エディット管理用の構造体 */
struct EDIT_INFORMATION
{
	int			iEditType;		// エディットの種類
	int			iEditEffect;	// エディットの効果
	int			iEditRank;		// エディットのランク
	bool		bEditUpgrade;	// アップグレードフラグ
};
