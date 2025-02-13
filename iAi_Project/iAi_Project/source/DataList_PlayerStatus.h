/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道 移動関連の変数・関数追加 */
/* 2025.01.22 菊池雅道 攻撃関連の変数・関数追加 */
/* 2025.02.05 菊池雅道 ステータス関連の変数・関数修正 */
/* 2025.02.10 菊池雅道 移動関連の変数・関数追加 */
/* 2025.02.11 菊池雅道 攻撃関連の変数・関数追加 */


#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"
#include "PlayerMotionDefine.h"

/* 前方参照 */
// ※AppFrameで定義されていないクラスを使用する場合、循環参照対策に実施する。
class EnemyBasic;

/* プレイヤー状態管理クラスの宣言 */

// プレイヤー状態管理クラス
class DataList_PlayerStatus : public DataListBase
{
	public:
		DataList_PlayerStatus();			// コンストラクタ
		virtual ~DataList_PlayerStatus();	// デストラクタ

		/* データ取得 */
		// プレイヤー状態関連
		int		iGetPlayerMoveState()				{ return this->iPlayerMoveState; }					// プレイヤーの移動状態取得										/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		int		iGetPlayerAttackState()				{ return this->iPlayerAttackState; }				// プレイヤーの攻撃状態取得										/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		bool	bGetPlayerLandingFlg()				{ return this->bPlayerLandingFlg; }					// プレイヤーが空中にいるかのフラグ取得
		float	fGetPlayerNowMoveSpeed()			{ return this->fPlayerNowMoveSpeed; }				// プレイヤーの現在の移動速度取得
		float	fGetPlayerAngleX()					{ return this->fPlayerAngleX; }						// プレイヤーのX軸回転量(ラジアン)取得
		float	fGetPlayerTurnSpeed()				{ return this->fPlayerTurnSpeed; }					// プレイヤーの回転速度取得										/* 2025.02.10 菊池雅道 移動関連の関数追加 */
		float	fGetPlayerNowFallSpeed()			{ return this->fPlayerNowFallSpeed; }				// プレイヤーの現在の落下速度取得
		int		iGetPlayerNowJumpCount()			{ return this->iPlayerNowJumpCount; }				// プレイヤーのジャンプ回数(現在数)取得
		int		iGetPlayerNowAttakChargeFlame()		{ return this->iPlayerNowAttakChargeFlame; }		// プレイヤーの現在の攻撃チャージフレーム数取得
		float	fGetPlayerNowMotionCount()			{ return this->fPlayerNowMotionCount; };			// プレイヤーのモーションの現在のカウント
		int		iGetPlayerNormalDashFlameCount()	{ return this->iPlayerNormalDashFlameCount; }		// 通常ダッシュ時経過フレーム数を取得（高速ダッシュへの移行に使用）	/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerJumpCount()				{ return this->iPlayerJumpCount; }					// プレイヤーの現在のジャンプ回数を取得								/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		bool	bGetPlayerJumpingFlag()				{ return this->bPlayerJumpingFlag; }				// プレイヤーがジャンプ中かのフラグを取得							/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		float	fGetPlayerDodgeProgress()			{ return this->fPlayerDodgeProgress; }				// プレイヤー回避モーション進行率を取得								/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		VECTOR	vecGetPlayerDodgeDirection()		{ return this->vecPlayerDodgeDirection; }			// プレイヤー回避方向を取得											/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerDodgeWhileJumpingCount()  { return this->iPlayerDodgeWhileJumpingCount; }		// プレイヤージャンプ中の回避回数を取得								/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		bool	bGetPlayerAfterDodgeFlag()			{ return this->bPlayerAfterDodgeFlag; }				// プレイヤーの回避後フラグを取得									/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		float	fGetPlayerDodgeSpeed()				{ return this->fPlayerDodgeSpeed; }					// プレイヤー回避速度を取得											/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		int		iGetPlayerNowDodgeFlame()			{ return this->iPlayerNowDodgeFlame; }				// プレイヤーの現在の回避フレーム数を取得							/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		VECTOR	vecGetPlayerChargeAttakTargetMove()	{ return this->vecPlayerChargeAttakTargetMove; }	// プレイヤー溜め攻撃の移動量を取得									/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */	/* 2025.01.26 駒沢風助 コード修正 */
		int		iGetPlayerChargeAttackCount()		{ return this->iPlayerChargeAttackCount; }			// プレイヤー溜め攻撃のカウントを取得
		EnemyBasic* pGetPlayerLockOnEnemy()			{ return this->pLockOnEnemy; }						// ロックオン対象のエネミーを取得
		int		iGetPlayerNowHp()					{ return this->iPlayerNowHp; }						// プレイヤーの現在のHPを取得
		int		iGetPlayerNowInvincibleTime()		{ return this->iPlayerNowInvincibleTime; }			// プレイヤーの現在の残り無敵時間を取得
		int		iGetPlayerComboNowCount()			{ return this->iPlayerComboNowCount; }				// プレイヤーの現在のコンボ数を取得
		int		iGetPlayerComboMaxCount()			{ return this->iPlayerComboMaxCount; }				// プレイヤーの最大コンボ数を取得
		int		iGetPlayerComboDuration()			{ return this->iPlayerComboDuration; }				// プレイヤーのコンボの残り持続時間を取得
		bool	bGetPlayerAimCancelledFlg()			{ return this->bPlayerAimCancelledFlg; }			// 遠距離攻撃(構え)がキャンセルされたかのフラグを取得				/* 2025.02.11 菊池雅道 攻撃関連の関数追加 */

