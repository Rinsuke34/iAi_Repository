/* 2024.12.XX YYYY ZZZZ */

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
		this->iImageDateHandle = *ImageList->piGetImage("Test/UIData");
		this->iImageDateChoiceHandle = *ImageList->piGetImage("Test/UIData_Choice");

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

	this->bGameStartFlg = false;

	//UI�J�E���g��������
	this->iUICount = CAMERA_FIXED_POSITION_START;

	//�J�����Œ�ʒu��ݒ�
	pSceneStage->SetNowCameraFixedPositionNo(0);
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
	//UI�J�E���g�ɂ���ď����𕪊�
    switch (iUICount)
	{
		// �J�����̈ʒu���|�W�V����A�܂���B���m�F
        case CAMERA_FIXED_POSITION_A:
        case CAMERA_FIXED_POSITION_B:

		//�J�����̈ʒu���|�W�V����A�܂���B�̏ꍇ
		// ����{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
		{
			//����{�^���������ꂽ�ꍇ
			//Ui�J�E���g���|�W�V����E�ɕύX
            iUICount = CAMERA_FIXED_POSITION_E;

			//�J�����Œ�ʒu���擾
			pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);

			//�Q�[���X�^�[�g�t���O�𖳌���
			this->bGameStartFlg = FALSE;
		}
		
		// ��{�^���������ꂽ���m�F
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
        {
            // ��{�^���������ꂽ�ꍇ
            //UI�J�E���g������
            iUICount--;

			//UI�J�E���g���|�W�V����A��菬�������m�F
            if (iUICount < CAMERA_FIXED_POSITION_A)
            {
				//UI�J�E���g���|�W�V����A��菬�����ꍇ
				//UI�J�E���g���|�W�V����D�ɐݒ�
                iUICount = CAMERA_FIXED_POSITION_D;
	}

			//�J�����Œ�ʒu���擾
            pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }

		// ���{�^���������ꂽ���m�F
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
        {
            // ���{�^���������ꂽ�ꍇ
			//UI�J�E���g�𑝉�
            iUICount++;

			//UI�J�E���g���|�W�V����E���傫�����m�F
            if (iUICount >= CAMERA_FIXED_POSITION_E)
            {
				//UI�J�E���g���|�W�V����E���傫���ꍇ
				//UI�J�E���g���|�W�V����A�ɐݒ�
                iUICount = CAMERA_FIXED_POSITION_A;
            }

			//�J�����Œ�ʒu���擾
            pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }

		// �L�����Z���{�^���������ꂽ���m�F
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
	{
            // �L�����Z���{�^���������ꂽ�ꍇ
			//UI�J�E���g���|�W�V�����X�^�[�g�ɐݒ�
            iUICount = CAMERA_FIXED_POSITION_START;

			//�J�����Œ�ʒu���擾
            pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }
        break;

		// �J�����̈ʒu���|�W�V����E���m�F
    case CAMERA_FIXED_POSITION_E:

		//�J�����̈ʒu���|�W�V����E�̏ꍇ
		//����{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID)&&this->bGameStartFlg == TRUE)
		{
			//����{�^���������ꂽ�ꍇ
            // �V�[���̒ǉ���ݒ�
			gpSceneServer->SetAddLoadSceneFlg(true);
	
			// �V�[���̍폜��ݒ�
			gpSceneServer->SetDeleteCurrentSceneFlg(true);
	
			// �V�[��"�Q�[���Z�b�g�A�b�v"��ǉ�
			gpSceneServer->AddSceneReservation(new SceneAddSceneGameSetup());
			return;
		}
		//�Q�[���X�^�[�g�t���O��L����
		this->bGameStartFlg = TRUE;

        // �L�����Z���{�^���������ꂽ���m�F
        if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
		{
			// �L�����Z���{�^���������ꂽ�ꍇ
			//UI�J�E���g���|�W�V����A�ɐݒ�
            iUICount = CAMERA_FIXED_POSITION_A;

			//�J�����Œ�ʒu���擾
			pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}
        break;

		// �J�����̈ʒu���|�W�V�����X�^�[�g���m�F
    case CAMERA_FIXED_POSITION_START:

		// �J�����̈ʒu���|�W�V�����X�^�[�g�̏ꍇ
			// �����{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_ANY))
	{
			// �����{�^���������ꂽ�ꍇ
			//UI�J�E���g���|�W�V����A�ɐݒ�
            iUICount++;

			//�J�����Œ�ʒu���擾
            pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
        }
        break;

		// �J�����̈ʒu���|�W�V����C�܂���D���m�F
    case CAMERA_FIXED_POSITION_D:
    case CAMERA_FIXED_POSITION_C:

		// �J�����̈ʒu���|�W�V����C�܂���D�̏ꍇ
		//��{�^���������ꂽ���m�F
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
	{
			//��{�^���������ꂽ�ꍇ
			//UI�J�E���g������
            iUICount--;

			//UI�J�E���g���|�W�V����A��菬�������m�F
            if (iUICount < CAMERA_FIXED_POSITION_A)
		{
				//UI�J�E���g���|�W�V����A��菬�����ꍇ
				//UI�J�E���g���|�W�V����D�ɐݒ�
                iUICount = CAMERA_FIXED_POSITION_D;
		}
			//�J�����Œ�ʒu���擾
		pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}
		//���{�^���������ꂽ���m�F
	if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
	{
			//���{�^���������ꂽ�ꍇ
			//UI�J�E���g�𑝉�
            iUICount++;

			//UI�J�E���g���|�W�V����E���傫�����m�F
            if (iUICount >= CAMERA_FIXED_POSITION_E)
	{
				//UI�J�E���g���|�W�V����E���傫���ꍇ
				//UI�J�E���g���|�W�V����A�ɐݒ�
                iUICount = CAMERA_FIXED_POSITION_A;
            }
           
			//�J�����Œ�ʒu���擾
			pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
	}

		//�L�����Z���{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
		{
			//�L�����Z���{�^���������ꂽ�ꍇ
			//UI�J�E���g���|�W�V�����X�^�[�g�ɐݒ�
            iUICount = CAMERA_FIXED_POSITION_START;

			//�J�����Œ�ʒu���擾
			pSceneStage->iGetNowCameraFixedPositionNo();

			//�J�����Œ�ʒu��UI�J�E���g�ɐݒ�
            pSceneStage->SetNowCameraFixedPositionNo(iUICount);
		}
        break;
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

	DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "����			�F�X�e�[�W1_1��");
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
