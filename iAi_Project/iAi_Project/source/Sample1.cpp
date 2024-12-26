#include "Sample1.h"
#include "SampleTitle.h"

// コンストラクタ
SceneSample::SceneSample() : SceneBase("Sample", 1, false)
{
	/* 非同期読み込みを有効化する */
	SetUseASyncLoadFlag(true);

	/* 非同期読み込みを無効化する */
	SetUseASyncLoadFlag(false);
}

// デストラクタ
SceneSample::~SceneSample()
{

}

// 計算
void SceneSample::Process()
{
	/* いずれかのボタンが入力されたらタイトルへ */
	if (gstInputData.igRel != 0)
	{
		gpSceneServer->AddSceneReservation(new SceneTitle(), true);
	}
}

// 描画
void SceneSample::Draw()
{
	DrawFormatString(10, 30, GetColor(237, 26, 61), "シーン : サンプル");
}
