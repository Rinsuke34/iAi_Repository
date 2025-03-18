/* 2025.03.05 �t�@�C���쐬 ��򕗏� */

#include "ScenePause.h"

/* �ꎞ��~�N���X�̒�` */
// �R���X�g���N�^
ScenePause::ScenePause() : SceneBase("Pause", 450, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ��� */
		this->piGrHandle_Arrow = ImageList->piGetImage("Test/Sign");
	}

	/* ������ */
	this->iSelectItem	= PAUSE_MANU_CONTINUE;
}

// �v�Z
void ScenePause::Process()
{
	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* �I�𒆂̍��ڂɂ���ď����𕪊� */
		switch (this->iSelectItem)
		{
			/* ������ */
			case PAUSE_MANU_CONTINUE:
				/* ���̃V�[���̍폜�t���O��L���ɂ��� */
				this->bDeleteFlg = true;
				break;

			/* �ŏ����� */
			case PAUSE_MANU_RESTART:
				/* �Q�[����Ԃ�"���Z�b�g"�ɕύX���� */
				this->StageStatusList->SetGameStatus(GAMESTATUS_RESET);

				/* ���̃V�[���̍폜�t���O��L���ɂ��� */
				this->bDeleteFlg = true;
				break;

			/* �I�v�V���� */
			case PAUSE_MANU_OPTION:
				/* �V�[��"�I�v�V����"��ǉ� */
				gpSceneServer->AddSceneReservation(new SceneOption());
				break;

			/* �^�C�g���� */
			case PAUSE_MANU_TITLE:
				/* ���[�h��ʒǉ��t���O��L���� */
				gpSceneServer->SetAddLoadSceneFlg(true);

				/* ���s�V�[���폜�t���O��L���� */
				gpSceneServer->SetDeleteCurrentSceneFlg(true);

				/* �V�[��"�^�C�g��"��ǉ� */
				gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
				break;
		}

		return;
	}

	/* "�L�����Z��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
	{
		// ���͂���Ă���ꍇ
		/* ���̃V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		return;
	}

	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// ���͂���Ă���ꍇ
		/* �I�����ڂ���ɐi�߂� */
		this->iSelectItem -= 1;
	}

	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// ���͂���Ă���ꍇ
		/* �I�����ڂ����ɐi�߂� */
		this->iSelectItem += 1;
	}

	/* �I�𒆂̍��ڂ̔ԍ���͈͓��Ɏ��߂�*/
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= PAUSE_MANU_MAX)
	{
		this->iSelectItem = PAUSE_MANU_MAX - 1;
	}
}

// �`��
void ScenePause::Draw()
{
	/* ��ʑS�̂��Â����� */
	{
		/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, PAUSE_BLACK_ALPHA);

		/* ��ʑS�̂����F�ŕ`�� */
		DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

		/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	/* �I�����`�� */
	{
		/* ������ */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2 - 100, GetColor(255, 255, 255), giFontHandle_Small, "������");

		/* �ŏ����� */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2 - 50, GetColor(255, 255, 255), giFontHandle_Small, "�ŏ�����");

		/* �I�v�V���� */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2, GetColor(255, 255, 255), giFontHandle_Small, "�I�v�V����");

		/* �^�C�g���� */
		DrawFormatStringToHandle(SCREEN_SIZE_WIDE / 2 - 100, SCREEN_SIZE_HEIGHT / 2 + 50, GetColor(255, 255, 255), giFontHandle_Small, "�^�C�g����");
	}

	/* ���`�� */
	{
		/* ���̕`�� */
		DrawGraph(SCREEN_SIZE_WIDE / 2 - 150, SCREEN_SIZE_HEIGHT / 2 - 100 + this->iSelectItem * 50, *this->piGrHandle_Arrow, TRUE);
	}
}
