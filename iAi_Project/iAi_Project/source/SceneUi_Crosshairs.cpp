/* 2025.01.27 ファイル作成 駒沢風助 */

#include "SceneUi_Crosshairs.h"

/* UI(クロスヘア)クラスの定義 */

// コンストラクタ
SceneUi_Crosshairs::SceneUi_Crosshairs() : SceneBase("UI_Crosshairs", 10, false)
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

	/* ロックオン対象のエネミーをデータリストに設定する */
	this->PlayerStatusList->SetPlayerLockOnEnemy(stNearEnemy.pEnemy);
}

// 描画
void SceneUi_Crosshairs::Draw()
{
	/* エネミーリストを取得 */
	auto& EnemyList = ObjectList->GetEnemyList();

	/* ロックオン範囲内、ロックオン対象のエネミーのコアにクロスヘアを合わせて描写 */
	for (auto* enemy : EnemyList)
	{
		/* プレイヤー視点でのロックオン状態を取得 */
		int iLockOnType = enemy->iGetPlayerLockOnType();

		/* ロックオン状態によって描写を変更 */
		switch (iLockOnType)
		{
			case PLAYER_LOCKON_NONE:
				// ロックオンされていない場合
				break;

			case PLAYER_LOCKON_RANGE:
				// ロックオン範囲内である場合
				{
					/* コアのワールド座標を取得 */
					VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

					/* コアの座標をスクリーン座標に変換 */
					VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

					/* クロスヘアの代わりに十字架を描写 */
					DrawBox((int)vecCoreScreen.x - 20, (int)vecCoreScreen.y - 2, (int)vecCoreScreen.x + 20, (int)vecCoreScreen.y + 2, GetColor(100, 0, 0), TRUE);
					DrawBox((int)vecCoreScreen.x - 2, (int)vecCoreScreen.y - 20, (int)vecCoreScreen.x + 2, (int)vecCoreScreen.y + 20, GetColor(100, 0, 0), TRUE);
				}
				break;

			case PLAYER_LOCKON_TARGET:
				// ロックオン対象である場合
				{
					/* コアのワールド座標を取得 */
					VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

					/* コアの座標をスクリーン座標に変換 */
					VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

					/* クロスヘアの代わりに十字架を描写 */
					DrawBox((int)vecCoreScreen.x - 20, (int)vecCoreScreen.y - 2, (int)vecCoreScreen.x + 20, (int)vecCoreScreen.y + 2, GetColor(255, 0, 0), TRUE);
					DrawBox((int)vecCoreScreen.x - 2, (int)vecCoreScreen.y - 20, (int)vecCoreScreen.x + 2, (int)vecCoreScreen.y + 20, GetColor(255, 0, 0), TRUE);
				}
				break;
		}
	}

	/* 画面中央にも十字架を作成 */
	DrawBox((SCREEN_SIZE_WIDE / 2) - 20, (SCREEN_SIZE_HEIGHT / 2) - 2, (SCREEN_SIZE_WIDE / 2) + 20, (SCREEN_SIZE_HEIGHT / 2) + 2, GetColor(0, 100, 0), TRUE);
	DrawBox((SCREEN_SIZE_WIDE / 2) - 2, (SCREEN_SIZE_HEIGHT / 2) - 20, (SCREEN_SIZE_WIDE / 2) + 2, (SCREEN_SIZE_HEIGHT / 2) + 20, GetColor(0, 100, 0), TRUE);
}
