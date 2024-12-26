/* 2024.12.25 駒沢風助 ファイル作成 */

#pragma once

#include "AppFunctionDefine.h"

/* 汎用的に使用できる計算式の定義 */

// 値を範囲内に収める
float PUBLIC_PROCESS::fClamp(float fValue, float fMax, float fMin)
{
	// 引数
	// fValue	<- 範囲内に収める値
	// fMax		<- 最大値
	// fMin		<- 最小値

	float fReturn = fValue;

	/* 最大値より大きいか確認 */
	if (fValue > fMax)
	{
		// 最大値より大きいなら
		/* 最大値に設定する */
		fReturn = fMax;
	}

	/* 最小値より小さいか確認 */
	if (fValue < fMin)
	{
		// 最小値より小さいなら
		/* 最小値に設定する */
		fReturn = fMin;
	}

	return fReturn;
}