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

// �t���[�����[�g��������
void Fps::FpsAdjustment()
{
	/* �����v�Z */
	FpsUpdate();

	/* �t���[�����[�g�����̂��ߑҋ@ */
	FpsWait();
}

// �t���[�����[�g�`��(�f�o�b�O�p)
void Fps::DrawFPS()
{
	/* �t���[�����[�g�`�� */
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), giFontHandle, "FPS:%d", giNowFps);
}

// �����v�Z
void Fps::FpsUpdate()
{
	/* �J�E���^�̊m�F */
	if (this->iCount == 0)
	{
		// 1�t���[���ڂł���Ȃ�
		/* �������擾 */
		this->iStartTime = GetNowCount();
	}
	if (this->iCount == FPS_RATE)
	{
		// �t���[�����[�g�ݒ�l�ł���Ȃ�
		/* ���ݎ������擾 */
		int t = GetNowCount();

		/* ���݂̃t���[�����[�g���擾 */
		giNowFps	= (int)(1000.f / ((t - iStartTime) / (float)FPS_RATE));

		/* �J�E���^�A�J�n�������X�V */
		this->iCount		= 0;
		this->iStartTime	= t;
	}

	/* �J�E���^�̉��Z */
	this->iCount++;

	return;
}

// �t���[�����[�g�����̂��ߑҋ@
void Fps::FpsWait()
{
	/* �t���[�����[�g�ݒ�l�܂łɂ����������Ԃ̎擾 */
	int iTookTime = GetNowCount() - this->iStartTime;

	/* �ҋ@���鎞�Ԃ��Z�o */
	int iWaitTime	= this->iCount * 1000 / FPS_RATE - iTookTime;

	/* �ҋ@���K�v�ł��邩�m�F */
	if (iWaitTime > 0)
	{
		// �ҋ@���K�v�ł���ꍇ
		/* �t���[�����[�g�����̂��߁A�ҋ@���s�� */
		Sleep(iWaitTime);
	}
}
