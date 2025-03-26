/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��E�֐��C�� */
/* 2025.02.10 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.11 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
/* 2025.02.26 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.03.03 �e�r�듹 �U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.03.12 �e�r�듹 �X���[���[�V�����֘A�̕ϐ��E�֐��ǉ� */
/* 2025.03.17 �e�r�듹 �ړ��E�U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.03.19 �e�r�듹 �ړ��E�U���֘A�̕ϐ��E�֐��ǉ� */
/* 2025.03.23 �e�r�듹 �ړ��E�U���֘A�̕ϐ��E�֐��ǉ� */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "PublicInclude.h"
#include "PlayerStatusDefine.h"
#include "PlayerMotionDefine.h"

/* �f�[�^���X�g */
#include "DataList_GameResource.h"

/* �O���Q�� */
// ��AppFrame�Œ�`����Ă��Ȃ��N���X���g�p����ꍇ�A�z�Q�Ƒ΍�Ɏ��{����B
class Enemy_Basic;

/* �v���C���[��ԊǗ��N���X�̐錾 */

// �v���C���[��ԊǗ��N���X
class DataList_PlayerStatus : public DataListBase
{
	public:
		DataList_PlayerStatus();			// �R���X�g���N�^
		virtual ~DataList_PlayerStatus();	// �f�X�g���N�^

		/* json�t�@�C���֘A */
		void	LoadPlayerStatuxData();			// �X�e�[�^�X�f�[�^�ǂݍ���
		void	SavePlayerStatuxData();			// �X�e�[�^�X�f�[�^�ۑ�

		/* �o�t�X�V */
		void	StatusBuffUpdate();				// �v���C���[�o�t�X�V

		/* �f�[�^�擾 */
		// �v���C���[��Ԋ֘A
		int		iGetPlayerMoveState()					{ return this->iPlayerMoveState; }					// �v���C���[�̈ړ���Ԏ擾										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		int		iGetPlayerAttackState()					{ return this->iPlayerAttackState; }				// �v���C���[�̍U����Ԏ擾										/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		bool	bGetPlayerLandingFlg()					{ return this->bPlayerLandingFlg; }					// �v���C���[���󒆂ɂ��邩�̃t���O�擾
		float	fGetPlayerNowMoveSpeed()				{ return this->fPlayerNowMoveSpeed; }				// �v���C���[�̌��݂̈ړ����x�擾
		float	fGetPlayerAngleX()						{ return this->fPlayerAngleX; }						// �v���C���[��X����]��(���W�A��)�擾
		float	fGetPlayerTurnSpeed()					{ return this->fPlayerTurnSpeed; }					// �v���C���[�̉�]���x�擾										/* 2025.02.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		float	fGetPlayerNowFallSpeed()				{ return this->fPlayerNowFallSpeed; }				// �v���C���[�̌��݂̗������x�擾
		int		iGetPlayerNowJumpCount()				{ return this->iPlayerNowJumpCount; }				// �v���C���[�̃W�����v��(���ݐ�)�擾
		int		iGetPlayerNowAttakChargeFlame()			{ return this->iPlayerNowAttakChargeFlame; }		// �v���C���[�̌��݂̍U���`���[�W�t���[�����擾
		float	fGetPlayerNowMotionCount()				{ return this->fPlayerNowMotionCount; };			// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		bool	bGetPlayerJumpingFlag()					{ return this->bPlayerJumpingFlag; }				// �v���C���[���W�����v�����̃t���O���擾							/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		
		VECTOR	vecGetPlayerDodgeDirection()			{ return this->vecPlayerDodgeDirection; }			// �v���C���[���������擾											/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerDodgeWhileJumpingCount()		{ return this->iPlayerDodgeWhileJumpingCount; }		// �v���C���[�W�����v���̉���񐔂��擾								/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerNowDodgeFlame()				{ return this->iPlayerNowDodgeFlame; }				// �v���C���[�̌��݂̉���t���[�������擾							/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		VECTOR	vecGetPlayerChargeAttakTargetMove()		{ return this->vecPlayerChargeAttakTargetMove; }	// �v���C���[���ߍU���̈ړ��ʂ��擾									/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */	/* 2025.01.26 ��򕗏� �R�[�h�C�� */
		int		iGetPlayerMeleeStrongAirMaxCount()		{ return this->iPlayerMeleeStrongAirMaxCount; }		// �v���C���[���󒆂ŋߋ����U��(��)���s���ő吔(���G���U�����Ă��Ȃ��ꍇ)���擾		/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetPlayerMeleeStrongAirCount()			{ return this->iPlayerMeleeStrongAirCount; }		// �v���C���[���󒆂ŋߋ����U��(��)���s�����񐔂��擾								/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		bool	bGetPlayerMeleeStrongEnemyAttackFlg()	{ return this->bPlayerMeleeStrongEnemyAttackFlg; }	// �v���C���[���ߋ����U��(��)�œG���U���������̃t���O���擾							/* 2025.03.03 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetPlayerMeleeStrongAfterCount()		{ return this->iPlayerMeleeStrongAfterCount; }		// �v���C���[���ߋ����U��(��)�œG���U��������̃t���[�������擾						/* 2025.03.03 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetiMeleeStrongDestroyCount()			{ return this->iMeleeStrongDestroyCount; }			// �ߋ����U��(��)�Ō��j�����G�̐����擾												/* 2025.03.18 �e�r�듹 �U���֘A�̊֐��ǉ� */
		bool	bGetPlayerMeleeStrongContinuousFlg()	{ return this->bPlayerMeleeStrongContinuousFlg; }	// �v���C���[���ߋ����U��(��)��A���ōs���邩�̃t���O���擾			/* 2025.03.17 �e�r�듹 �U���֘A�̊֐��ǉ� */
		bool	bGetPlayerLandingAfterMeleeStrongFlg() { return this->bPlayerLandingAfterMeleeStrongFlg; }	// �v���C���[���ߋ����U��(��)��ɒ��n���Ă��邩�̃t���O���擾		/* 2025.03.23 �e�r�듹 �U���֘A�̊֐��ǉ� */
		bool	bGetPlayerWallTouchFlg()				{ return this->bPlayerWallTouchFlg; }				// �v���C���[���ǂɐڐG�������̃t���O���擾							/* 2025.03.17 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerAfterWallTouchCount()			{ return this->iPlayerAfterWallTouchCount; }		// �v���C���[���ǂɐڐG������̌o�߃t���[�������擾					/* 2025.03.17 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		bool	bGetPlayerKickWallFlg()					{ return this->bPlayerKickWallFlg; }				// �v���C���[���ǂ��R�������̃t���O���擾							/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerAfterKickWallCount()			{ return this->iPlayerAfterKickWallCount; }			// �v���C���[���ǂ��R������̃J�E���g���擾							/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		bool	bGetPlayerAfterKickWallFlg()			{ return this->bPlayerAfterKickWallFlg; }			// �v���C���[���ǂ��R������̃t���O���擾							/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerMeleeStrongChargeCount()		{ return this->iPlayerMeleeStrongChargeCount; }		// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[�������擾
		int		iGetPlayerSlowMotionCount()				{ return this->iPlayerSlowMotionCount; }			// �v���C���[�̃X���[���[�V�����J�E���g���擾						/* 2025.03.12 �e�r�듹 �X���[���[�V�����֘A�̊֐��ǉ� */
		Enemy_Basic* pGetPlayerLockOnEnemy()			{ return this->pLockOnEnemy; }						// ���b�N�I���Ώۂ̃G�l�~�[���擾
		int		iGetPlayerNowHp()						{ return this->iPlayerNowHp; }						// �v���C���[�̌��݂�HP���擾
		int		iGetPlayerNowInvincibleTime()			{ return this->iPlayerNowInvincibleTime; }			// �v���C���[�̌��݂̎c�薳�G���Ԃ��擾
		int		iGetPlayerComboNowCount()				{ return this->iPlayerComboNowCount; }				// �v���C���[�̌��݂̃R���{�����擾
		int		iGetPlayerComboMaxCount()				{ return this->iPlayerComboMaxCount; }				// �v���C���[�̍ő�R���{�����擾
		int		iGetPlayerComboDuration()				{ return this->iPlayerComboDuration; }				// �v���C���[�̃R���{�̎c�莝�����Ԃ��擾
		bool	bGetPlayerAimCancelledFlg()				{ return this->bPlayerAimCancelledFlg; }			// �������U��(�\��)���L�����Z�����ꂽ���̃t���O���擾				/* 2025.02.11 �e�r�듹 �U���֘A�̊֐��ǉ� */
		bool	bGetPlayerDeadFlg()						{ return this->bPlayerDeadFlg; }					// �v���C���[���S�t���O���擾
		int		iGetPlayerDamageCount()					{ return this->iPlayerDamageCount; }				// �v���C���[�̔�_���[�W�����擾
		bool	bGetFallFlg()							{ return this->bFallFlg; }							// �����t���O���擾
		int		iGetNowHaveKunai()						{ return this->iNowHaveKunai; }						// ���ݎ����Ă���N�i�C�̐����擾
		int		iGetPlayerComboRunk()					{ return this->iPlayerComboRunk; }					// ���݂̃R���{�����N���擾

