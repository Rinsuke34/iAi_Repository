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

// 消失ギミッククラス
class GimmickDisappear : public PlatformBase
{
public:
	GimmickDisappear();				// コンストラクタ
	virtual ~GimmickDisappear();		// デストラクタ

	virtual void	Update()			override;				// 更新
	virtual void	Reset()				override;				// リセット処理

	void	SetSpawnPoint(std::shared_ptr<GimmickDisappearSpawnPoint> pGimmickDisappearSpawnPoint) { this->pGimmickDisappearSpawnPoint = pGimmickDisappearSpawnPoint; }	// 紐づいたスポナーの設定

private:

	/* 使用するデータリスト */
	std::shared_ptr<DataList_Object> ObjectList;								// オブジェクト管理
	std::shared_ptr<CharacterBase> pPlayer;										// プレイヤー
	/* スポナーのポインタ */
	std::shared_ptr<GimmickDisappearSpawnPoint> pGimmickDisappearSpawnPoint;	// 消失ギミックスポナー

	/* 関数 */
	void ProcessGimmick();										// ギミックの処理メソッドを追加

	/* 変数 */
	int iDisappearTime;											// 消滅時間
	int iSpawnCount;											// 出現カウント
	int iDisappearTimeCount;									// 消滅時間カウント
	int iTextureFirstChangeCount;								// テクスチャ変更時間
	int iTextureSecondChangeCount;								// テクスチャ変更時間
	int iTextureRedHandle;										// テクスチャハンドル
	int iTextureOrangeHandle;									// テクスチャハンドル
	int iTextureYellowHandle;									// テクスチャハンドル
	int iBlinkTime;												// 点滅時間



protected:
};
