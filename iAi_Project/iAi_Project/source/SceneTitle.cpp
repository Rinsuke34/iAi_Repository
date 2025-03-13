/* 2024.12.20 �t�@�C���ǉ�					��򕗏� */
/* 2025.01.09 ��o�p�Վ��R�[�f�B���O�C��	��򕗏� */

#include "SceneTitle.h"

/* �V�[���u�^�C�g���v�̒�` */

// �R���X�g���N�^
SceneTitle::SceneTitle() : SceneBase("Title", 10, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "���͊Ǘ�"���擾 */
		this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	}

	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �^�C�g�����S */
		this->piGrHandle_TitleLogo = ImageList->piGetImage_Movie("Test/TitleLogo");

		/* �j���[�Q�[�� */
		this->iImageNewgameHandle = *ImageList->piGetImage("Test/UINewgame");
		this->iImageNewgameChoiceHandle = *ImageList->piGetImage("Test/UINewgame_Choice");

		/* �R���e�B�j���[ */
		this->iImageContinueHandle = *ImageList->piGetImage("Test/UIContinue");
		this->iImageContinueChoiceHandle = *ImageList->piGetImage("Test/UIContinue_Choice");

		/* �f�[�^ */
		this->iImageDateHandle = *ImageList->piGetImage("Test/gameend");
		this->iImageDateChoiceHandle = *ImageList->piGetImage("Test/gameend2");

		/* �R���t�B�O */
		this->iImageConfigHandle = *ImageList->piGetImage("Test/UIConfig");
		this->iImageConfigChoiceHandle = *ImageList->piGetImage("Test/UIConfig_Choice");

	}

	/* BGM��ݒ� */
	gpDataList_Sound->BGM_SetHandle(BGM_TITLE);

	/* �ŏ��̃X�e�[�W�ԍ���"�^�C�g��/�z�[��"�ɐݒ� */
	this->StageStatusList->SetNowStageNo(STAGE_NO_TITLE);

	/* �J�������[�h��"�^�C�g��"�ɐݒ� */
	this->StageStatusList->SetCameraMode(CAMERA_MODE_TITLE);

	/* UI�ǉ��t���O�𖳌��� */
	this->StageStatusList->SetAddUiFlg(false);

	/* "�^�C�g��"�̃X�e�[�W��ǂݍ��� */
	/* �V�[��"�^�C�g��"���쐬 */
	this->pSceneStage = new SceneStage();

	/* �V�[��"�X�e�[�W"���V�[���T�[�o�[�ɒǉ� */
	gpSceneServer->AddSceneReservation(this->pSceneStage);

	/* �X�e�[�W�̓ǂݍ��݂��J�n */
	dynamic_cast<SceneStage*>(this->pSceneStage)->LoadMapData();

	/* ���������� */
	this->pSceneStage->Initialization();

	//�X�^�[�g�t���O�𖳌���
	this->bGameStartFlg = false;

	//�z�[���t���O�𖳌���
	this->bHomeFlg = false;


	//UI�J�E���g��������
	this->iUICount = CAMERA_FIXED_POSITION_START;

	//�J�����Œ�ʒu��ݒ�
	pSceneStage->SetNowCameraFixedPositionNo(0);

	/* �{�C�X"�^�C�g���R�[��"�Đ� */
	gpDataList_Sound->VOICE_PlaySound(VOICE_TITLE_CALL);
}

// �f�X�g���N�^
SceneTitle::~SceneTitle()
{
	
}

// ������
void SceneTitle::Initialization()
{
	
}