		/* �v���C���[���[�V�����֘A */
		int		iGetPlayerMotion_Move()						{ return this->iPlayerMotion_Move; }					// �v���C���[���[�V����(�ړ��n)���擾
		float	fGetMotionTimer_Move()						{ return this->fMotionTimer_Move; }						// ���[�V�����J�E���g(�ړ��n)���擾
		float	fGetMotionTimer_Move_End()					{ return this->fMotionTimer_Move_End; }					// ���[�V�����J�E���g(�ړ��n/�I������)���擾
		int		iGetPlayerMotionAttachIndex_Move()			{ return this->iPlayerMotionAttachIndex_Move; }			// �v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		int		iGetPlayerMotion_Move_Old()					{ return this->iPlayerMotion_Move_Old; }				// �ύX�O�v���C���[���[�V����(�ړ��n)���擾
		float	fGetMotionTimer_Move_Old()					{ return this->fMotionTimer_Move_Old; }					// �ύX�O���[�V�����J�E���g(�ړ��n)���擾
		float	fGetMotionTimer_Move_Old_End()				{ return this->fMotionTimer_Move_Old_End; }				// �ύX�O���[�V�����J�E���g(�ړ��n/�I������)���擾
		int		iGetPlayerMotionAttachIndex_Move_Old()		{ return this->iPlayerMotionAttachIndex_Move_Old; }		// �ύX�O�v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		float	fGetNowMoveMotionBlendRate()				{ return this->fNowMoveMotionBlendRate; };				// ���݂̈ړ����[�V�����̃u�����h��
		int		iGetPlayerMotion_Attack()					{ return this->iPlayerMotion_Attack; }					// �v���C���[���[�V����(�U���n)���擾
		float	fGetMotionTimer_Attack()					{ return this->fMotionTimer_Attack; }					// ���[�V�����J�E���g(�U���n)���擾
		float	fGetMotionTimer_Attack_End()				{ return this->fMotionTimer_Attack_End; }				// ���[�V�����J�E���g(�U���n/�I������)���擾
		int		iGetPlayerMotionAttachIndex_Attack()		{ return this->iPlayerMotionAttachIndex_Attack; }		// �v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�		
		int		iGetPlayerMotion_Attack_Old()				{ return this->iPlayerMotion_Attack_Old; }				// �ύX�O�v���C���[���[�V����(�U���n)���擾
		float	fGetMotionTimer_Attack_Old()				{ return this->fMotionTimer_Attack_Old; }				// �ύX�O���[�V�����J�E���g(�U���n)���擾
		float	fGetMotionTimer_Attack_Old_End()			{ return this->fMotionTimer_Attack_Old_End; }			// �ύX�O���[�V�����J�E���g(�U���n/�I������)���擾
		int		iGetPlayerMotionAttachIndex_Attack_Old()	{ return this->iPlayerMotionAttachIndex_Attack_Old; }	// �ύX�O�v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�
		float	fGetNowAttackMotionBlendRate()				{ return this->fNowAttackMotionBlendRate; }				// ���݂̍U�����[�V�����̃u�����h��
		bool	bGetStartFastMotion()						{ return this->bStartFastMotion; }						// �J�n�����[�V�����J�n�t���O
		int		iGetFastMotionCount()						{ return this->iFastMotionCount; }						// �J�n�����[�V�����J�E���g

		/* ���菈���p�R���W���� */
		COLLISION_CAPSULE	stGetMeleeSearchCollision()			{ return this->stMeleeSearchCollision; };		// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�������擾
		bool				bGetMeleeSearchCollisionUseFlg()	{ return this->bMeleeSearchCollisionUseFlg; };	// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�����g�p�t���O���擾

		// �\�͒l�֘A(���������s����X�e�[�^�X)
		float	fGetPlayerMoveAcceleration()	{ return this->fPlayerMoveAcceleration; }	// �v���C���[�̈ړ������x�擾
		float	fGetPlayerJumpSpeed()			{ return this->fPlayerJumpSpeed; }			// �v���C���[�̃W�����v���x�擾
		float	fGetPlayerFallAcceleration()	{ return this->fPlayerFallAcceleration; }	// �v���C���[�̗��������x�擾
		float	fGetPlayerMaxFallSpeed()		{ return this->fPlayerMaxFallSpeed; }		// �v���C���[�̍ő嗎�����x�擾	
		int		iGetPlayerMaxJumpCount()		{ return this->iPlayerMaxJumpCount; }		// �v���C���[�̃W�����v��(�ő吔)�擾
		int		iGetPlayerJumpCoolTime()		{ return this->iPlayerJumpCoolTime; }		// �v���C���[�̃W�����v�N�[���^�C���擾								/* 2025.03.23 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		float	fGetPlayerDodgeSpeed()			{ return this->fPlayerDodgeSpeed; }			// �v���C���[��𑬓x���擾											/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerMaxDodgeFlame()		{ return this->iPlayerMaxDodgeFlame; }		// �v���C���[�̍ő����t���[�������擾								/* 2025.03.19 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iGetPlayerDodgeCoolTime()		{ return this->iPlayerDodgeCoolTime; }		// �v���C���[�̉���N�[���^�C�����擾								/* 2025.03.23 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fGetPlayerKickWallHorizontalSpeed()			{ return this->fPlayerKickWallHorizontalSpeed; }			// �v���C���[�̕ǃL�b�N���x(��������)���擾								/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		float	fGetPlayerKickWallVerticalSpeed()			{ return this->fPlayerKickWallVerticalSpeed; }				// �v���C���[�̕ǃL�b�N���x(��������)���擾								/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerKickWallFlame()					{ return this->iPlayerKickWallFlame; }						// �v���C���[�̕ǃL�b�N�p���t���[�������擾								/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerKickWallInputMaxFlame()			{ return this->iPlayerKickWallInputMaxFlame; }				// �v���C���[�̕ǃL�b�N���͗P�\�t���[�������擾							/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		int		iGetPlayerMeleeWeakCoolTime()				{ return this->iPlayerMeleeWeakCoolTime; }		// �v���C���[�̋ߋ����U��(��)�N�[���^�C���擾							/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetPlayerMelleStrongChangeChargeFrame()	{ return this->iPlayerMelleStrongChangeChargeFrame; }		// �v���C���[�̋ߋ����U��(��)��ԂɂȂ�`���[�W�t���[�������擾			/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetPlayerMelleStrongMaxChargeFrame()		{ return this->iPlayerMelleStrongMaxChargeFrame; }			// �v���C���[�̋ߋ����U��(��)�̍ő�`���[�W�t���[�������擾				/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		float	fGetPlayerMelleStrongMoveScale()			{ return this->fPlayerMelleStrongMoveScale; }				// �v���C���[�̋ߋ����U��(��)�̈ړ������̃X�P�[�����擾					/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		float	fGetPlayerMeleeStrongMoveSpeed()			{ return this->fPlayerMelleStrongMoveSpeed; }				// �v���C���[�̋ߋ����U��(��)�̈ړ����x���擾							/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetPlayerMeleeStrongContinusMaxFrame()		{ return this->iPlayerMeleeStrongContinusMaxFrame; }		// �v���C���[�̋ߋ����U��(��)�ŘA���U���ł���ő�t���[�������擾		/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		float	fGetPlayerMeleeStrongNextSearchRange()		{ return this->fPlayerMeleeStrongNextSearchRange; }			// �v���C���[�̋ߋ����U��(��)��̍��G�͈͂��擾							/* 2025.03.23 �e�r�듹 �U���֘A�̊֐��ǉ� */
		float	fGetPlayerRockOnRadius()		{ return this->fPlayerRockOnRadius; }		// ���b�N�I���͈͂̔��a��ݒ�
		int		iGetStartHaveKunai()			{ return this->iStartHaveKunai; }			// ������ԂŎ����Ă���N�i�C�̐�
		int		iGetMaxHaveKunai()				{ return this->iMaxhaveKunai; }				// �ő�Ŏ��Ă�N�i�C�̐�
		int		iGetPlayerKunaiCoolTime()		{ return this->iPlayerKunaiCoolTime; }		// �N�i�C�̃N�[���^�C�����擾																		/* 2025.03.23 �e�r�듹 �U���֘A�̊֐��ǉ� */
		int		iGetPlayerMaxHp()				{ return this->iPlayerMaxHp; }				// �v���C���[�̍ő�HP�擾
		int		iGetPlayerMaxInvincibleTime()	{ return this->iPlayerMaxInvincibleTime; }	// �v���C���[�̍ő喳�G���Ԏ擾

