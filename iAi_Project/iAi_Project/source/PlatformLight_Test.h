/* 2024.01.13 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* ��������v���b�g�t�H�[���N���X(�e�X�g)�̐錾 */

// ��������v���b�g�t�H�[���N���X(�e�X�g)
class PlatformLight_Test : public PlatformBase
{
	public:
		PlatformLight_Test();				// �R���X�g���N�^
		virtual ~PlatformLight_Test();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override {};	// �X�V
		virtual void	Draw()				override;		// �`��
		virtual void	BloomDraw()			override;		// �����`��

	private:
	protected:

};
