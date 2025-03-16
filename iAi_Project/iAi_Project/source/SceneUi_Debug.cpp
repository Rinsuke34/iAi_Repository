/* 2025.01.31 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Debug.h"

/* UI(�f�o�b�O���j���[)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Debug::SceneUi_Debug() : SceneBase("UI_Debug", 200, true)
{
	/* ������ */
	this->iSelectMode	= DEBUG_MODE_OPTION;
	this->iSelectNo		= 0;

	/* �O���[�o���ϐ����f�o�b�O���ڂɓo�^ */
	pDebugManu.push_back(&gbDrawSceneListFlg);			// �V�[�����X�g�̕`��
	pDebugManu.push_back(&gbDrawDatalistFlg);			// �f�[�^���X�g�̕`��
	pDebugManu.push_back(&gbDrawShadowMapFlg);			// �V���h�E�}�b�v�̕`��
	pDebugManu.push_back(&gbDrawLightMapFlg);			// ���C�g�}�b�v�̕`��
	pDebugManu.push_back(&gbDrawLightMapDownScaleFlg);	// ���C�g�}�b�v(�k��)�̕`��
	pDebugManu.push_back(&gbDrawLightMapGaussFlg);		// ���C�g�}�b�v(�ڂ���)�̃n���h��
	pDebugManu.push_back(&gbDrawCollisionFlg);			// �S�I�u�W�F�N�g�̃R���W�����`��
	pDebugManu.push_back(&gbDrawDeleteBackGroundFlg);	// �o�b�N�O�����h�I�u�W�F�N�g�̔�\��
	pDebugManu.push_back(&gbUseMouseFlg);				// �}�E�X�g�p�t���O�̗L���E�����̐؂�ւ�
	pDebugManu.push_back(&gbDrawFpsFlg);				// �t���[�����[�g�̕`��
}

// �v�Z
void SceneUi_Debug::Process()
{
	/* ���[�h�ɉ����ď�����ύX���� */
	switch (this->iSelectMode)
	{
		/* �f�o�b�O�I�v�V���� */
		case DEBUG_MODE_OPTION:
			/* �v���C���[�̓��͎擾 */
			// ���v���C���[�̓��͂ɉ����đI�𒆂̍��ڔԍ���ύX����
			// �����
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
			{
				this->iSelectNo -= 1;
				if (this->iSelectNo < 0)
				{
					this->iSelectNo = 0;
				}
			}

			// ������
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
			{
				this->iSelectNo += 1;
				if (this->iSelectNo > pDebugManu.size())
				{
					this->iSelectNo = (int)pDebugManu.size();
				}
			}

			// ����
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
			{
				*pDebugManu[this->iSelectNo] = bToggleFlg(*pDebugManu[this->iSelectNo]);
			}
			break;

		/* �f�o�b�O���� */
		case DEBUG_MODE_OPERATION:
			/* �v���C���[�̓��͎擾 */
			// ���v���C���[�̓��͂ɉ����đI�𒆂̍��ڔԍ���ύX����
			// �����
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
			{
				this->iSelectNo -= 1;
				if (this->iSelectNo < 0)
				{
					this->iSelectNo = 0;
				}
			}

			// ������
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
			{
				this->iSelectNo += 1;
				if (this->iSelectNo > DEBUG_OPERATION_MAX)
				{
					this->iSelectNo = DEBUG_OPERATION_MAX;
				}
			}

			// ����
			if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
			{
				switch (this->iSelectNo)
				{
					/* �X�e�[�W�W�����v */
					case DEBUG_OPERATION_STAGEJUMP:
						{
							/* �V�[��"�X�e�[�W�W�����v"���쐬 */
							SceneBase* pAddScene = new SceneUi_Debug_StageJump();

							/* �V�[��"�X�e�[�W�W�����v"���V�[���T�[�o�[�ɒǉ� */
							gpSceneServer->AddSceneReservation(pAddScene);
						}
						break;

					/* �X�e�[�^�X���� */
					case DEBUG_OPERATION_STATUSSETUP:
						{
							/* �V�[��"�X�e�[�^�X����"���쐬 */
							SceneBase* pAddScene = new SceneUi_Debug_StatusSetup();
						
							/* �V�[��"�X�e�[�^�X����"���V�[���T�[�o�[�ɒǉ� */
							gpSceneServer->AddSceneReservation(pAddScene);
						}
						break;
				}
			}
			break;
	}

	// ������
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		this->iSelectNo = 0;

		this->iSelectMode += 1;
		if (this->iSelectMode >= DEBUG_MODE_MAX)
		{
			this->iSelectMode = DEBUG_MODE_MAX - 1;
		}
	}

	// �E����
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		this->iSelectNo = 0;

		this->iSelectMode -= 1;
		if (this->iSelectMode <= 0)
		{
			this->iSelectMode = 0;
		}
	}

	// �߂�
	{
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			this->bDeleteFlg = true;
		}
	}
}

