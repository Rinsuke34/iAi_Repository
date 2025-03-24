/* 2025.03.24 ファイル追加 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* シーン */
#include "SceneAddTitleSetup.h"

/* データリスト */
#include "DataList_Option.h"
#include "DataList_Image.h"

/* シーン"エンドクレジット"の宣言 */

// シーン "エンドクレジット"
class SceneEndcredit : public SceneBase
{
	public:
		SceneEndcredit();				// コンストラクタ
		virtual ~SceneEndcredit();		// デストラクタ

		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

	private:
		/* 使用するデータリスト */
		DataList_Option* OptionList;			// オプション設定管理

		/* 画像ハンドル */
		int* piGrHandle_Icon_Button_Select[2];	// 決定アイコン(0:コントローラー/1:キーボード)
		int* piGrHandle_Icon_Hold;				// ホールドアイコン
		int* piGrhandle_EndCredit;				// エンドクレジット

		/* 変数 */
		int		iElapsedTime;					// 経過時間
		int		iScrollEndTime;					// スクロール終了時間
		int		iHoldTimer;						// 長押し時間
};
