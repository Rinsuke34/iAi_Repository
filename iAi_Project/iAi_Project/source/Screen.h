/* 2024.02.28 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "PlatformBasic.h"
#include "EffectManualDelete.h"
#include "PlayerStatusDefine.h"
#include "GimmickDefine.h"

/* テスト用敵クラス */

// スクリーンクラス
class Screen : public PlatformBasic
{
public:
	Screen();				// コンストラクタ
	virtual ~Screen();		// デストラクタ

	void	Update()			override;		// 更新

	void			ScreenDraw();						// 描画
private:


	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理



	// テクスチャハンドルを追加
	int textureTitleHandle;

	int textureHomeHandle;


protected:
};
