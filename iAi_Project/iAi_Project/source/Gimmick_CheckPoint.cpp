/* 2025.03.16 駒沢風助 ファイル作成 */

#include "Gimmick_CheckPoint.h"

/* 中間ポイントクラスの定義 */
// コンストラクタ
Gimmick_CheckPoint::Gimmick_CheckPoint() : PlatformBase()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/CheckPoint/CheckPoint");
	}

	/* 画像取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 通常時(非アクティブ時)の発光色 */
		this->piGrHandle_NormalRight = ImageList->piGetImage("SpawnPoint/NormalRight");

		/* アクティブ時の発光色 */
		this->piGrHandle_ActiveRight = ImageList->piGetImage("SpawnPoint/ActiveRight");
	}

	/* 初期化 */
	this->bActiveFlg		= false;
	this->bStartPositionFlg = false;
}

// 初期化
void Gimmick_CheckPoint::Initialization()
{
	PlatformBase::Initialization();

	/* コリジョンをセット */
	this->stCollisionSqhere.vecSqhere		= this->vecPosition;
	this->stCollisionSqhere.fSqhereRadius	= 200.0f;

	/* スタート地点であるか確認 */
	if (this->bStartPositionFlg == true)
	{
		// スタート地点である場合
		/* アクティブ状態に設定する */
		this->bActiveFlg = true;

		/* 発光フレームをアクティブ時の発光色に設定する */
		MV1SetTextureGraphHandle(this->iModelHandle, this->aiLightFrameNo[0], *this->piGrHandle_ActiveRight, true);
	}
	else
	{
		// スタート地点でない場合
		/* 非アクティブ状態に設定する */
		this->bActiveFlg = false;

		/* 発光フレームを通常時の発光色に設定する */
		MV1SetTextureGraphHandle(this->iModelHandle, this->aiLightFrameNo[0], *this->piGrHandle_NormalRight, true);
	}
}

// 更新
void Gimmick_CheckPoint::Update()
{
	/* アクティブ状態でないか確認 */
	if (this->bActiveFlg == false)
	{
		// アクティブ状態でない場合
		/* プレイヤーを取得 */
		CharacterBase* pPlayer = this->ObjectList->GetCharacterPlayer();

		/* プレイヤーとの接触判定 */
		if (pPlayer->HitCheck(this->stCollisionSqhere) == true)
		{
			// 接触している場合
			/* アクティブ状態に設定する */
			this->bActiveFlg = true;

			/* 発光フレームをアクティブ時の発光色に設定する */
			MV1SetTextureGraphHandle(this->iModelHandle, this->aiLightFrameNo[0], *this->piGrHandle_ActiveRight, true);
		}
	}
}

// リセット処理
void Gimmick_CheckPoint::Reset()
{
	/* このオブジェクトの初期化処理を実行する */
	Initialization();
}

// 発光描写
void Gimmick_CheckPoint::BloomDraw()
{
	/* アクティブ状態であるか確認 */
	if (this->bActiveFlg == true)
	{
		// アクティブ状態である場合
		/* 発光描写 */
		PlatformBase::BloomDraw();
	}
}

// 当たり判定描写
void Gimmick_CheckPoint::CollisionDraw()
{
	/* 当たり判定を描写 */
	int iColor = GetColor(255, 0, 0);
	DrawSphere3D(this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius, 16, iColor, iColor, FALSE);
}
