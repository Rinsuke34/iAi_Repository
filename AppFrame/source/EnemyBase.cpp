/* 2024.12.21 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "EnemyBase.h"

/* ���ׂẴG�l�~�[�̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
EnemyBase::EnemyBase() : CharacterBase()
{
	/* ������ */
	this->iMaxHp	= 0;	// �ő�HP
	this->iNowHP	= 0;	// ����HP
}
