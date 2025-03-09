/* 2025.03.05 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include "PublicInclude.h"
#include "OptionDefine.h"

/* オプション設定管理クラスの宣言 */

// オプション設定管理クラス
class DataList_Option : public DataListBase
{
	public:
		DataList_Option();					// コンストラクタ
		virtual ~DataList_Option() {};		// デストラクタ

		/* jsonファイル関連 */
		void	LoadOptionData();			// オプションデータ読み込み
		void	SaveOptionData();			// オプションデータ保存

		/* データ取得 */
		bool	bGetCameraInversion(int iInputType, int iAxis)		{ return this->abCameraInversion[iInputType][iAxis]; }		// カメラ反転設定取得
		float	fGetCameraSensitivity(int iInputType, int iAxis)	{ return this->afCameraSensitivity[iInputType][iAxis]; }	// カメラ感度設定取得
		float	fGetEnemyDrawDistance()								{ return this->fEnemyDrawDistance; }						// エネミー描写距離取得
		int		iGetBgmVolume()										{ return this->iBgmVolume; }								// BGMの音量取得
		int		iGetSeVolume()										{ return this->iSeVolume; }									// SEの音量取得
		int		iGetVoiceVolume()									{ return this->iVoiceVolume; }								// ボイスの音量取得
		bool	bGetTutorialMassage()								{ return this->bTutorialMassage; }							// チュートリアルメッセージ表示取得

		/* データ設定 */
		void	SetCameraInversion(int iInputType, int iAxis, bool bCameraInversion)		{ this->abCameraInversion[iInputType][iAxis]	= bCameraInversion; }		// カメラ反転設定
		void	SetCameraSensitivity(int iInputType, int iAxis, float fCameraSensitivity)	{ this->afCameraSensitivity[iInputType][iAxis]	= fCameraSensitivity; }		// カメラ感度設定
		void	SetEnemyDrawDistance(float fEnemyDrawDistance)								{ this->fEnemyDrawDistance						= fEnemyDrawDistance; }		// エネミー描写距離設定
		void	SetBgmVolume(int iBgmVolume)												{ this->iBgmVolume								= iBgmVolume; }				// BGMの音量設定
		void	SetSeVolume(int iSeVolume)													{ this->iSeVolume								= iSeVolume; }				// SEの音量設定
		void	SetVoiceVolume(int iVoiceVolume)											{ this->iVoiceVolume							= iVoiceVolume; }			// ボイスの音量設定
		void	SetTutorialMassage(bool bTutorialMassage)									{ this->bTutorialMassage						= bTutorialMassage; }		// チュートリアルメッセージ表示設定

		/* オプションリストのポインタ取得 */
		std::vector<OPTION_LIST>* stGetOptionNameList() { return &this->astOptionNameList; }						// オプション名リスト取得

	private:
		/* 管理するデータ */
		// 入力設定
		bool	abCameraInversion[INPUT_TYPE_MAX][INPUT_CAMERA_MODE_MAX];		// カメラ反転設定(入力タイプ/カメラ状態)
		float	afCameraSensitivity[INPUT_TYPE_MAX][AXIS_MAX];					// カメラ感度設定(倍率)(入力タイプ/軸)
		float	fEnemyDrawDistance;
		// サウンド設定
		int		iBgmVolume;			// BGMの音量(0 ～ 255)
		int		iSeVolume;			// SEの音量(0 ～ 255)
		int		iVoiceVolume;		// ボイスの音量(0 ～ 255)
		// その他
		bool	bTutorialMassage;	// チュートリアルメッセージ表示

		/* Jsonファイルでのオプション名と変数の対応表 */
		// ※ オプション項目を追加する場合はここに追加する
		std::vector<OPTION_LIST> astOptionNameList =
		{
			/* オプション名(Json内),							オプション名(日本語),									対応した変数(ポインタ),													データ型,			最小値,							最大値,							変更量 */
			// カメラ系
			{ OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL,	OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL_JP,		&abCameraInversion[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_NORMAL],	DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM,		OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM_JP,			&abCameraInversion[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_AIM],		DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL,			OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL_JP,			&abCameraInversion[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_NORMAL],			DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERAINVERSION_MOUSE_AIM,			OPTION_NAME_CAMERAINVERSION_MOUSE_AIM_JP,				&abCameraInversion[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_AIM],			DATA_TYPE_BOOL,		0.f,							0.f,							0.f								},
			{ OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X,		OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X_JP,			&afCameraSensitivity[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_NORMAL],	DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y,		OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y_JP,			&afCameraSensitivity[INPUT_TYPE_CONTROLLER][INPUT_CAMERA_MODE_AIM],		DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_CAMERASENSITIVITY_MOUSE_X,			OPTION_NAME_CAMERASENSITIVITY_MOUSE_X_JP,				&afCameraSensitivity[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_NORMAL],		DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y,			OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y_JP,				&afCameraSensitivity[INPUT_TYPE_MOUSE][INPUT_CAMERA_MODE_AIM],			DATA_TYPE_FLOAT,	OPTION_CAMERA_SENSITIVITY_MIN,	OPTION_CAMERA_SENSITIVITY_MAX,	OPTION_CAMERA_SENSITIVITY_STEP	},
			{ OPTION_NAME_ENEMY_DRAW_DISTANCE,					OPTION_NAME_ENEMY_DRAW_DISTANCE_JP,						&fEnemyDrawDistance,													DATA_TYPE_FLOAT,	OPTION_ENEMY_DRAW_DISTANCE_MIN,	OPTION_ENEMY_DRAW_DISTANCE_MAX,	OPTION_ENEMY_DRAW_DISTANCE_STEP	},
			// サウンド系
			{ OPTION_NAME_BGMVOLUME,							OPTION_NAME_BGMVOLUME_JP,								&iBgmVolume,															DATA_TYPE_INT,		OPTION_SOUND_VOLUME_MIN,		OPTION_SOUND_VOLUME_MAX,		OPTION_SOUND_VOLUME_STEP		},
			{ OPTION_NAME_SEVOLUME,								OPTION_NAME_SEVOLUME_JP,								&iSeVolume,																DATA_TYPE_INT,		OPTION_SOUND_VOLUME_MIN,		OPTION_SOUND_VOLUME_MAX,		OPTION_SOUND_VOLUME_STEP		},
			{ OPTION_NAME_VOICEVOLUME,							OPTION_NAME_VOICEVOLUME_JP,								&iVoiceVolume,															DATA_TYPE_INT,		OPTION_SOUND_VOLUME_MIN,		OPTION_SOUND_VOLUME_MAX,		OPTION_SOUND_VOLUME_STEP		},
			// その他
			{ OPTION_NAME_TUTORIALMESSAGE,						OPTION_NAME_TUTORIALMESSAGE_JP,							&bTutorialMassage,														DATA_TYPE_BOOL,		0.f,							0.f,							0.f								}
		};
};
