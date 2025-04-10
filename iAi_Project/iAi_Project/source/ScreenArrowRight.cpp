/* 2025.03.26 石川智也 ファイル作成 */
#include "ScreenArrowRight.h"

// コンストラクタ
ScreenArrowRight::ScreenArrowRight() : PlatformBase()
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

		/* スクリーンに映る映像 */
		// 右矢印1
		this->iTextureArrowRightHandle1 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_1");

		// 右矢印2
		this->iTextureArrowRightHandle2 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_2");

		// 右矢印3
		this->iTextureArrowRightHandle3 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_3");

		// 右矢印4
		this->iTextureArrowRightHandle4 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_4");

		// 右矢印5
		this->iTextureArrowRightHandle5 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_5");

	}


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

	//初期化
	//矢印のカウント1
	this->iFirstCount = 0;

	//矢印のカウント2
	this->iSecondCount = 0;

	//矢印のカウント3
	this->iThirdCount = 0;

	//矢印のカウント4
	this->iFourthCount = 0;

	//矢印のカウント5
	this->iFifthCount = 0;

	//矢印フラグ1
	this->bArrowFlg = false;

	//矢印フラグ2
	this->bArrowFlg2 = false;

	//矢印フラグ3
	this->bArrowFlg3 = false;

	//矢印フラグ4
	this->bArrowFlg4 = false;

	//矢印フラグ5
	this->bArrowFlg5 = false;
}

// デストラクタ
ScreenArrowRight::~ScreenArrowRight()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

//処理
void ScreenArrowRight::Process()
{
	//UIカウントが0か確認
	if (this->iUICount == 0)
	{
		//UIカウントが0の場合
		//矢印カウント1が20以上か確認
		if (++iFirstCount >= 20)
		{
			//矢印カウント1が20以上の場合
			//UIカウントを1に変更
			iUICount = 1;

			//矢印カウント1を初期化
			iFirstCount = 0;
		}
	}

	//UIカウントが1か確認
	else if (this->iUICount == 1)
	{
		//UIカウントが1の場合
		//矢印カウント2が20以上か確認
		if (++iSecondCount >= 20)
		{
			//矢印カウント2が20以上の場合
			//UIカウントを2に変更
			iUICount = 2;

			//矢印カウント2を初期化
			iSecondCount = 0;
		}
	}

	//UIカウントが2か確認
	else if (this->iUICount == 2)
	{
		//UIカウントが2の場合
		//矢印カウント3が20以上か確認
		if (++iThirdCount >= 20)
		{
			//矢印カウント3が20以上の場合
			//UIカウントを3に変更
			iUICount = 3;

			//矢印カウント3を初期化
			iThirdCount = 0;
		}
	}

	//UIカウントが3か確認
	else if (this->iUICount == 3)
	{
		//UIカウントが3の場合
		//矢印カウント4が20以上か確認
		if (++iFourthCount >= 20)
		{
			//矢印カウント4が20以上の場合
			//UIカウントを4に変更
			iUICount = 4;

			//矢印カウント4を初期化
			iFourthCount = 0;
		}
	}

	//UIカウントが4か確認
	else if (this->iUICount == 4)
	{
		//UIカウントが4の場合
		//矢印カウント5が20以上か確認
		if (++iFifthCount >= 20)
		{
			//矢印カウント5が20以上の場合
			//UIカウントを0に変更
			iUICount = 0;

			//矢印カウント5を初期化
			iFifthCount = 0;
		}
	}
}


// 描画
void ScreenArrowRight::Draw()
{

	// 現在のテクスチャハンドル
	int currentTextureHandle = -1;

	// 次に設定するテクスチャハンドル
	int newTextureHandle = -1;

	// UIカウントによって処理を分岐
	switch (iUICount)
	{
		// UIカウントが0の場合
	case 0:

		// 矢印のテクスチャハンドル1を設定
		newTextureHandle = this->iTextureArrowRightHandle1;

		break;

		// UIカウントが1の場合
	case 1:

		// 矢印のテクスチャハンドル2を設定
		newTextureHandle = this->iTextureArrowRightHandle2;

		break;

		// UIカウントが2の場合
	case 2:

		// 矢印のテクスチャハンドル3を設定
		newTextureHandle = this->iTextureArrowRightHandle3;

		break;

		// UIカウントが3の場合
	case 3:

		// 矢印のテクスチャハンドル4を設定
		newTextureHandle = this->iTextureArrowRightHandle4;

		break;

		// UIカウントが4の場合
	case 4:

		// 矢印のテクスチャハンドル5を設定
		newTextureHandle = this->iTextureArrowRightHandle5;

		break;
	}

	// テクスチャが変更された場合のみ切り替える
	if (newTextureHandle != currentTextureHandle)
	{
		// モデルのテクスチャを設定
		MV1SetTextureGraphHandle(iModelHandle, 1, newTextureHandle, true);

		// テクスチャハンドルを更新
		currentTextureHandle = newTextureHandle;
	}

	// モデルの描画
	MV1DrawModel(iModelHandle);
}


// 更新
void ScreenArrowRight::Update()
{
	//処理
	Process();

	//描画
	Draw();
}
