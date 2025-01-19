/* 2025.01.16 駒沢風助 ステージ作成 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* データリスト */
#include "DataList_PlayerStatus.h"
#include "DataList_Model.h"

/* ステージ */
#include "SceneStage.h"

/* シーン「ゲーム」の宣言 */

// シーン "ゲーム画面"
class SceneGame : public SceneBase
{
	public:
		SceneGame();							// コンストラクタ
		virtual ~SceneGame();					// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:

		/* 変数 */
		int		iNowStageNo;	// 現在のステージ番号
		int		iEndStageNo;	// 最終ステージ番号

	protected:
};
