/* 2024.01.28 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "Enemy_Basic.h"
#include "EnemyDefine.h"
#include "EffectManualDelete.h"

/* テスト用敵クラス */

// エネミーベースクラス
class Enemy_Escape : public Enemy_Basic
{
	public:
		Enemy_Escape();				// コンストラクタ
		virtual ~Enemy_Escape();		// デストラクタ
	
		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
	virtual void	CollisionDraw()		override;	// 当たり判定描写
	private:
	/* エフェクト */
		EffectSelfDelete* pEffect;							// エフェクト

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理

	/* 関数 */
	void MoveEnemy();				// 敵を移動させるメソッドを追加
	void Enemy_Model_Animation();	// エネミーモデルアニメーション
	void Movement_Horizontal();		// 水平移動

	/* 変数 */
	int iXescapedistance;			// X軸の距離

	int iZescapedistance;			// Z軸の距離
	int iEscapespeed;			// 移動速度
	int iWaitCount;					// 待機カウント
	float fGravity;				// 重力
	bool	bHitEffectGenerated;						// ヒットエフェクト生成フラグ
	bool bDirectionFlg;										// 向き固定フラグ
	bool bEscapeEffectGenerated;	// 逃走エフェクト生成フラグ
	bool bWallHitFlg;				// 壁に当たったフラグ
	bool bWallFlg;					// 壁フラグ

	//モーション関係変数
	int iWaitAttachIndex;			// 待機モーションアタッチインデックス
	int iDieAttachIndex;			// 死亡モーションアタッチインデックス
	int	iRunAttachIndex;		// 走りモーションアタッチインデックス
	float fWaitTotalTime;			// 待機モーションの総時間
	float fDieTotalTime;			// 死亡モーションの総時間
	float fRunTotalTime;		// 走りモーションの総時間
	float fWaitPlayTime;			// 待機再生時間
	float fDiePlayTime;				// 死亡再生時間
	float fRunPlayTime;			// 走り再生時間


	VECTOR vecEscapeEffectPos;	// 逃走エフェクトの座標
protected:
	COLLISION_CAPSULE			stHorizontalCollision;		// 水平方向のコリジョン
	COLLISION_SQHERE			stSphere;					// 球のコリジョン
	VECTOR						vecNormalSum;				// プレイヤーに接触するオブジェクトの法線ベクトルの合計

	bool						bPlayeSeFlg;				// SEを再生開始したかのフラグ(ゲーム開始後に実行しないと他のシーン中に再生されるため)

};
