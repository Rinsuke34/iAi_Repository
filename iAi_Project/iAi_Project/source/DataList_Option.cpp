/* 2025.03.05 駒沢風助 ファイル作成 */

#include "DataList_Option.h"

/* オプション設定管理クラスの定義 */
// コンストラクタ
DataList_Option::DataList_Option() : DataListBase("DataList_Option")
{
	/* 初期化(仮) */
	abCameraInversion[0][0] = false;
	abCameraInversion[0][1] = false;
	abCameraInversion[1][0] = false;
	abCameraInversion[1][1] = false;

	afCameraSensitivity[0][0] = 1.f;
	afCameraSensitivity[0][1] = 0.5f;
	afCameraSensitivity[1][0] = 1.f;
	afCameraSensitivity[1][1] = 0.5f;
}
