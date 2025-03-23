/* 2025.03.22 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "SpawnPoint_Base.h"
#include "PickUpItem_Kunai.h"

/* クナイ(ピックアップアイテム)スポナークラスの宣言 */

// クナイ(ピックアップアイテム)スポナークラス
class SpawnPoint_Kunai_PickupItem : public SpawnPoint_Base
{
	public:
		SpawnPoint_Kunai_PickupItem();						// コンストラクタ
		virtual ~SpawnPoint_Kunai_PickupItem() {};			// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
