/* 2024.02.10 石川智也 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Model.h"
#include "DataList_Object.h"

/* オブジェクト */
#include "EffectManualDelete.h"
#include "PlayerStatusDefine.h"
#include "GimmickDefine.h"

/* テスト用敵クラス */

// 消失ギミッククラス
class GimmickDisappear : public PlatformBase
{
public:
	GimmickDisappear();				// コンストラクタ
	virtual ~GimmickDisappear();		// デストラクタ

	virtual void	Update()			override;		// 更新

private:

	void ProcessGimmick();					// ギミックの処理メソッドを追加

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー


	//ギミックの消滅時間
	int iDisappearTime;

	//ギミックの消滅時間カウント
	int iDisappearTimeCount;

	//ギミックテクスチャ変更カウント	
	int iTextureFirstChangeCount;

	int iTextureSecondChangeCount;

	// テクスチャハンドルを追加
	int textureRedHandle;

	int textureOrangeHandle;

	// エフェクト
	EffectManualDelete* pEffectSine;	// 光るエフェクト

protected:
};
