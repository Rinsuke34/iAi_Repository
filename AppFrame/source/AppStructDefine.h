/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>
#include "AppConstantDefine.h"

/* AppFrame�Ŏg�p����\���̂̐錾 */

// ���͊֘A
namespace Struct_Input
{
	struct PLAYER_INPUT_JOYPAD	// �v���C���[����(�W���C�p�b�h)
	{
		/* �W���C�p�b�h */
		char	cgInput[INPUT_MAX][16];						// �W���C�p�b�h����[0:�z�[���h�A1:�g���K�A2:�����[�X][���͓��e]
		bool	bgTrigger[INPUT_MAX][INPUT_DIRECTION];		// �W���C�p�b�h�̃g���K�[�̓���[0:�z�[���h�A1:�g���K�A2:�����[�X][0:���A1:�E]
		short	sAnalogStickX[INPUT_DIRECTION];				// X���A�i���O����[0:���A1:�E]
		short	sAnalogStickY[INPUT_DIRECTION];				// Y���A�i���O����[0:���A1:�E]
	};
	
	struct PLAYER_INPUT_KEYBOARD_MOUSE	// �v���C���[����(�L�[�{�[�h�A�}�E�X)
	{
		/* �L�[�{�[�h */
		char	cgInput[INPUT_MAX][256];	// �L�[����[0:�z�[���h�A1:�g���K�A2:�����[�X][���͓��e]

		/* �}�E�X */
		int	    igInput[INPUT_MAX];		// ����[0:�z�[���h�A1:�g���K�A2:�����[�X]

		int		iMouseX;		// �}�E�XX���W
		int		iMouseY;		// �}�E�XY���W
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

	struct COLLISION_LINE		// �����R���W����
	{
		VECTOR	vecLineStart;		// �����̎n�_
		VECTOR	vecLineEnd;			// �����̏I�_
	};
};