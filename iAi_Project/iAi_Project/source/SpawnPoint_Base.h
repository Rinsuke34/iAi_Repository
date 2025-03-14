/* 2025.03.08 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* 循環参照対策の先行定義 */
class DataList_Object;

/* スポナーベースクラスの宣言 */

// スポナーベースクラス
class SpawnPoint_Base : public PlatformBase
{
	public:
		SpawnPoint_Base();					// コンストラクタ
		virtual ~SpawnPoint_Base() {};		// デストラクタ

		virtual void	Reset()	override;		// リセット処理

	protected:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;	// オブジェクト管理
};
