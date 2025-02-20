/* 2025.02.07 駒沢風助 ファイル追加 */

#include "CharacterPlayer.h"

/* 2025.01.30 菊池雅道	モーション処理追加 開始 */
// プレイヤーのモーション遷移管理
void CharacterPlayer::Player_Motion_Transition()
{
	/* 現在のモーション番号を取得 */
	int iMotionNo_Move		= this->PlayerStatusList->iGetPlayerMotion_Move();
	int iMotionNo_Attack	= this->PlayerStatusList->iGetPlayerMotion_Attack();

	/* 現在のモーションの総時間を取得 */


	/* 移動系モーション */
	{
		/* モーションが変更されているか確認 */
		if (iMotionNo_Move != this->PlayerStatusList->iGetPlayerMotion_Move_Old())
		{
			// 変更されている場合
			/* 現在のモーションをデタッチする */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

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
		}

		/* 現在のモーション再生時間を取得 */
		float fNowMotionTime_Move = this->PlayerStatusList->fGetMotionTimer_Move();

		/* モーション時間を進める */
		fNowMotionTime_Move += 1.f;

		/* モーションの再生時間がモーションの終了時間を超えているか確認 */
		if (fNowMotionTime_Move > this->PlayerStatusList->fGetMotionTimer_Move_End())
		{
			// 最大時間を超えている場合
			/* 再生時間を初期化 */
			fNowMotionTime_Move = 0.f;

			/* モーション番号を変更後の値に設定 */
			this->PlayerStatusList->SetPlayerMotion_Move(MOTION_LIST[iMotionNo_Move].iNextMotionID);
		}

		/* モーションの再生時間を設定 */
		this->PlayerStatusList->SetMotionCount_Move(fNowMotionTime_Move);
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
	}
}
