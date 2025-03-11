/* 2025.02.27 ファイル作成 駒沢風助 */

#include <vector>
#include <iostream>
#include "SceneAddGameSetup.h"

/* シーン"ゲーム"追加セットアップの定義 */
// コンストラクタ
SceneAddSceneGameSetup::SceneAddSceneGameSetup() : SceneBase("AddSceneGameSetup", 10, true)
{
	/* データリスト取得 */
	{
		/* "エフェクトリソース管理"を追加 */
		this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));
	}

	/* 全エフェクトの事前読み込み */
	PreloadAllEffects();
}

// 計算
void SceneAddSceneGameSetup::Process()
{
	/* 現行シーン削除フラグを有効化 */
	gpSceneServer->SetDeleteCurrentSceneFlg(true);

	/* シーン"ゲーム"を追加 */
	gpSceneServer->AddSceneReservation(new SceneGame());
}

// 全エフェクトの事前読み込み
void SceneAddSceneGameSetup::PreloadAllEffects()
{
	/* エフェクトファイルに保存された全てのエフェクトをロードする */
	// ※Effekseerのエフェクトは非同期読み込みに対応していないため、非同期読み込みは行わない

	/* エフェクトフォルダ(resource/EffectData)内の全てのフォルダ名を取得する配列 */
	std::vector<std::string> aEffectFolderName;

	/* 取得したファイルの情報を保存する変数 */
	WIN32_FIND_DATA findFileData;

	/* フォルダ検索用のハンドル */
	HANDLE hFindFile = FindFirstFile("resource/EffectData\\*", &findFileData);

	/* フォルダが存在するなら、フォルダ名を取得する */
	while (hFindFile != INVALID_HANDLE_VALUE)
	{
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			/* フォルダ名をstd::string型に変換 */
			std::string folderName = findFileData.cFileName;

			/* ファイルではないか確認("."あるいは".."が入っているならファイルと判定) */
			if (folderName != "." && folderName != "..")
			{
				// ファイルではない場合(フォルダの場合)
				/* フォルダ名を配列に追加 */
				aEffectFolderName.push_back(findFileData.cFileName);
			}
		}

		/* 次のファイルを検索 */
		if (FindNextFile(hFindFile, &findFileData) == false)
		{
			// ファイルが見つからなかった場合
			/* ファイル検索終了 */
			break;
		}
	}

	/* 検索ハンドルを閉じる */
	FindClose(hFindFile);

	/* 読み込んだエフェクトフォルダに対応したエフェクトを読み込む */
	for (auto& effectFolderName : aEffectFolderName)
	{
		/* エフェクトを読み込む */
		this->EffectList->LoadEffect(effectFolderName + "/" + effectFolderName);
	}
}
