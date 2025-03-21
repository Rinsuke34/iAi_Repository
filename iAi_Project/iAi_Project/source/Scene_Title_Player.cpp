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

	/* 開始時モーション設定 */
	{
		//モデルに着地モーションをアタッチする
		this->iTitlePlayerWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 2, -1, FALSE);

		// 再生時間を初期化する
		this->fTitlePlayerWaitTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iTitlePlayerWaitAttachIndex);

		///* 発光停止フラグを有効化 */
		this->bBloomStopFlg = true;
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

	//アニメーション更新
	// アタッチした待機モーションを再生する
	MV1SetAttachAnimTime(this->iModelHandle, this->iTitlePlayerWaitAttachIndex, this->fTitlePlayerWaitNowTime);

	//待機モーションの再生時間を加算
	this->fTitlePlayerWaitNowTime += 2.0f;

	//待機モーションの再生時間が終了したか確認
	if (this->fTitlePlayerWaitNowTime >= this->fTitlePlayerWaitTotalTime)
	{
		//待機モーションの再生時間を初期化
		this->fTitlePlayerWaitNowTime = 0.0f;
	}

}
