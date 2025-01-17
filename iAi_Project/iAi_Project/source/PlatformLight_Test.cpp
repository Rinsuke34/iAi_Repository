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

	/* �����x�m�F */
	if (OpacityRate > 0.f)
	{
		// ���S�ɓ����łȂ��ꍇ
		/* ���f���`�� */
		MV1DrawModel(this->iModelHandle);
	}
}
