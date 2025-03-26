/* 2025.03.27 ファイル作成 駒沢風助 */

#pragma once
#include "AppFrame.h"

/* データリスト */
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* UI(チュートリアル)クラスの宣言 */

// UI(チュートリアル)クラス
class SceneUi_Tutorial : public SceneBase
{
	public:
		SceneUi_Tutorial();					// コンストラクタ
		virtual ~SceneUi_Tutorial();		// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

		/* データ取得 */
		int iGetTutorialNo()				{ return this->iTutorialNo; };			// 描写するチュートリアル番号を取得

		/* データ設定 */
		void SetTutorialNo(int iTutorialNo)	{ this->iTutorialNo	=	iTutorialNo; };	// 描写するチュートリアル番号を設定

	private:
		/* 使用するデータリスト */
		DataList_StageStatus*	StageStatusList;		// ゲーム状態管理

		/* 使用する画像のハンドル */
		int*				piGrHandle_Tutorial_Window;				// チュートリアルウィンドウ
		std::vector<int*>	apiGrHandle_Tutorial_Cg;				// チュートリアル描写画像

		/* 変数 */
		int iTutorialNo;								// 描写するチュートリアルの番号
		int iStopStartTime;								// 停止開始時の時間
		int iMaxItemNo;									// 現在のチュートリアルの最大項目数
		int iNowItemNo;									// 現在のチュートリアルの描写中の項目数
		std::vector<std::string>	aText;				// 描写テキスト
};
