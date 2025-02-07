/* 2025.02.07 駒沢風助 ファイル追加 */

#include "CharacterPlayer.h"

/* 2025.01.30 菊池雅道	モーション処理追加 開始 */
// プレイヤーのモーション遷移管理
void CharacterPlayer::Player_Motion_Transition()
{
	/* アニメーション番号取得 */
	int iMotionNo_Move		= MV1GetAnimIndex(this->iModelHandle, MOTION_MOVE_RUN.c_str());
	int iMotionNo_Attack	= MV1GetAnimIndex(this->iModelHandle, MOTION_CHARGE_LOOP.c_str());

	/* モーションのアタッチ */
	int iAttachHandle_Move		= MV1AttachAnim(this->iModelHandle, iMotionNo_Move, -1);
	int iAttachHandle_Attack	= MV1AttachAnim(this->iModelHandle, iMotionNo_Attack, -1);

	/* 現在のモーションの総再生時間を取得 */
	int iAnimTime_Move		= MV1GetAttachAnimTime(this->iModelHandle, iMotionNo_Move);
	int iAnimTime_Attack	= MV1GetAttachAnimTime(this->iModelHandle, iMotionNo_Attack);

	/* アニメーションブレンド率をセット */
	float blend = 0.5f;
	//MV1SetAttachAnimBlendRate(this->iModelHandle, iAttachHandle_Move,	1.f - blend);
	//MV1SetAttachAnimBlendRate(this->iModelHandle, iAttachHandle_Attack, blend);

	/* 現在のモーション再生時間を取得 */
	float fNowMotionTime_Move = this->PlayerStatusList->fGetMotionCount_Attack();
	
	/* モーションの再生時間を設定 */
	MV1SetAttachAnimTime(this->iModelHandle, iAttachHandle_Move, fNowMotionTime_Move);

	/* モーション時間を進める */
	fNowMotionTime_Move += 1.f;

	/* モーションの最大時間を取得 */
	float fMaxTime_Move = MV1GetAttachAnimTotalTime(this->iModelHandle, iAttachHandle_Move);

	/* 最大時間を超えているか */
	if (fMaxTime_Move < fNowMotionTime_Move)	{ fNowMotionTime_Move = 0; }	// 再生時間を初期化

	/* モーションの再生時間を設定 */
	this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Move);

	///* アタッチしたアニメーションの総再生時間を取得する*/
	//this->fMotionTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMotionAttachIndex);

	//// 居合(強)(終了)モーションは１ループ再生する
	//if (iOldMotion == PLAYER_MOTION_DRAW_SWORD_END)
	//{
	//	// モーションの再生時間が総再生時間を超えていなければ ※総再生時間そのままだとスルーされるので-2しています
	//	if (fMoionPlayTime <= this->fMotionTotalTime - 2)
	//	{
	//		/* モーションの再生時間を進める */
	//		this->fMoionPlayTime += 1.0f;
	//	}
	//	else
	//	{
	//		/* 居合(強)(終了)モーションをデタッチ */
	//		MV1DetachAnim(this->iModelHandle, this->iMotionAttachIndex);

	//		/* 居合(強)(終了)モーションが終わったら、待機モーションをアタッチ */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
	//	}
	//}
	//// それ以外は、モーションが変わっていなければ再生時間を進める
	//else  if (iOldMotion == this->PlayerStatusList->iGetPlayerMotion())
	//{
	//	/* モーションの再生時間を進める */
	//	this->fMoionPlayTime += 1.0f;
	//}
	//// モーションが変わった場合の処理
	//else
	//{
	//	// モーションがアタッチされていたら 
	//	if (this->iMotionAttachIndex != -1)
	//	{
	//		/* モーションをデタッチ */
	//		MV1DetachAnim(this->iModelHandle, this->iMotionAttachIndex);
	//	}

	//	/* プレイヤーのモーション状態を取得 */
	//	int iPlayerMotion = this->PlayerStatusList->iGetPlayerMotion();

	//	// プレイヤーのモーション状態に応じて、モーションをアタッチする
	//	switch (iPlayerMotion)
	//	{
	//		/* 待機 */
	//	case PLAYER_MOTION_IDLE:
	//		/* 待機モーションをアタッチ */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
	//		break;

	//		/* 歩行 */
	//	case PLAYER_MOTION_WALK:
	//		/* 走行(低速) */
	//	case PLAYER_MOTION_RUN_LOW:
	//		/* 走行(高速) */
	//	case PLAYER_MOTION_RUN_HIGH:
	//		/* 走りモーションをアタッチ */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_move_run"), -1, FALSE);
	//		break;

	//		/* 居合(溜め) */
	//	case PLAYER_MOTION_DRAW_SWORD_CHARGE:
	//		/* 居合（溜め）モーションをアタッチ */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
	//		break;

	//		/* 居合(弱) */
	//	case PLAYER_MOTION_DRAW_SWORD_WEAK:
	//		break;
	//		/* 居合(強) */
	//	case PLAYER_MOTION_DRAW_SWORD_STRONG:
	//		/* 居合（溜め）モーションをアタッチ */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_step"), -1, FALSE);
	//		break;

	//		/* 居合(強)(終了) */
	//	case PLAYER_MOTION_DRAW_SWORD_END:
	//		/* 居合(強)(終了)モーションをアタッチ */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_finish"), -1, FALSE);
	//		break;

	//		/* クナイ(構え) */
	//	case PLAYER_MOTION_THROW_KUNAI_AIM:
	//		break;

	//		/* クナイ(投げ) */
	//	case PLAYER_MOTION_THROW_KUNAI_THROW:
	//		break;

	//		/* 回避 */
	//	case PLAYER_MOTION_DODGE:
	//		break;

	//		/* ジャンプ(上昇) */
	//	case PLAYER_MOTION_JUMP_UP:
	//		break;

	//		/* ジャンプ(下降) */
	//	case PLAYER_MOTION_JUMP_DOWN:
	//		break;

	//		return;
	//	}

	//	/* モーションの再生時間をリセットする */
	//	this->fMoionPlayTime = 0.0f;
	//}

	//// モーションの再生時間が総再生時間を超えた場合
	//if (this->fMoionPlayTime > this->fMotionTotalTime)
	//{
	//	/* モーションの再生時間をリセットする */
	//	this->fMoionPlayTime = 0.0f;
	//}
}