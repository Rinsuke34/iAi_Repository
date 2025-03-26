/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道 移動関連の変数・関数追加 */
/* 2025.01.22 菊池雅道 攻撃関連の変数・関数追加 */
/* 2025.02.05 菊池雅道 ステータス関連の変数・関数修正 */
/* 2025.02.10 菊池雅道 移動関連の変数・関数追加 */
/* 2025.02.11 菊池雅道 攻撃関連の変数・関数追加 */
/* 2025.02.22 菊池雅道 移動関連の変数・関数追加 */
/* 2025.02.26 菊池雅道 攻撃関連の変数・関数追加 */
/* 2025.03.03 菊池雅道 攻撃関連の変数・関数追加 */
/* 2025.03.12 菊池雅道 スローモーション関連の変数・関数追加 */
/* 2025.03.17 菊池雅道 移動・攻撃関連の変数・関数追加 */
/* 2025.03.19 菊池雅道 移動・攻撃関連の変数・関数追加 */
/* 2025.03.23 菊池雅道 移動・攻撃関連の変数・関数追加 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"
#include "PlayerMotionDefine.h"

/* データリスト */
#include "DataList_GameResource.h"

/* 前方参照 */
// ※AppFrameで定義されていないクラスを使用する場合、循環参照対策に実施する。
class Enemy_Basic;

/* プレイヤー状態管理クラスの宣言 */

// プレイヤー状態管理クラス
class DataList_PlayerStatus : public DataListBase
{
	public:
		DataList_PlayerStatus();			// コンストラクタ
		virtual ~DataList_PlayerStatus();	// デストラクタ

		/* jsonファイル関連 */
		void	LoadPlayerStatuxData();			// ステータスデータ読み込み
		void	SavePlayerStatuxData();			// ステータスデータ保存

		/* バフ更新 */
		void	StatusBuffUpdate();				// プレイヤーバフ更新

		/* データ取得 */
		// プレイヤー状態関連
		int		iGetPlayerMoveState()					{ return this->iPlayerMoveState; }					// プレイヤーの移動状態取得										/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		int		iGetPlayerAttackState()					{ return this->iPlayerAttackState; }				// プレイヤーの攻撃状態取得										/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		bool	bGetPlayerLandingFlg()					{ return this->bPlayerLandingFlg; }					// プレイヤーが空中にいるかのフラグ取得
		float	fGetPlayerNowMoveSpeed()				{ return this->fPlayerNowMoveSpeed; }				// プレイヤーの現在の移動速度取得
		float	fGetPlayerAngleX()						{ return this->fPlayerAngleX; }						// プレイヤーのX軸回転量(ラジアン)取得
		float	fGetPlayerTurnSpeed()					{ return this->fPlayerTurnSpeed; }					// プレイヤーの回転速度取得										/* 2025.02.10 菊池雅道 移動関連の関数追加 */
		float	fGetPlayerNowFallSpeed()				{ return this->fPlayerNowFallSpeed; }				// プレイヤーの現在の落下速度取得
		int		iGetPlayerNowJumpCount()				{ return this->iPlayerNowJumpCount; }				// プレイヤーのジャンプ回数(現在数)取得
		int		iGetPlayerNowAttakChargeFlame()			{ return this->iPlayerNowAttakChargeFlame; }		// プレイヤーの現在の攻撃チャージフレーム数取得
		float	fGetPlayerNowMotionCount()				{ return this->fPlayerNowMotionCount; };			// プレイヤーのモーションの現在のカウント
		bool	bGetPlayerJumpingFlag()					{ return this->bPlayerJumpingFlag; }				// プレイヤーがジャンプ中かのフラグを取得							/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		
		VECTOR	vecGetPlayerDodgeDirection()			{ return this->vecPlayerDodgeDirection; }			// プレイヤー回避方向を取得											/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerDodgeWhileJumpingCount()		{ return this->iPlayerDodgeWhileJumpingCount; }		// プレイヤージャンプ中の回避回数を取得								/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerNowDodgeFlame()				{ return this->iPlayerNowDodgeFlame; }				// プレイヤーの現在の回避フレーム数を取得							/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		VECTOR	vecGetPlayerChargeAttakTargetMove()		{ return this->vecPlayerChargeAttakTargetMove; }	// プレイヤー溜め攻撃の移動量を取得									/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */	/* 2025.01.26 駒沢風助 コード修正 */
		int		iGetPlayerMeleeStrongAirMaxCount()		{ return this->iPlayerMeleeStrongAirMaxCount; }		// プレイヤーが空中で近距離攻撃(強)を行う最大数(※敵を攻撃していない場合)を取得		/* 2025.02.26 菊池雅道 攻撃関連の関数追加 */
		int		iGetPlayerMeleeStrongAirCount()			{ return this->iPlayerMeleeStrongAirCount; }		// プレイヤーが空中で近距離攻撃(強)を行った回数を取得								/* 2025.02.26 菊池雅道 攻撃関連の関数追加 */
		bool	bGetPlayerMeleeStrongEnemyAttackFlg()	{ return this->bPlayerMeleeStrongEnemyAttackFlg; }	// プレイヤーが近距離攻撃(強)で敵を攻撃したかのフラグを取得							/* 2025.03.03 菊池雅道 攻撃関連の関数追加 */
		int		iGetPlayerMeleeStrongAfterCount()		{ return this->iPlayerMeleeStrongAfterCount; }		// プレイヤーが近距離攻撃(強)で敵を攻撃した後のフレーム数を取得						/* 2025.03.03 菊池雅道 攻撃関連の関数追加 */
		int		iGetiMeleeStrongDestroyCount()			{ return this->iMeleeStrongDestroyCount; }			// 近距離攻撃(強)で撃破した敵の数を取得												/* 2025.03.18 菊池雅道 攻撃関連の関数追加 */
		bool	bGetPlayerMeleeStrongContinuousFlg()	{ return this->bPlayerMeleeStrongContinuousFlg; }	// プレイヤーが近距離攻撃(強)を連続で行えるかのフラグを取得			/* 2025.03.17 菊池雅道 攻撃関連の関数追加 */
		bool	bGetPlayerLandingAfterMeleeStrongFlg() { return this->bPlayerLandingAfterMeleeStrongFlg; }	// プレイヤーが近距離攻撃(強)後に着地しているかのフラグを取得		/* 2025.03.23 菊池雅道 攻撃関連の関数追加 */
		bool	bGetPlayerWallTouchFlg()				{ return this->bPlayerWallTouchFlg; }				// プレイヤーが壁に接触したかのフラグを取得							/* 2025.03.17 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerAfterWallTouchCount()			{ return this->iPlayerAfterWallTouchCount; }		// プレイヤーが壁に接触した後の経過フレーム数を取得					/* 2025.03.17 菊池雅道 移動関連の関数追加 */
		bool	bGetPlayerKickWallFlg()					{ return this->bPlayerKickWallFlg; }				// プレイヤーが壁を蹴ったかのフラグを取得							/* 2025.02.22 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerAfterKickWallCount()			{ return this->iPlayerAfterKickWallCount; }			// プレイヤーが壁を蹴った後のカウントを取得							/* 2025.02.22 菊池雅道 移動関連の関数追加 */
		bool	bGetPlayerAfterKickWallFlg()			{ return this->bPlayerAfterKickWallFlg; }			// プレイヤーが壁を蹴った後のフラグを取得							/* 2025.02.22 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerMeleeStrongChargeCount()		{ return this->iPlayerMeleeStrongChargeCount; }		// プレイヤーが近距離攻撃(強)状態になってからのチャージフレーム数を取得
		int		iGetPlayerSlowMotionCount()				{ return this->iPlayerSlowMotionCount; }			// プレイヤーのスローモーションカウントを取得						/* 2025.03.12 菊池雅道 スローモーション関連の関数追加 */
		Enemy_Basic* pGetPlayerLockOnEnemy()			{ return this->pLockOnEnemy; }						// ロックオン対象のエネミーを取得
		int		iGetPlayerNowHp()						{ return this->iPlayerNowHp; }						// プレイヤーの現在のHPを取得
		int		iGetPlayerNowInvincibleTime()			{ return this->iPlayerNowInvincibleTime; }			// プレイヤーの現在の残り無敵時間を取得
		int		iGetPlayerComboNowCount()				{ return this->iPlayerComboNowCount; }				// プレイヤーの現在のコンボ数を取得
		int		iGetPlayerComboMaxCount()				{ return this->iPlayerComboMaxCount; }				// プレイヤーの最大コンボ数を取得
		int		iGetPlayerComboDuration()				{ return this->iPlayerComboDuration; }				// プレイヤーのコンボの残り持続時間を取得
		bool	bGetPlayerAimCancelledFlg()				{ return this->bPlayerAimCancelledFlg; }			// 遠距離攻撃(構え)がキャンセルされたかのフラグを取得				/* 2025.02.11 菊池雅道 攻撃関連の関数追加 */
		bool	bGetPlayerDeadFlg()						{ return this->bPlayerDeadFlg; }					// プレイヤー死亡フラグを取得
		int		iGetPlayerDamageCount()					{ return this->iPlayerDamageCount; }				// プレイヤーの被ダメージ数を取得
		bool	bGetFallFlg()							{ return this->bFallFlg; }							// 落下フラグを取得
		int		iGetNowHaveKunai()						{ return this->iNowHaveKunai; }						// 現在持っているクナイの数を取得
		int		iGetPlayerComboRunk()					{ return this->iPlayerComboRunk; }					// 現在のコンボランクを取得

