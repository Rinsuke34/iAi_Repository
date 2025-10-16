/* 2025.01.27 ファイル作成 駒沢風助 */
/* 2025.02.17 遠距離攻撃関連の処理追加 菊池雅道 */
/* 2025.02.28 遠距離攻撃関連の処理追加 菊池雅道 */
/* 2025.03.23 プラットフォームの判定追加 菊池雅道 */
/* 2025.03.26  ロックオン処理修正 菊池雅道 */

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

		/* "ステージ状態管理"を取得 */
		this->StageStatusList	= dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 中心クロスヘア */
		this->piGrHandle_Flont			= ImageList->piGetImage("UI_Crosshairs/UI_Reticle_Dot/UI_Reticle_Dot");

		/* ロックオン対象(メイン)クロスヘア */
		this->piGrHandle_Target_Main	= ImageList->piGetImage("UI_Crosshairs/UI_Reticle_EnemyOUT/UI_Reticle_EnemyOUT");

		/* ロックオン対象(サブ)クロスヘア */
		this->piGrHandle_Target_Sub		= ImageList->piGetImage("UI_Crosshairs/UI_Reticle_EnemyIN_LRed/UI_Reticle_EnemyIN_LRed");

		/* クナイ残段無し表示 */
		this->piGrHandle_Kunai_Zero		= ImageList->piGetImage("UI_Crosshairs/UI_Kunai_Zero");
	}
}

