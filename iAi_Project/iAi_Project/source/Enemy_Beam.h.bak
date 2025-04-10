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
	void	Enemy_Model_Animation();					// エネミーモデルアニメーション
	void	Charge();									// チャージ


	//変数
	int		iFiringCount;	// 発射カウント

	int		iDurationCount;	// ビームの持続カウント

	int		iChargeCount;	// ビームのチャージカウント
	int		iBeamDurationCount;						//ビームの持続カウント
	bool	bEffectGenerated;							// 警告エフェクト生成フラグ
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool	bChargeFlg;									// チャージフラグ
	bool	bFiringFlg;									// 発射フラグ
	bool	bDirectionFlg;								// 向き固定フラグ
	bool	bBeamSEFlg;									// ビームSEフラグ
	bool	bShotFlg;									// ショットフラグ	
	bool	bWarningEffectFlg;							// 警告エフェクトフラグ

	//モーション関連変数
	int		iBeamAttackAttachIndex;						// ビーム攻撃モーションアタッチインデックス
	int		iBeamAttackNowAttachIndex;					// ビーム攻撃中モーションアタッチインデックス
	int		iBeamAttackEndAttachIndex;					// ビーム攻撃終了モーションアタッチインデックス
	int		iBeamAttackEndLoopAttachIndex;				// ビーム攻撃終了ループモーションアタッチインデックス
	int		iDieAttachIndex;							// 死亡モーションアタッチインデックス
	bool	bBeamAttackMotionFlg;						// ビーム攻撃モーションフラグ
	bool	bBeamAttackNowMotionFlg;					// ビーム攻撃中モーションフラグ
	bool	bBeamAttackEndMotionFlg;					// ビーム攻撃終了モーションフラグ
	bool	bBeamAttackEndLoopMotionFlg;				// ビーム攻撃終了ループモーションフラグ
	float	fBeamAttackTotalTime;						// ビーム攻撃モーションの総時間
	float	fBeamAttackNowTotalTime;					// ビーム攻撃中モーションの総時間
	float	fBeamAttackEndTotalTime;					// ビーム攻撃終了モーションの総時間
	float	fBeamAttackEndLoopTotalTime;				// ビーム攻撃終了ループモーションの総時間
	float	fDieTotalTime;								// 死亡の持続時間
	float	fBeamAttackPlayTime;						// ビーム攻撃再生時間
	float	fBeamAttackNowPlayTime;						// ビーム攻撃中再生時間
	float	fBeamAttackEndPlayTime;						// ビーム攻撃終了再生時間
	float	fBeamAttackEndLoopPlayTime;					// ビーム攻撃終了ループ再生時間
	float	fDiePlayTime;								// 死亡再生時間
protected:


};
