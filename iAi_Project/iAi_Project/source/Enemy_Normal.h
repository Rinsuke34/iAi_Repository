/* 2024.01.29 石川智也 ファイル作成 */

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
class Enemy_Normal : public Enemy_Basic
{
public:
	Enemy_Normal();				// コンストラクタ
	virtual ~Enemy_Normal();		// デストラクタ

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
	void	Enemy_Model_Animation();			// エネミーモデルアニメーション

	//変数
	int		iFiringCount;	// 発射カウント

	int		iGuidanceCount;	// 誘導カウント

	//モーション関連変数
	int		iAttackAttachIndex;			// 攻撃モーションアタッチインデックス
	int		iAttackNowAttachIndex;		// 攻撃中モーションアタッチインデックス
	int		iAttackEndAttachIndex;		// 攻撃終了モーションアタッチインデックス
	int		iAttackEndLoopAttachIndex;	// 攻撃終了ループモーションアタッチインデックス
	bool	bEffectGenerated;							// 警告エフェクト生成フラグ
	bool	bAttackMotionFlg;			// 攻撃モーションフラグ
	bool	bAttackNowMotionFlg;		// 攻撃中モーションフラグ
	bool	bAttackEndMotionFlg;		// 攻撃終了モーションフラグ
	bool	bAttackEndLoopMotionFlg;	// 攻撃終了ループモーションフラグ
	float	fAttackTotalTime;			// 攻撃モーションの総時間
	float	fAttackNowTotalTime;		// 攻撃中モーションの総時間
	float	fAttackEndTotalTime;		// 攻撃終了モーションの総時間
	float	fAttackEndLoopTotalTime;	// 攻撃終了ループモーションの総時間
	float	fAttackPlayTime;			// 攻撃再生時間
	float	fAttackNowPlayTime;			// 攻撃中再生時間
	float	fAttackEndPlayTime;			// 攻撃終了再生時間
	float	fAttackEndLoopPlayTime;		// 攻撃終了ループ再生時間
	

protected:


};
