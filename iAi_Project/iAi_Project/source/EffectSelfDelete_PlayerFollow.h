/* 2025.02.05 駒沢風助 ファイル作成 */

#pragma once
#include "EffectSelfDelete.h"

/* データリスト */
#include "DataList_Object.h"
#include "PlayerStatusDefine.h"

/* 時間経過で削除されるエフェクトクラスの宣言 */
// ※プレイヤーに自動追従

// エフェクトクラス(自動削除/プレイヤー追従)
class EffectSelfDelete_PlayerFollow : public EffectSelfDelete
{
	public:
		EffectSelfDelete_PlayerFollow(bool bCenterFollowFlg);	// コンストラクタ
		virtual ~EffectSelfDelete_PlayerFollow() {};			// デストラクタ

		void	Update()			override;	// 更新

	private:
		/* 追従対象のプレイヤークラス */
		CharacterBase* pCharacterPlayer;

		/* 変数 */
		bool bCenterFollowFlg;		// 足元ではなく中央に追従するかのフラグ
};
