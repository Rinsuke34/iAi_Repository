/* 2025.03.14 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_GameResource.h"
#include "DataList_PlayerStatus.h"

/* オブジェクト */
#include "CharacterPlayer.h"

/* ブラッド(ゲーム内通貨/ピックアップアイテム)クラスの宣言 */

// ブラッド(ゲーム内通貨/ピックアップアイテム)クラス
class PickUpItem_Blood : public PickUpItemBase
{
	public:
		PickUpItem_Blood();				// コンストラクタ
		virtual ~PickUpItem_Blood() {};	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Reset()				override;		// リセット処理

	private:
		/* データリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_GameResource*	GameResourceList;	// ゲーム内リソース管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態

		/* 変数 */
		CharacterPlayer*	pPlayer;					// プレイヤー
		int					iAddEffectDelay;			// エフェクト追加待機時間
};

