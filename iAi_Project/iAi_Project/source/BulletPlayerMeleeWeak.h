/* 2025.01.24 駒沢風助 ファイル作成 */
/* 2025.02.20 菊池雅道 関数・変数追加 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_Effect.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "PlayerBulletDefine.h"

/* 近接攻撃(弱)クラスの宣言 */

// 近接攻撃(弱)
class BulletPlayerMeleeWeak : public BulletBase
{
	public:
		BulletPlayerMeleeWeak();							// コンストラクタ
		virtual ~BulletPlayerMeleeWeak();					// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		void			ArrengementPositionPlayerFront();	// 座標設定						/* 2025.02.20 菊池雅道 関数追加 */

	private:
		/* 使用するデータリスト */
		DataList_PlayerStatus* PlayerStatusList;			// プレイヤー状態				/* 2025.02.20 菊池雅道 変数追加 */

		/* オブジェクト(エフェクト)のハンドル */
		EffectManualDelete* pMeleeWeakEffect;				// 近接攻撃(弱)エフェクト

		/* 追従対象のプレイヤークラス */
		CharacterBase* pCharacterPlayer;													/* 2025.02.20 菊池雅道 変数追加 */

		int iDeleteCount;	// 仮追加の削除カウント

	protected:
};
