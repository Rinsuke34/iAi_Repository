/* 2025.03.08 駒沢風助 ファイル作成 */

#include "EnemySpawnPoint_Beam.h"

/* エネミー(ビーム)スポナークラスの定義 */
// コンストラクタ
EnemySpawnPoint_Beam::EnemySpawnPoint_Beam() : EnemySpawnPoint_Base()
{

}

// 初期化
void EnemySpawnPoint_Beam::Initialization()
{
	/* エネミー(ビーム)生成処理 */
	{
		/* エネミー(ビーム)を作成 */
		BeamEnemy* AddEnemy = new BeamEnemy();

		/* 生成したエネミー(ビーム)をリストに追加 */
		this->ObjectList->SetEnemy(AddEnemy);

		/* 生成したエネミー(ビーム)の座標を設定 */
		AddEnemy->SetPosition(this->vecPosition);

		/* 生成したエネミー(ビーム)の回転量を設定 */
		AddEnemy->SetRotation(this->vecRotation);

		/* 生成したエネミー(ビーム)の初期化処理 */
		AddEnemy->Initialization();
	}
}
