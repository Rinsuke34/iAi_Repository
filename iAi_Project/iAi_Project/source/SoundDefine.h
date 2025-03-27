/* 2025.01.30 駒沢風助 ファイル作成 */

#pragma once

/* サウンド管理の構造体や定数の宣言を行う */

/* BGM関係 */
// BGM番号
static  const int	BGM_TITLE		    = 0;	// タイトル
static  const int	BGM_HOME		    = 1;	// ホーム
static  const int   BGM_CONVERSATION_0  = 2;    // 会話0
static  const int   BGM_CONVERSATION_1  = 3;    // 会話1
static  const int   BGM_CONVERSATION_2  = 4;    // 会話2
static  const int   BGM_CONVERSATION_3  = 5;    // 会話3
static  const int   BGM_CONVERSATION_4  = 6;    // 会話4
static  const int   BGM_CONVERSATION_5  = 7;    // 会話5(エンディング)
static  const int   BGM_STAGE_0         = 8;    // ステージ0(1_1 ～ 1_3)
static  const int   BGM_STAGE_1         = 9;    // ステージ1(2_1 ～ 2_3)
static  const int   BGM_STAGE_2         = 10;   // ステージ2(3_1 ～ 3_2)
static  const int   BGM_STAGE_3         = 11;   // ステージ3(3_3)
static  const int   BGM_EDIT            = 12;   // エディット 
static  const int	BGM_MAX			    = 13;	// BGM総数

// BGM名称
static const std::string BGM_NAME[BGM_MAX] =
{
    "Title/BGM_Title",                  // タイトル
    "Home/BGM_Home" ,                   // ホーム
    "Conversation/BGM_Conv_0",          // 会話0
    "Conversation/BGM_Conv_1",          // 会話1
    "Conversation/BGM_Conv_2",          // 会話2
    "Conversation/BGM_Conv_3",          // 会話3
	"Conversation/BGM_Conv_4",          // 会話4
    "Conversation/BGM_Conv_5_Ending",   // 会話5(エンディング)
    "Stage/BGM_Stage_1-1_1-3",          // ステージ0(1_1 ～ 1_3)
    "Stage/BGM_Stage_2-1_2-3",          // ステージ1(2_1 ～ 2_3)
    "Stage/BGM_Stage_3-1_3-2",          // ステージ2(3_1 ～ 3_2)
    "Stage/BGM_Stage_3-3",              // ステージ3(3_3)
    "Edit/BGM_Edit"                     // エディット
};

/* SE関係 */
// SEの情報用構造体
struct SE_INFO
{
	std::string     aSeName;    // SE名
	int             iSeType;    // SEの種類(FALSE:通常 / TRUE:3Dサウンド)
};

// 3Dサウンドが聞こえる範囲
static  const float SE_3D_SOUND_RADIUS          = 5000.f;

// SE番号(システム関係)
static  const int   SE_SYSTEM_MOVECURSOR        = 0;    // カーソル移動
static  const int   SE_SYSTEM_DICISION          = 1;    // 決定
static  const int   SE_SYSTEM_CANCEL            = 2;    // キャンセル
static  const int   SE_SYSTEM_BEEP              = 3;    // 失敗
static  const int   SE_SYSTEM_POSEMENU          = 4;    // ポーズメニュー
static  const int   SE_SYSTEM_STAGECLEAR        = 5;    // ステージクリア
static  const int   SE_SYSTEM_RESULT_COUNT      = 6;    // リザルトカウント
static  const int   SE_SYSTEM_RESULT_RANK_SMALL = 7;    // リザルト小評価
static  const int   SE_SYSTEM_RESULT_RANK_BIG   = 8;    // リザルト大評価
static  const int   SE_SYSTEM_CONV_DICISION     = 9;    // 会話シーン決定

// SE番号(プレイヤー関係)
static  const int   SE_PLAYER_RUN               = 10;    // 走る
static  const int   SE_PLAYER_JUMP              = 11;   // ジャンプ
static  const int   SE_PLAYER_LANDING           = 12;   // 着地
static  const int   SE_PLAYER_KUNAI_GET         = 13;   // クナイ入手
static  const int   SE_PLAYER_KUNAI             = 14;   // クナイ投擲
static  const int   SE_PLAYER_DODGE             = 15;   // 回避
static  const int   SE_PLAYER_ABSORB            = 16;   // 攻撃吸収
static  const int   SE_PLAYER_NIAI              = 17;   // 通常居合攻撃
static  const int   SE_PLAYER_SLASH_HIT         = 18;   // 攻撃ヒット音
static  const int   SE_PLAYER_DOWN              = 19;   // 倒れる
static  const int   SE_PLAYER_DAMAGE            = 20;   // 被ダメージ
static  const int   SE_PLAYER_DAMAGE_ELEC       = 21;   // 被ダメージビリビリ
static  const int   SE_PLAYER_CHARGE            = 22;   // 溜め居合チャージ
static  const int   SE_PLAYER_CHARGE_COMPLETE   = 23;   // 溜め居合チャージ完了
static  const int   SE_PLAYER_CHARGE_HOLD       = 24;   // 溜めチャージホールド
static  const int   SE_PLAYER_SPIAI             = 25;   // 溜め居合攻撃
static  const int   SE_PLAYER_GET_BLOOD         = 26;   // ブラッド取得
static  const int   SE_PLAYER_SPIAI_ELEC        = 27;   // 溜め居合放電

