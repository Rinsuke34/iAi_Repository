/* 2025.03.04 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_PlayerStatus.h"

/* 落下判定クラスの宣言 */

// 落下判定クラス
class Gimmick_FallJudgment : public PlatformBase
{
	public:
		Gimmick_FallJudgment();				// コンストラクタ
		virtual ~Gimmick_FallJudgment() {};	// デストラクタ

		virtual void	Update()			override;	// 更新

	private:
		/* 使用するデータリスト */
		DataList_Object*		ObjectList;			// オブジェクト管理
		DataList_PlayerStatus*	PlayerStatusList;	// プレイヤー状態管理
};
