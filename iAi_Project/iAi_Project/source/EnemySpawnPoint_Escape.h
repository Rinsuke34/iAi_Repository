/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "EnemySpawnPoint_Base.h"
#include "EnemyEscape.h"

/* エネミー(逃走)スポナークラスの宣言 */

// エネミー(逃走)スポナークラス
class EnemySpawnPoint_Escape : public EnemySpawnPoint_Base
{
	public:
		EnemySpawnPoint_Escape();					// コンストラクタ
		virtual ~EnemySpawnPoint_Escape() {};		// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
