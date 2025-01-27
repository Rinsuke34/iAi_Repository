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
	// �߂�l
	// float	<- �͈͓��Ɏ��߂��l

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

// 臒l�𒴂��Ă��邩�m�F
bool PUBLIC_PROCESS::bCheckAboveThreshold(unsigned char ucValue, unsigned char ucThreshold)
{
	// ����
	// ucValue		<- �m�F����l
	// ucThreshold	<- 臒l
	// �߂�l
	// bool			<- 臒l�𒴂��Ă��邩(true:�����Ă���Afalse:�����Ă��Ȃ�)

	bool bReturn = false;

	/* 臒l�𒴂��Ă��邩�m�F */
	if (ucValue > ucThreshold)
	{
		// 臒l�𒴂��Ă���Ȃ�
		/* true��Ԃ� */
		bReturn = true;
	}

	return bReturn;
}

// �A�i���O�X�e�B�b�N�̓��͂𐳋K��(�}1)
float PUBLIC_PROCESS::fAnalogStickNorm(short sMouseMove)
{
	// ����
	// sMouseMove	<- ���K���������A�i���O�X�e�B�b�N�̓���
	// �߂�l
	// float		<- ���K�������l(�}1�͈̔�)


	/* ���͒l���}1�͈̔͂֐��K�� */
	return (float)sMouseMove / 32767.f;
}

/* 2025.01.21 �e�r�듹 �f�b�h�]�[�������ǉ� �J�n*/
// ���͒l���f�b�h�]�[���͈͓̔��ł��邩�m�F
bool PUBLIC_PROCESS::bCheckInputDeadzone(float fInput, float fDeadzone)
{
	// ����
	// fInput		<- �m�F����l
	// fDeadzone	<- �f�b�h�]�[��
	// �߂�l
	// bool			<- �f�b�h�]�[���͈͓̔��ł��邩(true:�͈͓��ł���Afalse:�͈͓��ł͂Ȃ�)

	bool bReturn = false;

	/* �f�b�h�]�[���͈͓̔��ł��邩�m�F */
	if ((-fDeadzone < fInput) && (fInput < +fDeadzone))
	{
		// �f�b�h�]�[���͈͓̔��Ȃ�
		/* true��Ԃ� */
		bReturn = true;
	}
	else
	{
		bReturn = false;
	}

	return bReturn;

}
/* 2025.01.21 �e�r�듹 �f�b�h�]�[�������ǉ� �I��*/

// 2�̐����̌�_���擾
VECTOR PUBLIC_PROCESS::vecGetLineCrossPoint(VECTOR vecLineAStart, VECTOR vecLineADirection, VECTOR vecLineBStart, VECTOR vecLineBDirection)
{
	// ����
	// vecLineAStart		<- ����A�̎n�_
	// vecLineADirection	<- ����A�̕���
	// vecLineBStart		<- ����B�̎n�_
	// vecLineBDirection	<- ����B�̕���

	VECTOR vecReturn;

	/* ���������s�ł��邩�m�F */
	VECTOR vecGetLineCrossPoint	= VCross(vecLineADirection, vecLineBDirection);		// �O��
	float fCrossSize = VSize(vecGetLineCrossPoint);									// �O�ς̑傫��

	/* ���������s�łȂ����m�F */
	if (fCrossSize == 0.f)
	{
		// ���s�ł���ꍇ
		/* ��_���擾�ł��Ȃ����߁A�n�_��Ԃ� */
		vecReturn = vecLineAStart;
		return vecReturn;
	}

	// �p�����[�^ t1 ���v�Z
	VECTOR diff = VSub(vecLineBStart, vecLineAStart);

	// �p�����[�^ t1 �̓��ς��v�Z
	float t1 = VDot(diff, VCross(vecLineBDirection, vecGetLineCrossPoint)) / (fCrossSize * fCrossSize);

	// ����1��̌�_���v�Z
	return VAdd(vecLineAStart, VScale(vecLineADirection, t1));
}