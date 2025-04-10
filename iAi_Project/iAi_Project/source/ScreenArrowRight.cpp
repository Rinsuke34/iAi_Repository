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
		this->iModelHandle = ModelListHandle->iGetModel("Object/SignBoard/SignBoard");
	}

	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �X�N���[���ɉf��f�� */
		// �E���1
		this->iTextureArrowRightHandle1 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_1");

		// �E���2
		this->iTextureArrowRightHandle2 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_2");

		// �E���3
		this->iTextureArrowRightHandle3 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_3");

		// �E���4
		this->iTextureArrowRightHandle4 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_4");

		// �E���5
		this->iTextureArrowRightHandle5 = *ImageList->piGetImage("SignBoardArrow/Signboard_Arrow_Right_5");

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

	//������
	//���̃J�E���g1
	this->iFirstCount = 0;

	//���̃J�E���g2
	this->iSecondCount = 0;

	//���̃J�E���g3
	this->iThirdCount = 0;

	//���̃J�E���g4
	this->iFourthCount = 0;

	//���̃J�E���g5
	this->iFifthCount = 0;

	//���t���O1
	this->bArrowFlg = false;

	//���t���O2
	this->bArrowFlg2 = false;

	//���t���O3
	this->bArrowFlg3 = false;

	//���t���O4
	this->bArrowFlg4 = false;

	//���t���O5
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
	//UI�J�E���g��0���m�F
	if (this->iUICount == 0)
	{
		//UI�J�E���g��0�̏ꍇ
		//���J�E���g1��20�ȏォ�m�F
		if (++iFirstCount >= 20)
		{
			//���J�E���g1��20�ȏ�̏ꍇ
			//UI�J�E���g��1�ɕύX
			iUICount = 1;

			//���J�E���g1��������
			iFirstCount = 0;
		}
	}

	//UI�J�E���g��1���m�F
	else if (this->iUICount == 1)
	{
		//UI�J�E���g��1�̏ꍇ
		//���J�E���g2��20�ȏォ�m�F
		if (++iSecondCount >= 20)
		{
			//���J�E���g2��20�ȏ�̏ꍇ
			//UI�J�E���g��2�ɕύX
			iUICount = 2;

			//���J�E���g2��������
			iSecondCount = 0;
		}
	}

	//UI�J�E���g��2���m�F
	else if (this->iUICount == 2)
	{
		//UI�J�E���g��2�̏ꍇ
		//���J�E���g3��20�ȏォ�m�F
		if (++iThirdCount >= 20)
		{
			//���J�E���g3��20�ȏ�̏ꍇ
			//UI�J�E���g��3�ɕύX
			iUICount = 3;

			//���J�E���g3��������
			iThirdCount = 0;
		}
	}

	//UI�J�E���g��3���m�F
	else if (this->iUICount == 3)
	{
		//UI�J�E���g��3�̏ꍇ
		//���J�E���g4��20�ȏォ�m�F
		if (++iFourthCount >= 20)
		{
			//���J�E���g4��20�ȏ�̏ꍇ
			//UI�J�E���g��4�ɕύX
			iUICount = 4;

			//���J�E���g4��������
			iFourthCount = 0;
		}
	}

	//UI�J�E���g��4���m�F
	else if (this->iUICount == 4)
	{
		//UI�J�E���g��4�̏ꍇ
		//���J�E���g5��20�ȏォ�m�F
		if (++iFifthCount >= 20)
		{
			//���J�E���g5��20�ȏ�̏ꍇ
			//UI�J�E���g��0�ɕύX
			iUICount = 0;

			//���J�E���g5��������
			iFifthCount = 0;
		}
	}
}


// �`��
void ScreenArrowRight::Draw()
{

	// ���݂̃e�N�X�`���n���h��
	int currentTextureHandle = -1;

	// ���ɐݒ肷��e�N�X�`���n���h��
	int newTextureHandle = -1;

	// UI�J�E���g�ɂ���ď����𕪊�
	switch (iUICount)
	{
		// UI�J�E���g��0�̏ꍇ
	case 0:

		// ���̃e�N�X�`���n���h��1��ݒ�
		newTextureHandle = this->iTextureArrowRightHandle1;

		break;

		// UI�J�E���g��1�̏ꍇ
	case 1:

		// ���̃e�N�X�`���n���h��2��ݒ�
		newTextureHandle = this->iTextureArrowRightHandle2;

		break;

		// UI�J�E���g��2�̏ꍇ
	case 2:

		// ���̃e�N�X�`���n���h��3��ݒ�
		newTextureHandle = this->iTextureArrowRightHandle3;

		break;

		// UI�J�E���g��3�̏ꍇ
	case 3:

		// ���̃e�N�X�`���n���h��4��ݒ�
		newTextureHandle = this->iTextureArrowRightHandle4;

		break;

		// UI�J�E���g��4�̏ꍇ
	case 4:

		// ���̃e�N�X�`���n���h��5��ݒ�
		newTextureHandle = this->iTextureArrowRightHandle5;

		break;
	}

	// �e�N�X�`�����ύX���ꂽ�ꍇ�̂ݐ؂�ւ���
	if (newTextureHandle != currentTextureHandle)
	{
		// ���f���̃e�N�X�`����ݒ�
		MV1SetTextureGraphHandle(iModelHandle, 1, newTextureHandle, true);

		// �e�N�X�`���n���h�����X�V
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
