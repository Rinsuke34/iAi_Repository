/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "SpawnPoint_Base.h"
#include "Enemy_Beam.h"

/* エネミー(ビーム)スポナークラスの宣言 */

// エネミー(ビーム)スポナークラス
class EnemySpawnPoint_Beam : public SpawnPoint_Base
{
	public:
		EnemySpawnPoint_Beam();					// コンストラクタ
		virtual ~EnemySpawnPoint_Beam() {};		// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
