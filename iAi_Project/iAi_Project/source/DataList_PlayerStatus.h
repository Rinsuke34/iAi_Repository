/* 2024.12.26 駒沢風助 ファイル作成 */

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
		// 基本ステータス関連
		
		// カメラ関連
		VECTOR	vecGetCameraUp()				{ return this->vecCameraUp; };				// カメラの上方向取得
		VECTOR	vecGetCameraPosition()			{ return this->vecCameraPosition; };		// カメラの座標取得
		VECTOR	vecGetCameraTarget()			{ return this->vecCameraTarget; };			// カメラの注視点取得
		float	fGetCameraRadius()				{ return this->fCameraRadius; };			// カメラの中心点からの距離取得
		float	fGetCameraAngleX()				{ return this->fCameraAngleX; };			// カメラのX軸回転量取得
		float	fGetCameraAngleY()				{ return this->fCameraAngleY; };			// カメラのY軸回転量取得
		float	fGetCameraRotationalSpeed()		{ return this->fCameraRotationalSpeed; };	// カメラの回転速度取得
		float	fGetCameraAngleLimitUp()		{ return this->fCameraAngleLimitUp; };		// カメラの回転角度制限取得(上)
		float	fGetCameraAngleLimitDown()		{ return this->fCameraAngleLimitDown; };	// カメラの回転角度制限取得(下)

		/* データ設定 */
		// 基本ステータス関連

		// カメラ関連
		void	SetCameraUp(VECTOR vecCameraUp)								{ this->vecCameraUp				= vecCameraUp; };				// カメラの上方向設定
		void	SetCameraPosition(VECTOR vecCameraPosition)					{ this->vecCameraPosition		= vecCameraPosition; };			// カメラの座標設定
		void	SetCameraTarget(VECTOR vecCameraTarget)						{ this->vecCameraTarget			= vecCameraTarget; };			// カメラの注視点設定
		void	SetCameraRadius(float fCameraRadius)						{ this->fCameraRadius			= fCameraRadius; };				// カメラの中心点からの距離設定
		void	SetCameraAngleX(float fCameraAngleX)						{ this->fCameraAngleX			= fCameraAngleX; };				// カメラのX軸回転量設定
		void	SetCameraAngleY(float fCameraAngleY)						{ this->fCameraAngleY			= fCameraAngleY; };				// カメラのY軸回転量設定
		void	SetCameraRotationalSpeed(float fCameraRotationalSpeed)		{ this->fCameraRotationalSpeed	= fCameraRotationalSpeed; };	// カメラの回転速度設定
		void	SetCameraAngleLimitUp(float fCameraAngleupsideLimitUp)		{ this->fCameraAngleLimitUp		= fCameraAngleLimitUp; };		// カメラの回転角度制限設定(上)
		void	SetCameraAngleLimitDown(float fCameraAngleupsideLimitDown)	{ this->fCameraAngleLimitDown	= fCameraAngleLimitDown; };		// カメラの回転角度制限設定(下)

	private:
		/* 基本ステータス関連 */

		/* カメラ関連 */
		VECTOR	vecCameraUp;				// カメラの上方向
		VECTOR	vecCameraPosition;			// カメラの座標
		VECTOR	vecCameraTarget;			// カメラの注視点
		float	fCameraRadius;				// カメラの中心点からの距離(ズーム量)
		float	fCameraAngleX;				// カメラのX軸回転量
		float	fCameraAngleY;				// カメラのY軸回転量
		float	fCameraRotationalSpeed;		// カメラの回転速度
		float	fCameraAngleLimitUp;		// カメラの回転角度制限(上)
		float	fCameraAngleLimitDown;		// カメラの回転角度制限(下)

	protected:
};
