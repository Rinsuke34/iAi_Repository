/* 2024.01.29 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* オブジェクト */
#include "Enemy_Basic.h"
#include "EffectManualDelete.h"
#include "BulletEnemyRangeNormal.h"
#include "PlayerStatusDefine.h"

/* 地上ノーマルエネミークラス */

// エネミーノーマルクラス
class Enemy_Normal : public Enemy_Basic
{
public:
	Enemy_Normal();				// コンストラクタ
	virtual ~Enemy_Normal();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:

	/* エフェクト・使用するオブジェクトリスト */
	DataList_Object* ObjectList;						// オブジェクト管理
	CharacterBase* pPlayer;								// プレイヤー
	EffectManualDelete* pEffectWarning;					//警告エフェクト
	BulletEnemyRangeNormal* pBulletRangeNormal;			// ノーマル弾
	EffectManualDelete* pEffectHit;						//ヒットエフェクト

	//関数
	void	MoveEnemy();								// 敵を移動させるメソッドを追加
	void	Player_Range_Normal_Shot();					// ノーマル弾の発射
	void	Enemy_Model_Animation();					// エネミーモデルアニメーション

	//変数
	int		iFiringCount;								// 発射カウント
	int		iGuidanceCount;								// 誘導カウント
	bool	bEffectGenerated;							// 警告エフェクト生成フラグ
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool	bDirectionFlg;								// 向き固定フラグ
	bool	bWarningEffectFlg;							// 警告エフェクトフラグ
	bool	bShotFlg;									// ショットフラグ
	
	//モーション関連変数
	int		iNormalAttackAttachIndex;					// 攻撃モーションアタッチインデックス
	int		iNormalAttackNowAttachIndex;				// 攻撃中モーションアタッチインデックス
	int		iNormalAttackEndAttachIndex;				// 攻撃終了モーションアタッチインデックス
	int		iNormalAttackEndLoopAttachIndex;			// 攻撃終了ループモーションアタッチインデックス
	int		iDieAttachIndex;							// 死亡モーションアタッチインデックス
	bool	bNormalAttackMotionFlg;						// 攻撃モーションフラグ
	bool	bNormalAttackNowMotionFlg;					// 攻撃中モーションフラグ
	bool	bNormalAttackEndMotionFlg;					// 攻撃終了モーションフラグ
	bool	bNormalAttackEndLoopMotionFlg;				// 攻撃終了ループモーションフラグ
	float	fNormalAttackTotalTime;						// 攻撃モーションの総時間
	float	fNormalAttackNowTotalTime;					// 攻撃中モーションの総時間
	float	fNormalAttackEndTotalTime;					// 攻撃終了モーションの総時間
	float	fNormalAttackEndLoopTotalTime;				// 攻撃終了ループモーションの総時間
	float	fDieTotalTime;								// 死亡モーションの総時間
	float	fNormalAttackPlayTime;						// 攻撃再生時間
	float	fNormalAttackNowPlayTime;					// 攻撃中再生時間
	float	fNormalAttackEndPlayTime;					// 攻撃終了再生時間
	float	fNormalAttackEndLoopPlayTime;				// 攻撃終了ループ再生時間
	float	fDiePlayTime;								// 死亡再生時間

protected:


};
