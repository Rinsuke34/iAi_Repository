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

		/* �^�C�g�����S */
		//this->textureTitleHandle = ImageList->piGetImage_Movie("Object/SignBoard/ScreenTexture");
        this->textureTitleHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");
	}

	// �e�N�X�`���̓ǂݍ���
	MV1SetTextureGraphHandle(iModelHandle, 0, this->textureTitleHandle, true);

	//pScreen->iGetNowCameraFixedPositionNo();


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


// �X�V
void Screen::Update()
{

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

}
