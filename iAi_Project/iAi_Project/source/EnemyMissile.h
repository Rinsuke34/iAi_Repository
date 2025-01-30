/* 2024.01.30 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeMissile.h"

/* テスト用敵クラス */

// エネミーベースクラス
class MissileEnemy : public EnemyBasic
{
public:
	MissileEnemy();				// コンストラクタ
	virtual ~MissileEnemy();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:
	EffectManualDelete* eEffect;
protected:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	void	MoveEnemy();					// 敵を移動させるメソッドを追加
	void	Player_Range_Missile();			// イクラ弾攻撃

	BulletEnemyRangeMissile* pBulletRangeMissile;	// 近接攻撃(弱)の弾

};