// �`��
void SceneUi_Debug::Draw()
{
	/* ���[�h�ɉ����ď�����ύX���� */
	switch (this->iSelectMode)
	{
		/* �f�o�b�O�I�v�V���� */
		case DEBUG_MODE_OPTION:
			DrawBox(780, 300, 1200, 300 - 16, GetColor(255, 0, 0), TRUE);
			DrawFormatString(800, 300 - 16, GetColor(255, 255, 255), "�f�o�b�O�I�v�V����");
			DrawBox(780, 300, 1200, 300 + 16 * 10, GetColor(0, 0, 0), TRUE);
			DrawFormatString(800, 300 + 16 * 0, GetColor(255, 255, 255), "�V�[�����X�g�̕`��");
			DrawFormatString(800, 300 + 16 * 1, GetColor(255, 255, 255), "�f�[�^���X�g�̕`��");
			DrawFormatString(800, 300 + 16 * 2, GetColor(255, 255, 255), "�V���h�E�}�b�v�̕`��");
			DrawFormatString(800, 300 + 16 * 3, GetColor(255, 255, 255), "���C�g�}�b�v�̕`��");
			DrawFormatString(800, 300 + 16 * 4, GetColor(255, 255, 255), "���C�g�}�b�v(�k��)�̕`��");
			DrawFormatString(800, 300 + 16 * 5, GetColor(255, 255, 255), "���C�g�}�b�v(�ڂ���)�̃n���h��");
			DrawFormatString(800, 300 + 16 * 6, GetColor(255, 255, 255), "�S�I�u�W�F�N�g�̃R���W�����`��");
			DrawFormatString(800, 300 + 16 * 7, GetColor(255, 255, 255), "�o�b�N�O�����h�I�u�W�F�N�g�̔�\��");
			DrawFormatString(800, 300 + 16 * 8, GetColor(255, 255, 255), "�}�E�X�g�p�t���O");
			DrawFormatString(800, 300 + 16 * 9, GetColor(255, 255, 255), "�t���[�����[�g�̕`��");
			break;

		/* �f�o�b�O���� */
		case DEBUG_MODE_OPERATION:
			DrawBox(780, 300, 1200, 300 - 16, GetColor(255, 0, 0), TRUE);
			DrawFormatString(800, 300 - 16, GetColor(255, 255, 255), "�f�o�b�O����");
			DrawBox(780, 300, 1200, 300 + 16 * 2, GetColor(0, 0, 0), TRUE);
			DrawFormatString(800, 300 + 16 * 0, GetColor(255, 255, 255), "�X�e�[�W�W�����v");
			DrawFormatString(800, 300 + 16 * 1, GetColor(255, 255, 255), "�X�e�[�^�X����");
			break;

	}

	/* ����`�� */
	DrawFormatString(780, 300 + 16 * this->iSelectNo, GetColor(255, 255, 255), "��");
}

// true��false�̐؂�ւ�
bool SceneUi_Debug::bToggleFlg(bool bFlg)
{
	// ����
	// bFlg	: �؂�ւ���t���O

	return !bFlg;
}
