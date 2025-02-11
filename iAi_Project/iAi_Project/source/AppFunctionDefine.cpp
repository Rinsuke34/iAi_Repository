/* 2024.12.08 駒沢風助 ファイル作成 */

#include "AppFrame.h"
#include "VariableDefine.h"

/* シーン */
#include "SceneTitle.h"
#include "SceneLoad.h"

/* データリスト */
#include "DataList_Input.h"
#include "DataList_Sound.h"

/* AppFrameで使用する関数の定義 */

// シーンの設定
namespace SCENE_SET
{
	// ゲーム起動時のシーンをセット
	void	SetFastScene()
	{
		/* ロード画面追加フラグを有効化 */
		gpSceneServer->SetAddLoadSceneFlg(true);

		/* タイトルシーンを追加 */
		gpSceneServer->AddSceneReservation(new SceneTitle());
	}

	// ロードシーンをセット
	void	SetLoadScene()
	{
		/* ロードシーンを追加 */
		gpSceneServer->AddSceneReservation(new SceneLoad());
	}
}

// 初期化
namespace PROJECT_INIT
{
	// プロジェクト初期化処理
	void	Init()
	{
		/* データリスト作成 */
		{
			/* データリストサーバーに"プレイヤー入力管理"を追加 */
			gpDataListServer->AddDataList(new DataList_Input());

			/* データリストサーバーに"サウンド管理"を追加 */
			gpDataListServer->AddDataList(new DataList_Sound());
		}
	
		/* データリスト取得 */
		{
			/* 今追加した"プレイヤー入力管理"を取得 */
			gpDataList_Input = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

			/* 今追加した"サウンド管理"を取得 */
			gpDataList_Sound = dynamic_cast<DataList_Sound*>(gpDataListServer->GetDataList("DataList_Sound"));
		}

		/* フォント設定 */
		{
			/* フォントハンドルを取得 */
			giFontHandle = LoadFontDataToHandle("resource/FontData/Makinas-4-Flat.dft", 0);
		}
	}
}
