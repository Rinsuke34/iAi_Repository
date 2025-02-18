/* 2025.02.07 ��򕗏� �t�@�C���ǉ� */

#include "CharacterPlayer.h"

/* 2025.01.30 �e�r�듹	���[�V���������ǉ� �J�n */
// �v���C���[�̃��[�V�����J�ڊǗ�
void CharacterPlayer::Player_Motion_Transition()
{
	/* ���݂̃��[�V�����ԍ����擾 */
	int iMotionNo_Move = this->PlayerStatusList->iGetPlayerMotion_Move();
	int iMotionNo_Attack = this->PlayerStatusList->iGetPlayerMotion_Attack();

	/* �ړ��n���[�V���� */
	{
		/* ���[�V�������ύX����Ă��邩�m�F */
		if (iMotionNo_Move != this->PlayerStatusList->iGetPlayerMotion_Move_Old())
		{
			// �ύX����Ă���ꍇ
			/* ���݂̃��[�V�������f�^�b�`���� */
			MV1DetachAnim(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move());

			/* �ύX���������[�V�����̃��[�V�����ԍ����擾 */
			int iMotionIndex = MV1GetAnimIndex(this->iModelHandle, PlayerMotionList[iMotionNo_Move].strMotionName.c_str());

			/* ���[�V�������A�^�b�`���� */
			int iReturn = MV1AttachAnim(this->iModelHandle, iMotionIndex, -1);
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Move(iReturn);

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
			int iReturn = MV1AttachAnim(this->iModelHandle, iMotionIndex, -1);
			this->PlayerStatusList->SetPlayerMotionAttachIndex_Attack(iReturn);

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
			// �����Ă���ꍇ
			/* �Đ����Ԃ������� */
			fNowMotionTime_Move = 0.f;

			/* ���[�V�����ԍ���ύX��̒l�ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Attack(this->PlayerMotionList[iMotionNo_Attack].iNextMotionID);
		}

		/* ���[�V�����̍Đ����Ԃ�ݒ� */
		this->PlayerStatusList->SetMotionCount_Attack(fNowMotionTime_Move);
	}
}
