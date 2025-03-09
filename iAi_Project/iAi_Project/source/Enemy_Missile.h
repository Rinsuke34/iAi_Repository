/* 2024.01.30 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "Enemy_Basic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeMissile.h"
#include "PlayerStatusDefine.h"

/* テスト用敵クラス */

// エネミーベースクラス
class Enemy_Missile : public Enemy_Basic
{
public:
	Enemy_Missile();				// コンストラクタ
	virtual ~Enemy_Missile();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:
	EffectManualDelete* pEffect;

	EffectManualDelete* pEffectHit;					//警告エフェクト

protected:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー

	void	MoveEnemy();					// 敵を移動させるメソッドを追加
	void	Player_Range_Missile_Shot();			// イクラ弾攻撃

	BulletEnemyRangeMissile* pBulletRangeMissile;	// ミサイル弾

	int		iFiringCount;	// 発射カウント

};
