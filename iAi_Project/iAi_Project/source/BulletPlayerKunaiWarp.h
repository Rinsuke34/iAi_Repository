/* 2025.03.13 菊池雅道 ファイル作成 */
/* 2025.12.13 菊池雅道	コードリファクタリング */

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
		void	Warp();																												// ワープ処理
		void	Warp_ToTargetEnemy();																								// 敵ありワープ処理							//2025.12.13 菊池雅道 関数追加
		void	WarpPlayerBehindEnemy();																							// エネミー後方へワープする処理				//2025.12.13 菊池雅道 関数追加
		void	AdjustWarpPositionForPlatform(const VECTOR& vecEnemyPos, VECTOR& vecWarpOffset);									// 足場確認（敵あり）						//2025.12.13 菊池雅道 関数追加
		void	FinalizePlayerStateAfterWarp();																						// プレイヤー状態の後処理（敵あり）			//2025.12.13 菊池雅道 関数追加
		void	SetupKunaiAttackCollision();																						// ワープクナイ用当たり判定設定				//2025.12.13 菊池雅道 関数追加
		void	WarpToKunaiHitPosition();																							// 敵なしワープ処理							//2025.12.13 菊池雅道 関数追加
		void	AdjustWarpPositionWithoutEnemy(VECTOR& vecWarpPosition);															// 足場探索（敵なし）						//2025.12.13 菊池雅道 関数追加
		void	SearchNearbyPlatform(VECTOR& vecWarpPosition);																		// 近くのプラットフォームを探索する処理		//2025.12.13 菊池雅道 関数追加
		void	FinalizePlayerStateWithoutEnemy();																					// プレイヤー状態の後処理（敵なし）			//2025.12.13 菊池雅道 関数追加
		void	PlayWarpEffect();																									// ワープ演出処理							//2025.12.13 菊池雅道 関数追加
		void	HandleKunaiDeleteAfterAttack();																						// クナイ攻撃後の削除処理					//2025.12.13 菊池雅道 関数追加


	private:
		std::shared_ptr<Enemy_Basic> pTargetEnemy;						// クナイのターゲットエネミー

	protected:

};
