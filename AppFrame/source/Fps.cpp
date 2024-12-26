/* 2024.12.08 駒沢風助 ファイル作成 */

#include <math.h>
#include "DxLib.h"
#include "Fps.h"
#include "AppVariableDefine.h"
#include "AppConstantDefine.h"

/* フレームレート固定クラスの定義 */

// コンストラクタ(クラスが使用可能になったタイミングで実行する)
Fps::Fps()
{
	/* 変数の初期化 */
	this->iStartTime	= 0;	// 測定開始時刻	
	this->iCount		= 0;	// カウンタ
}

// 時刻計算
bool Fps::FpsUpdate()
{
	/* カウンタの確認 */
	if (this->iCount == 0)
	{
		// 1フレーム目であるなら
		/* 時刻を取得 */
		this->iStartTime = GetNowCount();
	}
	if (this->iCount == FRAME_RATE::FPS_RATE)
	{
		// フレームレート設定値であるなら
		/* 現在時刻を取得 */
		int t = GetNowCount();

		/* 現在のフレームレートを取得 */
		giNowFps	= (int)(1000.f / ((t - iStartTime) / (float)FRAME_RATE::FPS_RATE));

		/* カウンタ、開始時刻を更新 */
		this->iCount		= 0;
		this->iStartTime	= t;
	}

	/* カウンタの加算 */
	this->iCount++;

	return true;
}

// フレームレート調整のため待機
void Fps::FpsWait()
{
	/* フレームレート設定値までにかかった時間の取得 */
	int iTookTime = GetNowCount() - this->iStartTime;

	/* 待機する時間を算出 */
	int iWaitTime = this->iCount * 1000 / FRAME_RATE::FPS_RATE - iTookTime;
	if (iWaitTime > 0)
	{
		/* 必要であるならば待機を行う */
		Sleep(iWaitTime);
	}
}