		/* プレイヤーモーション関連 */
		int		iGetPlayerMotion_Move()						{ return this->iPlayerMotion_Move; }					// プレイヤーモーション(移動系)を取得
		float	fGetMotionTimer_Move()						{ return this->fMotionTimer_Move; }						// モーションカウント(移動系)を取得
		float	fGetMotionTimer_Move_End()					{ return this->fMotionTimer_Move_End; }					// モーションカウント(移動系/終了時間)を取得
		int		iGetPlayerMotionAttachIndex_Move()			{ return this->iPlayerMotionAttachIndex_Move; }			// プレイヤーモーション(移動系)のアタッチ番号
		int		iGetPlayerMotion_Move_Old()					{ return this->iPlayerMotion_Move_Old; }				// 変更前プレイヤーモーション(移動系)を取得
		float	fGetMotionTimer_Move_Old()					{ return this->fMotionTimer_Move_Old; }					// 変更前モーションカウント(移動系)を取得
		float	fGetMotionTimer_Move_Old_End()				{ return this->fMotionTimer_Move_Old_End; }				// 変更前モーションカウント(移動系/終了時間)を取得
		int		iGetPlayerMotionAttachIndex_Move_Old()		{ return this->iPlayerMotionAttachIndex_Move_Old; }		// 変更前プレイヤーモーション(移動系)のアタッチ番号
		float	fGetNowMoveMotionBlendRate()				{ return this->fNowMoveMotionBlendRate; };				// 現在の移動モーションのブレンド率
		int		iGetPlayerMotion_Attack()					{ return this->iPlayerMotion_Attack; }					// プレイヤーモーション(攻撃系)を取得
		float	fGetMotionTimer_Attack()					{ return this->fMotionTimer_Attack; }					// モーションカウント(攻撃系)を取得
		float	fGetMotionTimer_Attack_End()				{ return this->fMotionTimer_Attack_End; }				// モーションカウント(攻撃系/終了時間)を取得
		int		iGetPlayerMotionAttachIndex_Attack()		{ return this->iPlayerMotionAttachIndex_Attack; }		// プレイヤーモーション(攻撃系)のアタッチ番号		
		int		iGetPlayerMotion_Attack_Old()				{ return this->iPlayerMotion_Attack_Old; }				// 変更前プレイヤーモーション(攻撃系)を取得
		float	fGetMotionTimer_Attack_Old()				{ return this->fMotionTimer_Attack_Old; }				// 変更前モーションカウント(攻撃系)を取得
		float	fGetMotionTimer_Attack_Old_End()			{ return this->fMotionTimer_Attack_Old_End; }			// 変更前モーションカウント(攻撃系/終了時間)を取得
		int		iGetPlayerMotionAttachIndex_Attack_Old()	{ return this->iPlayerMotionAttachIndex_Attack_Old; }	// 変更前プレイヤーモーション(攻撃系)のアタッチ番号
		float	fGetNowAttackMotionBlendRate()				{ return this->fNowAttackMotionBlendRate; }				// 現在の攻撃モーションのブレンド率
		bool	bGetStartFastMotion()						{ return this->bStartFastMotion; }						// 開始時モーション開始フラグ
		int		iGetFastMotionCount()						{ return this->iFastMotionCount; }						// 開始時モーションカウント

		/* 判定処理用コリジョン */
		COLLISION_CAPSULE	stGetMeleeSearchCollision()			{ return this->stMeleeSearchCollision; };		// 近接攻撃(強)のロックオン範囲コリジョンを取得
		bool				bGetMeleeSearchCollisionUseFlg()	{ return this->bMeleeSearchCollisionUseFlg; };	// 近接攻撃(強)のロックオン範囲コリジョン使用フラグを取得

		// 能力値関連(※調整を行えるステータス)
		float	fGetPlayerMoveAcceleration()	{ return this->fPlayerMoveAcceleration; }	// プレイヤーの移動加速度取得
		float	fGetPlayerJumpSpeed()			{ return this->fPlayerJumpSpeed; }			// プレイヤーのジャンプ速度取得
		float	fGetPlayerFallAcceleration()	{ return this->fPlayerFallAcceleration; }	// プレイヤーの落下加速度取得
		float	fGetPlayerMaxFallSpeed()		{ return this->fPlayerMaxFallSpeed; }		// プレイヤーの最大落下速度取得	
		int		iGetPlayerMaxJumpCount()		{ return this->iPlayerMaxJumpCount; }		// プレイヤーのジャンプ回数(最大数)取得
		int		iGetPlayerJumpCoolTime()		{ return this->iPlayerJumpCoolTime; }		// プレイヤーのジャンプクールタイム取得								/* 2025.03.23 菊池雅道 移動関連の関数追加 */
		float	fGetPlayerDodgeSpeed()			{ return this->fPlayerDodgeSpeed; }			// プレイヤー回避速度を取得											/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerMaxDodgeFlame()		{ return this->iPlayerMaxDodgeFlame; }		// プレイヤーの最大回避フレーム数を取得								/* 2025.03.19 菊池雅道 移動関連の変数追加 */
		int		iGetPlayerDodgeCoolTime()		{ return this->iPlayerDodgeCoolTime; }		// プレイヤーの回避クールタイムを取得								/* 2025.03.23 菊池雅道 移動関連の変数追加 */
		float	fGetPlayerKickWallHorizontalSpeed()			{ return this->fPlayerKickWallHorizontalSpeed; }			// プレイヤーの壁キック速度(水平成分)を取得								/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		float	fGetPlayerKickWallVerticalSpeed()			{ return this->fPlayerKickWallVerticalSpeed; }				// プレイヤーの壁キック速度(垂直成分)を取得								/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerKickWallFlame()					{ return this->iPlayerKickWallFlame; }						// プレイヤーの壁キック継続フレーム数を取得								/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerKickWallInputMaxFlame()			{ return this->iPlayerKickWallInputMaxFlame; }				// プレイヤーの壁キック入力猶予フレーム数を取得							/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerMeleeWeakCoolTime()				{ return this->iPlayerMeleeWeakCoolTime; }		// プレイヤーの近距離攻撃(弱)クールタイム取得							/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		int		iGetPlayerMelleStrongChangeChargeFrame()	{ return this->iPlayerMelleStrongChangeChargeFrame; }		// プレイヤーの近距離攻撃(強)状態になるチャージフレーム数を取得			/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		int		iGetPlayerMelleStrongMaxChargeFrame()		{ return this->iPlayerMelleStrongMaxChargeFrame; }			// プレイヤーの近距離攻撃(強)の最大チャージフレーム数を取得				/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		float	fGetPlayerMelleStrongMoveScale()			{ return this->fPlayerMelleStrongMoveScale; }				// プレイヤーの近距離攻撃(強)の移動距離のスケールを取得					/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		float	fGetPlayerMeleeStrongMoveSpeed()			{ return this->fPlayerMelleStrongMoveSpeed; }				// プレイヤーの近距離攻撃(強)の移動速度を取得							/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		int		iGetPlayerMeleeStrongContinusMaxFrame()		{ return this->iPlayerMeleeStrongContinusMaxFrame; }		// プレイヤーの近距離攻撃(強)で連続攻撃できる最大フレーム数を取得		/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		float	fGetPlayerMeleeStrongNextSearchRange()		{ return this->fPlayerMeleeStrongNextSearchRange; }			// プレイヤーの近距離攻撃(強)後の索敵範囲を取得							/* 2025.03.23 菊池雅道 攻撃関連の関数追加 */
		float	fGetPlayerRockOnRadius()		{ return this->fPlayerRockOnRadius; }		// ロックオン範囲の半径を設定
		int		iGetStartHaveKunai()			{ return this->iStartHaveKunai; }			// 初期状態で持っているクナイの数
		int		iGetMaxHaveKunai()				{ return this->iMaxhaveKunai; }				// 最大で持てるクナイの数
		int		iGetPlayerKunaiCoolTime()		{ return this->iPlayerKunaiCoolTime; }		// クナイのクールタイムを取得																		/* 2025.03.23 菊池雅道 攻撃関連の関数追加 */
		int		iGetPlayerMaxHp()				{ return this->iPlayerMaxHp; }				// プレイヤーの最大HP取得
		int		iGetPlayerMaxInvincibleTime()	{ return this->iPlayerMaxInvincibleTime; }	// プレイヤーの最大無敵時間取得

