/* 2024.01.07 ��򕗏� �t�@�C���쐬 */

#include "PlatformBasic.h"

/* ��{�v���b�g�t�H�[���N���X�̐錾 */

// �R���X�g���N�^
PlatformBasic::PlatformBasic() : PlatformBase()
{
	/* ������ */

}

// �f�X�g���N�^
PlatformBasic::~PlatformBasic()
{

}

// �`��
void PlatformBasic::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* ���f���g�� */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}