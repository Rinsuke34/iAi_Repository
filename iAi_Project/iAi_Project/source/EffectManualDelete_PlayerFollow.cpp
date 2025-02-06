/* 2025.02.05 駒沢風助 ファイル作成 */

#include "EffectManualDelete_PlayerFollow.h"

/* 手動で削除タイミングを設定するエフェクトクラスの定義 */
// ※プレイヤーに自動追従
// コンストラクタ
EffectManualDelete_PlayerFollow::EffectManualDelete_PlayerFollow(bool bCenterFollowFlg) : EffectManualDelete()
{
	// 引数
	// bCenterFollowFlg		<- プレイヤーの中央に追従するかのフラグ(true:中央に追従 / false:足元に追従)

	/* 中央追従フラグの設定 */
	this->bCenterFollowFlg = bCenterFollowFlg;

	/* プレイヤー取得 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
}

// 更新
void EffectManualDelete_PlayerFollow::Update()
{
	/* 座標更新(プレイヤー座標に) */
	this->vecPosition = this->pCharacterPlayer->vecGetPosition();

	/* 中央追従フラグが有効であるか */
	if (this->bCenterFollowFlg == true)
	{
		// 有効である場合
		this->vecPosition.y += PLAYER_HEIGHT / 2;
	}

	/* エフェクト座標更新 */
	Effect_PosUpdate();

	/* エフェクト回転量更新 */
	Effect_RotationUpdate();
}
