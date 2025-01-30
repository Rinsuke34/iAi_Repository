/* 2024.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeNormal.h"

/* テスト用敵クラス */

// エネミーベースクラス
class NormalEnemy : public EnemyBasic
{
public:
	NormalEnemy();				// コンストラクタ
	virtual ~NormalEnemy();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:
	EffectManualDelete* eEffect;
protected:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	void	MoveEnemy();					// 敵を移動させるメソッドを追加
	void	Player_Range_Normal();			// イクラ弾攻撃

	BulletEnemyRangeNormal* pBulletRangeNormal;	// 近接攻撃(弱)の弾

};
