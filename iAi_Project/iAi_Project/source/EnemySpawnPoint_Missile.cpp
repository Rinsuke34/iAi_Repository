/* 2025.03.08 駒沢風助 ファイル作成 */

#include "EnemySpawnPoint_Missile.h"

/* エネミー(ミサイル)スポナークラスの定義 */
// コンストラクタ
EnemySpawnPoint_Missile::EnemySpawnPoint_Missile() : SpawnPoint_Base()
{

}

// 初期化
void EnemySpawnPoint_Missile::Initialization()
{
	/* エネミー(ミサイル)生成処理 */
	{
		/* エネミー(ミサイル)を作成 */
		Enemy_Missile* AddEnemy = new Enemy_Missile();

		/* 生成したエネミー(ミサイル)をリストに追加 */
		this->ObjectList->SetEnemy(AddEnemy);

		/* 生成したエネミー(ミサイル)の座標を設定 */
		AddEnemy->SetPosition(this->vecPosition);

		/* 生成したエネミー(ミサイル)の回転量を設定 */
		AddEnemy->SetRotation(this->vecRotation);

		/* 生成したエネミー(ミサイル)の初期化処理 */
		AddEnemy->Initialization();
	}
}
