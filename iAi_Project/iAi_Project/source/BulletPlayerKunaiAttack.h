/* 2025.03.13 菊池雅道 ファイル作成 */
#pragma once

/* オブジェクト */
#include "BulletPlayerKunai.h"

/* クナイ(攻撃)クラスの宣言 */

// クナイ(攻撃)
class BulletPlayerKunaiAttack : public BulletPlayerKunai
{
public:
	BulletPlayerKunaiAttack();				// コンストラクタ
	virtual ~BulletPlayerKunaiAttack();		// デストラクタ

	virtual void	Initialization()	override;			// 初期化
	virtual void	Update()			override;			// 更新
	virtual void	Draw()				override;			// 描画	

	void	Attack();								// 攻撃処理
	

private:
	
protected:

};

