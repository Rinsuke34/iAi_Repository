/* 2024.12.15 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EnemyBasic.h"
#include "EnemyDefine.h"
#include "EffectManualDelete.h"
#include "CharacterPlayer.h"

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

	//起爆エフェクト
	EffectManualDelete* pEffectDetonation;

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理


	DataList_PlayerStatus* PlayerStatusList;	// プレイヤー状態
	/*関数*/
	void MoveEnemy(); // 敵を移動させるメソッドを追加
	void Enemy_Gravity(); // 重力処理メソッドを追加
	void CliffFallCheck();	// 崖に落ちるかどうかの判定メソッドを追加


	/*変数*/
	int iXdistance;			// X軸の距離

	int iZdistance;			// Z軸の距離
	int iDetonationRange;			//起爆範囲内
	int iBlastRange;				//爆発範囲内
	int iStopCount;			// 停止カウント
	float fSpeed;			// 移動速度
	float fGravity;						// 重力


	bool bEffectGenerated;	// 起爆予告エフェクト生成フラグ
	bool bFallFlg;			// 落下フラグ
	bool bStopFlg;			// 停止フラグ
	bool bCountFlg;			//カウントフラグ
	bool bBlastFlg;			//爆発フラグ


	VECTOR vecLastRotation;	// 最後の回転量
protected:
	COLLISION_LINE		stVerticalCollision;			// 垂直方向のコリジョン

	VECTOR				vecMove;				// 移動量
};
