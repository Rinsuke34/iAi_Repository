/* 2025.01.07 ファイル追加 駒沢風助 */

#include "SceneGame.h"

/* オブジェクト */
#include "CharacterPlayer.h"
#include "PlatformBasic.h"

/* シーン「ゲーム」の定義(マップ読み込み) */

// マップデータのロード
void SceneGame::LoadMapData()
{
	/* 読み込むマップデータの番号を取得 */
	{
		/* マップデータのロード処理 */
	}

	/* マップデータの読み込み */
	{
		/* 読み込みたいマップデータのパス設定 */
		std::string path = "resource/MapData/";
		std::string jsonFile = "Island.json";
		std::ifstream file(path + jsonFile);

		/* データの入っている場所の名称設定 */
		std::string jsonObjName = "Island";

		/* Jsonファイル読み込み */
		nlohmann::json json;
		file >> json;

		nlohmann::json stage = json.at(jsonObjName);

		for (auto& data : stage)
		{
			/* プラットフォーム追加(仮) */
			{
				/* "オブジェクト管理"にプラットフォームを追加 */
				PlatformBase* pPlatform = new PlatformBasic();
				this->ObjectList->SetPlatform(pPlatform);

				/* モデル */
				std::string	name;
				data.at("objectName").get_to(name);
				pPlatform->SetModelHandle(this->ModelList->iGetModel(name));

				/* 座標 */
				VECTOR vecPos;
				// 読み込み
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z座標反転
				vecPos.z *= -1;
				// 設定
				pPlatform->SetPosition(vecPos);

				/* 回転量 */
				VECTOR vecRot;
				// 読み込み
				data.at("rotate").at("x").get_to(vecRot.x);
				data.at("rotate").at("z").get_to(vecRot.y);
				data.at("rotate").at("y").get_to(vecRot.z);
				// degree -> radian変換
				vecRot.x = vecRot.x / 180.f * PI;
				vecRot.y = vecRot.y / 180.f * PI;
				vecRot.z = vecRot.z / 180.f * PI;
				// 設定
				pPlatform->SetRotate(vecRot);

				/* 拡大率 */
				VECTOR vecScale;
				// 読み込み
				data.at("scale").at("x").get_to(vecScale.x);
				data.at("scale").at("z").get_to(vecScale.y);
				data.at("scale").at("y").get_to(vecScale.z);
				// 設定
				pPlatform->SetScale(vecScale);
			}
		}
	}

	/* プレイヤー追加(仮) */
	{
		/* "オブジェクト管理"にプレイヤーを追加 */
		ObjectList->SetCharacterPlayer(new CharacterPlayer());
	}
}