		/* �v���C���[�o�t�֘A(�G�f�B�b�g����) */
		float	fGetAddMoveSpeedUp()					{ return this->fAddMoveSpeedUp; }					// �ړ����x�㏸�l(���x/�t���[��)
		int		iGetAddBlood()							{ return this->iAddBlood; }							// �u���b�h(�Q�[�����ʉ�)�̓����(��)
		int		iGetAddComboTime()						{ return this->iAddComboTime; }						// �R���{���ԑ����l(�t���[��)
		int		iGetAddAttackChargeFrameShortening()	{ return this->iAddAttackChargeFrameShortening; }	// �`���[�W���ԒZ�k�l(�t���[��)
		int		iGetAddJumpCount()						{ return this->iAddJumpCount; }						// �W�����v�񐔑����l(��)
		int		iGetAddMeleeStrongAirMaxCount()			{ return this->iAddMeleeStrongAirMaxCount; }		// �󒆂ł̋ߋ����U��(��)�񐔑����l(��)
		int		iGetAddKunaiKeepProbability()			{ return this->iAddKunaiKeepProbability; }			// �N�i�C�ێ��m��(%)
		int		iGetAddBarrier()						{ return this->iAddBarrier; }						// �o���A��(��)
		bool	bGetAddCounter()						{ return this->bAddCounter; }						// �J�E���^�[�ǉ��t���O(�L��/����)
		bool	bGetKunaiExplosion()					{ return this->bAddKunaiExplosion; }				// �N�i�C�������t���O(�L��/����)
		bool	bGetAddMaxHpOne()						{ return this->bAddMaxHpOne; }						// �ő�HP1���t���O(�L��/����)
		int		iGetAddKunai()							{ return this->iAddKunai; }							// �N�i�C�ǉ���(��)

