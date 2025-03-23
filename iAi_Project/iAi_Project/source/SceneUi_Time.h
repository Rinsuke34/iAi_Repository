/* 2025.03.22 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_Image.h"
#include "DataList_StageStatus.h"

/* UI(時間)クラスの宣言 */

// UI(時間)クラス
class SceneUi_Time : public SceneBase
{
	public:
		SceneUi_Time();					// コンストラクタ
		virtual ~SceneUi_Time() {};		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;	// ステージ状態管理

		/* 使用する画像のハンドル */
		int* piGrHandle_Text_Frame;					// テキストフレーム

		/* 変数 */
		int iTimeMinute;			// 現在の経過時間(分)
		int iTimeSecond;			// 現在の経過時間(秒)
		int iTimeFractionalSecond;	// 現在の経過時間(少数秒)
};
