/* 2024.02.10 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* オブジェクト */
#include "Gimmick_ForcedJump_Spawn.h"
#include "CharacterPlayer.h"

/* 循環参照対策(後ほど対策は実施) */
class DataList_Object;
class Gimmick_ForcedJump_Spawn;
class CharacterPlayer;

/* 強制ジャンプアイテム(ギミック)クラスの宣言 */

// 強制ジャンプアイテム(ギミック)クラス
class PickUpItem_ForcedJump : public PickUpItemBase
{
	public:
		PickUpItem_ForcedJump();			// コンストラクタ
		virtual ~PickUpItem_ForcedJump();	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	BloomDraw()			override {};	// 発光描写

		/* データ設定 */
		void SetGimmick_ForcedJump_Spawn(Gimmick_ForcedJump_Spawn* pGimmick_ForcedJump_Spawn) { this->pGimmick_ForcedJump_Spawn = pGimmick_ForcedJump_Spawn; };		// 強制ジャンプギミックスポナー(自身の生成元)を設定

	private:
		/* データリスト */
		DataList_Object* ObjectList;				// オブジェクト管理
		DataList_PlayerStatus* PlayerStatusList;	// プレイヤー状態

		/* 変数 */
		CharacterPlayer*			pPlayer;					// プレイヤー
		Gimmick_ForcedJump_Spawn*	pGimmick_ForcedJump_Spawn;	// 強制ジャンプギミックスポナー(自身の生成元)

	//エフェクト
	EffectManualDelete* pEffectExplosion;	// 爆発エフェクト

};

