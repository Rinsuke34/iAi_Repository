/* 2024.02.10 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* オブジェクト */
#include "PlatformBasic.h"
#include "EffectManualDelete.h"
#include "GimmickDefine.h"

/* テスト用敵クラス */

// 消失ギミッククラス
class GimmickJump : public PlatformBasic
{
public:
	GimmickJump();				// コンストラクタ
	virtual ~GimmickJump();		// デストラクタ

	virtual void	Update()			override;		// 更新

private:

	void ProcessGimmick();					// ギミックの処理メソッドを追加

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー
	DataList_PlayerStatus* PlayerStatusList;	// プレイヤー状態


	//ギミックの消滅時間
	int iDisappearTime;

	//ギミックの消滅時間カウント
	int iDisappearTimeCount;

	//ギミックテクスチャ変更カウント	
	int iTextureChangeCount;

	// テクスチャハンドルを追加
	int textureHandle;

protected:
};
