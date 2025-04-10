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

/* テスト用敵クラス */

// 消失ギミッククラス
class ScreenArrowLeft : public PlatformBase
{
public:
	ScreenArrowLeft();				// コンストラクタ
	virtual ~ScreenArrowLeft();		// デストラクタ

	virtual void	Update()			override;		// 更新

private:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;	// オブジェクト管理
	CharacterBase* pPlayer;	// プレイヤー

	/* 関数 */
	void	Process();				// 更新
	void	Draw();					// 描画

	//変数
	int iFirstCount;
	int iSecondCount;
	int iThirdCount;
	int iFourthCount;
	int iFifthCount;
	int iUICount;	//UIのカウント

	int iTextureArrowLeftHandle1;		// 左矢印
	int iTextureArrowLeftHandle2;		// 右矢印
	int iTextureArrowLeftHandle3;		// 左矢印
	int iTextureArrowLeftHandle4;		// 右矢印
	int iTextureArrowLeftHandle5;		// 左矢印

	bool bArrowFlg;
	bool bArrowFlg2;
	bool bArrowFlg3;
	bool bArrowFlg4;
	bool bArrowFlg5;
};
