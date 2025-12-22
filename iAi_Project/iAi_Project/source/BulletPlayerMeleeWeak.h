/* 2025.01.24 駒沢風助 ファイル作成 */
/* 2025.02.20 菊池雅道 関数・変数追加 */
/* 2025.03.13 駒沢風助 弾パリィ作成 */
/* 2025.12.13 菊池雅道	コードリファクタリング */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_Effect.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "PlayerBulletDefine.h"
#include "DataList_Object.h"

/* 近接攻撃(弱)クラスの宣言 */

// 近接攻撃(弱)
class BulletPlayerMeleeWeak : public BulletBase
{
	public:
		BulletPlayerMeleeWeak();				// コンストラクタ
		virtual ~BulletPlayerMeleeWeak();		// デストラクタ

		virtual void	Initialization()	override;											// 初期化
		virtual void	Update()			override;											// 更新
		void			ArrengementPositionPlayerFront();										// 座標設定								/* 2025.02.20 菊池雅道 関数追加 */
		void			HandleParryBullet();													// 弾パリィ処理							/* 2025.12.13 菊池雅道 関数追加 */
		void			HandleCounterParry(std::shared_ptr <BulletBase> bullet);				// カウンター有効時の処理				/* 2025.12.13 菊池雅道 関数追加 */
		void			HandleNormalParry(std::shared_ptr <BulletBase> bullet);					// カウンター無効時の処理（吸収)		/* 2025.12.13 菊池雅道 関数追加 */
		void			CreateCounterHitEffect();												// カウンターエフェクト生成処理			/* 2025.12.13 菊池雅道 関数追加 */
		void			UpdateDeleteCount();													// 削除カウント更新処理					/* 2025.12.13 菊池雅道 関数追加 */
		void			UpdateEffectTransform();												//エフェクトの座標更新処理				/* 2025.12.13 菊池雅道 関数追加 */
		void 			UpdateCollisionPosition();												// 当たり判定の位置更新処理				/* 2025.12.13 菊池雅道 関数追加 */	

	private:
		/* 使用するデータリスト */
		std::shared_ptr<DataList_PlayerStatus>	PlayerStatusList;			// プレイヤー状態				/* 2025.02.20 菊池雅道 変数追加 */
		std::shared_ptr<DataList_Object>		ObjectList;					// オブジェクト管理				/* 2025.03.13 駒沢風助 弾パリィ作成 */ 
		std::shared_ptr<DataList_Effect>		EffectList;					// エフェクト管理				/* 2025.03.13 駒沢風助 弾パリィ作成 */

		/* オブジェクト(エフェクト)のハンドル */
		std::shared_ptr<EffectManualDelete> pMeleeWeakEffect;				// 近接攻撃(弱)エフェクト

		/* 追従対象のプレイヤークラス */
		std::shared_ptr<CharacterBase> pCharacterPlayer;													/* 2025.02.20 菊池雅道 変数追加 */

		int iDeleteCount;	// 削除カウント

	protected:
};
