/* 2024.03.17 石川智也 ファイル作成 */

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
#include "BulletEnemyRangeMissile.h"
/* テスト用敵クラス */

// エネミーベースクラス
class Enemy_Fixed_Turret : public Enemy_Basic
{
public:
	Enemy_Fixed_Turret();				// コンストラクタ
	virtual ~Enemy_Fixed_Turret();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新
	virtual void	Draw()				override;		// 描写

private:

	EffectManualDelete* pEffectWarning;					//警告エフェクト

	BulletEnemyRangeNormal* pBulletRangeNormal;			// ノーマル弾
	BulletEnemyRangeMissile* pBulletRangeMissile;		// ミサイル弾

	EffectManualDelete* pEffectHit;						//ヒットエフェクト

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー

	VECTOR vecEffectPos; // エフェクトの座標

	//関数
	void	MoveEnemy();					// 敵を移動させるメソッドを追加

	//変数
	int		iFiringCount;	// 発射カウント
	int		iGuidanceCount;	// 誘導カウント
	int		iModelturretHandle;	// モデルハンドル
	int		iModelscaffoldHandle;	// モデルハンドル
	int		iMaintainCount;	// 維持カウント
	int		iEffectWaitCount;	// エフェクト待機カウント

	float fTargetAngle;	// ターゲットの角度
	float fCurrentAngle;	// 現在の角度
	float fAngleDifference;	// 角度の差

	bool	bEffectGenerated;							// 警告エフェクト生成フラグ
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool	bDirectionFlg;								// 向き固定フラグ
	bool	bWarningEffectFlg;							// 警告エフェクトフラグ
	bool	bShotFlg;									// ショットフラグ
	bool	bUpFlg;										// 上フラグ
	bool	bDownFlg;									// 下フラグ
	bool	bMissile;									// ミサイルフラグ
	bool bTestFlg;									// テストフラグ
	bool bTestFlg2;									// テストフラグ2
	bool bTestFlg3;									// テストフラグ3




protected:


};
