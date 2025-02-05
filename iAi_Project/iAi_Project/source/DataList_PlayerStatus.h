/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��E�֐��C�� */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"

/* �O���Q�� */
// ��AppFrame�Œ�`����Ă��Ȃ��N���X���g�p����ꍇ�A�z�Q�Ƒ΍�Ɏ��{����B
class EnemyBasic;

/* �v���C���[��ԊǗ��N���X�̐錾 */

// �v���C���[��ԊǗ��N���X
class DataList_PlayerStatus : public DataListBase
{
	public:
		DataList_PlayerStatus();			// �R���X�g���N�^
		virtual ~DataList_PlayerStatus();	// �f�X�g���N�^

		/* �f�[�^�擾 */
		// �v���C���[��Ԋ֘A
		int		iGetPlayerMoveState()				{ return this->iPlayerMoveState; }					// �v���C���[�̈ړ���Ԏ擾										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		int		iGetPlayerAttackState()				{ return this->iPlayerAttackState; }				// �v���C���[�̍U����Ԏ擾										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		int		iGetPlayerMotion()					{ return this->iPlayerMotion; }						// �v���C���[�̃��[�V�����擾
		bool	bGetPlayerLandingFlg()				{ return this->bPlayerLandingFlg; }					// �v���C���[���󒆂ɂ��邩�̃t���O�擾
		float	fGetPlayerNowMoveSpeed()			{ return this->fPlayerNowMoveSpeed; }				// �v���C���[�̌��݂̈ړ����x�擾
		float	fGetPlayerAngleX()					{ return this->fPlayerAngleX; }						// �v���C���[��X����]��(���W�A��)�擾
		float	fGetPlayerNowFallSpeed()			{ return this->fPlayerNowFallSpeed; }				// �v���C���[�̌��݂̗������x�擾
		int		iGetPlayerNowJumpCount()			{ return this->iPlayerNowJumpCount; }				// �v���C���[�̃W�����v��(���ݐ�)�擾
		int		iGetPlayerNowAttakChargeFlame()		{ return this->iPlayerNowAttakChargeFlame; }		// �v���C���[�̌��݂̍U���`���[�W�t���[�����擾
		float	fGetPlayerNowMotionCount()			{ return this->fPlayerNowMotionCount; };			// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		VECTOR	vecGetPlayerOldVector()				{ return this->vecPlayerOldVector; }				// �v���C���[�̈ړ����̃x�N�g�����擾�i�W�����v�������Ɏg�p�j		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		float	fGetPlayerOldRadian()				{ return this->fPlayerOldRadian; }					// �v���C���[�̈ړ����̊p�x���擾�i�����]�������Ɏg�p�j				/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerNormalDashFlameCount()	{ return this->iPlayerNormalDashFlameCount; }		// �ʏ�_�b�V�����o�߃t���[�������擾�i�����_�b�V���ւ̈ڍs�Ɏg�p�j	/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerJumpCount()				{ return this->iPlayerJumpCount; }					// �v���C���[�̌��݂̃W�����v�񐔂��擾								/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		bool	bGetPlayerJumpingFlag()				{ return this->bPlayerJumpingFlag; }				// �v���C���[���W�����v�����̃t���O���擾							/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		float	fGetPlayerDodgeProgress()			{ return this->fPlayerDodgeProgress; }				// �v���C���[������[�V�����i�s�����擾								/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		VECTOR	vecGetPlayerDodgeDirection()		{ return this->vecPlayerDodgeDirection; }			// �v���C���[���������擾											/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerDodgeWhileJumpingCount()  { return this->iPlayerDodgeWhileJumpingCount; }		// �v���C���[�W�����v���̉���񐔂��擾								/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		bool	bGetPlayerAfterDodgeFlag()			{ return this->bPlayerAfterDodgeFlag; }				// �v���C���[�̉����t���O���擾									/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		float	fGetPlayerDodgeSpeed()				{ return this->fPlayerDodgeSpeed; }					// �v���C���[��𑬓x���擾											/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerNowDodgeFlame()			{ return this->iPlayerNowDodgeFlame; }				// �v���C���[�̌��݂̉���t���[�������擾							/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		VECTOR	vecGetPlayerChargeAttakTargetMove()	{ return this->vecPlayerChargeAttakTargetMove; }	// �v���C���[���ߍU���̈ړ��ʂ��擾									/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */	/* 2025.01.26 ��򕗏� �R�[�h�C�� */
		int		iGetPlayerChargeAttackCount()		{ return this->iPlayerChargeAttackCount; }			// �v���C���[���ߍU���̃J�E���g���擾
		EnemyBasic* pGetPlayerLockOnEnemy()			{ return this->pLockOnEnemy; }						// ���b�N�I���Ώۂ̃G�l�~�[���擾
		int		iGetPlayerNowHp()					{ return this->iPlayerNowHp; }						// �v���C���[�̌��݂�HP���擾
		int		iGetPlayerNowInvincibleTime()		{ return this->iPlayerNowInvincibleTime; }			// �v���C���[�̌��݂̎c�薳�G���Ԃ��擾

