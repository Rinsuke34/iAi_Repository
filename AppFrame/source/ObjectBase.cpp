/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "ObjectBase.h"

/* ���ׂẴI�u�W�F�N�g�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
ObjectBase::ObjectBase()
{
	/* ������ */
	this->bDeleteFlg			= false;				// �폜�t���O
	this->vecPosition			= VGet(0.f, 0.f, 0.f);	// �I�u�W�F�N�g���W
	this->vecRotation			= VGet(0.f, 0.f, 0.f);	// �I�u�W�F�N�g�̉�]��
	this->vecScale				= VGet(1.f, 1.f, 1.f);	// �I�u�W�F�N�g�̊g�嗦
	this->vecPosition_Initial	= VGet(0.f, 0.f, 0.f);	// ������Ԃł̃I�u�W�F�N�g�̍��W
	this->vecRotation_Initial	= VGet(0.f, 0.f, 0.f);	// ������Ԃł̃I�u�W�F�N�g�̉�]��
	this->vecScale_Initial		= VGet(1.f, 1.f, 1.f);	// ������Ԃł̃I�u�W�F�N�g�̊g�嗦(x,y,z�������ꂼ��̊g��{��)
}

// �����ʒu�ݒ�
void ObjectBase::SetupInitialPosition()
{
	/* �����ʒu��ݒ� */
	this->vecPosition_Initial	= this->vecPosition;
	this->vecRotation_Initial	= this->vecRotation;
	this->vecScale_Initial		= this->vecScale;
}