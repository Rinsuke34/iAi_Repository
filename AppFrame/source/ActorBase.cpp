/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "ActorBase.h"

/* ���ׂẴA�N�^�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
ActorBase::ActorBase() : ObjectBase()
{
	/* ������ */
	this->iModelHandle	= -1;	// ���f���n���h��
	this->iLightFrameNo	= -2;	// ���������̐ݒ肳�ꂽ���f���̃t���[���ԍ�
	this->iObjectType	= -1;	// �I�u�W�F�N�g�̎��
}

// �f�X�g���N�^
ActorBase::~ActorBase()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}
