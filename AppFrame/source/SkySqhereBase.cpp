/* 2025.02.06 ��򕗏� �t�@�C���쐬 */

#include "SkySqhereBase.h"

/* ���ׂẴX�J�C�X�t�B�A(��Ƃ��ĕ`�ʂ��鋅��)�̃x�[�X�ƂȂ�N���X�̒�` */
// �R���X�g���N�^
SkySqhereBase::SkySqhereBase() : ObjectBase()
{
	/* ������ */
	this->iModelHandle = 0;					// ���f���n���h��
}

// �f�X�g���N�^
SkySqhereBase::~SkySqhereBase()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}

// �`��
void SkySqhereBase::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}
