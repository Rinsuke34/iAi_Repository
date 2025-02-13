/* 2025.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"
#include "EnemyBulletDefine.h"

/* ビームクラスの定義 */

// ビーム
class BulletEnemyRangeBeam : public BulletBase
{
public:
	BulletEnemyRangeBeam();				// コンストラクタ
	virtual ~BulletEnemyRangeBeam();		// デストラクタ

	virtual void	Initialization()	override;	// 初期化
	virtual void	Update()			override;	// 更新
	virtual void	CollisionDraw()		override;	// 当たり判定描写

private:
	/* オブジェクト(エフェクト)のハンドル */
	EffectManualDelete* pEffect;

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理

	/* 当たり判定 */
	COLLISION_CAPSULE stCollisionCapsule;	// カプセル型の当たり判定

	void BulletEnemyRangeBeamMove();	// ビームの移動処理

	int iChargeCount;		// ビームのチャージカウント	

	int iBulletCount;		// ビーム発射カウント

	int iEnemyBeamDurationCount;		//ビームの持続カウント

	VECTOR vecEnemyPosition; // エネミーの位置を保持するメンバ変数を追加

	VECTOR vecPlayerDirection; // プレイヤーの方向を保持するメンバ変数を追加

protected:

};
