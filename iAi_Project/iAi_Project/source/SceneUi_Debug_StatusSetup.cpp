/* 2025.03.16 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Debug_StatusSetup.h"

/* UI(�f�o�b�O���j���[/�X�e�[�^�X����)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Debug_StatusSetup::SceneUi_Debug_StatusSetup() : SceneBase("UI_Debug_StatusSetup", 201, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* ������ */
	this->iSelectItem	= 0;		// �I�𒆂̍��ڂ̔ԍ�
	this->bSelectFlg	= false;	// �I����Ԃł��邩�̃t���O
}

// �f�X�g���N�^
SceneUi_Debug_StatusSetup::~SceneUi_Debug_StatusSetup()
{
	/* json�t�@�C�����X�V */
	this->PlayerStatusList->SavePlayerStatuxData();

	/* �v���C���[�X�e�[�^�X�̍ēǂݍ��� */
	this->PlayerStatusList->LoadPlayerStatuxData();
}

// �v�Z
void SceneUi_Debug_StatusSetup::Process()
{
	/* �I����Ԃł��邩�m�F */
	if (this->bSelectFlg == false)
	{
		// �I����ԂłȂ��ꍇ
		/* �v���C���[�̓��͎擾 */
		// �����
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
		{
			this->iSelectItem -= 1;
			if (this->iSelectItem < 0)
			{
				this->iSelectItem = 0;
			}
		}

		// ������
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
		{
			this->iSelectItem += 1;
			if (this->iSelectItem >= 10)
			{
				this->iSelectItem = 10;
			}
		}

		// ����
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			/* �I����Ԃɂ��� */
			this->bSelectFlg = true;
		}

		// �L�����Z��
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			/* �V�[�����폜���� */
			this->bDeleteFlg = true;
		}
	}
	else
	{
		// �I����Ԃł���ꍇ
		/* ���݂̐ݒ�l���擾 */
		float fValue = 0.0f;	// �ݒ�l
		bool bIntFlg = false;	// int�^�ł��邩�̃t���O

		/* �ݒ�l���擾 */
		switch (this->iSelectItem)
		{
			case 0:
				// �ړ������x
				fValue = this->PlayerStatusList->fGetPlayerMoveAcceleration();
				break;
			case 1:
				// �W�����v���x
				fValue = this->PlayerStatusList->fGetPlayerJumpSpeed();
				break;
			case 2:
				// ���������x
				fValue = this->PlayerStatusList->fGetPlayerFallAcceleration();
				break;
			case 3:
				// �ő嗎�����x
				fValue = this->PlayerStatusList->fGetPlayerMaxFallSpeed();
				break;
			case 4:
				// �W�����v��
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxJumpCount());
				bIntFlg = true;
				break;
			case 5:
				// ��𑬓x
				fValue = this->PlayerStatusList->fGetPlayerDodgeSpeed();
				break;
			case 6:
				// ����t���[����
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxDodgeFlame());
				bIntFlg = true;
				break;
			case 7:
				// �ǃL�b�N���x(��������
				fValue = this->PlayerStatusList->fGetPlayerKickWallHorizontalSpeed();
			case 8:
				// �ǃL�b�N���x(��������)
				fValue = this->PlayerStatusList->fGetPlayerKickWallVerticalSpeed();
				break;
			case 9:
				// �ǃL�b�N�p���t���[����
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerKickWallFlame());
			case 10:
				// �ǃL�b�N���͗P�\�t���[����
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerKickWallInputMaxFlame());
			case 11:
				// �ߋ����U��(��)�ɐ؂�ւ��`���[�W�t���[����
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMelleStrongChangeChargeFrame());
				bIntFlg = true;
				break;
			case 12:
				// �ߋ����U��(��)�̍ő�`���[�W�t���[����
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMelleStrongMaxChargeFrame());
				bIntFlg = true;
				break;
			case 13:
				// �ߋ����U��(��)�̈ړ��X�P�[��
				fValue = this->PlayerStatusList->fGetPlayerMelleStrongMoveScale();
				break;
			case 14:
				// �ߋ����U��(��)�̈ړ����x
				fValue = this->PlayerStatusList->fGetPlayerMeleeStrongMoveSpeed();
				break;
			case 15:
				// �ߋ����U��(��)�̘A���U���ő�t���[����
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMeleeStrongContinusMaxFrame());
				bIntFlg = true;
				break;
			case 16:
				// �󒆂ł̋ߐڍU��(��)��
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount());
				bIntFlg = true;
				break;
			case 17:
				// ���b�N�I���͈͂̔��a
				fValue = this->PlayerStatusList->fGetPlayerRockOnRadius();
				break;
			case 18:
				// ������ԃN�i�C��������
				fValue = static_cast<float>(this->PlayerStatusList->iGetStartHaveKunai());
				bIntFlg = true;
				break;
			case 19:
				// �ő�N�i�C������
				fValue = static_cast<float>(this->PlayerStatusList->iGetMaxhaveKunai());
				bIntFlg = true;
				break;
			case 20:
				// �ő�HP
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxHp());
				bIntFlg = true;
				break;
			case 21:
				// �ő喳�G����
				fValue = static_cast<float>(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());
				bIntFlg = true;
				break;
		}

		// �����
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

		// ������
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

		/* �ݒ�l��ݒ� */
		switch (this->iSelectItem)
		{
			case 0:
				// �ړ������x
				this->PlayerStatusList->SetPlayerMoveAcceleration(fValue);
				break;
			case 1:
				// �W�����v���x
				this->PlayerStatusList->SetplayerJumpSpeed(fValue);
				break;
			case 2:
				// ���������x
				this->PlayerStatusList->SetPlayerFallAcceleration(fValue);
				break;
			case 3:
				// �ő嗎�����x
				this->PlayerStatusList->SetPlayerMaxFallSpeed(fValue);
				break;
			case 4:
				// �W�����v��
				this->PlayerStatusList->SetPlayerMaxJumpCount(static_cast<int>(fValue));
				break;

			case 5:
				// ��𑬓x
				this->PlayerStatusList->SetPlayerDodgeSpeed(fValue);
				break;
			case 6:
				// ����t���[����
				this->PlayerStatusList->SetPlayerMaxDodgeFlame(static_cast<int>(fValue));
				break;
			case 7:
				// �ǃL�b�N���x(��������)
				this->PlayerStatusList->SetPlayerKickWallHorizontalSpeed(fValue);
				break;
			case 8:
				// �ǃL�b�N���x(��������)
				this->PlayerStatusList->SetPlayerKickWallVerticalSpeed(fValue);
				break;
			case 9:
				// �ǃL�b�N�p���t���[����
				this->PlayerStatusList->SetPlayerKickWallFlame(static_cast<int>(fValue));
				break;
			case 10:
				// �ǃL�b�N���͗P�\�t���[����
				this->PlayerStatusList->SetPlyerKickWallInputMaxFrame(static_cast<int>(fValue));
				break;
			case 11:
				// �ߋ����U��(��)�ɐ؂�ւ��`���[�W�t���[����
				this->PlayerStatusList->SetPlayerMelleStrongChangeChargeFrame(static_cast<int>(fValue));
				break;
			case 12:
				// �ߋ����U��(��)�̍ő�`���[�W�t���[����
				this->PlayerStatusList->SetPlayerMelleStrongMaxChargeFrame(static_cast<int>(fValue));
				break;
			case 13:
				// �ߋ����U��(��)�̈ړ��X�P�[��
				this->PlayerStatusList->SetPlayerMelleStrongMoveScale(fValue);
				break;
			case 14:
				// �ߋ����U��(��)�̈ړ����x
				this->PlayerStatusList->SetPlayerMeleeStrongMoveSpeed(fValue);
				break;
			case 15:
				// �ߋ����U��(��)�̘A���U���ő�t���[����
				this->PlayerStatusList->SetPlayerMeleeStrongContinusMaxFrame(static_cast<int>(fValue));
				break;
			case 16:
				// �󒆂ł̋ߐڍU��(��)��
				this->PlayerStatusList->SetPlayerMeleeStrongAirMaxCount(static_cast<int>(fValue));
				break;
			case 17:
				// ���b�N�I���͈͂̔��a
				this->PlayerStatusList->SetPlayerRockOnRadius(fValue);
				break;
			case 18:
				// ������ԃN�i�C��������
				this->PlayerStatusList->SetStartHaveKunai(static_cast<int>(fValue));
				break;
			case 19:
				// �ő�N�i�C������
				this->PlayerStatusList->SetMaxhaveKunai(static_cast<int>(fValue));
				break;
			case 20:
				// �ő�HP
				this->PlayerStatusList->SetPlayerMaxHp(static_cast<int>(fValue));
				break;
			case 21:
				// �ő喳�G����
				this->PlayerStatusList->SetPlayerMaxInvincibleTime(static_cast<int>(fValue));
				break;
			
			
		}

		// �L�����Z��
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			/* �I����Ԃ����� */
			this->bSelectFlg = false;
		}
	}
	
}

