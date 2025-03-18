/* 2025.03.13 菊池雅道 ファイル作成 */
#pragma once

/* オブジェクト */
#include "BulletPlayerKunai.h"

/* クナイ(爆発)クラスの宣言 */

// クナイ(爆発)
class BulletPlayerKunaiExplosion : public BulletPlayerKunai
{
public:
	BulletPlayerKunaiExplosion();				// コンストラクタ
	virtual ~BulletPlayerKunaiExplosion();		// デストラクタ

	virtual void	Initialization()	override;			// 初期化
	virtual void	Update()			override;			// 更新
	virtual void	Draw()				override;			// 描画	

	void	Explosion();								// 爆発処理
	
private:
	
protected:

};

