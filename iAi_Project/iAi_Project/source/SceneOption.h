/* 2025.03.05 ファイル追加 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneOptionDefine.h"
#include <vector>

/* データリスト */
#include "DataList_Image.h"
#include "DataList_Option.h"

/* シーン「オプション」の宣言 */

// シーン "オプション画面"
class SceneOption : public SceneBase
{
	public:
		SceneOption();							// コンストラクタ
		virtual ~SceneOption();					// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_Option* OptionList;			// オプション設定管理

		/* 画像ハンドル */
		int* piGrHandle_ResultFrame;			// リザルト用フレーム

		/* 変数 */
		std::vector<OPTION_LIST>*	astOptionNameList;	// オプション名リスト
		int							iSelectItem;		// 選択中の項目の番号
};
