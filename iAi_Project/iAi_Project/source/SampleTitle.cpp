#include "SampleTitle.h"
#include "Sample1.h"

// コンストラクタ
SceneTitle::SceneTitle() : SceneBase("Title", 0, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneTitle::~SceneTitle()
{

}

// 計算
void SceneTitle::Process()
{
	/* いずれかのボタンが入力されたらメニューを追加 */
	if (gstInputData.igRel != 0)
	{
		gpSceneServer->AddSceneReservation(new SceneSample(), true);
	}
}

// 描画
void SceneTitle::Draw()
{
	DrawFormatString(10, 10, GetColor(237, 26, 61), "シーン : タイトル");
}
