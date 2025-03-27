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

		this->iTextureArrowRightHandle1 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_1");	// 右矢印1
		this->iTextureArrowRightHandle2 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_2");	// 右矢印2
		this->iTextureArrowRightHandle3 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_3");	// 右矢印3
		this->iTextureArrowRightHandle4 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_4");	// 右矢印4
		this->iTextureArrowRightHandle5 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_5");	// 右矢印5

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
	this->iFirstCount = 0;
	this->iSecondCount = 0;
	this->iThirdCount = 0;
	this->iFourthCount = 0;
	this->iFifthCount = 0;

	this->bArrowFlg = false;
	this->bArrowFlg2 = false;
	this->bArrowFlg3 = false;
	this->bArrowFlg4 = false;
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
	// 1秒後にSceneをAに変更
	if (this->iUICount == CAMERA_FIXED_POSITION_START)
	{
		if (++iFirstCount >= 20)
		{
			iUICount = CAMERA_FIXED_POSITION_A;
			iFirstCount = 0;
		}
	}

	// 1秒後にSceneをBに変更
	else if (this->iUICount == CAMERA_FIXED_POSITION_A)
	{
		if (++iSecondCount >= 20)
		{
			iUICount = CAMERA_FIXED_POSITION_B;
			iSecondCount = 0;
		}
	}

	// 1秒後にSceneをCに変更
	else if (this->iUICount == CAMERA_FIXED_POSITION_B)
	{
		if (++iThirdCount >= 20)
		{
			iUICount = CAMERA_FIXED_POSITION_C;
			iThirdCount = 0;
		}
	}

	// 1秒後にSceneをDに変更
	else if (this->iUICount == CAMERA_FIXED_POSITION_C)
	{
		if (++iFourthCount >= 20)
		{
			iUICount = CAMERA_FIXED_POSITION_D;
			iFourthCount = 0;
		}
	}

	// 1秒後にSceneをEに変更
	else if (this->iUICount == CAMERA_FIXED_POSITION_D)
	{
		if (++iFifthCount >= 20)
		{
			iUICount = CAMERA_FIXED_POSITION_START;
			iFifthCount = 0;
		}
	}
}


// 描画
void ScreenArrowRight::Draw()
{
	int currentTextureHandle = -1;
	int newTextureHandle = -1;

	// UIカウントによって処理を分岐
	switch (iUICount)
	{
	case CAMERA_FIXED_POSITION_START:
		newTextureHandle = this->iTextureArrowRightHandle1;
		break;

	case CAMERA_FIXED_POSITION_A:
		newTextureHandle = this->iTextureArrowRightHandle2;
		break;

	case CAMERA_FIXED_POSITION_B:
		newTextureHandle = this->iTextureArrowRightHandle3;
		break;

	case CAMERA_FIXED_POSITION_C:
		newTextureHandle = this->iTextureArrowRightHandle4;
		break;

	case CAMERA_FIXED_POSITION_D:
		newTextureHandle = this->iTextureArrowRightHandle5;
		break;
	}

	// テクスチャが変更された場合のみ切り替える
	if (newTextureHandle != currentTextureHandle)
	{
		MV1SetTextureGraphHandle(iModelHandle, 1, newTextureHandle, true);
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
