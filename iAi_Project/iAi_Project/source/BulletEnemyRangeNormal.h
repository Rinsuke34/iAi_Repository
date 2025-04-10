/* 2025.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"
#include "EnemyBulletDefine.h"


/* ノーマル弾クラスの宣言 */

// ノーマル弾
class BulletEnemyRangeNormal : public BulletBase
{
public:
	BulletEnemyRangeNormal();				// コンストラクタ
	virtual ~BulletEnemyRangeNormal();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:

	/* エフェクト・使用するデータリスト */
	DataList_Object* ObjectList;						// オブジェクト管理
	EffectManualDelete* pEffect;						// エフェクト	

	/* 関数 */
	void BulletEnemyRangeNormalMove();					// ノーマル弾の移動処理

	/* 変数 */
	int iDurationCount;									// ノーマル弾の持続カウント
	int iBulletCount;									// ノーマル弾発射カウント
	int iEnemyNormalDurationCount;						//ノーマル弾の持続カウント

protected:

};
