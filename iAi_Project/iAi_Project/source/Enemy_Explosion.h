/* 2024.12.15 駒沢風助 ファイル作成 */

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
class ExplosionEnemy : public EnemyBasic
{
public:
	ExplosionEnemy();				// コンストラクタ
	virtual ~ExplosionEnemy();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:
	/* エフェクト */
	EffectManualDelete* pEffect;

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理


	/*関数*/
	void MoveEnemy(); // 敵を移動させるメソッドを追加


	/*変数*/
	int iXdistance;			// X軸の距離

	int iZdistance;			// Z軸の距離

	float fSpeed;			// 移動速度

	int iDetonationRange;	//起爆範囲内

	int iLastTime;			//起爆タイマー

protected:
};