		/* �f�[�^�ݒ� */
		// �v���C���[��Ԋ֘A
		void	SetPlayerMoveState(int iPlayerMoveState)									{ this->iPlayerMoveState					= iPlayerMoveState; }					// �v���C���[�̈ړ���Ԑݒ�					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		void	SetPlayerAttackState(int iPlayerAttackState)								{ this->iPlayerAttackState					= iPlayerAttackState; }					// �v���C���[�̍U����Ԑݒ�					/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̊֐��C�� */
		void	SetPlayerLanding(bool bPlayerLanding)										{ this->bPlayerLandingFlg					= bPlayerLanding; }						// �v���C���[���󒆂ɂ��邩�̃t���O�ݒ�
		void	SetPlayerNowMoveSpeed(float fPlayerNowMoveSpeed)							{ this->fPlayerNowMoveSpeed					= fPlayerNowMoveSpeed; }				// �v���C���[�̌��݂̈ړ����x�ݒ�
		void	SetPlayerAngleX(float fPlayerAngleX)										{ this->fPlayerAngleX						= fPlayerAngleX; }						// �v���C���[��X����]��(���W�A��)�擾
		void	SetPlayerTurnSpeed(float fPlayerTurnSpeed)									{ this->fPlayerTurnSpeed					= fPlayerTurnSpeed; }					// �v���C���[�̉�]���x�ݒ�					/* 2025.02.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetplayerJumpSpeed(float fPlayerJumpSpeed)									{ this->fPlayerJumpSpeed					= fPlayerJumpSpeed; }					// �v���C���[�̃W�����v���x�ݒ�
		void	SetPlayerNowFallSpeed(float fPlayerNowFallSpeed)							{ this->fPlayerNowFallSpeed					= fPlayerNowFallSpeed; }				// �v���C���[�̌��݂̗������x�ݒ�
		void	SetPlayerNowJumpCount(int iPlayerNowJumpCount)								{ this->iPlayerNowJumpCount					= iPlayerNowJumpCount; }				// �v���C���[�̃W�����v��(���ݐ�)�ݒ�
		void	SetPlayerNowAttakChargeFlame(int iPlayerNowAttakChargeFlame)				{ this->iPlayerNowAttakChargeFlame			= iPlayerNowAttakChargeFlame; }			// �v���C���[�̌��݂̍U���`���[�W�t���[�����ݒ�
		void	SetPlayerChargeAttakTargetMove(VECTOR vecPlayerChargeAttakTargetMove)		{ this->vecPlayerChargeAttakTargetMove		= vecPlayerChargeAttakTargetMove; }		// �v���C���[���ߍU���̈ړ��ʂ�ݒ�															/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */	/* 2025.01.26 ��򕗏� �R�[�h�C�� */
		void	SetPlayerMeleeStrongChargeCount(int iPlayerMeleeStrongChargeCount)			{ this->iPlayerMeleeStrongChargeCount		= iPlayerMeleeStrongChargeCount; }		// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[������ݒ�
		void	SetPlayerMeleeStrongAirCount(int iPlayerMeleeStrongAirCount)				{ this->iPlayerMeleeStrongAirCount			= iPlayerMeleeStrongAirCount; }			// �v���C���[���󒆂ŋߋ����U��(��)���s�����񐔂�ݒ�		/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongEnemyAttackFlg(bool bPlayerMeleeStrongEnemyAttackFlg)	{ this->bPlayerMeleeStrongEnemyAttackFlg	= bPlayerMeleeStrongEnemyAttackFlg; }	// �v���C���[���ߋ����U��(��)�ŃG�l�~�[���U���������̃t���O��ݒ�		/* 2025.03.03 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongAfterCount(int iPlayerMeleeStrongAfterCount)			{ this->iPlayerMeleeStrongAfterCount		= iPlayerMeleeStrongAfterCount; }		// �v���C���[���ߋ����U��(��)�ŃG�l�~�[���U��������̃t���[������ݒ�	/* 2025.03.03 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetMeleeStrongDestroyCount(int iMeleeStrongDestroyCount)					{ this->iMeleeStrongDestroyCount = iMeleeStrongDestroyCount; }						// �ߋ����U��(��)�Ō��j�����G�̐���ݒ�									/* 2025.03.18 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongContinuousFlg(bool bPlayerMeleeStrongContinuousFlg)		{ this->bPlayerMeleeStrongContinuousFlg		= bPlayerMeleeStrongContinuousFlg; }	// �v���C���[���ߋ����U��(��)��A���ōs���邩�̃t���O��ݒ�				/* 2025.03.17 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerLandingAfterMeleeStrongFlg(bool bPlayerLandingAfterMeleeStrongFlg) { this->bPlayerLandingAfterMeleeStrongFlg = bPlayerLandingAfterMeleeStrongFlg; }	// �v���C���[���ߋ����U��(��)��ɒ��n���Ă��邩�̃t���O��ݒ�			/* 2025.03.23 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerSlowMotionCount(int iPlayerSlowMotionCount)						{ this->iPlayerSlowMotionCount				= iPlayerSlowMotionCount; }				// �v���C���[�̃X���[���[�V�����̃J�E���g��ݒ�									/* 2025.03.12 �e�r�듹 �X���[���[�V�����֘A�̊֐��ǉ� */
		void	SetPlayerNowMotionCount(float fPlayerNowMotionCount)						{ this->fPlayerNowMotionCount				= fPlayerNowMotionCount; };				// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		void	SetPlayerJumpingFlag(bool bPlayerJumpingFlag)								{ this->bPlayerJumpingFlag					= bPlayerJumpingFlag; }					// �v���C���[���W�����v�����̃t���O��ݒ�	/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerNowDodgeFlame(int iPlayerNowDodgeFlame)							{ this->iPlayerNowDodgeFlame				= iPlayerNowDodgeFlame; }				// �v���C���[�̌��݂̉�����Ԃ�ݒ�			/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */		
		void	SetPlayerDodgeDirection(VECTOR vecPlayerDodgeDirection)						{ this->vecPlayerDodgeDirection				= vecPlayerDodgeDirection; }			// �v���C���[��������ݒ�					/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeWhileJumpingCount(int iPlayerDodgeWhileJumpingCount)			{ this->iPlayerDodgeWhileJumpingCount		= iPlayerDodgeWhileJumpingCount; }		// �v���C���[�W�����v���̉���񐔂�ݒ�		/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerWallTouchFlg(bool bPlayerWallTouchFlg)								{ this->bPlayerWallTouchFlg					= bPlayerWallTouchFlg; }				// �v���C���[���ǂɐڐG�������̃t���O��ݒ�								/* 2025.03.17 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerAfterWallTouchCount(int iPlayerAfterWallTouchCount)				{ this->iPlayerAfterWallTouchCount = iPlayerAfterWallTouchCount; }					// �v���C���[���ǂɐڐG������̌o�߃t���[������ݒ�						/* 2025.03.17 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerKickWallFlg(bool bPlayerKickWallFlg)								{ this->bPlayerKickWallFlg					= bPlayerKickWallFlg; }					// �v���C���[���ǂ��R�������̃t���O��ݒ�	/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerAfterKickWallCount(int iPlayerAfterKickWallCount)					{ this->iPlayerAfterKickWallCount			= iPlayerAfterKickWallCount; }			// �v���C���[���ǂ��R������̃J�E���g��ݒ�	/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerAfterKickWallFlg(bool bPlayerAfterKickWallFlg)						{ this->bPlayerAfterKickWallFlg				= bPlayerAfterKickWallFlg; }			// �v���C���[���ǂ��R������̃t���O��ݒ�	/* 2025.02.22 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerLockOnEnemy(Enemy_Basic* pLockOnEnemy)								{ this->pLockOnEnemy						= pLockOnEnemy; };						// ���b�N�I���Ώۂ̃G�l�~�[��ݒ�
		void	SetPlayerNowHp(int iPlayerNowHp)											{ this->iPlayerNowHp						= iPlayerNowHp; }						// �v���C���[�̌��݂�HP��ݒ�
		void	SetPlayerNowInvincibleTime(int iPlayerNowInvincibleTime)					{ this->iPlayerNowInvincibleTime			= iPlayerNowInvincibleTime; }			// �v���C���[�̌��݂̎c�薳�G���Ԃ�ݒ�
		void	SetPlayerComboNowCount(int iPlayerComboNowCount)							{ this->iPlayerComboNowCount				= iPlayerComboNowCount; }				// �v���C���[�̌��݂̃R���{����ݒ�
		void	SetPlayerComboMaxCount(int iPlayerComboMaxCount)							{ this->iPlayerComboMaxCount				= iPlayerComboMaxCount; }				// �v���C���[�̍ő�R���{����ݒ�
		void	SetPlayerComboDuration(int iPlayerComboDuration)							{ this->iPlayerComboDuration				= iPlayerComboDuration; }				// �v���C���[�̃R���{�̎c�莝�����Ԃ�ݒ�
		void	SetPlayerAimCancelledFlg(bool bPlayerAimCancelledFlg)						{ this->bPlayerAimCancelledFlg				= bPlayerAimCancelledFlg; }				// �������U��(�\��)���L�����Z�����ꂽ���̃t���O��ݒ�	/* 2025.02.11 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerDeadFlg(bool bPlayerDeadFlg)										{ this->bPlayerDeadFlg						= bPlayerDeadFlg; }						// �v���C���[���S�t���O
		void	SetPlayerDamageCount(int iPlayerDamageCount)								{ this->iPlayerDamageCount					= iPlayerDamageCount; }					// �v���C���[�̔�_���[�W����ݒ�
		void	SetFallFlg(bool bFallFlg)													{ this->bFallFlg							= bFallFlg; }							// �����t���O��ݒ�
		void	SetNowHaveKunai(int iNowHaveKunai)											{ this->iNowHaveKunai						= iNowHaveKunai; }						// ���ݎ����Ă���N�i�C�̐���ݒ�
		void	SetPlayerComboRunk(int iPlayerComboRunk)									{ this->iPlayerComboRunk					= iPlayerComboRunk; }					// ���݂̃R���{�����N��ݒ�

