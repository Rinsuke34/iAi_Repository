/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once

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
	float	fClamp(float fValue, float fMax, float fMin);	// �l��͈͓��Ɏ��߂�
}

