/* 2025.01.30 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "EffectManualDelete.h"


/* 近接攻撃(弱)クラスの宣言 */

// 近接攻撃(弱)
class BulletEnemyRangeMissile : public BulletBase
{
public:
	BulletEnemyRangeMissile();				// コンストラクタ
	virtual ~BulletEnemyRangeMissile();		// デストラクタ

	virtual void	Initialization()	override;	// 初期化
	virtual void	Update()			override;	// 更新

private:
	/* オブジェクト(エフェクト)のハンドル */
	EffectManualDelete* eEffect;

	int iDeleteCount;	// 仮追加の削除カウント

protected:
	DataList_Object* ObjectList;			// オブジェクト管理
	void BulletEnemyRangeMissileMove();	// 敵の弾の移動処理
};
