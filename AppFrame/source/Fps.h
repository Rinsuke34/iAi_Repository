/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "DxLib.h"

/* �t���[�����[�g�Œ�N���X�̐錾 */

// �t���[�����[�g�Œ�N���X
class Fps
{
	// �ǂ��ł��g�p�\
	public:
		// �R���X�g���N�^(�N���X���g�p�\�ɂȂ����^�C�~���O�Ŏ��s����)
		Fps();

		bool FpsUpdate();				// �����v�Z
		void FpsWait();					// �t���[�����[�g�����̂��ߑҋ@

	// Fps�N���X���݂̂Ŏg�p�\
	private:
		int iStartTime;					// ����J�n����
		int iCount;						// �J�E���^

	// Fps�N���X�Ƃ��̎q�N���X�݂̂Ŏg�p�\
	protected:
};
