/* 2025.03.16 ファイル作成 駒沢風助 */

#include "SceneUi_Debug_StatusSetup.h"

/* UI(デバッグメニュー/ステータス調整)クラスの定義 */
// コンストラクタ
SceneUi_Debug_StatusSetup::SceneUi_Debug_StatusSetup() : SceneBase("UI_Debug_StatusSetup", 201, true)
{
	/* データリスト取得 */
	{
		/* "プレイヤー状態"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* 初期化 */
	this->iSelectItem	= 0;		// 選択中の項目の番号
	this->bSelectFlg	= false;	// 選択状態であるかのフラグ
}

// デストラクタ
SceneUi_Debug_StatusSetup::~SceneUi_Debug_StatusSetup()
{
	/* jsonファイルを更新 */
	this->PlayerStatusList->SavePlayerStatuxData();

	/* プレイヤーステータスの再読み込み */
	this->PlayerStatusList->LoadPlayerStatuxData();
}

// 計算
void SceneUi_Debug_StatusSetup::Process()
{
	/* 選択状態であるか確認 */
	if (this->bSelectFlg == false)
	{
		// 選択状態でない場合
		/* プレイヤーの入力取得 */
		// 上入力
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
		{
			this->iSelectItem -= 1;
			if (this->iSelectItem < 0)
			{
				this->iSelectItem = 0;
			}
		}

		// 下入力
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
		{
			this->iSelectItem += 1;
			if (this->iSelectItem >= 10)
			{
				this->iSelectItem = 10;
			}
		}

		// 決定
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			/* 選択状態にする */
			this->bSelectFlg = true;
		}

		// キャンセル
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			/* シーンを削除する */
			this->bDeleteFlg = true;
		}
	}
	else
	{
		// 選択状態である場合
		/* 現在の設定値を取得 */
		float fValue = 0.0f;	// 設定値
		bool bIntFlg = false;	// int型であるかのフラグ

		/* 設定値を取得 */
		switch (this->iSelectItem)
		{
			case 0:
				// 移動加速度
				fValue = this->PlayerStatusList->fGetPlayerMoveAcceleration();
				break;
			case 1:
				// ジャンプ速度
				fValue = this->PlayerStatusList->fGetPlayerJumpSpeed();
				break;
			case 2:
				// 落下加速度
				fValue = this->PlayerStatusList->fGetPlayerFallAcceleration();
				break;
			case 3:
				// 最大落下速度
				fValue = this->PlayerStatusList->fGetPlayerMaxFallSpeed();
				break;
			case 4:
				// ジャンプ回数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxJumpCount());
				bIntFlg = true;
				break;
			case 5:
				// 回避速度
				fValue = this->PlayerStatusList->fGetPlayerDodgeSpeed();
				break;
			case 6:
				// 回避フレーム数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxDodgeFlame());
				bIntFlg = true;
				break;
			case 7:
				// 壁キック速度(水平成分
				fValue = this->PlayerStatusList->fGetPlayerKickWallHorizontalSpeed();
			case 8:
				// 壁キック速度(垂直成分)
				fValue = this->PlayerStatusList->fGetPlayerKickWallVerticalSpeed();
				break;
			case 9:
				// 壁キック継続フレーム数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerKickWallFlame());
			case 10:
				// 壁キック入力猶予フレーム数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerKickWallInputMaxFlame());
			case 11:
				// 近距離攻撃(強)に切り替わるチャージフレーム数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMelleStrongChangeChargeFrame());
				bIntFlg = true;
				break;
			case 12:
				// 近距離攻撃(強)の最大チャージフレーム数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMelleStrongMaxChargeFrame());
				bIntFlg = true;
				break;
			case 13:
				// 近距離攻撃(強)の移動スケール
				fValue = this->PlayerStatusList->fGetPlayerMelleStrongMoveScale();
				break;
			case 14:
				// 近距離攻撃(強)の移動速度
				fValue = this->PlayerStatusList->fGetPlayerMeleeStrongMoveSpeed();
				break;
			case 15:
				// 近距離攻撃(強)の連続攻撃最大フレーム数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMeleeStrongContinusMaxFrame());
				bIntFlg = true;
				break;
			case 16:
				// 空中での近接攻撃(強)回数
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount());
				bIntFlg = true;
				break;
			case 17:
				// ロックオン範囲の半径
				fValue = this->PlayerStatusList->fGetPlayerRockOnRadius();
				break;
			case 18:
				// 初期状態クナイ数所持数
				fValue = static_cast<float>(this->PlayerStatusList->iGetStartHaveKunai());
				bIntFlg = true;
				break;
			case 19:
				// 最大クナイ所持数
				fValue = static_cast<float>(this->PlayerStatusList->iGetMaxhaveKunai());
				bIntFlg = true;
				break;
			case 20:
				// 最大HP
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxHp());
				bIntFlg = true;
				break;
			case 21:
				// 最大無敵時間
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());
				bIntFlg = true;
				break;
		}

		// 上入力
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
		{
			if (bIntFlg == true)
			{
				fValue += 1.0f;
			}
			else
			{
				fValue += 0.1f;
			}
		}

		// 下入力
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
		{
			if (bIntFlg == true)
			{
				fValue -= 1.0f;
			}
			else
			{
				fValue -= 0.1f;
			}
		}

		/* 設定値を設定 */
		switch (this->iSelectItem)
		{
			case 0:
				// 移動加速度
				this->PlayerStatusList->SetPlayerMoveAcceleration(fValue);
				break;
			case 1:
				// ジャンプ速度
				this->PlayerStatusList->SetplayerJumpSpeed(fValue);
				break;
			case 2:
				// 落下加速度
				this->PlayerStatusList->SetPlayerFallAcceleration(fValue);
				break;
			case 3:
				// 最大落下速度
				this->PlayerStatusList->SetPlayerMaxFallSpeed(fValue);
				break;
			case 4:
				// ジャンプ回数
				this->PlayerStatusList->SetPlayerMaxJumpCount(static_cast<int>(fValue));
				break;

			case 5:
				// 回避速度
				this->PlayerStatusList->SetPlayerDodgeSpeed(fValue);
				break;
			case 6:
				// 回避フレーム数
				this->PlayerStatusList->SetPlayerMaxDodgeFlame(static_cast<int>(fValue));
				break;
			case 7:
				// 壁キック速度(水平成分)
				this->PlayerStatusList->SetPlayerKickWallHorizontalSpeed(fValue);
				break;
			case 8:
				// 壁キック速度(垂直成分)
				this->PlayerStatusList->SetPlayerKickWallVerticalSpeed(fValue);
				break;
			case 9:
				// 壁キック継続フレーム数
				this->PlayerStatusList->SetPlayerKickWallFlame(static_cast<int>(fValue));
				break;
			case 10:
				// 壁キック入力猶予フレーム数
				this->PlayerStatusList->SetPlyerKickWallInputMaxFrame(static_cast<int>(fValue));
				break;
			case 11:
				// 近距離攻撃(強)に切り替わるチャージフレーム数
				this->PlayerStatusList->SetPlayerMelleStrongChangeChargeFrame(static_cast<int>(fValue));
				break;
			case 12:
				// 近距離攻撃(強)の最大チャージフレーム数
				this->PlayerStatusList->SetPlayerMelleStrongMaxChargeFrame(static_cast<int>(fValue));
				break;
			case 13:
				// 近距離攻撃(強)の移動スケール
				this->PlayerStatusList->SetPlayerMelleStrongMoveScale(fValue);
				break;
			case 14:
				// 近距離攻撃(強)の移動速度
				this->PlayerStatusList->SetPlayerMeleeStrongMoveSpeed(fValue);
				break;
			case 15:
				// 近距離攻撃(強)の連続攻撃最大フレーム数
				this->PlayerStatusList->SetPlayerMeleeStrongContinusMaxFrame(static_cast<int>(fValue));
				break;
			case 16:
				// 空中での近接攻撃(強)回数
				this->PlayerStatusList->SetPlayerMeleeStrongAirMaxCount(static_cast<int>(fValue));
				break;
			case 17:
				// ロックオン範囲の半径
				this->PlayerStatusList->SetPlayerRockOnRadius(fValue);
				break;
			case 18:
				// 初期状態クナイ数所持数
				this->PlayerStatusList->SetStartHaveKunai(static_cast<int>(fValue));
				break;
			case 19:
				// 最大クナイ所持数
				this->PlayerStatusList->SetMaxhaveKunai(static_cast<int>(fValue));
				break;
			case 20:
				// 最大HP
				this->PlayerStatusList->SetPlayerMaxHp(static_cast<int>(fValue));
				break;
			case 21:
				// 最大無敵時間
				this->PlayerStatusList->SetPlayerMaxInvincibleTime(static_cast<int>(fValue));
				break;
			
			
		}

		// キャンセル
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			/* 選択状態を解除 */
			this->bSelectFlg = false;
		}
	}
	
}

