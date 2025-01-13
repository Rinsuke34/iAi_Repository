/* 2024.01.13 ��򕗏� �t�@�C���쐬 */

#include "PlatformLight_Test.h"

/* ��������v���b�g�t�H�[���N���X(�e�X�g)�̒�` */

// �R���X�g���N�^
PlatformLight_Test::PlatformLight_Test() : PlatformBase()
{

}

// �f�X�g���N�^
PlatformLight_Test::~PlatformLight_Test()
{

}

// ������
void PlatformLight_Test::Initialization()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* ���f���g�� */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* �R���W�����t���[���ԍ��擾 */
	this->SetCollisionFrameNo(MV1SearchFrame(this->iModelHandle, "Collision"));

	/* �����t���[���ԍ��擾 */
	this->SetLightHandle(MV1SearchFrame(this->iModelHandle, "Light"));

	/* �R���W�������\�z */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);
}

// �`��
void PlatformLight_Test::Draw()
{
	/* ���݂̃��f���̓����x�擾 */
	float OpacityRate = MV1GetOpacityRate(this->iModelHandle);

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_UP] == TRUE)
	{		
		/* �����x���グ�� */
		OpacityRate += 0.01f;
		MV1SetOpacityRate(this->iModelHandle, OpacityRate);
	}
	else if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_DOWN] == TRUE)
	{
		/* �����x�������� */
		OpacityRate -= 0.01f;
		MV1SetOpacityRate(this->iModelHandle, OpacityRate);
	}

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}