/* 2024.01.28 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EnemyBasic.h"
#include "EnemyDefine.h"
#include "EffectManualDelete.h"

/* テスト用敵クラス */

// エネミーベースクラス
class EscapeEnemy : public EnemyBasic
{
	public:
		EscapeEnemy();				// コンストラクタ
		virtual ~EscapeEnemy();		// デストラクタ
	
		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
	virtual void	CollisionDraw()		override;	// 当たり判定描写
	private:
	/* エフェクト */
	EffectManualDelete* pEffect;

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理

	/* 関数 */
	void MoveEnemy(); // 敵を移動させるメソッドを追加
	void Enemy_Gravity(); // 重力処理メソッドを追加

	/* 変数 */
	int iXescapedistance;			// X軸の距離

	int iZescapedistance;			// Z軸の距離
	int iEscapespeed;			// 移動速度
	float fGravity;				// 重力


	VECTOR vecEscapeEffectPos;	// 逃走エフェクトの座標
protected:
	COLLISION_LINE		stVerticalCollision;			// 垂直方向のコリジョン

	VECTOR				vecMove;				// 移動量

};