		/* ���菈���p�R���W���� */
		COLLISION_CAPSULE	stGetMeleeSearchCollision()			{ return this->stMeleeSearchCollision; };		// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�������擾
		bool				bGetMeleeSearchCollisionUseFlg()	{ return this->bMeleeSearchCollisionUseFlg; };	// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�����g�p�t���O���擾

		// �\�͒l�֘A���v���C���[�̑������ɂ���ď㉺����\���̂���X�e�[�^�X)
		float	fGetPlayerMoveAcceleration()	{ return this->fPlayerMoveAcceleration; }	// �v���C���[�̈ړ������x�擾
		float	fGetPlayerMaxMoveSpeed()		{ return this->fPlayerMaxMoveSpeed; }		// �v���C���[�̍ő�ړ����x�擾
		float	fGetPlayerFallAcceleration()	{ return this->fPlayerFallAcceleration; }	// �v���C���[�̗��������x�擾
		float	fGetPlayerMaxFallSpeed()		{ return this->fPlayerMaxFallSpeed; }		// �v���C���[�̍ő嗎�����x�擾
		int		iGetPlayerMaxJumpCount()		{ return this->iPlayerMaxJumpCount; }		// �v���C���[�̃W�����v��(�ő吔)�擾
		float	fGetPlayerRockOnRadius()		{ return this->fPlayerRockOnRadius; }		// ���b�N�I���͈͂̔��a��ݒ�
		int		iGetPlayerMaxHp()				{ return this->iPlayerMaxHp; }				// �v���C���[�̍ő�HP�擾
		int		iGetPlayerMaxInvincibleTime()	{ return this->iPlayerMaxInvincibleTime; }	// �v���C���[�̍ő喳�G���Ԏ擾

		// �J�����֘A
		int		iGetCameraMode()							{ return this->iCameraMode; }							// �J�������[�h�擾
		int		iGetCameraMode_Old()						{ return this->iCameraMode_Old; }						// �J�������[�h�擾(�ύX�O)
		VECTOR	vecGetCameraUp()							{ return this->vecCameraUp; }							// �J�����̏�����擾
		VECTOR	vecGetCameraPosition()						{ return this->vecCameraPosition; }						// �J�����̍��W�擾(���ݒn�_)
		VECTOR	vecGetCameraPosition_Start()				{ return this->vecCameraPosition_Start; }				// �J�����̍��W�擾(�ړ��O�n�_)
		VECTOR	vecGetCameraPosition_Target()				{ return this->vecCameraPosition_Target; }				// �J�����̍��W�擾(�ړ���n�_)
		int		iGetCameraPositionLeapCount()				{ return this->iCameraPositionLeapCount; }				// �J�������W�̐��`�ۊǗp�J�E���g�擾
		VECTOR	vecGetCameraTarget()						{ return this->vecCameraTarget; }						// �J�����̒����_�擾
		float	fGetCameraRadius()							{ return this->fCameraRadius; }							// �J�����̒��S�_����̋����擾
		float	fGetCameraAngleX()							{ return this->fCameraAngleX; }							// �J������X����]��(���W�A��)�擾
		float	fGetCameraAngleY()							{ return this->fCameraAngleY; }							// �J������Y����]��(���W�A��)�擾
		float	fGetCameraRotationalSpeed_Controller()		{ return this->fCameraRotationalSpeed_Controller; }		// �J�����̉�]���x(�R���g���[���[)�擾
		float	fGetCameraRotationalSpeed_Mouse()			{ return this->fCameraRotationalSpeed_Mouse; }			// �J�����̉�]���x(�}�E�X)�擾
		float	fGetCameraAngleLimitUp()					{ return this->fCameraAngleLimitUp; }					// �J�����̉�]�p�x�����擾(��)
		float	fGetCameraAngleLimitDown()					{ return this->fCameraAngleLimitDown; }					// �J�����̉�]�p�x�����擾(��)

