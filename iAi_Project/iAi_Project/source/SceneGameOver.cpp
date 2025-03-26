/* 2025.02.20 �t�@�C���쐬 ��򕗏� */

#include "SceneGameOver.h"

/* �V�[��"�Q�[���I�[�o�["�N���X�̒�` */

// �R���X�g���N�^
SceneGameOver::SceneGameOver() : SceneBase("GameOver", 200, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList				= dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �摜�擾 */
		this->piGrHandle_GameOver				= ImageList->piGetImage_Movie("GameOver/UI_GameOver");

		/* �E�B���h�E(���g���C) */
		this->piGrHandle_Window_GameOver		= ImageList->piGetImage("GameOver/UI_Window_GameOver");

		/* �E�B���h�E(���g���C�x��) */
		this->piGrHandle_Window_GameOverCheck	= ImageList->piGetImage("GameOver/UI_Window_GameOver_Check");

		/* �X�L�b�v�m�F�E�B���h�E_�{�^�� */
		this->apiGrHandle_SkipWindow_Yes[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_Selected");
		this->apiGrHandle_SkipWindow_Yes[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_Yes_NotSelected");
		this->apiGrHandle_SkipWindow_No[0]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_Selected");
		this->apiGrHandle_SkipWindow_No[1]		= ImageList->piGetImage("Conversation/SkipWindow/UI_Moji_No_NotSelected");
	}

	/* ������ */
	this->iBlendAlpha	= 0;		// �`�ʂ���摜�̃A���t�@�l(0�`255)
	this->iDrawPhase	= 0;		// �`�ʃt�F�C�Y(0:�Q�[���I�[�o�[, 1:���g���C�m�F, 2:���g���C�ŏI�m�F)
	this->bSelectYes	= false;	// YES��I�𒆂ł��邩(�X�L�b�v���)
}

// �v�Z
void SceneGameOver::Process()
{
	/* �A���t�@�u�����h�l�����Z */
	this->iBlendAlpha += FADE_ALPHA_CHANGE_SPEED;

	/* �A���t�@�u�����h�l���ő�l(255)�𒴂��Ă��邩�m�F */
	if (this->iBlendAlpha > ALPHA_MAX)
	{
		// �ő�l�𒴂��Ă���ꍇ
		/* �ő�l�𒴂��Ȃ��悤�ɕ␳���s�� */
		this->iBlendAlpha = ALPHA_MAX;

		/* "����"�����͂��ꂽ���m�F */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			// "����"�����͂��ꂽ�Ȃ��
			/* "����"��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

			/* �`�ʃt�F�C�Y�ɉ��������� */
			switch (this->iDrawPhase)
			{
				/* �Q�[���I�[�o�[ */
				case 0:
					/* �`�ʃt�F�C�Y��"���g���C�m�F"�ɐݒ� */
					this->iDrawPhase = 1;
					break;

				/* ���g���C�m�F */
				case 1:
					/* YES��I�𒆂ł��邩�m�F */
					if (this->bSelectYes == true)
					{
						// YES��I�𒆂ł���ꍇ
						/* �Q�[����Ԃ�"���Z�b�g"�ɐݒ� */
						this->StageStatusList->SetGameStatus(GAMESTATUS_RESET);

						/* ���̃V�[���̍폜�t���O��L���ɂ��� */
						this->bDeleteFlg = true;
					}
					else
					{
						// YES��I�𒆂łȂ��ꍇ
						/* �`�ʃt�F�C�Y��"���g���C�ŏI�m�F"�ɐݒ� */
						this->iDrawPhase = 2;

						/* NO��I�𒆂̏�Ԃɂ��� */
						this->bSelectYes = false;
					}
					break;

				/* ���g���C�ŏI�m�F */
				case 2:
					/* YES��I�𒆂ł��邩�m�F */
					if (this->bSelectYes == true)
					{
						// YES��I�𒆂ł���ꍇ
						/* ���[�h�V�[���ǉ��t���O��L���� */
						gpSceneServer->SetAddLoadSceneFlg(true);

						/* ���s�V�[���폜�t���O��L���� */
						gpSceneServer->SetDeleteCurrentSceneFlg(true);

						/* �V�[��"�^�C�g��"��ǉ� */
						gpSceneServer->AddSceneReservation(new SceneAddTitleSetup());
					}
					else
					{
						// YES��I�𒆂łȂ��ꍇ
						/* �`�ʃt�F�C�Y��"���g���C�m�F"�ɐݒ� */
						this->iDrawPhase = 1;
					}
					break;
			}
		}

		/* "��"�����͂��ꂽ���m�F */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
		{
			// ���͂��ꂽ�ꍇ
			/* "�J�[�\���ړ�"��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

			/* YES��I�𒆂̏�Ԃɂ��� */
			this->bSelectYes = true;
		}

		/* "�E"�����͂��ꂽ���m�F */
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
		{
			// ���͂��ꂽ�ꍇ
			/* "�J�[�\���ړ�"��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

			/* NO��I�𒆂̏�Ԃɂ��� */
			this->bSelectYes = false;
		}
	}
}