// SE番号(エネミー関係)
static  const int   SE_ENEMY_IKURA_ATTACK       = 28;   // ノーマル攻撃音
static  const int   SE_ENEMY_DAMAGE             = 29;   // 撃破音
static  const int   SE_ENEMY_BEAM_CHARGE        = 30;   // ビームチャージ音
static  const int   SE_ENEMY_BEAM_SHOT          = 31;   // ビーム発射音
static  const int   SE_ENEMY_WARNING            = 32;   // 攻撃予告音
static  const int   SE_ENEMY_MISSILE_SHOT       = 33;   // ミサイル発射音
static  const int   SE_ENEMY_MISSILE_HIT        = 34;   // ミサイル発射音
static  const int   SE_ENEMY_MISSILE_EXPLOSION  = 35;   // ミサイル着弾ビリビリ音
static  const int   SE_ENEMY_WARNING_EXPLOSION  = 36;   // 自爆予告音
static  const int   SE_ENEMY_RUN                = 37;   // 逃走キラキラ音
// SE番号(オブジェクト関係)
static  const int   SE_GIMMIC_JUMPEXPLP         = 38;   // 強制ジャンプ
static  const int   SE_RESPAWN_ACTIVATE         = 39;   // リスポーン地点起動
static  const int   SE_GOAL_SHUTTER             = 40;   // ゴール演出(シャッター音)
static  const int   SE_GOAL_SHINE               = 41;   // ゴール演出(光あふれる)
static  const int   SE_GOAL                     = 42;   // ゴールが発する音

static  const int   SE_MAX                      = 43;   // SE総数

// SE名称
static const SE_INFO SE_NAME[SE_MAX] =
{
    // システム関係
    { "System/SE_Movecursor_ver2",       FALSE },     // カーソル移動
    { "System/SE_Player_Niai",           FALSE },     // 決定
    { "System/SE_Cancel",                FALSE },     // キャンセル
    { "System/SE_Beep",                  FALSE },     // 失敗
    { "System/SE_PoseMenu",              FALSE },     // ポーズメニュー
    { "System/SE_StageClear",            FALSE },     // ステージクリア
    { "System/SE_Result_Count",          FALSE },     // リザルトカウント
    { "System/SE_Result_Rank_Small",     FALSE },     // リザルト小評価
    { "System/SE_Result_Rank_Big",       FALSE },     // リザルト大評価
    { "System/SE_Conv_Button",           FALSE },     // 会話シーン決定
    // プレイヤー関係
    { "Player/SE_Player_Run_ver2",       FALSE },     // 走る
    { "Player/SE_Player_Jump_ver2",      FALSE },     // ジャンプ
    { "Player/SE_Player_Landing",	     FALSE },     // 着地
    { "Player/SE_Player_Getkunai",       FALSE },     // クナイ入手
    { "Player/SE_Kunai_ver2",            FALSE },     // クナイ投擲
    { "Player/SE_Player_Dodge_ver2",     FALSE },	  // 回避
    { "Player/SE_Player_Absorb",         FALSE },     // 攻撃吸収
    { "Player/SE_Player_Niai",           FALSE },     // 通常居合
    { "Player/SE_Slash_Hit",             FALSE },     // 攻撃ヒット音
    { "Player/SE_Player_Down",           FALSE },     // 倒れる
    { "Player/SE_Player_Damagehit",      FALSE },     // 被ダメージ
    { "Player/SE_Player_Damage_Elec",    FALSE },     // 被ダメージビリビリ
    { "Player/SE_Player_Charge_ver2",    FALSE },     // 溜め攻撃チャージ音
    { "Player/SE_Player_ChargeComplete", FALSE },     // 溜め攻撃チャージ完了音
    { "Player/SE_Player_Charge_Hold",    FALSE },     // 溜めチャージホールド
    { "Player/SE_Player_SPiai",          FALSE },     // 溜め攻撃音
    { "Player/SE_Player_GetBlood",       FALSE },     // ブラッド取得
    { "Player/SE_Player_SPiaiElec",	     FALSE },	  // 溜め攻撃放電
    // エネミー関係
    { "Enemy/SE_Ikura_Attack",           TRUE },      // ノーマル攻撃音
    { "Enemy/SE_Enemy_Dmage",            TRUE },      // 撃破音
    { "Enemy/SE_Beam_Charge",            TRUE },      // ビームチャージ音
    { "Enemy/SE_Beam_Shot",              TRUE },      // ビーム発射音
    { "Enemy/SE_Warning",                TRUE },      // 攻撃予告音
    { "Enemy/SE_Missile_shot",           TRUE },      // ミサイル発射音
    { "Enemy/SE_Missile_hit",            TRUE },      // ミサイル着弾音
    { "Enemy/SE_Missile_elec",           TRUE },      // ミサイル着弾ビリビリ音
    { "Enemy/SE_Warning_Jibaku",         TRUE },      // 自爆予告音
    { "Enemy/SE_Nige_Shining",           TRUE },      // 逃走キラキラ音
    // オブジェクト関係
    { "Object/SE_Gimmic_JumpExplo",      TRUE },      // 強制ジャンプ音
    { "Object/SE_RespownActivate",       TRUE },      // リスポーン地点起動
    { "Object/SE_Goal_Shutter",          FALSE},      // ゴール演出(シャッター音)
    { "Object/SE_Goal_Shine",            TRUE },      // ゴール演出(光あふれる)
    { "Object/SE_Goal",                  TRUE }       // ゴールが発する音
};

