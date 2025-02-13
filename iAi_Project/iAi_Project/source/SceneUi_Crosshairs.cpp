/* 2025.01.27 ファイル作成 駒沢風助 */

#include "SceneUi_Crosshairs.h"

/* UI(クロスヘア)クラスの定義 */

// コンストラクタ
SceneUi_Crosshairs::SceneUi_Crosshairs() : SceneBase("UI_Crosshairs", 100, false)
{
	/* データリスト取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ゲーム状態管理"を取得 */
		this->GameStatusList	= dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 中心クロスヘア */
		this->ipCgHandle_Flont			= ImageList->piGetImage("Test/Front");

		/* ロックオン対象(メイン)クロスヘア */
		this->ipCgHandle_Target_Main	= ImageList->piGetImage("Test/Target_Main");

		/* ロックオン対象(サブ)クロスヘア */
		this->ipCgHandle_Target_Sub		= ImageList->piGetImage("Test/Target_Sub");
	}
}

// 計算
void SceneUi_Crosshairs::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->GameStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}

	/* 最も画面の中心点から近いエネミーを取得する */
	NearEnemy stNearEnemy = { nullptr, 0.f };

	/* 強攻撃ロックオン使用フラグを確認 */
	if (this->PlayerStatusList->bGetMeleeSearchCollisionUseFlg() == true)
	{
		// 使用する場合
		/* エネミーリストを取得 */
		auto& EnemyList = ObjectList->GetEnemyList();

		/* ロックオン範囲内のエネミーのうち最も画面中央に近いエネミーをロックオン対象に設定 */
		for (auto* enemy : EnemyList)
		{
			/* ロックオン範囲に接触しているか確認 */
			if (enemy->HitCheck(this->PlayerStatusList->stGetMeleeSearchCollision()) == true)
			{
				// 接触している場合
				/* プレイヤー視点でのロックオン状態を"ロックオン範囲内である"に設定 */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_RANGE);

				// ロックオン範囲内である場合
				/* コアのワールド座標を取得 */
				VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* コアの座標をスクリーン座標に変換 */
				VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

				/* スクリーン座標が有効であるか確認 */
				// ※スクリーン座標のZ軸が0.0f以下、あるいは1.0f以上であるならば無効となる
				if (0.f < vecCoreScreen.z && vecCoreScreen.z < 1.f)
				{
					// 有効である場合
					/* 画面の中心との差を求める */
					float fx = vecCoreScreen.x - (SCREEN_SIZE_WIDE / 2.f);
					float fy = vecCoreScreen.y - (SCREEN_SIZE_HEIGHT / 2.f);
					float fDistance = (fx * fx) + (fy * fy);

					/* 現在の最も画面の中心点から近いエネミーよりも画面中央に近いか確認 */
					if (fDistance < stNearEnemy.fDistance || stNearEnemy.pEnemy == nullptr)
					{
						// 近い場合
						/* 最も画面の中心点から近いエネミーを更新 */
						stNearEnemy.pEnemy = enemy;
						stNearEnemy.fDistance = fDistance;
					}
				}
				else
				{
					// 無効である場合
					/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
					enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
				}
			}
			else
			{
				// 接触していない場合
				/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
			}
		}

		/* 最も画面の中心点から近いエネミーをロックオン対象に指定 */
		if (stNearEnemy.pEnemy != nullptr)
		{
			// ロックオン対象が存在する場合
			/* プレイヤー視点でのロックオン状態を"ロックオンされている"に設定 */
			stNearEnemy.pEnemy->SetPlayerLockOnType(PLAYER_LOCKON_TARGET);
		}
	}
	else
	{
		// 使用しない場合
		/* ロックオン対象のエネミーを取得 */
		EnemyBasic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

		/* ロックオン対象のエネミーが存在するか確認 */
		if (pLockOnEnemy != nullptr)
		{
			/* ロックオン対象のエネミーをロックオン対象外に変更 */
			pLockOnEnemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);

			/* ロックオン対象のエネミーを該当無し状態にする */
			this->PlayerStatusList->SetPlayerLockOnEnemy(nullptr);
		}
	}

	/* ロックオン対象のエネミーをデータリストに設定する */
	this->PlayerStatusList->SetPlayerLockOnEnemy(stNearEnemy.pEnemy);
}