		/* �v���C���[���[�V�����֘A */
		void	SetPlayerMotion_Move(int iPlayerMotion_Move)								{ this->iPlayerMotion_Move					= iPlayerMotion_Move; };						// �v���C���[���[�V����(�ړ��n)��ݒ�
		void	SetMotionCount_Move(float fMotionCount_Move)								{ this->fMotionTimer_Move					= fMotionCount_Move; };							// ���[�V�����J�E���g(�ړ��n)
		void	SetMotionCount_Move_End(float fMotionCount_Move_End)						{ this->fMotionTimer_Move_End				= fMotionCount_Move_End; };						// ���[�V�����J�E���g(�ړ��n/�I������)��ݒ�
		void	SetPlayerMotionAttachIndex_Move(int iPlayerMotionAttachIndex_Move)			{ this->iPlayerMotionAttachIndex_Move		= iPlayerMotionAttachIndex_Move; }				// �v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		void	SetPlayerMotion_Move_Old(int iPlayerMotion_Move_Old)						{ this->iPlayerMotion_Move_Old				= iPlayerMotion_Move_Old; };					// �ύX�O�v���C���[���[�V����(�ړ��n)��ݒ�
		void	SetMotionCount_Move_Old(float fMotionCount_Move_Old)						{ this->fMotionTimer_Move_Old				= fMotionCount_Move_Old; };						// �ύX�O���[�V�����J�E���g(�ړ��n)
		void	SetMotionCount_Move_Old_End(float fMotionCount_Move_Old_End)				{ this->fMotionTimer_Move_Old_End			= fMotionCount_Move_Old_End; };					// �ύX�O���[�V�����J�E���g(�ړ��n/�I������)��ݒ�
		void	SetPlayerMotionAttachIndex_Move_Old(int iPlayerMotionAttachIndex_Move_Old)	{ this->iPlayerMotionAttachIndex_Move_Old	= iPlayerMotionAttachIndex_Move_Old; }			// �ύX�O�v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		void	SetNowMoveMotionBlendRate(float fNowMoveMotionBlendRate)					{ this->fNowMoveMotionBlendRate				= fNowMoveMotionBlendRate; }					// ���݂̈ړ����[�V�����̃u�����h��
		void	SetPlayerMotion_Attack(int iPlayerMotion_Attack)							{ this->iPlayerMotion_Attack				= iPlayerMotion_Attack; };						// �v���C���[���[�V����(�U���n)��ݒ�
		void	SetMotionCount_Attack(float fMotionCount_Attack)							{ this->fMotionTimer_Attack					= fMotionCount_Attack; };						// ���[�V�����J�E���g(�U���n)��ݒ�
		void	SetMotionCount_Attack_End(float fMotionCount_Attack_End)					{ this->fMotionTimer_Attack_End				= fMotionCount_Attack_End; };					// ���[�V�����J�E���g(�U���n/�I������)��ݒ�
		void	SetPlayerMotionAttachIndex_Attack(int iPlayerMotionAttachIndex_Attack)		{ this->iPlayerMotionAttachIndex_Attack		= iPlayerMotionAttachIndex_Attack; }			// �v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�
		void	SetPlayerMotion_Attack_Old(int iPlayerMotion_Attack_Old)						{ this->iPlayerMotion_Attack_Old			= iPlayerMotion_Attack_Old; };				// �ύX�O�v���C���[���[�V����(�U���n)��ݒ�
		void	SetMotionCount_Attack_Old(float fMotionCount_Attack_Old)						{ this->fMotionTimer_Attack_Old				= fMotionCount_Attack_Old; };				// �ύX�O���[�V�����J�E���g(�U���n)��ݒ�
		void	SetMotionCount_Attack_Old_End(float fMotionCount_Attack_Old_End)				{ this->fMotionTimer_Attack_Old_End			= fMotionCount_Attack_Old_End; };			// �ύX�O���[�V�����J�E���g(�U���n/�I������)��ݒ�		
		void	SetPlayerMotionAttachIndex_Attack_Old(int iPlayerMotionAttachIndex_Attack_Old)	{ this->iPlayerMotionAttachIndex_Attack_Old	= iPlayerMotionAttachIndex_Attack_Old; }	// �ύX�O�v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ���ݒ�
		void	SetNowAttackMotionBlendRate(float fNowAttackMotionBlendRate)					{ this->fNowAttackMotionBlendRate			= fNowAttackMotionBlendRate; }				// ���݂̍U�����[�V�����̃u�����h����ݒ�
		void	SetStartFastMotion(bool bStartFastMotion)										{ this->bStartFastMotion					= bStartFastMotion; }						// �J�n�����[�V�����J�n�t���O��ݒ�
		void	SetFastMotionCount(int iFastMotionCount)										{ this->iFastMotionCount					= iFastMotionCount; }						// �J�n�����[�V�����J�E���g��ݒ�

		/* ���菈���p�R���W���� */
		void	SetMeleeSearchCollision(COLLISION_CAPSULE stMeleeSearchCollision)				{ this->stMeleeSearchCollision			= stMeleeSearchCollision; }						// �ߐڍU��(��)�̃��b�N�I���͈̓R���W������ݒ�
		void	SetMeleeSearchCollisionUseFlg(bool bMeleeSearchCollisionUseFlg)					{ this->bMeleeSearchCollisionUseFlg		= bMeleeSearchCollisionUseFlg; }				// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�����g�p�t���O��ݒ�

		// �\�͒l�֘A(���������s����X�e�[�^�X)
		void	SetPlayerMoveAcceleration(float fPlayerMoveAcceleration)						{ this->fPlayerMoveAcceleration			= fPlayerMoveAcceleration; }		// �v���C���[�̈ړ������x�ݒ�
		void	SetPlayerFallAcceleration(float fPlayerFallAcceleration)						{ this->fPlayerFallAcceleration			= fPlayerFallAcceleration; }		// �v���C���[�̗��������x�ݒ�
		void	SetPlayerJumpSpeed(float fPlayerJumpSpeed)										{ this->fPlayerJumpSpeed				= fPlayerJumpSpeed; }				// �v���C���[�̃W�����v���x�ݒ�
		void	SetPlayerMaxFallSpeed(float fPlayerMaxFallSpeed)								{ this->fPlayerMaxFallSpeed				= fPlayerMaxFallSpeed; }			// �v���C���[�̍ő嗎�����x�ݒ�
		void	SetPlayerMaxJumpCount(int iPlayerMaxJumpCount)									{ this->iPlayerMaxJumpCount				= iPlayerMaxJumpCount; }			// �v���C���[�̃W�����v��(�ő吔)�ݒ�
		void	SetPlayerJumpCoolTime(int iPlayerJumpCoolTime)									{ this->iPlayerJumpCoolTime				= iPlayerJumpCoolTime; }			// �v���C���[�̃W�����v�N�[���^�C����ݒ�													/* 2025.03.23 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeSpeed(float fPlayerDodgeSpeed)									{ this->fPlayerDodgeSpeed				= fPlayerDodgeSpeed; }				// �v���C���[��𑬓x��ݒ�																	/* 2025.01.10 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerDodgeCoolTime(int iPlayerDodgeCoolTime)								{ this->iPlayerDodgeCoolTime			= iPlayerDodgeCoolTime; }			// �v���C���[����N�[���^�C����ݒ�															/* 2025.03.23 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerMaxDodgeFlame(int iPlayerMaxDodgeFlame)								{ this->iPlayerMaxDodgeFlame			= iPlayerMaxDodgeFlame; }			// �v���C���[�̍ő����t���[������ݒ�														/* 2025.03.19 �e�r�듹 �ړ��֘A�̕ϐ��E�֐��ǉ� */
		void	SetPlayerKickWallHorizontalSpeed(float fPlayerKickWallHorizontalSpeed)			{ this->fPlayerKickWallHorizontalSpeed	= fPlayerKickWallHorizontalSpeed; }	// �v���C���[�̕ǃL�b�N���x(��������)��ݒ�													/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerKickWallVerticalSpeed(float fPlayerKickWallVerticalSpeed)				{ this->fPlayerKickWallVerticalSpeed	= fPlayerKickWallVerticalSpeed; }	// �v���C���[�̕ǃL�b�N���x(��������)��ݒ�													/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerKickWallFlame(int iPlayerKickWallFlame)								{ this->iPlayerKickWallFlame			= iPlayerKickWallFlame; }			// �v���C���[�̕ǃL�b�N�p���t���[������ݒ�													/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlyerKickWallInputMaxFrame(int iPlayerKickWallInputMaxFrame)					{ this->iPlayerKickWallInputMaxFlame	= iPlayerKickWallInputMaxFrame; }	// �v���C���[�̕ǃL�b�N�̓��͗P�\�t���[������ݒ�											/* 2025.03.19 �e�r�듹 �ړ��֘A�̊֐��ǉ� */
		void	SetPlayerMeleeWeakCoolTime(int iPlayerMeleeWeakCoolTime)						{ this->iPlayerMeleeWeakCoolTime = iPlayerMeleeWeakCoolTime; }		// �v���C���[�̋ߋ����U��(��)�̃N�[���^�C����ݒ�																/* 2025.03.23 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMelleStrongChangeChargeFrame(int iPlayerMelleStrongChangeChargeFrame)	{ this->iPlayerMelleStrongChangeChargeFrame		= iPlayerMelleStrongChangeChargeFrame; }		// �v���C���[�̋ߋ����U��(��)�ɐ؂�ւ��`���[�W�t���[������ݒ�					/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMelleStrongMaxChargeFrame(int iPlayerMelleStrongMaxChargeFrame)		{ this->iPlayerMelleStrongMaxChargeFrame		= iPlayerMelleStrongMaxChargeFrame; }			// �v���C���[�̋ߋ����U��(��)�̍ő�`���[�W�t���[������ݒ�							/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMelleStrongMoveScale(float fPlayerMelleStrongMoveScale)				{ this->fPlayerMelleStrongMoveScale				= fPlayerMelleStrongMoveScale; }				// �v���C���[�̋ߋ����U��(��)�̈ړ������̃X�P�[����ݒ�								/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongMoveSpeed(float fPlayerMeleeStrongMoveSpeed)				{ this->fPlayerMelleStrongMoveSpeed				= fPlayerMeleeStrongMoveSpeed; }				// �v���C���[�ߋ����U��(��)�̈ړ����x��ݒ�											/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongContinusMaxFrame(int iPlayerMeleeStrongContinusMaxFrame)	{ this->iPlayerMeleeStrongContinusMaxFrame		= iPlayerMeleeStrongContinusMaxFrame; }			// �v���C���[�ߋ����U��(��)�ŘA���U���ł���ő�t���[������ݒ�						/* 2025.03.19 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongAirMaxCount(int iPlayerMeleeStrongAirMaxCount)				{ this->iPlayerMeleeStrongAirMaxCount	= iPlayerMeleeStrongAirMaxCount; }				// �v���C���[���󒆂ŋߋ����U��(��)���s���ő吔(���G���U�����Ă��Ȃ��ꍇ)��ݒ�				/* 2025.02.26 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMeleeStrongNextSearchRange(float fPlayerMeleeStrongNextSearchRange)	{ this->fPlayerMeleeStrongNextSearchRange	= fPlayerMeleeStrongNextSearchRange; }				// �v���C���[���ߋ����U��(��)���s������̍��G�͈͂�ݒ�								/* 2025.03.23 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerRockOnRadius(float fPlayerRockOnRadius)								{ this->fPlayerRockOnRadius				= fPlayerRockOnRadius; }			// ���b�N�I���͈͂̔��a��ݒ�
		void	SetStartHaveKunai(int iStartHaveKunai)											{ this->iStartHaveKunai					= iStartHaveKunai; }				// ������ԂŎ����Ă���N�i�C�̐�
		void	SetMaxhaveKunai(int iMaxhaveKunai)												{ this->iMaxhaveKunai					= iMaxhaveKunai; }					// �ő�Ŏ��Ă�N�i�C�̐�
		void	SetPlayerKunaiCoolTime(int iPlayerKunaiCoolTime)								{ this->iPlayerKunaiCoolTime				= iPlayerKunaiCoolTime; }							// �N�i�C�̃N�[���^�C����ݒ�														/* 2025.03.23 �e�r�듹 �U���֘A�̊֐��ǉ� */
		void	SetPlayerMaxHp(int iPlayerMaxHp) { this->iPlayerMaxHp = iPlayerMaxHp; }					// �v���C���[�̍ő�HP�ݒ�
		void	SetPlayerMaxInvincibleTime(int iPlayerMaxInvincibleTime) { this->iPlayerMaxInvincibleTime = iPlayerMaxInvincibleTime; }		// �v���C���[�̍ő喳�G���Ԑݒ�
		
