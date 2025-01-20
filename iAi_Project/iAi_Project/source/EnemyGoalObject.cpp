/* 2025.01.21 ��򕗏� �t�@�C���쐬 */

#include "EnemyGoalObject.h"

/* �S�[���I�u�W�F�N�g�N���X�̒�` */

// �R���X�g���N�^
EnemyGoalObject::EnemyGoalObject() : EnemyBase()
{
	/* HP��ݒ�(��) */
	this->iMaxHp = 1;
	this->iNowHp = 1;

	/* ������ */
	/* �f�[�^���X�g�擾 */
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
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

// �`��
void EnemyGoalObject::Draw()
{
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.fCapsuleRadius, 40, 8, GetColor(255, 0, 0), GetColor(255, 0, 0));
}
