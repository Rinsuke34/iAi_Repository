/* 2025.03.26 ファイル作成 駒沢風助 */

#include "SceneUi_Jump.h"

/* UI(ジャンプ回数)クラスの定義 */
// コンストラクタ
SceneUi_Jump::SceneUi_Jump() : SceneBase("UI_Jump", 107, false)
{
	/* データリスト取得 */
	{
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* 画像読み込み */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ジャンプアイコン(有効) */
		this->piGrHandle_Jump_Icon_Valid = ImageList->piGetImage("UI_Player_Jump/UI_Jump_Count");

		/* ジャンプアイコン(無効) */
		this->piGrHandle_Jump_Icon_Invalid = ImageList->piGetImage("UI_Player_Jump/UI_Jump_Count_Empty");
	}
}

// 計算
void SceneUi_Jump::Process()
{
	/* ゲーム状態が"ゲーム実行"以外であるならシーンを削除 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void SceneUi_Jump::Draw()
{
	/* プレイヤーが空中にいるか確認 */
	//if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
	//{
	//	// 空中にいる(着地していない)場合
	//	/* プレイヤーの頭上の座標を取得 */
	//	VECTOR vecPlayerHeadPos = VAdd(this->ObjectList->GetCharacterPlayer()->vecGetPosition(), VGet(0, PLAYER_HEIGHT, 0));

	//	/* プレイヤーの頭上の座標をスクリーン座標に変換 */
	//	VECTOR vecScreenPos = ConvWorldPosToScreenPos(vecPlayerHeadPos);

	//	/* ジャンプ回数最大数を取得 */
	//	int iJumpMax = this->PlayerStatusList->iGetPlayerMaxJumpCount() + this->PlayerStatusList->iGetAddJumpCount();

	//	/* 現在のジャンプ可能回数を取得 */
	//	int iJumpNow = iJumpMax - this->PlayerStatusList->iGetPlayerJumpCount();

	//	/* 最大ジャンプ回数分ジャンプアイコンを描写 */
	//	for (int i = 0; i < iJumpMax; i++)
	//	{
	//		/* 描写座標取得 */
	//		st2DPosition stDrawPos;
	//		stDrawPos.ix = vecScreenPos.x - (iJumpMax * 64) + (i * 64);
	//		stDrawPos.iy = vecScreenPos.y - 32;

	//		/* 描写対象が有効であるか確認 */
	//		if (i <= iJumpNow)
	//		{
	//			// 有効である場合
	//			/* ジャンプアイコン(有効)を描写 */
	//			DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Valid, TRUE);
	//		}
	//		else
	//		{
	//			// 無効である場合
	//			/* ジャンプアイコン(無効)を描写 */
	//			DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Invalid, TRUE);
	//		}
	//	}
	//}
	// 空中にいる(着地していない)場合
	/* プレイヤーが空中にいるか確認 */
	if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
	{
		// 空中にいる(着地していない)場合
		/* プレイヤーの頭上の座標を取得 */
		VECTOR vecPlayerHeadPos = VAdd(this->ObjectList->GetCharacterPlayer()->vecGetPosition(), VGet(0, PLAYER_HEIGHT, 0));

		/* プレイヤーの頭上の座標をスクリーン座標に変換 */
		VECTOR vecScreenPos = ConvWorldPosToScreenPos(vecPlayerHeadPos);

		/* ジャンプ回数最大数を取得 */
		int iJumpMax = this->PlayerStatusList->iGetPlayerMaxJumpCount() + this->PlayerStatusList->iGetAddJumpCount();

		/* 現在のジャンプ可能回数を取得 */
		int iJumpNow = iJumpMax - this->PlayerStatusList->iGetPlayerNowJumpCount();

		/* アイコンの幅 */
		const int iIconWidth = 64;

		/* 描画開始位置を調整（中央配置のため左端をずらす） */
		int iStartX = vecScreenPos.x - (iJumpMax * iIconWidth) / 2;

		/* 最大ジャンプ回数分ジャンプアイコンを描写 */
		for (int i = 0; i < iJumpMax; i++)
		{
			/* 描写座標取得 */
			st2DPosition stDrawPos;
			stDrawPos.ix = iStartX + (i * iIconWidth);
			stDrawPos.iy = vecScreenPos.y - 32;

			/* 右から順に黒色アイコンに変化 */
			if (i < iJumpNow)
			{
				// 残っているジャンプ回数分は有効アイコン
				DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Valid, TRUE);
			}
			else
			{
				// 使ったジャンプ回数分は黒色アイコン（無効）
				DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Invalid, TRUE);
			}
		}
	}


}


