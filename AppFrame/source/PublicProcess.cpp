/* 2024.12.25 ��򕗏� �t�@�C���쐬 */

#pragma once

#include "AppFunctionDefine.h"

/* �ėp�I�Ɏg�p�ł���v�Z���̒�` */

// �l��͈͓��Ɏ��߂�
float PUBLIC_PROCESS::fClamp(float fValue, float fMax, float fMin)
{
	// ����
	// fValue	<- �͈͓��Ɏ��߂�l
	// fMax		<- �ő�l
	// fMin		<- �ŏ��l

	float fReturn = fValue;

	/* �ő�l���傫�����m�F */
	if (fValue > fMax)
	{
		// �ő�l���傫���Ȃ�
		/* �ő�l�ɐݒ肷�� */
		fReturn = fMax;
	}

	/* �ŏ��l��菬�������m�F */
	if (fValue < fMin)
	{
		// �ŏ��l��菬�����Ȃ�
		/* �ŏ��l�ɐݒ肷�� */
		fReturn = fMin;
	}

	return fReturn;
}