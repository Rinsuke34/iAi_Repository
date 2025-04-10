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

/* 固定砲台エネミー土台部分クラス */

// エネミーフィックスクラス
class Enemy_Fixed : public Enemy_Basic
{
public:
	Enemy_Fixed();				// コンストラクタ
	virtual ~Enemy_Fixed();		// デストラクタ

	virtual void	Initialization()	override;		// 初期化
	virtual void	Update()			override;		// 更新

private:


	/* 使用するデータリスト */
	DataList_Object* ObjectList;						// オブジェクト管理

	//関数
	void	MoveEnemy();								// 敵を移動させるメソッドを追加

	//変数
	int		iModelturretHandle;							// モデルハンドル
	int		iModelscaffoldHandle;						// モデルハンドル




protected:


};
