/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "PlatformBase.h"

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
PlatformBase::PlatformBase() : ObjectBase()
{
	/* ������ */
	this->iModelHandle = -1;	// ���f���n���h��
}

// �f�X�g���N�^
PlatformBase::~PlatformBase()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}
