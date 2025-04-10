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

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー
	BulletEnemyRangeMissile* pBulletRangeMissile;		// ミサイル弾
	EffectManualDelete* pEffectHit;						//ヒットエフェクト
	EffectManualDelete* pEffectWarning;					//警告エフェクト

	//関数
	void	MoveEnemy();					// 敵を移動させるメソッドを追加
	void	Player_Range_Missile_Shot();				// ミサイル弾攻撃
	void	Enemy_Model_Animation();					// エネミーモデルアニメーション

	//変数
	int		iFiringCount;	// 発射カウント
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool	bDirectionFlg;								// 向き固定フラグ
	bool	bShotFlg;									// ショットフラグ
	bool	bWarningEffectFlg;							// 警告エフェクトフラグ


	//モーション関連変数
	int		iMissileAttackAttachIndex;					// ミサイル攻撃モーションアタッチインデックス
	int		iMissileAttackNowAttachIndex;				// ミサイル攻撃中モーションアタッチインデックス
	int		iMissileAttackEndAttachIndex;				// ミサイル攻撃終了モーションアタッチインデックス
	int		iMissileAttackEndLoopAttachIndex;			// ミサイル攻撃終了ループモーションアタッチインデックス
	int		iDieAttachIndex;							// 死亡モーションアタッチインデックス
	bool	bMissileAttackMotionFlg;					// ミサイル攻撃モーションフラグ
	bool	bMissileAttackNowMotionFlg;					// ミサイル攻撃中モーションフラグ
	bool	bMissileAttackEndMotionFlg;					// ミサイル攻撃終了モーションフラグ
	bool	bMissileAttackEndLoopMotionFlg;				// ミサイル攻撃終了ループモーションフラグ
	float	fMissileAttackTotalTime;					// ミサイル攻撃モーションの総時間
	float	fMissileAttackNowTotalTime;					// ミサイル攻撃中モーションの総時間
	float	fMissileAttackEndTotalTime;					// ミサイル攻撃終了モーションの総時間
	float	fMissileAttackEndLoopTotalTime;				// ミサイル攻撃終了ループモーションの総時間
	float	fDieTotalTime;								// 死亡モーションの総時間
	float	fMissileAttackPlayTime;						// ミサイル攻撃再生時間
	float	fMissileAttackNowPlayTime;					// ミサイル攻撃中再生時間
	float	fMissileAttackEndPlayTime;					// ミサイル攻撃終了再生時間
	float	fMissileAttackEndLoopPlayTime;				// ミサイル攻撃終了ループ再生時間
	float	fDiePlayTime;								// 死亡再生時間

protected:

};