/* 2025.02.17 菊池雅道 遠距離攻撃関連の処理追加 開始 */
/* 2025.02.28 菊池雅道 遠距離攻撃関連の処理追加 開始 */
/* 2025.03.23 菊池雅道 プラットフォームの判定追加 開始 */
/* 2025.03.26 菊池雅道 ロックオン処理修正 開始 */
// 計算
void SceneUi_Crosshairs::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
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

		/* プラットフォームを取得 */
		auto& PlatformList = ObjectList->GetPlatformList();

		/* ロックオン範囲内のエネミーのうち最も画面中央に近いエネミーをロックオン対象に設定 */
		for (auto* enemy : EnemyList)
		{
			/* 対象のエネミーの死亡フラグが有効であるか確認 */
			if (enemy->bGetDeadFlg() == true)
			{
				// 有効である場合
				/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);

				/* 判定の対象外とする */
				continue;
			}

			/* コアのワールド座標を取得 */
			VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

			/* コアの座標をスクリーン座標に変換 */
			VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

			/* ロックオン範囲に接触しているか確認 */
			if (enemy->HitCheck(this->PlayerStatusList->stGetMeleeSearchCollision()) == true)
			{
				// 接触している場合
				// 敵との間に障害物が存在するか確認する
				/* 障害物を確認する線分コリジョンを設定 */
				COLLISION_LINE stCollisionLine;

				/* 線分の開始点を設定(プレイヤー位置) */
				stCollisionLine.vecLineStart = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

				/* 線分の開始点の高さはプレイヤーの身長の半分にする(足元だと接触判定が適切にできないため) */
				stCollisionLine.vecLineStart.y += PLAYER_HEIGHT / 2;

				/* 線分の終了点を設定(敵の位置) */
				stCollisionLine.vecLineEnd = vecCoreWord;

				 /* プラットフォームが存在するか確認する */
				for (auto* platform : PlatformList)
				{
					/* 線分プラットフォームと接触しているか確認 */
					MV1_COLL_RESULT_POLY stHitPoly = platform->HitCheck_Line(stCollisionLine);

					/* 接触フラグを確認する */
					if (stHitPoly.HitFlag == true)
					{
						// 接触している場合
						/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
						enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);

						/* ループを抜ける(次の敵へ) */
						return;
					}
					else
					{
						
						// 接触していない場合
					/* プレイヤー視点でのロックオン状態を"ロックオン範囲内である"に設定 */
						enemy->SetPlayerLockOnType(PLAYER_LOCKON_RANGE);

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
	/* カメラモードが構え(クナイ構え)か確認 */
	else if ((this->StageStatusList->iGetCameraMode() == CAMERA_MODE_AIM_KUNAI))
	{
		
		// 構え(クナイ構え)の場合
		/* エネミーリストを取得 */
		auto& EnemyList = ObjectList->GetEnemyList();

		/* プラットフォームを取得 */
		auto& PlatformList = ObjectList->GetPlatformList();

		/* プレイヤーを取得 */
		CharacterBase* pPlayer = (ObjectList->GetCharacterPlayer());

		/* スクリーンのロックオン範囲内のエネミーのうち最もレティクル(画面の中心的)に近いエネミーをロックオン対象に設定 */
		for (auto* enemy : EnemyList)
		{
			/* 対象のエネミーの死亡フラグが有効であるか確認 */
			if (enemy->bGetDeadFlg() == true)
			{
				// 有効である場合
				/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
				/* 判定の対象外とする */
				continue;
			}

			/* コアのワールド座標を取得 */
			VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

			/* コアの座標をスクリーン座標に変換 */
			VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

			/* プレイヤーからエネミーへのベクトルを取得 */
			VECTOR vecDistance = VSub(vecCoreWord, pPlayer->vecGetPosition());

			/* プレイヤーとエネミーの距離を取得 */
			float fDistance = VSize(vecDistance);

			/* スクリーンのロックオン範囲に接触しているか確認 */
			if (vecCoreScreen.x >= SCREEN_SIZE_WIDE / 2.f - 200 && vecCoreScreen.x <= SCREEN_SIZE_WIDE / 2.f + 200 && vecCoreScreen.y >= SCREEN_SIZE_HEIGHT / 2.f -200 && vecCoreScreen.y<= SCREEN_SIZE_HEIGHT / 2.f + 200)
			{
				// 接触している場合
				/* プレイヤーとエネミーの距離が射程範囲内であるか確認 */
				if (fDistance < PLAYER_LOCKON_RADIUS)
				{
					// 射程範囲内である場合
					// 敵との間に障害物が存在するか確認する
					/* 障害物を確認する線分コリジョンを設定 */
					COLLISION_LINE stCollisionLine;

					/* 線分の開始点を設定(カメラ位置) */
					stCollisionLine.vecLineStart = this->StageStatusList->vecGetCameraPosition();

					/* 線分の終了点を設定(敵の位置) */
					stCollisionLine.vecLineEnd = vecCoreWord;

					// プラットフォームが存在するか確認する
					for (auto* platform : PlatformList)
					{
						/* 線分プラットフォームと接触しているか確認 */
						MV1_COLL_RESULT_POLY stHitPoly = platform->HitCheck_Line(stCollisionLine);

						/* 接触フラグを確認する */
						if (stHitPoly.HitFlag == true)
						{
							// 接触している場合
							/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
							enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
							
							/* 処理を終了する */
							return;
						}
						else
						{
							// 接触していない場合
							/* プレイヤー視点でのロックオン状態を"ロックオン範囲内である"に設定 */
							enemy->SetPlayerLockOnType(PLAYER_LOCKON_RANGE);	

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
					}	
				}
			else
			{
				// 接触していない場合
				/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
			}
		}
			else
			{
				// 射程範囲でない場合
				/* プレイヤー視点でのロックオン状態を"ロックオンされていない"に設定 */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
			}
		}
		/* 最もレティクル画面の中心点から近いエネミーをロックオン対象に指定 */
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
		Enemy_Basic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

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
/* 2025.02.17 菊池雅道 遠距離攻撃関連の処理追加 終了 */
/* 2025.02.28 菊池雅道 遠距離攻撃関連の処理追加 終了 */
/* 2025.03.23 菊池雅道 プラットフォームの判定追加 終了 */
/* 2025.03.26 菊池雅道 ロックオン処理修正 終了 */

// 描画
void SceneUi_Crosshairs::Draw()
{
	/* カメラモードが構え(近接攻撃構え)であるか確認 */	
	if (this->StageStatusList->iGetCameraMode() == CAMERA_MODE_AIM_MELEE)
	{
		// 構え(近接攻撃構え)である場合
		/* エネミーのロックオン描写 */
		Draw_RockOn_Melee();

		/* 溜め攻撃による移動後座標を描写 */
		Draw_Move();
	}

	/* カメラモードが構え(クナイ構え)であるか確認 */
	if (this->StageStatusList->iGetCameraMode() == CAMERA_MODE_AIM_KUNAI)
	{
		// 構え(クナイ構え)である場合
		/* エネミーのロックオン描写 */
		Draw_RockOn_Kunai();
	}
}

// 描写(近接攻撃の溜め時のロックオンエネミー)
void SceneUi_Crosshairs::Draw_RockOn_Melee()
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
				GetGraphSize(*this->piGrHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
				DrawGraph((int)vecCoreScreen.x - (iCgSizeX / 2), (int)vecCoreScreen.y - (iCgSizeY / 2), *this->piGrHandle_Target_Sub, TRUE);
				break;

			case PLAYER_LOCKON_TARGET:
				// ロックオン対象である場合
				/* コアのワールド座標を取得 */
				vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* コアの座標をスクリーン座標に変換 */
				vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

				/* クロスヘア(ロックオン対象(サブ))を描写 */
				GetGraphSize(*this->piGrHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
				DrawGraph((int)vecCoreScreen.x - (iCgSizeX / 2), (int)vecCoreScreen.y - (iCgSizeY / 2), *this->piGrHandle_Target_Sub, TRUE);

				/* クロスヘア(ロックオン対象(メイン))を描写 */
				GetGraphSize(*this->piGrHandle_Target_Main, &iCgSizeX, &iCgSizeY);
				DrawGraph((int)vecCoreScreen.x - (iCgSizeX / 2), (int)vecCoreScreen.y - (iCgSizeY / 2), *this->piGrHandle_Target_Main, TRUE);
				break;
		}
	}

	/* クロスヘア(中心)を描写 */
	GetGraphSize(*this->piGrHandle_Flont, &iCgSizeX, &iCgSizeY);
	DrawGraph((SCREEN_SIZE_WIDE / 2) - (iCgSizeX / 2), (SCREEN_SIZE_HEIGHT / 2) - (iCgSizeY / 2), *this->piGrHandle_Flont, TRUE);
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

/* 2025.02.17 菊池雅道 遠距離攻撃関連の処理追加 開始 */
// 描写(遠距離攻撃の溜め時のロックオンエネミー)
void SceneUi_Crosshairs::Draw_RockOn_Kunai()
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
			GetGraphSize(*this->piGrHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
			DrawGraph((int)vecCoreScreen.x - (iCgSizeX / 2), (int)vecCoreScreen.y - (iCgSizeY / 2), *this->piGrHandle_Target_Sub, TRUE);
			break;

		case PLAYER_LOCKON_TARGET:
			// ロックオン対象である場合
			/* コアのワールド座標を取得 */
			vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

			/* コアの座標をスクリーン座標に変換 */
			vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

			/* クロスヘア(ロックオン対象(サブ))を描写 */
			GetGraphSize(*this->piGrHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
			DrawGraph((int)vecCoreScreen.x - (iCgSizeX / 2), (int)vecCoreScreen.y - (iCgSizeY / 2), *this->piGrHandle_Target_Sub, TRUE);

			/* クロスヘア(ロックオン対象(メイン))を描写 */
			GetGraphSize(*this->piGrHandle_Target_Main, &iCgSizeX, &iCgSizeY);
			DrawGraph((int)vecCoreScreen.x - (iCgSizeX / 2), (int)vecCoreScreen.y - (iCgSizeY / 2), *this->piGrHandle_Target_Main, TRUE);
			break;
		}
	}

	/* クロスヘア(中心)を描写 */
	GetGraphSize(*this->piGrHandle_Flont, &iCgSizeX, &iCgSizeY);
	DrawGraph((SCREEN_SIZE_WIDE / 2) - (iCgSizeX / 2), (SCREEN_SIZE_HEIGHT / 2) - (iCgSizeY / 2), *this->piGrHandle_Flont, TRUE);

	/* 所持クナイ本数が0本であるか確認 */
	if (this->PlayerStatusList->iGetNowHaveKunai() <= 0)
	{
		// 0本である場合
		/* クナイ残段無し表示を描写 */
		DrawGraph(890, 400, *this->piGrHandle_Kunai_Zero, TRUE);
	}

}
/* 2025.02.17 菊池雅道 遠距離攻撃関連の処理追加 終了 */