/* 2024.02.10 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_Image.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "PlayerStatusDefine.h"
#include "GimmickDefine.h"

/*シーン*/
#include "SceneStage.h"
#include "SceneTitle.h"

/* テスト用敵クラス */

// 消失ギミッククラス
class Screen : public PlatformBase
{
	public:
		Screen();				// コンストラクタ
		virtual ~Screen();		// デストラクタ

		virtual void	Update()			override;		// 更新
	
	private:
		/* 使用するデータリスト */
		DataList_Object*	ObjectList;	// オブジェクト管理
		CharacterBase*		pPlayer;	// プレイヤー

		/* 関数 */
		void	Process();				// 更新
		void	Draw();					// 描画

		/* テクスチャハンドル */
		int iTextureTitleHandle;		// タイトル
		int iTextureNewgameHandle;		// ニューゲーム
		int iTextureContinueHandle;		// コンティニュー
		int iTextureDateHandle;			// データ
		int iTextureConfigHandle;		// コンフィグ
		int iTextureStageHandle;		// ステージ

		bool bStartFlg;					//スタートフラグ	
		bool bHomeFlg;					//ホームフラグ
		bool bGameStartFlg;				//ゲームスタートフラグ

		int iUICount;					//UIのカウント
};
