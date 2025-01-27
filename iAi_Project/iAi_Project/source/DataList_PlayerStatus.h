/* 2024.12.26 駒沢風助 ファイル作成 */
/* 2025.01.09 菊池雅道 移動関連の変数・関数追加 */
/* 2025.01.22 菊池雅道 攻撃関連の変数・関数追加 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"

/* プレイヤー状態管理クラスの宣言 */

// プレイヤー状態管理クラス
class DataList_PlayerStatus : public DataListBase
{
	public:
		DataList_PlayerStatus();			// コンストラクタ
		virtual ~DataList_PlayerStatus();	// デストラクタ

		/* データ取得 */
		// プレイヤー状態関連
		int		iGetPlayerState()					{ return this->iPlayerState; }						// プレイヤーの状態取得
		int		iGetPlayerMotion()					{ return this->iPlayerMotion; }						// プレイヤーのモーション取得
		bool	bGetPlayerLandingFlg()				{ return this->bPlayerLandingFlg; }					// プレイヤーが空中にいるかのフラグ取得
		float	fGetPlayerNowMoveSpeed()			{ return this->fPlayerNowMoveSpeed; }				// プレイヤーの現在の移動速度取得
		float	fGetPlayerAngleX()					{ return this->fPlayerAngleX; }						// プレイヤーのX軸回転量(ラジアン)取得
		float	fGetPlayerNowFallSpeed()			{ return this->fPlayerNowFallSpeed; }				// プレイヤーの現在の落下速度取得
		int		iGetPlayerNowJumpCount()			{ return this->iPlayerNowJumpCount; }				// プレイヤーのジャンプ回数(現在数)取得
		int		iGetPlayerNowAttakChargeFlame()		{ return this->iPlayerNowAttakChargeFlame; }		// プレイヤーの現在の攻撃チャージフレーム数取得
		float	fGetPlayerNowMotionCount()			{ return this->fPlayerNowMotionCount; };			// プレイヤーのモーションの現在のカウント
		VECTOR	vecGetPlayerOldVector()				{ return this->vecPlayerOldVector; }				// プレイヤーの移動時のベクトルを取得（ジャンプ慣性等に使用）		/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		float	fGetPlayerOldRadian()				{ return this->fPlayerOldRadian; }					// プレイヤーの移動時の角度を取得（方向転換時等に使用）				/* 2025.01.10 菊池雅道 移動関連の関数追加 */
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

		/* 判定処理用コリジョン */
		COLLISION_CAPSULE	stGetMeleeSearchCollision()	{ return this->stMeleeSearchCollision; };		// 近接攻撃(強)のロックオン範囲コリジョンを取得

		// 能力値関連
		float	fGetPlayerMoveAcceleration()	{ return this->fPlayerMoveAcceleration; }	// プレイヤーの移動加速度取得
		float	fGetPlayerMaxMoveSpeed()		{ return this->fPlayerMaxMoveSpeed; }		// プレイヤーの最大移動速度取得
		float	fGetPlayerFallAcceleration()	{ return this->fPlayerFallAcceleration; }	// プレイヤーの落下加速度取得
		float	fGetPlayerMaxFallSpeed()		{ return this->fPlayerMaxFallSpeed; }		// プレイヤーの最大落下速度取得
		int		iGetPlayerMaxJumpCount()		{ return this->iPlayerMaxJumpCount; }		// プレイヤーのジャンプ回数(最大数)取得

