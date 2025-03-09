/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "EnemySpawnPoint_Base.h"
#include "EnemyBeam.h"

/* エネミー(ビーム)スポナークラスの宣言 */

// エネミー(ビーム)スポナークラス
class EnemySpawnPoint_Beam : public EnemySpawnPoint_Base
{
	public:
		EnemySpawnPoint_Beam();					// コンストラクタ
		virtual ~EnemySpawnPoint_Beam() {};		// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
