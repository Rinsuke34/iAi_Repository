/* 2025.03.03 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* �I�u�W�F�N�g */
#include "PlatformBasic.h"

/* ��(�����ʒu)�N���X�̐錾 */

// ��(�����ʒu)�N���X
class FallFog : public PlatformBasic
{
	public:
		FallFog();				// �R���X�g���N�^
		virtual ~FallFog() {};	// �f�X�g���N�^

		virtual void	Draw()				override;	// �`��

	private:
		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Fog;		// ��
};
