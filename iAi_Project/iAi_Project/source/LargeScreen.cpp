/* 2025.02.28 �ΐ�q�� �t�@�C���쐬 */
#include "LargeScreen.h"

// �R���X�g���N�^
LargeScreen::LargeScreen() : PlatformBase()
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
		this->iModelHandle = ModelListHandle->iGetModel("Object/LargeScreen/LargeScreen");
	}

	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �X�N���[���ɉf��f�� */
		this->iTextureTitleHandle = *ImageList->piGetImage_Movie("Home/TitleLogo");			//�^�C�g��
		this->iTextureNewgameHandle = *ImageList->piGetImage_Movie("Home/Newgame");			//�j���[�Q�[��
		this->iTextureContinueHandle = *ImageList->piGetImage_Movie("Home/Continue");		//�R���e�B�j���[
		this->iTextureDateHandle = *ImageList->piGetImage_Movie("Home/Config");				//�f�[�^
		this->iTextureConfigHandle = *ImageList->piGetImage("Home/GameEnd");			//�R���t�B�O
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
			if (strncmp(cFrameName, "Large", 5) == 0)
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
LargeScreen::~LargeScreen()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

//����
void LargeScreen::Process()
{
	// ���݂̃V�[�����^�C�g���V�[�����m�F
	{
		// ����{�^���������ꂽ���m�F
		if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
		{
			switch (iUICount)
			{
				//�^�C�g�����
			case CAMERA_FIXED_POSITION_START:
				// �����{�^���������ꂽ�ꍇ
				// Home�t���O��L����
				this->bHomeFlg = TRUE;

				this->bStartFlg = TRUE;

				//UI�J�E���g���|�W�V����A�ɕύX
				iUICount = CAMERA_FIXED_POSITION_A;
				break;
				//�͂��߂���z�[�����
			case CAMERA_FIXED_POSITION_A:
				//�Â�����z�[�����
			case CAMERA_FIXED_POSITION_B:
				//�Q�[���X�^�[�g�t���O�𖳌���
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
				//�f�[�^�z�[�����
			case CAMERA_FIXED_POSITION_C:
				//�ݒ�z�[�����
			case CAMERA_FIXED_POSITION_D:

				//�z�[���t���O��L�������m�F
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
				//�Â�����z�[�����
			case CAMERA_FIXED_POSITION_B:
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
				//�Â�����z�[�����
			case CAMERA_FIXED_POSITION_B:
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

		//UI�J�E���g�ɂ���ď����𕪊�
		switch (iUICount)
		{
			// �J�����Œ�ʒu�������ʒu���m�F
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
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureTitleHandle, true);


			//�^�C�g���f���̍Đ����I�����Ă��邩�m�F
			if (GetMovieStateToGraph(this->iTextureTitleHandle) == FALSE)
			{
				//�^�C�g���f���̍Đ����I�����Ă���ꍇ
				//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
				SeekMovieToGraph(this->iTextureTitleHandle, 0);
			}

			//�X�^�[�g�t���O�𖳌���
			this->bStartFlg = false;
			break;

			// �|�W�V����A���m�F
		case CAMERA_FIXED_POSITION_A:
			//�X�^�[�g�t���O��L�������m�F
			if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				SeekMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//���f���̃e�N�X�`�����j���[�Q�[���e�N�X�`���ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureNewgameHandle, true);


			//�j���[�Q�[���f���̍Đ����I�����Ă��邩�m�F
			if (GetMovieStateToGraph(this->iTextureNewgameHandle) == FALSE)
			{
				//�j���[�Q�[���f���̍Đ����I�����Ă���ꍇ
				//�j���[�Q�[���f���̍Đ��ʒu��0�ɐݒ�
				SeekMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//�X�^�[�g�t���O�𖳌���
			this->bStartFlg = false;
			break;

			// �|�W�V����B���m�F
		case CAMERA_FIXED_POSITION_B:
			//�X�^�[�g�t���O��L�������m�F
			if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				SeekMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//���f���̃e�N�X�`�����R���e�B�j���[�e�N�X�`���ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureContinueHandle, true);


			//�R���e�B�j���[�f���̍Đ����I�����Ă��邩�m�F
			if (GetMovieStateToGraph(this->iTextureContinueHandle) == FALSE)
			{
				//�R���e�B�j���[�f���̍Đ����I�����Ă���ꍇ
				//�R���e�B�j���[�f���̍Đ��ʒu��0�ɐݒ�
				SeekMovieToGraph(this->iTextureContinueHandle, 0);
			}

			//�X�^�[�g�t���O�𖳌���
			this->bStartFlg = false;
			break;

			// �|�W�V����C���m�F
		case CAMERA_FIXED_POSITION_C:
			//�X�^�[�g�t���O��L�������m�F
			if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				PauseMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				SeekMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//���f���̃e�N�X�`�����f�[�^�e�N�X�`���ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureDateHandle, true);

			//�f�[�^�f���̍Đ����I�����Ă��邩�m�F
			if (GetMovieStateToGraph(this->iTextureDateHandle) == FALSE)
			{
				//�f�[�^�f���̍Đ����I�����Ă���ꍇ
				//�f�[�^�f���̍Đ��ʒu��0�ɐݒ�
				SeekMovieToGraph(this->iTextureDateHandle, 0);
			}

			//�X�^�[�g�t���O�𖳌���
			this->bStartFlg = false;
			break;

			// �|�W�V����D���m�F
		case CAMERA_FIXED_POSITION_D:
			//�X�^�[�g�t���O��L�������m�F
			if (this->bStartFlg == TRUE)
			{
				//�X�^�[�g�t���O���L���ȏꍇ
				//�^�C�g���f���̍Đ��ʒu��0�ɐݒ�
				PauseMovieToGraph(this->iTextureTitleHandle, 0);
				SeekMovieToGraph(this->iTextureConfigHandle, 0);
				PauseMovieToGraph(this->iTextureContinueHandle, 0);
				PauseMovieToGraph(this->iTextureDateHandle, 0);
				PauseMovieToGraph(this->iTextureNewgameHandle, 0);
			}

			//���f���̃e�N�X�`�����R���t�B�O�e�N�X�`���ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 0, this->iTextureConfigHandle, true);


			//�R���t�B�O�f���̍Đ����I�����Ă��邩�m�F
			if (GetMovieStateToGraph(this->iTextureConfigHandle) == FALSE)
			{
				//�R���t�B�O�f���̍Đ����I�����Ă���ꍇ
				//�R���t�B�O�f���̍Đ��ʒu��0�ɐݒ�
				SeekMovieToGraph(this->iTextureConfigHandle, 0);
			}

			//�X�^�[�g�t���O�𖳌���
			this->bStartFlg = false;
			break;
		}
	}
}



// �X�V
void LargeScreen::Update()
{
	//����
	Process();
}
