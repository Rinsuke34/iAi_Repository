/* 2025.02.05 駒沢風助 ファイル作成 */

#pragma once
#include "EffectManualDelete.h"

/* データリスト */
#include "DataList_Object.h"
#include "PlayerStatusDefine.h"

/* 手動で削除タイミングを設定するエフェクトクラスの宣言 */
// ※プレイヤーに自動追従

// エフェクトクラス(手動削除/プレイヤー追従)
class EffectManualDelete_PlayerFollow : public EffectManualDelete
{
	public:
		EffectManualDelete_PlayerFollow(bool bCenterFollowFlg);		// コンストラクタ
		virtual ~EffectManualDelete_PlayerFollow() {};				// デストラクタ

		void	Update() override;	// 更新

	private:
		/* 追従対象のプレイヤークラス */
		CharacterBase* pCharacterPlayer;

		/* 変数 */
		bool bCenterFollowFlg;		// 足元ではなく中央に追従するかのフラグ
};
