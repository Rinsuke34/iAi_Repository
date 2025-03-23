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

				/* "�|���"��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_DOWN);

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

		/* ���݂̃��[�V������"���s"�ł��邩�m�F */
		if (this->PlayerStatusList->iGetPlayerMotion_Move() == MOTION_ID_MOVE_WALK)
		{
			// "���s"�ł���ꍇ
			/* �T�E���h"����"���Đ����łȂ����m�F */
			if (this->bPlayRunSound == false)
			{
				// �Đ����ł���ꍇ
				/* �T�E���h"����"���Đ� */
				gpDataList_Sound->SE_PlaySound_Loop(SE_PLAYER_RUN);

				/* �T�E���h���Đ����ɐݒ� */
				this->bPlayRunSound = true;
			}
		}
		else
		{
			// "���s"�łȂ��ꍇ
			/* �T�E���h"����"���Đ����ł��邩�m�F */
			if (this->bPlayRunSound == true)
			{
				// �Đ����ł���ꍇ
				/* �T�E���h"����"���~ */
				gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_RUN);

				/* �T�E���h�|�C���^���Đ����ɐݒ� */
				this->bPlayRunSound = false;
			}
		}
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

		/* ���݂̃��[�V������"����"�ł��邩�m�F */
		if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_CHARGE)
		{
			// "����"�ł���ꍇ
			/* �T�E���h"���ߋ����`���[�W"���Đ����łȂ����m�F */
			if (this->bPlayChargeSound == false)
			{
				// �Đ����ł���ꍇ
				/* �T�E���h"���ߋ����`���[�W"���Đ� */
				gpDataList_Sound->SE_PlaySound_Loop(SE_PLAYER_CHARGE);
				gpDataList_Sound->SE_PlaySound_Loop(SE_PLAYER_CHARGE_HOLD);

				/* �T�E���h���Đ����ɐݒ� */
				this->bPlayChargeSound = true;
			}
		}
		else
		{
			// "����"�łȂ��ꍇ
			/* �T�E���h"���ߋ����`���[�W"���Đ����ł��邩�m�F */
			if (this->bPlayChargeSound == true)
			{
				// �Đ����ł���ꍇ
				/* �T�E���h"���ߋ����`���[�W"���~ */
				gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE);
				gpDataList_Sound->SE_PlaySound_Stop(SE_PLAYER_CHARGE_HOLD);

				/* �T�E���h���Đ����ɐݒ� */
				this->bPlayChargeSound = false;
			}
		}
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
}

// �V�F�C�v����
void CharacterPlayer::Player_Shape()
{
	/* �V�F�C�v�̓K�p���y������ */
	{
		/* �V�F�C�v���K�p����Ă��邩�m�F */
		if (this->fShapeRate > 0.f)
		{
			// �K�p����Ă���ꍇ
			/* �V�F�C�v�K�p�������炷 */
			this->fShapeRate -= 0.05f;
		}
		else
		{
			// �K�p����Ă��Ȃ��ꍇ
			/* �V�F�C�v�K�p���������� */
			this->fShapeRate = 0.f;
		}
	}

	/* �v���C���[���S���� */
	{
		/* �v���C���[�̌���HP��0�ȉ�(���S���)�ł��邩�m�F */
		if (this->PlayerStatusList->iGetPlayerNowHp() <= 0)
		{
			// HP��0�ȉ�(���S���)�ł���ꍇ
			/* �V�F�C�v�̓K�p�����ő�l(100%)�����ł��邩�m�F */
			if (this->fShapeRate < 1.f)
			{
				// �����Ă��Ȃ��ꍇ
				/* �V�F�C�v�̓K�p�����㏸ */
				this->fShapeRate += 0.05f;
			}
			else
			{
				// �����Ă���ꍇ
				/* �V�F�C�v�̓K�p�����ő�l(100%)�ɐݒ� */
				this->fShapeRate = 1.f;
			}
		}
	}
}

// �Q�[���J�n���̃��[�V����
void CharacterPlayer::FastMotion()
{
	/* �J�n�����[�V�����J�n�t���O���L���ł��邩�m�F */
	if (this->PlayerStatusList->bGetStartFastMotion() == true)
	{
		// �L���ł���ꍇ
		/* �J�n�����[�V�����J�E���g���擾 */
		int iFastMotionCount = this->PlayerStatusList->iGetFastMotionCount();

		/* �J�n�����[�V�����J�E���g������ */
		iFastMotionCount--;

		/* ���[�V�����J�E���g��ݒ� */
		this->PlayerStatusList->SetFastMotionCount(iFastMotionCount);

		/* �A�j���[�V�����^�C�}�[���擾���� */
		float fMotionCount = this->PlayerStatusList->fGetMotionTimer_Move();

		/* �A�j���[�V�����^�C�}�[��i�߂� */
		fMotionCount += 9.f / static_cast<float>(CAMERA_CLOSEUP_COUNT_MAX);

		/* �A�j���[�V�����^�C�}�[��ݒ� */
		this->PlayerStatusList->SetMotionCount_Move(fMotionCount);

		/* �V�F�C�v�K�p����ύX */
		this->fShapeRate = 1.f - (static_cast<float>(CAMERA_CLOSEUP_COUNT_MAX - iFastMotionCount) / static_cast<float>(CAMERA_CLOSEUP_COUNT_MAX));

		/* �J�n�����[�V�����J�E���g������(0�ȉ�)�ł��邩�m�F */
		if (iFastMotionCount <= 0)
		{
			// �����ł���ꍇ
			/* ���݂̃��[�V�������f�^�b�`���� */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

			/* ���[�V���������� */
			MotionReset();

			/* �V�F�C�v�K�p���������� */
			this->fShapeRate = 0.f;

			/* ������~�t���O�𖳌��� */
			this->bBloomStopFlg = false;
		}
	}
}

// ���[�V����������
void CharacterPlayer::MotionReset()
{
	/* ���[�V�����̏��������� */
	{
		/* �������[�V�����ԍ���ݒ� */
		int iInitialMotionNo_Move = this->PlayerStatusList->iGetPlayerMotion_Move();
		int iInitialMotionNo_Attack = this->PlayerStatusList->iGetPlayerMotion_Attack();

		// ���[�V�����̃A�^�b�`
		int iMotionIndex_Move = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iInitialMotionNo_Move].strMotionName.c_str());
		this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(MV1AttachAnim(this->iModelHandle, iMotionIndex_Move, -1));

		int iMotionIndex_Attack = MV1GetAnimIndex(this->iModelHandle, MOTION_LIST[iInitialMotionNo_Attack].strMotionName.c_str());
		this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(MV1AttachAnim(this->iModelHandle, iMotionIndex_Attack, -1));

		// ���[�V�����^�C�}�[�̏�����
		this->PlayerStatusList->SetMotionCount_Move(0.f);
		this->PlayerStatusList->SetMotionCount_Attack(0.f);

		// ���[�V�����I�����Ԃ̐ݒ�
		float fEndTime_Move = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());
		this->PlayerStatusList->SetMotionCount_Move_End(fEndTime_Move);

		float fEndTime_Attack = MV1GetAttachAnimTotalTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack());
		this->PlayerStatusList->SetMotionCount_Attack_End(fEndTime_Attack);

		// �������[�V�����ԍ���ۑ�
		this->PlayerStatusList->SetPlayerMotion_Move(iInitialMotionNo_Move);
		this->PlayerStatusList->SetPlayerMotion_Move_Old(MOTION_ID_MOVE_LAND);
		this->PlayerStatusList->SetPlayerMotion_Attack(iInitialMotionNo_Attack);
	}
}