// �`��
void SceneGameOver::Draw()
{
	/* �`�ʃu�����h���[�h��"�A���t�@�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iBlendAlpha);

	/* ��ʑS�̂����F�ŕ`�� */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);

	/* �`�ʃu�����h���[�h��"�m�[�u�����h"�ɐݒ� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/* �A���t�@�u�����h�l���ő�l(255)�𒴂��Ă��邩�m�F */
	if (this->iBlendAlpha >= ALPHA_MAX)
	{
		// �ő�l�𒴂��Ă���ꍇ
		/* �`�ʃt�F�C�Y�ɉ��������� */
		switch (this->iDrawPhase)
		{
			/* �Q�[���I�[�o�[ */
			case 0:
				/* �Q�[���I�[�o�[��ʂ��Đ� */
				PlayMovieToGraph(*this->piGrHandle_GameOver);

				/* "�Q�[���I�[�o�["��`�� */
				DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_GameOver, TRUE);

				/* �Đ����I�����Ă��邩�m�F */
				if (GetMovieStateToGraph(*this->piGrHandle_GameOver) == FALSE)
				{
					// �Đ����I�����Ă���ꍇ
					/* ���[�r�[�̍Đ����Ԃ����������� */
					SeekMovieToGraph(*this->piGrHandle_GameOver, 0);
				}
				break;

			/* ���g���C�m�F */
			case 1:
				/* "���g���C�m�F"��`�� */
				DrawGraph(570, 270, *this->piGrHandle_Window_GameOver, TRUE);
				break;

			/* ���g���C�ŏI�m�F */
			case 2:
				/* "���g���C�ŏI�m�F"��`�� */
				DrawGraph(570, 270, *this->piGrHandle_Window_GameOverCheck, TRUE);
				break;
		}
	}

	/* �`�ʃt�F�C�Y��"�Q�[���I�[�o�["�ȊO�ł��邩�m�F */
	if (this->iDrawPhase != 0)
	{
		// "�Q�[���I�[�o�["�ȊO�ł���ꍇ
		/* YES���I�𒆂ł��邩�m�F */
		if (this->bSelectYes == true)
		{
			// YES���I�𒆂̏ꍇ
			/* YES��I�𒆂Ƃ��ĕ`�� */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[0], TRUE);

			/* NO���I�𒆂Ƃ��ĕ`�� */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[1], TRUE);
		}
		else
		{
			// YES���I�𒆂łȂ��ꍇ
			/* YES���I�𒆂Ƃ��ĕ`�� */
			DrawGraph(690, 560, *this->apiGrHandle_SkipWindow_Yes[1], TRUE);

			/* NO��I�𒆂Ƃ��ĕ`�� */
			DrawGraph(1020, 560, *this->apiGrHandle_SkipWindow_No[0], TRUE);
		}
	}
}
