/* 2025.02.07 駒沢風助 ファイル追加 */

#include "CharacterPlayer.h"

// プレイヤーのモーション遷移管理
void CharacterPlayer::Player_Motion_Transition()
{
	/* 現在のモーション番号を取得 */
	int iMotionNo_Move			= this->PlayerStatusList->iGetPlayerMotion_Move();
	int iMotionNo_Attack		= this->PlayerStatusList->iGetPlayerMotion_Attack();

	/* 現在の変更前モーション番号を取得 */
	int iMotionNo_Move_Old		= this->PlayerStatusList->iGetPlayerMotion_Move_Old();
	int iMotionNo_Attack_Old	= this->PlayerStatusList->iGetPlayerMotion_Attack_Old();

	/* 移動系モーション */
	{
		/* モーションが変更されているか確認 */
		if (iMotionNo_Move != this->PlayerStatusList->iGetPlayerMotion_Move_Old())
		{
			// 変更されている場合
			/* 変更前のモーションをデタッチする */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move_Old());

			/* 現在のモーション情報を変更前モーションとして保存 */
			this->PlayerStatusList->SetMotionCount_Move_Old(this->PlayerStatusList->fGetMotionTimer_Move());
			this->PlayerStatusList->SetMotionCount_Move_Old_End(this->PlayerStatusList->fGetMotionTimer_Move_End());
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Move_Old(this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

			/* 変更したいモーションのモーション番号を取得 */
			int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Move].strMotionName.c_str());

			/* モーションをアタッチする */
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

			/* 現在のモーションを更新する */
			this->PlayerStatusList->SetPlayerMotion_Move_Old(iMotionNo_Move);

			/* アニメーションタイマーを初期化する */
			this->PlayerStatusList->SetMotionCount_Move(0.f);

			/* アニメーションの終了時間を再設定する */
			float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());
			this->PlayerStatusList->SetMotionCount_Move_End(fEndTime);

			/* モーションブレンド率を初期化する*/
			this->PlayerStatusList->SetNowMoveMotionBlendRate(0.f);
		}

		/* 現在のモーション再生時間を取得 */
		float fNowMotionTime_Move		= this->PlayerStatusList->fGetMotionTimer_Move();
		float fNowMotionTime_Move_Old	= this->PlayerStatusList->fGetMotionTimer_Move_Old();

		/* モーション時間を進める */
		fNowMotionTime_Move		+= 1.f;
		fNowMotionTime_Move_Old	+= 1.f;

		/* 現在のモーションの再生時間がモーションの終了時間を超えているか確認 */
		if (fNowMotionTime_Move > this->PlayerStatusList->fGetMotionTimer_Move_End())
		{
			// 最大時間を超えている場合
			/* プレイヤーモーションが"死亡"以外であるか確認 */
			if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_DIE)
			{
				// "死亡"以外である場合
				/* 再生時間を初期化 */
				fNowMotionTime_Move = 0.f;
			}
			else
			{
				// "死亡"である場合
				/* 再生時間を最後の時間で停止 */
				fNowMotionTime_Move -= 1.f;

				/* "倒れる"のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_DOWN);

				/* 死亡フラグを有効にする */
				this->PlayerStatusList->SetPlayerDeadFlg(true);
			}

			/* モーション番号を変更後の値に設定 */
			this->PlayerStatusList->SetPlayerMotion_Move(MOTION_LIST[iMotionNo_Move].iNextMotionID);
		}

		/* 変更前のモーションの再生時間がモーションの終了時間を超えているか確認 */
		if (fNowMotionTime_Move_Old > this->PlayerStatusList->fGetMotionTimer_Move_Old_End())
		{
			// 最大時間を超えている場合
			/* 再生時間を初期化 */
			fNowMotionTime_Move_Old = 0.f;
		}

		/* ブレンド率を更新 */
		float fBlendRate = this->PlayerStatusList->fGetNowMoveMotionBlendRate();

		/* ブレンド率を進める */
		fBlendRate += 0.1f;

		/* ブレンド率が1.0fを超えているか確認 */
		if (fBlendRate > 1.0f)
		{
			// 1.0fを超えている場合
			/* ブレンド率を1.0fに設定 */
			fBlendRate = 1.0f;
		}

		/* ブレンド率を保存 */
		this->PlayerStatusList->SetNowMoveMotionBlendRate(fBlendRate);

		/* モーションの再生時間を設定 */
		this->PlayerStatusList->SetMotionCount_Move(fNowMotionTime_Move);
		this->PlayerStatusList->SetMotionCount_Move_Old(fNowMotionTime_Move_Old);

		/* 現在のモーションが"歩行"であるか確認 */
		if (this->PlayerStatusList->iGetPlayerMotion_Move() == MOTION_ID_MOVE_WALK)
		{
			// "歩行"である場合
			/* サウンド"走る"が再生中でないか確認 */
			if (this->bPlayRunSound == false)
			{
				// 再生中である場合
				/* サウンド"走る"を再生 */
				gpDataList_Sound->SE_PlaySound_Loop(SE_PLAYER_RUN);

				/* サウンドを再生中に設定 */
				this->bPlayRunSound = true;
			}
		}
		else
		{
			// "歩行"でない場合
			/* サウンド"走る"が再生中であるか確認 */
			if (this->bPlayRunSound == true)
			{
				// 再生中である場合
				/* サウンド"走る"を停止 */
				gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_RUN);

				/* サウンドポインタを非再生中に設定 */
				this->bPlayRunSound = false;
			}
		}
	}

	/* 攻撃系モーション */
	{
		/* モーションが変更されているか確認 */
		if (iMotionNo_Attack != this->PlayerStatusList->iGetPlayerMotion_Attack_Old())
		{
			// 変更されている場合
			/* 現在のモーションをデタッチする */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());

			/* 変更したいモーションのモーション番号を取得 */
			int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Attack].strMotionName.c_str());

			/* モーションをアタッチする */
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

			/* 現在のモーションを更新する */
			this->PlayerStatusList->SetPlayerMotion_Attack_Old(iMotionNo_Attack);

			/* アニメーションタイマーを初期化する */
			this->PlayerStatusList->SetMotionCount_Attack(0.f);

			/* アニメーションの終了時間を再設定する */
			float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
			this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime);
		}

		/* 現在のモーション再生時間を取得 */
		float fNowMotionTime_Attack = this->PlayerStatusList->fGetMotionTimer_Attack();

		/* モーション時間を進める */
		fNowMotionTime_Attack += 1.f;

		/* モーションの再生時間がモーションの終了時間を超えているか確認 */
		if (fNowMotionTime_Attack > this->PlayerStatusList->fGetMotionTimer_Attack_End())
		{
			// 最大時間を超えている場合
			/* 再生時間を初期化 */
			fNowMotionTime_Attack = 0.f;

			/* モーション番号を変更後の値に設定 */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_LIST[iMotionNo_Attack].iNextMotionID);
		}

		/* モーションの再生時間を設定 */
		this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Attack);

		/* 現在のモーションが"溜め"であるか確認 */
		if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_CHARGE)
		{
			// "溜め"である場合
			/* サウンド"溜め居合チャージ"が再生中でないか確認 */
			if (this->bPlayChargeSound == false)
			{
				// 再生中である場合
				/* サウンド"溜め居合チャージ"を再生 */
				gpDataList_Sound->SE_PlaySound_Loop(SE_PLAYER_CHARGE);
				gpDataList_Sound->SE_PlaySound_Loop(SE_PLAYER_CHARGE_HOLD);

				/* サウンドを再生中に設定 */
				this->bPlayChargeSound = true;
			}
		}
		else
		{
			// "溜め"でない場合
			/* サウンド"溜め居合チャージ"が再生中であるか確認 */
			if (this->bPlayChargeSound == true)
			{
				// 再生中である場合
				/* サウンド"溜め居合チャージ"を停止 */
				gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE);
				gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE_HOLD);

				/* サウンドを非再生中に設定 */
				this->bPlayChargeSound = false;
			}
		}
	}

	/* 現在のモーションの武器を手に持っているかのフラグを確認 */
	if (MOTION_LIST[iMotionNo_Attack].bWeponHandFlg == true)
	{
		// 表示フラグが有効である場合
		/* 右手の刀を表示する */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, TRUE);

		/* 背面の刀を非表示にする */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, FALSE);
	}
	else
	{
		// 表示フラグが無効である場合
		/* 右手の刀を非表示にする */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, FALSE);

		/* 背面の刀を表示する */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, TRUE);
	}

	/* 現在クナイを所持している状態であるか確認 */
	if (this->PlayerStatusList->iGetNowHaveKunai() > 0)
	{
		// 所持している場合
		/* 手のクナイを表示する */
		MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, TRUE);
	}
	else
	{
		// 所持していない場合
		/* 手のクナイを非表示にする */
		MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, FALSE);
	}
}

