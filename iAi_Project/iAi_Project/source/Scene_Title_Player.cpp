/* 2025.02.28 石川智也 ファイル作成 */
#include "Scene_Title_Player.h"

// コンストラクタ
TitlePlayer::TitlePlayer() : PlatformBase()
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
		this->iModelHandle = ModelListHandle->iGetModel("Player/Player");
	}

}

// デストラクタ
TitlePlayer::~TitlePlayer()
{
	/* 紐づいているエフェクトの削除フラグを有効化 */
}

//処理
void TitlePlayer::Process()
{

}


// 更新
void TitlePlayer::Update()
{
	//処理
	Process();
}
