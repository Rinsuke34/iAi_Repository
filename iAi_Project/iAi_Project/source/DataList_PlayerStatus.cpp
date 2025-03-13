/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.10 菊池雅道 初期化処理追加  */
/* 2025.01.22 菊池雅道 初期化処理追加  */
/* 2025.02.10 菊池雅道 初期化処理追加 */
/* 2025.02.11 菊池雅道 初期化処理追加 */
/* 2025.02.22 菊池雅道 初期化処理追加 */
/* 2025.02.26 菊池雅道 初期化処理追加 */
/* 2025.03.03 菊池雅道 初期化処理追加 */
/* 2025.03.11 菊池雅道 初期化処理追加 */

#include "DataList_PlayerStatus.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* プレイヤーステータス管理クラスの定義 */

// コンストラクタ
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* 初期化 */
	/* プレイヤー状態関連 */
	this->iPlayerMoveState					= PLAYER_MOVESTATUS_FREE;			// プレイヤーの移動状態
	this->iPlayerAttackState				= PLAYER_ATTACKSTATUS_FREE;			// プレイヤーの攻撃状態
	this->bPlayerLandingFlg					= false;							// プレイヤーが着地しているか
	this->fPlayerNowMoveSpeed				= 0;								// プレイヤーの現在の移動速度
	this->fPlayerAngleX						= 0;								// プレイヤーのX軸回転量(ラジアン)
	this->fPlayerTurnSpeed					= PLAYER_TURN_SPEED;				// プレイヤーの方向転換の速度	/* 2025.02.10 菊池雅道 初期化処理追加 */
	this->fPlayerNowFallSpeed				= 0;								// プレイヤーの現在の落下速度
	this->iPlayerNowJumpCount				= 0;								// プレイヤーのジャンプ回数(現在数)
	this->bPlayerJumpingFlag				= false;							//プレイヤーがジャンプ中かのフラグ									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerJumpCount					= 0;								//プレイヤーの現在のジャンプ回数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->fPlayerDodgeProgress				= 0.0f;								//プレイヤー回避モーション進行度									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };						//プレイヤー回避方向												/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerDodgeWhileJumpingCount		= 0;								//プレイヤージャンプ中の回避回数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->fPlayerJumpSpeed					= 0;								//プレイヤージャンプ速度											/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerNowDodgeFlame				= 0;								//プレイヤーの現在の回避フレーム数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->fPlayerDodgeSpeed					= 0;								//プレイヤー回避速度												/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->bPlayerKickWallFlg				= false;							//プレイヤーが壁を蹴ったかのフラグ									/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->iPlayerAfterKickWallCount			= 0;								//プレイヤーが壁を蹴った後のカウント								/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->bPlayerAfterKickWallFlg			= false;							//プレイヤーが壁を蹴った後のフラグ									/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->iPlayerNowAttakChargeFlame		= 0;								//現在のプレイヤー溜め攻撃チャージフレーム数						/* 2025.01.22 菊池雅道 初期化処理追加 */
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };						//プレイヤー溜め攻撃の目的地										/* 2025.01.22 菊池雅道 初期化処理追加 */
	this->iPlayerMeleeStrongChargeCount		= 0;								// プレイヤーが近距離攻撃(強)状態になってからのチャージフレーム数
	this->iPlayerMeleeStrongAirCount		= 0;								// プレイヤーが空中で近距離攻撃(強)を行った回数(※敵を攻撃していない場合)		/* 2025.02.26 菊池雅道 初期化処理追加 */
	this->bPlayerMeleeStrongEnemyAttackFlg	= false;							// プレイヤーが近距離攻撃(強)で敵を攻撃したかのフラグ							/* 2025.03.03 菊池雅道 初期化処理追加 */
	this->iPlayerMeleeStrongAfterCount		= 0;								// プレイヤーが近距離攻撃(強)で敵を攻撃した後のカウント							/* 2025.03.03 菊池雅道 初期化処理追加 */
	this->iPlayerSlowMotionCount			= 0;								// プレイヤーのスローモーションカウント											/* 2025.03.11 菊池雅道 初期化処理追加 */
	this->pLockOnEnemy						= nullptr;							// ロックオン対象のエネミー
	this->iPlayerNowInvincibleTime			= 0;								// プレイヤーの現在の残り無敵時間
	this->iPlayerComboNowCount				= 0;								// プレイヤーの現在のコンボ数
	this->iPlayerComboMaxCount				= 0;								// プレイヤーの最大コンボ数
	this->iPlayerComboDuration				= 0;								// プレイヤーのコンボの残り持続時間
	this->bPlayerAimCancelledFlg			= false;							// 遠距離攻撃(構え)がキャンセルされたかのフラグ		/* 2025.02.11 菊池雅道 初期化処理追加 */
	this->bPlayerDeadFlg					= false;							// プレイヤー死亡フラグ
	this->iPlayerDamageCount				= 0;								// 被ダメージ回数
	this->bFallFlg							= false;							// 落下フラグ

	/* プレイヤーモーション関連 */
	this->iPlayerMotion_Move				= MOTION_ID_MOVE_WAIT;				// プレイヤーモーション(移動系)
	this->iPlayerMotion_Move_Old			= -1;								// 変更前プレイヤーモーション(移動系)
	this->iPlayerMotion_Attack				= MOTION_ID_ATTACK_NONE;			// プレイヤーモーション(攻撃系)
	this->iPlayerMotion_Attack_Old			= -1;								// 変更前プレイヤーモーション(攻撃系)
	this->fMotionTimer_Move					= 0;								// モーションカウント(移動系)
	this->fMotionTimer_Move_End				= 1;								// モーションカウント(移動系/終了時間)(※初期化時の不具合防止のため1に設定)
	this->fMotionTimer_Attack				= 0;								// モーションカウント(攻撃系)
	this->fMotionTimer_Attack_End			= 1;								// モーションカウント(攻撃系/終了時間)(※初期化時の不具合防止のため1に設定)

	/* 判定処理用コリジョン */
	this->bMeleeSearchCollisionUseFlg		= false;

	/* ステータスデータの読み込み */
	LoadPlayerStatuxData();

	/* HP現在値をHP最大値に設定 */
	this->iPlayerNowHp = this->iPlayerMaxHp;
}

