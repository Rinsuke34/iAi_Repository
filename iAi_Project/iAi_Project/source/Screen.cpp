/* 2025.02.28 �ΐ�q�� �t�@�C���쐬 */
#include "Screen.h"

// �R���X�g���N�^
Screen::Screen() : PlatformBase()
{
	/* �f�[�^���X�g */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}
	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Object/SignBoard/SignBoard");
	}

	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �X�N���[���ɉf��f�� */
		this->iTextureTitleHandle = *ImageList->piGetImage_Movie("Home/TitleLogo");			//�^�C�g��
		this->iTextureNewgameHandle = *ImageList->piGetImage_Movie("Home/Newgame");			//�j���[�Q�[��
		this->iTextureContinueHandle = *ImageList->piGetImage_Movie("Home/Continue");		//�R���e�B�j���[
		this->iTextureDateHandle = *ImageList->piGetImage_Movie("Home/Config");				//�R���t�B�O
		this->iTextureConfigHandle = *ImageList->piGetImage("Home/GameEnd");				//�f�[�^
		this->iTextureStageHandle = *ImageList->piGetImage_Movie("Home/TitleLogo");			//�X�e�[�W
	}

	/* UI�J�E���g�������� */
	this->iUICount = CAMERA_FIXED_POSITION_START;

	//����Đ��t���O��������
	this->bStartFlg = false;

	//�z�[���t���O��������
	this->bHomeFlg = false;

	//�Q�[���X�^�[�g�t���O��������
	this->bGameStartFlg = false;

	/* �X�N���[���𔭌��t���[���Ƃ��ēo�^ */
	{
		/* ���f���n���h������t���[�������擾 */
		int iFrameNum = MV1GetFrameNum(this->iModelHandle);

		/* ��������t���[���ԍ����擾���� */
		for (int i = 0; i < iFrameNum; i++)
		{
			/* �t���[�����擾 */
			const char* cFrameName = MV1GetFrameName(this->iModelHandle, i);

			/* �ŏ���6������"Screen"�ł��邩�m�F */
			if (strncmp(cFrameName, "Screen", 5) == 0)
			{
				/* �����t���[���ԍ����擾 */
				this->aiLightFrameNo.push_back(i);

				/* �����t���[���̐e�t���[���ԍ����擾 */
				int parentFrame = MV1GetFrameParent(this->iModelHandle, i);

				/* �����t���[���̐e�t���[�������݂���Ȃ�� */
				while (parentFrame >= 0)
				{
					// �e�t���[�������݂���ꍇ
					/* �e�t���[���ԍ���ǉ� */
					this->aiLightFrameNo.push_back(parentFrame);

					/* �e�t���[���ԍ��̐e�t���[�����擾 */
					parentFrame = MV1GetFrameParent(this->iModelHandle, parentFrame);
				}

				/* ���[�v�𔲂��� */
				break;
			}
		}
	}
}

// �f�X�g���N�^
Screen::~Screen()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

