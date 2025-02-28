/* 2025.02.28 石川智也 ファイル作成 */
#include "Screen.h"

// コンストラクタ
Screen::Screen() : PlatformBasic()
{
	/* データリスト */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Object/SignBoard/SignBoard");
	}

	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* タイトルロゴ */
        this->textureTitleHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");
	}
	/*this->SetModelHandle(this->iModelHandle);
	MV1SetTextureGraphHandle(this->iModelHandle, 0, textureTitleHandle, true);*/

}

// デストラクタ
Screen::~Screen()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}


void Screen::Initialization()
{
    
}

// スクリーン描画
void Screen::ScreenDraw()
{
	/* 描画ブレンドモードを加算にする */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	/* タイトルロゴを描画 */
	PlayMovieToGraph(this->textureTitleHandle);

	/* ムービー映像を画面いっぱいに描画します */
	DrawGraph(100, -100, this->textureTitleHandle, TRUE);

	/* 再生が終了しているか */
	if (GetMovieStateToGraph(this->textureTitleHandle) == FALSE)
	{
		// 再生が終了している場合
		/* ムービーの再生時間を初期化する */
		SeekMovieToGraph(this->textureTitleHandle, 0);
	}

	/* 描画ブレンドモードをブレンド無しに戻す */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* 描画モードを二アレストに戻す */
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// 更新
void Screen::Update()
{
	//ScreenDraw();
}
