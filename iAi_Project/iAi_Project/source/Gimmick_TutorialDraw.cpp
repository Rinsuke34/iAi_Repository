/* 2025.03.27 駒沢風助 ファイル作成 */

#include "Gimmick_TutorialDraw.h"

/* チュートリアル描写地点クラスの定義 */
// コンストラクタ
Gimmick_TutorialDraw::Gimmick_TutorialDraw() : PlatformBase()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* 初期化 */
	this->iDrawTutorialNo = 0;	// 描写するチュートリアル番号
}

// 初期化
void Gimmick_TutorialDraw::Initialization()
{
	/* コリジョンをセット */
	this->stCollisionSqhere.vecSqhere		= this->vecPosition;
	this->stCollisionSqhere.fSqhereRadius	= 800.0f * this->vecScale.x;
}

// 更新
void Gimmick_TutorialDraw::Update()
{
	/* プレイヤーを取得 */
	CharacterBase* pPlayer = this->ObjectList->GetCharacterPlayer();

	/* プレイヤーとの接触判定 */
	if (pPlayer->HitCheck(this->stCollisionSqhere) == true)
	{
		// 接触している場合
		/* シーン"UI(チュートリアル)"を作成 */
		SceneUi_Tutorial* pSceneUi_Tutorial = new SceneUi_Tutorial();
		gpSceneServer->AddSceneReservation(pSceneUi_Tutorial);

		/* チュートリアル番号を設定する */
		pSceneUi_Tutorial->SetTutorialNo(this->iDrawTutorialNo);

		/* 初期化処理を実行する */
		pSceneUi_Tutorial->Initialization();

		/* 削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}

// 当たり判定描写
void Gimmick_TutorialDraw::CollisionDraw()
{
	/* 当たり判定を描写 */
	int iColor = GetColor(255, 0, 0);
	DrawSphere3D(this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius, 16, iColor, iColor, FALSE);
}
