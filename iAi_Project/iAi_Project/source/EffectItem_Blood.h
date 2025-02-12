/* 2025.02.11 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "EffectItem_BloodDefine.h"

/* シーン */
#include "DataList_Object.h"
#include "DataList_GameResource.h"

/* 循環参照対策(後ほど対策は実施) */
class DataList_Object;

/* ブラッド(ゲーム内通貨)クラスの宣言 */
// ※ 所持量等を管理するのではなく、主に演出で使用する

// ブラッドクラス
class EffectItem_Blood : public EffectItemBase
{
	public:
		EffectItem_Blood();				// コンストラクタ
		virtual ~EffectItem_Blood();	// デストラクタ

		virtual void	Update()		override;	// 更新
		virtual void	Draw()			override;	// 描写

		/* データ設定 */
		void	SetMoveDirection(VECTOR vecMoveDirection) { this->vecMoveDirection = vecMoveDirection; }	// 移動方向を設定

	private:
		/* データリスト */
		DataList_Object* ObjectList;			// オブジェクト管理

		/* 関数 */

		/* 変数 */
		VECTOR	vecMoveDirection;		// 移動方向
		int		iMoveCount;				// 移動カウント
		int		iMoveFaze;				// 移動フェーズ
};

