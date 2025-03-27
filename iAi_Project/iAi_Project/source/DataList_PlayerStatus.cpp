/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.10 菊池雅道 初期化処理追加  */
/* 2025.01.22 菊池雅道 初期化処理追加  */
/* 2025.02.10 菊池雅道 初期化処理追加 */
/* 2025.02.11 菊池雅道 初期化処理追加 */
/* 2025.02.22 菊池雅道 初期化処理追加 */
/* 2025.02.26 菊池雅道 初期化処理追加 */
/* 2025.03.03 菊池雅道 初期化処理追加 */
/* 2025.03.11 菊池雅道 初期化処理追加 */
/* 2025.03.17 菊池雅道 初期化処理追加 */
/* 2025.03.19 菊池雅道 初期化処理追加 */
/* 2025.03.23 菊池雅道 初期化処理追加 */

#include "DataList_PlayerStatus.h"
#include <vector>
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
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };						//プレイヤー回避方向												/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerDodgeWhileJumpingCount		= 0;								//プレイヤージャンプ中の回避回数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->iPlayerNowDodgeFlame				= 0;								//プレイヤーの現在の回避フレーム数									/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->fPlayerDodgeSpeed					= 0;								//プレイヤー回避速度												/* 2025.01.10 菊池雅道 初期化処理追加 */
	this->bPlayerWallTouchFlg				= false;							//プレイヤーが壁に接触したかのフラグ								/* 2025.03.17 菊池雅道 初期化処理追加 */
	this->iPlayerAfterWallTouchCount		= 0;								//プレイヤーが壁に接触してからの経過フレーム数						/* 2025.03.17 菊池雅道 初期化処理追加 */
	this->bPlayerKickWallFlg				= false;							//プレイヤーが壁を蹴ったかのフラグ									/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->iPlayerAfterKickWallCount			= 0;								//プレイヤーが壁を蹴った後のカウント								/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->bPlayerAfterKickWallFlg			= false;							//プレイヤーが壁を蹴った後のフラグ									/* 2025.02.22 菊池雅道 初期化処理追加 */
	this->iPlayerNowAttakChargeFlame		= 0;								//現在のプレイヤー溜め攻撃チャージフレーム数						/* 2025.01.22 菊池雅道 初期化処理追加 */
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };						//プレイヤー溜め攻撃の目的地										/* 2025.01.22 菊池雅道 初期化処理追加 */
	this->iPlayerMeleeStrongChargeCount		= 0;								// プレイヤーが近距離攻撃(強)状態になってからのチャージフレーム数
	this->iPlayerMeleeStrongAirCount		= 0;								// プレイヤーが空中で近距離攻撃(強)を行った回数(※敵を攻撃していない場合)		/* 2025.02.26 菊池雅道 初期化処理追加 */
	this->bPlayerMeleeStrongEnemyAttackFlg	= false;							// プレイヤーが近距離攻撃(強)で敵を攻撃したかのフラグ							/* 2025.03.03 菊池雅道 初期化処理追加 */
	this->iPlayerMeleeStrongAfterCount		= 0;								// プレイヤーが近距離攻撃(強)で敵を攻撃した後のフレーム数						/* 2025.03.03 菊池雅道 初期化処理追加 */
	this->iMeleeStrongDestroyCount			= 0;								// プレイヤーが近距離攻撃(強)で撃破した敵の数									/* 2025.03.18 菊池雅道 初期化処理追加 */
	this->bPlayerMeleeStrongContinuousFlg	= false;							// プレイヤーが連続で近距離攻撃(強)できるかのフラグ								/* 2025.03.17 菊池雅道 初期化処理追加 */
	this->bPlayerLandingAfterMeleeStrongFlg = false;							// プレイヤーが近距離攻撃(強)後に着地しているかのフラグ							/* 2025.03.23 菊池雅道 初期化処理追加 */
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
	this->iNowHaveKunai						= 0;								// 現在持っているクナイの数
	this->bStartFastMotion					= false;							// 開始時モーション開始フラグ
	this->iFastMotionCount					= 0;								// 開始時モーションカウント
	this->iPlayerComboRunk					= 0;								// 現在のコンボランク

	/* プレイヤーモーション関連 */
	this->iPlayerMotion_Move				= MOTION_ID_MOVE_WAIT;			// プレイヤーモーション(移動系)
	this->iPlayerMotion_Move_Old			= MOTION_ID_MOVE_WALK;			// 変更前プレイヤーモーション(移動系)
	this->fMotionTimer_Move					= 0;							// モーションタイマー(移動系)
	this->fMotionTimer_Move_Old				= 0;							// 変更前モーションタイマー(移動系)
	this->fMotionTimer_Move_End				= 0;							// モーションタイマー(移動系/終了時間)
	this->fMotionTimer_Move_Old_End			= 0;							// 変更前モーションタイマー(移動系/終了時間)
	this->iPlayerMotionAttachIndex_Move		= 0;							// プレイヤーモーション(移動系)のアタッチ番号		
	this->iPlayerMotionAttachIndex_Move_Old	= 0;							// 変更前プレイヤーモーション(移動系)のアタッチ番号
	this->fNowMoveMotionBlendRate			= 0;							// 現在の移動モーションのブレンド率

	this->iPlayerMotion_Attack					= MOTION_ID_ATTACK_NONE;	// プレイヤーモーション(攻撃系)
	this->iPlayerMotion_Attack_Old				= MOTION_ID_ATTACK_NONE;	// 変更前プレイヤーモーション(攻撃系)
	this->fMotionTimer_Attack					= 0;						// モーションタイマー(攻撃系)
	this->fMotionTimer_Attack_Old				= 0;						// 変更前モーションタイマー(攻撃系)
	this->fMotionTimer_Attack_End				= 0;						// モーションタイマー(攻撃系/終了時間)
	this->fMotionTimer_Attack_Old_End			= 0;						// 変更前モーションタイマー(攻撃系/終了時間)
	this->iPlayerMotionAttachIndex_Attack		= 0;						// プレイヤーモーション(攻撃系)のアタッチ番号	
	this->iPlayerMotionAttachIndex_Attack_Old	= 0;						// 変更前プレイヤーモーション(攻撃系)のアタッチ番号
	this->fNowAttackMotionBlendRate				= 0;						// 現在の攻撃モーションのブレンド率

	/* 判定処理用コリジョン */
	this->bMeleeSearchCollisionUseFlg		= false;

	/* 能力値関連(※プレイヤーの装備等によって上下する可能性のあるステータス))*/
	this->fPlayerMoveAcceleration			= 0;	// プレイヤーの移動加速度
	this->fPlayerJumpSpeed					= 0;	// プレイヤージャンプ速度
	this->fPlayerFallAcceleration			= 0;	// プレイヤーの落下加速度
	this->fPlayerMaxFallSpeed				= 0;	// プレイヤーの最大落下速度
	this->iPlayerMaxJumpCount				= 0;	// プレイヤーのジャンプ回数(最大数)
	this->iPlayerJumpCoolTime					= 0;	// プレイヤーのジャンプのクールタイム											/* 2025.03.23 菊池雅道 初期化処理追加 */
	this->fPlayerDodgeSpeed					= 0;	// プレイヤー回避速度															/* 2025.01.10 菊池雅道 初期化処理追加  */
	this->iPlayerDodgeCoolTime					= 0;	// プレイヤーの回避のクールタイム												/* 2025.03.23 菊池雅道 初期化処理追加 */
	this->iPlayerMaxDodgeFlame				= 0;	// プレイヤーの回避最大フレーム数												/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->fPlayerKickWallHorizontalSpeed	= 0;	// プレイヤーの壁キック速度(水平成分)											/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->fPlayerKickWallVerticalSpeed		= 0;	// プレイヤーの壁キック速度(垂直成分)											/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->iPlayerKickWallFlame				= 0;	// プレイヤーの壁キック継続フレーム数											/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->iPlayerKickWallInputMaxFlame		= 0;	// プレイヤーの壁キック入力猶予フレーム数
	this->iPlayerMeleeWeakCoolTime				= 0;	// プレイヤーの近距離攻撃(弱)のクールタイム										/* 2025.03.23 菊池雅道 初期化処理追加 */
	this->iPlayerMelleStrongChangeChargeFrame	= 0;	// プレイヤーの近距離攻撃(強)に切り替わるチャージフレーム数						/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->iPlayerMelleStrongMaxChargeFrame		= 0;	// プレイヤーの近距離攻撃(強)の最大チャージフレーム数							/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->fPlayerMelleStrongMoveScale			= 0;	// プレイヤーの近距離攻撃(強)の移動距離のスケール								/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->fPlayerMelleStrongMoveSpeed			= 0;	// プレイヤーの近距離攻撃(強)の移動速度											/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->iPlayerMeleeStrongContinusMaxFrame	= 0;	// プレイヤーの近距離攻撃(強)の連続最大フレーム数								/* 2025.03.19 菊池雅道 初期化処理追加 */
	this->iPlayerMeleeStrongAirMaxCount			= 0;	// プレイヤーの空中での近距離攻撃(強)回数(※敵を攻撃していない場合の最大数)		/* 2025.02.26 菊池雅道 初期化処理追加 */
	this->fPlayerMeleeStrongNextSearchRange		= 0;	// プレイヤーの近距離攻撃(強)語の索敵範囲										/* 2025.03.23 菊池雅道 初期化処理追加 */
	this->fPlayerRockOnRadius				= 0;	// ロックオン範囲の半径
	this->iStartHaveKunai					= 0;	// 初期状態で持っているクナイの数
	this->iMaxhaveKunai						= 0;	// 最大で持てるクナイの数
	this->iPlayerKunaiCoolTime					= 0;	// クナイのクールタイム															/* 2025.03.23 菊池雅道 初期化処理追加 */
	this->iPlayerMaxHp							= 0;	// プレイヤーの最大HP
	this->iPlayerMaxInvincibleTime				= 0;	// プレイヤーの最大無敵時間
	

	/* プレイヤーバフ関連(エディット周り) */
	this->fAddMoveSpeedUp					= 0;		// 移動速度上昇値(速度/フレーム)
	this->iAddBlood							= 0;		// ブラッド(ゲーム内通貨)の入手量(個)
	this->iAddComboTime						= 0;		// コンボ時間増加値(フレーム)
	this->iAddAttackChargeFrameShortening	= 0;		// チャージ時間短縮値(フレーム)
	this->iAddJumpCount						= 0;		// ジャンプ回数増加値(回)
	this->iAddMeleeStrongAirMaxCount		= 0;		// 空中での近距離攻撃(強)回数増加値(回)
	this->iAddKunaiKeepProbability			= 0;		// クナイ保持確率(%)
	this->iAddBarrier						= 0;		// バリア数(個)
	this->bAddCounter						= false;	// カウンター追加フラグ(有効/無効)
	this->bAddMaxHpOne						= false;	// 最大HP1化フラグ(有効/無効)
	this->iAddKunai							= 0;		// クナイ本数増加値(個)
	this->iAddFallSpeedDown					= 0;		// 落下速度上限値(速度/フレーム)

	/* ステータスデータの読み込み */
	LoadPlayerStatuxData();
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

	/* HP現在値をHP最大値に設定 */
	this->iPlayerNowHp = this->iPlayerMaxHp;

	/* クナイ本数を初期状態でのクナイ本数に設定 */
	this->iNowHaveKunai = this->iStartHaveKunai;
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

