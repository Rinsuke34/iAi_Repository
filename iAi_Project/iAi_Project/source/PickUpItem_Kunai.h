/* 2025.03.2 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* オブジェクト */
#include "CharacterPlayer.h"

/* 循環参照対策(後ほど対策は実施) */
class DataList_Object;
class CharacterPlayer;

/* クナイ(ピックアップアイテム)クラスの宣言 */

// クナイ(ピックアップアイテム)クラス
class PickUpItem_Kunai : public PickUpItemBase
{
	public:
		PickUpItem_Kunai();				// コンストラクタ
		virtual ~PickUpItem_Kunai() {};	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Reset()				override;		// リセット処理

	private:
		/* データリスト */
		DataList_Object*		ObjectList;				// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;		// プレイヤー状態管理

		/* 変数 */
		CharacterPlayer*	pPlayer;					// プレイヤー
		int					iAddEffectDelay;			// エフェクト追加待機時間
};

