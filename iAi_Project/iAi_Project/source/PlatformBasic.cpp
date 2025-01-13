/* 2024.01.07 ��򕗏� �t�@�C���쐬 */

#include "PlatformBasic.h"

/* ��{�v���b�g�t�H�[���N���X�̐錾 */

// �R���X�g���N�^
PlatformBasic::PlatformBasic() : PlatformBase()
{

}

// �f�X�g���N�^
PlatformBasic::~PlatformBasic()
{

}

// ������
void PlatformBasic::Initialization()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* ���f���g�� */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* �R���W�����t���[���ԍ��擾 */
	//this->SetCollisionFrameNo(MV1SearchFrame(this->iModelHandle, "Collision"));
	this->SetCollisionFrameNo(-1);

	/* �R���W�������\�z */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);
}

// �`��
void PlatformBasic::Draw()
{
	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}