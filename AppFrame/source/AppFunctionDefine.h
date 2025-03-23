/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>
#include <string>

/* AppFrame�Ŏg�p����֐��̐錾 */

// �V�[���̐ݒ�
namespace SCENE_SET
{
	// �����̊֐��͊e�v���O�������ɓ��e��ύX����K�v�����邽�߁AAppFrame�ł͐錾�̂ݍs���e�v���W�F�N�g�Œ�`����
	void	SetFastScene();		// �Q�[���N�����̃V�[�����Z�b�g
	void	SetLoadScene();		// ���[�h�V�[�����Z�b�g
}

// ������
namespace PROJECT_INIT
{
	void	Init();				// �v���W�F�N�g����������
}

// �ėp�v�Z�n
namespace PUBLIC_PROCESS
{
	float		fClamp(float fValue, float fMax, float fMin);																			// �l��͈͓��Ɏ��߂�
	bool		bCheckAboveThreshold(unsigned char ucValue, unsigned char ucThreshold);													// 臒l�𒴂��Ă��邩�m�F
	float		fAnalogStickNorm(short sMouseMove);																						// �A�i���O�X�e�B�b�N�̓��͂𐳋K��(�}1)
	bool		bCheckInputDeadzone(float fInput, float fDeadzone);																		// ���͒l���f�b�h�]�[���͈͓̔��ł��邩�m�F		/* 2025.01.21 �e�r�듹 �f�b�h�]�[�������ǉ� */
	VECTOR		vecGetLineCrossPoint(VECTOR vecLineAStart, VECTOR vecLineADirection, VECTOR vecLineBStart, VECTOR vecLineBDirection);	// 2�̐����̌�_���擾
	COLOR_F		stAddCollorF(COLOR_F vecColorF_A, COLOR_F vecColorF_B);																	// 2�̐F(COLOR_F�^)������
	std::string	aUtf8ToShiftJIS(std::string Utf8);																						// UTF-8 �� Shift-JIS �ϊ�
	std::string	aShiftJisToUtf8(std::string ShiftJis);																					// Shift-JIS �� UTF-8 �ϊ�
	std::string	aCutShitfJisString(std::string ShiftJis, int iLength);																	// Shift-JIS��������w�蕶�����ŃJ�b�g
	std::string aInsertNewLine(std::string ShiftJis, int iLength);																		// Shift-JIS��������w�蕶�����ŉ��s
}
