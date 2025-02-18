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
#include "PlayerStatusDefine.h"

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
	//EffectManualDelete* pEffect;

	EffectManualDelete* pEffectWarning;					//警告エフェクト

	BulletEnemyRangeNormal* pBulletRangeNormal;			// ノーマル弾


	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー

	//関数
	void	MoveEnemy();					// 敵を移動させるメソッドを追加
	void	Player_Range_Normal_Shot();			// ノーマル弾の発射


	//変数
	int		iFiringCount;	// 発射カウント

	int		iGuidanceCount;	// 誘導カウント

	int		iModelFootHandle;	// エネミー足元モデルハンドル

	bool	bEffectGenerated;							// 警告エフェクト生成フラグ
	

protected:


};
