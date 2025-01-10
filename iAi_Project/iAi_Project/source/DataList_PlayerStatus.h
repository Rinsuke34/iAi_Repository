/* 2024.12.26 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"

/* �v���C���[��ԊǗ��N���X�̐錾 */

// �v���C���[��ԊǗ��N���X
class DataList_PlayerStatus : public DataListBase
{
	public:
		DataList_PlayerStatus();			// �R���X�g���N�^
		virtual ~DataList_PlayerStatus();	// �f�X�g���N�^

		/* �f�[�^�擾 */
		// �v���C���[��Ԋ֘A
		float	fGetPlayerNowMoveSpeed()		{ return this->fPlayerNowMoveSpeed; }		// �v���C���[�̌��݂̈ړ����x�擾
		float	fGetPlayerAngleX()				{ return this->fPlayerAngleX; }				// �v���C���[��X����]��(���W�A��)�擾
		float	fGetPlayerNowFallSpeed()		{ return this->fPlayerNowFallSpeed; }		// �v���C���[�̌��݂̗������x�擾
		// �\�͒l�֘A
		float	fGetPlayerMoveAcceleration()	{ return this->fPlayerMoveAcceleration; }	// �v���C���[�̈ړ������x�擾
		float	fGetPlayerMaxMoveSpeed()		{ return this->fPlayerMaxMoveSpeed; }		// �v���C���[�̍ő�ړ����x�擾
		float	fGetPlayerFallAcceleration()	{ return this->fPlayerFallAcceleration; }	// �v���C���[�̗��������x�擾
		float	fGetPlayerMaxFallSpeed()		{ return this->fPlayerMaxFallSpeed; }		// �v���C���[�̍ő嗎�����x�擾
		// �J�����֘A
		int		iGetCameraMode()							{ return this->iCameraMode; }							// �J�������[�h�擾
		VECTOR	vecGetCameraUp()							{ return this->vecCameraUp; };							// �J�����̏�����擾
		VECTOR	vecGetCameraPosition()						{ return this->vecCameraPosition; };					// �J�����̍��W�擾
		VECTOR	vecGetCameraTarget()						{ return this->vecCameraTarget; };						// �J�����̒����_�擾
		float	fGetCameraRadius()							{ return this->fCameraRadius; };						// �J�����̒��S�_����̋����擾
		float	fGetCameraAngleX()							{ return this->fCameraAngleX; };						// �J������X����]��(���W�A��)�擾
		float	fGetCameraAngleY()							{ return this->fCameraAngleY; };						// �J������Y����]��(���W�A��)�擾
		float	fGetCameraRotationalSpeed_Controller()		{ return this->fCameraRotationalSpeed_Controller; };	// �J�����̉�]���x(�R���g���[���[)�擾
		float	fGetCameraRotationalSpeed_Mouse()			{ return this->fCameraRotationalSpeed_Mouse; };			// �J�����̉�]���x(�}�E�X)�擾
		float	fGetCameraAngleLimitUp()					{ return this->fCameraAngleLimitUp; };					// �J�����̉�]�p�x�����擾(��)
		float	fGetCameraAngleLimitDown()					{ return this->fCameraAngleLimitDown; };				// �J�����̉�]�p�x�����擾(��)

