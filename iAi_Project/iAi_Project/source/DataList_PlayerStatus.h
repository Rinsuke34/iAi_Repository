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
		int		iGetPlayerState()				{ return this->iPlayerState; }				// �v���C���[�̏�Ԏ擾
		bool	bGetPlayerLandingFlg()			{ return this->bPlayerLandingFlg; }			// �v���C���[���󒆂ɂ��邩�̃t���O�擾
		float	fGetPlayerNowMoveSpeed()		{ return this->fPlayerNowMoveSpeed; }		// �v���C���[�̌��݂̈ړ����x�擾
		float	fGetPlayerAngleX()				{ return this->fPlayerAngleX; }				// �v���C���[��X����]��(���W�A��)�擾
		float	fGetPlayerNowFallSpeed()		{ return this->fPlayerNowFallSpeed; }		// �v���C���[�̌��݂̗������x�擾
		int		iGetPlayerNowJumpCount()		{ return this->iPlayerNowJumpCount; }		// �v���C���[�̃W�����v��(���ݐ�)�擾
		// �\�͒l�֘A
		float	fGetPlayerMoveAcceleration()	{ return this->fPlayerMoveAcceleration; }	// �v���C���[�̈ړ������x�擾
		float	fGetPlayerMaxMoveSpeed()		{ return this->fPlayerMaxMoveSpeed; }		// �v���C���[�̍ő�ړ����x�擾
		float	fGetPlayerFallAcceleration()	{ return this->fPlayerFallAcceleration; }	// �v���C���[�̗��������x�擾
		float	fGetPlayerMaxFallSpeed()		{ return this->fPlayerMaxFallSpeed; }		// �v���C���[�̍ő嗎�����x�擾
		int		iGetPlayerMaxJumpCount()		{ return this->iPlayerMaxJumpCount; }		// �v���C���[�̃W�����v��(�ő吔)�擾

		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� �J�n*/
		
		//�ړ��i�����E���蓙�j
		VECTOR	vecGetPlayerOldVector() { return this->vecPlayerOldVector; }			//�v���C���[�̈ړ����̃x�N�g�����擾�i�W�����v�������Ɏg�p�j
		float	fGetPlayerOldRadian() { return this->fPlayerOldRadian; }			//�v���C���[�̈ړ����̊p�x���擾�i�����]�������Ɏg�p�j
		int		iGetPlayerNormalDashFlameCount() { return this->iPlayerNormalDashFlameCount; }  //�ʏ�_�b�V�����o�߃t���[�������擾�i�����_�b�V���ւ̈ڍs�Ɏg�p�j
		
		//�W�����v
		int		iGetPlayerJumpCount() { return this->iPlayerJumpCount; }			//�v���C���[�W�����v�񐔂��擾
		bool	bGetPlayerJumpingFlag() { return this->bPlayerJumpingFlag; }			//�v���C���[���W�����v�����̃t���O���擾
		
		//���
		bool	bGetPlayerDodgingFlag() { return this->bPlayerDodgingFlag; }						//�v���C���[����𒆂��̃t���O���擾
		float	fGetPlayerDodgeProgress() { return this->fPlayerDodgeProgress; }					// �v���C���[������[�V�����i�s�����擾 
		VECTOR	vecGetPlayerDodgeDirection() { return this->vecPlayerDodgeDirection; }				// �v���C���[���������擾
		int		iGetPlayerDodgeWhileJumpingCount() { return this->iPlayerDodgeWhileJumpingCount; }	//�v���C���[�W�����v���̉���񐔂��擾
		bool	bGetPlayerAfterDodgeFlag() { return this->bPlayerAfterDodgeFlag; }					//�v���C���[�̉����t���O���擾
		float	fGetPlayerDodgeSpeed() { return this->fPlayerDodgeSpeed; }			//�v���C���[��𑬓x���擾
		int		iGetPlayerNowDodgeFlame() { return this->iPlayerNowDodgeFlame; }	// �v���C���[�̌��݂̉���t���[�������擾
		
		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� �I��*/

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
		void	SetPlayerState(int iPlayerState)							{ this->iPlayerState			= iPlayerState; }				// �v���C���[�̏�Ԑݒ�
		void	SetPlayerLanding(bool bPlayerLanding)						{ this->bPlayerLandingFlg		= bPlayerLanding; }				// �v���C���[���󒆂ɂ��邩�̃t���O�ݒ�
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)			{ this->fPlayerNowMoveSpeed		= fPlayerNowMoveSpeed; }		// �v���C���[�̌��݂̈ړ����x�ݒ�
		void	SetPlayerAngleX(float fPlayerAngleX)						{ this->fPlayerAngleX			= fPlayerAngleX; }				// �v���C���[��X����]��(���W�A��)�擾
		void	SetPlayerNowFallSpeed(float fPlayerNowFallSpeed)			{ this->fPlayerNowFallSpeed		= fPlayerNowFallSpeed; }		// �v���C���[�̌��݂̗������x�ݒ�
		void	SetPlayerNowJumpCount(int iPlayerNowJumpCount)				{ this->iPlayerNowJumpCount		= iPlayerNowJumpCount; }		// �v���C���[�̃W�����v��(���ݐ�)�ݒ�
		void	SetPlayerNormalDashFlameCount(int iPlayerNormalDashFlameCount) { this->iPlayerNormalDashFlameCount = iPlayerNormalDashFlameCount; }			//�ʏ�_�b�V�����o�߃t���[������ݒ�
		//���
		void	SetPlayerDodgingFlag(bool bPlayerDodgingFlag) { this->bPlayerDodgingFlag = bPlayerDodgingFlag; }											//�v���C���[����𒆂��̃t���O��ݒ�
		void	SetPlayerDodgeProgress(float fPlayerDodgeProgress) { this->fPlayerDodgeProgress = fPlayerDodgeProgress; }									// �v���C���[������[�V�����i�s����ݒ�
		void	SetPlayerDodgeDirection(VECTOR vecPlayerDodgeDirection) { this->vecPlayerDodgeDirection = vecPlayerDodgeDirection; }						// �v���C���[��������ݒ�
		void	SetPlayerDodgeWhileJumpingCount(int iPlayerDodgeWhileJumpingCount) { this->iPlayerDodgeWhileJumpingCount = iPlayerDodgeWhileJumpingCount; } //�v���C���[�W�����v���̉���񐔂�ݒ�
		void	SetPlayerAfterDodgeFlag(bool bPlayerAfterDodgeFlag) { this->bPlayerAfterDodgeFlag = bPlayerAfterDodgeFlag; }								//�v���C���[�̉����t���O��ݒ�
		//�W�����v
		void	SetPlayerJumpCount(int iPlayerJumpCount) { this->iPlayerJumpCount = iPlayerJumpCount; }				//�v���C���[�W�����v�񐔂�ݒ�
		void	SetPlayerJumpingFlag(bool bPlayerJumpingFlag) { this->bPlayerJumpingFlag = bPlayerJumpingFlag; }	//�v���C���[���W�����v�����̃t���O��ݒ�

		// �\�͒l�֘A
		void	SetPlayerMoveAcceleration(float fPlayerMoveAcceleration)	{ this->fPlayerMoveAcceleration	= fPlayerMoveAcceleration; }	// �v���C���[�̈ړ������x�ݒ�
		void	SetPlayerMaxMoveSpeed(float fPlayerMaxMoveSpeed)			{ this->fPlayerMaxMoveSpeed		= fPlayerMaxMoveSpeed;}			// �v���C���[�̍ő�ړ����x�擾
		void	SetPlayerFallAcceleration(float fPlayerFallAcceleration)	{ this->fPlayerFallAcceleration	= fPlayerFallAcceleration; }	// �v���C���[�̗��������x�ݒ�
		void	SetPlayerMaxFallSpeed(float fPlayerMaxFallSpeed)			{ this->fPlayerMaxFallSpeed		= fPlayerMaxFallSpeed; }		// �v���C���[�̍ő嗎�����x�ݒ�
		void	SetPlayerMaxJumpCount(int iPlayerMaxJumpCount)				{ this->iPlayerMaxJumpCount		= iPlayerMaxJumpCount; }		// �v���C���[�̃W�����v��(�ő吔)�ݒ�

		//���
		void	SetPlayerDodgeSpeed(float fPlayerDodgeSpeed) { this->fPlayerDodgeSpeed = fPlayerDodgeSpeed; }			//�v���C���[��𑬓x���擾
		void	SetPlayerNowDodgeFlame(int iPlayerNowDodgeFlame) { this->iPlayerNowDodgeFlame = iPlayerNowDodgeFlame; }			// �v���C���[������Ԃ��擾
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

		/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ��J�n */
		//�U��
		VECTOR vecPlayerChargeAttakPoint;	//�v���C���[���ߍU���̖ړI�n
		VECTOR vecPlayerChargeAttakVector;	//�v���C���[���ߍU���̕���
		int iPlayerNowAttakChargeFlame;		//���݂̃v���C���[���ߍU���`���[�W�t���[����
		/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ��I�� */

	private:
		/* �v���C���[��Ԋ֘A */
		int		iPlayerState;				// �v���C���[�̏��
		bool	bPlayerLandingFlg;			// �v���C���[�����n���Ă��邩�̃t���O
		float	fPlayerNowMoveSpeed;		// �v���C���[�̌��݂̈ړ����x
		float	fPlayerAngleX;				// �v���C���[��X����]��(���W�A��)
		float	fPlayerNowFallSpeed;		// �v���C���[�̌��݂̗������x
		int		iPlayerNowJumpCount;		// �v���C���[�̃W�����v��(���ݐ�)

		/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ��J�n */
		//�ړ��i�����E���蓙�j
		float fPlayerMoveSpeed;				//�v���C���[���݂̈ړ����x
		VECTOR vecPlayerOldVector;			//�v���C���[�̈ړ����̃x�N�g����ۑ�����i�W�����v�������Ɏg�p�j
		float fPlayerOldRadian;				//�v���C���[�̈ړ����̊p�x��ێ����遦�P�ʂ̓��W�A���i�����]�������Ɏg�p�j
		int iPlayerNormalDashFlameCount;	//�ʏ�_�b�V�����o�߃t���[�����i�����_�b�V���ւ̈ڍs�Ɏg�p�j

		//�W�����v
		bool bPlayerJumpingFlag; //�v���C���[���W�����v�����̃t���O
		int iPlayerJumpCount;	 //�v���C���[�̌��݂̃W�����v��

		//���
		int iPlayerNowDodgeFlame;			// �v���C���[�̌��݂̉���t���[����
		bool bPlayerDodgingFlag;			//�v���C���[����𒆂��̃t���O
		float fPlayerDodgeProgress;			// �v���C���[������[�V�����i�s�� (�͈́F0.0�`1.0)		
		VECTOR vecPlayerDodgeDirection;		// �v���C���[������
		int iPlayerDodgeWhileJumpingCount;	//�v���C���[�W�����v���̉����
		bool bPlayerAfterDodgeFlag;			//�v���C���[�̉����t���O
		/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ��I�� */
		
		/* �\�͒l�֘A */
		float	fPlayerMoveAcceleration;	// �v���C���[�̈ړ������x
		float	fPlayerMaxMoveSpeed;		// �v���C���[�̍ő�ړ����x
		float	fPlayerFallAcceleration;	// �v���C���[�̗��������x
		float	fPlayerMaxFallSpeed;		// �v���C���[�̍ő嗎�����x
		int		iPlayerMaxJumpCount;		// �v���C���[�̃W�����v��(�ő吔)

		float fPlayerJumpSpeed; //�v���C���[�W�����v���x
		float fPlayerDodgeSpeed; //�v���C���[��𑬓x
		/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ��I�� */
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
