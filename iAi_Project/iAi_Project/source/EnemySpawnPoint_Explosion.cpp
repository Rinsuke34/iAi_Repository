/* 2025.03.08 駒沢風助 ファイル作成 */

#include "EnemySpawnPoint_Explosion.h"

/* エネミー(自爆)スポナークラスの定義 */
// コンストラクタ
EnemySpawnPoint_Explosion::EnemySpawnPoint_Explosion() : EnemySpawnPoint_Base()
{

}

// 初期化
void EnemySpawnPoint_Explosion::Initialization()
{
	/* エネミー(自爆)生成処理 */
	{
		/* エネミー(自爆)を作成 */
		Enemy_Explosion* AddEnemy = new Enemy_Explosion();

		/* 生成したエネミー(自爆)をリストに追加 */
		this->ObjectList->SetEnemy(AddEnemy);

		/* 生成したエネミー(自爆)の座標を設定 */
		AddEnemy->SetPosition(this->vecPosition);

		/* 生成したエネミー(自爆)の回転量を設定 */
		AddEnemy->SetRotation(this->vecRotation);

		/* 生成したエネミー(自爆)の初期化処理 */
		AddEnemy->Initialization();
	}
}
