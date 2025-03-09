/* 2025.03.08 駒沢風助 ファイル作成 */

#include "EnemySpawnPoint_Escape.h"

/* エネミー(逃走)スポナークラスの定義 */
// コンストラクタ
EnemySpawnPoint_Escape::EnemySpawnPoint_Escape() : EnemySpawnPoint_Base()
{

}

// 初期化
void EnemySpawnPoint_Escape::Initialization()
{
	/* エネミー(逃走)生成処理 */
	{
		/* エネミー(逃走)を作成 */
		EscapeEnemy* AddEnemy = new EscapeEnemy();

		/* 生成したエネミー(逃走)をリストに追加 */
		this->ObjectList->SetEnemy(AddEnemy);

		/* 生成したエネミー(逃走)の座標を設定 */
		AddEnemy->SetPosition(this->vecPosition);

		/* 生成したエネミー(逃走)の回転量を設定 */
		AddEnemy->SetRotation(this->vecRotation);

		/* 生成したエネミー(逃走)の初期化処理 */
		AddEnemy->Initialization();
	}
}
