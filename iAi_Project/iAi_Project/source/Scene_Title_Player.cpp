/* 2025.02.28 �ΐ�q�� �t�@�C���쐬 */
#include "SceneTitle.h" 
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

	/* �J�n�����[�V�����ݒ� */
	{
		//���f���ɒ��n���[�V�������A�^�b�`����
		this->iTitlePlayerWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 10, -1, FALSE);

		// �Đ����Ԃ�����������
		this->fTitlePlayerWaitTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iTitlePlayerWaitAttachIndex);

		// 6�J�E���g���J�b�g������ԂŃA�^�b�`
		this->fTitlePlayerWaitNowTime = 6.0f;

		// �A�^�b�`�������[�V�����̊J�n���Ԃ�ݒ�
		MV1SetAttachAnimTime(this->iModelHandle, this->iTitlePlayerWaitAttachIndex, this->fTitlePlayerWaitNowTime);

		///* ������~�t���O��L���� */
		this->bBloomStopFlg = true;
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

	//�A�N�e�B�u�t���O���L�����m�F
	if (g_bActiveFlg == true)
	{
		//�A�N�e�B�u�t���O���L���̏ꍇ
		//�A�j���[�V�����X�V
		// �A�^�b�`�����ҋ@���[�V�������Đ�����
		MV1SetAttachAnimTime(this->iModelHandle, this->iTitlePlayerWaitAttachIndex, this->fTitlePlayerWaitNowTime);

		//�ҋ@���[�V�����̍Đ����Ԃ����Z
		this->fTitlePlayerWaitNowTime += 0.1f;

	}
}