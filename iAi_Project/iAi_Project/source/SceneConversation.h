/* 2025.03.19 ファイル追加 駒沢風助 */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include <vector>

/* データリスト */
#include "DataList_Option.h"
#include "DataList_Image.h"

/* シーン"会話パート"の宣言 */

// シーン "会話パート"
class SceneConversation : public SceneBase
{
	public:
		SceneConversation();					// コンストラクタ
		virtual ~SceneConversation() {};		// デストラクタ

		void	Initialization()	override;	// 初期化
		void	Process()			override;	// 計算
		void	Draw()				override;	// 描画

		int		iGetTextFileNo()				{ return this->iTextFileNo; }			// テキストファイル番号を取得

		void	SetTextFileNo(int iTextFileNo)	{ this->iTextFileNo	=	iTextFileNo; }	// テキストファイル番号を設定

	private:
		/* 関数 */
		void	LoadTextData();					// テキストデータ読み込み
		void	Process_SkipCheck();			// 計算(スキップ画面描写中)
		void	Process_Conversation();			// 計算(会話パート描写中)

		/* 使用するデータリスト */
		DataList_Option* OptionList;			// オプション設定管理

		/* 画像ハンドル */
		int* piGrHandle_SkipWindow;				// スキップ確認画面ウィンドウ
		int* apiGrHandle_SkipWindow_Yes[2];		// スキップ確認YES(0:選択中/1:非選択中)
		int* apiGrHandle_SkipWindow_No[2];		// スキップ確認NO(0:選択中/1:非選択中)
		int* piGrHandle_Icon_Button_A;			// Aボタンアイコン
		int* piGrHandle_Icon_Hold;				// ホールドアイコン

		/* 変数 */
		std::vector<TEXT_DATA>		astTextDataList;	// 会話パート用のテキストデータリスト
		int		iTextDrawDelay;							// テキスト更新待機時間
		int		iTextFileNo;							// テキストファイル番号
		int		iDrawText;								// テキストの描写量
		int		iNowTextNo;								// 現在のテキスト番号
		int		iHoldTimer;								// 長押し時間
		bool	bAddSkipCheckFlg;						// スキップ確認画面を描写中であるか
		bool	bSelectYes;								// YESを選択中であるか(スキップ画面)
};
