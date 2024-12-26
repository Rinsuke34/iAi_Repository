/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include <math.h>
#include "DxLib.h"
#include "Fps.h"
#include "AppVariableDefine.h"
#include "AppConstantDefine.h"

/* �t���[�����[�g�Œ�N���X�̒�` */

// �R���X�g���N�^(�N���X���g�p�\�ɂȂ����^�C�~���O�Ŏ��s����)
Fps::Fps()
{
	/* �ϐ��̏����� */
	this->iStartTime	= 0;	// ����J�n����	
	this->iCount		= 0;	// �J�E���^
}

// �����v�Z
bool Fps::FpsUpdate()
{
	/* �J�E���^�̊m�F */
	if (this->iCount == 0)
	{
		// 1�t���[���ڂł���Ȃ�
		/* �������擾 */
		this->iStartTime = GetNowCount();
	}
	if (this->iCount == FRAME_RATE::FPS_RATE)
	{
		// �t���[�����[�g�ݒ�l�ł���Ȃ�
		/* ���ݎ������擾 */
		int t = GetNowCount();

		/* ���݂̃t���[�����[�g���擾 */
		giNowFps	= (int)(1000.f / ((t - iStartTime) / (float)FRAME_RATE::FPS_RATE));

		/* �J�E���^�A�J�n�������X�V */
		this->iCount		= 0;
		this->iStartTime	= t;
	}

	/* �J�E���^�̉��Z */
	this->iCount++;

	return true;
}

// �t���[�����[�g�����̂��ߑҋ@
void Fps::FpsWait()
{
	/* �t���[�����[�g�ݒ�l�܂łɂ����������Ԃ̎擾 */
	int iTookTime = GetNowCount() - this->iStartTime;

	/* �ҋ@���鎞�Ԃ��Z�o */
	int iWaitTime = this->iCount * 1000 / FRAME_RATE::FPS_RATE - iTookTime;
	if (iWaitTime > 0)
	{
		/* �K�v�ł���Ȃ�Αҋ@���s�� */
		Sleep(iWaitTime);
	}
}