/* ボイス関連 */
// ボイスタイプ
static  const int   VOICE_TYPE_PLAYER   = 0;    // プレイヤー
static  const int   VOICE_TYPE_DOCTOR   = 1;    // 博士(サエジマキョウコ)
static  const int   VOICE_TYPE_MAX      = 2;    // ボイスタイプ総数

// ボイス番号(共通)
static  const int   VOICE_TITLE_CALL                        = 0;    // タイトルコール(共通)
static  const int   VOICE_GAMEOVER                          = 1;    // ゲームオーバー(共通)
static  const int   VOICE_RETRY                             = 2;    // リトライ(共通)
// ボイス番号(プレイヤー)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_1     = 3;    // 会話(プレイヤー/承諾1)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_2     = 4;    // 会話(プレイヤー/承諾2)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_3     = 5;    // 会話(プレイヤー/承諾3)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_4     = 6;    // 会話(プレイヤー/承諾4)
static  const int   VOICE_PLAYER_CONVERSATION_CONSENT_5     = 7;    // 会話(プレイヤー/承諾5)
static  const int   VOICE_PLAYER_ACTION                     = 8;    // アクション(プレイヤー)
static  const int   VOICE_PLAYER_STRONG_MELEE               = 9;    // 強攻撃(プレイヤー)
static  const int   VOICE_PLAYER_KILL_ENEMY                 = 10;   // 敵撃破(プレイヤー)
static  const int   VOICE_PLAYER_DAMAGE                     = 11;   // ダメージ(プレイヤー)
static  const int   VOICE_PLAYER_STAGECLEAR                 = 12;   // ステージクリア(プレイヤー)
static  const int   VOICE_PLAYER_PROJECTILE                 = 13;   // 遠距離攻撃(プレイヤー)
// ボイス番号(博士)
static  const int   VOICE_DOCTOR_CONVERSATION_WELLWELL      = 14;   // 会話(博士/やれやれ)
static  const int   VOICE_DOCTOR_CONVERSATION_SO            = 15;   // 会話(博士/それで)
static  const int   VOICE_DOCTOR_PRAISE                     = 16;   // 賞賛(博士)
static  const int   VOICE_DOCTOR_RESULT_S                   = 17;   // 結果S(博士)
static  const int   VOICE_DOCTOR_RESULT_A                   = 18;   // 結果A(博士)
static  const int   VOICE_DOCTOR_RESULT_BC                  = 19;   // 結果BC(博士)
static  const int   VOICE_DOCTOR_RESULT_D                   = 20;   // 結果D(博士)
static  const int   VOICE_DOCTOR_CONVERSATION_CONSENT       = 21;   // 会話(博士/ああ)
static  const int   VOICE_DOCTOR_CONVERSATION_BYTHEWAY      = 22;   // 会話(博士/ところで)
static  const int   VOICE_DOCTOR_CONVERSATION_THAT_1        = 23;   // 会話(博士/あれは1)
static  const int   VOICE_DOCTOR_CONVERSATION_THAT_2        = 24;   // 会話(博士/あれは2)

static  const int   VOICE_MAX                               = 54;   // ボイス総数(一部重複あり)

// ボイス情報配列用構造体
struct VOICE_INFO
{
	int         iVoiceType;     // ボイスタイプ
	int         iVoiceNo;       // ボイス番号
	std::string aVoiceName;     // ファイル名
};