		// カメラ関連
		int		iGetCameraMode()							{ return this->iCameraMode; }							// カメラモード取得
		VECTOR	vecGetCameraUp()							{ return this->vecCameraUp; }							// カメラの上方向取得
		VECTOR	vecGetCameraPosition()						{ return this->vecCameraPosition; }						// カメラの座標取得
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
		void	SetPlayerState(int iPlayerState)									{ this->iPlayerState					= iPlayerState; }						// プレイヤーの状態設定
		void	SetPlayerMotion(int iPlayerMotion)									{ this->iPlayerMotion					= iPlayerMotion; };						// プレイヤーのモーション設定
		void	SetPlayerLanding(bool bPlayerLanding)								{ this->bPlayerLandingFlg				= bPlayerLanding; }						// プレイヤーが空中にいるかのフラグ設定
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)					{ this->fPlayerNowMoveSpeed				= fPlayerNowMoveSpeed; }				// プレイヤーの現在の移動速度設定
		void	SetPlayerAngleX(float fPlayerAngleX)								{ this->fPlayerAngleX					= fPlayerAngleX; }						// プレイヤーのX軸回転量(ラジアン)取得
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

		/* 判定処理用コリジョン */
		void	SetMeleeSearchCollision(COLLISION_CAPSULE stMeleeSearchCollision)	{ this->stMeleeSearchCollision			= stMeleeSearchCollision; }				// 近接攻撃(強)のロックオン範囲コリジョンを設定

		// 能力値関連
		void	SetPlayerMoveAcceleration(float fPlayerMoveAcceleration)				{ this->fPlayerMoveAcceleration			= fPlayerMoveAcceleration; }		// プレイヤーの移動加速度設定
		void	SetPlayerMaxMoveSpeed(float fPlayerMaxMoveSpeed)						{ this->fPlayerMaxMoveSpeed				= fPlayerMaxMoveSpeed;}				// プレイヤーの最大移動速度設定
		void	SetPlayerFallAcceleration(float fPlayerFallAcceleration)				{ this->fPlayerFallAcceleration			= fPlayerFallAcceleration; }		// プレイヤーの落下加速度設定
		void	SetPlayerMaxFallSpeed(float fPlayerMaxFallSpeed)						{ this->fPlayerMaxFallSpeed				= fPlayerMaxFallSpeed; }			// プレイヤーの最大落下速度設定
		void	SetPlayerMaxJumpCount(int iPlayerMaxJumpCount)							{ this->iPlayerMaxJumpCount				= iPlayerMaxJumpCount; }			// プレイヤーのジャンプ回数(最大数)設定
		void	SetPlayerDodgeSpeed(float fPlayerDodgeSpeed)							{ this->fPlayerDodgeSpeed				= fPlayerDodgeSpeed; }				// プレイヤー回避速度を取得				/* 2025.01.10 菊池雅道 移動関連の関数追加 */
		void	SetPlayerNowDodgeFlame(int iPlayerNowDodgeFlame)						{ this->iPlayerNowDodgeFlame			= iPlayerNowDodgeFlame; }			// プレイヤー回避時間を取得				/* 2025.01.10 菊池雅道 移動関連の関数追加 */		
		void	SetPlayerChargeAttakTargetMove(VECTOR vecPlayerChargeAttakTargetMove)	{ this->vecPlayerChargeAttakTargetMove	= vecPlayerChargeAttakTargetMove; }	// プレイヤー溜め攻撃の移動量を設定		/* 2025.01.22 菊池雅道 攻撃関連の変数追加 */	/* 2025.01.26 駒沢風助 コード修正 */
		void	SetPlayerChargeAttackCount(int iPlayerChargeAttackCount)				{ this->iPlayerChargeAttackCount		= iPlayerChargeAttackCount;}		// 近接攻撃(強)のカウント
		
		// カメラ関連
		void	SetCameraMode(int iCameraMode)										{ this->iCameraMode							= iCameraMode; }				// カメラモード設定
		void	SetCameraUp(VECTOR vecCameraUp)										{ this->vecCameraUp							= vecCameraUp; }				// カメラの上方向設定
		void	SetCameraPosition(VECTOR vecCameraPosition)							{ this->vecCameraPosition					= vecCameraPosition; }			// カメラの座標設定
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
		int		iPlayerState;					// プレイヤーの状態(アクション)
		int		iPlayerMotion;					// プレイヤーの状態(モーション)
		bool	bPlayerLandingFlg;				// プレイヤーが着地しているかのフラグ
		float	fPlayerNowMoveSpeed;			// プレイヤーの現在の移動速度
		float	fPlayerAngleX;					// プレイヤーのX軸回転量(ラジアン)
		float	fPlayerNowFallSpeed;			// プレイヤーの現在の落下速度
		int		iPlayerNowJumpCount;			// プレイヤーのジャンプ回数(現在数)
		float	fPlayerNowMotionCount;			// プレイヤーのモーションの現在のカウント
		VECTOR	vecPlayerOldVector;				// プレイヤーの移動時のベクトルを保存する（ジャンプ慣性等に使用）				/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		float	fPlayerOldRadian;				// プレイヤーの移動時の角度を保持する※単位はラジアン（方向転換時等に使用）		/* 2025.01.09 菊池雅道 移動関連の変数追加 */
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

		/* 判定処理用コリジョン */
		COLLISION_CAPSULE	stMeleeSearchCollision;			// 近接攻撃(強)のロックオン範囲コリジョン
		
		/* 能力値関連 */
		float	fPlayerMoveAcceleration;	// プレイヤーの移動加速度
		float	fPlayerMaxMoveSpeed;		// プレイヤーの最大移動速度
		float	fPlayerFallAcceleration;	// プレイヤーの落下加速度
		float	fPlayerMaxFallSpeed;		// プレイヤーの最大落下速度
		int		iPlayerMaxJumpCount;		// プレイヤーのジャンプ回数(最大数)
		float	fPlayerJumpSpeed;			// プレイヤージャンプ速度				/* 2025.01.09 菊池雅道 移動関連の変数追加 */
		float	fPlayerDodgeSpeed;			// プレイヤー回避速度					/* 2025.01.09 菊池雅道 移動関連の変数追加 */

		/* カメラ関連 */
		int		iCameraMode;						// カメラモード
		VECTOR	vecCameraUp;						// カメラの上方向
		VECTOR	vecCameraPosition;					// カメラの座標
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