		/* �f�[�^�ݒ� */
		// �v���C���[��Ԋ֘A
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)			{ this->fPlayerNowMoveSpeed		= fPlayerNowMoveSpeed; }		// �v���C���[�̌��݂̈ړ����x�ݒ�
		void	SetPlayerAngleX(float fPlayerAngleX)						{ this->fPlayerAngleX			= fPlayerAngleX; }				// �v���C���[��X����]��(���W�A��)�擾
		void	SetPlayerNowFallSpeed(float fPlayerNowFallSpeed)			{ this->fPlayerNowFallSpeed		= fPlayerNowFallSpeed; }		// �v���C���[�̌��݂̗������x�ݒ�
		// �\�͒l�֘A
		void	SetPlayerMoveAcceleration(float fPlayerMoveAcceleration)	{ this->fPlayerMoveAcceleration	= fPlayerMoveAcceleration; }	// �v���C���[�̈ړ������x�ݒ�
		void	SetPlayerMaxMoveSpeed(float fPlayerMaxMoveSpeed)			{ this->fPlayerMaxMoveSpeed		= fPlayerMaxMoveSpeed;}			// �v���C���[�̍ő�ړ����x�擾
		void	SetPlayerFallAcceleration(float fPlayerFallAcceleration)	{ this->fPlayerFallAcceleration	= fPlayerFallAcceleration; }	// �v���C���[�̗��������x�ݒ�
		void	SetPlayerMaxFallSpeed(float fPlayerMaxFallSpeed)			{ this->fPlayerMaxFallSpeed		= fPlayerMaxFallSpeed; }		// �v���C���[�̍ő嗎�����x�ݒ�
		// �J�����֘A
		void	SetCameraMode(int iCameraMode)										{ this->iCameraMode							= iCameraMode; };				// �J�������[�h�ݒ�
		void	SetCameraUp(VECTOR vecCameraUp)										{ this->vecCameraUp							= vecCameraUp; };				// �J�����̏�����ݒ�
		void	SetCameraPosition(VECTOR vecCameraPosition)							{ this->vecCameraPosition					= vecCameraPosition; };			// �J�����̍��W�ݒ�
		void	SetCameraTarget(VECTOR vecCameraTarget)								{ this->vecCameraTarget						= vecCameraTarget; };			// �J�����̒����_�ݒ�
		void	SetCameraRadius(float fCameraRadius)								{ this->fCameraRadius						= fCameraRadius; };				// �J�����̒��S�_����̋����ݒ�
		void	SetCameraAngleX(float fCameraAngleX)								{ this->fCameraAngleX						= fCameraAngleX; };				// �J������X����]��(���W�A��)�ݒ�
		void	SetCameraAngleY(float fCameraAngleY)								{ this->fCameraAngleY						= fCameraAngleY; };				// �J������Y����]��(���W�A��)�ݒ�
		void	SetCameraRotationalSpeed_Controller(float fCameraRotationalSpeed)	{ this->fCameraRotationalSpeed_Controller	= fCameraRotationalSpeed; };	// �J�����̉�]���x(�R���g���[���[)�ݒ�
		void	SetCameraRotationalSpeed_Mouse(float fCameraRotationalSpeed)		{ this->fCameraRotationalSpeed_Mouse		= fCameraRotationalSpeed; };	// �J�����̉�]���x(�}�E�X)�ݒ�
		void	SetCameraAngleLimitUp(float fCameraAngleupsideLimitUp)				{ this->fCameraAngleLimitUp					= fCameraAngleLimitUp; };		// �J�����̉�]�p�x�����ݒ�(��)
		void	SetCameraAngleLimitDown(float fCameraAngleupsideLimitDown)			{ this->fCameraAngleLimitDown				= fCameraAngleLimitDown; };		// �J�����̉�]�p�x�����ݒ�(��)

	private:
		/* �v���C���[��Ԋ֘A */
		float	fPlayerNowMoveSpeed;		// �v���C���[�̌��݂̈ړ����x
		float	fPlayerAngleX;				// �v���C���[��X����]��(���W�A��)
		float	fPlayerNowFallSpeed;		// �v���C���[�̌��݂̗������x

		/* �\�͒l�֘A */
		float	fPlayerMoveAcceleration;	// �v���C���[�̈ړ������x
		float	fPlayerMaxMoveSpeed;		// �v���C���[�̍ő�ړ����x
		float	fPlayerFallAcceleration;	// �v���C���[�̗��������x
		float	fPlayerMaxFallSpeed;		// �v���C���[�̍ő嗎�����x

		/* �J�����֘A */
		int		iCameraMode;						// �J�������[�h
		VECTOR	vecCameraUp;						// �J�����̏����
		VECTOR	vecCameraPosition;					// �J�����̍��W
		VECTOR	vecCameraTarget;					// �J�����̒����_
		float	fCameraRadius;						// �J�����̒��S�_����̋���(�Y�[����)
		float	fCameraAngleX;						// �J������X����]��(���W�A��)
		float	fCameraAngleY;						// �J������Y����]��(���W�A��)
		float	fCameraRotationalSpeed_Controller;	// �J�����̉�]���x(�R���g���[���[)
		float	fCameraRotationalSpeed_Mouse;		// �J�����̉�]���x(�}�E�X)
		float	fCameraAngleLimitUp;				// �J�����̉�]�p�x����(��)
		float	fCameraAngleLimitDown;				// �J�����̉�]�p�x����(��)

	protected:
};