// �`��
void SceneUi_Debug_StatusSetup::Draw()
{
	DrawBox(850, 350, 1400, 350 + 16 * 11, GetColor(0, 0, 0), TRUE);
	DrawFormatString(870, 350 + 16 * 0, GetColor(255, 255, 255), "�ړ������x");
	DrawFormatString(1200, 350 + 16 * 0, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMoveAcceleration());
	DrawFormatString(870, 350 + 16 * 1, GetColor(255, 255, 255), "�W�����v���x");
	DrawFormatString(1200, 350 + 16 * 1, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerJumpSpeed());
	DrawFormatString(870, 350 + 16 * 2, GetColor(255, 255, 255), "���������x");
	DrawFormatString(1200, 350 + 16 * 2, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerFallAcceleration());
	DrawFormatString(870, 350 + 16 * 3, GetColor(255, 255, 255), "�ő嗎�����x");
	DrawFormatString(1200, 350 + 16 * 3, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMaxFallSpeed());
	DrawFormatString(870, 350 + 16 * 4, GetColor(255, 255, 255), "�W�����v��");
	DrawFormatString(1200, 350 + 16 * 4, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxJumpCount());
	DrawFormatString(870, 350 + 16 * 5, GetColor(255, 255, 255), "��𑬓x");
	DrawFormatString(1200, 350 + 16 * 5, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerDodgeSpeed());
	DrawFormatString(870, 350 + 16 * 6, GetColor(255, 255, 255), "����t���[����");
	DrawFormatString(1200, 350 + 16 * 6, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxDodgeFlame());
	DrawFormatString(870, 350 + 16 * 7, GetColor(255, 255, 255), "�ǃL�b�N���x(��������)");
	DrawFormatString(1200, 350 + 16 * 7, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerKickWallHorizontalSpeed());
	DrawFormatString(870, 350 + 16 * 8, GetColor(255, 255, 255), "�ǃL�b�N���x(��������)");
	DrawFormatString(1200, 350 + 16 * 8, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerKickWallVerticalSpeed());
	DrawFormatString(870, 350 + 16 * 9, GetColor(255, 255, 255), "�ǃL�b�N�p���t���[����");
	DrawFormatString(1200, 350 + 16 * 9, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerKickWallFlame());
	DrawFormatString(870, 350 + 16 * 10, GetColor(255, 255, 255), "�ǃL�b�N���͗P�\�t���[����");
	DrawFormatString(1200, 350 + 16 * 10, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerKickWallInputMaxFlame());
	DrawFormatString(870, 350 + 16 * 11, GetColor(255, 255, 255), "�ߋ����U��(��)�ɐ؂�ւ��`���[�W�t���[����");
	DrawFormatString(1200, 350 + 16 * 11, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMelleStrongChangeChargeFrame());
	DrawFormatString(870, 350 + 16 * 12, GetColor(255, 255, 255), "�ߋ����U��(��)�̍ő�`���[�W�t���[����");
	DrawFormatString(1200, 350 + 16 * 12, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMelleStrongMaxChargeFrame());
	DrawFormatString(870, 350 + 16 * 13, GetColor(255, 255, 255), "�ߋ����U��(��)�̈ړ��X�P�[��");
	DrawFormatString(1200, 350 + 16 * 13, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMelleStrongMoveScale());
	DrawFormatString(870, 350 + 16 * 14, GetColor(255, 255, 255), "�ߋ����U��(��)�̈ړ����x");
	DrawFormatString(1200, 350 + 16 * 14, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerMeleeStrongMoveSpeed());
	DrawFormatString(870, 350 + 16 * 15, GetColor(255, 255, 255), "�ߋ����U��(��)�̘A���U���ő�t���[����");
	DrawFormatString(1200, 350 + 16 * 15, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMeleeStrongContinusMaxFrame());
	DrawFormatString(870, 350 + 16 * 16, GetColor(255, 255, 255), "���b�N�I���͈͂̔��a");
	DrawFormatString(1200, 350 + 16 * 16, GetColor(255, 255, 255), "%f", this->PlayerStatusList->fGetPlayerRockOnRadius());
	DrawFormatString(870, 350 + 16 * 17, GetColor(255, 255, 255), "�ő�HP");
	DrawFormatString(1200, 350 + 16 * 17, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxHp());
	DrawFormatString(870, 350 + 16 * 18, GetColor(255, 255, 255), "�ő喳�G����");
	DrawFormatString(1200, 350 + 16 * 18, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMaxInvincibleTime());
	DrawFormatString(870, 350 + 16 * 19, GetColor(255, 255, 255), "�󒆂ł̋ߐڍU��(��)��");
	DrawFormatString(1200, 350 + 16 * 19, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetPlayerMeleeStrongAirMaxCount());
	DrawFormatString(870, 350 + 16 * 20, GetColor(255, 255, 255), "������ԃN�i�C��������");
	DrawFormatString(1200, 350 + 16 * 20, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetStartHaveKunai());
	DrawFormatString(870, 350 + 16 * 21, GetColor(255, 255, 255), "�ő�N�i�C������");
	DrawFormatString(1200, 350 + 16 * 21, GetColor(255, 255, 255), "%d", this->PlayerStatusList->iGetMaxhaveKunai());

	/* ����`�� */
	if (this->bSelectFlg == true)
	{
		DrawFormatString(850, 350 + 16 * this->iSelectItem, GetColor(255, 0, 0), "��");
	}
	else
	{
		DrawFormatString(850, 350 + 16 * this->iSelectItem, GetColor(255, 255, 255), "��");
	}
}
