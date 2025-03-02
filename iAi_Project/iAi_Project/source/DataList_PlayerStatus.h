/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��E�֐��C�� */
/* 2025.02.10 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.11 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.26 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */


#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"
#include "PlayerMotionDefine.h"

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
		bool	bGetPlayerLandingFlg()				{ return this->bPlayerLandingFlg; }					// �v���C���[���󒆂ɂ��邩�̃t���O�擾
		float	fGetPlayerNowMoveSpeed()			{ return this->fPlayerNowMoveSpeed; }				// �v���C���[�̌��݂̈ړ����x�擾
		float	fGetPlayerAngleX()					{ return this->fPlayerAngleX; }						// �v���C���[��X����]��(���W�A��)�擾
		float	fGetPlayerTurnSpeed()				{ return this->fPlayerTurnSpeed; }					// �v���C���[�̉�]���x�擾										/* 2025.02.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		float	fGetPlayerNowFallSpeed()			{ return this->fPlayerNowFallSpeed; }				// �v���C���[�̌��݂̗������x�擾
		int		iGetPlayerNowJumpCount()			{ return this->iPlayerNowJumpCount; }				// �v���C���[�̃W�����v��(���ݐ�)�擾
		int		iGetPlayerNowAttakChargeFlame()		{ return this->iPlayerNowAttakChargeFlame; }		// �v���C���[�̌��݂̍U���`���[�W�t���[�����擾
		float	fGetPlayerNowMotionCount()			{ return this->fPlayerNowMotionCount; };			// �v���C���[�̃��[�V�����̌��݂̃J�E���g
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
		int		iGetPlayerMeleeStrongAirMaxCount()	{ return this->iPlayerMeleeStrongAirMaxCount; }		// �v���C���[���󒆂ŋߋ����U��(��)���s���ő吔(���G���U�����Ă��Ȃ��ꍇ)���擾		/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetPlayerMeleeStrongAirCount()		{ return this->iPlayerMeleeStrongAirCount; }		// �v���C���[���󒆂ŋߋ����U��(��)���s�����񐔂��擾								/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		bool	bGetPlayerKickWallFlg()				{ return this->bPlayerKickWallFlg; }				// �v���C���[���ǂ��R�������̃t���O���擾							/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerAfterKickWallCount()		{ return this->iPlayerAfterKickWallCount; }			// �v���C���[���ǂ��R������̃J�E���g���擾							/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		bool	bGetPlayerAfterKickWallFlg()		{ return this->bPlayerAfterKickWallFlg; }			// �v���C���[���ǂ��R������̃t���O���擾							/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerMeleeStrongChargeCount()	{ return this->iPlayerMeleeStrongChargeCount; }		// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[�������擾
		EnemyBasic* pGetPlayerLockOnEnemy()			{ return this->pLockOnEnemy; }						// ���b�N�I���Ώۂ̃G�l�~�[���擾
		int		iGetPlayerNowHp()					{ return this->iPlayerNowHp; }						// �v���C���[�̌��݂�HP���擾
		int		iGetPlayerNowInvincibleTime()		{ return this->iPlayerNowInvincibleTime; }			// �v���C���[�̌��݂̎c�薳�G���Ԃ��擾
		int		iGetPlayerComboNowCount()			{ return this->iPlayerComboNowCount; }				// �v���C���[�̌��݂̃R���{�����擾
		int		iGetPlayerComboMaxCount()			{ return this->iPlayerComboMaxCount; }				// �v���C���[�̍ő�R���{�����擾
		int		iGetPlayerComboDuration()			{ return this->iPlayerComboDuration; }				// �v���C���[�̃R���{�̎c�莝�����Ԃ��擾
		bool	bGetPlayerAimCancelledFlg()			{ return this->bPlayerAimCancelledFlg; }			// �������U��(�\��)���L�����Z�����ꂽ���̃t���O���擾				/* 2025.02.11 �e�r�듹 �U���֘A�̊֐��ǉ� */
		bool	bGetPlayerDeadFlg()					{ return this->bPlayerDeadFlg; }					// �v���C���[���S�t���O���擾
		int		iGetPlayerDamageCount()				{ return this->iPlayerDamageCount; }				// �v���C���[�̔�_���[�W�����擾

		/* �v���C���[���[�V�����֘A */
		int		iGetPlayerMotion_Move()					{ return this->iPlayerMotion_Move; }				// �v���C���[���[�V����(�ړ��n)���擾
		int		iGetPlayerMotion_Move_Old()				{ return this->iPlayerMotion_Move_Old; }			// �ύX�O�v���C���[���[�V����(�ړ��n)���擾
		int		iGetPlayerMotion_Attack()				{ return this->iPlayerMotion_Attack; }				// �v���C���[���[�V����(�U���n)���擾
		int		iGetPlayerMotion_Attack_Old()			{ return this->iPlayerMotion_Attack_Old; }			// �ύX�O�v���C���[���[�V����(�U���n)���擾
		float	fGetMotionTimer_Move()					{ return this->fMotionTimer_Move; }					// ���[�V�����J�E���g(�ړ��n)���擾
		float	fGetMotionTimer_Move_End()				{ return this->fMotionTimer_Move_End; }				// ���[�V�����J�E���g(�ړ��n/�I������)���擾
		float	fGetMotionTimer_Attack()				{ return this->fMotionTimer_Attack; }				// ���[�V�����J�E���g(�U���n)���擾
		float	fGetMotionTimer_Attack_End()			{ return this->fMotionTimer_Attack_End; }			// ���[�V�����J�E���g(�U���n/�I������)���擾
		int		iGetPlayerMotionAttachIndex_Move()		{ return this->iPlayerMotionAttachIndex_Move; }		// �v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		int		iGetPlayerMotionAttachIndex_Attack()	{ return this->iPlayerMotionAttachIndex_Attack; }	// �v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�

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

		/* �f�[�^�ݒ� */
		// �v���C���[��Ԋ֘A
		void	SetPlayerMoveState(int iPlayerMoveState)							{ this->iPlayerMoveState				= iPlayerMoveState; }					// �v���C���[�̈ړ���Ԑݒ�					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		void	SetPlayerAttackState(int iPlayerAttackState)						{ this->iPlayerAttackState				= iPlayerAttackState; }					// �v���C���[�̍U����Ԑݒ�					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		void	SetPlayerLanding(bool bPlayerLanding)								{ this->bPlayerLandingFlg				= bPlayerLanding; }						// �v���C���[���󒆂ɂ��邩�̃t���O�ݒ�
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)					{ this->fPlayerNowMoveSpeed				= fPlayerNowMoveSpeed; }				// �v���C���[�̌��݂̈ړ����x�ݒ�
		void	SetPlayerAngleX(float fPlayerAngleX)								{ this->fPlayerAngleX					= fPlayerAngleX; }						// �v���C���[��X����]��(���W�A��)�擾
		void	SetPlayerTurnSpeed(float fPlayerTurnSpeed)							{ this->fPlayerTurnSpeed				= fPlayerTurnSpeed; }					// �v���C���[�̉�]���x�ݒ�					/* 2025.02.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerNowFallSpeed(float fPlayerNowFallSpeed)					{ this->fPlayerNowFallSpeed				= fPlayerNowFallSpeed; }				// �v���C���[�̌��݂̗������x�ݒ�
		void	SetPlayerNowJumpCount(int iPlayerNowJumpCount)						{ this->iPlayerNowJumpCount				= iPlayerNowJumpCount; }				// �v���C���[�̃W�����v��(���ݐ�)�ݒ�
		void	SetPlayerNormalDashFlameCount(int iPlayerNormalDashFlameCount)		{ this->iPlayerNormalDashFlameCount		= iPlayerNormalDashFlameCount; }		// �ʏ�_�b�V�����o�߃t���[������ݒ�
		void	SetPlayerNowAttakChargeFlame(int iPlayerNowAttakChargeFlame)		{ this->iPlayerNowAttakChargeFlame		= iPlayerNowAttakChargeFlame; }			// �v���C���[�̌��݂̍U���`���[�W�t���[�����ݒ�
		void	SetPlayerMeleeStrongAirCount(int iPlayerMeleeStrongAirCount)		{ this->iPlayerMeleeStrongAirCount		= iPlayerMeleeStrongAirCount; }			// �v���C���[���󒆂ŋߋ����U��(��)���s�����񐔂�ݒ�		/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerNowMotionCount(float fPlayerNowMotionCount)				{ this->fPlayerNowMotionCount			= fPlayerNowMotionCount; };				// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		void	SetPlayerJumpCount(int iPlayerJumpCount)							{ this->iPlayerJumpCount				= iPlayerJumpCount; }					// �v���C���[�W�����v�񐔂�ݒ�				/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerJumpingFlag(bool bPlayerJumpingFlag)						{ this->bPlayerJumpingFlag				= bPlayerJumpingFlag; }					// �v���C���[���W�����v�����̃t���O��ݒ�	/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeProgress(float fPlayerDodgeProgress)					{ this->fPlayerDodgeProgress			= fPlayerDodgeProgress; }				// �v���C���[������[�V�����i�s����ݒ�		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeDirection(VECTOR vecPlayerDodgeDirection)				{ this->vecPlayerDodgeDirection			= vecPlayerDodgeDirection; }			// �v���C���[��������ݒ�					/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeWhileJumpingCount(int iPlayerDodgeWhileJumpingCount)  { this->iPlayerDodgeWhileJumpingCount	= iPlayerDodgeWhileJumpingCount; }		// �v���C���[�W�����v���̉���񐔂�ݒ�		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerAfterDodgeFlag(bool bPlayerAfterDodgeFlag)					{ this->bPlayerAfterDodgeFlag			= bPlayerAfterDodgeFlag; }				// �v���C���[�̉����t���O��ݒ�			/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerKickWallFlg(bool bPlayerKickWallFlg)						{ this->bPlayerKickWallFlg = bPlayerKickWallFlg; }								// �v���C���[���ǂ��R�������̃t���O��ݒ�	/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerAfterKickWallCount(int iPlayerAfterKickWallCount)			{ this->iPlayerAfterKickWallCount = iPlayerAfterKickWallCount; }				// �v���C���[���ǂ��R������̃J�E���g��ݒ�	/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerAfterKickWallFlg(bool bPlayerAfterKickWallFlg)				{ this->bPlayerAfterKickWallFlg = bPlayerAfterKickWallFlg; }					// �v���C���[���ǂ��R������̃t���O��ݒ�	/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerLockOnEnemy(EnemyBasic* pLockOnEnemy)						{ this->pLockOnEnemy					= pLockOnEnemy; };						// ���b�N�I���Ώۂ̃G�l�~�[��ݒ�
		void	SetPlayerNowHp(int iPlayerNowHp)									{ this->iPlayerNowHp					= iPlayerNowHp; }						// �v���C���[�̌��݂�HP��ݒ�
		void	SetPlayerNowInvincibleTime(int iPlayerNowInvincibleTime)			{ this->iPlayerNowInvincibleTime		= iPlayerNowInvincibleTime; }			// �v���C���[�̌��݂̎c�薳�G���Ԃ�ݒ�
		void	SetPlayerComboNowCount(int iPlayerComboNowCount)					{ this->iPlayerComboNowCount			= iPlayerComboNowCount; }				// �v���C���[�̌��݂̃R���{����ݒ�
		void	SetPlayerComboMaxCount(int iPlayerComboMaxCount)					{ this->iPlayerComboMaxCount			= iPlayerComboMaxCount; }				// �v���C���[�̍ő�R���{����ݒ�
		void	SetPlayerComboDuration(int iPlayerComboDuration)					{ this->iPlayerComboDuration			= iPlayerComboDuration; }				// �v���C���[�̃R���{�̎c�莝�����Ԃ�ݒ�
		void	SetPlayerAimCancelledFlg(bool bPlayerAimCancelledFlg)				{ this->bPlayerAimCancelledFlg			= bPlayerAimCancelledFlg; }				// �������U��(�\��)���L�����Z�����ꂽ���̃t���O��ݒ�	/* 2025.02.11 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerDeadFlg(bool bPlayerDeadFlg)								{ this->bPlayerDeadFlg					= bPlayerDeadFlg; }						// �v���C���[���S�t���O
		void	SetPlayerDamageCount(int iPlayerDamageCount)						{ this->iPlayerDamageCount				= iPlayerDamageCount; }					// �v���C���[�̔�_���[�W����ݒ�

		/* �v���C���[���[�V�����֘A */
		void	SetPlayerMotion_Move(int iPlayerMotion_Move)							{ this->iPlayerMotion_Move				= iPlayerMotion_Move; };				// �v���C���[���[�V����(�ړ��n)��ݒ�
		void	SetPlayerMotion_Move_Old(int iPlayerMotion_Move_Old)					{ this->iPlayerMotion_Move_Old			= iPlayerMotion_Move_Old; };			// �ύX�O�v���C���[���[�V����(�ړ��n)��ݒ�
		void	SetPlayerMotion_Attack(int iPlayerMotion_Attack)						{ this->iPlayerMotion_Attack			= iPlayerMotion_Attack; };				// �v���C���[���[�V����(�U���n)��ݒ�
		void	SetPlayerMotion_Attack_Old(int iPlayerMotion_Attack_Old)				{ this->iPlayerMotion_Attack_Old		= iPlayerMotion_Attack_Old; };			// �ύX�O�v���C���[���[�V����(�U���n)��ݒ�
		void	SetMotionCount_Move(float fMotionCount_Move)							{ this->fMotionTimer_Move				= fMotionCount_Move; };					// ���[�V�����J�E���g(�ړ��n)
		void	SetMotionCount_Move_End(float fMotionCount_Move_End)					{ this->fMotionTimer_Move_End			= fMotionCount_Move_End; };				// ���[�V�����J�E���g(�ړ��n/�I������)��ݒ�
		void	SetMotionCount_Attack(float fMotionCount_Attack)						{ this->fMotionTimer_Attack				= fMotionCount_Attack; };				// ���[�V�����J�E���g(�U���n)��ݒ�
		void	SetMotionCount_Attack_End(float fMotionCount_Attack_End)				{ this->fMotionTimer_Attack_End			= fMotionCount_Attack_End; };			// ���[�V�����J�E���g(�U���n/�I������)��ݒ�
		void	SetPlayerMotionAttachIndex_Move(int iPlayerMotionAttachIndex_Move)		{ this->iPlayerMotionAttachIndex_Move	= iPlayerMotionAttachIndex_Move; }		// �v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		void	SetPlayerMotionAttachIndex_Attack(int iPlayerMotionAttachIndex_Attack)	{ this->iPlayerMotionAttachIndex_Attack	= iPlayerMotionAttachIndex_Attack; }	// �v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�

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
		void	SetPlayerMeleeStrongAirMaxCount(int iPlayerMeleeStrongAirMaxCount)		{ this->iPlayerMeleeStrongAirMaxCount	= iPlayerMeleeStrongAirMaxCount; }	// �v���C���[���󒆂ŋߋ����U��(��)���s���ő吔(���G���U�����Ă��Ȃ��ꍇ)��ݒ�				/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongChargeCount(int iPlayerMeleeStrongChargeCount)		{ this->iPlayerMeleeStrongChargeCount	= iPlayerMeleeStrongChargeCount;}	// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[������ݒ�
		void	SetPlayerRockOnRadius(float fPlayerRockOnRadius)						{ this->fPlayerRockOnRadius				= fPlayerRockOnRadius; }			// ���b�N�I���͈͂̔��a��ݒ�
		void	SetPlayerMaxHp(int iPlayerMaxHp)										{ this->iPlayerMaxHp					= iPlayerMaxHp; }					// �v���C���[�̍ő�HP�ݒ�
		void	SetPlayerMaxInvincibleTime(int iPlayerMaxInvincibleTime)				{ this->iPlayerMaxInvincibleTime		= iPlayerMaxInvincibleTime; }		// �v���C���[�̍ő喳�G���Ԑݒ�

	private:
		/* �v���C���[��Ԋ֘A */
		int		iPlayerMoveState;				// �v���C���[�̈ړ����(�A�N�V����)										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��C�� */
		int		iPlayerAttackState;				// �v���C���[�̍U�����(�A�N�V����)										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��C�� */
		bool	bPlayerLandingFlg;				// �v���C���[�����n���Ă��邩�̃t���O
		float	fPlayerNowMoveSpeed;			// �v���C���[�̌��݂̈ړ����x
		float	fPlayerAngleX;					// �v���C���[��X����]��(���W�A��)
		float	fPlayerTurnSpeed;				// �v���C���[�̕����]���̑��x�i�͈́F0.0?1.0�j								/* 2025.02.10 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerNowFallSpeed;			// �v���C���[�̌��݂̗������x
		int		iPlayerNowJumpCount;			// �v���C���[�̃W�����v��(���ݐ�)
		float	fPlayerNowMotionCount;			// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		int		iPlayerNormalDashFlameCount;	// �ʏ�_�b�V�����o�߃t���[�����i�����_�b�V���ւ̈ڍs�Ɏg�p�j					/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerJumpingFlag;				// �v���C���[���W�����v�����̃t���O												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerJumpCount;				// �v���C���[�̌��݂̃W�����v��												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerNowDodgeFlame;			// �v���C���[�̌��݂̉���t���[����												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerDodgeProgress;			// �v���C���[������[�V�����i�s�� (�͈́F0.0�`1.0)								/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		VECTOR	vecPlayerDodgeDirection;		// �v���C���[������															/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerDodgeWhileJumpingCount;	// �v���C���[�W�����v���̉����												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerAfterDodgeFlag;			// �v���C���[�̉����t���O														/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerKickWallFlg;				// �v���C���[���ǂ��R�������̃t���O												/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerAfterKickWallCount;		// �v���C���[���ǂ��R���Ă���̌o�߃t���[����									/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerAfterKickWallFlg;		// �v���C���[���ǂ��R������̏�Ԃ��̃t���O										/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		VECTOR	vecPlayerChargeAttakTargetMove;	// �ߐڍU��(��)�ɂ��ړ���														/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */	/* 2025.01.26 ��򕗏� �R�[�h�C�� */
		int		iPlayerNowAttakChargeFlame;		//���݂̃v���C���[���ߍU���`���[�W�t���[����									/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerMeleeStrongChargeCount;	// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[����
		int		iPlayerMeleeStrongAirCount;		// �v���C���[���󒆂ŋߋ����U��(��)���s������(���G���U�����Ă��Ȃ��ꍇ)		/* 2025.02.26 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		EnemyBasic*	pLockOnEnemy;				// ���b�N�I���Ώۂ̃G�l�~�[
		int		iPlayerNowHp;					// �v���C���[�̌��݂�HP
		int		iPlayerNowInvincibleTime;		// �v���C���[�̌��݂̎c�薳�G����
		int		iPlayerComboNowCount;			// �v���C���[�̌��݂̃R���{��
		int		iPlayerComboMaxCount;			// �v���C���[�̍ő�R���{��
		int		iPlayerComboDuration;			// �v���C���[�̃R���{�̎c�莝������
		bool	bPlayerAimCancelledFlg;			// �������U��(�\��)���L�����Z�����ꂽ���̃t���O
		bool	bPlayerDeadFlg;					// �v���C���[���S�t���O
		int		iPlayerDamageCount;				// ��_���[�W��

		/* �v���C���[���[�V�����֘A */
		int		iPlayerMotion_Move;					// �v���C���[���[�V����(�ړ��n)
		int		iPlayerMotion_Move_Old;				// �ύX�O�v���C���[���[�V����(�ړ��n)
		int		iPlayerMotion_Attack;				// �v���C���[���[�V����(�U���n)
		int		iPlayerMotion_Attack_Old;			// �ύX�O�v���C���[���[�V����(�U���n)
		float	fMotionTimer_Move;					// ���[�V�����^�C�}�[(�ړ��n)
		float	fMotionTimer_Move_End;				// ���[�V�����^�C�}�[(�ړ��n/�I������)
		float	fMotionTimer_Attack;				// ���[�V�����^�C�}�[(�U���n)
		float	fMotionTimer_Attack_End;			// ���[�V�����^�C�}�[(�U���n/�I������)
		int		iPlayerMotionAttachIndex_Move;		// �v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		int		iPlayerMotionAttachIndex_Attack;	// �v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�

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
		int		iPlayerMeleeStrongAirMaxCount;	// �v���C���[�̋󒆂ł̋ߋ����U��(��)��(���G���U�����Ă��Ȃ��ꍇ�̍ő吔)		/* 2025.02.26 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		

	protected:
};