// 描画
void SceneUi_Debug_StatusSetup::Draw()
{
	DrawBox(850, 350, 1400, 350 + 16 * 11, GetColor(0, 0, 0), TRUE);
	DrawFormatString(870, 350 + 16 * 0, GetColor(255, 255, 255), "移動加速度");
	DrawFormatString(1200, 350 + 16 * 0, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMoveAcceleration());
	DrawFormatString(870, 350 + 16 * 1, GetColor(255, 255, 255), "ジャンプ速度");
	DrawFormatString(1200, 350 + 16 * 1, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerJumpSpeed());
	DrawFormatString(870, 350 + 16 * 2, GetColor(255, 255, 255), "落下加速度");
	DrawFormatString(1200, 350 + 16 * 2, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerFallAcceleration());
	DrawFormatString(870, 350 + 16 * 3, GetColor(255, 255, 255), "最大落下速度");
	DrawFormatString(1200, 350 + 16 * 3, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMaxFallSpeed());
	DrawFormatString(870, 350 + 16 * 4, GetColor(255, 255, 255), "ジャンプ回数");
	DrawFormatString(1200, 350 + 16 * 4, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxJumpCount());
	DrawFormatString(870, 350 + 16 * 5, GetColor(255, 255, 255), "回避速度");
	DrawFormatString(1200, 350 + 16 * 5, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerDodgeSpeed());
	DrawFormatString(870, 350 + 16 * 6, GetColor(255, 255, 255), "回避フレーム数");
	DrawFormatString(1200, 350 + 16 * 6, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxDodgeFlame());
	DrawFormatString(870, 350 + 16 * 7, GetColor(255, 255, 255), "壁キック速度(水平成分)");
	DrawFormatString(1200, 350 + 16 * 7, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerKickWallHorizontalSpeed());
	DrawFormatString(870, 350 + 16 * 8, GetColor(255, 255, 255), "壁キック速度(垂直成分)");
	DrawFormatString(1200, 350 + 16 * 8, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerKickWallVerticalSpeed());
	DrawFormatString(870, 350 + 16 * 9, GetColor(255, 255, 255), "壁キック継続フレーム数");
	DrawFormatString(1200, 350 + 16 * 9, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerKickWallFlame());
	DrawFormatString(870, 350 + 16 * 10, GetColor(255, 255, 255), "壁キック入力猶予フレーム数");
	DrawFormatString(1200, 350 + 16 * 10, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerKickWallInputMaxFlame());
	DrawFormatString(870, 350 + 16 * 11, GetColor(255, 255, 255), "近距離攻撃(強)に切り替わるチャージフレーム数");
	DrawFormatString(1200, 350 + 16 * 11, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMelleStrongChangeChargeFrame());
	DrawFormatString(870, 350 + 16 * 12, GetColor(255, 255, 255), "近距離攻撃(強)の最大チャージフレーム数");
	DrawFormatString(1200, 350 + 16 * 12, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMelleStrongMaxChargeFrame());
	DrawFormatString(870, 350 + 16 * 13, GetColor(255, 255, 255), "近距離攻撃(強)の移動スケール");
	DrawFormatString(1200, 350 + 16 * 13, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMelleStrongMoveScale());
	DrawFormatString(870, 350 + 16 * 14, GetColor(255, 255, 255), "近距離攻撃(強)の移動速度");
	DrawFormatString(1200, 350 + 16 * 14, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMeleeStrongMoveSpeed());
	DrawFormatString(870, 350 + 16 * 15, GetColor(255, 255, 255), "近距離攻撃(強)の連続攻撃最大フレーム数");
	DrawFormatString(1200, 350 + 16 * 15, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMeleeStrongContinusMaxFrame());
	DrawFormatString(870, 350 + 16 * 16, GetColor(255, 255, 255), "ロックオン範囲の半径");
	DrawFormatString(1200, 350 + 16 * 16, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerRockOnRadius());
	DrawFormatString(870, 350 + 16 * 17, GetColor(255, 255, 255), "最大HP");
	DrawFormatString(1200, 350 + 16 * 17, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxHp());
	DrawFormatString(870, 350 + 16 * 18, GetColor(255, 255, 255), "最大無敵時間");
	DrawFormatString(1200, 350 + 16 * 18, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxInvincibleTime());
	DrawFormatString(870, 350 + 16 * 19, GetColor(255, 255, 255), "空中での近接攻撃(強)回数");
	DrawFormatString(1200, 350 + 16 * 19, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount());
	DrawFormatString(870, 350 + 16 * 20, GetColor(255, 255, 255), "初期状態クナイ数所持数");
	DrawFormatString(1200, 350 + 16 * 20, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetStartHaveKunai());
	DrawFormatString(870, 350 + 16 * 21, GetColor(255, 255, 255), "最大クナイ所持数");
	DrawFormatString(1200, 350 + 16 * 21, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetMaxhaveKunai());

	/* 矢印を描写 */
	if (this->bSelectFlg == true)
	{
		DrawFormatString(850, 350 + 16 * this->iSelectItem, GetColor(255, 0, 0), "→");
	}
	else
	{
		DrawFormatString(850, 350 + 16 * this->iSelectItem, GetColor(255, 255, 255), "→");
	}
}