		/* プレイヤーモーション関連 */
		int		iGetPlayerMotion_Move()					{ return this->iPlayerMotion_Move; }				// プレイヤーモーション(移動系)を取得
		int		iGetPlayerMotion_Move_Old()				{ return this->iPlayerMotion_Move_Old; }			// 変更前プレイヤーモーション(移動系)を取得
		int		iGetPlayerMotion_Attack()				{ return this->iPlayerMotion_Attack; }				// プレイヤーモーション(攻撃系)を取得
		int		iGetPlayerMotion_Attack_Old()			{ return this->iPlayerMotion_Attack_Old; }			// 変更前プレイヤーモーション(攻撃系)を取得
		float	fGetMotionTimer_Move()					{ return this->fMotionTimer_Move; }					// モーションカウント(移動系)を取得
		float	fGetMotionTimer_Move_End()				{ return this->fMotionTimer_Move_End; }				// モーションカウント(移動系/終了時間)を取得
		float	fGetMotionTimer_Attack()				{ return this->fMotionTimer_Attack; }				// モーションカウント(攻撃系)を取得
		float	fGetMotionTimer_Attack_End()			{ return this->fMotionTimer_Attack_End; }			// モーションカウント(攻撃系/終了時間)を取得
		int		iGetPlayerMotionAttachIndex_Move()		{ return this->iPlayerMotionAttachIndex_Move; }		// プレイヤーモーション(移動系)のアタッチ番号
		int		iGetPlayerMotionAttachIndex_Attack()	{ return this->iPlayerMotionAttachIndex_Attack; }	// プレイヤーモーション(攻撃系)のアタッチ番号

		/* 判定処理用コリジョン */
		COLLISION_CAPSULE	stGetMeleeSearchCollision()			{ return this->stMeleeSearchCollision; };		// 近接攻撃(強)のロックオン範囲コリジョンを取得
		bool				bGetMeleeSearchCollisionUseFlg()	{ return this->bMeleeSearchCollisionUseFlg; };	// 近接攻撃(強)のロックオン範囲コリジョン使用フラグを取得