//����
void Screen::Process()
{
	if (g_bActiveFlg == false)
	{
	//���݂̃V�[�����^�C�g���V�[�����m�F
	if (gpSceneServer->GetScene("Title"))
	{
		// ����{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			switch (iUICount)
			{
				//�^�C�g�����
			case CAMERA_FIXED_POSITION_START:
				// Home�t���O��L����
				this->bHomeFlg = TRUE;

				// UI�J�E���g���͂��߂���ɕύX
				iUICount = CAMERA_FIXED_POSITION_A;
				break;

				//�͂��߂���z�[�����
			case CAMERA_FIXED_POSITION_A:
				//�Â�����z�[�����
			case CAMERA_FIXED_POSITION_B:
				// Home�t���O�𖳌���
				this->bGameStartFlg = FALSE;
				//�z�[���t���O�𖳌���
				this->bHomeFlg = FALSE;

				this->bStartFlg = TRUE;
				break;

				//�f�[�^�z�[�����
			case CAMERA_FIXED_POSITION_C:
				//�ݒ�z�[�����
			case CAMERA_FIXED_POSITION_D:
				// Home�t���O�𖳌���

			if (this->bHomeFlg == FALSE)
			{
				this->bHomeFlg = TRUE;
			}
					this->bHomeFlg = FALSE;

					this->bStartFlg = TRUE;
					break;
				}
		}

		// �L�����Z���{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_CANCEL))
		{
			switch (iUICount)
			{
				//�͂��߂���z�[�����
			case CAMERA_FIXED_POSITION_A:
				//�Â�����z�[�����
			case CAMERA_FIXED_POSITION_B:
				//�z�[���t���O���L�����m�F
				if (this->bHomeFlg == FALSE)
				{
					//�z�[���t���O���L���ȏꍇ
					//UI�J�E���g(�J����)���͂��߂���ɐݒ�
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				if (this->bHomeFlg == TRUE)
				{
					//�z�[���t���O���L���ȏꍇ
					//UI�J�E���g(�J����)���^�C�g���ɐݒ�
					iUICount = CAMERA_FIXED_POSITION_START;
				}

				//�z�[���t���O��L����
				this->bHomeFlg = TRUE;

				this->bStartFlg = TRUE;
				break;
				//�f�[�^�z�[�����
			case CAMERA_FIXED_POSITION_C:

				if (this->bHomeFlg == FALSE)
				{
				if (iUICount == CAMERA_FIXED_POSITION_C)
				{
					//���݂̃J�����|�W�V�������ݒ��ʂł��邩�m�F
					this->iUICount = CAMERA_FIXED_POSITION_C;
					this->bHomeFlg = TRUE;
				}
				}
				else
				{
					//UI�J�E���g(�J����)���^�C�g���ɐݒ�
					iUICount = CAMERA_FIXED_POSITION_START;
				}

				this->bStartFlg = TRUE;
				break;
				//�ݒ�z�[�����
			case CAMERA_FIXED_POSITION_D:
				
				if (this->bHomeFlg == FALSE)
				{
				if (iUICount == CAMERA_FIXED_POSITION_D)
				{
					iUICount = CAMERA_FIXED_POSITION_D;
					this->bHomeFlg = TRUE;
				}
				}
				else
				{
					//UI�J�E���g(�J����)���^�C�g���ɐݒ�
					iUICount = CAMERA_FIXED_POSITION_START;
				}

				this->bStartFlg = TRUE;
				break;

			
			}
		}

		// ��{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
		{
			switch (iUICount)
			{
				//�^�C�g�����
			case CAMERA_FIXED_POSITION_START:
				iUICount = 0;

				this->bStartFlg = TRUE;
				break;
				//�͂��߂���z�[�����
			case CAMERA_FIXED_POSITION_A:
				if(this->bHomeFlg == FALSE)
				{
					//�͂��߂�����
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				else
				{
					// UI�J�E���g������
					iUICount--;

					// UI�J�E���g���͂��߂����菬�������m�F
					if (iUICount < CAMERA_FIXED_POSITION_A)
					{
						//�J�����Œ�ʒu��ݒ�z�[����ʂɐݒ�
						iUICount = CAMERA_FIXED_POSITION_D;
					}
				}
				this->bStartFlg = TRUE;
				break;
				//�Â�����z�[�����
			case CAMERA_FIXED_POSITION_B:
				if(this->bHomeFlg == FALSE)
				{
					//�Â�������
					iUICount = CAMERA_FIXED_POSITION_B;
				}
				else
				{
					// UI�J�E���g������
					iUICount--;
					// UI�J�E���g���͂��߂����菬�������m�F
					if (iUICount < CAMERA_FIXED_POSITION_A)
					{
						//�J�����Œ�ʒu��ݒ�z�[����ʂɐݒ�
						iUICount = CAMERA_FIXED_POSITION_D;
					}
				}

				this->bStartFlg = TRUE;
				break;
				//�f�[�^�z�[�����
			case CAMERA_FIXED_POSITION_C:
				//�ݒ�z�[�����
			case CAMERA_FIXED_POSITION_D:
				// UI�J�E���g������
				iUICount--;

				// UI�J�E���g���͂��߂����菬�������m�F
				if (iUICount < CAMERA_FIXED_POSITION_A)
				{
					//�J�����Œ�ʒu��ݒ�z�[����ʂɐݒ�
					iUICount = CAMERA_FIXED_POSITION_D;
				}
				this->bStartFlg = TRUE;
				break;
			}
		}

		// ���{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
		{
			switch (iUICount)
			{
				//�^�C�g�����
			case CAMERA_FIXED_POSITION_START:
				iUICount = 0;

				this->bStartFlg = TRUE;
				break;
				//�͂��߂���z�[�����
			case CAMERA_FIXED_POSITION_A:
				if(this->bHomeFlg == FALSE)
				{
					//�͂��߂�����
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				else
				{
					// UI�J�E���g�𑝉�
					iUICount++;
					// UI�J�E���g���m�F��ʂ��傫�����m�F
					if (iUICount >= CAMERA_FIXED_POSITION_E)
					{
						//�J�����Œ�ʒu���͂��߂���ɐݒ�
						iUICount = CAMERA_FIXED_POSITION_A;
					}
				}
				this->bStartFlg = TRUE;
				break;
				//�Â�����z�[�����
			case CAMERA_FIXED_POSITION_B:
				if(this->bHomeFlg == FALSE)
				{
					//�Â�������
					iUICount = CAMERA_FIXED_POSITION_B;
				}
				else
				{
					// UI�J�E���g�𑝉�
					iUICount++;
					// UI�J�E���g���m�F��ʂ��傫�����m�F
					if (iUICount >= CAMERA_FIXED_POSITION_E)
					{
						//�J�����Œ�ʒu���͂��߂���ɐݒ�
						iUICount = CAMERA_FIXED_POSITION_A;
					}
				}
				this->bStartFlg = TRUE;
				break;
				//�f�[�^�z�[�����
			case CAMERA_FIXED_POSITION_C:
				//�ݒ�z�[�����
			case CAMERA_FIXED_POSITION_D:
				// UI�J�E���g�𑝉�
				iUICount++;

				// UI�J�E���g���m�F��ʂ��傫�����m�F
				if (iUICount >= CAMERA_FIXED_POSITION_E)
				{
					// �J�����Œ�ʒu���͂��߂���ɐݒ�
					iUICount = CAMERA_FIXED_POSITION_A;
				}
				this->bStartFlg = TRUE;
				break;
			}
		}

		// ���{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
		{
			// ���{�^���������ꂽ�ꍇ			
			//�J�����̈ʒu���ŏI�m�F��ʂ��m�F
			if (iUICount == CAMERA_FIXED_POSITION_E)
			{
				//�ŏI�m�F��ʂ̏ꍇ
				// �u�͂��v��I��
				this->bGameStartFlg = TRUE;
			}
			this->bStartFlg = TRUE;
		}

		// �E�{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
		{
			if (iUICount == CAMERA_FIXED_POSITION_E)
			{
				// �u�������v��I��
				this->bGameStartFlg = FALSE;
			}
			this->bStartFlg = TRUE;
		}

      
	}
	else if (gpSceneServer->GetScene("Stage"))
	{
		////�X�^�[�g�t���O��L�������m�F
		//if (this->bStartFlg == TRUE)
		//{
		//	//�X�^�[�g�t���O���L���ȏꍇ
		//	//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
		//	SeekMovieToGraph(this->iTextureTitleHandle, 0);
		//}

		//���f���̃e�N�X�`�����^�C�g���e�N�X�`���ɐݒ�
		MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureTitleHandle, true);

		//�^�C�g���f���̍Đ�
		PlayMovieToGraph(this->iTextureTitleHandle);

		//�^�C�g���f���̕`��
		DrawGraph(100, -100, this->iTextureTitleHandle, TRUE);

		//�^�C�g���f���̍Đ����I�����Ă��邩�m�F
		if (GetMovieStateToGraph(this->iTextureTitleHandle) == FALSE)
        {
			//�^�C�g���f���̍Đ����I�����Ă���ꍇ
			//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
			SeekMovieToGraph(this->iTextureTitleHandle, 0);
		}

		//�X�^�[�g�t���O�𖳌���
		//this->bStartFlg = false;
		}
	}
}

// �`��
void Screen::Draw()
{
	//UI�J�E���g�ɂ���ď����𕪊�
	switch (iUICount)
    {
		// �J�����Œ�ʒu���^�C�g�����m�F
        case CAMERA_FIXED_POSITION_START:

			//�X�^�[�g�t���O��L�������m�F
            if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
                SeekMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
            }

			//���f���̃e�N�X�`�����^�C�g���e�N�X�`���ɐݒ�
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureTitleHandle, true);

			/* �`��u�����h���[�h�����Z�ɂ��� */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//�^�C�g���f���̍Đ�
            PlayMovieToGraph(this->iTextureTitleHandle);

			//�^�C�g���f���̕`��
            DrawGraph(100, -100, this->iTextureTitleHandle, TRUE);

			//�^�C�g���f���̍Đ����I�����Ă��邩�m�F
            if (GetMovieStateToGraph(this->iTextureTitleHandle) == FALSE)
            {
				//�^�C�g���f���̍Đ����I�����Ă���ꍇ
				//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
                SeekMovieToGraph(this->iTextureTitleHandle, 0);
            }
			/* �`��u�����h���[�h���u�����h�����ɖ߂� */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//�X�^�[�g�t���O�𖳌���
            this->bStartFlg = false;
            break;

			// �͂��߂��炩�m�F
        case CAMERA_FIXED_POSITION_A:
			//�X�^�[�g�t���O���L�����m�F
            if (this->bStartFlg == TRUE)
            {
				//�X�^�[�g�t���O���L���ȏꍇ
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
                SeekMovieToGraph(this->iTextureNewgameHandle, 0);
            }

			//���f���̃e�N�X�`�����j���[�Q�[���e�N�X�`���ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureNewgameHandle, false);

			/* �`��u�����h���[�h�����Z�ɂ��� */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//�j���[�Q�[���f���̍Đ�
            PlayMovieToGraph(this->iTextureNewgameHandle);

			//�j���[�Q�[���f���̍Đ����I�����Ă��邩�m�F
            if (GetMovieStateToGraph(this->iTextureNewgameHandle) == FALSE)
            {
				//�j���[�Q�[���f���̍Đ����I�����Ă���ꍇ
				//�j���[�Q�[���f���̍Đ��ʒu��0�ɐݒ�
                SeekMovieToGraph(this->iTextureNewgameHandle, 0);
            }
			/* �`��u�����h���[�h���u�����h�����ɖ߂� */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			/* �`��u�����h���[�h���u�����h�����ɖ߂� */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//�X�^�[�g�t���O�𖳌���
            this->bStartFlg = false;
            break;

			// �Â����炩�m�F
        case CAMERA_FIXED_POSITION_B:
			//�X�^�[�g�t���O���L�����m�F
            if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
                SeekMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//���f���̃e�N�X�`�����R���e�B�j���[�e�N�X�`���ɐݒ�
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureContinueHandle, true);



			//�X�^�[�g�t���O�𖳌���
            this->bStartFlg = false;
            break;

			// �f�[�^���m�F
        case CAMERA_FIXED_POSITION_C:
			//�X�^�[�g�t���O���L�����m�F
            if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
                SeekMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//���f���̃e�N�X�`�����f�[�^�e�N�X�`���ɐݒ�
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureDateHandle, true);

			/* �`��u�����h���[�h�����Z�ɂ��� */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//�f�[�^�f���̍Đ�
            PlayMovieToGraph(this->iTextureDateHandle);

			//�f�[�^�f���̍Đ����I�����Ă��邩�m�F
            if (GetMovieStateToGraph(this->iTextureDateHandle) == FALSE)
            {
				//�f�[�^�f���̍Đ����I�����Ă���ꍇ
				//�f�[�^�f���̍Đ��ʒu��0�ɐݒ�
                SeekMovieToGraph(this->iTextureDateHandle, 0);
			}
			/* �`��u�����h���[�h���u�����h�����ɖ߂� */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//�X�^�[�g�t���O�𖳌���
            this->bStartFlg = false;
            break;

			// �ݒ肩�m�F
        case CAMERA_FIXED_POSITION_D:

			//�X�^�[�g�t���O���L�����m�F
            if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
                SeekMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
            }

			//���f���̃e�N�X�`�����R���t�B�O�e�N�X�`���ɐݒ�
            MV1SetTextureGraphHandle(iModelHandle, 1, this->iTextureConfigHandle, true);

			/* �`��u�����h���[�h�����Z�ɂ��� */
			SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

			//�R���t�B�O�f���̍Đ�
			PauseMovieToGraph(this->iTextureConfigHandle);

			//�R���t�B�O�f���̍Đ����I�����Ă��邩�m�F
            if (GetMovieStateToGraph(this->iTextureConfigHandle) == FALSE)
            {
				//�R���t�B�O�f���̍Đ����I�����Ă���ꍇ
				//�R���t�B�O�f���̍Đ��ʒu��0�ɐݒ�
                SeekMovieToGraph(this->iTextureConfigHandle, 0);
			}
			/* �`��u�����h���[�h���u�����h�����ɖ߂� */
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

			//�X�^�[�g�t���O�𖳌���
            this->bStartFlg = false;
            break;
	}
	// ���f���̕`��
	MV1DrawModel(iModelHandle);

	/* �`��u�����h���[�h�����Z�ɂ��� */
	SetDrawBlendMode(DX_BLENDMODE_SUB, 0);

	//�R���e�B�j���[�f���̍Đ�
	PlayMovieToGraph(this->iTextureContinueHandle);

	//�R���e�B�j���[�f���̍Đ����I�����Ă��邩�m�F
	if (GetMovieStateToGraph(this->iTextureContinueHandle) == FALSE)
    {
		//�R���e�B�j���[�f���̍Đ����I�����Ă���ꍇ
		//�R���e�B�j���[�f���̍Đ��ʒu��0�ɐݒ�
		SeekMovieToGraph(this->iTextureContinueHandle, 0);
	}
	/* �`��u�����h���[�h���u�����h�����ɖ߂� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}


// �X�V
void Screen::Update()
{
	//����
	Process();

	//�`��
	Draw();

}