		/* プレイヤーバフ関連(エディット周り) */
		float	fGetAddMoveSpeedUp()					{ return this->fAddMoveSpeedUp; }					// 移動速度上昇値(速度/フレーム)
		int		iGetAddBlood()							{ return this->iAddBlood; }							// ブラッド(ゲーム内通貨)の入手量(個)
		int		iGetAddComboTime()						{ return this->iAddComboTime; }						// コンボ時間増加値(フレーム)
		int		iGetAddAttackChargeFrameShortening()	{ return this->iAddAttackChargeFrameShortening; }	// チャージ時間短縮値(フレーム)
		int		iGetAddJumpCount()						{ return this->iAddJumpCount; }						// ジャンプ回数増加値(回)
		int		iGetAddMeleeStrongAirMaxCount()			{ return this->iAddMeleeStrongAirMaxCount; }		// 空中での近距離攻撃(強)回数増加値(回)
		int		iGetAddKunaiKeepProbability()			{ return this->iAddKunaiKeepProbability; }			// クナイ保持確率(%)
		int		iGetAddBarrier()						{ return this->iAddBarrier; }						// バリア数(個)
		bool	bGetAddCounter()						{ return this->bAddCounter; }						// カウンター追加フラグ(有効/無効)
		bool	bGetKunaiExplosion()					{ return this->bAddKunaiExplosion; }				// クナイ爆発化フラグ(有効/無効)
		bool	bGetAddMaxHpOne()						{ return this->bAddMaxHpOne; }						// 最大HP1化フラグ(有効/無効)
		int		iGetAddKunai()							{ return this->iAddKunai; }							// クナイ追加数(個)

