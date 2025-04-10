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

// スクリーン右矢印クラス
class ScreenArrowRight : public PlatformBase
{
public:
	ScreenArrowRight();				// コンストラクタ
	virtual ~ScreenArrowRight();		// デストラクタ

	virtual void	Update()			override;		// 更新

private:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;						// オブジェクト管理
	CharacterBase* pPlayer;								// プレイヤー

	/* 関数 */
	void	Process();									// 更新
	void	Draw();										// 描画

	/* 変数 */
	int iFirstCount;									// 1回目のカウント
	int iSecondCount;									// 2回目のカウント
	int iThirdCount;									// 3回目のカウント
	int iFourthCount;									// 4回目のカウント
	int iFifthCount;									// 5回目のカウント
	int iUICount;										//UIのカウント
	int iTextureArrowRightHandle1;						// 右矢印
	int iTextureArrowRightHandle2;						// 右矢印
	int iTextureArrowRightHandle3;						// 右矢印
	int iTextureArrowRightHandle4;						// 右矢印
	int iTextureArrowRightHandle5;						// 右矢印
	bool bArrowFlg;										// 矢印フラグ
	bool bArrowFlg2;									// 矢印フラグ2
	bool bArrowFlg3;									// 矢印フラグ3
	bool bArrowFlg4;									// 矢印フラグ4
	bool bArrowFlg5;									// 矢印フラグ5
};
