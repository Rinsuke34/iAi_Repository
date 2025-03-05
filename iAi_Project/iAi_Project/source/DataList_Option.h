/* 2025.03.05 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include "PublicInclude.h"

/* オプション設定管理クラスの宣言 */

// オプション設定管理クラス
class DataList_Option : public DataListBase
{
	public:
		DataList_Option();					// コンストラクタ
		virtual ~DataList_Option() {};		// デストラクタ

		/* データ取得 */
		bool	bGetCameraInversion(int iInputType, int iAxis)		{ return this->abCameraInversion[iInputType][iAxis]; }		// カメラ反転設定取得
		float	fGetCameraSensitivity(int iInputType, int iAxis)	{ return this->afCameraSensitivity[iInputType][iAxis]; }	// カメラ感度設定取得

		/* データ設定 */
		void	SetCameraInversion(int iInputType, int iAxis, bool bCameraInversion)		{ this->abCameraInversion[iInputType][iAxis] = bCameraInversion; }		// カメラ反転設定
		void	SetCameraSensitivity(int iInputType, int iAxis, float fCameraSensitivity)	{ this->afCameraSensitivity[iInputType][iAxis] = fCameraSensitivity; }	// カメラ感度設定

	private:
		/* 管理するデータ */
		// 入力設定
		bool	abCameraInversion[INPUT_TYPE_MAX][INPUT_CAMERA_MODE_MAX];		// カメラ反転設定(入力タイプ/軸)
		float	afCameraSensitivity[INPUT_TYPE_MAX][AXIS_MAX];					// カメラ感度設定(倍率)(入力タイプ/軸)

		// サウンド設定
		int		iBgmVolume;			// BGMの音量(0 ～ 255)
		int		iSeVolume;			// SEの音量(0 ～ 255)
		int		iVoiceVolume;		// ボイスの音量(0 ～ 255)

		// その他
		bool	bTutorialMassage;	// チュートリアルメッセージ表示
};
