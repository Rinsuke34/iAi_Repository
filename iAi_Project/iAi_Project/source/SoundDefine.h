/* 2025.01.30 駒沢風助 ファイル作成 */

#pragma once

/* サウンド管理の構造体や定数の宣言を行う */

/* BGM関係 */
// BGM番号
static  const int	BGM_STAGE		= 0;	// ステージ
static  const int	BGM_TITLE		= 1;	// タイトル
static  const int	BGM_HOME		= 2;	// ホーム
static  const int	BGM_MAX			= 3;	// BGM総数

// BGM名称
static const std::string BGM_NAME[BGM_MAX] =
{
    "BGM_Stage",    // ステージ
    "BGM_Title",    // タイトル
    "BGM_Home"      // ホーム
};

/* SE関係 */
// SE番号(システム関係)
static  const int   SE_SYSTEM_MOVECURSOR        = 0;    // カーソル移動
static  const int   SE_SYSTEM_DICISION          = 1;    // 決定
static  const int   SE_SYSTEM_CANCEL            = 2;    // キャンセル
// SE番号(プレイヤー関係)
static  const int   SE_PLAYER_WALK              = 3;    // 歩く
static  const int   SE_PLAYER_RUN               = 4;    // 走る
static  const int   SE_PLAYER_RUN_SP            = 5;    // 高速ダッシュ
static  const int   SE_PLAYER_JUMP              = 6;    // ジャンプ
static  const int   SE_PLAYER_LANDING           = 7;    // 着地
static  const int   SE_PLAYER_KUNAI_GET         = 8;    // クナイ入手
static  const int   SE_PLAYER_KUNAI             = 9;    // クナイ投擲
static  const int   SE_PLAYER_DODGE             = 10;   // 回避
static  const int   SE_PLAYER_ABSORB            = 11;   // 攻撃吸収
static  const int   SE_PLAYER_NIAI              = 12;   // 通常居合攻撃
static  const int   SE_PLAYER_DOWN              = 13;   // 倒れる
static  const int   SE_PLAYER_DAMAGE            = 14;   // 被ダメージ
static  const int   SE_PLAYER_CHARGE            = 15;   // 溜め居合チャージ
static  const int   SE_PLAYER_CHARGE_COMPLETE   = 16;   // 溜め居合チャージ完了
static  const int   SE_PLAYER_SPIAI             = 17;   // 溜め居合攻撃
// SE番号(エネミー関係)
static  const int   SE_ENEMY_IKURA_ATTACK       = 18;   // いくら攻撃
static  const int   SE_ENEMY_BEAM_CHARGE        = 19;   // ビームチャージ
static  const int   SE_ENEMY_BEAM_SHOT          = 20;   // ビームショット
static  const int   SE_ENEMY_DAMAGE             = 21;   // 撃破

static  const int   SE_MAX                      = 22;   // SE総数

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
    "SE_Beam_Charge",               // ビームチャージ
	"SE_Beam_Shot",                 // ビームショット
    "SE_Enemy_Damage"               // 撃破
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