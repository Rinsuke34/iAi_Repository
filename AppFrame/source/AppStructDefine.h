/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>

/* AppFrame�Ŏg�p����\���̂̐錾 */

// ���͊֘A
namespace Struct_Input
{
	struct PLAYER_INPUT_JOYPAD	// �v���C���[����(�W���C�p�b�h)
	{
		/* �W���C�p�b�h */
		int	    igInput[3];			// �W���C�p�b�h����(0:�z�[���h�A1:�g���K�A2:�����[�X)

		/* �W���C�p�b�h(���A�i���O�X�e�B�b�N) */
		int		iXAnalog;		// X���A�i���O����
		int		iYAnalog;		// Y���A�i���O����
	};
	
	struct PLAYER_INPUT_KEYBOARD_MOUSE	// �v���C���[����(�L�[�{�[�h�A�}�E�X)
	{
		/* �L�[�{�[�h */
		char	cgInput[3][256];	// �L�[����(0:�z�[���h�A1:�g���K�A2:�����[�X)

		/* �}�E�X */
		int	    igInput[3];		// ����(0:�z�[���h�A1:�g���K�A2:�����[�X)

		int		iMouseMoveX;	// X�ړ���
		int		iMouseMoveY;	// Y�ړ���
	};
}

// �R���W�����֘A
namespace Struct_Collision
{
	struct COLLISION_CAPSULE	// �J�v�Z���R���W����
	{
		VECTOR	vecCapsuleTop;		// �J�v�Z���̏㕔
		VECTOR	vecCapsuleBottom;	// �J�v�Z���̉���
		float	fCapsuleRadius;		// �J�v�Z���̔��a
	};

	struct COLLISION_SQHERE		// ���̃R���W����
	{
		VECTOR	vecSqhere;			// ���̂̒��S
		float	fSqhereRadius;		// ���̂̔��a
	};
};