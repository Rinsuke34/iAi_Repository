/* 2024.01.28 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EnemyBasic.h"
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
	
	private:
		EffectManualDelete* eEffect;
	protected:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;			// オブジェクト管理
		void MoveEnemy(); // 敵を移動させるメソッドを追加

		int _lastTime; // 追加: _lastTime メンバー変数
};
