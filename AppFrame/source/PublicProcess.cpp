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

// 2�̐F(COLOR_F�^)������
COLOR_F	PUBLIC_PROCESS::stAddCollorF(COLOR_F vecColorF_A, COLOR_F vecColorF_B)
{
	// ����
	// vecColorF_A		<- 1�ڂ̐F
	// vecColorF_B		<- 2�ڂ̐F

	COLOR_F stReturn;

	/* �e�v�f�����Z */
	stReturn.a	=	vecColorF_A.a + vecColorF_B.a;
	stReturn.b	=	vecColorF_A.b + vecColorF_B.b;
	stReturn.g	=	vecColorF_A.g + vecColorF_B.g;
	stReturn.r	=	vecColorF_A.r + vecColorF_B.r;

	/* �e�v�f���ő�l(1.f)�𒴂��Ȃ��悤�ɒ��� */
	if (stReturn.a > 1.f)	{ stReturn.a = 1.f; }
	if (stReturn.b > 1.f)	{ stReturn.b = 1.f; }
	if (stReturn.g > 1.f)	{ stReturn.g = 1.f; }
	if (stReturn.r > 1.f)	{ stReturn.r = 1.f; }

	return stReturn;
}

// UTF-8 �� Shift-JIS �ϊ�
std::string	PUBLIC_PROCESS::aUtf8ToShiftJIS(std::string Utf8)
{
	// ����
	// Utf8		<- Shift-Jis�ɕϊ��\���UTF8������

	/* UTF-8 �� UTF-16(���C�h����) */
	int	iWideSize = MultiByteToWideChar(CP_UTF8, 0, Utf8.c_str(), -1, NULL, 0);

	if (iWideSize == 0) return "";

	std::wstring wideStr(iWideSize, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, Utf8.c_str(), -1, &wideStr[0], iWideSize);

	/* UTF-16 �� Shift-JIS */
	int iSjisSize = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, NULL, 0, NULL, NULL);
	if (iSjisSize == 0) return "";

	std::string aSjisStr(iSjisSize, '\0');
	WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, &aSjisStr[0], iSjisSize, NULL, NULL);

	return aSjisStr;
}

// Shift-JIS��������w�蕶�����ŃJ�b�g
std::string	PUBLIC_PROCESS::aCutShitfJisString(std::string ShiftJis, int iLength)
{
	// ����
	// ShiftJis		<- �J�b�g����Shift-JIS������
	// iLength		<- �J�b�g���镶����

	int iCount = 0;
	int iPossition = 0;

	while (iPossition < ShiftJis.size() && iCount < iLength)
	{
		/* Shift-JIS �̐擪�o�C�g���擾 */
		unsigned char ch = static_cast<unsigned char>(ShiftJis[iPossition]);

		/* �����̃o�C�g�����擾 */
		if (ch <= 0x7F || (ch >= 0xA1 && ch <= 0xDF))
		{
			// ���p����(1�o�C�g)�ł���ꍇ
			iPossition += 1;
		}
		else
		{
			// �S�p����(2�o�C�g)�ł���ꍇ
			/* �������Ō�܂ŋL�q����Ă��邩�m�F */
			if (iPossition + 1 < ShiftJis.size())
			{
				// �������Ō�܂ŋL�q����Ă���ꍇ
				iPossition += 2;
			}
			else
			{
				// �������r���œr�؂�Ă���ꍇ
				break;
			}
		}

		/* �J�E���g�����Z���� */
		iCount++;
	}

	return ShiftJis.substr(0, iPossition);
}

// Shift-JIS��������w�蕶�����ŉ��s
std::string PUBLIC_PROCESS::aInsertNewLine(std::string ShiftJis, int iLength)
{
	// ����
	// ShiftJis		<- ���s����Shift-JIS������
	// iLength		<- ���s���镶����

	int iPossition = 0;  // ���݂̈ʒu
	int iCount = 0;      // �������J�E���g

	while (iPossition < ShiftJis.size())
	{
		/* ���s����������J�E���g�����Z�b�g */
		if (ShiftJis[iPossition] == '\n')
		{
			iCount = 0;
			iPossition += 1;
			continue;
		}

		/* Shift-JIS �̐擪�o�C�g���擾 */
		unsigned char ch = static_cast<unsigned char>(ShiftJis[iPossition]);

		/* �����̃o�C�g�����擾 */
		if (ch <= 0x7F || (ch >= 0xA1 && ch <= 0xDF))
		{
			// ���p���� (1�o�C�g)
			iPossition += 1;
		}
		else
		{
			// �S�p���� (2�o�C�g)
			if (iPossition + 1 < ShiftJis.size())
			{
				iPossition += 2;
			}
			else
			{
				break; // �������r���œr�؂�Ă���ꍇ
			}
		}

		iCount++;

		// �w�蕶�����ɒB��������s��}��
		if (iCount >= iLength)
		{
			ShiftJis.insert(iPossition, "\n");
			iPossition += 1; // ���s�̕������ʒu�����炷
			iCount = 0;       // �J�E���g�����Z�b�g
		}
	}

	return ShiftJis;
}

