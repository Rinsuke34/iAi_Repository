/* 2025.01.16 ファイル作成 駒沢風助 */

#include "SceneStage.h"

/* オブジェクト */
// ※仮処理(増えたりする可能性あり)
// プレイヤー
#include "CharacterPlayer.h"
// エネミー
#include "EnemyNormal.h"
#include "EnemyEscape.h"
#include "EnemyGoalObject.h"
#include "EnemyNormal.h"
#include "EnemyMissile.h"
#include "EnemyBeam.h"
#include "Enemy_Explosion.h"
// プラットフォーム
#include "PlatformBasic.h"
// スカイスフィア
#include "SkySqhereBasic.h"
// ギミック
#include "GimmickDisappear.h"
#include "Gimmick_ForcedJump_Spawn.h"

/* ステージクラスの定義(マップ読み込み部分) */

// マップデータのロード
void SceneStage::LoadMapData()
{
	/* 現在のステージ番号を取得 */
	int iStageNo = this->StageStatusList->iGetNowStageNo();

	/* マップ名を取得 */
	std::string MapName = STAGE_NAME[iStageNo];

	/* マップデータの読み込み */
	{
		/* 読み込みたいマップデータのパス設定 */
		// ※ファイル名とステージ名が一致するようにする
		std::string Path = "resource/MapData/";
		std::string Format = MapName + ".json";
		std::ifstream file(Path + Format);

		/* Jsonファイル読み込み */
		nlohmann::json json;
		file >> json;

		/* プラットフォーム(描写オブジェクト)読み込み */
		{
			/* Jsonファイルから読み込み */
			std::string Type = "/Object";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
			{
				/* "オブジェクト管理"にプラットフォームを追加 */
				PlatformBase* pPlatform = new PlatformBase();
				this->ObjectList->SetPlatform(pPlatform);

				/* モデル */
				std::string	name;
				data.at("objectName").get_to(name);
				std::string Path = "Object/" + name + "/" + name;
				pPlatform->SetModelHandle(this->ModelList->iGetModel(Path));

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
				pPlatform->SetRotation(vecRot);

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

				/* 座標を取得 */
				VECTOR vecPos;
				// 読み込み
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z座標反転
				vecPos.z *= -1;

				/* 回転量を取得 */
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

				/* マーカータイプ確認 */
				if (name == "Marker_Player_Start")
				{
					// プレイヤースタート地点の場合
					/* "オブジェクト管理"にプレイヤーを追加 */
					CharacterPlayer* pPlayer = new CharacterPlayer();
					ObjectList->SetCharacterPlayer(pPlayer);

					/* 座標設定 */
					pPlayer->SetPosition(vecPos);

					/* 回転量設定 */
					pPlayer->SetRotation(vecRot);
				}
				else if (name == "Marker_Goal_Object")
				{
					// ゴール地点の場合
					/* "オブジェクト管理"にゴールオブジェクトを追加 */
					EnemyBasic* pGoal = new EnemyGoalObject();
					ObjectList->SetEnemy(pGoal);

					/* 座標設定 */
					pGoal->SetPosition(vecPos);

					/* 回転量設定 */
					pGoal->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Beam")
				{
					// エネミー(ビーム)の場合
					/* "オブジェクト管理"にエネミー(ビーム)を追加 */
					BeamEnemy* AddEnemy = new BeamEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Escape")
				{
					// エネミー(逃走)の場合
					/* "オブジェクト管理"にエネミー(逃走)を追加 */
					EscapeEnemy* AddEnemy = new EscapeEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Explosion")
				{
					// エネミー(自爆)の場合
					/* "オブジェクト管理"にエネミー(自爆)を追加 */
					ExplosionEnemy* AddEnemy = new ExplosionEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Missile")
				{
					// エネミー(ミサイル)の場合
					/* "オブジェクト管理"にエネミー(ミサイル)を追加 */
					MissileEnemy* AddEnemy = new MissileEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Normal")
				{
					// エネミー(通常)の場合
					/* "オブジェクト管理"にエネミー(通常)を追加 */
					NormalEnemy* AddEnemy = new NormalEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Gimmick_Jump")
				{
					// ギミック(強制ジャンプ)の場合
					PlatformBasic* pAddGimick = new Gimmick_ForcedJump_Spawn();
					ObjectList->SetPlatform(pAddGimick);

					/* 座標設定 */
					pAddGimick->SetPosition(vecPos);

					/* 回転量設定 */
					pAddGimick->SetRotation(vecRot);
				}
				else if (name == "Marker_Camera_Position_Start")
				{
					// カメラ位置(スタート)の場合
					/* 座標設定(カメラ座標) */
					StageStatusList->SetCameraPosition(vecPos);				// カメラの座標設定(現在地点)
					StageStatusList->SetCameraPosition_Start(vecPos);		// カメラの座標設定(移動前地点)
					StageStatusList->SetCameraPosition_Target(vecPos);		// カメラの座標設定(移動後地点)

					/* 座標設定(固定座標(開始地点)) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosA")
				{
					// カメラ位置(ポジションA)の場合
					/* 座標設定(ポジションA) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosB")
				{
					// カメラ位置(ポジションB)の場合
					/* 座標設定(ポジションB) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosC")
				{
					// カメラ位置(ポジションC)の場合
					/* 座標設定(ポジションC) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosD")
				{
					// カメラ位置(ポジションD)の場合
					/* 座標設定(ポジションD) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosE")
				{
					// カメラ位置(ポジションE)の場合
					/* 座標設定(ポジションE) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Target_Start")
				{
					// カメラ注視点(スタート)の場合
					/* 座標設定(カメラ注視点) */
					StageStatusList->SetCameraTarget(vecPos);				// カメラの注視点設定(現在地点)

					/* 座標設定(固定座標(開始地点)) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosA")
				{
					// カメラ注視点(ポジションA)の場合
					/* 座標設定(ポジションA) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosB")
				{
					// カメラ注視点(ポジションB)の場合
					/* 座標設定(ポジションB) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosC")
				{
					// カメラ注視点(ポジションC)の場合
					/* 座標設定(ポジションC) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosD")
				{
					// カメラ注視点(ポジションD)の場合
					/* 座標設定(ポジションD) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosE")
				{
					// カメラ注視点(ポジションE)の場合
					/* 座標設定(ポジションE) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].vecTarget	= vecPos;
				}
			}
		}

		/* スカイスフィア追加 */
		// ※標準で追加する
		{
			/* "オブジェクト管理"にスカイスフィアを追加 */
			SkySqhereBasic* pSkySqhere = new SkySqhereBasic();
			ObjectList->SetSkySqhere(pSkySqhere);

			/* モデル */
			pSkySqhere->SetModelHandle(this->ModelList->iGetModel("SkySqhere/skysphere"));

			/* サイズ */
			pSkySqhere->SetScale(VGet(5.f, 5.f, 5.f));
		}
	}

	/* すべてのオブジェクトの初期化を行う */
	ObjectList->InitializationAll();

	/* カメラ固定座標の総数を取得 */
	{
		/* 総数を初期化する */
		this->iMaxCameraFixedPositionNo = 0;

		/* カメラ固定座標の総数を取得する */
		for (int i = 0; i < CAMERA_FIXED_POSITION_MAX; ++i)
		{
			/* 使用状態が有効であるか確認 */
			if (this->vecCameraPositionInfo[i].bUseFlg == true)
			{
				// 有効である場合
				/* 総数を加算する */
				this->iMaxCameraFixedPositionNo += 1;
			}
			else
			{
				// 無効である場合
				/* ループを抜ける */
				break;
			}
		}
	}
}
