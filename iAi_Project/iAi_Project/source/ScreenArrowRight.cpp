/* 2025.03.26 �ΐ�q�� �t�@�C���쐬 */
#include "ScreenArrowRight.h"

// �R���X�g���N�^
ScreenArrowRight::ScreenArrowRight() : PlatformBase()
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

		this->iTextureArrowRightHandle1 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Left_1");	// �����1
		this->iTextureArrowRightHandle2 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Left_2");	// �����2
		this->iTextureArrowRightHandle3 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Left_3");	// �����3
		this->iTextureArrowRightHandle4 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Left_4");	// �����4
		this->iTextureArrowRightHandle5 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Left_5");	// �����5

	}


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
	this->iFirstCount = 0;
	this->iSecondCount = 0;
	this->iThirdCount = 0;
	this->iFourthCount = 0;
	this->iFifthCount = 0;

	this->bArrowFlg = false;
	this->bArrowFlg2 = false;
	this->bArrowFlg3 = false;
	this->bArrowFlg4 = false;
	this->bArrowFlg5 = false;
}

// �f�X�g���N�^
ScreenArrowRight::~ScreenArrowRight()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

//����
void ScreenArrowRight::Process()
{
	// ���݂̃V�[�����^�C�g���V�[�����m�F
	if (g_bActiveFlg == false)
	{
		// 1�b���Scene��A�ɕύX
		if (this->iUICount == CAMERA_FIXED_POSITION_START)
		{
			if (++iFirstCount >= 60)
			{
				iUICount = CAMERA_FIXED_POSITION_A;
				iFirstCount = 0;
			}
		}

		// 1�b���Scene��B�ɕύX
		else if (this->iUICount == CAMERA_FIXED_POSITION_A)
		{
			if (++iSecondCount >= 60)
			{
				iUICount = CAMERA_FIXED_POSITION_B;
				iSecondCount = 0;
			}
		}

		// 1�b���Scene��C�ɕύX
		else if (this->iUICount == CAMERA_FIXED_POSITION_B)
		{
			if (++iThirdCount >= 60)
			{
				iUICount = CAMERA_FIXED_POSITION_C;
				iThirdCount = 0;
			}
		}

		// 1�b���Scene��D�ɕύX
		else if (this->iUICount == CAMERA_FIXED_POSITION_C)
		{
			if (++iFourthCount >= 60)
			{
				iUICount = CAMERA_FIXED_POSITION_D;
				iFourthCount = 0;
			}
		}

		// 1�b���Scene��E�ɕύX
		else if (this->iUICount == CAMERA_FIXED_POSITION_D)
		{
			if (++iFifthCount >= 60)
			{
				iUICount = CAMERA_FIXED_POSITION_START;
				iFifthCount = 0;
			}
		}
	}
}


// �`��
void ScreenArrowRight::Draw()
{
	static int currentTextureHandle = -1;
	int newTextureHandle = -1;

	// UI�J�E���g�ɂ���ď����𕪊�
	switch (iUICount)
	{
	case CAMERA_FIXED_POSITION_START:
		newTextureHandle = this->iTextureArrowRightHandle1;
		break;

	case CAMERA_FIXED_POSITION_A:
		newTextureHandle = this->iTextureArrowRightHandle2;
		break;

	case CAMERA_FIXED_POSITION_B:
		newTextureHandle = this->iTextureArrowRightHandle3;
		break;

	case CAMERA_FIXED_POSITION_C:
		newTextureHandle = this->iTextureArrowRightHandle4;
		break;

	case CAMERA_FIXED_POSITION_D:
		newTextureHandle = this->iTextureArrowRightHandle5;
		break;
	}

	// �e�N�X�`�����ύX���ꂽ�ꍇ�̂ݐ؂�ւ���
	if (newTextureHandle != currentTextureHandle)
	{
		MV1SetTextureGraphHandle(iModelHandle, 1, newTextureHandle, true);
		currentTextureHandle = newTextureHandle;
	}

	// ���f���̕`��
	MV1DrawModel(iModelHandle);
}


// �X�V
void ScreenArrowRight::Update()
{
	//����
	Process();

	//�`��
	Draw();
}
