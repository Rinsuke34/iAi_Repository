/* 2024.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "Enemy_Basic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeBeam.h"
#include "PlayerStatusDefine.h"

/* テスト用敵クラス */

// エネミーベースクラス
class Enemy_Beam : public Enemy_Basic
{
public:
	Enemy_Beam();				// コンストラクタ
	virtual ~Enemy_Beam();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:

	//エフェクト
	EffectManualDelete* pEffectWarning;					//警告エフェクト

	BulletEnemyRangeBeam* pBulletRangeBeam;				// ビーム

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー


	//関数
	void	MoveEnemy();					// 敵を移動させるメソッドを追加
	void	Player_Range_Beam_Shot();			// ビームの発射


	//変数
	int		iFiringCount;	// 発射カウント

	int		iDurationCount;	// ビームの持続カウント

	int		iChargeCount;	// ビームのチャージカウント

	bool	bEffectGenerated;							// 警告エフェクト生成フラグ
protected:


};
