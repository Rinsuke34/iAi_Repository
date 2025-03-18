/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* オブジェクト */
#include "SpawnPoint_Base.h"
#include "Enemy_Missile.h"
#include "Enemy_Fixed.h"
#include "Enemy_Fixed_Turret.h"

/* エネミー(ミサイル)スポナークラスの宣言 */

// エネミー(ミサイル)スポナークラス
class EnemySpawnPoint_Missile : public SpawnPoint_Base
{
	public:
		EnemySpawnPoint_Missile();					// コンストラクタ
		virtual ~EnemySpawnPoint_Missile() {};		// デストラクタ

		virtual void	Initialization() override;	// 初期化
};
