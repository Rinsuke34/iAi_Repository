/* 2024.12.08 駒沢風助 ファイル作成 */

#include "AppFrame.h"
#include "VariableDefine.h"

/* シーン */
#include "SceneLoad.h"
#include "SceneTitle.h"
#include "SceneLogo.h"

/* データリスト */
#include "DataList_Input.h"
#include "DataList_Sound.h"
#include "DataList_Model.h"
#include "DataList_Image.h"
#include "DataList_Effect.h"
#include "DataList_StageStatus.h"
#include "DataList_Option.h"

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

		/* ロゴシーンを追加 */
		gpSceneServer->AddSceneReservation(new SceneLogo());
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

			/* データリストサーバーに"3Dモデル管理"を追加 */
			gpDataListServer->AddDataList(new DataList_Model());

			/* データリストサーバーに"画像リソース管理"を追加 */
			gpDataListServer->AddDataList(new DataList_Image());

			/* データリストサーバーに"エフェクトリソース管理"を追加 */
			gpDataListServer->AddDataList(new DataList_Effect());

			/* データリストサーバーに"ステージ状態管理"を追加 */
			gpDataListServer->AddDataList(new DataList_StageStatus());

			/* データリストサーバーに"オプション設定管理"を追加 */
			gpDataListServer->AddDataList(new DataList_Option());

			/* データリストサーバーに"サウンド管理"を追加 */
			// ※サウンド管理では、オプション設定管理を取得するため、オプション設定管理より後に追加する
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
			/* フォントハンドルを取得(マキナス/通常サイズ) */
			giFontHandle_Small					= LoadFontDataToHandle("resource/FontData/Makinas-4-Flat.dft", 0);

			/* フォントハンドルを取得(マキナス/中サイズ) */
			giFontHandle_Medium					= CreateFontToHandle(NULL, 60, 9, DX_FONTTYPE_ANTIALIASING, -1, giFontHandle_Small);

			/* フォントハンドルを取得(マキナス/大サイズ) */
			giFontHandle_Large					= CreateFontToHandle(NULL, 90, 9, DX_FONTTYPE_ANTIALIASING, -1, giFontHandle_Small);

			/* フォントハンドルを取得(のとせりふ/セリフテキスト用) */
			giFontHandle_NotoSerifJP_Medium		= LoadFontDataToHandle("resource/FontData/NotoSerifJP-Medium.dft", 0);

			/* フォントハンドルを取得(のとせりふ/ネームタグ、オプション用) */
			giFontHandle_NotoSerifJP_SemiBold	= LoadFontDataToHandle("resource/FontData/NotoSerifJP-SemiBold.dft", 0);
		}
	}
}
