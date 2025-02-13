/* 2025.02.10 �ΐ�q�� �t�@�C���쐬 */
#include "GimmickJump.h"

// �R���X�g���N�^
GimmickJump::GimmickJump() : PlatformBasic()
{
	/* �f�[�^���X�g */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}
	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/cube");
	}

	//�v���C���[�̏����擾
	this->pPlayer = ObjectList->GetCharacterPlayer();

	//�M�~�b�N�̏��Ŏ���
	this->iDisappearTime = GIMMICK_DISAPPEAR_TIME;

	//�M�~�b�N�e�N�X�`���ύX�J�E���g
	this->iTextureChangeCount = GIMMICK_TEXTURE_CHANGE_FIRST_COUNT;
}

// �f�X�g���N�^
GimmickJump::~GimmickJump()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

//�M�~�b�N�̏���
void GimmickJump::ProcessGimmick()
{
	//�v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�v���C���[���M�~�b�N�̏�ɏ���Ă��邩�m�F
	if (playerPos.x > this->vecPosition.x - 50 && playerPos.x < this->vecPosition.x + 50 &&
		playerPos.y > this->vecPosition.y - 50 && playerPos.y < this->vecPosition.y + 50 &&
		playerPos.z > this->vecPosition.z - 50 && playerPos.z < this->vecPosition.z + 50)
	{
		//�v���C���[���M�~�b�N�̏�ɏ���Ă���ꍇ

		//�v���C���[�𐁂���΂�
		this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

		//�v���C���[�̃W�����v�񐔂�1�ɐݒ�
		this->PlayerStatusList->SetPlayerNowJumpCount(1);
	}
}

// �X�V
void GimmickJump::Update()
{
	//�M�~�b�N�̏���
	ProcessGimmick();
}
