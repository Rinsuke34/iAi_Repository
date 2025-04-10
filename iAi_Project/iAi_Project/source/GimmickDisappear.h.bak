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
#include "GimmickDisappearSpawnPoint.h"

/* 先行定義 */
class GimmickDisappearSpawnPoint;

/* テスト用敵クラス */

// 消失ギミッククラス
class GimmickDisappear : public PlatformBase
{
public:
	GimmickDisappear();				// コンストラクタ
	virtual ~GimmickDisappear();		// デストラクタ

	virtual void	Update()			override;		// 更新
	virtual void	Reset()				override;	// リセット処理

	void	SetSpawnPoint(GimmickDisappearSpawnPoint* pGimmickDisappearSpawnPoint) { this->pGimmickDisappearSpawnPoint = pGimmickDisappearSpawnPoint; }	// 紐づいたスポナーの設定

private:

	void ProcessGimmick();					// ギミックの処理メソッドを追加

	/* 使用するデータリスト */
	DataList_Object* ObjectList;			// オブジェクト管理
	CharacterBase* pPlayer;			// プレイヤー


	//ギミックの消滅時間
	int iDisappearTime;					// 消滅時間
	int iSpawnCount;					// 出現カウント
	int iDisappearTimeCount;			// 消滅時間カウント
	int iTextureFirstChangeCount;		// テクスチャ変更時間
	int iTextureSecondChangeCount;		// テクスチャ変更時間
	int iTextureRedHandle;				// テクスチャハンドル
	int iTextureOrangeHandle;			// テクスチャハンドル
	int iTextureYellowHandle;			// テクスチャハンドル
	int iBlinkTime;						// 点滅時間

	/* スポナーのポインタ */
	GimmickDisappearSpawnPoint* pGimmickDisappearSpawnPoint;	// 消失ギミックスポナー

protected:
};
