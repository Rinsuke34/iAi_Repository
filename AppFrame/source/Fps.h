/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "DxLib.h"

/* �t���[�����[�g�Œ�N���X�̐錾 */

// �t���[�����[�g�Œ�N���X
class Fps
{
	public:
		Fps();				// �R���X�g���N�^
		virtual ~Fps() {};	// �f�X�g���N�^

		void FpsAdjustment();			// �t���[�����[�g��������

	private:
		/* �֐� */
		void FpsUpdate();				// �����v�Z
		void FpsWait();					// �t���[�����[�g�����̂��ߑҋ@

		/* �ϐ� */
		int iStartTime;					// ����J�n����
		int iCount;						// �J�E���^

};
