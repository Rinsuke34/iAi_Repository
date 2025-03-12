/* 2025.03.12 駒沢風助 ファイル作成 */

#ifndef SCREEN_EFFECT_SLOWMOTION_H
#define SCREEN_EFFECT_SLOWMOTION_H

#include "ScreenEffect_Base.h"

/* データリスト */
#include "DataList_StageStatus.h"

/* 画面エフェクト(スローモーション)クラスの宣言 */

// 画面エフェクト(スローモーション)クラス
class ScreenEffect_SlowMotion : public ScreenEffect_Base
{
	public:
		ScreenEffect_SlowMotion();				// コンストラクタ
		virtual ~ScreenEffect_SlowMotion() {};	// デストラクタ

		void	Update(int iGrHandle_Screen)			override;	// 更新
		void	ScreenEffectDraw(int iGrHandle_Screen)	override;	// 画面エフェクト描写

	private:
		/* 使用するデータリスト */
		DataList_StageStatus* StageStatusList;	// ステージ状態管理
};

#endif