/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ActorBase.h"

/* ���ׂẴA�N�^�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
ActorBase::ActorBase() : ObjectBase()
{
	/* ������ */
	this->vecMovement	= {};	// �ړ���
	this->iModelHandle	= -1;	// ���f���n���h��
}

// �f�X�g���N�^
ActorBase::~ActorBase()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}