// デストラクタ
DataList_PlayerStatus::~DataList_PlayerStatus()
{
	/* ステータスデータの保存 */
	SavePlayerStatuxData();
}

// ステータスデータ読み込み
void DataList_PlayerStatus::LoadPlayerStatuxData()
{
	/* Jsonファイル展開 */
	std::ifstream inputFile(FILE_PATH_STATUS);

	/* ファイルの展開が成功したか確認 */
	if (inputFile.is_open() == true)
	{
		// ファイルが存在する場合
		/* 現在のステージの各評価の基準値を取得する */
		nlohmann::json	json;
		inputFile >> json;

		for (auto& option : this->astPlayerStatusList)
		{
			if (json.contains(option.Name) && json[option.Name].contains("value"))
			{
				if (option.Type == DATA_TYPE_BOOL)
				{
					*static_cast<bool*>(option.pValue) = json[option.Name]["value"].get<bool>();
				}
				else if (option.Type == DATA_TYPE_INT)
				{
					*static_cast<int*>(option.pValue) = json[option.Name]["value"].get<int>();
				}
				else if (option.Type == DATA_TYPE_FLOAT)
				{
					*static_cast<float*>(option.pValue) = json[option.Name]["value"].get<float>();
				}
			}
		}
	}
}

// ステータスデータ保存
void DataList_PlayerStatus::SavePlayerStatuxData()
{
	/* Jsonファイル読み込み */
	nlohmann::json json;

	/* 変数リストをループして JSON に書き込み */
	for (auto& option : this->astPlayerStatusList)
	{
		if (option.Type == DATA_TYPE_BOOL)
		{
			json[option.Name]["value"] = *static_cast<bool*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_INT)
		{
			json[option.Name]["value"] = *static_cast<int*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_FLOAT)
		{
			json[option.Name]["value"] = *static_cast<float*>(option.pValue);
		}
	}

	/* Jsonファイル展開 */
	std::ofstream outputFile(FILE_PATH_STATUS);

	/* Jsonファイル書き込み */
	outputFile << json.dump(4);
}
