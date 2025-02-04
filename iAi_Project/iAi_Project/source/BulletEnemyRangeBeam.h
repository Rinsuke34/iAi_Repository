/* 2025.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"
#include "EnemyBulletDefine.h"


/* ビームクラスの宣言 */

// ビーム
class BulletEnemyRangeBeam : public BulletBase
{
public:
	BulletEnemyRangeBeam();				// コンストラクタ
	virtual ~BulletEnemyRangeBeam();		// デストラクタ

	virtual void	Initialization()	override;	// 初期化
	virtual void	Update()			override;	// 更新

private:
	/* オブジェクト(エフェクト)のハンドル */
	EffectManualDelete* pEffect;

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理


	void BulletEnemyRangeBeamMove();	// ビームの移動処理

	int iDurationCount;	// ビームの持続カウント

	int iBulletCount;		// ビーム発射カウント


	int iEnemyBeamDurationCount;		//ビームの持続カウント
protected:

};