		// 能力値関連※プレイヤーの装備等によって上下する可能性のあるステータス)
		float	fGetPlayerMoveAcceleration()	{ return this->fPlayerMoveAcceleration; }	// プレイヤーの移動加速度取得
		float	fGetPlayerMaxMoveSpeed()		{ return this->fPlayerMaxMoveSpeed; }		// プレイヤーの最大移動速度取得
		float	fGetPlayerFallAcceleration()	{ return this->fPlayerFallAcceleration; }	// プレイヤーの落下加速度取得
		float	fGetPlayerMaxFallSpeed()		{ return this->fPlayerMaxFallSpeed; }		// プレイヤーの最大落下速度取得
		int		iGetPlayerMaxJumpCount()		{ return this->iPlayerMaxJumpCount; }		// プレイヤーのジャンプ回数(最大数)取得
		float	fGetPlayerRockOnRadius()		{ return this->fPlayerRockOnRadius; }		// ロックオン範囲の半径を設定
		int		iGetPlayerMaxHp()				{ return this->iPlayerMaxHp; }				// プレイヤーの最大HP取得
		int		iGetPlayerMaxInvincibleTime()	{ return this->iPlayerMaxInvincibleTime; }	// プレイヤーの最大無敵時間取得

		// カメラ関連
		int		iGetCameraMode()							{ return this->iCameraMode; }							// カメラモード取得
		int		iGetCameraMode_Old()						{ return this->iCameraMode_Old; }						// カメラモード取得(変更前)
		VECTOR	vecGetCameraUp()							{ return this->vecCameraUp; }							// カメラの上方向取得
		VECTOR	vecGetCameraPosition()						{ return this->vecCameraPosition; }						// カメラの座標取得(現在地点)
		VECTOR	vecGetCameraPosition_Start()				{ return this->vecCameraPosition_Start; }				// カメラの座標取得(移動前地点)
		VECTOR	vecGetCameraPosition_Target()				{ return this->vecCameraPosition_Target; }				// カメラの座標取得(移動後地点)
		int		iGetCameraPositionLeapCount()				{ return this->iCameraPositionLeapCount; }				// カメラ座標の線形保管用カウント取得
		VECTOR	vecGetCameraTarget()						{ return this->vecCameraTarget; }						// カメラの注視点取得
		float	fGetCameraRadius()							{ return this->fCameraRadius; }							// カメラの中心点からの距離取得
		float	fGetCameraAngleX()							{ return this->fCameraAngleX; }							// カメラのX軸回転量(ラジアン)取得
		float	fGetCameraAngleY()							{ return this->fCameraAngleY; }							// カメラのY軸回転量(ラジアン)取得
		float	fGetCameraRotationalSpeed_Controller()		{ return this->fCameraRotationalSpeed_Controller; }		// カメラの回転速度(コントローラー)取得
		float	fGetCameraRotationalSpeed_Mouse()			{ return this->fCameraRotationalSpeed_Mouse; }			// カメラの回転速度(マウス)取得
		float	fGetCameraAngleLimitUp()					{ return this->fCameraAngleLimitUp; }					// カメラの回転角度制限取得(上)
		float	fGetCameraAngleLimitDown()					{ return this->fCameraAngleLimitDown; }					// カメラの回転角度制限取得(下)

