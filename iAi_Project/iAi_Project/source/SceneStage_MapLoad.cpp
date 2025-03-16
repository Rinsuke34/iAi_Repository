/* 2025.01.16 ファイル作成 駒沢風助 */

#include "SceneStage.h"

/* オブジェクト */
// プレイヤー
#include "CharacterPlayer.h"
// エネミー
#include "Enemy_GoalObject.h"
// エネミー(スポーンポイント)
#include "EnemySpawnPoint_Normal.h"
#include "EnemySpawnPoint_Escape.h"
#include "EnemySpawnPoint_Missile.h"
#include "EnemySpawnPoint_Beam.h"
#include "EnemySpawnPoint_Explosion.h"
// スポーンポイント
#include "SpawnPoint_Blood_PickupItem.h"
// スカイスフィア
#include "SkySqhereBasic.h"
// ギミック
#include "GimmickDisappear.h"
#include "Gimmick_ForcedJump_Spawn.h"
#include "Screen.h"
#include "LargeScreen.h"
#include "Gimmick_FallJudgment.h"
#include "Gimmick_MoveFloor.h"
#include "Gimmick_CheckPoint.h"
// 霧
#include "FallFog.h"

/* 循環参照対策の先行定義 */
class Gimmick_CheckPoint;

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
				vecRot.x *= -1;

				/* 拡大率 */
				VECTOR vecScale;
				// 読み込み
				data.at("scale").at("x").get_to(vecScale.x);
				data.at("scale").at("z").get_to(vecScale.y);
				data.at("scale").at("y").get_to(vecScale.z);

				/* マーカータイプ確認 */
				if (name == "Marker_Player_Start")
				{
					// プレイヤースタート地点の場合
					/* "オブジェクト管理"にプレイヤーを追加 */
					CharacterPlayer* pPlayer = new CharacterPlayer();
					ObjectList->SetCharacterPlayer(pPlayer);

					/* "オブジェクト管理"にチェックポイントを追加 */
					PlatformBase* pCheckPoint = new Gimmick_CheckPoint();
					ObjectList->SetPlatform(pCheckPoint);

					/* 座標設定 */
					pPlayer->SetPosition(vecPos);
					pCheckPoint->SetPosition(vecPos);

					/* 回転量設定 */
					pPlayer->SetRotation(vecRot);
					pCheckPoint->SetRotation(vecRot);

					/* チェックポイントを初期地点として設定 */
					dynamic_cast<Gimmick_CheckPoint*>(pCheckPoint)->SetStartPositionFlg(true);
				}
				else if (name == "Marker_Goal_Object")
				{
					// ゴール地点の場合
					/* "オブジェクト管理"にゴールオブジェクトを追加 */
					Enemy_Basic* pGoal = new Enemy_GoalObject();
					ObjectList->SetEnemy(pGoal);

					/* 座標設定 */
					pGoal->SetPosition(vecPos);

					/* 回転量設定 */
					pGoal->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Beam")
				{
					// エネミー(ビーム)の場合
					/* "オブジェクト管理"にエネミー(ビーム)スポナーを追加 */
					EnemySpawnPoint_Beam* AddEnemy = new EnemySpawnPoint_Beam();
					ObjectList->SetSpawnPoint(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Escape")
				{
					// エネミー(逃走)の場合
					/* "オブジェクト管理"にエネミー(逃走)スポナーを追加 */
					EnemySpawnPoint_Escape* AddEnemy = new EnemySpawnPoint_Escape();
					ObjectList->SetSpawnPoint(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Explosion")
				{
					// エネミー(自爆)の場合
					/* "オブジェクト管理"にエネミー(自爆)スポナーを追加 */
					EnemySpawnPoint_Explosion* AddEnemy = new EnemySpawnPoint_Explosion();
					ObjectList->SetSpawnPoint(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Missile")
				{
					// エネミー(ミサイル)の場合
					/* "オブジェクト管理"にエネミー(ミサイル)スポナーを追加 */
					EnemySpawnPoint_Missile* AddEnemy = new EnemySpawnPoint_Missile();
					ObjectList->SetSpawnPoint(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Normal")
				{
					// エネミー(通常)の場合
					/* "オブジェクト管理"にエネミー(通常)スポナーを追加 */
					EnemySpawnPoint_Normal* AddEnemy = new EnemySpawnPoint_Normal();
					ObjectList->SetSpawnPoint(AddEnemy);

					/* 座標設定 */
					AddEnemy->SetPosition(vecPos);

					/* 回転量設定 */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Gimmick_Jump")
				{
					// ギミック(強制ジャンプ)の場合
					PlatformBase* pAddGimick = new Gimmick_ForcedJump_Spawn();
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
					StageStatusList->SetCameraTarget_Start(vecPos);			// カメラの注視点設定(移動前地点)
					StageStatusList->SetCameraTarget_Target(vecPos);		// カメラの注視点設定(移動後地点)

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
				else if (name == "SignBoard")
				{
					// スクリーンの場合
					/* "オブジェクト管理"にスクリーンを追加 */
					Screen* pScreen = new Screen();
					ObjectList->SetPlatform(pScreen);

					/* 座標設定 */
					pScreen->SetPosition(vecPos);

					/* 回転量設定 */
					pScreen->SetRotation(vecRot);
				}
				else if (name == "LargeScreen")
				{
					// スクリーンの場合
					/* "オブジェクト管理"にスクリーンを追加 */
					LargeScreen* pLargeScreen = new LargeScreen();
					ObjectList->SetPlatform(pLargeScreen);

					/* 座標設定 */
					pLargeScreen->SetPosition(vecPos);

					/* 回転量設定 */
					pLargeScreen->SetRotation(vecRot);

					/* 拡大率設定*/
					pLargeScreen->SetScale(vecScale);
				}
				else if (name == "FallJudgment")
				{
					// 落下判定の場合
					/* 落下判定用オブジェクトの四方の座標の保存場所作成 */
					VECTOR vecFourDirections[4];

					/* 落下判定用のオブジェクトの基準サイズの設定 */
					VECTOR localVertices[4] =
					{
						VGet(+1000.0f,	0.0f, +1000.0f),	// 右奥
						VGet(+1000.0f,	0.0f, -1000.0f),	// 右前
						VGet(-1000.0f,	0.0f, -1000.0f),	// 左前
						VGet(-1000.0f,	0.0f, +1000.0f)		// 左奥
					};

					/* 霧等の位置を下げる */
					vecPos.y -= 2000.0f;

					/* 行列の作成 (スケール → 回転 → 平行移動) */
					MATRIX matScale	= MGetScale(vecScale);
					MATRIX matRotX	= MGetRotX(vecRot.x);
					MATRIX matRotY	= MGetRotY(vecRot.y);
					MATRIX matRotZ	= MGetRotZ(vecRot.z);
					MATRIX matTrans	= MGetTranslate(vecPos);

					/* 最終変換行列の計算 */
					MATRIX matTransform = MMult(matScale, MMult(MMult(matRotX, matRotY), MMult(matRotZ, matTrans)));

					/* 各頂点に行列を適用してワールド座標を計算 */
					for (int i = 0; i < 4; i++)
					{
						vecFourDirections[i] = VTransform(localVertices[i], matTransform);
					}

					/* 霧を作成 */
					VECTOR topRight = vecFourDirections[0];
					VECTOR topLeft = vecFourDirections[3];
					VECTOR bottomRight = vecFourDirections[1];

					// 水平方向と垂直方向のステップ
					VECTOR horizontalStep = VScale(VNorm(VSub(topLeft, topRight)), 3000.0f);
					VECTOR verticalStep = VScale(VNorm(VSub(bottomRight, topRight)), 3000.0f);

					// 最も右奥から左奥まで横に進みつつ縦に埋めていく
					for (VECTOR startPos = topRight; startPos.x >= topLeft.x; startPos = VAdd(startPos, horizontalStep))
					{
						VECTOR verticalPos = startPos;
						while (verticalPos.z >= bottomRight.z)
						{
							PlatformBase* pFog = new FallFog();
							ObjectList->SetPlatform(pFog);
							pFog->SetPosition(verticalPos);

							verticalPos = VAdd(verticalPos, verticalStep);
						}
					}

					/* "オブジェクト管理"に落下判定位置を追加 */
					PlatformBase* pPlatform = new Gimmick_FallJudgment();
					this->ObjectList->SetPlatform(pPlatform);

					/* モデル */
					std::string Path = "Object/" + name + "/" + name;
					pPlatform->SetModelHandle(this->ModelList->iGetModel(Path));

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);
				}
				else if(name == "Marker_FallRecovery")
				{
					// 落下復帰ポイントの場合
					/* "オブジェクト管理"にチェックポイントを追加 */
					PlatformBase* pCheckPoint = new Gimmick_CheckPoint();
					ObjectList->SetPlatform(pCheckPoint);

					/* 座標設定 */
					pCheckPoint->SetPosition(vecPos);

					/* 回転量設定 */
					pCheckPoint->SetRotation(vecRot);
				}
				else if (name == "DisappearFloor")
				{
					// 床消失の場合
					/* "オブジェクト管理"に床消失を追加 */
					PlatformBase* pPlatform = new GimmickDisappear();
					this->ObjectList->SetPlatform(pPlatform);

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);
				}
				else if (name == "MoveFloor_X_Long")
				{
					// 移動床(X軸)(長距離)の場合
					/* "オブジェクト管理"に移動床を追加 */
					Gimmick_MoveFloor* pPlatform = new Gimmick_MoveFloor();
					this->ObjectList->SetPlatform(pPlatform);

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);

					/* 移動方向設定 */
					pPlatform->SetupMoveDirection(false, GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_LONG);
				}
				else if (name == "MoveFloor_X_Normal")
				{
					// 移動床(X軸)(通常)の場合
					/* "オブジェクト管理"に移動床を追加 */
					Gimmick_MoveFloor* pPlatform = new Gimmick_MoveFloor();
					this->ObjectList->SetPlatform(pPlatform);

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);

					/* 移動方向設定 */
					pPlatform->SetupMoveDirection(false, GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_NORMAL);
				}
				else if (name == "MoveFloor_X_Short")
				{
					// 移動床(X軸)(短距離)の場合
					/* "オブジェクト管理"に移動床を追加 */
					Gimmick_MoveFloor* pPlatform = new Gimmick_MoveFloor();
					this->ObjectList->SetPlatform(pPlatform);

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);

					/* 移動方向設定 */
					pPlatform->SetupMoveDirection(false, GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_SHORT);
				}
				else if (name == "MoveFloor_Y_Long")
				{
					// 移動床(Y軸)(長距離)の場合
					/* "オブジェクト管理"に移動床を追加 */
					Gimmick_MoveFloor* pPlatform = new Gimmick_MoveFloor();
					this->ObjectList->SetPlatform(pPlatform);

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);

					/* 移動方向設定 */
					pPlatform->SetupMoveDirection(true, GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_LONG);
				}
				else if (name == "MoveFloor_Y_Normal")
				{
					// 移動床(Y軸)(通常)の場合
					/* "オブジェクト管理"に移動床を追加 */
					Gimmick_MoveFloor* pPlatform = new Gimmick_MoveFloor();
					this->ObjectList->SetPlatform(pPlatform);

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);

					/* 移動方向設定 */
					pPlatform->SetupMoveDirection(true, GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_NORMAL);
				}
				else if (name == "MoveFloor_Y_Short")
				{
					// 移動床(Y軸)(短距離)の場合
					/* "オブジェクト管理"に移動床を追加 */
					Gimmick_MoveFloor* pPlatform = new Gimmick_MoveFloor();
					this->ObjectList->SetPlatform(pPlatform);

					/* 座標 */
					pPlatform->SetPosition(vecPos);

					/* 回転量 */
					pPlatform->SetRotation(vecRot);

					/* 拡大率 */
					pPlatform->SetScale(vecScale);

					/* 移動方向設定 */
					pPlatform->SetupMoveDirection(true, GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_SHORT);
				}
				else if (name == "Blood")
				{
					// ブラッド(ピックアップアイテム)スポナーの場合
					/* "オブジェクト管理"にブラッド(ピックアップアイテム)スポナーを追加 */
					SpawnPoint_Blood_PickupItem* pBlood = new SpawnPoint_Blood_PickupItem();
					ObjectList->SetSpawnPoint(pBlood);

					/* 座標設定 */
					pBlood->SetPosition(vecPos);

					/* 回転量設定 */
					pBlood->SetRotation(vecRot);
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
			pSkySqhere->SetModelHandle(this->ModelList->iGetModel("SkySqhere/SkySphere"));

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
