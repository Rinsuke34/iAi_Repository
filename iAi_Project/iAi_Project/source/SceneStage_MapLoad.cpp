/* 2025.01.16 ファイル作成 駒沢風助 */

#include "SceneStage.h"

/* オブジェクト */
// ※仮
#include "CharacterPlayer.h"
#include "PlatformBasic.h"
#include "Enemy_Test.h"
#include "EnemyGoalObject.h"

/* ステージクラスの定義(マップ読み込み部分) */

// マップデータのロード
void SceneStage::LoadMapData()
{
	/* 現在のステージ番号を取得 */
	int iStageNo = this->GameStatusList->iGetNowStageNo();

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

		/* プラットフォーム(描写オブジェクト)読み込み */
		{
			/* Jsonファイルから読み込み */
			std::string Type	= "/Object";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
			{
				/* "オブジェクト管理"にプラットフォーム(描写モデル)を追加 */
				BackGroundBase* pBackGround = new BackGroundBase();
				this->ObjectList->SetBackGround(pBackGround);

				/* モデル */
				std::string	name;
				data.at("objectName").get_to(name);
				pBackGround->SetModelHandle(this->ModelList->iGetModel(name));

				/* 座標 */
				VECTOR vecPos;
				// 読み込み
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z座標反転
				vecPos.z *= -1;
				// 設定
				pBackGround->SetPosition(vecPos);

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
				pBackGround->SetRotation(vecRot);

				/* 拡大率 */
				VECTOR vecScale;
				// 読み込み
				data.at("scale").at("x").get_to(vecScale.x);
				data.at("scale").at("z").get_to(vecScale.y);
				data.at("scale").at("y").get_to(vecScale.z);
				// 設定
				pBackGround->SetScale(vecScale);
			}
		}

		/* プラットフォーム(コリジョン)読み込み */
		{
			/* Jsonファイルから読み込み */
			std::string Type		= "/Collision";
			std::string GetName		= MapName + Type;
			nlohmann::json stage	= json.at(GetName);

			for (auto& data : stage)
			{
				/* "オブジェクト管理"にプラットフォーム(コリジョン)を追加 */
				CollisionBase* pCollision = new CollisionBase();
				this->ObjectList->SetCollision(pCollision);

				/* モデル */
				std::string	name;
				data.at("objectName").get_to(name);
				pCollision->SetModelHandle(this->ModelList->iGetModel(name));

				/* 座標 */
				VECTOR vecPos;
				// 読み込み
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z座標反転
				vecPos.z *= -1;
				// 設定
				pCollision->SetPosition(vecPos);

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
				pCollision->SetRotation(vecRot);

				/* 拡大率 */
				VECTOR vecScale;
				// 読み込み
				data.at("scale").at("x").get_to(vecScale.x);
				data.at("scale").at("z").get_to(vecScale.y);
				data.at("scale").at("y").get_to(vecScale.z);
				// 設定
				pCollision->SetScale(vecScale);
			}
		}

		/* マーカー読み込み */
		{
			/* Jsonファイルから読み込み */
			std::string Type = "/Marker";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
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

			AddEnemy->SetPosition(VGet(1000.f, -1000.f, 0.f));

			AddEnemy = new TestEnemy();
			ObjectList->SetEnemy(AddEnemy);

			AddEnemy->SetPosition(VGet(500.f, -1000.f, 0.f));

			AddEnemy = new TestEnemy();
			ObjectList->SetEnemy(AddEnemy);

			AddEnemy->SetPosition(VGet(0.f, -1000.f, 0.f));

			AddEnemy = new TestEnemy();
			ObjectList->SetEnemy(AddEnemy);

			AddEnemy->SetPosition(VGet(-500.f, -1000.f, 0.f));
		}
	}

	/* すべてのオブジェクトの初期化を行う */
	ObjectList->InitializationAll();
}
