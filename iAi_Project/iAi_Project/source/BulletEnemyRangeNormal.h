/* 2025.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"


/* 近接攻撃(弱)クラスの宣言 */

// 近接攻撃(弱)
class BulletEnemyRangeNormal : public BulletBase
{
public:
	BulletEnemyRangeNormal();				// コンストラクタ
	virtual ~BulletEnemyRangeNormal();		// デストラクタ

	virtual void	Initialization()	override;	// 初期化
	virtual void	Update()			override;	// 更新

private:
	/* オブジェクト(エフェクト)のハンドル */
	EffectManualDelete* eEffect;

	int iDeleteCount;	// 仮追加の削除カウント

protected:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理


	void BulletEnemyRangeNormalMove();	// 敵の弾の移動処理
};
