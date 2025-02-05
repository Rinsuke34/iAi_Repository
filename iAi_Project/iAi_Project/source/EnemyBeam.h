/* 2024.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeBeam.h"
#include "PlayerStatusDefine.h"

/* テスト用敵クラス */

// エネミーベースクラス
class BeamEnemy : public EnemyBasic
{
public:
	BeamEnemy();				// コンストラクタ
	virtual ~BeamEnemy();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:
	EffectManualDelete* pEffect;
	EffectManualDelete* pEffectWarning;


	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー

	void	MoveEnemy();					// 敵を移動させるメソッドを追加
	void	Player_Range_Beam_Shot();			// ビームの発射

	BulletEnemyRangeBeam* pBulletRangeBeam;	// ビーム

	int		iFiringCount;	// 発射カウント

	int		iGuidanceCount;	// 誘導カウント

	VECTOR vecWarning;

	int		iModelFootHandle;	// エネミー足元モデルハンドル
protected:


};
