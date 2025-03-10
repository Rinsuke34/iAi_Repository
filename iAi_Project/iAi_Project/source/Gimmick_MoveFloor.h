/* 2025.03.10 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"
#include "GimmickDefine.h"

/* データリスト */
#include "DataList_Model.h"

/* 移動床クラスの宣言 */

// 移動床クラス方向
class Gimmick_MoveFloor : public PlatformBase
{
	public:
		Gimmick_MoveFloor();				// コンストラクタ
		virtual ~Gimmick_MoveFloor() {};	// デストラクタ

		virtual void	Update()			override;		// 更新

		void	SetupMoveDirection(bool bVerticalDirection, int iMoveDistance);		// 移動方向を設定

	private:
		/* 変数 */
		VECTOR	vecMovePos;			// 移動床の移動先座標
		bool	bTargetMove;		// 移動床の移動先座標に向かっているか(true:移動先座標へ / false:初期座標へ)
};
