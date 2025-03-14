/* 2025.02.14 �e�r�듹 �t�@�C���쐬 */

#include "BulletPlayerKunai.h"

/* �N�i�C�N���X�̒�` */

// �R���X�g���N�^
BulletPlayerKunai::BulletPlayerKunai() : BulletBase()
{
	/* ������ */
	this->iObjectType					= OBJECT_TYPE_BULLET_PLAYER;		// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->vecKunaiTargetPosition		= VGet(0,0,0);						// �^�[�Q�b�g���W
	this->vecKunaiMoveDirection			= VGet(0, 0, 0);					// �N�i�C�̈ړ��������
	this->fKunaiTargetDistance			= 0.0f;								// �N�i�C�̔��˒n�_����^�[�Q�b�g�܂ł̋���
	this->fKunaiMoveDistance			= 0.0f;								// �N�i�C�̈ړ�����
	this->fKunaiAngleX					= 0.0f;								// �N�i�C��X����]�p�x
	this->fKunaiAngleY					= 0.0f;								// �N�i�C��Y����]�p�x
	this->iKunaiDeleteCount				= KUNAI_ATTACK_COUNT;				// �N�i�C�̍폜�J�E���g(�U������)
	this->bKunaiAttackFlg				= false;							// �N�i�C�̍U���t���O

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Bullet/Kunai/Kunai");
	}

	/* �f�[�^���X�g�擾 */
	{
		/* "���͊Ǘ�"���擾 */
		this->InputList = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));

		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		
		/* "�v���C���[��ԊǗ�"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�X�e�[�W��ԊǗ�"���Ǘ� */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�G�t�F�N�g���\�[�X�Ǘ�"���擾 */
		this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));
	}
}

// �f�X�g���N�^
BulletPlayerKunai::~BulletPlayerKunai()
{
	
}

// ������
void BulletPlayerKunai::Initialization()
{

}

// �`��
void BulletPlayerKunai::Draw()
{
	
}

// �X�V
void BulletPlayerKunai::Update()
{
	
}
