/* 2025.03.08 駒沢風助 ファイル作成 */

#include "EnemySpawnPoint_Normal.h"

/* エネミー(ノーマル)スポナークラスの定義 */
// コンストラクタ
EnemySpawnPoint_Normal::EnemySpawnPoint_Normal() : EnemySpawnPoint_Base()
{

}

// 初期化
void EnemySpawnPoint_Normal::Initialization()
{
	/* エネミー(ノーマル)生成処理 */
	{
		/* エネミー(ノーマル)を作成 */
		NormalEnemy* AddEnemy = new NormalEnemy();

		/* 生成したエネミー(ノーマル)をリストに追加 */
		this->ObjectList->SetEnemy(AddEnemy);

		/* 生成したエネミー(ノーマル)の座標を設定 */
		AddEnemy->SetPosition(this->vecPosition);

		/* 生成したエネミー(ノーマル)の回転量を設定 */
		AddEnemy->SetRotation(this->vecRotation);

		/* 生成したエネミー(ノーマル)の初期化処理 */
		AddEnemy->Initialization();
	}
}
