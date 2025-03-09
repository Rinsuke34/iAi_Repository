/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "EnemySpawnPoint_Base.h"
#include "Enemy_Explosion.h"

/* エネミー(自爆)スポナークラスの宣言 */

// エネミー(自爆)スポナークラス
class EnemySpawnPoint_Explosion : public EnemySpawnPoint_Base
{
	public:
		EnemySpawnPoint_Explosion();				// コンストラクタ
		virtual ~EnemySpawnPoint_Explosion() {};	// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