		/* �f�[�^�ݒ� */
		// �v���C���[��Ԋ֘A
		void	SetPlayerMoveState(int iPlayerMoveState)							{ this->iPlayerMoveState				= iPlayerMoveState; }					// �v���C���[�̈ړ���Ԑݒ�					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		void	SetPlayerAttackState(int iPlayerAttackState)						{ this->iPlayerAttackState				= iPlayerAttackState; }					// �v���C���[�̍U����Ԑݒ�					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		void	SetPlayerMotion(int iPlayerMotion)									{ this->iPlayerMotion					= iPlayerMotion; };						// �v���C���[�̃��[�V�����ݒ�
		void	SetPlayerLanding(bool bPlayerLanding)								{ this->bPlayerLandingFlg				= bPlayerLanding; }						// �v���C���[���󒆂ɂ��邩�̃t���O�ݒ�
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)					{ this->fPlayerNowMoveSpeed				= fPlayerNowMoveSpeed; }				// �v���C���[�̌��݂̈ړ����x�ݒ�
		void	SetPlayerAngleX(float fPlayerAngleX)								{ this->fPlayerAngleX					= fPlayerAngleX; }						// �v���C���[��X����]��(���W�A��)�擾
		void	SetPlayerNowFallSpeed(float fPlayerNowFallSpeed)					{ this->fPlayerNowFallSpeed				= fPlayerNowFallSpeed; }				// �v���C���[�̌��݂̗������x�ݒ�
		void	SetPlayerNowJumpCount(int iPlayerNowJumpCount)						{ this->iPlayerNowJumpCount				= iPlayerNowJumpCount; }				// �v���C���[�̃W�����v��(���ݐ�)�ݒ�
		void	SetPlayerNormalDashFlameCount(int iPlayerNormalDashFlameCount)		{ this->iPlayerNormalDashFlameCount		= iPlayerNormalDashFlameCount; }		// �ʏ�_�b�V�����o�߃t���[������ݒ�
		void	SetPlayerNowAttakChargeFlame(int iPlayerNowAttakChargeFlame)		{ this->iPlayerNowAttakChargeFlame		= iPlayerNowAttakChargeFlame; }			// �v���C���[�̌��݂̍U���`���[�W�t���[�����ݒ�
		void	SetPlayerNowMotionCount(float fPlayerNowMotionCount)				{ this->fPlayerNowMotionCount			= fPlayerNowMotionCount; };				// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		void	SetPlayerJumpCount(int iPlayerJumpCount)							{ this->iPlayerJumpCount				= iPlayerJumpCount; }					// �v���C���[�W�����v�񐔂�ݒ�				/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerJumpingFlag(bool bPlayerJumpingFlag)						{ this->bPlayerJumpingFlag				= bPlayerJumpingFlag; }					// �v���C���[���W�����v�����̃t���O��ݒ�	/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeProgress(float fPlayerDodgeProgress)					{ this->fPlayerDodgeProgress			= fPlayerDodgeProgress; }				// �v���C���[������[�V�����i�s����ݒ�		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeDirection(VECTOR vecPlayerDodgeDirection)				{ this->vecPlayerDodgeDirection			= vecPlayerDodgeDirection; }			// �v���C���[��������ݒ�					/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeWhileJumpingCount(int iPlayerDodgeWhileJumpingCount)  { this->iPlayerDodgeWhileJumpingCount	= iPlayerDodgeWhileJumpingCount; }		// �v���C���[�W�����v���̉���񐔂�ݒ�		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerAfterDodgeFlag(bool bPlayerAfterDodgeFlag)					{ this->bPlayerAfterDodgeFlag			= bPlayerAfterDodgeFlag; }				// �v���C���[�̉����t���O��ݒ�			/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerLockOnEnemy(EnemyBasic* pLockOnEnemy)						{ this->pLockOnEnemy					= pLockOnEnemy; };						// ���b�N�I���Ώۂ̃G�l�~�[��ݒ�
		void	SetPlayerNowHp(int iPlayerNowHp)									{ this->iPlayerNowHp					= iPlayerNowHp; }						// �v���C���[�̌��݂�HP��ݒ�
		void	SetPlayerNowInvincibleTime(int iPlayerNowInvincibleTime)			{ this->iPlayerNowInvincibleTime		= iPlayerNowInvincibleTime; }			// �v���C���[�̌��݂̎c�薳�G���Ԃ�ݒ�

		/* ���菈���p�R���W���� */
		void	SetMeleeSearchCollision(COLLISION_CAPSULE stMeleeSearchCollision)	{ this->stMeleeSearchCollision			= stMeleeSearchCollision; }				// �ߐڍU��(��)�̃��b�N�I���͈̓R���W������ݒ�
		void	SetMeleeSearchCollisionUseFlg(bool bMeleeSearchCollisionUseFlg)		{ this->bMeleeSearchCollisionUseFlg		= bMeleeSearchCollisionUseFlg; }		// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�����g�p�t���O��ݒ�

		// �\�͒l�֘A(���v���C���[�̑������ɂ���ď㉺����\���̂���X�e�[�^�X)
		void	SetPlayerMoveAcceleration(float fPlayerMoveAcceleration)				{ this->fPlayerMoveAcceleration			= fPlayerMoveAcceleration; }		// �v���C���[�̈ړ������x�ݒ�
		void	SetPlayerMaxMoveSpeed(float fPlayerMaxMoveSpeed)						{ this->fPlayerMaxMoveSpeed				= fPlayerMaxMoveSpeed;}				// �v���C���[�̍ő�ړ����x�ݒ�
		void	SetPlayerFallAcceleration(float fPlayerFallAcceleration)				{ this->fPlayerFallAcceleration			= fPlayerFallAcceleration; }		// �v���C���[�̗��������x�ݒ�
		void	SetPlayerMaxFallSpeed(float fPlayerMaxFallSpeed)						{ this->fPlayerMaxFallSpeed				= fPlayerMaxFallSpeed; }			// �v���C���[�̍ő嗎�����x�ݒ�
		void	SetPlayerMaxJumpCount(int iPlayerMaxJumpCount)							{ this->iPlayerMaxJumpCount				= iPlayerMaxJumpCount; }			// �v���C���[�̃W�����v��(�ő吔)�ݒ�
		void	SetPlayerDodgeSpeed(float fPlayerDodgeSpeed)							{ this->fPlayerDodgeSpeed				= fPlayerDodgeSpeed; }				// �v���C���[��𑬓x��ݒ�				/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerNowDodgeFlame(int iPlayerNowDodgeFlame)						{ this->iPlayerNowDodgeFlame			= iPlayerNowDodgeFlame; }			// �v���C���[������Ԃ�ݒ�				/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */		
		void	SetPlayerChargeAttakTargetMove(VECTOR vecPlayerChargeAttakTargetMove)	{ this->vecPlayerChargeAttakTargetMove	= vecPlayerChargeAttakTargetMove; }	// �v���C���[���ߍU���̈ړ��ʂ�ݒ�		/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */	/* 2025.01.26 ��򕗏� �R�[�h�C�� */
		void	SetPlayerChargeAttackCount(int iPlayerChargeAttackCount)				{ this->iPlayerChargeAttackCount		= iPlayerChargeAttackCount;}		// �ߐڍU��(��)�̃J�E���g��ݒ�
		void	SetPlayerRockOnRadius(float fPlayerRockOnRadius)						{ this->fPlayerRockOnRadius				= fPlayerRockOnRadius; }			// ���b�N�I���͈͂̔��a��ݒ�
		void	SetPlayerMaxHp(int iPlayerMaxHp)										{ this->iPlayerMaxHp					= iPlayerMaxHp; }					// �v���C���[�̍ő�HP�ݒ�
		void	SetPlayerMaxInvincibleTime(int iPlayerMaxInvincibleTime)				{ this->iPlayerMaxInvincibleTime		= iPlayerMaxInvincibleTime; }		// �v���C���[�̍ő喳�G���Ԑݒ�

		// �J�����֘A
		void	SetCameraMode(int iCameraMode)										{ this->iCameraMode							= iCameraMode; }				// �J�������[�h�ݒ�
		void	SetCameraMode_Old(int iCameraMode_Old)								{ this->iCameraMode_Old						= iCameraMode_Old; }			// �J�������[�h(�ύX�O)�ݒ�
		void	SetCameraUp(VECTOR vecCameraUp)										{ this->vecCameraUp							= vecCameraUp; }				// �J�����̏�����ݒ�
		void	SetCameraPosition(VECTOR vecCameraPosition)							{ this->vecCameraPosition					= vecCameraPosition; }			// �J�����̍��W�ݒ�(���ݒn�_)
		void	SetCameraPosition_Start(VECTOR vecCameraPosition_Start)				{ this->vecCameraPosition_Start				= vecCameraPosition_Start; }	// �J�����̍��W�ݒ�(�ړ��O�n�_)
		void	SetCameraPosition_Target(VECTOR vecCameraPosition_Target)			{ this->vecCameraPosition_Target			= vecCameraPosition_Target; }	// �J�����̍��W�ݒ�(�ړ���n�_)
		void	SetCameraPositionLeapCount(int iCameraPositionLeapCount)			{ this->iCameraPositionLeapCount			= iCameraPositionLeapCount; }	// �J�������W�̐��`�ۊǗp�J�E���g�ݒ�
		void	SetCameraTarget(VECTOR vecCameraTarget)								{ this->vecCameraTarget						= vecCameraTarget; }			// �J�����̒����_�ݒ�
		void	SetCameraRadius(float fCameraRadius)								{ this->fCameraRadius						= fCameraRadius; }				// �J�����̒��S�_����̋����ݒ�
		void	SetCameraAngleX(float fCameraAngleX)								{ this->fCameraAngleX						= fCameraAngleX; }				// �J������X����]��(���W�A��)�ݒ�
		void	SetCameraAngleY(float fCameraAngleY)								{ this->fCameraAngleY						= fCameraAngleY; }				// �J������Y����]��(���W�A��)�ݒ�
		void	SetCameraRotationalSpeed_Controller(float fCameraRotationalSpeed)	{ this->fCameraRotationalSpeed_Controller	= fCameraRotationalSpeed; }		// �J�����̉�]���x(�R���g���[���[)�ݒ�
		void	SetCameraRotationalSpeed_Mouse(float fCameraRotationalSpeed)		{ this->fCameraRotationalSpeed_Mouse		= fCameraRotationalSpeed; }		// �J�����̉�]���x(�}�E�X)�ݒ�
		void	SetCameraAngleLimitUp(float fCameraAngleupsideLimitUp)				{ this->fCameraAngleLimitUp					= fCameraAngleLimitUp; }		// �J�����̉�]�p�x�����ݒ�(��)
		void	SetCameraAngleLimitDown(float fCameraAngleupsideLimitDown)			{ this->fCameraAngleLimitDown				= fCameraAngleLimitDown; }		// �J�����̉�]�p�x�����ݒ�(��)

		/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ��J�n */
		//�U��
		VECTOR vecPlayerChargeAttakPoint;	//�v���C���[���ߍU���̖ړI�n
		VECTOR vecPlayerChargeAttakVector;	//�v���C���[���ߍU���̕���
		int iPlayerNowAttakChargeFlame;		//���݂̃v���C���[���ߍU���`���[�W�t���[����
		/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ��I�� */

	private:
		/* �v���C���[��Ԋ֘A */
		int		iPlayerMoveState;				// �v���C���[�̈ړ����(�A�N�V����)										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��C�� */
		int		iPlayerAttackState;				// �v���C���[�̍U�����(�A�N�V����)										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��C�� */
		int		iPlayerMotion;					// �v���C���[�̏��(���[�V����)
		bool	bPlayerLandingFlg;				// �v���C���[�����n���Ă��邩�̃t���O
		float	fPlayerNowMoveSpeed;			// �v���C���[�̌��݂̈ړ����x
		float	fPlayerAngleX;					// �v���C���[��X����]��(���W�A��)
		float	fPlayerNowFallSpeed;			// �v���C���[�̌��݂̗������x
		int		iPlayerNowJumpCount;			// �v���C���[�̃W�����v��(���ݐ�)
		float	fPlayerNowMotionCount;			// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		VECTOR	vecPlayerOldVector;				// �v���C���[�̈ړ����̃x�N�g����ۑ�����i�W�����v�������Ɏg�p�j				/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerOldRadian;				// �v���C���[�̈ړ����̊p�x��ێ����遦�P�ʂ̓��W�A���i�����]�������Ɏg�p�j		/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerNormalDashFlameCount;	// �ʏ�_�b�V�����o�߃t���[�����i�����_�b�V���ւ̈ڍs�Ɏg�p�j					/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerJumpingFlag;				// �v���C���[���W�����v�����̃t���O												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerJumpCount;				// �v���C���[�̌��݂̃W�����v��												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerNowDodgeFlame;			// �v���C���[�̌��݂̉���t���[����												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerDodgeProgress;			// �v���C���[������[�V�����i�s�� (�͈́F0.0�`1.0)								/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		VECTOR	vecPlayerDodgeDirection;		// �v���C���[������															/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerDodgeWhileJumpingCount;	// �v���C���[�W�����v���̉����												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerAfterDodgeFlag;			// �v���C���[�̉����t���O														/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		VECTOR	vecPlayerChargeAttakTargetMove;	// �ߐڍU��(��)�ɂ��ړ���														/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */	/* 2025.01.26 ��򕗏� �R�[�h�C�� */
		int		iPlayerChargeAttackCount;		// �ߐڍU��(��)�̃J�E���g
		EnemyBasic*	pLockOnEnemy;				// ���b�N�I���Ώۂ̃G�l�~�[
		int		iPlayerNowHp;					// �v���C���[�̌��݂�HP
		int		iPlayerNowInvincibleTime;		// �v���C���[�̌��݂̎c�薳�G����

		/* ���菈���p�R���W���� */
		COLLISION_CAPSULE	stMeleeSearchCollision;			// �ߐڍU��(��)�̃��b�N�I���͈̓R���W����
		bool				bMeleeSearchCollisionUseFlg;	// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�����g�p�t���O
		
		/* �\�͒l�֘A(���v���C���[�̑������ɂ���ď㉺����\���̂���X�e�[�^�X))*/
		float	fPlayerMoveAcceleration;		// �v���C���[�̈ړ������x
		float	fPlayerMaxMoveSpeed;			// �v���C���[�̍ő�ړ����x
		float	fPlayerFallAcceleration;		// �v���C���[�̗��������x
		float	fPlayerMaxFallSpeed;			// �v���C���[�̍ő嗎�����x
		int		iPlayerMaxJumpCount;			// �v���C���[�̃W�����v��(�ő吔)
		float	fPlayerJumpSpeed;				// �v���C���[�W�����v���x				/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerDodgeSpeed;				// �v���C���[��𑬓x					/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerRockOnRadius;			// ���b�N�I���͈͂̔��a
		int		iPlayerMaxHp;					// �v���C���[�̍ő�HP
		int		iPlayerMaxInvincibleTime;		// �v���C���[�̍ő喳�G����

		/* �J�����֘A */
		int		iCameraMode;						// �J�������[�h
		int		iCameraMode_Old;					// �J�������[�h(�ύX�O)
		VECTOR	vecCameraUp;						// �J�����̏����
		VECTOR	vecCameraPosition;					// �J�����̍��W(���ݒn�_)
		VECTOR	vecCameraPosition_Start;			// �J�����̍��W(�ړ��O�n�_)
		VECTOR	vecCameraPosition_Target;			// �J�����̍��W(�ړ���n�_)
		int		iCameraPositionLeapCount;			// �J�������W�̐��`�ۊǗp�J�E���g
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
