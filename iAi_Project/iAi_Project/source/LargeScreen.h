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


// タイトル専用縦スクリーンクラス
class LargeScreen : public PlatformBase
{
public:
	LargeScreen();				// コンストラクタ
	virtual ~LargeScreen();		// デストラクタ

	virtual void	Update()			override;		// 更新


private:

	/* 使用するデータリスト */
	DataList_Object* ObjectList;						// オブジェクト管理
	CharacterBase* pPlayer;								// プレイヤー

	/* 関数 */
	void	Process();									// 処理

	/* 変数 */
	int iTextureTitleHandle;							// タイトル
	int iTextureNewgameHandle;							// ニューゲーム
	int iTextureContinueHandle;							// コンティニュー
	int iTextureDateHandle;								// データ
	int iTextureConfigHandle;							// コンフィグ
	int iTextureStageHandle;							// ステージ
	int iUICount;										//UIのカウント
	bool bStartFlg;										//スタートフラグ	
	bool bHomeFlg;										//ホームフラグ
	bool bGameStartFlg;									//ゲームスタートフラグ

protected:
};
