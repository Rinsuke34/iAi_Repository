/* 2024.03.26 石川智也 ファイル作成 */

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

// ゲーム内左矢印スクリーンクラス
class ScreenArrowLeft : public PlatformBase
{
public:
	ScreenArrowLeft();				// コンストラクタ
	virtual ~ScreenArrowLeft();		// デストラクタ

	virtual void	Update()			override;		// 更新

private:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;						// オブジェクト管理
	CharacterBase* pPlayer;								// プレイヤー

	/* 関数 */
	void	Process();									// 更新
	void	Draw();										// 描画

	/* 変数 */
	int iFirstCount;									//最初のカウント
	int iSecondCount;									//二回目のカウント
	int iThirdCount;									//三回目のカウント
	int iFourthCount;									//四回目のカウント
	int iFifthCount;									//五回目のカウント
	int iUICount;										//UIのカウント
	int iTextureArrowLeftHandle1;						// 左矢印
	int iTextureArrowLeftHandle2;						// 左矢印
	int iTextureArrowLeftHandle3;						// 左矢印
	int iTextureArrowLeftHandle4;						// 左矢印
	int iTextureArrowLeftHandle5;						// 左矢印
	bool bArrowFlg;										//矢印フラグ
	bool bArrowFlg2;									//矢印フラグ2
	bool bArrowFlg3;									//矢印フラグ3
	bool bArrowFlg4;									//矢印フラグ4
	bool bArrowFlg5;									//矢印フラグ5
};
