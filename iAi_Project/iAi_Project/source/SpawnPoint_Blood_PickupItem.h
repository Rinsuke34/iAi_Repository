/* 2025.03.14 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "SpawnPoint_Base.h"
#include "PickUpItem_Blood.h"

/* ブラッド(ピックアップアイテム)スポナークラスの宣言 */

// ブラッド(ピックアップアイテム)スポナークラス
class SpawnPoint_Blood_PickupItem : public SpawnPoint_Base
{
	public:
		SpawnPoint_Blood_PickupItem();						// コンストラクタ
		virtual ~SpawnPoint_Blood_PickupItem() {};			// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