		/* データ設定 */
		// プレイヤー状態関連
		void	SetPlayerMoveState(int iPlayerMoveState)									{ this->iPlayerMoveState					= iPlayerMoveState; }					// プレイヤーの移動状態設定					/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		void	SetPlayerAttackState(int iPlayerAttackState)								{ this->iPlayerAttackState					= iPlayerAttackState; }					// プレイヤーの攻撃状態設定					/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		void	SetPlayerLanding(bool bPlayerLanding)										{ this->bPlayerLandingFlg					= bPlayerLanding; }						// プレイヤーが空中にいるかのフラグ設定
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)							{ this->fPlayerNowMoveSpeed					= fPlayerNowMoveSpeed; }				// プレイヤーの現在の移動速度設定
		void	SetPlayerAngleX(float fPlayerAngleX)										{ this->fPlayerAngleX						= fPlayerAngleX; }						// プレイヤーのX軸回転量(ラジアン)取得
		void	SetPlayerTurnSpeed(float fPlayerTurnSpeed)									{ this->fPlayerTurnSpeed					= fPlayerTurnSpeed; }					// プレイヤーの回転速度設定					/* 2025.02.10 菊池雅道 移動関連の関数追加 */
		void	SetplayerJumpSpeed(float fPlayerJumpSpeed)									{ this->fPlayerJumpSpeed					= fPlayerJumpSpeed; }					// プレイヤーのジャンプ速度設定
		void	SetPlayerNowFallSpeed(float fPlayerNowFallSpeed)							{ this->fPlayerNowFallSpeed					= fPlayerNowFallSpeed; }				// プレイヤーの現在の落下速度設定
		void	SetPlayerNowJumpCount(int iPlayerNowJumpCount)								{ this->iPlayerNowJumpCount					= iPlayerNowJumpCount; }				// プレイヤーのジャンプ回数(現在数)設定
		void	SetPlayerNowAttakChargeFlame(int iPlayerNowAttakChargeFlame)				{ this->iPlayerNowAttakChargeFlame			= iPlayerNowAttakChargeFlame; }			// プレイヤーの現在の攻撃チャージフレーム数設定
		void	SetPlayerChargeAttakTargetMove(VECTOR vecPlayerChargeAttakTargetMove)		{ this->vecPlayerChargeAttakTargetMove		= vecPlayerChargeAttakTargetMove; }		// プレイヤー溜め攻撃の移動量を設定															/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */	/* 2025.01.26 駒沢風助 コード修正 */
		void	SetPlayerMeleeStrongChargeCount(int iPlayerMeleeStrongChargeCount)			{ this->iPlayerMeleeStrongChargeCount		= iPlayerMeleeStrongChargeCount; }		// プレイヤーが近距離攻撃(強)状態になってからのチャージフレーム数を設定
		void	SetPlayerMeleeStrongAirCount(int iPlayerMeleeStrongAirCount)				{ this->iPlayerMeleeStrongAirCount			= iPlayerMeleeStrongAirCount; }			// プレイヤーが空中で近距離攻撃(強)を行った回数を設定		/* 2025.02.26 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMeleeStrongEnemyAttackFlg(bool bPlayerMeleeStrongEnemyAttackFlg)	{ this->bPlayerMeleeStrongEnemyAttackFlg	= bPlayerMeleeStrongEnemyAttackFlg; }	// プレイヤーが近距離攻撃(強)でエネミーを攻撃したかのフラグを設定		/* 2025.03.03 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMeleeStrongAfterCount(int iPlayerMeleeStrongAfterCount)			{ this->iPlayerMeleeStrongAfterCount		= iPlayerMeleeStrongAfterCount; }		// プレイヤーが近距離攻撃(強)でエネミーを攻撃した後のフレーム数を設定	/* 2025.03.03 菊池雅道 攻撃関連の関数追加 */
		void	SetMeleeStrongDestroyCount(int iMeleeStrongDestroyCount)					{ this->iMeleeStrongDestroyCount = iMeleeStrongDestroyCount; }						// 近距離攻撃(強)で撃破した敵の数を設定									/* 2025.03.18 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMeleeStrongContinuousFlg(bool bPlayerMeleeStrongContinuousFlg)		{ this->bPlayerMeleeStrongContinuousFlg		= bPlayerMeleeStrongContinuousFlg; }	// プレイヤーが近距離攻撃(強)を連続で行えるかのフラグを設定				/* 2025.03.17 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerLandingAfterMeleeStrongFlg(bool bPlayerLandingAfterMeleeStrongFlg) { this->bPlayerLandingAfterMeleeStrongFlg = bPlayerLandingAfterMeleeStrongFlg; }	// プレイヤーが近距離攻撃(強)後に着地しているかのフラグを設定			/* 2025.03.23 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerSlowMotionCount(int iPlayerSlowMotionCount)						{ this->iPlayerSlowMotionCount				= iPlayerSlowMotionCount; }				// プレイヤーのスローモーションのカウントを設定									/* 2025.03.12 菊池雅道 スローモーション関連の関数追加 */
		void	SetPlayerNowMotionCount(float fPlayerNowMotionCount)						{ this->fPlayerNowMotionCount				= fPlayerNowMotionCount; };				// プレイヤーのモーションの現在のカウント
		void	SetPlayerJumpingFlag(bool bPlayerJumpingFlag)								{ this->bPlayerJumpingFlag					= bPlayerJumpingFlag; }					// プレイヤーがジャンプ中かのフラグを設定	/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerNowDodgeFlame(int iPlayerNowDodgeFlame)							{ this->iPlayerNowDodgeFlame				= iPlayerNowDodgeFlame; }				// プレイヤーの現在の回避時間を設定			/* 2025.01.10 菊池雅道 移動関連の関数追加 */		
		void	SetPlayerDodgeDirection(VECTOR vecPlayerDodgeDirection)						{ this->vecPlayerDodgeDirection				= vecPlayerDodgeDirection; }			// プレイヤー回避方向を設定					/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerDodgeWhileJumpingCount(int iPlayerDodgeWhileJumpingCount)			{ this->iPlayerDodgeWhileJumpingCount		= iPlayerDodgeWhileJumpingCount; }		// プレイヤージャンプ中の回避回数を設定		/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerWallTouchFlg(bool bPlayerWallTouchFlg)								{ this->bPlayerWallTouchFlg					= bPlayerWallTouchFlg; }				// プレイヤーが壁に接触したかのフラグを設定								/* 2025.03.17 菊池雅道 移動関連の関数追加 */
		void	SetPlayerAfterWallTouchCount(int iPlayerAfterWallTouchCount)				{ this->iPlayerAfterWallTouchCount = iPlayerAfterWallTouchCount; }					// プレイヤーが壁に接触した後の経過フレーム数を設定						/* 2025.03.17 菊池雅道 移動関連の関数追加 */
		void	SetPlayerKickWallFlg(bool bPlayerKickWallFlg)								{ this->bPlayerKickWallFlg					= bPlayerKickWallFlg; }					// プレイヤーが壁を蹴ったかのフラグを設定	/* 2025.02.22 菊池雅道 移動関連の関数追加 */
		void	SetPlayerAfterKickWallCount(int iPlayerAfterKickWallCount)					{ this->iPlayerAfterKickWallCount			= iPlayerAfterKickWallCount; }			// プレイヤーが壁を蹴った後のカウントを設定	/* 2025.02.22 菊池雅道 移動関連の関数追加 */
		void	SetPlayerAfterKickWallFlg(bool bPlayerAfterKickWallFlg)						{ this->bPlayerAfterKickWallFlg				= bPlayerAfterKickWallFlg; }			// プレイヤーが壁を蹴った後のフラグを設定	/* 2025.02.22 菊池雅道 移動関連の関数追加 */
		void	SetPlayerLockOnEnemy(Enemy_Basic* pLockOnEnemy)								{ this->pLockOnEnemy						= pLockOnEnemy; };						// ロックオン対象のエネミーを設定
		void	SetPlayerNowHp(int iPlayerNowHp)											{ this->iPlayerNowHp						= iPlayerNowHp; }						// プレイヤーの現在のHPを設定
		void	SetPlayerNowInvincibleTime(int iPlayerNowInvincibleTime)					{ this->iPlayerNowInvincibleTime			= iPlayerNowInvincibleTime; }			// プレイヤーの現在の残り無敵時間を設定
		void	SetPlayerComboNowCount(int iPlayerComboNowCount)							{ this->iPlayerComboNowCount				= iPlayerComboNowCount; }				// プレイヤーの現在のコンボ数を設定
		void	SetPlayerComboMaxCount(int iPlayerComboMaxCount)							{ this->iPlayerComboMaxCount				= iPlayerComboMaxCount; }				// プレイヤーの最大コンボ数を設定
		void	SetPlayerComboDuration(int iPlayerComboDuration)							{ this->iPlayerComboDuration				= iPlayerComboDuration; }				// プレイヤーのコンボの残り持続時間を設定
		void	SetPlayerAimCancelledFlg(bool bPlayerAimCancelledFlg)						{ this->bPlayerAimCancelledFlg				= bPlayerAimCancelledFlg; }				// 遠距離攻撃(構え)がキャンセルされたかのフラグを設定	/* 2025.02.11 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerDeadFlg(bool bPlayerDeadFlg)										{ this->bPlayerDeadFlg						= bPlayerDeadFlg; }						// プレイヤー死亡フラグ
		void	SetPlayerDamageCount(int iPlayerDamageCount)								{ this->iPlayerDamageCount					= iPlayerDamageCount; }					// プレイヤーの被ダメージ数を設定
		void	SetFallFlg(bool bFallFlg)													{ this->bFallFlg							= bFallFlg; }							// 落下フラグを設定
		void	SetNowHaveKunai(int iNowHaveKunai)											{ this->iNowHaveKunai						= iNowHaveKunai; }						// 現在持っているクナイの数を設定
		void	SetPlayerComboRunk(int iPlayerComboRunk)									{ this->iPlayerComboRunk					= iPlayerComboRunk; }					// 現在のコンボランクを設定

		/* プレイヤーモーション関連 */
		void	SetPlayerMotion_Move(int iPlayerMotion_Move)								{ this->iPlayerMotion_Move					= iPlayerMotion_Move; };						// プレイヤーモーション(移動系)を設定
		void	SetMotionCount_Move(float fMotionCount_Move)								{ this->fMotionTimer_Move					= fMotionCount_Move; };							// モーションカウント(移動系)
		void	SetMotionCount_Move_End(float fMotionCount_Move_End)						{ this->fMotionTimer_Move_End				= fMotionCount_Move_End; };						// モーションカウント(移動系/終了時間)を設定
		void	SetPlayerMotionAttachIndex_Move(int iPlayerMotionAttachIndex_Move)			{ this->iPlayerMotionAttachIndex_Move		= iPlayerMotionAttachIndex_Move; }				// プレイヤーモーション(移動系)のアタッチ番号
		void	SetPlayerMotion_Move_Old(int iPlayerMotion_Move_Old)						{ this->iPlayerMotion_Move_Old				= iPlayerMotion_Move_Old; };					// 変更前プレイヤーモーション(移動系)を設定
		void	SetMotionCount_Move_Old(float fMotionCount_Move_Old)						{ this->fMotionTimer_Move_Old				= fMotionCount_Move_Old; };						// 変更前モーションカウント(移動系)
		void	SetMotionCount_Move_Old_End(float fMotionCount_Move_Old_End)				{ this->fMotionTimer_Move_Old_End			= fMotionCount_Move_Old_End; };					// 変更前モーションカウント(移動系/終了時間)を設定
		void	SetPlayerMotionAttachIndex_Move_Old(int iPlayerMotionAttachIndex_Move_Old)	{ this->iPlayerMotionAttachIndex_Move_Old	= iPlayerMotionAttachIndex_Move_Old; }			// 変更前プレイヤーモーション(移動系)のアタッチ番号
		void	SetNowMoveMotionBlendRate(float fNowMoveMotionBlendRate)					{ this->fNowMoveMotionBlendRate				= fNowMoveMotionBlendRate; }					// 現在の移動モーションのブレンド率
		void	SetPlayerMotion_Attack(int iPlayerMotion_Attack)							{ this->iPlayerMotion_Attack				= iPlayerMotion_Attack; };						// プレイヤーモーション(攻撃系)を設定
		void	SetMotionCount_Attack(float fMotionCount_Attack)							{ this->fMotionTimer_Attack					= fMotionCount_Attack; };						// モーションカウント(攻撃系)を設定
		void	SetMotionCount_Attack_End(float fMotionCount_Attack_End)					{ this->fMotionTimer_Attack_End				= fMotionCount_Attack_End; };					// モーションカウント(攻撃系/終了時間)を設定
		void	SetPlayerMotionAttachIndex_Attack(int iPlayerMotionAttachIndex_Attack)		{ this->iPlayerMotionAttachIndex_Attack		= iPlayerMotionAttachIndex_Attack; }			// プレイヤーモーション(攻撃系)のアタッチ番号
		void	SetPlayerMotion_Attack_Old(int iPlayerMotion_Attack_Old)						{ this->iPlayerMotion_Attack_Old			= iPlayerMotion_Attack_Old; };				// 変更前プレイヤーモーション(攻撃系)を設定
		void	SetMotionCount_Attack_Old(float fMotionCount_Attack_Old)						{ this->fMotionTimer_Attack_Old				= fMotionCount_Attack_Old; };				// 変更前モーションカウント(攻撃系)を設定
		void	SetMotionCount_Attack_Old_End(float fMotionCount_Attack_Old_End)				{ this->fMotionTimer_Attack_Old_End			= fMotionCount_Attack_Old_End; };			// 変更前モーションカウント(攻撃系/終了時間)を設定		
		void	SetPlayerMotionAttachIndex_Attack_Old(int iPlayerMotionAttachIndex_Attack_Old)	{ this->iPlayerMotionAttachIndex_Attack_Old	= iPlayerMotionAttachIndex_Attack_Old; }	// 変更前プレイヤーモーション(攻撃系)のアタッチ番号を設定
		void	SetNowAttackMotionBlendRate(float fNowAttackMotionBlendRate)					{ this->fNowAttackMotionBlendRate			= fNowAttackMotionBlendRate; }				// 現在の攻撃モーションのブレンド率を設定
		void	SetStartFastMotion(bool bStartFastMotion)										{ this->bStartFastMotion					= bStartFastMotion; }						// 開始時モーション開始フラグを設定
		void	SetFastMotionCount(int iFastMotionCount)										{ this->iFastMotionCount					= iFastMotionCount; }						// 開始時モーションカウントを設定

		/* 判定処理用コリジョン */
		void	SetMeleeSearchCollision(COLLISION_CAPSULE stMeleeSearchCollision)				{ this->stMeleeSearchCollision			= stMeleeSearchCollision; }						// 近接攻撃(強)のロックオン範囲コリジョンを設定
		void	SetMeleeSearchCollisionUseFlg(bool bMeleeSearchCollisionUseFlg)					{ this->bMeleeSearchCollisionUseFlg		= bMeleeSearchCollisionUseFlg; }				// 近接攻撃(強)のロックオン範囲コリジョン使用フラグを設定

		// 能力値関連(※調整を行えるステータス)
		void	SetPlayerMoveAcceleration(float fPlayerMoveAcceleration)						{ this->fPlayerMoveAcceleration			= fPlayerMoveAcceleration; }		// プレイヤーの移動加速度設定
		void	SetPlayerFallAcceleration(float fPlayerFallAcceleration)						{ this->fPlayerFallAcceleration			= fPlayerFallAcceleration; }		// プレイヤーの落下加速度設定
		void	SetPlayerJumpSpeed(float fPlayerJumpSpeed)										{ this->fPlayerJumpSpeed				= fPlayerJumpSpeed; }				// プレイヤーのジャンプ速度設定
		void	SetPlayerMaxFallSpeed(float fPlayerMaxFallSpeed)								{ this->fPlayerMaxFallSpeed				= fPlayerMaxFallSpeed; }			// プレイヤーの最大落下速度設定
		void	SetPlayerMaxJumpCount(int iPlayerMaxJumpCount)									{ this->iPlayerMaxJumpCount				= iPlayerMaxJumpCount; }			// プレイヤーのジャンプ回数(最大数)設定
		void	SetPlayerJumpCoolTime(int iPlayerJumpCoolTime)									{ this->iPlayerJumpCoolTime				= iPlayerJumpCoolTime; }			// プレイヤーのジャンプクールタイムを設定													/* 2025.03.23 菊池雅道 移動関連の関数追加 */
		void	SetPlayerDodgeSpeed(float fPlayerDodgeSpeed)									{ this->fPlayerDodgeSpeed				= fPlayerDodgeSpeed; }				// プレイヤー回避速度を設定																	/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerDodgeCoolTime(int iPlayerDodgeCoolTime)								{ this->iPlayerDodgeCoolTime			= iPlayerDodgeCoolTime; }			// プレイヤー回避クールタイムを設定															/* 2025.03.23 菊池雅道 移動関連の関数追加 */
		void	SetPlayerMaxDodgeFlame(int iPlayerMaxDodgeFlame)								{ this->iPlayerMaxDodgeFlame			= iPlayerMaxDodgeFlame; }			// プレイヤーの最大回避フレーム数を設定														/* 2025.03.19 菊池雅道 移動関連の変数・関数追加 */
		void	SetPlayerKickWallHorizontalSpeed(float fPlayerKickWallHorizontalSpeed)			{ this->fPlayerKickWallHorizontalSpeed	= fPlayerKickWallHorizontalSpeed; }	// プレイヤーの壁キック速度(水平成分)を設定													/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		void	SetPlayerKickWallVerticalSpeed(float fPlayerKickWallVerticalSpeed)				{ this->fPlayerKickWallVerticalSpeed	= fPlayerKickWallVerticalSpeed; }	// プレイヤーの壁キック速度(垂直成分)を設定													/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		void	SetPlayerKickWallFlame(int iPlayerKickWallFlame)								{ this->iPlayerKickWallFlame			= iPlayerKickWallFlame; }			// プレイヤーの壁キック継続フレーム数を設定													/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		void	SetPlyerKickWallInputMaxFrame(int iPlayerKickWallInputMaxFrame)					{ this->iPlayerKickWallInputMaxFlame	= iPlayerKickWallInputMaxFrame; }	// プレイヤーの壁キックの入力猶予フレーム数を設定											/* 2025.03.19 菊池雅道 移動関連の関数追加 */
		void	SetPlayerMeleeWeakCoolTime(int iPlayerMeleeWeakCoolTime)						{ this->iPlayerMeleeWeakCoolTime = iPlayerMeleeWeakCoolTime; }		// プレイヤーの近距離攻撃(弱)のクールタイムを設定																/* 2025.03.23 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMelleStrongChangeChargeFrame(int iPlayerMelleStrongChangeChargeFrame)	{ this->iPlayerMelleStrongChangeChargeFrame		= iPlayerMelleStrongChangeChargeFrame; }		// プレイヤーの近距離攻撃(強)に切り替わるチャージフレーム数を設定					/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMelleStrongMaxChargeFrame(int iPlayerMelleStrongMaxChargeFrame)		{ this->iPlayerMelleStrongMaxChargeFrame		= iPlayerMelleStrongMaxChargeFrame; }			// プレイヤーの近距離攻撃(強)の最大チャージフレーム数を設定							/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMelleStrongMoveScale(float fPlayerMelleStrongMoveScale)				{ this->fPlayerMelleStrongMoveScale				= fPlayerMelleStrongMoveScale; }				// プレイヤーの近距離攻撃(強)の移動距離のスケールを設定								/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMeleeStrongMoveSpeed(float fPlayerMeleeStrongMoveSpeed)				{ this->fPlayerMelleStrongMoveSpeed				= fPlayerMeleeStrongMoveSpeed; }				// プレイヤー近距離攻撃(強)の移動速度を設定											/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMeleeStrongContinusMaxFrame(int iPlayerMeleeStrongContinusMaxFrame)	{ this->iPlayerMeleeStrongContinusMaxFrame		= iPlayerMeleeStrongContinusMaxFrame; }			// プレイヤー近距離攻撃(強)で連続攻撃できる最大フレーム数を設定						/* 2025.03.19 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMeleeStrongAirMaxCount(int iPlayerMeleeStrongAirMaxCount)				{ this->iPlayerMeleeStrongAirMaxCount	= iPlayerMeleeStrongAirMaxCount; }				// プレイヤーが空中で近距離攻撃(強)を行う最大数(※敵を攻撃していない場合)を設定				/* 2025.02.26 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMeleeStrongNextSearchRange(float fPlayerMeleeStrongNextSearchRange)	{ this->fPlayerMeleeStrongNextSearchRange	= fPlayerMeleeStrongNextSearchRange; }				// プレイヤーが近距離攻撃(強)を行った後の索敵範囲を設定								/* 2025.03.23 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerRockOnRadius(float fPlayerRockOnRadius)								{ this->fPlayerRockOnRadius				= fPlayerRockOnRadius; }			// ロックオン範囲の半径を設定
		void	SetStartHaveKunai(int iStartHaveKunai)											{ this->iStartHaveKunai					= iStartHaveKunai; }				// 初期状態で持っているクナイの数
		void	SetMaxhaveKunai(int iMaxhaveKunai)												{ this->iMaxhaveKunai					= iMaxhaveKunai; }					// 最大で持てるクナイの数
		void	SetPlayerKunaiCoolTime(int iPlayerKunaiCoolTime)								{ this->iPlayerKunaiCoolTime				= iPlayerKunaiCoolTime; }							// クナイのクールタイムを設定														/* 2025.03.23 菊池雅道 攻撃関連の関数追加 */
		void	SetPlayerMaxHp(int iPlayerMaxHp) { this->iPlayerMaxHp = iPlayerMaxHp; }					// プレイヤーの最大HP設定
		void	SetPlayerMaxInvincibleTime(int iPlayerMaxInvincibleTime) { this->iPlayerMaxInvincibleTime = iPlayerMaxInvincibleTime; }		// プレイヤーの最大無敵時間設定
		
		/* プレイヤーバフ関連(エディット周り) */
		void	SetAddMoveSpeedUp(float fAddMoveSpeedUp)										{ this->fAddMoveSpeedUp					= fAddMoveSpeedUp; }					// 移動速度上昇値(速度/フレーム)
		void	SetAddBlood(int iAddBlood)														{ this->iAddBlood						= iAddBlood; }							// ブラッド(ゲーム内通貨)の入手量(個)
		void	SetAddComboTime(int iAddComboTime)												{ this->iAddComboTime					= iAddComboTime; }						// コンボ時間増加値(フレーム)
		void	SetAddAttackChargeFrameShortening(int iAddAttackChargeFrameShortening)			{ this->iAddAttackChargeFrameShortening	= iAddAttackChargeFrameShortening; }	// チャージ時間短縮値(フレーム)
		void	SetAddJumpCount(int iAddJumpCount)												{ this->iAddJumpCount					= iAddJumpCount; }						// ジャンプ回数増加値(回)
		void	SetAddMeleeStrongAirMaxCount(int iAddMeleeStrongAirMaxCount)					{ this->iAddMeleeStrongAirMaxCount		= iAddMeleeStrongAirMaxCount; }			// 空中での近距離攻撃(強)回数増加値(回)
		void	SetAddKunaiKeepProbability(int iAddKunaiKeepProbability)						{ this->iAddKunaiKeepProbability		= iAddKunaiKeepProbability; }			// クナイ保持確率(%)
		void	SetAddBarrier(int iAddBarrier)													{ this->iAddBarrier						= iAddBarrier; }						// バリア数(個)
		void	SetAddCounter(bool bAddCounter)													{ this->bAddCounter						= bAddCounter; }						// カウンター追加フラグ(有効/無効)
		void	SetKunaiExplosion(bool bKunaiExplosion)											{ this->bAddKunaiExplosion				= bKunaiExplosion; };					// クナイ爆発化フラグ(有効/無効)
		void	SetAddMaxHpOne(bool bAddMaxHpOne)												{ this->bAddMaxHpOne					= bAddMaxHpOne; }						// 最大HP1化フラグ(有効/無効)
		void	SetAddKunai(int iAddKunai)														{ this->iAddKunai						= iAddKunai; }							// クナイ追加数(個)

	private:
		/* プレイヤー状態関連 */
		int		iPlayerMoveState;					// プレイヤーの移動状態(アクション)												/* 2025.02.05 菊池雅道 ステータス関連の変数修正 */
		int		iPlayerAttackState;					// プレイヤーの攻撃状態(アクション)												/* 2025.02.05 菊池雅道 ステータス関連の変数修正 */
		bool	bPlayerLandingFlg;					// プレイヤーが着地しているかのフラグ
		float	fPlayerNowMoveSpeed;				// プレイヤーの現在の移動速度
		float	fPlayerAngleX;						// プレイヤーのX軸回転量(ラジアン)
		float	fPlayerTurnSpeed;					// プレイヤーの方向転換の速度（範囲：0.0?1.0）									/* 2025.02.10 菊池雅道 移動関連の変数追加 */
		float	fPlayerNowFallSpeed;				// プレイヤーの現在の落下速度
		int		iPlayerNowJumpCount;				// プレイヤーのジャンプ回数(現在数)
		float	fPlayerNowMotionCount;				// プレイヤーのモーションの現在のカウント
		bool	bPlayerJumpingFlag;					// プレイヤーがジャンプ中かのフラグ												/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		int		iPlayerNowDodgeFlame;				// プレイヤーの現在の回避フレーム数												/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		VECTOR	vecPlayerDodgeDirection;			// プレイヤー回避方向															/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		int		iPlayerDodgeWhileJumpingCount;		// プレイヤージャンプ中の回避回数												/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		bool	bPlayerWallTouchFlg;				// プレイヤーが壁に接触したかのフラグ											/* 2025.03.17 菊池雅道 移動関連の変数追加 */
		int		iPlayerAfterWallTouchCount;			// プレイヤーが壁に接触してからの経過フレーム数									/* 2025.03.17 菊池雅道 移動関連の変数追加 */
		bool	bPlayerKickWallFlg;					// プレイヤーが壁を蹴ったかのフラグ												/* 2025.02.22 菊池雅道 移動関連の変数追加 */
		int		iPlayerAfterKickWallCount;			// プレイヤーが壁を蹴ってからの経過フレーム数									/* 2025.02.22 菊池雅道 移動関連の変数追加 */
		bool	bPlayerAfterKickWallFlg;			// プレイヤーが壁を蹴った後の状態かのフラグ										/* 2025.02.22 菊池雅道 移動関連の変数追加 */
		VECTOR	vecPlayerChargeAttakTargetMove;		// 近接攻撃(強)による移動量														/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */	/* 2025.01.26 駒沢風助 コード修正 */
		int		iPlayerNowAttakChargeFlame;			// 現在のプレイヤー溜め攻撃チャージフレーム数									/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */
		int		iPlayerMeleeStrongChargeCount;		// プレイヤーが近距離攻撃(強)状態になってからのチャージフレーム数
		int		iPlayerMeleeStrongAirCount;			// プレイヤーが空中で近距離攻撃(強)を行った回数(※敵を攻撃していない場合)		/* 2025.02.26 菊池雅道 攻撃関連の変数追加 */
		bool	bPlayerMeleeStrongEnemyAttackFlg;	// プレイヤーが近距離攻撃(強)で敵を攻撃したかのフラグ							/* 2025.03.03 菊池雅道 攻撃関連の変数追加 */
		int		iPlayerMeleeStrongAfterCount;		// プレイヤーが近距離攻撃(強)で敵を攻撃した後のフレーム数						/* 2025.03.03 菊池雅道 攻撃関連の変数追加 */
		int		iMeleeStrongDestroyCount;			// プレイヤーが近距離攻撃(強)で撃破した敵の数									/* 2025.03.18 菊池雅道 攻撃関連の変数追加 */
		bool	bPlayerMeleeStrongContinuousFlg;	// プレイヤーが連続で近距離攻撃(強)できるかのフラグ								/* 2025.03.17 菊池雅道 攻撃関連の変数追加 */
		bool	bPlayerLandingAfterMeleeStrongFlg;	// プレイヤーが近距離攻撃(強)後に着地しているかのフラグ							/* 2025.03.23 菊池雅道 攻撃関連の変数追加 */
		int		iPlayerSlowMotionCount;				// プレイヤーのスローモーションフレーム数カウント								/* 2025.03.12 菊池雅道 スローモーション関連の変数追加 */
		Enemy_Basic* pLockOnEnemy;				// ロックオン対象のエネミー
		int		iPlayerNowHp;						// プレイヤーの現在のHP
		int		iPlayerNowInvincibleTime;			// プレイヤーの現在の残り無敵時間
		int		iPlayerComboNowCount;				// プレイヤーの現在のコンボ数
		int		iPlayerComboMaxCount;				// プレイヤーの最大コンボ数
		int		iPlayerComboDuration;				// プレイヤーのコンボの残り持続時間
		bool	bPlayerAimCancelledFlg;				// 遠距離攻撃(構え)がキャンセルされたかのフラグ
		bool	bPlayerDeadFlg;						// プレイヤー死亡フラグ
		int		iPlayerDamageCount;					// 被ダメージ回数
		bool	bFallFlg;							// 落下フラグ
		int		iNowHaveKunai;						// 現在持っているクナイの数
		int		iPlayerComboRunk;					// 現在のコンボランク

		/* プレイヤーモーション関連 */
		int		iPlayerMotion_Move;						// プレイヤーモーション(移動系)
		float	fMotionTimer_Move;						// モーションタイマー(移動系)
		float	fMotionTimer_Move_End;					// モーションタイマー(移動系/終了時間)
		int		iPlayerMotionAttachIndex_Move;			// プレイヤーモーション(移動系)のアタッチ番号
		int		iPlayerMotion_Move_Old;					// 変更前プレイヤーモーション(移動系)
		float	fMotionTimer_Move_Old;					// 変更前モーションタイマー(移動系)
		float	fMotionTimer_Move_Old_End;				// 変更前モーションタイマー(移動系/終了時間)
		int		iPlayerMotionAttachIndex_Move_Old;		// 変更前プレイヤーモーション(移動系)のアタッチ番号
		float	fNowMoveMotionBlendRate;				// 現在の移動モーションのブレンド率
		int		iPlayerMotion_Attack;					// プレイヤーモーション(攻撃系)
		float	fMotionTimer_Attack;					// モーションタイマー(攻撃系)
		float	fMotionTimer_Attack_End;				// モーションタイマー(攻撃系/終了時間)
		int		iPlayerMotionAttachIndex_Attack;		// プレイヤーモーション(攻撃系)のアタッチ番号
		int		iPlayerMotion_Attack_Old;				// 変更前プレイヤーモーション(攻撃系)		
		float	fMotionTimer_Attack_Old;				// 変更前モーションタイマー(攻撃系)
		float	fMotionTimer_Attack_Old_End;			// 変更前モーションタイマー(攻撃系/終了時間)
		int		iPlayerMotionAttachIndex_Attack_Old;	// 変更前プレイヤーモーション(攻撃系)のアタッチ番号
		float	fNowAttackMotionBlendRate;				// 現在の攻撃モーションのブレンド率
		bool	bStartFastMotion;						// 開始時モーション開始フラグ
		int		iFastMotionCount;						// 開始時モーションカウント

		/* 判定処理用コリジョン */
		COLLISION_CAPSULE	stMeleeSearchCollision;			// 近接攻撃(強)のロックオン範囲コリジョン
		bool				bMeleeSearchCollisionUseFlg;	// 近接攻撃(強)のロックオン範囲コリジョン使用フラグ
		
		/* 能力値関連(※プレイヤーの装備等によって上下する可能性のあるステータス))*/
		float	fPlayerMoveAcceleration;				// プレイヤーの移動加速度
		float	fPlayerJumpSpeed;						// プレイヤージャンプ速度														/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		float	fPlayerFallAcceleration;				// プレイヤーの落下加速度
		float	fPlayerMaxFallSpeed;					// プレイヤーの最大落下速度
		int		iPlayerMaxJumpCount;					// プレイヤーのジャンプ回数(最大数)
		int		iPlayerJumpCoolTime;					// プレイヤーのジャンプクールタイム												/* 2025.03.23 菊池雅道 移動関連の変数追加 */
		float	fPlayerDodgeSpeed;						// プレイヤー回避速度															/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		int		iPlayerMaxDodgeFlame;					// プレイヤーの最大回避フレーム数												/* 2025.03.19 菊池雅道 移動関連の変数追加 */
		int		iPlayerDodgeCoolTime;					// プレイヤーの回避クールタイム													/* 2025.03.23 菊池雅道 移動関連の変数追加 */
		float	fPlayerKickWallHorizontalSpeed;			// プレイヤーの壁キック速度(水平成分)											/* 2025.03.19 菊池雅道 移動関連の変数追加 */
		float	fPlayerKickWallVerticalSpeed;			// プレイヤーの壁キック速度(垂直成分)											/* 2025.03.19 菊池雅道 移動関連の変数追加 */
		int		iPlayerKickWallFlame;					// プレイヤーの壁キック継続フレーム数											/* 2025.03.19 菊池雅道 移動関連の変数追加 */
		int		iPlayerKickWallInputMaxFlame;			// プレイヤーの壁キック入力猶予フレーム数										/* 2025.03.19 菊池雅道 移動関連の変数追加 */
		int		iPlayerMeleeWeakCoolTime;				// プレイヤーの近距離攻撃(弱)のクールタイム										/* 2025.03.24 菊池雅道 攻撃関連の変数追加 */
		int		iPlayerMelleStrongChangeChargeFrame;	// プレイヤーの近距離攻撃(強)に切り替わるチャージフレーム数						/* 2025.03.19 菊池雅道 攻撃関連の変数追加 */
		int		iPlayerMelleStrongMaxChargeFrame;		// プレイヤーの近距離攻撃(強)の最大チャージフレーム数							/* 2025.03.19 菊池雅道 攻撃関連の変数追加 */
		float	fPlayerMelleStrongMoveScale;			// プレイヤーの近距離攻撃(強)の移動距離のスケール								/* 2025.03.19 菊池雅道 攻撃関連の変数追加 */
		float	fPlayerMelleStrongMoveSpeed;			// プレイヤーの近距離攻撃(強)の移動速度											/* 2025.03.19 菊池雅道 攻撃関連の変数追加 */
		int		iPlayerMeleeStrongContinusMaxFrame;		// プレイヤーが近距離攻撃(強)で連続攻撃できる最大フレーム数						/* 2025.03.19 菊池雅道 攻撃関連の変数追加 */
		int		iPlayerMeleeStrongAirMaxCount;			// プレイヤーの空中での近距離攻撃(強)回数(※敵を攻撃していない場合の最大数)		/* 2025.02.26 菊池雅道 攻撃関連の変数追加 */
		float	fPlayerMeleeStrongNextSearchRange;		// プレイヤーの近距離攻撃(強)後の索敵範囲										/* 2025.03.23 菊池雅道 攻撃関連の変数追加 */
		float	fPlayerRockOnRadius;					// ロックオン範囲の半径
		int		iStartHaveKunai;						// 初期状態で持っているクナイの数
		int		iMaxhaveKunai;							// 最大で持てるクナイの数
		int		iPlayerKunaiCoolTime;					// クナイのクールタイム
		int		iPlayerMaxHp;							// プレイヤーの最大HP
		int		iPlayerMaxInvincibleTime;				// プレイヤーの最大無敵時間


		/* プレイヤーバフ関連(エディット周り) */
		float	fAddMoveSpeedUp;					// 移動速度上昇値(速度/フレーム)
		int		iAddBlood;							// ブラッド(ゲーム内通貨)の入手量(個)
		int		iAddComboTime;						// コンボ時間増加値(フレーム)
		int		iAddAttackChargeFrameShortening;	// チャージ時間短縮値(フレーム)
		int		iAddJumpCount;						// ジャンプ回数増加値(回)
		int		iAddMeleeStrongAirMaxCount;			// 空中での近距離攻撃(強)回数増加値(回)
		int		iAddKunaiKeepProbability;			// クナイ保持確率(%)
		int		iAddBarrier;						// バリア数(個)
		bool	bAddCounter;						// カウンター追加フラグ(有効/無効)
		bool	bAddKunaiExplosion;					// クナイ爆発化フラグ(有効/無効)
		bool	bAddMaxHpOne;						// 最大HP1化フラグ(有効/無効)
		int		iAddKunai;							// クナイ追加数(個)
		
		/* Jsonファイルでのオプション名と変数の対応表 */
		std::vector<PLAYER_STATUS_LIST> astPlayerStatusList =
		{
			// 能力値名称(Json内),									対応した変数(ポインタ),						データ型
			{ BASE_STATUS_NAME_MOVE_ACCELERATION,					&fPlayerMoveAcceleration,					DATA_TYPE_FLOAT	},	// プレイヤーの移動加速度
			{ BASE_STATUS_NAME_JUMP_SPEED,							&fPlayerJumpSpeed,							DATA_TYPE_FLOAT	},	// プレイヤーのジャンプ回数(最大数)
			{ BASE_STATUS_NAME_FALL_ACCELERATION,					&fPlayerFallAcceleration,					DATA_TYPE_FLOAT	},	// プレイヤーの落下加速度
			{ BASE_STATUS_NAME_FALL_SPEED_MAX,						&fPlayerMaxFallSpeed,						DATA_TYPE_FLOAT	},	// プレイヤーの最大落下速度			
			{ BASE_STATUS_NAME_JUMP_COUNT_MAX,						&iPlayerMaxJumpCount,						DATA_TYPE_INT	},	// プレイヤーのジャンプ回数(最大数)
			{ BASE_STATUS_NAME_JUMP_COOL_TIME,						&iPlayerJumpCoolTime,						DATA_TYPE_INT	},	// プレイヤーのジャンプクールタイム										/* 2025.03.23 菊池雅道 追加 */
			{ BASE_STATUS_NAME_DODGE_SPEED,							&fPlayerDodgeSpeed,							DATA_TYPE_FLOAT	},	// プレイヤーの回避速度													/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_DODGE_FRAME,							&iPlayerMaxDodgeFlame,						DATA_TYPE_INT	},	// プレイヤーの回避フレーム数											/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_DODGE_COOL_TIME,						&iPlayerDodgeCoolTime,						DATA_TYPE_INT	},	// プレイヤーの回避クールタイム											/* 2025.03.23 菊池雅道 追加 */
			{ BASE_STATUS_NAME_KICKWALL_HORIZONTAL_SPEED,			&fPlayerKickWallHorizontalSpeed,			DATA_TYPE_FLOAT },	// プレイヤーの壁キック速度(水平成分)									/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_KICKWALL_VERTICAL_SPEED,				&fPlayerKickWallVerticalSpeed,				DATA_TYPE_FLOAT },	// プレイヤーの壁キック速度(垂直成分)									/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_KICKWALL_FLAME,						&iPlayerKickWallFlame,						DATA_TYPE_INT	},	// プレイヤーの壁キック継続フレーム数									/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STASUS_NAME_KICKWALL_INPUT_MAX_FLAME,			&iPlayerKickWallInputMaxFlame,				DATA_TYPE_INT	},	// プレイヤーの壁キック入力猶予フレーム数								/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_MELEE_WEAK_COOL_TIME,				&iPlayerMeleeWeakCoolTime,					DATA_TYPE_INT	},	// プレイヤーの近距離攻撃(弱)のクールタイム								/* 2025.03.23 菊池雅道 追加 */
			{ BASE_STATUS_NAME_MELEE_STRONG_CHANGE_CHARGE_FRAME,	&iPlayerMelleStrongChangeChargeFrame,		DATA_TYPE_INT	},	// プレイヤーの近距離攻撃(強)に切り替わるチャージフレーム数				/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_MELEE_STRONG_MAX_CHARGE_FRAME,		&iPlayerMelleStrongMaxChargeFrame,			DATA_TYPE_INT	},	// プレイヤーの近距離攻撃(強)の最大チャージフレーム数					/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_MELEE_STRONG_MOVE_SCALE,				&fPlayerMelleStrongMoveScale,				DATA_TYPE_FLOAT	},	// プレイヤーの近距離攻撃(強)の移動距離のスケール						/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_MELEE_STRONG_MOVE_SPEED,				&fPlayerMelleStrongMoveSpeed,				DATA_TYPE_FLOAT	},	// プレイヤー近距離攻撃(強)の移動速度									/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_MELEE_STRONG_CONTINUS_MAX_FRAME,		&iPlayerMeleeStrongContinusMaxFrame,		DATA_TYPE_INT	},	// プレイヤー近距離攻撃(強)で連続攻撃できる最大フレーム数				/* 2025.03.19 菊池雅道 追加 */
			{ BASE_STATUS_NAME_MELEE_STRONG_AIR_MAX_COUNT,			&iPlayerMeleeStrongAirMaxCount,				DATA_TYPE_INT	},	// プレイヤーが空中で近距離攻撃(強)を行える最大回数(※敵を攻撃していない場合)
			{ BASE_STATUS_NAME_MELEE_STRONG_NEXT_SEARCH_RANGE,		&fPlayerMeleeStrongNextSearchRange,			DATA_TYPE_FLOAT	},	// プレイヤーが近距離攻撃(強)を行った後の索敵範囲						/* 2025.03.23 菊池雅道 追加 */
			{ BASE_STATUS_NAME_ROCK_ON_RADIUS,						&fPlayerRockOnRadius,						DATA_TYPE_FLOAT	},	// ロックオン範囲の半径
			{ BASE_STATUS_NAME_START_HAVE_KUNAI,					&iStartHaveKunai,							DATA_TYPE_INT	},	// 初期状態で持っているクナイの個数
			{ BASE_STATUS_NAME_MAX_HAVE_KUNAI,						&iMaxhaveKunai,								DATA_TYPE_INT	},	// 最大で持てるクナイの個数
			{ BASE_STATUS_NAME_KUNAI_COOL_TIME,						&iPlayerKunaiCoolTime,							DATA_TYPE_INT	},	// クナイのクールタイム													/* 2025.03.23 菊池雅道 追加 */
			{ BASE_STATUS_NAME_HP_MAX,								&iPlayerMaxHp,								DATA_TYPE_INT	},	// プレイヤーの最大HP
			{ BASE_STATUS_NAME_INVINCIBLE_TIME_MAX,					&iPlayerMaxInvincibleTime,					DATA_TYPE_INT	},	// プレイヤーの最大無敵時間
		};
};
