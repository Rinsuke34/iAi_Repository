/* 2025.01.22 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "PlatformBase.h"

/* ���O��ԏȗ� */
using namespace Struct_Collision;

/* ���ׂĂ̕`�ʃ��f���̃x�[�X�ƂȂ�N���X�̐錾 */
// ���f�U�C�i�[�̕��S�΍�ɃR���W�����p�ƕ`�ʗp�Ń��f���𕪂���

// �`�ʃ��f���x�[�X�N���X
class BackGroundBase : public PlatformBase
{
	public:
		BackGroundBase();			// �R���X�g���N�^
		virtual ~BackGroundBase() {};	// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Draw();								// �`��
		virtual void	BloomDraw();						// �����`��

	private:
	protected:
		/* �֐� */
		void	UpdataLightFrame();						// �����̐ݒ肳�ꂽ�t���[�����擾

		/* �ϐ� */
		std::vector<int>		aiLightFrameNo;			// �����t���[���ԍ�
};
