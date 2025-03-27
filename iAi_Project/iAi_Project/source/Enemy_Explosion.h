/* 2024.12.15 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_Effect.h"
#include "DataList_StageStatus.h"

/* オブジェクト */
#include "Enemy_Basic.h"
#include "EnemyDefine.h"
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"

/* テスト用敵クラス */

// エネミーベースクラス
class Enemy_Explosion : public Enemy_Basic
{
public:
	Enemy_Explosion();				// コンストラクタ
	virtual ~Enemy_Explosion();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新
	virtual void	CollisionDraw()		override;	// 当たり判定描写

private:
	/* エフェクト */
	EffectManualDelete* pEffect; 						// エフェクト
	EffectManualDelete* pEffectDetonation;				// 起爆エフェクト
	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	DataList_Effect* EffectList;			// エフェクト管理
	DataList_StageStatus* StageStatusList;	// ステージ状態


	DataList_PlayerStatus* PlayerStatusList;	// プレイヤー状態
	/*関数*/
	void MoveEnemy(); // 敵を移動させるメソッドを追加
	void Enemy_Gravity();									// 重力処理メソッドを追加
	void Movement_Horizontal();		// 水平移動



	/*変数*/
	int iXdistance;			// X軸の距離

	int iZdistance;			// Z軸の距離
	int iDetonationRange;			//起爆範囲内
	int iBlastRange;				//爆発範囲内
	int iStopCount;			// 停止カウント
	int iReturnCount;				// 戻るカウント
	float fSpeed;			// 移動速度
	float fGravity;						// 重力


	bool bEffectGenerated;	// 起爆予告エフェクト生成フラグ
	bool bFallFlg;			// 落下フラグ
	bool bStopFlg;			// 停止フラグ
	bool bCountFlg;			//カウントフラグ
	bool bBlastFlg;			//爆発フラグ
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool bDirectionFlg;								// 向き固定フラグ
	bool bChaseFlg;								// 追跡フラグ
	bool bSavePositionFlg;							// 座標保存フラグ
	bool bFallNowFlg;
	

	//モーション関連変数
	int iWaitAttachIndex;						// 待機モーションアタッチインデックス
	int iRunAttachIndex;						// 走りモーションアタッチインデックス
	int iExplosionAttachIndex;					// 爆発モーションアタッチインデックス
	int iDieAttachIndex;						// 死亡モーションアタッチインデックス
	float fWaitTotalTime;						// 待機モーションの総時間
	float fRunTotalTime;						// 走りモーションの総時間
	float fExplosionTotalTime;					// 爆発モーションの総時間
	float fDieTotalTime;						// 死亡モーションの総時間
	float fWaitPlayTime;						// 待機再生時間
	float fRunPlayTime;							// 走り再生時間
	float fExplosionPlayTime;					// 爆発再生時間
	float fDiePlayTime;							// 死亡再生時間


	VECTOR vecLastRotation;	// 最後の回転量
	VECTOR vecStartPosition;	// 初期座標
protected:
	COLLISION_CAPSULE		stHorizontalCollision;			// 水平方向のコリジョン
};
