/* 2025.02.12 駒沢風助 ファイル作成 */

#pragma once
#include "CharacterBase.h"

/* すべての実体のあるアイテムのベースとなるクラスの宣言 */

// 実体ありアイテムクラス
class PickUpItemBase : public CharacterBase
{
	public:
		PickUpItemBase();				// コンストラクタ
		virtual ~PickUpItemBase() {};	// デストラクタ

	private:
	protected:

};
