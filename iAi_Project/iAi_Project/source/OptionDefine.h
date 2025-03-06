/* 2025.03.06 駒沢風助 ファイル作成 */

#pragma once
#include <string>

/* オプション関連の構造体や定数の宣言を行う */

/* オプション関連の最大、最小値 */
static const float	OPTION_CAMERA_SENSITIVITY_MIN	=	0.1f;	// カメラ感度の最小値
static const float	OPTION_CAMERA_SENSITIVITY_MAX	=	10.f;	// カメラ感度の最大値
static const float	OPTION_CAMERA_SENSITIVITY_STEP	=	0.1f;	// カメラ感度の変更量
static const float	OPTION_SOUND_VOLUME_MIN			=	0.f;	// サウンドの音量の最小値
static const float	OPTION_SOUND_VOLUME_MAX			=	255.f;	// サウンドの音量の最大値
static const float	OPTION_SOUND_VOLUME_STEP		=	1.f;	// サウンドの音量の変更量

/* オプション名(Jsonファイル内) */
// カメラ系
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL	= "CameraInversion_Controller_Normal";		// カメラ反転設定(コントローラー/通常時)
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM	= "CameraInversion_Controller_Aim";			// カメラ反転設定(コントローラー/エイム時)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL		= "CameraInversion_Mouse_Normal";			// カメラ反転設定(マウス/通常時)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_AIM			= "CameraInversion_Mouse_Aim";				// カメラ反転設定(マウス/エイム時)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X	= "CameraSensitivity_Controller_X";			// カメラ感度倍率(コントローラー/X軸)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y	= "CameraSensitivity_Controller_Y";			// カメラ感度倍率(コントローラー/Y軸)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_X			= "CameraSensitivity_Mouse_X";				// カメラ感度倍率(マウス/X軸)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y			= "CameraSensitivity_Mouse_Y";				// カメラ感度倍率(マウス/Y軸)
// サウンド系
const std::string OPTION_NAME_BGMVOLUME							= "Bgm_Volume";								// BGMの音量( 0 ～ 255 )
const std::string OPTION_NAME_SEVOLUME							= "Se_Volume";								// SEの音量( 0 ～ 255 )
const std::string OPTION_NAME_VOICEVOLUME						= "Voice_Volume";							// ボイスの音量( 0 ～ 255 )
// その他
const std::string OPTION_NAME_TUTORIALMESSAGE					= "TutorialMassage";						// チュートリアルメッセージ表示

/* オプション名(日本語) */
// カメラ系
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_NORMAL_JP	= "カメラ反転設定(コントローラー/通常時)";		// カメラ反転設定(コントローラー/通常時)
const std::string OPTION_NAME_CAMERAINVERSION_CONTROLLER_AIM_JP		= "カメラ反転設定(コントローラー/エイム時)";	// カメラ反転設定(コントローラー/エイム時)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_NORMAL_JP		= "カメラ反転設定(マウス/通常時)";				// カメラ反転設定(マウス/通常時)
const std::string OPTION_NAME_CAMERAINVERSION_MOUSE_AIM_JP			= "カメラ反転設定(マウス/エイム時)";			// カメラ反転設定(マウス/エイム時)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_X_JP		= "カメラ感度倍率(コントローラー/X軸)";			// カメラ感度倍率(コントローラー/X軸)
const std::string OPTION_NAME_CAMERASENSITIVITY_CONTROLLER_Y_JP		= "カメラ感度倍率(コントローラー/Y軸)";			// カメラ感度倍率(コントローラー/Y軸)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_X_JP			= "カメラ感度倍率(マウス/X軸)";					// カメラ感度倍率(マウス/X軸)
const std::string OPTION_NAME_CAMERASENSITIVITY_MOUSE_Y_JP			= "カメラ感度倍率(マウス/Y軸)";					// カメラ感度倍率(マウス/Y軸)
// サウンド系
const std::string OPTION_NAME_BGMVOLUME_JP							= "BGMの音量";									// BGMの音量( 0 ～ 255 )
const std::string OPTION_NAME_SEVOLUME_JP							= "SEの音量";									// SEの音量( 0 ～ 255 )
const std::string OPTION_NAME_VOICEVOLUME_JP						= "ボイスの音量";								// ボイスの音量( 0 ～ 255 )
// その他
const std::string OPTION_NAME_TUTORIALMESSAGE_JP					= "チュートリアルメッセージ表示";				// チュートリアルメッセージ表示

/* ファイルパス */
const std::string FILE_PATH_OPTION = "resource/SetupData/OptionData.json";

/* オプションリスト */
struct OPTION_LIST
{
	std::string	Name_Json;			// 名称(Jsonファイル内)
	std::string	Name;				// 名称(日本語)
	void*		pValue;				// 変数(※std::variantが使用出来ないので危険だがこの方法で関数を取得する)
	std::string	Type;				// データ型
	float		fMin;				// 最小値(データ型に応じてキャストして使用する / bool型は未使用)
	float		fMax;				// 最大値(データ型に応じてキャストして使用する / bool型は未使用)
	float		fStepValue;			// 変更量(データ型に応じてキャストして使用する / bool型は未使用)
};
