/* 2025.02.28 �ΐ�q�� �t�@�C���쐬 */
#include "Scene_Title_Player.h"

// �R���X�g���N�^
TitlePlayer::TitlePlayer() : PlatformBase()
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
		this->iModelHandle = ModelListHandle->iGetModel("Player/Player");
	}

}

// �f�X�g���N�^
TitlePlayer::~TitlePlayer()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

//����
void TitlePlayer::Process()
{

}


// �X�V
void TitlePlayer::Update()
{
	//����
	Process();
}
