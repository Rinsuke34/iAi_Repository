/* 2024.12.18 ��򕗏� �t�@�C���쐬 */

#include "BulletBase.h"

/* ���ׂĂ̒e�ۂ̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
BulletBase::BulletBase() : ActorBase()
{
	/* ������ */
	this->stCollisionSqhere = {};	// �R���W����(����)
	this->vecMoveDirection	= {};	// �ړ�����
}
