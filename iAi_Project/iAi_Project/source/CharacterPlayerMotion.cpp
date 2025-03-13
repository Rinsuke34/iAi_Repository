/* 2025.02.07 ��򕗏� �t�@�C���ǉ� */

#include "CharacterPlayer.h"

// �v���C���[�̃��[�V�����J�ڊǗ�
void CharacterPlayer::Player_Motion_Transition()
{
	/* ���݂̃��[�V�����ԍ����擾 */
	int iMotionNo_Move			= this->PlayerStatusList->iGetPlayerMotion_Move();
	int iMotionNo_Attack		= this->PlayerStatusList->iGetPlayerMotion_Attack();

	/* ���݂̕ύX�O���[�V�����ԍ����擾 */
	int iMotionNo_Move_Old		= this->PlayerStatusList->iGetPlayerMotion_Move_Old();
	int iMotionNo_Attack_Old	= this->PlayerStatusList->iGetPlayerMotion_Attack_Old();

	/* �ړ��n���[�V���� */
	{
		/* ���[�V�������ύX����Ă��邩�m�F */
		if (iMotionNo_Move != this->PlayerStatusList->iGetPlayerMotion_Move_Old())
		{
			// �ύX����Ă���ꍇ
			/* �ύX�O�̃��[�V�������f�^�b�`���� */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move_Old());

			/* ���݂̃��[�V��������ύX�O���[�V�����Ƃ��ĕۑ� */
			this->PlayerStatusList->SetMotionCount_Move_Old(this->PlayerStatusList->fGetMotionTimer_Move());
			this->PlayerStatusList->SetMotionCount_Move_Old_End(this->PlayerStatusList->fGetMotionTimer_Move_End());
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Move_Old(this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

			/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
			int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Move].strMotionName.c_str());

			/* ���[�V�������A�^�b�`���� */
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

			/* ���݂̃��[�V�������X�V���� */
			this->PlayerStatusList->SetPlayerMotion_Move_Old(iMotionNo_Move);

			/* �A�j���[�V�����^�C�}�[������������ */
			this->PlayerStatusList->SetMotionCount_Move(0.f);

			/* �A�j���[�V�����̏I�����Ԃ��Đݒ肷�� */
			float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());
			this->PlayerStatusList->SetMotionCount_Move_End(fEndTime);

			/* ���[�V�����u�����h��������������*/
			this->PlayerStatusList->SetNowMoveMotionBlendRate(0.f);
		}

		/* ���݂̃��[�V�����Đ����Ԃ��擾 */
		float fNowMotionTime_Move		= this->PlayerStatusList->fGetMotionTimer_Move();
		float fNowMotionTime_Move_Old	= this->PlayerStatusList->fGetMotionTimer_Move_Old();

		/* ���[�V�������Ԃ�i�߂� */
		fNowMotionTime_Move		+= 1.f;
		fNowMotionTime_Move_Old	+= 1.f;

		/* ���݂̃��[�V�����̍Đ����Ԃ����[�V�����̏I�����Ԃ𒴂��Ă��邩�m�F */
		if (fNowMotionTime_Move > this->PlayerStatusList->fGetMotionTimer_Move_End())
		{
			// �ő厞�Ԃ𒴂��Ă���ꍇ
			/* �v���C���[���[�V������"���S"�ȊO�ł��邩�m�F */
			if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_DIE)
			{
				// "���S"�ȊO�ł���ꍇ
				/* �Đ����Ԃ������� */
				fNowMotionTime_Move = 0.f;
			}
			else
			{
				// "���S"�ł���ꍇ
				/* �Đ����Ԃ��Ō�̎��ԂŒ�~ */
				fNowMotionTime_Move -= 1.f;

				/* ���S�t���O��L���ɂ��� */
				this->PlayerStatusList->SetPlayerDeadFlg(true);
			}

			/* ���[�V�����ԍ���ύX��̒l�ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Move(MOTION_LIST[iMotionNo_Move].iNextMotionID);
		}

		/* �ύX�O�̃��[�V�����̍Đ����Ԃ����[�V�����̏I�����Ԃ𒴂��Ă��邩�m�F */
		if (fNowMotionTime_Move_Old > this->PlayerStatusList->fGetMotionTimer_Move_Old_End())
		{
			// �ő厞�Ԃ𒴂��Ă���ꍇ
			/* �Đ����Ԃ������� */
			fNowMotionTime_Move_Old = 0.f;
		}

		/* �u�����h�����X�V */
		float fBlendRate = this->PlayerStatusList->fGetNowMoveMotionBlendRate();

		/* �u�����h����i�߂� */
		fBlendRate += 0.1f;

		/* �u�����h����1.0f�𒴂��Ă��邩�m�F */
		if (fBlendRate > 1.0f)
		{
			// 1.0f�𒴂��Ă���ꍇ
			/* �u�����h����1.0f�ɐݒ� */
			fBlendRate = 1.0f;
		}

		/* �u�����h����ۑ� */
		this->PlayerStatusList->SetNowMoveMotionBlendRate(fBlendRate);

		/* ���[�V�����̍Đ����Ԃ�ݒ� */
		this->PlayerStatusList->SetMotionCount_Move(fNowMotionTime_Move);
		this->PlayerStatusList->SetMotionCount_Move_Old(fNowMotionTime_Move_Old);
	}

	/* �U���n���[�V���� */
	{
		///* ���[�V�������ύX����Ă��邩�m�F */
		//if (iMotionNo_Attack != this->PlayerStatusList->iGetPlayerMotion_Attack_Old())
		//{
		//	// �ύX����Ă���ꍇ
		//	/* �ύX�O�̃��[�V�������f�^�b�`���� */
		//	MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack_Old());

		//	/* ���݂̃��[�V��������ύX�O���[�V�����Ƃ��ĕۑ� */
		//	this->PlayerStatusList->SetMotionCount_Attack_Old(this->PlayerStatusList->fGetMotionTimer_Attack());
		//	this->PlayerStatusList->SetMotionCount_Attack_Old_End(this->PlayerStatusList->fGetMotionTimer_Attack_End());
		//	this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack_Old(this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());

		//	/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
		//	int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Attack].strMotionName.c_str());

		//	/* ���[�V�������A�^�b�`���� */
		//	this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

		//	/* ���݂̃��[�V�������X�V���� */
		//	this->PlayerStatusList->SetPlayerMotion_Attack_Old(iMotionNo_Attack);

		//	/* �A�j���[�V�����^�C�}�[������������ */
		//	this->PlayerStatusList->SetMotionCount_Attack(0.f);

		//	/* �A�j���[�V�����̏I�����Ԃ��Đݒ肷�� */
		//	float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
		//	this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime);

		//	/* ���[�V�����u�����h��������������*/
		//	this->PlayerStatusList->SetNowAttackMotionBlendRate(0.f);
		//}

		///* ���݂̃��[�V�����Đ����Ԃ��擾 */
		//float fNowMotionTime_Attack = this->PlayerStatusList->fGetMotionTimer_Attack();
		//float fNowMotionTime_Attack_Old = this->PlayerStatusList->fGetMotionTimer_Attack_Old();

		///* ���[�V�������Ԃ�i�߂� */
		//fNowMotionTime_Attack += 1.f;
		//fNowMotionTime_Attack_Old += 1.f;

		///* ���݂̃��[�V�����̍Đ����Ԃ����[�V�����̏I�����Ԃ𒴂��Ă��邩�m�F */
		//if (fNowMotionTime_Attack > this->PlayerStatusList->fGetMotionTimer_Attack_End())
		//{
		//	// �ő厞�Ԃ𒴂��Ă���ꍇ
		//	/* �Đ����Ԃ������� */
		//	fNowMotionTime_Attack = 0.f;

		//	/* ���[�V�����ԍ���ύX��̒l�ɐݒ� */
		//	this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_LIST[iMotionNo_Attack].iNextMotionID);
		//}

		///* �ύX�O�̃��[�V�����̍Đ����Ԃ����[�V�����̏I�����Ԃ𒴂��Ă��邩�m�F */
		//if (fNowMotionTime_Attack_Old > this->PlayerStatusList->fGetMotionTimer_Attack_Old_End())
		//{
		//	// �ő厞�Ԃ𒴂��Ă���ꍇ
		//	/* �Đ����Ԃ������� */
		//	fNowMotionTime_Attack_Old = 0.f;
		//}

		///* �u�����h�����X�V */
		//float fBlendRate = this->PlayerStatusList->fGetNowAttackMotionBlendRate();

		///* �u�����h����i�߂� */
		//fBlendRate += 0.1f;

		///* �u�����h����1.0f�𒴂��Ă��邩�m�F */
		//if (fBlendRate > 1.0f)
		//{
		//	// 1.0f�𒴂��Ă���ꍇ
		//	/* �u�����h����1.0f�ɐݒ� */
		//	fBlendRate = 1.0f;
		//}

		///* �u�����h����ۑ� */
		//this->PlayerStatusList->SetNowAttackMotionBlendRate(fBlendRate);

		///* ���[�V�����̍Đ����Ԃ�ݒ� */
		//this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Attack);
		//this->PlayerStatusList->SetMotionCount_Attack_Old(fNowMotionTime_Attack_Old);

		/* ���[�V�������ύX����Ă��邩�m�F */
		if (iMotionNo_Attack != this->PlayerStatusList->iGetPlayerMotion_Attack_Old())
		{
			// �ύX����Ă���ꍇ
			/* ���݂̃��[�V�������f�^�b�`���� */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());

			/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
			int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Attack].strMotionName.c_str());

			/* ���[�V�������A�^�b�`���� */
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

			/* ���݂̃��[�V�������X�V���� */
			this->PlayerStatusList->SetPlayerMotion_Attack_Old(iMotionNo_Attack);

			/* �A�j���[�V�����^�C�}�[������������ */
			this->PlayerStatusList->SetMotionCount_Attack(0.f);

			/* �A�j���[�V�����̏I�����Ԃ��Đݒ肷�� */
			float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
			this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime);
		}

		/* ���݂̃��[�V�����Đ����Ԃ��擾 */
		float fNowMotionTime_Attack = this->PlayerStatusList->fGetMotionTimer_Attack();

		/* ���[�V�������Ԃ�i�߂� */
		fNowMotionTime_Attack += 1.f;

		/* ���[�V�����̍Đ����Ԃ����[�V�����̏I�����Ԃ𒴂��Ă��邩�m�F */
		if (fNowMotionTime_Attack > this->PlayerStatusList->fGetMotionTimer_Attack_End())
		{
			// �ő厞�Ԃ𒴂��Ă���ꍇ
			/* �Đ����Ԃ������� */
			fNowMotionTime_Attack = 0.f;

			/* ���[�V�����ԍ���ύX��̒l�ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_LIST[iMotionNo_Attack].iNextMotionID);
		}

		/* ���[�V�����̍Đ����Ԃ�ݒ� */
		this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Attack);
	}

	/* ���݂̃��[�V�����̕������Ɏ����Ă��邩�̃t���O���m�F */
	if (MOTION_LIST[iMotionNo_Attack].bWeponHandFlg == true)
	{
		// �\���t���O���L���ł���ꍇ
		/* �E��̓���\������ */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, TRUE);

		/* �w�ʂ̓����\���ɂ��� */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, FALSE);
	}
	else
	{
		// �\���t���O�������ł���ꍇ
		/* �E��̓����\���ɂ��� */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, FALSE);

		/* �w�ʂ̓���\������ */
		MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, TRUE);
	}

	/* ���݃N�i�C���������Ă����Ԃł��邩�m�F */
	if (this->PlayerStatusList->iGetNowHaveKunai() > 0)
	{
		// �������Ă���ꍇ
		/* ��̃N�i�C��\������ */
		MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, TRUE);
	}
	else
	{
		// �������Ă��Ȃ��ꍇ
		/* ��̃N�i�C���\���ɂ��� */
		MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, FALSE);
	}




	///* ���݂̃��[�V�����ԍ����擾 */
	//int iMotionNo_Move = this->PlayerStatusList->iGetPlayerMotion_Move();
	//int iMotionNo_Attack = this->PlayerStatusList->iGetPlayerMotion_Attack();

	///* �ړ��n���[�V���� */
	//{
	//	/* ���[�V�������ύX����Ă��邩�m�F */
	//	if (iMotionNo_Move != this->PlayerStatusList->iGetPlayerMotion_Move_Old())
	//	{
	//		// �ύX����Ă���ꍇ
	//		/* ���݂̃��[�V�������f�^�b�`���� */
	//		MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

	//		/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
	//		int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Move].strMotionName.c_str());

	//		/* ���[�V�������A�^�b�`���� */
	//		this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

	//		/* ���݂̃��[�V�������X�V���� */
	//		this->PlayerStatusList->SetPlayerMotion_Move_Old(iMotionNo_Move);

	//		/* �A�j���[�V�����^�C�}�[������������ */
	//		this->PlayerStatusList->SetMotionCount_Move(0.f);

	//		/* �A�j���[�V�����̏I�����Ԃ��Đݒ肷�� */
	//		float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());
	//		this->PlayerStatusList->SetMotionCount_Move_End(fEndTime);
	//	}

	//	/* ���݂̃��[�V�����Đ����Ԃ��擾 */
	//	float fNowMotionTime_Move = this->PlayerStatusList->fGetMotionTimer_Move();

	//	/* ���[�V�������Ԃ�i�߂� */
	//	fNowMotionTime_Move += 1.f;

	//	/* ���[�V�����̍Đ����Ԃ����[�V�����̏I�����Ԃ𒴂��Ă��邩�m�F */
	//	if (fNowMotionTime_Move > this->PlayerStatusList->fGetMotionTimer_Move_End())
	//	{
	//		// �ő厞�Ԃ𒴂��Ă���ꍇ
	//		/* �v���C���[���[�V������"���S"�ȊO�ł��邩�m�F */
	//		if (this->PlayerStatusList->iGetPlayerMotion_Move() != MOTION_ID_MOVE_DIE)
	//		{
	//			// "���S"�ȊO�ł���ꍇ
	//			/* �Đ����Ԃ������� */
	//			fNowMotionTime_Move = 0.f;
	//		}
	//		else
	//		{
	//			// "���S"�ł���ꍇ
	//			/* �Đ����Ԃ��Ō�̎��ԂŒ�~ */
	//			fNowMotionTime_Move -= 1.f;

	//			/* ���S�t���O��L���ɂ��� */
	//			this->PlayerStatusList->SetPlayerDeadFlg(true);
	//		}

	//		/* ���[�V�����ԍ���ύX��̒l�ɐݒ� */
	//		this->PlayerStatusList->SetPlayerMotion_Move(MOTION_LIST[iMotionNo_Move].iNextMotionID);
	//	}

	//	/* ���[�V�����̍Đ����Ԃ�ݒ� */
	//	this->PlayerStatusList->SetMotionCount_Move(fNowMotionTime_Move);
	//}

	///* �U���n���[�V���� */
	//{
	//	/* ���[�V�������ύX����Ă��邩�m�F */
	//	if (iMotionNo_Attack != this->PlayerStatusList->iGetPlayerMotion_Attack_Old())
	//	{
	//		// �ύX����Ă���ꍇ
	//		/* ���݂̃��[�V�������f�^�b�`���� */
	//		MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());

	//		/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
	//		int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iMotionNo_Attack].strMotionName.c_str());

	//		/* ���[�V�������A�^�b�`���� */
	//		this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex, -1));

	//		/* ���݂̃��[�V�������X�V���� */
	//		this->PlayerStatusList->SetPlayerMotion_Attack_Old(iMotionNo_Attack);

	//		/* �A�j���[�V�����^�C�}�[������������ */
	//		this->PlayerStatusList->SetMotionCount_Attack(0.f);

	//		/* �A�j���[�V�����̏I�����Ԃ��Đݒ肷�� */
	//		float fEndTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
	//		this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime);
	//	}

	//	/* ���݂̃��[�V�����Đ����Ԃ��擾 */
	//	float fNowMotionTime_Attack = this->PlayerStatusList->fGetMotionTimer_Attack();

	//	/* ���[�V�������Ԃ�i�߂� */
	//	fNowMotionTime_Attack += 1.f;

	//	/* ���[�V�����̍Đ����Ԃ����[�V�����̏I�����Ԃ𒴂��Ă��邩�m�F */
	//	if (fNowMotionTime_Attack > this->PlayerStatusList->fGetMotionTimer_Attack_End())
	//	{
	//		// �ő厞�Ԃ𒴂��Ă���ꍇ
	//		/* �Đ����Ԃ������� */
	//		fNowMotionTime_Attack = 0.f;

	//		/* ���[�V�����ԍ���ύX��̒l�ɐݒ� */
	//		this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_LIST[iMotionNo_Attack].iNextMotionID);
	//	}

	//	/* ���[�V�����̍Đ����Ԃ�ݒ� */
	//	this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Attack);
	//}

	///* ���݂̃��[�V�����̕������Ɏ����Ă��邩�̃t���O���m�F */
	//if (MOTION_LIST[iMotionNo_Attack].bWeponHandFlg == true)
	//{
	//	// �\���t���O���L���ł���ꍇ
	//	/* �E��̓���\������ */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, TRUE);

	//	/* �w�ʂ̓����\���ɂ��� */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, FALSE);
	//}
	//else
	//{
	//	// �\���t���O�������ł���ꍇ
	//	/* �E��̓����\���ɂ��� */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_RightHand, FALSE);

	//	/* �w�ʂ̓���\������ */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKatanaFrameNo_Waist, TRUE);
	//}

	///* ���݃N�i�C���������Ă����Ԃł��邩�m�F */
	//if (this->PlayerStatusList->iGetNowHaveKunai() > 0)
	//{
	//	// �������Ă���ꍇ
	//	/* ��̃N�i�C��\������ */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, TRUE);
	//}
	//else
	//{
	//	// �������Ă��Ȃ��ꍇ
	//	/* ��̃N�i�C���\���ɂ��� */
	//	MV1SetFrameVisible(this->iModelHandle, this->iKunaiHandFrameNo, FALSE);
	//}
}
