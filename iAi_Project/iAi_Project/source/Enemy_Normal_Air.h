/* 2024.03.13 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "Enemy_Basic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeNormal.h"
#include "PlayerStatusDefine.h"

/* テスト用敵クラス */

// エネミーベースクラス
class Enemy_Normal_Air : public Enemy_Basic
{
public:
	Enemy_Normal_Air();										// コンストラクタ
	virtual ~Enemy_Normal_Air();							// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:

	EffectManualDelete* pEffectWarning;					//警告エフェクト

	BulletEnemyRangeNormal* pBulletRangeNormal;			// ノーマル弾

	EffectManualDelete* pEffectHit;						//ヒットエフェクト

	/* 使用するデータリスト */
	DataList_Object* ObjectList;						// オブジェクト管理
	CharacterBase* pPlayer;								// プレイヤー

	//関数
	void	MoveEnemy();								// 敵を移動させるメソッドを追加
	void	Player_Range_Normal_Shot();					// ノーマル弾の発射

	//変数
	int		iFiringCount;								// 発射カウント
	int		iGuidanceCount;								// 誘導カウント
	bool	bEffectGenerated;							// 警告エフェクト生成フラグ
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool	bDirectionFlg;								// 向き固定フラグ

	//モーション関連変数
	int		iNormalAirAttachIndex;						// 空中モーションアタッチインデックス
	int		iDieAttachIndex;							// 死亡モーションアタッチインデックス
	float	fNormalAirTotalTime;						// 空中モーションの総時間
	float	fDieTotalTime;								// 死亡モーションの総時間
	float	fNormalAirPlayTime;							// 空中再生時間
	float	fDiePlayTime;								// 死亡再生時間

protected:
};