// シェイプ処理
void CharacterPlayer::Player_Shape()
{
	/* シェイプの適用率軽減処理 */
	{
		/* シェイプが適用されているか確認 */
		if (this->fShapeRate > 0.f)
		{
			// 適用されている場合
			/* シェイプ適用率を減らす */
			this->fShapeRate -= 0.05f;
		}
		else
		{
			// 適用されていない場合
			/* シェイプ適用率を初期化 */
			this->fShapeRate = 0.f;
		}
	}

	/* プレイヤー死亡処理 */
	{
		/* プレイヤーの現在HPが0以下(死亡状態)であるか確認 */
		if (this->PlayerStatusList->iGetPlayerNowHp() <= 0)
		{
			// HPが0以下(死亡状態)である場合
			/* シェイプの適用率が最大値(100%)未満であるか確認 */
			if (this->fShapeRate < 1.f)
			{
				// 超えていない場合
				/* シェイプの適用率を上昇 */
				this->fShapeRate += 0.05f;
			}
			else
			{
				// 超えている場合
				/* シェイプの適用率を最大値(100%)に設定 */
				this->fShapeRate = 1.f;
			}
		}
	}
}

// ゲーム開始時のモーション
void CharacterPlayer::FastMotion()
{
	/* 開始時モーション開始フラグが有効であるか確認 */
	if (this->PlayerStatusList->bGetStartFastMotion() == true)
	{
		// 有効である場合
		/* 開始時モーションカウントを取得 */
		int iFastMotionCount = this->PlayerStatusList->iGetFastMotionCount();

		/* 開始時モーションカウントを減少 */
		iFastMotionCount--;

		/* モーションカウントを設定 */
		this->PlayerStatusList->SetFastMotionCount(iFastMotionCount);

		/* アニメーションタイマーを取得する */
		float fMotionCount = this->PlayerStatusList->fGetMotionTimer_Move();

		/* アニメーションタイマーを進める */
		fMotionCount += 9.f / static_cast<float>(CAMERA_CLOSEUP_COUNT_MAX);

		/* アニメーションタイマーを設定 */
		this->PlayerStatusList->SetMotionCount_Move(fMotionCount);

		/* シェイプ適用率を変更 */
		this->fShapeRate = 1.f - (static_cast<float>(CAMERA_CLOSEUP_COUNT_MAX - iFastMotionCount) / static_cast<float>(CAMERA_CLOSEUP_COUNT_MAX));

		/* 開始時モーションカウントが無効(0以下)であるか確認 */
		if (iFastMotionCount <= 0)
		{
			// 無効である場合
			/* 現在のモーションをデタッチする */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

			/* モーション初期化 */
			MotionReset();

			/* シェイプ適用率を初期化 */
			this->fShapeRate = 0.f;

			/* 発光停止フラグを無効化 */
			this->bBloomStopFlg = false;
		}
	}
}

