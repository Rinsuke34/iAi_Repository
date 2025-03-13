/* 2024.03.13 石川智也 ファイル作成 */

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
class Enemy_Missile_Air : public Enemy_Basic
{
public:
	Enemy_Missile_Air();									// コンストラクタ
	virtual ~Enemy_Missile_Air();							// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:

	/* 使用するデータリスト */
	DataList_Object* ObjectList;						// オブジェクト管理
	CharacterBase* pPlayer;								// プレイヤー
	BulletEnemyRangeMissile* pBulletRangeMissile;		// ミサイル弾
	EffectManualDelete* pEffectHit;						//警告エフェクト

	//関数
	void	MoveEnemy();								// 敵を移動させるメソッドを追加
	void	Player_Range_Missile_Shot();				// ミサイル弾攻撃

	//変数
	int		iFiringCount;								// 発射カウント
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool	bDirectionFlg;								// 向き固定フラグ


	//モーション関連変数
	int		iMissileAirAttachIndex;						// 空中モーションアタッチインデックス
	int		iDieAttachIndex;							// 死亡モーションアタッチインデックス
	float	fNormalAirTotalTime;						// 空中モーションの総時間
	float	fDieTotalTime;								// 死亡モーションの総時間
	float	fNormalAirPlayTime;							// 空中再生時間
	float	fDiePlayTime;								// 死亡再生時間

protected:

};
