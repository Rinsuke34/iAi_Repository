/* 2025.01.22 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include "StageStatusDefine.h"

/* 画面エフェクト */
#include "ScreenEffect_Base.h"

/* ステージ状態管理クラスの宣言 */

// ステージ状態管理クラス
class DataList_StageStatus : public DataListBase
{
	public:
		DataList_StageStatus();				// コンストラクタ
		virtual ~DataList_StageStatus() {};	// デストラクタ

		/* データ取得 */
		// リスト
		std::vector<ScreenEffect_Base*>& GetScreenEffectList() { return this->pScreenEffectList; }		// 画面エフェクトリスト取得
		// 単独
		int		iGetGameStatus()	{ return this->iGameStatus; };	// ゲーム状態を取得
		int		iGetNowStageNo()	{ return this->iNowStageNo; };	// 現在のステージ番号を取得
		int		iGetEndStageNo()	{ return this->iEndStageNo; };	// 最終ステージ番号を取得
		bool	bGetGameSlowFlg()	{ return this->bGameSlowFlg; };	// スローモーションフラグを取得		/*2025.02.05 菊池雅道 スローモーションに関する関数追加 */
		bool	bGetAddUiFlg()		{ return this->bAddUiFlg; };	// UI追加フラグを取得
		// カメラ関連
		int		iGetCameraMode()						{ return this->iCameraMode; }							// カメラモード取得
		int		iGetCameraMode_Old()					{ return this->iCameraMode_Old; }						// カメラモード取得(変更前)
		VECTOR	vecGetCameraUp()						{ return this->vecCameraUp; }							// カメラの上方向取得
		VECTOR	vecGetCameraPosition()					{ return this->vecCameraPosition; }						// カメラの座標取得(現在地点)
		VECTOR	vecGetCameraPosition_Start()			{ return this->vecCameraPosition_Start; }				// カメラの座標取得(移動前地点)
		VECTOR	vecGetCameraPosition_Target()			{ return this->vecCameraPosition_Target; }				// カメラの座標取得(移動後地点)
		int		iGetCameraPositionLeapCount()			{ return this->iCameraPositionLeapCount; }				// カメラ座標の線形保管用カウント取得
		VECTOR	vecGetCameraTarget()					{ return this->vecCameraTarget; }						// カメラの注視点取得
		float	fGetCameraRadius()						{ return this->fCameraRadius; }							// カメラの中心点からの距離取得
		float	fGetCameraAngleX()						{ return this->fCameraAngleX; }							// カメラのX軸回転量(ラジアン)取得
		float	fGetCameraAngleY()						{ return this->fCameraAngleY; }							// カメラのY軸回転量(ラジアン)取得
		float	fGetCameraRotationalSpeed_Controller()	{ return this->fCameraRotationalSpeed_Controller; }		// カメラの回転速度(コントローラー)取得
		float	fGetCameraRotationalSpeed_Mouse()		{ return this->fCameraRotationalSpeed_Mouse; }			// カメラの回転速度(マウス)取得
		float	fGetCameraAngleLimitUp()				{ return this->fCameraAngleLimitUp; }					// カメラの回転角度制限取得(上)
		float	fGetCameraAngleLimitDown()				{ return this->fCameraAngleLimitDown; }					// カメラの回転角度制限取得(下)

		/* データ設定 */
		// 画面エフェクト
		void	SetScreenEffect(ScreenEffect_Base* pScreenEffect)	{ pScreenEffectList.emplace_back(pScreenEffect); };
		// ステージ状態
		void	SetGameStatus(int iGameStatus)		{ this->iGameStatus		= iGameStatus; };	// ゲーム状態を設定
		void	SetNowStageNo(int iNowStageNo)		{ this->iNowStageNo		= iNowStageNo; };	// ゲーム状態を設定
		void	SetEndStageNo(int iEndStageNo)		{ this->iEndStageNo		= iEndStageNo; };	// 最終ステージ番号を設定
		void	SetGameSlowFlg(bool bGameSlowFlg)	{ this->bGameSlowFlg	= bGameSlowFlg; };	// スローモーションフラグを設定		/*2025.02.05 スローモーションに関する菊池雅道 関数追加 */
		void	SetAddUiFlg(bool bAddUiFlg)			{ this->bAddUiFlg		= bAddUiFlg; };		// UI追加フラグ設定
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

	private:
		/* 管理するデータリスト */
		std::vector<ScreenEffect_Base*>	pScreenEffectList;	// 画面エフェクトリスト

		/* 管理するデータ */
		int		iGameStatus;	// ゲーム状態
		int		iNowStageNo;	// 現在のステージ番号
		int		iEndStageNo;	// 最終ステージ番号
		bool	bGameSlowFlg;	// スローモーションフラグ		/*2025.02.05 菊池雅道 変数追加 */
		bool	bAddUiFlg;		// UI追加フラグ

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
};