		/* データ設定 */
		// プレイヤー状態関連
		void	SetPlayerMoveState(int iPlayerMoveState)							{ this->iPlayerMoveState				= iPlayerMoveState; }					// プレイヤーの移動状態設定					/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		void	SetPlayerAttackState(int iPlayerAttackState)						{ this->iPlayerAttackState				= iPlayerAttackState; }					// プレイヤーの攻撃状態設定					/* 2025.02.05 菊池雅道 ステータス関連の関数修正 */
		void	SetPlayerLanding(bool bPlayerLanding)								{ this->bPlayerLandingFlg				= bPlayerLanding; }						// プレイヤーが空中にいるかのフラグ設定
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)					{ this->fPlayerNowMoveSpeed				= fPlayerNowMoveSpeed; }				// プレイヤーの現在の移動速度設定
		void	SetPlayerAngleX(float fPlayerAngleX)								{ this->fPlayerAngleX					= fPlayerAngleX; }						// プレイヤーのX軸回転量(ラジアン)取得
		void	SetPlayerTurnSpeed(float fPlayerTurnSpeed)							{ this->fPlayerTurnSpeed				= fPlayerTurnSpeed; }					// プレイヤーの回転速度設定					/* 2025.02.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerNowFallSpeed(float fPlayerNowFallSpeed)					{ this->fPlayerNowFallSpeed				= fPlayerNowFallSpeed; }				// プレイヤーの現在の落下速度設定
		void	SetPlayerNowJumpCount(int iPlayerNowJumpCount)						{ this->iPlayerNowJumpCount				= iPlayerNowJumpCount; }				// プレイヤーのジャンプ回数(現在数)設定
		void	SetPlayerNormalDashFlameCount(int iPlayerNormalDashFlameCount)		{ this->iPlayerNormalDashFlameCount		= iPlayerNormalDashFlameCount; }		// 通常ダッシュ時経過フレーム数を設定
		void	SetPlayerNowAttakChargeFlame(int iPlayerNowAttakChargeFlame)		{ this->iPlayerNowAttakChargeFlame		= iPlayerNowAttakChargeFlame; }			// プレイヤーの現在の攻撃チャージフレーム数設定
		void	SetPlayerNowMotionCount(float fPlayerNowMotionCount)				{ this->fPlayerNowMotionCount			= fPlayerNowMotionCount; };				// プレイヤーのモーションの現在のカウント
		void	SetPlayerJumpCount(int iPlayerJumpCount)							{ this->iPlayerJumpCount				= iPlayerJumpCount; }					// プレイヤージャンプ回数を設定				/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerJumpingFlag(bool bPlayerJumpingFlag)						{ this->bPlayerJumpingFlag				= bPlayerJumpingFlag; }					// プレイヤーがジャンプ中かのフラグを設定	/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerDodgeProgress(float fPlayerDodgeProgress)					{ this->fPlayerDodgeProgress			= fPlayerDodgeProgress; }				// プレイヤー回避モーション進行率を設定		/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerDodgeDirection(VECTOR vecPlayerDodgeDirection)				{ this->vecPlayerDodgeDirection			= vecPlayerDodgeDirection; }			// プレイヤー回避方向を設定					/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerDodgeWhileJumpingCount(int iPlayerDodgeWhileJumpingCount)  { this->iPlayerDodgeWhileJumpingCount	= iPlayerDodgeWhileJumpingCount; }		// プレイヤージャンプ中の回避回数を設定		/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerAfterDodgeFlag(bool bPlayerAfterDodgeFlag)					{ this->bPlayerAfterDodgeFlag			= bPlayerAfterDodgeFlag; }				// プレイヤーの回避後フラグを設定			/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerLockOnEnemy(EnemyBasic* pLockOnEnemy)						{ this->pLockOnEnemy					= pLockOnEnemy; };						// ロックオン対象のエネミーを設定
		void	SetPlayerNowHp(int iPlayerNowHp)									{ this->iPlayerNowHp					= iPlayerNowHp; }						// プレイヤーの現在のHPを設定
		void	SetPlayerNowInvincibleTime(int iPlayerNowInvincibleTime)			{ this->iPlayerNowInvincibleTime		= iPlayerNowInvincibleTime; }			// プレイヤーの現在の残り無敵時間を設定
		void	SetPlayerComboNowCount(int iPlayerComboNowCount)					{ this->iPlayerComboNowCount			= iPlayerComboNowCount; }				// プレイヤーの現在のコンボ数を設定
		void	SetPlayerComboMaxCount(int iPlayerComboMaxCount)					{ this->iPlayerComboMaxCount			= iPlayerComboMaxCount; }				// プレイヤーの最大コンボ数を設定
		void	SetPlayerComboDuration(int iPlayerComboDuration)					{ this->iPlayerComboDuration			= iPlayerComboDuration; }				// プレイヤーのコンボの残り持続時間を設定
		void	SetPlayerAimCancelledFlg(bool bPlayerAimCancelledFlg)				{ this->bPlayerAimCancelledFlg			= bPlayerAimCancelledFlg; }				// 遠距離攻撃(構え)がキャンセルされたかのフラグを設定	/* 2025.02.11 菊池雅道 攻撃関連の関数追加 */

		/* プレイヤーモーション関連 */
		void	SetPlayerMotion_Move(int iPlayerMotion_Move)							{ this->iPlayerMotion_Move				= iPlayerMotion_Move; };				// プレイヤーモーション(移動系)を設定
		void	SetPlayerMotion_Move_Old(int iPlayerMotion_Move_Old)					{ this->iPlayerMotion_Move_Old			= iPlayerMotion_Move_Old; };			// 変更前プレイヤーモーション(移動系)を設定
		void	SetPlayerMotion_Attack(int iPlayerMotion_Attack)						{ this->iPlayerMotion_Attack			= iPlayerMotion_Attack; };				// プレイヤーモーション(攻撃系)を設定
		void	SetPlayerMotion_Attack_Old(int iPlayerMotion_Attack_Old)				{ this->iPlayerMotion_Attack_Old		= iPlayerMotion_Attack_Old; };			// 変更前プレイヤーモーション(攻撃系)を設定
		void	SetMotionCount_Move(float fMotionCount_Move)							{ this->fMotionTimer_Move				= fMotionCount_Move; };					// モーションカウント(移動系)
		void	SetMotionCount_Move_End(float fMotionCount_Move_End)					{ this->fMotionTimer_Move_End			= fMotionCount_Move_End; };				// モーションカウント(移動系/終了時間)を設定
		void	SetMotionCount_Attack(float fMotionCount_Attack)						{ this->fMotionTimer_Attack				= fMotionCount_Attack; };				// モーションカウント(攻撃系)を設定
		void	SetMotionCount_Attack_End(float fMotionCount_Attack_End)				{ this->fMotionTimer_Attack_End			= fMotionCount_Attack_End; };			// モーションカウント(攻撃系/終了時間)を設定
		void	SetPlayerMotionAttachIndex_Move(int iPlayerMotionAttachIndex_Move)		{ this->iPlayerMotionAttachIndex_Move	= iPlayerMotionAttachIndex_Move; }		// プレイヤーモーション(移動系)のアタッチ番号
		void	SetPlayerMotionAttachIndex_Attack(int iPlayerMotionAttachIndex_Attack)	{ this->iPlayerMotionAttachIndex_Attack	= iPlayerMotionAttachIndex_Attack; }	// プレイヤーモーション(攻撃系)のアタッチ番号

		/* 判定処理用コリジョン */
		void	SetMeleeSearchCollision(COLLISION_CAPSULE stMeleeSearchCollision)	{ this->stMeleeSearchCollision			= stMeleeSearchCollision; }				// 近接攻撃(強)のロックオン範囲コリジョンを設定
		void	SetMeleeSearchCollisionUseFlg(bool bMeleeSearchCollisionUseFlg)		{ this->bMeleeSearchCollisionUseFlg		= bMeleeSearchCollisionUseFlg; }		// 近接攻撃(強)のロックオン範囲コリジョン使用フラグを設定

		// 能力値関連(※プレイヤーの装備等によって上下する可能性のあるステータス)
		void	SetPlayerMoveAcceleration(float fPlayerMoveAcceleration)				{ this->fPlayerMoveAcceleration			= fPlayerMoveAcceleration; }		// プレイヤーの移動加速度設定
		void	SetPlayerMaxMoveSpeed(float fPlayerMaxMoveSpeed)						{ this->fPlayerMaxMoveSpeed				= fPlayerMaxMoveSpeed;}				// プレイヤーの最大移動速度設定
		void	SetPlayerFallAcceleration(float fPlayerFallAcceleration)				{ this->fPlayerFallAcceleration			= fPlayerFallAcceleration; }		// プレイヤーの落下加速度設定
		void	SetPlayerMaxFallSpeed(float fPlayerMaxFallSpeed)						{ this->fPlayerMaxFallSpeed				= fPlayerMaxFallSpeed; }			// プレイヤーの最大落下速度設定
		void	SetPlayerMaxJumpCount(int iPlayerMaxJumpCount)							{ this->iPlayerMaxJumpCount				= iPlayerMaxJumpCount; }			// プレイヤーのジャンプ回数(最大数)設定
		void	SetPlayerDodgeSpeed(float fPlayerDodgeSpeed)							{ this->fPlayerDodgeSpeed				= fPlayerDodgeSpeed; }				// プレイヤー回避速度を設定				/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerNowDodgeFlame(int iPlayerNowDodgeFlame)						{ this->iPlayerNowDodgeFlame			= iPlayerNowDodgeFlame; }			// プレイヤー回避時間を設定				/* 2025.01.10 菊池雅道 移動関連の関数追加 */		
		void	SetPlayerChargeAttakTargetMove(VECTOR vecPlayerChargeAttakTargetMove)	{ this->vecPlayerChargeAttakTargetMove	= vecPlayerChargeAttakTargetMove; }	// プレイヤー溜め攻撃の移動量を設定		/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */	/* 2025.01.26 駒沢風助 コード修正 */
		void	SetPlayerChargeAttackCount(int iPlayerChargeAttackCount)				{ this->iPlayerChargeAttackCount		= iPlayerChargeAttackCount;}		// 近接攻撃(強)のカウントを設定
		void	SetPlayerRockOnRadius(float fPlayerRockOnRadius)						{ this->fPlayerRockOnRadius				= fPlayerRockOnRadius; }			// ロックオン範囲の半径を設定
		void	SetPlayerMaxHp(int iPlayerMaxHp)										{ this->iPlayerMaxHp					= iPlayerMaxHp; }					// プレイヤーの最大HP設定
		void	SetPlayerMaxInvincibleTime(int iPlayerMaxInvincibleTime)				{ this->iPlayerMaxInvincibleTime		= iPlayerMaxInvincibleTime; }		// プレイヤーの最大無敵時間設定

		// カメラ関連
		void	SetCameraMode(int iCameraMode)										{ this->iCameraMode							= iCameraMode; }				// カメラモード設定
		void	SetCameraMode_Old(int iCameraMode_Old)								{ this->iCameraMode_Old						= iCameraMode_Old; }			// カメラモード(変更前)設定
		void	SetCameraUp(VECTOR vecCameraUp)										{ this->vecCameraUp							= vecCameraUp; }				// カメラの上方向設定
		void	SetCameraPosition(VECTOR vecCameraPosition)							{ this->vecCameraPosition					= vecCameraPosition; }			// カメラの座標設定(現在地点)
		void	SetCameraPosition_Start(VECTOR vecCameraPosition_Start)				{ this->vecCameraPosition_Start				= vecCameraPosition_Start; }	// カメラの座標設定(移動前地点)
		void	SetCameraPosition_Target(VECTOR vecCameraPosition_Target)			{ this->vecCameraPosition_Target			= vecCameraPosition_Target; }	// カメラの座標設定(移動後地点)
		void	SetCameraPositionLeapCount(int iCameraPositionLeapCount)			{ this->iCameraPositionLeapCount			= iCameraPositionLeapCount; }	// カメラ座標の線形保管用カウント設定
		void	SetCameraTarget(VECTOR vecCameraTarget)								{ this->vecCameraTarget						= vecCameraTarget; }			// カメラの注視点設定
		void	SetCameraRadius(float fCameraRadius)								{ this->fCameraRadius						= fCameraRadius; }				// カメラの中心点からの距離設定
		void	SetCameraAngleX(float fCameraAngleX)								{ this->fCameraAngleX						= fCameraAngleX; }				// カメラのX軸回転量(ラジアン)設定
		void	SetCameraAngleY(float fCameraAngleY)								{ this->fCameraAngleY						= fCameraAngleY; }				// カメラのY軸回転量(ラジアン)設定
		void	SetCameraRotationalSpeed_Controller(float fCameraRotationalSpeed)	{ this->fCameraRotationalSpeed_Controller	= fCameraRotationalSpeed; }		// カメラの回転速度(コントローラー)設定
		void	SetCameraRotationalSpeed_Mouse(float fCameraRotationalSpeed)		{ this->fCameraRotationalSpeed_Mouse		= fCameraRotationalSpeed; }		// カメラの回転速度(マウス)設定
		void	SetCameraAngleLimitUp(float fCameraAngleupsideLimitUp)				{ this->fCameraAngleLimitUp					= fCameraAngleLimitUp; }		// カメラの回転角度制限設定(上)
		void	SetCameraAngleLimitDown(float fCameraAngleupsideLimitDown)			{ this->fCameraAngleLimitDown				= fCameraAngleLimitDown; }		// カメラの回転角度制限設定(下)

		/* 2025.01.22 菊池雅道 攻撃関連の変数追加開始 */
		//攻撃
		VECTOR vecPlayerChargeAttakPoint;	//プレイヤー溜め攻撃の目的地
		VECTOR vecPlayerChargeAttakVector;	//プレイヤー溜め攻撃の方向
		int iPlayerNowAttakChargeFlame;		//現在のプレイヤー溜め攻撃チャージフレーム数
		/* 2025.01.22 菊池雅道 攻撃関連の変数追加終了 */

	private:
		/* プレイヤー状態関連 */
		int		iPlayerMoveState;				// プレイヤーの移動状態(アクション)										/* 2025.02.05 菊池雅道 ステータス関連の変数修正 */
		int		iPlayerAttackState;				// プレイヤーの攻撃状態(アクション)										/* 2025.02.05 菊池雅道 ステータス関連の変数修正 */
		bool	bPlayerLandingFlg;				// プレイヤーが着地しているかのフラグ
		float	fPlayerNowMoveSpeed;			// プレイヤーの現在の移動速度
		float	fPlayerAngleX;					// プレイヤーのX軸回転量(ラジアン)
		float	fPlayerTurnSpeed;				// プレイヤーの方向転換の速度（範囲：0.0?1.0）								/* 2025.02.10 菊池雅道 移動関連の変数追加 */
		float	fPlayerNowFallSpeed;			// プレイヤーの現在の落下速度
		int		iPlayerNowJumpCount;			// プレイヤーのジャンプ回数(現在数)
		float	fPlayerNowMotionCount;			// プレイヤーのモーションの現在のカウント
		int		iPlayerNormalDashFlameCount;	// 通常ダッシュ時経過フレーム数（高速ダッシュへの移行に使用）					/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		bool	bPlayerJumpingFlag;				// プレイヤーがジャンプ中かのフラグ												/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		int		iPlayerJumpCount;				// プレイヤーの現在のジャンプ回数												/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		int		iPlayerNowDodgeFlame;			// プレイヤーの現在の回避フレーム数												/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		float	fPlayerDodgeProgress;			// プレイヤー回避モーション進行率 (範囲：0.0～1.0)								/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		VECTOR	vecPlayerDodgeDirection;		// プレイヤー回避方向															/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		int		iPlayerDodgeWhileJumpingCount;	// プレイヤージャンプ中の回避回数												/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		bool	bPlayerAfterDodgeFlag;			// プレイヤーの回避後フラグ														/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		VECTOR	vecPlayerChargeAttakTargetMove;	// 近接攻撃(強)による移動量														/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */	/* 2025.01.26 駒沢風助 コード修正 */
		int		iPlayerChargeAttackCount;		// 近接攻撃(強)のカウント
		EnemyBasic*	pLockOnEnemy;				// ロックオン対象のエネミー
		int		iPlayerNowHp;					// プレイヤーの現在のHP
		int		iPlayerNowInvincibleTime;		// プレイヤーの現在の残り無敵時間
		int		iPlayerComboNowCount;			// プレイヤーの現在のコンボ数
		int		iPlayerComboMaxCount;			// プレイヤーの最大コンボ数
		int		iPlayerComboDuration;			// プレイヤーのコンボの残り持続時間
		bool	bPlayerAimCancelledFlg;			// 遠距離攻撃(構え)がキャンセルされたかのフラグ

		/* プレイヤーモーション関連 */
		int		iPlayerMotion_Move;					// プレイヤーモーション(移動系)
		int		iPlayerMotion_Move_Old;				// 変更前プレイヤーモーション(移動系)
		int		iPlayerMotion_Attack;				// プレイヤーモーション(攻撃系)
		int		iPlayerMotion_Attack_Old;			// 変更前プレイヤーモーション(攻撃系)
		float	fMotionTimer_Move;					// モーションタイマー(移動系)
		float	fMotionTimer_Move_End;				// モーションタイマー(移動系/終了時間)
		float	fMotionTimer_Attack;				// モーションタイマー(攻撃系)
		float	fMotionTimer_Attack_End;			// モーションタイマー(攻撃系/終了時間)
		int		iPlayerMotionAttachIndex_Move;		// プレイヤーモーション(移動系)のアタッチ番号
		int		iPlayerMotionAttachIndex_Attack;	// プレイヤーモーション(攻撃系)のアタッチ番号

		/* 判定処理用コリジョン */
		COLLISION_CAPSULE	stMeleeSearchCollision;			// 近接攻撃(強)のロックオン範囲コリジョン
		bool				bMeleeSearchCollisionUseFlg;	// 近接攻撃(強)のロックオン範囲コリジョン使用フラグ
		
		/* 能力値関連(※プレイヤーの装備等によって上下する可能性のあるステータス))*/
		float	fPlayerMoveAcceleration;		// プレイヤーの移動加速度
		float	fPlayerMaxMoveSpeed;			// プレイヤーの最大移動速度
		float	fPlayerFallAcceleration;		// プレイヤーの落下加速度
		float	fPlayerMaxFallSpeed;			// プレイヤーの最大落下速度
		int		iPlayerMaxJumpCount;			// プレイヤーのジャンプ回数(最大数)
		float	fPlayerJumpSpeed;				// プレイヤージャンプ速度				/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		float	fPlayerDodgeSpeed;				// プレイヤー回避速度					/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		float	fPlayerRockOnRadius;			// ロックオン範囲の半径
		int		iPlayerMaxHp;					// プレイヤーの最大HP
		int		iPlayerMaxInvincibleTime;		// プレイヤーの最大無敵時間

		/* カメラ関連 */
		int		iCameraMode;						// カメラモード
		int		iCameraMode_Old;					// カメラモード(変更前)
		VECTOR	vecCameraUp;						// カメラの上方向
		VECTOR	vecCameraPosition;					// カメラの座標(現在地点)
		VECTOR	vecCameraPosition_Start;			// カメラの座標(移動前地点)
		VECTOR	vecCameraPosition_Target;			// カメラの座標(移動後地点)
		int		iCameraPositionLeapCount;			// カメラ座標の線形保管用カウント
		VECTOR	vecCameraTarget;					// カメラの注視点
		float	fCameraRadius;						// カメラの中心点からの距離(ズーム量)
		float	fCameraAngleX;						// カメラのX軸回転量(ラジアン)
		float	fCameraAngleY;						// カメラのY軸回転量(ラジアン)
		float	fCameraRotationalSpeed_Controller;	// カメラの回転速度(コントローラー)
		float	fCameraRotationalSpeed_Mouse;		// カメラの回転速度(マウス)
		float	fCameraAngleLimitUp;				// カメラの回転角度制限(上)
		float	fCameraAngleLimitDown;				// カメラの回転角度制限(下)

	protected:
};
