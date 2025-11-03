/* 2025.03.13 菊池雅道 ファイル作成 */
#pragma once

/* オブジェクト */
#include "BulletPlayerKunai.h"

/* クナイ(攻撃)クラスの宣言 */

// クナイ(攻撃)
class BulletPlayerKunaiWarp : public BulletPlayerKunai
{
	public:
		BulletPlayerKunaiWarp();				// コンストラクタ
		virtual ~BulletPlayerKunaiWarp();		// デストラクタ

		virtual void	Initialization()	override;			// 初期化
		virtual void	Update()			override;			// 更新
		virtual void	Draw()				override;			// 描画	

		void	SetKunaiTargetEnemy(std::shared_ptr<Enemy_Basic> pTargetEnemy) { this->pTargetEnemy = pTargetEnemy; }				// クナイのターゲットエネミーを設定
		void	Warp();																								// ワープ処理

	private:
		std::shared_ptr<Enemy_Basic> pTargetEnemy;						// クナイのターゲットエネミー

	protected:

};
