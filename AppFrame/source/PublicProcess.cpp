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
	// 戻り値
	// float	<- 範囲内に収めた値

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

// 閾値を超えているか確認
bool PUBLIC_PROCESS::bCheckAboveThreshold(unsigned char ucValue, unsigned char ucThreshold)
{
	// 引数
	// ucValue		<- 確認する値
	// ucThreshold	<- 閾値
	// 戻り値
	// bool			<- 閾値を超えているか(true:超えている、false:超えていない)

	bool bReturn = false;

	/* 閾値を超えているか確認 */
	if (ucValue > ucThreshold)
	{
		// 閾値を超えているなら
		/* trueを返す */
		bReturn = true;
	}

	return bReturn;
}

// アナログスティックの入力を正規化(±1)
float PUBLIC_PROCESS::fAnalogStickNorm(short sMouseMove)
{
	// 引数
	// sMouseMove	<- 正規化したいアナログスティックの入力
	// 戻り値
	// float		<- 正規化した値(±1の範囲)


	/* 入力値を±1の範囲へ正規化 */
	return (float)sMouseMove / 32767.f;
}

/* 2025.01.21 菊池雅道 デッドゾーン処理追加 開始*/
// 入力値がデッドゾーンの範囲内であるか確認
bool PUBLIC_PROCESS::bCheckInputDeadzone(float fInput, float fDeadzone)
{
	// 引数
	// fInput		<- 確認する値
	// fDeadzone	<- デッドゾーン
	// 戻り値
	// bool			<- デッドゾーンの範囲内であるか(true:範囲内である、false:範囲内ではない)

	bool bReturn = false;

	/* デッドゾーンの範囲内であるか確認 */
	if ((-fDeadzone < fInput) && (fInput < +fDeadzone))
	{
		// デッドゾーンの範囲内なら
		/* trueを返す */
		bReturn = true;
	}
	else
	{
		bReturn = false;
	}

	return bReturn;

}
/* 2025.01.21 菊池雅道 デッドゾーン処理追加 終了*/

// 2つの線分の交点を取得
VECTOR PUBLIC_PROCESS::vecGetLineCrossPoint(VECTOR vecLineAStart, VECTOR vecLineADirection, VECTOR vecLineBStart, VECTOR vecLineBDirection)
{
	// 引数
	// vecLineAStart		<- 線分Aの始点
	// vecLineADirection	<- 線分Aの方向
	// vecLineBStart		<- 線分Bの始点
	// vecLineBDirection	<- 線分Bの方向

	VECTOR vecReturn;

	/* 直線が平行であるか確認 */
	VECTOR vecGetLineCrossPoint	= VCross(vecLineADirection, vecLineBDirection);		// 外積
	float fCrossSize = VSize(vecGetLineCrossPoint);									// 外積の大きさ

	/* 直線が平行でないか確認 */
	if (fCrossSize == 0.f)
	{
		// 平行である場合
		/* 交点を取得できないため、始点を返す */
		vecReturn = vecLineAStart;
		return vecReturn;
	}

	// パラメータ t1 を計算
	VECTOR diff = VSub(vecLineBStart, vecLineAStart);

	// パラメータ t1 の内積を計算
	float t1 = VDot(diff, VCross(vecLineBDirection, vecGetLineCrossPoint)) / (fCrossSize * fCrossSize);

	// 直線1上の交点を計算
	return VAdd(vecLineAStart, VScale(vecLineADirection, t1));
}