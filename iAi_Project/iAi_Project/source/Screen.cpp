/* 2025.02.28 �ΐ�q�� �t�@�C���쐬 */
#include "Screen.h"

// �R���X�g���N�^
Screen::Screen() : PlatformBasic()
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
		this->textureTitleHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");			//�^�C�g��
		this->textureNewgameHandle = *ImageList->piGetImage_Movie("Test/Newgame");			//�j���[�Q�[��
		this->textureContinueHandle = *ImageList->piGetImage_Movie("Test/Continue");		//�R���e�B�j���[
		this->textureDateHandle = *ImageList->piGetImage_Movie("Test/Date");				//�f�[�^
		this->textureConfigHandle = *ImageList->piGetImage_Movie("Test/Config");			//�R���t�B�O
		this->textureStageHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");			//�X�e�[�W
	}

	/* UI�J�E���g�������� */
	this->UICount = 0;

	//����Đ��t���O��������
	this->StartFlg = false;
	this->bHomeFlg = false;

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
	//���݂̃V�[�����^�C�g���V�[�����m�F
	if (gpSceneServer->GetScene("Title"))
	{
		//�^�C�g���V�[���̏ꍇ
		//�J�����Œ�ʒu�������ʒu���m�F
		if (UICount > 0)
		{
			//����{�^���������ꂽ���m�F
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				//����{�^���������ꂽ�ꍇ
				this->bHomeFlg = FALSE;
			}
		}
		if (UICount == 0)
		{
			//�����ʒu�̏ꍇ
			//����{�^���������ꂽ���m�F
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DECID))
			{
				//����{�^���������ꂽ�ꍇ
				this->bHomeFlg = TRUE;
				//UI�J�E���g�𑝂₷
				UICount = 1;
			}
		}
		//�����ʒu�ȊO���m�F
		if ((5 > UICount) || (UICount > 0))
		{
			//�����ʒu�ȊO�̏ꍇ
			//��{�^���������ꂽ���m�F
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_UP))
			{
				//��{�^���������ꂽ�ꍇ
				//����Đ��t���O��L����
				this->StartFlg = TRUE;
				this->bHomeFlg = TRUE;
				//UI�J�E���g�𑝂₷
				UICount++;
				//UI�J�E���g���|�W�V����E�ȏォ�m�F
				if (UICount >= CAMERA_FIXED_POSITION_E)
				{
					//UI�J�E���g���|�W�V����E�ȏ�̏ꍇ
					//UI�J�E���g���|�W�V����A�ɐݒ�
					UICount = 1;
				}
			}

			//���{�^���������ꂽ���m�F
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_DOWN))
			{
				//���{�^���������ꂽ�ꍇ
				//����Đ��t���O��L����
				this->StartFlg = TRUE;
				this->bHomeFlg = TRUE;
				//UI�J�E���g�����炷
				UICount--;
				//UI�J�E���g���|�W�V����A�������m�F
				if (UICount < 1)
				{
					//UI�J�E���g���|�W�V����A�����̏ꍇ
					//UI�J�E���g���|�W�V����D�ɐݒ�
					UICount = CAMERA_FIXED_POSITION_D;

				}
			}
			//�L�����Z���{�^���������ꂽ���m�F
			if (gpDataList_Input->bGetInterfaceInput(INPUT_REL, UI_CANCEL))
{
				//�L�����Z���{�^���������ꂽ�ꍇ
				if (this->bHomeFlg ==TRUE)
				{
					//UI�J�E���g��������
					UICount = 0;
					this->StartFlg = TRUE;
				}
				if(this->bHomeFlg == FALSE)
				{
					//UI�J�E���g���|�W�V����A�ɐݒ�
					UICount = 1;

				}

				this->bHomeFlg = TRUE;
			}
		}
		//�J�����Œ�ʒu�������ʒu���m�F
		if (UICount == 0)
		{
			//�����ʒu�̏ꍇ
			//����Đ��t���O���L�����m�F
			if (this->StartFlg == TRUE)
			{
				//����Đ��t���O���L���̏ꍇ
				//���[�r�[�̍Đ����Ԃ�����������
				SeekMovieToGraph(this->textureTitleHandle, 0);
			}
			//���f���̃e�N�X�`����TitleHandle�ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureTitleHandle, true);
	/* �^�C�g�����S���Đ� */
	PlayMovieToGraph(this->textureTitleHandle);

	/* ���[�r�[��`�� */
	DrawGraph(100, -100, this->textureTitleHandle, TRUE);

	/* �Đ����I�����Ă��邩�m�F */
	if (GetMovieStateToGraph(this->textureTitleHandle) == FALSE)
	{
		// �Đ����I�����Ă���ꍇ
		/* ���[�r�[�̍Đ����Ԃ����������� */
		SeekMovieToGraph(this->textureTitleHandle, 0);
	}
			//����Đ��t���O�𖳌���
			this->StartFlg = false;
		}
		//�J�����Œ�ʒu���|�W�V����A���m�F
		if (UICount == 1)
		{
			//�|�W�V����A�̏ꍇ
			//����Đ��t���O���L�����m�F
			if (this->StartFlg == TRUE)
			{
				//����Đ��t���O���L���̏ꍇ
				//���[�r�[�̍Đ����Ԃ�����������
				SeekMovieToGraph(this->textureNewgameHandle, 0);
			}
			//���f���̃e�N�X�`����NewgameHandle�ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureNewgameHandle, true);
			/* �^�C�g�����S���Đ� */
			PlayMovieToGraph(this->textureNewgameHandle);
			/* ���[�r�[��`�� */
			DrawGraph(100, -100, this->textureNewgameHandle, TRUE);
			/* �Đ����I�����Ă��邩�m�F */
			if (GetMovieStateToGraph(this->textureNewgameHandle) == FALSE)
			{
				// �Đ����I�����Ă���ꍇ
				/* ���[�r�[�̍Đ����Ԃ����������� */
				SeekMovieToGraph(this->textureNewgameHandle, 0);
			}
			//����Đ��t���O�𖳌���
			this->StartFlg = false;
		}
		//�J�����Œ�ʒu���|�W�V����B���m�F
		if (UICount == 2)
		{
			//�|�W�V����B�̏ꍇ
			//����Đ��t���O���L�����m�F
			if (this->StartFlg == TRUE)
			{
				//����Đ��t���O���L���̏ꍇ
				//���[�r�[�̍Đ����Ԃ�����������
				SeekMovieToGraph(this->textureContinueHandle, 0);
			}
			//���f���̃e�N�X�`����ContinueHandle�ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureContinueHandle, true);
			/* �^�C�g�����S���Đ� */
			PlayMovieToGraph(this->textureContinueHandle);
			/* ���[�r�[��`�� */
			DrawGraph(100, -100, this->textureContinueHandle, TRUE);
			/* �Đ����I�����Ă��邩�m�F */
			if (GetMovieStateToGraph(this->textureContinueHandle) == FALSE)
			{
				// �Đ����I�����Ă���ꍇ
				/* ���[�r�[�̍Đ����Ԃ����������� */
				SeekMovieToGraph(this->textureContinueHandle, 0);
			}
			//����Đ��t���O�𖳌���
			this->StartFlg = false;
		}
		//�J�����Œ�ʒu���|�W�V����C���m�F
		if (UICount == 3)
		{
			//�|�W�V����C�̏ꍇ
			//����Đ��t���O���L�����m�F
			if (this->StartFlg == TRUE)
			{
				//����Đ��t���O���L���̏ꍇ
				//���[�r�[�̍Đ����Ԃ�����������
				SeekMovieToGraph(this->textureDateHandle, 0);
			}
			//���f���̃e�N�X�`����DateHandle�ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureDateHandle, true);
			/* �^�C�g�����S���Đ� */
			PlayMovieToGraph(this->textureDateHandle);
			/* ���[�r�[��`�� */
			DrawGraph(100, -100, this->textureDateHandle, TRUE);
			/* �Đ����I�����Ă��邩�m�F */
			if (GetMovieStateToGraph(this->textureDateHandle) == FALSE)
			{
				// �Đ����I�����Ă���ꍇ
				/* ���[�r�[�̍Đ����Ԃ����������� */
				SeekMovieToGraph(this->textureDateHandle, 0);
			}
			//����Đ��t���O�𖳌���
			this->StartFlg = false;
		}
		//�J�����Œ�ʒu���|�W�V����D���m�F
		if (UICount == 4)
		{
			//�|�W�V����D�̏ꍇ
			//����Đ��t���O���L�����m�F
			if (this->StartFlg == TRUE)
			{
				//����Đ��t���O���L���̏ꍇ
				//���[�r�[�̍Đ����Ԃ�����������
				SeekMovieToGraph(this->textureConfigHandle, 0);
			}
			//���f���̃e�N�X�`����ConfigHandle�ɐݒ�
			MV1SetTextureGraphHandle(iModelHandle, 1, this->textureConfigHandle, true);
			/* �^�C�g�����S���Đ� */
			PlayMovieToGraph(this->textureConfigHandle);
			/* ���[�r�[��`�� */
			DrawGraph(100, -100, this->textureConfigHandle, TRUE);
			/* �Đ����I�����Ă��邩�m�F */
			if (GetMovieStateToGraph(this->textureConfigHandle) == FALSE)
			{
				// �Đ����I�����Ă���ꍇ
				/* ���[�r�[�̍Đ����Ԃ����������� */
				SeekMovieToGraph(this->textureConfigHandle, 0);
			}
			//����Đ��t���O�𖳌���
			this->StartFlg = false;
		}
	}
	//���݂̃V�[�����X�e�[�W�V�[���ȊO���m�F
	else if (gpSceneServer->GetScene("Stage"))
	{
		//�X�e�[�W�V�[���ȊO�̏ꍇ
		//���f���̃e�N�X�`����StageHandle�ɐݒ�
		MV1SetTextureGraphHandle(iModelHandle, 1, this->textureStageHandle, true);
		/* �^�C�g�����S���Đ� */
		PlayMovieToGraph(this->textureStageHandle);
		/* ���[�r�[��`�� */
		DrawGraph(100, -100, this->textureStageHandle, TRUE);
		/* �Đ����I�����Ă��邩�m�F */
		if (GetMovieStateToGraph(this->textureStageHandle) == FALSE)
		{
			// �Đ����I�����Ă���ꍇ
			/* ���[�r�[�̍Đ����Ԃ����������� */
			SeekMovieToGraph(this->textureStageHandle, 1);
		}
	}
}


// �X�V
void Screen::Update()
{
	//����
	Process();
}