// プレイヤーバフ更新
void DataList_PlayerStatus::StatusBuffUpdate()
{
	/* ステータスデータの読み込み */
	LoadPlayerStatuxData();

	/* 現在のエディット情報に応じてプレイヤーバフ関連を更新する */
	/* 全ステータス初期化 */
	this->fAddMoveSpeedUp					= 0;		// 移動速度上昇値(速度/フレーム)
	this->iAddBlood							= 0;		// ブラッド(ゲーム内通貨)の入手量(個)
	this->iAddComboTime						= 0;		// コンボ時間増加値(フレーム)
	this->iAddAttackChargeFrameShortening	= 0;		// チャージ時間短縮値(フレーム)
	this->iAddJumpCount						= 0;		// ジャンプ回数増加値(回)
	this->iAddMeleeStrongAirMaxCount		= 0;		// 空中での近距離攻撃(強)回数増加値(回)
	this->iAddKunaiKeepProbability			= 0;		// クナイ保持確率(%)
	this->iAddBarrier						= 0;		// バリア数(個)
	this->bAddCounter						= false;	// カウンター追加フラグ(有効/無効)
	this->bAddMaxHpOne						= false;	// 最大HP1化フラグ(有効/無効)
	this->iAddKunai							= 0;		// クナイ本数増加値(個)
	this->iAddFallSpeedDown					= 0;		// 落下速度上限値(速度/フレーム)

	/* "ゲーム内リソース管理"を取得 */
	DataList_GameResource* GameResource = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

	/* 現在のエディット情報を取得 */
	for (int i = 0; i < EDIT_MAX; i++)
	{
		/* エディット情報取得 */
		EDIT_DATA EditData = GameResource->stGetNowEditData(i);

		/* エディットの効果量を取得 */
		int iEffectValue = 0;
		for (auto& data : GameResource->GetEffectValueList())
		{
			/* エディットの種類とランクが同じであるか確認 */
			if ((EditData.iEditEffect == data.iEditEffect) && (EditData.iEditRank == data.iEditRank))
			{
				// 同じである場合
				iEffectValue = data.iValue;
				break;
			}
		}
		
		/* エディット情報に応じてプレイヤーバフ関連を更新する */
		switch (EditData.iEditEffect)
		{
			/* 通常 */
			// 移動速度アップ
			case EDIT_EFFECT_NORMAL_MOVE_SPEED_UP:
				/* 効果量分加算する */
				this->fAddMoveSpeedUp += static_cast<float>(iEffectValue);
				break;

			// ブラッド取得量アップ
			case EDIT_EFFECT_NORMAL_GET_BLOOD_UP:
				/* 効果量分加算する */
				this->iAddBlood += iEffectValue;
				break;

			// コンボ継続時間アップ
			case EDIT_EFFECT_NORMAL_COMBO_DURATION_UP:
				/* 効果量分加算する */
				// ※単位を秒→フレームに変換
				this->iAddComboTime += (iEffectValue * 60);
				break;

			// 近接攻撃溜め時間減少
			case EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION:
				/* 効果量分加算する */
				this->iAddAttackChargeFrameShortening += iEffectValue;
				break;

			// ジャンプ回数アップ
			case EDIT_EFFECT_NORMAL_JUMP_COUNT_UP:
				/* 効果量分加算する */
				this->iAddJumpCount += iEffectValue;
				break;

			// 空中居合攻撃回数アップ
			case EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP:
				/* 効果量分加算する */
				this->iAddMeleeStrongAirMaxCount += iEffectValue;
				break;

			// クナイ消費確率無効
			case EDIT_EFFECT_NORMAL_KUNAI_KEEP:
				/* 効果量分加算する */
				this->iAddKunaiKeepProbability += iEffectValue;
				break;

			// バリア回数アップ
			case EDIT_EFFECT_NORMAL_BARIER_COUNT_UP:
				/* 効果量分加算する */
				this->iAddBarrier += iEffectValue;
				break;


			// クナイ本数増加
			case EDIT_EFFECT_NORMAL_GET_KUNAI_UP:
				this->iAddKunai	+= iEffectValue;
				break;

			/* 特殊 */
			// カウンターアクション追加
			case EDIT_EFFECT_SPECIAL_COUNTER:
				/* 有効に設定する */
				this->bAddCounter = true;
				break;

			// クナイワープ化
			case EDIT_EFFECT_KUNAI_WARP:
				/* 有効に設定する */
				this->bAddKunaiWarp = true;
				break;

			// 落下速度低下
			case EDIT_EFFECT_FALL_SPEED_DOWN:
				/* 効果量に設定する */
				// ※加算はしない
				this->iAddFallSpeedDown = iEffectValue;
				break;

			/* 呪い */
			// HP1制限
			case EDIT_EFFECT_CURCE_LIMIT_HP_ONE:
				/* 有効に設定する */
				this->bAddMaxHpOne = true;
				break;
		}
	}
}
