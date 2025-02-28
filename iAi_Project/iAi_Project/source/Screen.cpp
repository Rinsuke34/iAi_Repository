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
        this->textureTitleHandle = *ImageList->piGetImage_Movie("Test/TitleLogo");
	}
	/*this->SetModelHandle(this->iModelHandle);
	MV1SetTextureGraphHandle(this->iModelHandle, 0, textureTitleHandle, true);*/

}

// �f�X�g���N�^
Screen::~Screen()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}


void Screen::Initialization()
{
    
}

// �X�N���[���`��
void Screen::ScreenDraw()
{
	/* �`��u�����h���[�h�����Z�ɂ��� */
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	/* �^�C�g�����S��`�� */
	PlayMovieToGraph(this->textureTitleHandle);

	/* ���[�r�[�f������ʂ����ς��ɕ`�悵�܂� */
	DrawGraph(100, -100, this->textureTitleHandle, TRUE);

	/* �Đ����I�����Ă��邩 */
	if (GetMovieStateToGraph(this->textureTitleHandle) == FALSE)
	{
		// �Đ����I�����Ă���ꍇ
		/* ���[�r�[�̍Đ����Ԃ����������� */
		SeekMovieToGraph(this->textureTitleHandle, 0);
	}

	/* �`��u�����h���[�h���u�����h�����ɖ߂� */
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	/* �`�惂�[�h���A���X�g�ɖ߂� */
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

// �X�V
void Screen::Update()
{
	//ScreenDraw();
}
