/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* 循環参照対策の先行定義 */
class DataList_Object;

/* エネミースポナーベースクラスの宣言 */

// エネミースポナーベースクラス
class EnemySpawnPoint_Base : public PlatformBase
{
	public:
		EnemySpawnPoint_Base();					// コンストラクタ
		virtual ~EnemySpawnPoint_Base() {};		// デストラクタ

		virtual void	Reset()	override;		// リセット処理

	protected:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;	// オブジェクト管理
};
