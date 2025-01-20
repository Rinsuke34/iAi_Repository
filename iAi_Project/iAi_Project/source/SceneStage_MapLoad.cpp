/* 2025.01.16 ファイル作成 駒沢風助 */

#include "SceneStage.h"

/* オブジェクト */
// ※仮
#include "CharacterPlayer.h"
#include "PlatformBasic.h"
#include "Enemy_Test.h"
#include "PlatformLight_Test.h"
#include "EnemyGoalObject.h"

/* ステージクラスの定義(マップ読み込み部分) */

// マップデータのロード
void SceneStage::LoadMapData(int iStageNo)
{
	// 引数
	// iStageNo		<- ロードを行うステージ番号

	/* マップ名を取得 */
	std::string MapName = STAGE_NAME[iStageNo];

	/* マップデータの読み込み */
	{
		/* 読み込みたいマップデータのパス設定 */
		// ※ファイル名とステージ名が一致するようにする
		std::string Path	= "resource/MapData/";
		std::string Format	= MapName + ".json";
		std::ifstream file(Path + Format);

		/* Jsonファイル読み込み */
		nlohmann::json json;
		file >> json;

		/* プラットフォーム読み込み */
		{
			/* Jsonファイル内のステージ名と同一の要素を読み込み */
			nlohmann::json stage = json.at(MapName);

			for (auto& data : stage)
			{
				/* プラットフォーム追加 */
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
					vecRot.x = DEG2RAD(vecRot.x);
					vecRot.y = DEG2RAD(vecRot.y);
					vecRot.z = DEG2RAD(vecRot.z);
					// X軸の回転方向を反転
					// ※正しいか不明な処理
					vecRot.x *= -1;
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

		/* マーカー読み込み */
		{
			/* Jsonファイル内のマーカーを読み込み */
			nlohmann::json marker = json.at("Marker");

			for (auto& data : marker)
			{
				/* マーカー名取得 */
				std::string	name;
				data.at("objectName").get_to(name);

				/* マーカータイプ確認 */
				if (name == "S_Marker_StartPoint")
				{
					// プレイヤースタート地点の場合
					/* "オブジェクト管理"にプレイヤーを追加 */
					CharacterPlayer* pPlayer = new CharacterPlayer();
					ObjectList->SetCharacterPlayer(pPlayer);

					/* モデル */
					pPlayer->SetModelHandle(this->ModelList->iGetModel("Player"));

					/* 座標 */
					VECTOR vecPos;
					// 読み込み
					data.at("translate").at("x").get_to(vecPos.x);
					data.at("translate").at("z").get_to(vecPos.y);
					data.at("translate").at("y").get_to(vecPos.z);
					// Z座標反転
					vecPos.z *= -1;
					// 設定
					pPlayer->SetPosition(vecPos);

					/* 回転量 */
					// 後ほど追加

				}
				else if (name == "S_Marker_Goal")
				{
					// ゴール地点の場合
					/* "オブジェクト管理"にゴールオブジェクトを追加 */
					EnemyBase* pGoal = new EnemyGoalObject();
					ObjectList->SetEnemy(pGoal);

					/* 座標 */
					VECTOR vecPos;
					// 読み込み
					data.at("translate").at("x").get_to(vecPos.x);
					data.at("translate").at("z").get_to(vecPos.y);
					data.at("translate").at("y").get_to(vecPos.z);
					// Z座標反転
					vecPos.z *= -1;
					// 設定
					pGoal->SetPosition(vecPos);
				}
			}
		}
	}

	/* テスト用仮オブジェクト追加処理 */
	{
		/* エネミー追加(仮) */
		{
			TestEnemy* AddEnemy = new TestEnemy();
			ObjectList->SetEnemy(AddEnemy);

			AddEnemy->SetPosition(VGet(100, 100, 100));
		}

		/* 光る足場追加(仮) */
		{
			PlatformLight_Test* pPlatform = new PlatformLight_Test();
			this->ObjectList->SetPlatform(pPlatform);

			/* モデル */
			std::string	name = "Test/LightBlock/Test_Cube_1";
			pPlatform->SetModelHandle(this->ModelList->iGetModel(name));

			/* 座標 */
			VECTOR vecPos = VGet(500.f, 100.f, 0.f);
			pPlatform->SetPosition(vecPos);

			/* 回転量 */
			VECTOR vecRot = VGet(0.f, 0.f, 0.f);
			pPlatform->SetRotate(vecRot);

			/* 拡大率 */
			VECTOR vecScale = VGet(10.f, 1.f, 10.f);
			pPlatform->SetScale(vecScale);
		}

		/* 光る足場(2個目) */
		{
			PlatformLight_Test* pPlatform = new PlatformLight_Test();
			this->ObjectList->SetPlatform(pPlatform);

			/* モデル */
			std::string	name = "Test/LightBlock/Test_Cube";
			pPlatform->SetModelHandle(this->ModelList->iGetModel(name));

			/* 座標 */
			VECTOR vecPos = VGet(300.f, 200.f, 300.f);
			pPlatform->SetPosition(vecPos);

			/* 回転量 */
			VECTOR vecRot = VGet(0.f, 0.f, 0.f);
			pPlatform->SetRotate(vecRot);

			/* 拡大率 */
			VECTOR vecScale = VGet(10.f, 1.f, 10.f);
			pPlatform->SetScale(vecScale);
		}

		/* 町 */
		{
			PlatformBase* pPlatform = new PlatformBasic();
			this->ObjectList->SetPlatform(pPlatform);

			/* モデル */
			pPlatform->SetModelHandle(this->ModelList->iGetModel("Test/City/city"));

			/* 座標 */
			VECTOR vecPos = VGet(0.f, 0.f, 0.f);
			pPlatform->SetPosition(vecPos);

			/* 回転量 */
			VECTOR vecRot = VGet(0.f, 0.f, 0.f);
			pPlatform->SetRotate(vecRot);

			/* 拡大率 */
			VECTOR vecScale = VGet(1.f, 1.f, 1.f);
			pPlatform->SetScale(vecScale);
			// 設定
			pPlatform->SetScale(vecScale);
		}
	}

	/* すべてのオブジェクトの初期化を行う */
	ObjectList->InitializationAll();
}
