/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "SpawnPoint_Base.h"
#include "Enemy_Escape.h"

/* エネミー(逃走)スポナークラスの宣言 */

// エネミー(逃走)スポナークラス
class EnemySpawnPoint_Escape : public SpawnPoint_Base
{
	public:
		EnemySpawnPoint_Escape();					// コンストラクタ
		virtual ~EnemySpawnPoint_Escape() {};		// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
