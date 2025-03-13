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
	}

	/* 攻撃系モーション */
	{
		///* モーションが変更されているか確認 */
		//if (iMotionNo_Attack != this->PlayerStatusList->iGetPlayerMotion_Attack_Old())
		//{
		//	// 変更されている場合
		//	/* 変更前のモーションをデタッチする */
		//	MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack_Old());

		//	/* 現在のモーション情報を変更前モーションとして保存 */
		//	this->PlayerStatusList->SetMotionCount_Attack_Old(this->PlayerStatusList->fGetMotionTimer_Attack());
		//	this->PlayerStatusList->SetMotionCount_Attack_Old_End(this->PlayerStatusList->fGetMotionTimer_Attack_End());
		//	this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack_Old(this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());

		//	/* 変更したいモーションのモーション番号を取得 */
		//	int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Attack].strMotionName.c_str());

		//	/* モーションをアタッチする */
		//	this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

		//	/* 現在のモーションを更新する */
		//	this->PlayerStatusList->SetPlayerMotion_Attack_Old(iMotionNo_Attack);

		//	/* アニメーションタイマーを初期化する */
		//	this->PlayerStatusList->SetMotionCount_Attack(0.f);

		//	/* アニメーションの終了時間を再設定する */
		//	float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
		//	this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime);

		//	/* モーションブレンド率を初期化する*/
		//	this->PlayerStatusList->SetNowAttackMotionBlendRate(0.f);
		//}

		///* 現在のモーション再生時間を取得 */
		//float fNowMotionTime_Attack = this->PlayerStatusList->fGetMotionTimer_Attack();
		//float fNowMotionTime_Attack_Old = this->PlayerStatusList->fGetMotionTimer_Attack_Old();

		///* モーション時間を進める */
		//fNowMotionTime_Attack += 1.f;
		//fNowMotionTime_Attack_Old += 1.f;

		///* 現在のモーションの再生時間がモーションの終了時間を超えているか確認 */
		//if (fNowMotionTime_Attack > this->PlayerStatusList->fGetMotionTimer_Attack_End())
		//{
		//	// 最大時間を超えている場合
		//	/* 再生時間を初期化 */
		//	fNowMotionTime_Attack = 0.f;

		//	/* モーション番号を変更後の値に設定 */
		//	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_LIST[iMotionNo_Attack].iNextMotionID);
		//}

		///* 変更前のモーションの再生時間がモーションの終了時間を超えているか確認 */
		//if (fNowMotionTime_Attack_Old > this->PlayerStatusList->fGetMotionTimer_Attack_Old_End())
		//{
		//	// 最大時間を超えている場合
		//	/* 再生時間を初期化 */
		//	fNowMotionTime_Attack_Old = 0.f;
		//}

		///* ブレンド率を更新 */
		//float fBlendRate = this->PlayerStatusList->fGetNowAttackMotionBlendRate();

		///* ブレンド率を進める */
		//fBlendRate += 0.1f;

		///* ブレンド率が1.0fを超えているか確認 */
		//if (fBlendRate > 1.0f)
		//{
		//	// 1.0fを超えている場合
		//	/* ブレンド率を1.0fに設定 */
		//	fBlendRate = 1.0f;
		//}

		///* ブレンド率を保存 */
		//this->PlayerStatusList->SetNowAttackMotionBlendRate(fBlendRate);

		///* モーションの再生時間を設定 */
		//this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Attack);
		//this->PlayerStatusList->SetMotionCount_Attack_Old(fNowMotionTime_Attack_Old);

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




	///* 現在のモーション番号を取得 */
	//int iMotionNo_Move = this->PlayerStatusList->iGetPlayerMotion_Move();
	//int iMotionNo_Attack = this->PlayerStatusList->iGetPlayerMotion_Attack();

	///* 移動系モーション */
	//{
	//	/* モーションが変更されているか確認 */
	//	if (iMotionNo_Move != this->PlayerStatusList->iGetPlayerMotion_Move_Old())
	//	{
	//		// 変更されている場合
	//		/* 現在のモーションをデタッチする */
	//		MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

	//		/* 変更したいモーションのモーション番号を取得 */
	//		int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Move].strMotionName.c_str());

	//		/* モーションをアタッチする */
	//		this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

	//		/* 現在のモーションを更新する */
	//		this->PlayerStatusList->SetPlayerMotion_Move_Old(iMotionNo_Move);

	//		/* アニメーションタイマーを初期化する */
	//		this->PlayerStatusList->SetMotionCount_Move(0.f);

	//		/* アニメーションの終了時間を再設定する */
	//		float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());
	//		this->PlayerStatusList->SetMotionCount_Move_End(fEndTime);
	//	}

	//	/* 現在のモーション再生時間を取得 */
	//	float fNowMotionTime_Move = this->PlayerStatusList->fGetMotionTimer_Move();

	//	/* モーション時間を進める */
	//	fNowMotionTime_Move += 1.f;

	//	/* モーションの再生時間がモーションの終了時間を超えているか確認 */
	//	if (fNowMotionTime_Move > this->PlayerStatusList->fGetMotionTimer_Move_End())
	//	{
	//		// 最大時間を超えている場合
	//		/* プレイヤーモーションが"死亡"以外であるか確認 */
	//		if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_DIE)
	//		{
	//			// "死亡"以外である場合
	//			/* 再生時間を初期化 */
	//			fNowMotionTime_Move = 0.f;
	//		}
	//		else
	//		{
	//			// "死亡"である場合
	//			/* 再生時間を最後の時間で停止 */
	//			fNowMotionTime_Move -= 1.f;

	//			/* 死亡フラグを有効にする */
	//			this->PlayerStatusList->SetPlayerDeadFlg(true);
	//		}

	//		/* モーション番号を変更後の値に設定 */
	//		this->PlayerStatusList->SetPlayerMotion_Move(MOTION_LIST[iMotionNo_Move].iNextMotionID);
	//	}

	//	/* モーションの再生時間を設定 */
	//	this->PlayerStatusList->SetMotionCount_Move(fNowMotionTime_Move);
	//}

	///* 攻撃系モーション */
	//{
	//	/* モーションが変更されているか確認 */
	//	if (iMotionNo_Attack != this->PlayerStatusList->iGetPlayerMotion_Attack_Old())
	//	{
	//		// 変更されている場合
	//		/* 現在のモーションをデタッチする */
	//		MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());

	//		/* 変更したいモーションのモーション番号を取得 */
	//		int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Attack].strMotionName.c_str());

	//		/* モーションをアタッチする */
	//		this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

	//		/* 現在のモーションを更新する */
	//		this->PlayerStatusList->SetPlayerMotion_Attack_Old(iMotionNo_Attack);

	//		/* アニメーションタイマーを初期化する */
	//		this->PlayerStatusList->SetMotionCount_Attack(0.f);

	//		/* アニメーションの終了時間を再設定する */
	//		float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
	//		this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime);
	//	}

	//	/* 現在のモーション再生時間を取得 */
	//	float fNowMotionTime_Attack = this->PlayerStatusList->fGetMotionTimer_Attack();

	//	/* モーション時間を進める */
	//	fNowMotionTime_Attack += 1.f;

	//	/* モーションの再生時間がモーションの終了時間を超えているか確認 */
	//	if (fNowMotionTime_Attack > this->PlayerStatusList->fGetMotionTimer_Attack_End())
	//	{
	//		// 最大時間を超えている場合
	//		/* 再生時間を初期化 */
	//		fNowMotionTime_Attack = 0.f;

	//		/* モーション番号を変更後の値に設定 */
	//		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_LIST[iMotionNo_Attack].iNextMotionID);
	//	}

	//	/* モーションの再生時間を設定 */
	//	this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Attack);
	//}

	///* 現在のモーションの武器を手に持っているかのフラグを確認 */
	//if (MOTION_LIST[iMotionNo_Attack].bWeponHandFlg == true)
	//{
	//	// 表示フラグが有効である場合
	//	/* 右手の刀を表示する */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, TRUE);

	//	/* 背面の刀を非表示にする */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, FALSE);
	//}
	//else
	//{
	//	// 表示フラグが無効である場合
	//	/* 右手の刀を非表示にする */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, FALSE);

	//	/* 背面の刀を表示する */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, TRUE);
	//}

	///* 現在クナイを所持している状態であるか確認 */
	//if (this->PlayerStatusList->iGetNowHaveKunai() > 0)
	//{
	//	// 所持している場合
	//	/* 手のクナイを表示する */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, TRUE);
	//}
	//else
	//{
	//	// 所持していない場合
	//	/* 手のクナイを非表示にする */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, FALSE);
	//}
}