// ボイスハンドル管理用構造体
struct VOICE_HANDLE_INFO
{
	int         iVoiceHandle;   // ボイスハンドル
	int         iVoiceType;     // ボイスタイプ
	int         iVoiceNo;       // ボイス番号
};

// ファイル名称(ボイスタイプ)
static const std::string VOICE_TYPE_NAME[VOICE_TYPE_MAX] =
{
    "Player",   // プレイヤー
    "Doctor"    // 博士
};

// ボイス情報
const VOICE_INFO stVoice_Info[VOICE_MAX] =
{
    // ボイスタイプ,        ボイス番号,                             ファイル名
    { VOICE_TYPE_PLAYER,    VOICE_TITLE_CALL,                       "CV_P_Title1"       },      // タイトルコール(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_TITLE_CALL,                       "CV_P_Title2"       },      // タイトルコール(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_TITLE_CALL,                       "CV_P_Title3"       },      // タイトルコール(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_1,    "CV_P_Understand01" },      // 会話(プレイヤー/承諾1)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_2,    "CV_P_Understand02" },      // 会話(プレイヤー/承諾2)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_3,    "CV_P_Understand03" },      // 会話(プレイヤー/承諾3)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_4,    "CV_P_Understand04" },      // 会話(プレイヤー/承諾4)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_CONVERSATION_CONSENT_5,    "CV_P_Understand05" },      // 会話(プレイヤー/承諾5)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_ACTION,                    "CV_P_Move01"       },      // アクション(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_ACTION,                    "CV_P_Move02"       },      // アクション(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_ACTION,                    "CV_P_Move03"       },      // アクション(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STRONG_MELEE,              "CV_P_ChargeIai1"   },      // 強攻撃(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STRONG_MELEE,              "CV_P_ChargeIai2"   },      // 強攻撃(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd1"   },      // 敵撃破(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd2"   },      // 敵撃破(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd3"   },      // 敵撃破(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd4"   },      // 敵撃破(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_KILL_ENEMY,                "CV_P_AttackEnd5"   },      // 敵撃破(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_DAMAGE,                    "CV_P_Damage"       },      // ダメージ(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear1"   },      // ステージクリア時(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear2"   },      // ステージクリア時(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear3"   },      // ステージクリア時(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear4"   },      // ステージクリア時(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_STAGECLEAR,                "CV_P_GameClear5"   },      // ステージクリア時(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_GAMEOVER,                         "CV_P_GameOver1"    },      // ゲームオーバー(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_GAMEOVER,                         "CV_P_Gameover2"    },      // ゲームオーバー(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_RETRY,                            "CV_P_Retry"        },      // リトライ(プレイヤー)
    { VOICE_TYPE_PLAYER,    VOICE_PLAYER_PROJECTILE,                "CV_P_Kunai"        },      // ゲームオーバー(プレイヤー)
    { VOICE_TYPE_DOCTOR,    VOICE_TITLE_CALL,                       "CV_S_Title"        },      // タイトルコール(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_WELLWELL,     "CV_S_Wellwell"     },      // 会話(博士/やれやれ)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_SO,           "CV_S_So"           },      // 会話(博士/それで)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise1"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise2"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise3"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise4"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise5"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise6"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise7"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_PRAISE,                    "CV_S_Praise8"      },      // 賞賛(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S1"    },      // 結果S(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S2"    },      // 結果S(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S3"    },      // 結果S(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_S,                  "CV_S_Result_S4"    },      // 結果S(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_A,                  "CV_S_Result_A"     },      // 結果A(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_BC,                 "CV_S_Result_BC"    },      // 結果BC(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_D,                  "CV_S_Result_D1"    },      // 結果D(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_RESULT_D,                  "CV_S_Result_D2"    },      // 結果D(博士)
    { VOICE_TYPE_DOCTOR,    VOICE_GAMEOVER,                         "CV_S_Defeal1"      },      // ゲームオーバー(共通)
    { VOICE_TYPE_DOCTOR,    VOICE_GAMEOVER,                         "CV_S_Defeal2"      },      // ゲームオーバー(共通)
    { VOICE_TYPE_DOCTOR,    VOICE_RETRY,                            "CV_S_Retry"        },      // リトライ(共通)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_CONSENT,      "CV_S_Aa"           },      // 会話(博士/ああ)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_BYTHEWAY,     "CV_S_ByTheWay"     },      // 会話(博士/ところで)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_THAT_1,       "CV_S_That"         },      // 会話(博士/あれは1)
    { VOICE_TYPE_DOCTOR,    VOICE_DOCTOR_CONVERSATION_THAT_2,       "CV_S_That2"        },      // 会話(博士/あれは2)
};