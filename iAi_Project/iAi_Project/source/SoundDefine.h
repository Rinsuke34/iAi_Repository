/* 2025.01.30 駒沢風助 ファイル作成 */

#pragma once

/* サウンド管理の構造体や定数の宣言を行う */

/* BGM関係 */
// BGM番号
const int	BGM_STAGE		= 0;	// ステージ
const int	BGM_TITLE		= 1;	// タイトル
const int	BGM_HOME		= 2;	// ホーム
const int	BGM_MAX			= 3;	// BGM総数

// BGM名称
static const std::string BGM_NAME[BGM_MAX] =
{
    "BGM_Stage",    // ステージ
    "BGM_Title",    // タイトル
    "BGM_Home"      // ホーム
};

/* SE関係 */
// SE番号(システム関係)
const int   SE_SYSTEM_MOVECURSOR        = 0;    // カーソル移動
const int   SE_SYSTEM_DICISION          = 1;    // 決定
const int   SE_SYSTEM_CANCEL            = 2;    // キャンセル
// SE番号(プレイヤー関係)
const int   SE_PLAYER_WALK              = 3;    // 歩く
const int   SE_PLAYER_RUN               = 4;    // 走る
const int   SE_PLAYER_RUN_SP            = 5;    // 高速ダッシュ
const int   SE_PLAYER_JUMP              = 6;    // ジャンプ
const int   SE_PLAYER_LANDING           = 7;    // 着地
const int   SE_PLAYER_KUNAI_GET         = 8;    // クナイ入手
const int   SE_PLAYER_KUNAI             = 9;    // クナイ投擲
const int   SE_PLAYER_DODGE             = 10;   // 回避
const int   SE_PLAYER_ABSORB            = 11;   // 攻撃吸収
const int   SE_PLAYER_NIAI              = 12;   // 通常居合攻撃
const int   SE_PLAYER_DOWN              = 13;   // 倒れる
const int   SE_PLAYER_DAMAGE            = 14;   // 被ダメージ
const int   SE_PLAYER_CHARGE            = 15;   // 溜め居合チャージ
const int   SE_PLAYER_CHARGE_COMPLETE   = 16;   // 溜め居合チャージ完了
const int   SE_PLAYER_SPIAI             = 17;   // 溜め居合攻撃
// SE番号(エネミー関係)
const int   SE_ENEMY_IKURA_ATTACK       = 18;   // いくら攻撃
const int   SE_ENEMY_BEAM_ATTACK        = 19;   // ビーム攻撃
const int   SE_ENEMY_DAMAGE             = 20;   // 撃破

const int   SE_MAX                      = 21;   // SE総数

// SE名称
static const std::string SE_NAME[SE_MAX] =
{
    // システム関係
    "SE_Movecursor",                // カーソル移動
    "SE_Decision",                  // 決定
    "SE_Cancel",                    // キャンセル
    // プレイヤー関係
    "SE_Player_Walk",               // 歩く
    "SE_Player_Run",                // 走る
    "SE_Player_SPRun",              // 高速ダッシュ
    "SE_Player_Jump",               // ジャンプ
    "SE_Player_Landing",            // 着地
    "SE_Player_Getkunai",           // クナイ入手
    "SE_Player_Kunai",              // クナイ投擲
    "SE_Player_Dodge",              // 回避
    "SE_Player_Absorb",             // 攻撃吸収
    "SE_Player_Niai",               // 通常居合攻撃
    "SE_Player_Down",               // 倒れる
    "SE_Player_Damage",             // 被ダメージ
    "SE_Player_Charge",             // 溜め居合チャージ
    "SE_Player_ChargeComplete",     // 溜め居合チャージ官僚
    "SE_Player_SPiai",              // 溜め居合攻撃
    // エネミー関係
    "SE_Ikura_Attack",              // いくら攻撃
    "SE_Beam_Attack",               // ビーム攻撃
    "SE_Enemy_Damage"               // 撃破
};
