/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "EnemySpawnPoint_Base.h"
#include "Enemy_Normal.h"

/* エネミー(ノーマル)スポナークラスの宣言 */

// エネミー(ノーマル)スポナークラス
class EnemySpawnPoint_Normal : public EnemySpawnPoint_Base
{
	public:
		EnemySpawnPoint_Normal();						// コンストラクタ
		virtual ~EnemySpawnPoint_Normal() {};			// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
