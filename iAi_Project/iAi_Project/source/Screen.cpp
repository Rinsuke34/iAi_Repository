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
		//this->textureTitleHandle = ImageList->piGetImage_Movie("Object/SignBoard/ScreenTexture");
        this->textureTitleHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");
	}

	// テクスチャの読み込み
	MV1SetTextureGraphHandle(iModelHandle, 0, this->textureTitleHandle, true);

	//pScreen->iGetNowCameraFixedPositionNo();


	/* スクリーンを発光フレームとして登録 */
	{
		/* モデルハンドルからフレーム数を取得 */
		int iFrameNum = MV1GetFrameNum(this->iModelHandle);

		/* 発光するフレーム番号を取得する */
		for (int i = 0; i < iFrameNum; i++)
		{
			/* フレーム名取得 */
			const char* cFrameName = MV1GetFrameName(this->iModelHandle, i);

			/* 最初の6文字が"Screen"であるか確認 */
			if (strncmp(cFrameName, "Screen", 5) == 0)
			{
				/* 発光フレーム番号を取得 */
				this->aiLightFrameNo.push_back(i);

				/* 発光フレームの親フレーム番号を取得 */
				int parentFrame = MV1GetFrameParent(this->iModelHandle, i);

				/* 発光フレームの親フレームが存在するならば */
				while (parentFrame >= 0)
				{
					// 親フレームが存在する場合
					/* 親フレーム番号を追加 */
					this->aiLightFrameNo.push_back(parentFrame);

					/* 親フレーム番号の親フレームを取得 */
					parentFrame = MV1GetFrameParent(this->iModelHandle, parentFrame);
				}

				/* ループを抜ける */
				break;
			}
		}
	}
}

// デストラクタ
Screen::~Screen()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}


// 更新
void Screen::Update()
{

	/* タイトルロゴを再生 */
	PlayMovieToGraph(this->textureTitleHandle);

	/* ムービーを描写 */
	DrawGraph(100, -100, this->textureTitleHandle, TRUE);

	/* 再生が終了しているか確認 */
	if (GetMovieStateToGraph(this->textureTitleHandle) == FALSE)
	{
		// 再生が終了している場合
		/* ムービーの再生時間を初期化する */
		SeekMovieToGraph(this->textureTitleHandle, 0);
	}

}
