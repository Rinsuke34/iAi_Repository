/* 2025.01.27 駒沢風助 ファイル作成 */

#include "Enemy_Basic.h"

/* 基本エネミークラスの定義 */

// コンストラクタ
Enemy_Basic::Enemy_Basic() : EnemyBase()
{
	/* データリストを取得 */
	{
		/* "オブジェクト管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "オプション設定管理"を取得 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));

		/* "オブジェクト管理"を取得 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* 初期化 */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ロックオンされていない状態にする
	this->iCoreFrameNo		= -1;					// コアフレーム番号を初期化
	this->bDeadFlg			= false;				// 死亡フラグ
	this->iBloodAmount		= 0;					// ブラッド量
}

// 発光描写
void Enemy_Basic::BloomDraw()
{
	/* カメラ位置からの距離を取得 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* カメラからの距離との距離がエネミー描写距離の範囲内であるか */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* 発光部分の描写 */
		CharacterBase::BloomDraw();
	}
}

// 当たり判定描写
void Enemy_Basic::CollisionDraw()
{
	/* カメラ位置からの距離を取得 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* カメラからの距離との距離がエネミー描写距離の範囲内であるか */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* 当たり判定の描写 */
		CharacterBase::CollisionDraw();
	}
}

// 描写
void Enemy_Basic::Draw()
{
	/* カメラ位置からの距離を取得 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* カメラからの距離との距離がエネミー描写距離の範囲内であるか */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* 描写 */
		CharacterBase::Draw();
	}
}

// リセット処理
void Enemy_Basic::Reset()
{
	/* このオブジェクトの削除フラグを有効にする */
	this->bDeleteFlg = true;
}

// 敵撃破時の処理
void Enemy_Basic::Defeat()
{
	/* データリスト取得 */
	DataList_PlayerStatus* PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* データリストが存在しない(強制終了された)場合は処理を終了する */
	if (PlayerStatusList == nullptr)
	{
		return;
	}

	/* プレイヤーのコンボ数加算＆継続時間リセット */
	{
		/* プレイヤーのコンボ数加算 */
		PlayerStatusList->SetPlayerComboNowCount(PlayerStatusList->iGetPlayerComboNowCount() + 1);

		/* プレイヤーのコンボ継続時間リセット */
		PlayerStatusList->SetPlayerComboDuration(INIT_ATTRIBUTES_COMBO_DURATION);
	}

	/* 爆発エフェクト生成 */
	{
		/* 時間経過で削除されるエフェクトを追加 */
		EffectSelfDelete* AddEffect = new EffectSelfDelete();

		/* エフェクト読み込み */
		AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die/FX_e_die")));

		/* エフェクトの座標設定 */
		AddEffect->SetPosition(this->vecPosition);

		/* エフェクトの回転量設定 */
		AddEffect->SetRotation(this->vecRotation);

		/* エフェクトの削除されるまでの時間を設定 */
		AddEffect->SetDeleteCount(75);

		/* エフェクトの初期化 */
		AddEffect->Initialization();

		/* リストに登録 */
		{
			/* "オブジェクト管理"データリストを取得 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffect(AddEffect);
		}
	}

	/* ブラッド(ゲーム内通貨)を作成 */
	{
		/* "オブジェクト管理"データリストを取得 */
		DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* プレイヤーのコンボランクを取得 */
		int iComboRank = PlayerStatusList->iGetPlayerComboRunk();

		/* ブラッドの生成数を算出 */
		// 基本のブラッド生成数
		int iBloodAmount = this->iBloodAmount;
		// プレイヤーのエディットによるブラッド生成数の加算
		iBloodAmount += PlayerStatusList->iGetAddBlood();

		/* コンボランクが"無し"以外であるか確認 */
		if (iComboRank != COMBO_RANK_NONE)
		{
			// コンボランクが"無し"以外である場合
			// コンボランクに応じたブラッド生成数を乗算
			iBloodAmount *= COMBO_RANK_MAX - iComboRank;
		}

		/* ブラッドの生成 */
		for (int i = 0; i < iBloodAmount; i++)
		{
			/* 時間経過で削除されるアイテムを追加 */
			EffectItemBase* AddItem = new EffectItem_Blood();

			/* エフェクトの座標設定 */
			AddItem->SetPosition(this->vecPosition);

			/* エフェクトをリストに登録 */
			ObjectListHandle->SetEffectItem(AddItem);
		}
	}

	/* エネミーの削除フラグを有効にする */
	this->bDeleteFlg = true;
}

// コアフレーム番号取得
void Enemy_Basic::LoadCoreFrameNo()
{
	/* コアフレーム番号を取得 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}

void Enemy_Basic::Enemy_Gravity()
{
	// 移動後の座標を取得(垂直方向)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	// 主人公の上部分の当たり判定から下方向へ向けた線分を作成
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;

	// 足場を取得
	auto& PlatformList = ObjectList->GetPlatformList();

	// 着地する座標
	// 初期値を移動後の座標に設定
	float fStandPosY = vecNextPosition.y;

	// 足場と接触するか確認
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// 接触しているか確認
		if (stHitPolyDim.HitFlag == 1)
		{
			// 接触している場合

			// ヒットした座標が現在の着地座標より高い位置であるか確認
			if (stHitPolyDim.HitPosition.y >= fStandPosY)
			{
				// エネミーのy座標を減算
				this->vecPosition.y = stHitPolyDim.HitPosition.y;
				this->vecMove.y = 0; // 落下速度をリセット

				// ヒットした座標がプレイヤーが歩いて登れる位置より低い位置であるか確認
				if (fStandPosY < this->vecPosition.y + PLAYER_CLIMBED_HEIGHT)
				{
					// 着地座標がプレイヤーの現在位置より低い場合
					// 地面に着地したと判定する
					// 着地座標を着地した座標に更新
					fStandPosY = stHitPolyDim.HitPosition.y;
				}
				else
				{
					// 着地座標がプレイヤーの現在位置より高い場合
					// 着地座標をプレイヤーが天井にめり込まない高さに更新
					fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

					// ループを抜ける
					break;
				}
			}
		}
	}
}