/* 2025.02.07 ��򕗏� �t�@�C���ǉ� */

#include "CharacterPlayer.h"

/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �J�n */
// �v���C���[�̃��[�V�����J�ڊǗ�
void CharacterPlayer::Player_Motion_Transition()
{
	/* ���݂̃��[�V�����ԍ����擾 */
	int iMotionNo_Move		= this->PlayerStatusList->iGetPlayerMotion_Move();
	int iMotionNo_Attack	= this->PlayerStatusList->iGetPlayerMotion_Attack();

	/* �ړ��n���[�V���� */
	{
		/* ���[�V�������ύX����Ă��邩�m�F */
		if (iMotionNo_Move != this->PlayerStatusList->iGetPlayerMotion_Move_Old())
		{
			// �ύX����Ă���ꍇ
			/* ���݂̃��[�V�������f�^�b�`���� */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

			/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
			int iMotionIndex	= MV1GetAnimIndex(this->iModelHandle, PlayerMotionList[iMotionNo_Move].strMotionName.c_str());

			/* ���[�V�������A�^�b�`���� */
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

			/* ���݂̃��[�V�������X�V���� */
			this->PlayerStatusList->SetPlayerMotion_Move_Old(iMotionNo_Move);

			/* �A�j���[�V�����^�C�}�[������������ */
			this->PlayerStatusList->SetMotionCount_Move(0.f);

			/* �A�j���[�V�����̏I�����Ԃ��Đݒ肷�� */
			this->PlayerStatusList->SetMotionCount_Move_End(this->PlayerMotionList[iMotionNo_Move].fMotion_MaxTime);
		}

		/* ���݂̃��[�V�����Đ����Ԃ��擾 */
		float fNowMotionTime_Move = this->PlayerStatusList->fGetMotionTimer_Move();

		/* ���[�V�������Ԃ�i�߂� */
		fNowMotionTime_Move += 1.f;

		/* �ő厞�Ԃ𒴂��Ă��邩 */
		if (fNowMotionTime_Move > this->PlayerStatusList->fGetMotionTimer_Move_End())
		{
			// �����Ă���ꍇ
			/* �Đ����Ԃ������� */
			fNowMotionTime_Move = 0.f;

			/* ���[�V�����ԍ���ύX��̒l�ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Move(this->PlayerMotionList[iMotionNo_Move].iNextMotionID);
		}

		/* ���[�V�����̍Đ����Ԃ�ݒ� */
		this->PlayerStatusList->SetMotionCount_Move(fNowMotionTime_Move);
	}

	/* �U���n���[�V���� */
	{
		/* ���[�V�������ύX����Ă��邩�m�F */
		if (iMotionNo_Attack != this->PlayerStatusList->iGetPlayerMotion_Attack_Old())
		{
			// �ύX����Ă���ꍇ
			/* ���݂̃��[�V�������f�^�b�`���� */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());

			/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
			int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, PlayerMotionList[iMotionNo_Attack].strMotionName.c_str());

			/* ���[�V�������A�^�b�`���� */
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

			/* ���݂̃��[�V�������X�V���� */
			this->PlayerStatusList->SetPlayerMotion_Attack_Old(iMotionNo_Attack);

			/* �A�j���[�V�����^�C�}�[������������ */
			this->PlayerStatusList->SetMotionCount_Attack(0.f);

			/* �A�j���[�V�����̏I�����Ԃ��Đݒ肷�� */
			this->PlayerStatusList->SetMotionCount_Attack_End(this->PlayerMotionList[iMotionNo_Attack].fMotion_MaxTime);
		}

		/* ���݂̃��[�V�����Đ����Ԃ��擾 */
		float fNowMotionTime_Move = this->PlayerStatusList->fGetMotionTimer_Attack();

		/* ���[�V�������Ԃ�i�߂� */
		fNowMotionTime_Move += 1.f;

		/* �ő厞�Ԃ𒴂��Ă��邩 */
		if (fNowMotionTime_Move > this->PlayerStatusList->fGetMotionTimer_Attack_End())
		{
			fNowMotionTime_Move = 0.f;
		}

		/* ���[�V�����̍Đ����Ԃ�ݒ� */
		this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Move);
	}

	///* �A�j���[�V�����ԍ��擾 */
	//int iMotionNo_Move		= MV1GetAnimIndex(this->iModelHandle, MOTION_MOVE_RUN.c_str());
	//int iMotionNo_Attack	= MV1GetAnimIndex(this->iModelHandle, MOTION_CHARGE_LOOP.c_str());

	///* ���[�V�����̃A�^�b�` */
	//int iAttachHandle_Move		= MV1AttachAnim(this->iModelHandle, iMotionNo_Move, -1);
	//int iAttachHandle_Attack	= MV1AttachAnim(this->iModelHandle, iMotionNo_Attack, -1);

	///* ���݂̃��[�V�����̑��Đ����Ԃ��擾 */
	//int iAnimTime_Move		= MV1GetAttachAnimTime(this->iModelHandle, iMotionNo_Move);
	//int iAnimTime_Attack	= MV1GetAttachAnimTime(this->iModelHandle, iMotionNo_Attack);

	///* �A�j���[�V�����u�����h�����Z�b�g */
	//float blend = 0.5f;
	////MV1SetAttachAnimBlendRate(this->iModelHandle, iAttachHandle_Move,	1.f - blend);
	////MV1SetAttachAnimBlendRate(this->iModelHandle, iAttachHandle_Attack, blend);

	///* ���݂̃��[�V�����Đ����Ԃ��擾 */
	//float fNowMotionTime_Move = this->PlayerStatusList->fGetMotionTimer_Attack();
	//
	///* ���[�V�����̍Đ����Ԃ�ݒ� */
	//MV1SetAttachAnimTime(this->iModelHandle, iAttachHandle_Move, fNowMotionTime_Move);

	///* ���[�V�������Ԃ�i�߂� */
	//fNowMotionTime_Move += 0.1f;

	///* ���[�V�����̍ő厞�Ԃ��擾 */
	//float fMaxTime_Move = MV1GetAttachAnimTotalTime(this->iModelHandle, iAttachHandle_Move);

	///* �ő厞�Ԃ𒴂��Ă��邩 */
	//if (fMaxTime_Move < fNowMotionTime_Move)	{ fNowMotionTime_Move = 0; }	// �Đ����Ԃ�������

	///* ���[�V�����̍Đ����Ԃ�ݒ� */
	//this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Move);

	///* �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����*/
	//this->fMotionTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iMotionAttachIndex);

	//// ����(��)(�I��)���[�V�����͂P���[�v�Đ�����
	//if (iOldMotion == PLAYER_MOTION_DRAW_SWORD_END)
	//{
	//	// ���[�V�����̍Đ����Ԃ����Đ����Ԃ𒴂��Ă��Ȃ���� �����Đ����Ԃ��̂܂܂��ƃX���[�����̂�-2���Ă��܂�
	//	if (fMoionPlayTime <= this->fMotionTotalTime - 2)
	//	{
	//		/* ���[�V�����̍Đ����Ԃ�i�߂� */
	//		this->fMoionPlayTime += 1.0f;
	//	}
	//	else
	//	{
	//		/* ����(��)(�I��)���[�V�������f�^�b�` */
	//		MV1DetachAnim(this->iModelHandle, this->iMotionAttachIndex);

	//		/* ����(��)(�I��)���[�V�������I�������A�ҋ@���[�V�������A�^�b�` */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
	//	}
	//}
	//// ����ȊO�́A���[�V�������ς���Ă��Ȃ���΍Đ����Ԃ�i�߂�
	//else  if (iOldMotion == this->PlayerStatusList->iGetPlayerMotion())
	//{
	//	/* ���[�V�����̍Đ����Ԃ�i�߂� */
	//	this->fMoionPlayTime += 1.0f;
	//}
	//// ���[�V�������ς�����ꍇ�̏���
	//else
	//{
	//	// ���[�V�������A�^�b�`����Ă����� 
	//	if (this->iMotionAttachIndex != -1)
	//	{
	//		/* ���[�V�������f�^�b�` */
	//		MV1DetachAnim(this->iModelHandle, this->iMotionAttachIndex);
	//	}

	//	/* �v���C���[�̃��[�V������Ԃ��擾 */
	//	int iPlayerMotion = this->PlayerStatusList->iGetPlayerMotion();

	//	// �v���C���[�̃��[�V������Ԃɉ����āA���[�V�������A�^�b�`����
	//	switch (iPlayerMotion)
	//	{
	//		/* �ҋ@ */
	//	case PLAYER_MOTION_IDLE:
	//		/* �ҋ@���[�V�������A�^�b�` */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
	//		break;

	//		/* ���s */
	//	case PLAYER_MOTION_WALK:
	//		/* ���s(�ᑬ) */
	//	case PLAYER_MOTION_RUN_LOW:
	//		/* ���s(����) */
	//	case PLAYER_MOTION_RUN_HIGH:
	//		/* ���胂�[�V�������A�^�b�` */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_move_run"), -1, FALSE);
	//		break;

	//		/* ����(����) */
	//	case PLAYER_MOTION_DRAW_SWORD_CHARGE:
	//		/* �����i���߁j���[�V�������A�^�b�` */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_loop"), -1, FALSE);
	//		break;

	//		/* ����(��) */
	//	case PLAYER_MOTION_DRAW_SWORD_WEAK:
	//		break;
	//		/* ����(��) */
	//	case PLAYER_MOTION_DRAW_SWORD_STRONG:
	//		/* �����i���߁j���[�V�������A�^�b�` */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_step"), -1, FALSE);
	//		break;

	//		/* ����(��)(�I��) */
	//	case PLAYER_MOTION_DRAW_SWORD_END:
	//		/* ����(��)(�I��)���[�V�������A�^�b�` */
	//		this->iMotionAttachIndex = MV1AttachAnim(this->iModelHandle, MV1GetAnimIndex(this->iModelHandle, "mot_attack_charge_finish"), -1, FALSE);
	//		break;

	//		/* �N�i�C(�\��) */
	//	case PLAYER_MOTION_THROW_KUNAI_AIM:
	//		break;

	//		/* �N�i�C(����) */
	//	case PLAYER_MOTION_THROW_KUNAI_THROW:
	//		break;

	//		/* ��� */
	//	case PLAYER_MOTION_DODGE:
	//		break;

	//		/* �W�����v(�㏸) */
	//	case PLAYER_MOTION_JUMP_UP:
	//		break;

	//		/* �W�����v(���~) */
	//	case PLAYER_MOTION_JUMP_DOWN:
	//		break;

	//		return;
	//	}

	//	/* ���[�V�����̍Đ����Ԃ����Z�b�g���� */
	//	this->fMoionPlayTime = 0.0f;
	//}

	//// ���[�V�����̍Đ����Ԃ����Đ����Ԃ𒴂����ꍇ
	//if (this->fMoionPlayTime > this->fMotionTotalTime)
	//{
	//	/* ���[�V�����̍Đ����Ԃ����Z�b�g���� */
	//	this->fMoionPlayTime = 0.0f;
	//}
}