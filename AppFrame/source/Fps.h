/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include "DxLib.h"

/* フレームレート固定クラスの宣言 */

// フレームレート固定クラス
class Fps
{
	// どこでも使用可能
	public:
		// コンストラクタ(クラスが使用可能になったタイミングで実行する)
		Fps();

		bool FpsUpdate();				// 時刻計算
		void FpsWait();					// フレームレート調整のため待機

	// Fpsクラス内のみで使用可能
	private:
		int iStartTime;					// 測定開始時刻
		int iCount;						// カウンタ

	// Fpsクラスとその子クラスのみで使用可能
	protected:
};
