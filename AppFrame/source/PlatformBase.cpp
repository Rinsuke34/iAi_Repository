/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "PlatformBase.h"

/* ���ׂẴv���b�g�t�H�[���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
PlatformBase::PlatformBase() : ObjectBase()
{
	/* ������ */
	this->iModelHandle		= 0;					// ���f���n���h��
	this->vecRotation			= VGet(0.f, 0.f, 0.f);	// ��]��
	this->vecScale			= VGet(1.f, 1.f, 1.f);	// �g�嗦
}

// �f�X�g���N�^
PlatformBase::~PlatformBase()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}

// ������
void PlatformBase::Initialization()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* ���f���g�� */
	MV1SetScale(this->iModelHandle, this->vecScale);
}
