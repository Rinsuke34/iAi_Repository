/* 2025.01.30 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "EnemyBulletDefine.h"
#include "PlayerStatusDefine.h"


/*ミサイル弾クラスの宣言 */

// ミサイル弾
class BulletEnemyRangeMissile : public BulletBase
{
public:
	BulletEnemyRangeMissile();				// コンストラクタ
	virtual ~BulletEnemyRangeMissile();		// デストラクタ

	virtual void	Initialization()	override;	// 初期化
	virtual void	Update()			override;	// 更新

private:

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー


	/* オブジェクト(エフェクト)のハンドル */
	EffectManualDelete* pEffect;//ミサイル弾のエフェクト

	EffectManualDelete* pEffectExplosion;//ミサイル弾着弾エフェクト


	void BulletEnemyRangeMissileMove();	// ミサイル弾の移動処理

	int iDurationCount;			// 弾の持続カウント

	int iBulletUPCount;			// ミサイル弾打ち上げカウント

	int iBulletDownCount;		// ミサイル弾打ち下げカウント

	int iBulletGuidanceCount;	// ミサイル誘導カウント


	int iEnemyMissileDurationCount;	//ミサイル弾の持続カウント

protected:
};