// 描画
void SceneUi_Crosshairs::Draw()
{
	/* エネミーのロックオン描写 */
	Draw_RockOn();

	/* カメラモードが構え"ズーム"であるか確認 */	
	if (this->PlayerStatusList->iGetCameraMode() == CAMERA_MODE_AIM)
	{
		// 構え"ズーム"である場合
		/* 溜め攻撃による移動後座標を描写 */
		Draw_Move();
	}
}

// 描写(ロックオンエネミー)
void SceneUi_Crosshairs::Draw_RockOn()
{
	/* 画像サイズ取得用変数 */
	int iCgSizeX, iCgSizeY;

	/* エネミーリストを取得 */
	auto& EnemyList = ObjectList->GetEnemyList();

	/* ロックオン範囲内、ロックオン対象のエネミーのコアにクロスヘアを合わせて描写 */
	for (auto* enemy : EnemyList)
	{
		/* プレイヤー視点でのロックオン状態を取得 */
		int iLockOnType = enemy->iGetPlayerLockOnType();
		VECTOR vecCoreWord;
		VECTOR vecCoreScreen;

		/* ロックオン状態によって描写を変更 */
		switch (iLockOnType)
		{
			case PLAYER_LOCKON_NONE:
				// ロックオンされていない場合
				break;

			case PLAYER_LOCKON_RANGE:
				// ロックオン範囲内である場合
				/* コアのワールド座標を取得 */
				vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* コアの座標をスクリーン座標に変換 */
				vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

				/* クロスヘア(ロックオン対象(サブ))を描写 */
				GetGraphSize(*this->ipCgHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
				DrawGraph(vecCoreScreen.x - (iCgSizeX / 2), vecCoreScreen.y - (iCgSizeY / 2), *this->ipCgHandle_Target_Sub, TRUE);
				break;

			case PLAYER_LOCKON_TARGET:
				// ロックオン対象である場合
				/* コアのワールド座標を取得 */
				vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* コアの座標をスクリーン座標に変換 */
				vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

				/* クロスヘア(ロックオン対象(サブ))を描写 */
				GetGraphSize(*this->ipCgHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
				DrawGraph(vecCoreScreen.x - (iCgSizeX / 2), vecCoreScreen.y - (iCgSizeY / 2), *this->ipCgHandle_Target_Sub, TRUE);

				/* クロスヘア(ロックオン対象(メイン))を描写 */
				GetGraphSize(*this->ipCgHandle_Target_Main, &iCgSizeX, &iCgSizeY);
				DrawGraph(vecCoreScreen.x - (iCgSizeX / 2), vecCoreScreen.y - (iCgSizeY / 2), *this->ipCgHandle_Target_Main, TRUE);
				break;
		}
	}

	/* クロスヘア(中心)を描写 */
	GetGraphSize(*this->ipCgHandle_Flont, &iCgSizeX, &iCgSizeY);
	DrawGraph((SCREEN_SIZE_WIDE / 2) - (iCgSizeX / 2), (SCREEN_SIZE_HEIGHT / 2) - (iCgSizeY / 2), *this->ipCgHandle_Flont, TRUE);
}

// 描写(溜め攻撃の移動後座標)
void SceneUi_Crosshairs::Draw_Move()
{
	///* プレイヤーの座標を取得 */
	//VECTOR vecPlayer = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	///* 移動後の座標の座標を取得 */
	//VECTOR vecTarget = VAdd(this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove(), vecPlayer);

	///* 現在の座標と移動後の座標間の四角形を描写 */
	//// ※仮作成(ポリゴンにする予定)
	//VECTOR Pos[4];

	//Pos[0] = VAdd(vecPlayer, VGet(PLAYER_WIDE, 0, PLAYER_WIDE));
	//Pos[1] = VAdd(vecPlayer, VGet(-PLAYER_WIDE, 0, -PLAYER_WIDE));

	//Pos[2] = VAdd(vecTarget, VGet(PLAYER_WIDE, 0, PLAYER_WIDE));
	//Pos[3] = VAdd(vecTarget, VGet(-PLAYER_WIDE, 0, -PLAYER_WIDE));

	//DrawTriangle3D(Pos[0], Pos[1], Pos[2], GetColor(255, 255, 255), TRUE);
	//DrawTriangle3D(Pos[3], Pos[2], Pos[1], GetColor(255, 255, 255), TRUE);

	//DrawLine3D(vecPlayer, vecTarget, GetColor(255, 255, 255));
}