		/* �v���C���[�o�t�֘A(�G�f�B�b�g����) */
		void	SetAddMoveSpeedUp(float fAddMoveSpeedUp)										{ this->fAddMoveSpeedUp					= fAddMoveSpeedUp; }					// �ړ����x�㏸�l(���x/�t���[��)
		void	SetAddBlood(int iAddBlood)														{ this->iAddBlood						= iAddBlood; }							// �u���b�h(�Q�[�����ʉ�)�̓����(��)
		void	SetAddComboTime(int iAddComboTime)												{ this->iAddComboTime					= iAddComboTime; }						// �R���{���ԑ����l(�t���[��)
		void	SetAddAttackChargeFrameShortening(int iAddAttackChargeFrameShortening)			{ this->iAddAttackChargeFrameShortening	= iAddAttackChargeFrameShortening; }	// �`���[�W���ԒZ�k�l(�t���[��)
		void	SetAddJumpCount(int iAddJumpCount)												{ this->iAddJumpCount					= iAddJumpCount; }						// �W�����v�񐔑����l(��)
		void	SetAddMeleeStrongAirMaxCount(int iAddMeleeStrongAirMaxCount)					{ this->iAddMeleeStrongAirMaxCount		= iAddMeleeStrongAirMaxCount; }			// �󒆂ł̋ߋ����U��(��)�񐔑����l(��)
		void	SetAddKunaiKeepProbability(int iAddKunaiKeepProbability)						{ this->iAddKunaiKeepProbability		= iAddKunaiKeepProbability; }			// �N�i�C�ێ��m��(%)
		void	SetAddBarrier(int iAddBarrier)													{ this->iAddBarrier						= iAddBarrier; }						// �o���A��(��)
		void	SetAddCounter(bool bAddCounter)													{ this->bAddCounter						= bAddCounter; }						// �J�E���^�[�ǉ��t���O(�L��/����)
		void	SetKunaiExplosion(bool bKunaiExplosion)											{ this->bAddKunaiExplosion				= bKunaiExplosion; };					// �N�i�C�������t���O(�L��/����)
		void	SetAddMaxHpOne(bool bAddMaxHpOne)												{ this->bAddMaxHpOne					= bAddMaxHpOne; }						// �ő�HP1���t���O(�L��/����)
		void	SetAddKunai(int iAddKunai)														{ this->iAddKunai						= iAddKunai; }							// �N�i�C�ǉ���(��)