// モーション初期化
void CharacterPlayer::MotionReset()
{
	/* モーションの初期化処理 */
	{
		/* 初期モーション番号を設定 */
		int iInitialMotionNo_Move = this->PlayerStatusList->iGetPlayerMotion_Move();
		int iInitialMotionNo_Attack = this->PlayerStatusList->iGetPlayerMotion_Attack();

		// モーションのアタッチ
		int iMotionIndex_Move = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iInitialMotionNo_Move].strMotionName.c_str());
		this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(MV1AttachAnim(this->iModelHandle, iMotionIndex_Move, -1));

		int iMotionIndex_Attack = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iInitialMotionNo_Attack].strMotionName.c_str());
		this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex_Attack, -1));

		// モーションタイマーの初期化
		this->PlayerStatusList->SetMotionCount_Move(0.f);
		this->PlayerStatusList->SetMotionCount_Attack(0.f);

		// モーション終了時間の設定
		float fEndTime_Move = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());
		this->PlayerStatusList->SetMotionCount_Move_End(fEndTime_Move);

		float fEndTime_Attack = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
		this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime_Attack);

		// 初期モーション番号を保存
		this->PlayerStatusList->SetPlayerMotion_Move(iInitialMotionNo_Move);
		this->PlayerStatusList->SetPlayerMotion_Move_Old(MOTION_ID_MOVE_LAND);
		this->PlayerStatusList->SetPlayerMotion_Attack(iInitialMotionNo_Attack);
	}
}