// �v�Z
void SceneTitle::Process()
{
	// ����{�^���������ꂽ���m�F
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
	{
    switch (iUICount)
	{
		case CAMERA_FIXED_POSITION_START:
			//UI�J�E���g(�J����)���͂��߂���z�[����ʂɐݒ�
			iUICount++;

			//�J�����Œ�ʒu���͂��߂���z�[����ʂɐݒ�
			pSceneStage->SetNowCameraFixedPositionNo(iUICount);
			this->bHomeFlg = TRUE;

			break;
			//�͂��߂���z�[�����
        case CAMERA_FIXED_POSITION_A:
			//�Â�����z�[�����
        case CAMERA_FIXED_POSITION_B:
			//Ui�J�E���g(�J����)���m�F��ʂɕύX
	            iUICount = CAMERA_FIXED_POSITION_E;

			//�J�����Œ�ʒu��UI�J�E���g(�J����)�ɐݒ�
		        pSceneStage->SetNowCameraFixedPositionNo(iUICount);

				//�Q�[���X�^�[�g�t���O�𖳌���
				this->bGameStartFlg = FALSE;

			//�z�[���t���O�𖳌���
			this->bHomeFlg = FALSE;
			break;

			//�m�F���
		case CAMERA_FIXED_POSITION_E:
			if (this->bGameStartFlg == TRUE)
			{
				// �V�[���̒ǉ���ݒ�
				gpSceneServer->SetAddLoadSceneFlg(true);
	
				// �V�[���̍폜��ݒ�
				gpSceneServer->SetDeleteCurrentSceneFlg(true);
	
				// �V�[��"�Q�[���Z�b�g�A�b�v"��ǉ�
				gpSceneServer->AddSceneReservation(new SceneAddSceneGameSetup());
				return;
			}
			this->bGameStartFlg = TRUE;
			break;

			//�f�[�^�z�[�����
		case CAMERA_FIXED_POSITION_C:
		{
			gbEndFlg = true;
		}
			//�ݒ�z�[�����
		case CAMERA_FIXED_POSITION_D:
			/* ���݂̃J�����|�W�V�������ݒ��ʂł��邩�m�F */
			if (this->iUICount == CAMERA_FIXED_POSITION_D)
			{
				/* �V�[��"�I�v�V����"��ǉ� */
				gpSceneServer->AddSceneReservation(new SceneOption());
			}
			//�z�[���t���O�𖳌���
			this->bHomeFlg = FALSE;
			break;
			}
	}

	// �L�����Z���{�^���������ꂽ���m�F
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
		switch (iUICount)
		{
			//�͂��߂���z�[�����
		case CAMERA_FIXED_POSITION_A:
			//�Â�����z�[�����
		case CAMERA_FIXED_POSITION_B:
			//�f�[�^�z�[�����
		case CAMERA_FIXED_POSITION_C:
			//UI�J�E���g(�J����)���^�C�g���ɐݒ�
			iUICount = CAMERA_FIXED_POSITION_START;
			break;


			//�ݒ�z�[�����
		case CAMERA_FIXED_POSITION_D:
			//�z�[���t���O���L�����m�F
			if (this->bHomeFlg == FALSE)
			{
				//UI�J�E���g(�J����)���͂��߂���z�[����ʂɐݒ�
				iUICount = CAMERA_FIXED_POSITION_D;
			}
			if (this->bHomeFlg == TRUE)
				{
				//UI�J�E���g(�J����)���͂��߂���z�[����ʂɐݒ�
				iUICount = CAMERA_FIXED_POSITION_START;
				}
			this->bHomeFlg = TRUE;
			break;

			//�m�F���
		case CAMERA_FIXED_POSITION_E:
			//UI�J�E���g���͂��߂���z�[����ʂɐݒ�
			iUICount = CAMERA_FIXED_POSITION_A;
			break;
		}

		//�J�����Œ�ʒu���J�����ɐݒ�
		pSceneStage->SetNowCameraFixedPositionNo(iUICount);
			}
			
			//��{�^���������ꂽ���m�F
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
			{
		switch (iUICount)
		{
			//�^�C�g�����
		case CAMERA_FIXED_POSITION_START:
			iUICount = 0;
			break;
			//�͂��߂���z�[�����
		case CAMERA_FIXED_POSITION_A:
			//�Â�����z�[�����
		case CAMERA_FIXED_POSITION_B:
			//�f�[�^�z�[�����
		case CAMERA_FIXED_POSITION_C:
			//�ݒ�z�[�����
		case CAMERA_FIXED_POSITION_D:
				//UI�J�E���g������
				iUICount--;

			//UI�̑I��������ɂ��邩�m�F
				if (iUICount < CAMERA_FIXED_POSITION_A)
				{
				//��ɂȂ��ꍇ
				//UI�J�E���g(�J����)��ݒ�z�[����ʂɐݒ�
				     iUICount = CAMERA_FIXED_POSITION_D;
				}
			break;
		}

				//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
	            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
			}

			//���{�^���������ꂽ���m�F
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
			{
		switch (iUICount)
		{
			//�^�C�g�����
		case CAMERA_FIXED_POSITION_START:
			iUICount = 0;
			break;
			//�͂��߂���z�[�����
		case CAMERA_FIXED_POSITION_A:
			//�Â�����z�[�����
		case CAMERA_FIXED_POSITION_B:
			//�f�[�^�z�[�����
		case CAMERA_FIXED_POSITION_C:
			//�ݒ�z�[�����
		case CAMERA_FIXED_POSITION_D:
				//UI�J�E���g�𑝉�
				iUICount++;

			//�I���������ɂ��邩�m�F
				if (iUICount >= CAMERA_FIXED_POSITION_E)
				{
				//���ɂȂ��ꍇ
				//UI�J�E���g(�J����)���͂��߂���z�[����ʂɐݒ�
				    iUICount = CAMERA_FIXED_POSITION_A;
				}
			break;
			}

				//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
			    pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}
}

// �`��
void SceneTitle::Draw()
{
	if (iUICount == CAMERA_FIXED_POSITION_START)
	{
	/* �`��u�����h���[�h�����Z�ɂ��� */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	/* �^�C�g�����S���Đ� */
	PlayMovieToGraph(*this->piGrHandle_TitleLogo);

	/* ���[�r�[��`�� */
	DrawGraph(100, -100, *this->piGrHandle_TitleLogo, TRUE);

	/* �Đ����I�����Ă��邩�m�F */
	if (GetMovieStateToGraph(*this->piGrHandle_TitleLogo) == FALSE)
	{
		// �Đ����I�����Ă���ꍇ
		/* ���[�r�[�̍Đ����Ԃ����������� */
		SeekMovieToGraph(*this->piGrHandle_TitleLogo, 0);
	}

	/* �`��u�����h���[�h���u�����h�����ɖ߂� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* �`�惂�[�h���A���X�g�ɖ߂� */
	SetDrawMode(DX_DRAWMODE_NEAREST);

	}

	switch (iUICount)
	{
	case CAMERA_FIXED_POSITION_A:
		/* �j���[�Q�[�� */
		DrawGraph(100, 589, this->iImageNewgameChoiceHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
		break;
	case CAMERA_FIXED_POSITION_B:
		DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueChoiceHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
		break;
	case CAMERA_FIXED_POSITION_C:
		DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateChoiceHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigHandle, TRUE);
		break;
	case CAMERA_FIXED_POSITION_D:
		DrawGraph(100, 589, this->iImageNewgameHandle, TRUE);
		DrawGraph(100, 690, this->iImageContinueHandle, TRUE);
		DrawGraph(100, 795, this->iImageDateHandle, TRUE);
		DrawGraph(100, 900, this->iImageConfigChoiceHandle, TRUE);
		break;
	}
}
