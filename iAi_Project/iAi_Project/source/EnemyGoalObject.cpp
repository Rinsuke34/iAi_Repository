/* 2025.01.21 ��򕗏� �t�@�C���쐬 */

#include "EnemyGoalObject.h"

/* �S�[���I�u�W�F�N�g�N���X�̒�` */

// �R���X�g���N�^
EnemyGoalObject::EnemyGoalObject() : EnemyBase()
{
	/* ������ */
	this->iMaxHp = 1;
	this->iNowHp = 1;
	this->iObjectType = OBJECT_TYPE_ENEMY;	// �I�u�W�F�N�g�̎��

	/* �f�[�^���X�g�擾 */
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
		this->iModelHandle = ModelListHandle->iGetModel("Player");
	}
}

// �f�X�g���N�^
EnemyGoalObject::~EnemyGoalObject()
{

}

// ������
void EnemyGoalObject::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.vecCapsuleBottom	= this->vecPosition;
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.f, 100.f, 0.f));
	this->stCollisionCapsule.fCapsuleRadius		= 100.0f;
}

// �X�V
void EnemyGoalObject::Update()
{
	/* ���_���[�W���� */
	if (this->iNowHp <= 0)
	{
		// �_���[�W���󂯂��ꍇ
	}
}