	private:
		/* �v���C���[��Ԋ֘A */
		int		iPlayerMoveState;					// �v���C���[�̈ړ����(�A�N�V����)												/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��C�� */
		int		iPlayerAttackState;					// �v���C���[�̍U�����(�A�N�V����)												/* 2025.02.05 �e�r�듹 �X�e�[�^�X�֘A�̕ϐ��C�� */
		bool	bPlayerLandingFlg;					// �v���C���[�����n���Ă��邩�̃t���O
		float	fPlayerNowMoveSpeed;				// �v���C���[�̌��݂̈ړ����x
		float	fPlayerAngleX;						// �v���C���[��X����]��(���W�A��)
		float	fPlayerTurnSpeed;					// �v���C���[�̕����]���̑��x�i�͈́F0.0?1.0�j									/* 2025.02.10 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerNowFallSpeed;				// �v���C���[�̌��݂̗������x
		int		iPlayerNowJumpCount;				// �v���C���[�̃W�����v��(���ݐ�)
		float	fPlayerNowMotionCount;				// �v���C���[�̃��[�V�����̌��݂̃J�E���g
		bool	bPlayerJumpingFlag;					// �v���C���[���W�����v�����̃t���O												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerNowDodgeFlame;				// �v���C���[�̌��݂̉���t���[����												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		VECTOR	vecPlayerDodgeDirection;			// �v���C���[������															/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerDodgeWhileJumpingCount;		// �v���C���[�W�����v���̉����												/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerWallTouchFlg;				// �v���C���[���ǂɐڐG�������̃t���O											/* 2025.03.17 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerAfterWallTouchCount;			// �v���C���[���ǂɐڐG���Ă���̌o�߃t���[����									/* 2025.03.17 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerKickWallFlg;					// �v���C���[���ǂ��R�������̃t���O												/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerAfterKickWallCount;			// �v���C���[���ǂ��R���Ă���̌o�߃t���[����									/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		bool	bPlayerAfterKickWallFlg;			// �v���C���[���ǂ��R������̏�Ԃ��̃t���O										/* 2025.02.22 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		VECTOR	vecPlayerChargeAttakTargetMove;		// �ߐڍU��(��)�ɂ��ړ���														/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */	/* 2025.01.26 ��򕗏� �R�[�h�C�� */
		int		iPlayerNowAttakChargeFlame;			// ���݂̃v���C���[���ߍU���`���[�W�t���[����									/* 2025.01.22 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerMeleeStrongChargeCount;		// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[����
		int		iPlayerMeleeStrongAirCount;			// �v���C���[���󒆂ŋߋ����U��(��)���s������(���G���U�����Ă��Ȃ��ꍇ)		/* 2025.02.26 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		bool	bPlayerMeleeStrongEnemyAttackFlg;	// �v���C���[���ߋ����U��(��)�œG���U���������̃t���O							/* 2025.03.03 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerMeleeStrongAfterCount;		// �v���C���[���ߋ����U��(��)�œG���U��������̃t���[����						/* 2025.03.03 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iMeleeStrongDestroyCount;			// �v���C���[���ߋ����U��(��)�Ō��j�����G�̐�									/* 2025.03.18 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		bool	bPlayerMeleeStrongContinuousFlg;	// �v���C���[���A���ŋߋ����U��(��)�ł��邩�̃t���O								/* 2025.03.17 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		bool	bPlayerLandingAfterMeleeStrongFlg;	// �v���C���[���ߋ����U��(��)��ɒ��n���Ă��邩�̃t���O							/* 2025.03.23 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerSlowMotionCount;				// �v���C���[�̃X���[���[�V�����t���[�����J�E���g								/* 2025.03.12 �e�r�듹 �X���[���[�V�����֘A�̕ϐ��ǉ� */
		Enemy_Basic* pLockOnEnemy;				// ���b�N�I���Ώۂ̃G�l�~�[
		int		iPlayerNowHp;						// �v���C���[�̌��݂�HP
		int		iPlayerNowInvincibleTime;			// �v���C���[�̌��݂̎c�薳�G����
		int		iPlayerComboNowCount;				// �v���C���[�̌��݂̃R���{��
		int		iPlayerComboMaxCount;				// �v���C���[�̍ő�R���{��
		int		iPlayerComboDuration;				// �v���C���[�̃R���{�̎c�莝������
		bool	bPlayerAimCancelledFlg;				// �������U��(�\��)���L�����Z�����ꂽ���̃t���O
		bool	bPlayerDeadFlg;						// �v���C���[���S�t���O
		int		iPlayerDamageCount;					// ��_���[�W��
		bool	bFallFlg;							// �����t���O
		int		iNowHaveKunai;						// ���ݎ����Ă���N�i�C�̐�
		int		iPlayerComboRunk;					// ���݂̃R���{�����N

		/* �v���C���[���[�V�����֘A */
		int		iPlayerMotion_Move;						// �v���C���[���[�V����(�ړ��n)
		float	fMotionTimer_Move;						// ���[�V�����^�C�}�[(�ړ��n)
		float	fMotionTimer_Move_End;					// ���[�V�����^�C�}�[(�ړ��n/�I������)
		int		iPlayerMotionAttachIndex_Move;			// �v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		int		iPlayerMotion_Move_Old;					// �ύX�O�v���C���[���[�V����(�ړ��n)
		float	fMotionTimer_Move_Old;					// �ύX�O���[�V�����^�C�}�[(�ړ��n)
		float	fMotionTimer_Move_Old_End;				// �ύX�O���[�V�����^�C�}�[(�ړ��n/�I������)
		int		iPlayerMotionAttachIndex_Move_Old;		// �ύX�O�v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
		float	fNowMoveMotionBlendRate;				// ���݂̈ړ����[�V�����̃u�����h��
		int		iPlayerMotion_Attack;					// �v���C���[���[�V����(�U���n)
		float	fMotionTimer_Attack;					// ���[�V�����^�C�}�[(�U���n)
		float	fMotionTimer_Attack_End;				// ���[�V�����^�C�}�[(�U���n/�I������)
		int		iPlayerMotionAttachIndex_Attack;		// �v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�
		int		iPlayerMotion_Attack_Old;				// �ύX�O�v���C���[���[�V����(�U���n)		
		float	fMotionTimer_Attack_Old;				// �ύX�O���[�V�����^�C�}�[(�U���n)
		float	fMotionTimer_Attack_Old_End;			// �ύX�O���[�V�����^�C�}�[(�U���n/�I������)
		int		iPlayerMotionAttachIndex_Attack_Old;	// �ύX�O�v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�
		float	fNowAttackMotionBlendRate;				// ���݂̍U�����[�V�����̃u�����h��
		bool	bStartFastMotion;						// �J�n�����[�V�����J�n�t���O
		int		iFastMotionCount;						// �J�n�����[�V�����J�E���g

		/* ���菈���p�R���W���� */
		COLLISION_CAPSULE	stMeleeSearchCollision;			// �ߐڍU��(��)�̃��b�N�I���͈̓R���W����
		bool				bMeleeSearchCollisionUseFlg;	// �ߐڍU��(��)�̃��b�N�I���͈̓R���W�����g�p�t���O
		
		/* �\�͒l�֘A(���v���C���[�̑������ɂ���ď㉺����\���̂���X�e�[�^�X))*/
		float	fPlayerMoveAcceleration;				// �v���C���[�̈ړ������x
		float	fPlayerJumpSpeed;						// �v���C���[�W�����v���x														/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerFallAcceleration;				// �v���C���[�̗��������x
		float	fPlayerMaxFallSpeed;					// �v���C���[�̍ő嗎�����x
		int		iPlayerMaxJumpCount;					// �v���C���[�̃W�����v��(�ő吔)
		int		iPlayerJumpCoolTime;					// �v���C���[�̃W�����v�N�[���^�C��												/* 2025.03.23 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerDodgeSpeed;						// �v���C���[��𑬓x															/* 2025.01.09 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerMaxDodgeFlame;					// �v���C���[�̍ő����t���[����												/* 2025.03.19 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerDodgeCoolTime;					// �v���C���[�̉���N�[���^�C��													/* 2025.03.23 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerKickWallHorizontalSpeed;			// �v���C���[�̕ǃL�b�N���x(��������)											/* 2025.03.19 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		float	fPlayerKickWallVerticalSpeed;			// �v���C���[�̕ǃL�b�N���x(��������)											/* 2025.03.19 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerKickWallFlame;					// �v���C���[�̕ǃL�b�N�p���t���[����											/* 2025.03.19 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerKickWallInputMaxFlame;			// �v���C���[�̕ǃL�b�N���͗P�\�t���[����										/* 2025.03.19 �e�r�듹 �ړ��֘A�̕ϐ��ǉ� */
		int		iPlayerMeleeWeakCoolTime;				// �v���C���[�̋ߋ����U��(��)�̃N�[���^�C��										/* 2025.03.24 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerMelleStrongChangeChargeFrame;	// �v���C���[�̋ߋ����U��(��)�ɐ؂�ւ��`���[�W�t���[����						/* 2025.03.19 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerMelleStrongMaxChargeFrame;		// �v���C���[�̋ߋ����U��(��)�̍ő�`���[�W�t���[����							/* 2025.03.19 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		float	fPlayerMelleStrongMoveScale;			// �v���C���[�̋ߋ����U��(��)�̈ړ������̃X�P�[��								/* 2025.03.19 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		float	fPlayerMelleStrongMoveSpeed;			// �v���C���[�̋ߋ����U��(��)�̈ړ����x											/* 2025.03.19 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerMeleeStrongContinusMaxFrame;		// �v���C���[���ߋ����U��(��)�ŘA���U���ł���ő�t���[����						/* 2025.03.19 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		int		iPlayerMeleeStrongAirMaxCount;			// �v���C���[�̋󒆂ł̋ߋ����U��(��)��(���G���U�����Ă��Ȃ��ꍇ�̍ő吔)		/* 2025.02.26 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		float	fPlayerMeleeStrongNextSearchRange;		// �v���C���[�̋ߋ����U��(��)��̍��G�͈�										/* 2025.03.23 �e�r�듹 �U���֘A�̕ϐ��ǉ� */
		float	fPlayerRockOnRadius;					// ���b�N�I���͈͂̔��a
		int		iStartHaveKunai;						// ������ԂŎ����Ă���N�i�C�̐�
		int		iMaxhaveKunai;							// �ő�Ŏ��Ă�N�i�C�̐�
		int		iPlayerKunaiCoolTime;					// �N�i�C�̃N�[���^�C��
		int		iPlayerMaxHp;							// �v���C���[�̍ő�HP
		int		iPlayerMaxInvincibleTime;				// �v���C���[�̍ő喳�G����


		/* �v���C���[�o�t�֘A(�G�f�B�b�g����) */
		float	fAddMoveSpeedUp;					// �ړ����x�㏸�l(���x/�t���[��)
		int		iAddBlood;							// �u���b�h(�Q�[�����ʉ�)�̓����(��)
		int		iAddComboTime;						// �R���{���ԑ����l(�t���[��)
		int		iAddAttackChargeFrameShortening;	// �`���[�W���ԒZ�k�l(�t���[��)
		int		iAddJumpCount;						// �W�����v�񐔑����l(��)
		int		iAddMeleeStrongAirMaxCount;			// �󒆂ł̋ߋ����U��(��)�񐔑����l(��)
		int		iAddKunaiKeepProbability;			// �N�i�C�ێ��m��(%)
		int		iAddBarrier;						// �o���A��(��)
		bool	bAddCounter;						// �J�E���^�[�ǉ��t���O(�L��/����)
		bool	bAddKunaiExplosion;					// �N�i�C�������t���O(�L��/����)
		bool	bAddMaxHpOne;						// �ő�HP1���t���O(�L��/����)
		int		iAddKunai;							// �N�i�C�ǉ���(��)
		
		/* Json�t�@�C���ł̃I�v�V�������ƕϐ��̑Ή��\ */
		std::vector<PLAYER_STATUS_LIST> astPlayerStatusList =
		{
			// �\�͒l����(Json��),									�Ή������ϐ�(�|�C���^),						�f�[�^�^
			{ BASE_STATUS_NAME_MOVE_ACCELERATION,					&fPlayerMoveAcceleration,					DATA_TYPE_FLOAT	},	// �v���C���[�̈ړ������x
			{ BASE_STATUS_NAME_JUMP_SPEED,							&fPlayerJumpSpeed,							DATA_TYPE_FLOAT	},	// �v���C���[�̃W�����v��(�ő吔)
			{ BASE_STATUS_NAME_FALL_ACCELERATION,					&fPlayerFallAcceleration,					DATA_TYPE_FLOAT	},	// �v���C���[�̗��������x
			{ BASE_STATUS_NAME_FALL_SPEED_MAX,						&fPlayerMaxFallSpeed,						DATA_TYPE_FLOAT	},	// �v���C���[�̍ő嗎�����x			
			{ BASE_STATUS_NAME_JUMP_COUNT_MAX,						&iPlayerMaxJumpCount,						DATA_TYPE_INT	},	// �v���C���[�̃W�����v��(�ő吔)
			{ BASE_STATUS_NAME_JUMP_COOL_TIME,						&iPlayerJumpCoolTime,						DATA_TYPE_INT	},	// �v���C���[�̃W�����v�N�[���^�C��										/* 2025.03.23 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_DODGE_SPEED,							&fPlayerDodgeSpeed,							DATA_TYPE_FLOAT	},	// �v���C���[�̉�𑬓x													/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_DODGE_FRAME,							&iPlayerMaxDodgeFlame,						DATA_TYPE_INT	},	// �v���C���[�̉���t���[����											/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_DODGE_COOL_TIME,						&iPlayerDodgeCoolTime,						DATA_TYPE_INT	},	// �v���C���[�̉���N�[���^�C��											/* 2025.03.23 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_KICKWALL_HORIZONTAL_SPEED,			&fPlayerKickWallHorizontalSpeed,			DATA_TYPE_FLOAT },	// �v���C���[�̕ǃL�b�N���x(��������)									/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_KICKWALL_VERTICAL_SPEED,				&fPlayerKickWallVerticalSpeed,				DATA_TYPE_FLOAT },	// �v���C���[�̕ǃL�b�N���x(��������)									/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_KICKWALL_FLAME,						&iPlayerKickWallFlame,						DATA_TYPE_INT	},	// �v���C���[�̕ǃL�b�N�p���t���[����									/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STASUS_NAME_KICKWALL_INPUT_MAX_FLAME,			&iPlayerKickWallInputMaxFlame,				DATA_TYPE_INT	},	// �v���C���[�̕ǃL�b�N���͗P�\�t���[����								/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_MELEE_WEAK_COOL_TIME,				&iPlayerMeleeWeakCoolTime,					DATA_TYPE_INT	},	// �v���C���[�̋ߋ����U��(��)�̃N�[���^�C��								/* 2025.03.23 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_MELEE_STRONG_CHANGE_CHARGE_FRAME,	&iPlayerMelleStrongChangeChargeFrame,		DATA_TYPE_INT	},	// �v���C���[�̋ߋ����U��(��)�ɐ؂�ւ��`���[�W�t���[����				/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_MELEE_STRONG_MAX_CHARGE_FRAME,		&iPlayerMelleStrongMaxChargeFrame,			DATA_TYPE_INT	},	// �v���C���[�̋ߋ����U��(��)�̍ő�`���[�W�t���[����					/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_MELEE_STRONG_MOVE_SCALE,				&fPlayerMelleStrongMoveScale,				DATA_TYPE_FLOAT	},	// �v���C���[�̋ߋ����U��(��)�̈ړ������̃X�P�[��						/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_MELEE_STRONG_MOVE_SPEED,				&fPlayerMelleStrongMoveSpeed,				DATA_TYPE_FLOAT	},	// �v���C���[�ߋ����U��(��)�̈ړ����x									/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_MELEE_STRONG_CONTINUS_MAX_FRAME,		&iPlayerMeleeStrongContinusMaxFrame,		DATA_TYPE_INT	},	// �v���C���[�ߋ����U��(��)�ŘA���U���ł���ő�t���[����				/* 2025.03.19 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_MELEE_STRONG_AIR_MAX_COUNT,			&iPlayerMeleeStrongAirMaxCount,				DATA_TYPE_INT	},	// �v���C���[���󒆂ŋߋ����U��(��)���s����ő��(���G���U�����Ă��Ȃ��ꍇ)
			{ BASE_STATUS_NAME_MELEE_STRONG_NEXT_SEARCH_RANGE,		&fPlayerMeleeStrongNextSearchRange,			DATA_TYPE_FLOAT	},	// �v���C���[���ߋ����U��(��)���s������̍��G�͈�						/* 2025.03.23 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_ROCK_ON_RADIUS,						&fPlayerRockOnRadius,						DATA_TYPE_FLOAT	},	// ���b�N�I���͈͂̔��a
			{ BASE_STATUS_NAME_START_HAVE_KUNAI,					&iStartHaveKunai,							DATA_TYPE_INT	},	// ������ԂŎ����Ă���N�i�C�̌�
			{ BASE_STATUS_NAME_MAX_HAVE_KUNAI,						&iMaxhaveKunai,								DATA_TYPE_INT	},	// �ő�Ŏ��Ă�N�i�C�̌�
			{ BASE_STATUS_NAME_KUNAI_COOL_TIME,						&iPlayerKunaiCoolTime,							DATA_TYPE_INT	},	// �N�i�C�̃N�[���^�C��													/* 2025.03.23 �e�r�듹 �ǉ� */
			{ BASE_STATUS_NAME_HP_MAX,								&iPlayerMaxHp,								DATA_TYPE_INT	},	// �v���C���[�̍ő�HP
			{ BASE_STATUS_NAME_INVINCIBLE_TIME_MAX,					&iPlayerMaxInvincibleTime,					DATA_TYPE_INT	},	// �v���C���[�̍ő喳�G����
		};
};
