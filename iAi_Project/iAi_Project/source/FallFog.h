/* 2025.03.03 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Object.h"

/* ��(�����ʒu)�N���X�̐錾 */

// ��(�����ʒu)�N���X
class FallFog : public PlatformBase
{
	public:
		FallFog();				// �R���X�g���N�^
		virtual ~FallFog() {};	// �f�X�g���N�^

		void	Initialization()	override;		// ������
		void	Draw()				override;		// �`��
		void	BloomDraw()			override {};	// �����`��

	private:
		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_Fog;		// ��
};
