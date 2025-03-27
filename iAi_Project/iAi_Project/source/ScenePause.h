/* 2025.03.05 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "ScenePauseDefine.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"

/* シーン */
#include "SceneOption.h"
#include "SceneAddTitleSetup.h"

/* 一時停止クラスの宣言 */

// 一時停止クラス
class ScenePause : public SceneBase
{
	public:
		ScenePause();				// コンストラクタ
		virtual ~ScenePause();		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;	// ステージ状態管理
		DataList_GameResource*	GameResourceList;	// ゲーム内リソース管理

		/* 変数 */
		int	iSelectItem;			// 選択中の項目の番号
		int iStopStartTime;			// 停止開始時の時間

		/* 関数 */
		void	SaveDataCreate();	// セーブデータ作成
};
