/* 2024.03.19 石川智也 ファイル作成 */

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
#include "SceneTitle.h"

/* テスト用敵クラス */

class TitlePlayer : public PlatformBase
{
public:
	TitlePlayer();				// コンストラクタ
	virtual ~TitlePlayer();		// デストラクタ

	virtual void	Update()			override;		// 更新

private:
	/* 使用するデータリスト */
	DataList_Object* ObjectList;	// オブジェクト管理
	CharacterBase* pPlayer;	// プレイヤー

	/* 関数 */
	void	Process();				// 更新

	//変数

	//モーション関係変数
	int		iTitlePlayerWaitAttachIndex;	// 待機モーションアタッチインデックス
	int		iTitlePlayerLandingAttachIndex;	// 着地モーションアタッチインデックス
	bool	bTitlePlayerWaitFlg;			// 待機フラグ
	bool	bTitlePlayerLandingFlg;			// 着地フラグ
	float	fTitlePlayerWaitTotalTime;		// 待機モーションの総再生時間
	float	fTitlePlayerLandingTotalTime;	// 着地モーションの総再生時間
	float	fTitlePlayerWaitNowTime;		// 待機モーションの現在の再生時間
	float	fTitlePlayerLandingNowTime;		// 着地モーションの現在の再生時間

};
