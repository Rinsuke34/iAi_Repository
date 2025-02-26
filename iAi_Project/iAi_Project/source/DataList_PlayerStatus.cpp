/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.10 �e�r�듹 �����������ǉ�  */
/* 2025.01.22 �e�r�듹 �����������ǉ�  */
/* 2025.02.10 �e�r�듹 �����������ǉ� */
/* 2025.02.11 �e�r�듹 �����������ǉ� */
/* 2025.02.22 �e�r�듹 �����������ǉ� */

#include "DataList_PlayerStatus.h"

/* �v���C���[�X�e�[�^�X�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* ������(��) */
	/* �v���C���[��Ԋ֘A */
	this->iPlayerMoveState					= PLAYER_MOVESTATUS_FREE;			// �v���C���[�̈ړ����
	this->iPlayerAttackState				= PLAYER_ATTACKSTATUS_FREE;			// �v���C���[�̍U�����
	this->bPlayerLandingFlg					= false;							// �v���C���[�����n���Ă��邩
	this->fPlayerNowMoveSpeed				= 0;								// �v���C���[�̌��݂̈ړ����x
	this->fPlayerAngleX						= 0;								// �v���C���[��X����]��(���W�A��)
	this->fPlayerTurnSpeed					= PLAYER_TURN_SPEED;				// �v���C���[�̕����]���̑��x										/* 2025.02.10 �e�r�듹 �����������ǉ� */
	this->fPlayerNowFallSpeed				= 0;								// �v���C���[�̌��݂̗������x
	this->iPlayerNowJumpCount				= 0;								// �v���C���[�̃W�����v��(���ݐ�)
	this->iPlayerNormalDashFlameCount		= 0;								//�ʏ�_�b�V�����o�߃t���[�����i�����_�b�V���ւ̈ڍs�Ɏg�p			/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->bPlayerJumpingFlag				= false;							//�v���C���[���W�����v�����̃t���O									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerJumpCount					= 0;								//�v���C���[�̌��݂̃W�����v��									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->fPlayerDodgeProgress				= 0.0f;								//�v���C���[������[�V�����i�s�x									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };						//�v���C���[������												/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerDodgeWhileJumpingCount		= 0;								//�v���C���[�W�����v���̉����									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->fPlayerJumpSpeed					= 0;								//�v���C���[�W�����v���x											/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerNowDodgeFlame				= 0;								//�v���C���[�̌��݂̉���t���[����									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->fPlayerDodgeSpeed					= 0;								//�v���C���[��𑬓x												/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->bPlayerAfterDodgeFlag				= false;							//�v���C���[�̉����t���O											/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->bPlayerKickWallFlg				= false;							//�v���C���[���ǂ��R�������̃t���O									/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->iPlayerAfterKickWallCount			= 0;								//�v���C���[���ǂ��R������̃J�E���g								/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->bPlayerAfterKickWallFlg			= false;							//�v���C���[���ǂ��R������̃t���O									/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->iPlayerNowAttakChargeFlame		= 0;								//���݂̃v���C���[���ߍU���`���[�W�t���[����						/* 2025.01.22 �e�r�듹 �����������ǉ� */
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };						//�v���C���[���ߍU���̖ړI�n										/* 2025.01.22 �e�r�듹 �����������ǉ� */
	this->iPlayerChargeAttackCount			= 0;								// �ߐڍU��(��)�̃J�E���g
	this->pLockOnEnemy						= nullptr;							// ���b�N�I���Ώۂ̃G�l�~�[
	this->iPlayerNowHp						= INIT_ATTRIBUTES_HP_MAX;			// �v���C���[�̌��݂�HP
	this->iPlayerNowInvincibleTime			= 0;								// �v���C���[�̌��݂̎c�薳�G����
	this->iPlayerComboNowCount				= 0;								// �v���C���[�̌��݂̃R���{��
	this->iPlayerComboMaxCount				= 0;								// �v���C���[�̍ő�R���{��
	this->iPlayerComboDuration				= 0;								// �v���C���[�̃R���{�̎c�莝������
	this->bPlayerAimCancelledFlg			= false;							// �������U��(�\��)���L�����Z�����ꂽ���̃t���O		/* 2025.02.11 �e�r�듹 �����������ǉ� */
	this->bPlayerDeadFlg					= false;							// �v���C���[���S�t���O

	/* �v���C���[���[�V�����֘A */
	this->iPlayerMotion_Move				= MOTION_ID_MOVE_WAIT;				// �v���C���[���[�V����(�ړ��n)
	this->iPlayerMotion_Move_Old			= -1;								// �ύX�O�v���C���[���[�V����(�ړ��n)
	this->iPlayerMotion_Attack				= MOTION_ID_ATTACK_NONE;			// �v���C���[���[�V����(�U���n)
	this->iPlayerMotion_Attack_Old			= -1;								// �ύX�O�v���C���[���[�V����(�U���n)
	
	this->fMotionTimer_Move					= 0;								// ���[�V�����J�E���g(�ړ��n)
	this->fMotionTimer_Move_End				= 1;								// ���[�V�����J�E���g(�ړ��n/�I������)(�����������̕s��h�~�̂���1�ɐݒ�)
	this->fMotionTimer_Attack				= 0;								// ���[�V�����J�E���g(�U���n)
	this->fMotionTimer_Attack_End			= 1;								// ���[�V�����J�E���g(�U���n/�I������)(�����������̕s��h�~�̂���1�ɐݒ�)

	/* ���菈���p�R���W���� */
	this->bMeleeSearchCollisionUseFlg		= false;
	
	/* �\�͒l�֘A */
	this->fPlayerMoveAcceleration			= INIT_ATTRIBUTES_MOVE_ACCELERATION;	// �v���C���[�̈ړ������x
	this->fPlayerMaxMoveSpeed				= INIT_ATTRIBUTES_MOVE_SPEED_MAX;		// �v���C���[�̍ő�ړ����x
	this->fPlayerFallAcceleration			= INIT_ATTRIBUTES_FALL_ACCELERATION;	// �v���C���[�̗��������x
	this->fPlayerMaxFallSpeed				= INIT_ATTRIBUTES_FALL_SPEED_MAX;		// �v���C���[�̍ő嗎�����x
	this->iPlayerMaxJumpCount				= INIT_ATTRIBUTES_JUMP_COUNT_MAX;		// �v���C���[�̃W�����v��(�ő吔)
	this->fPlayerRockOnRadius				= INIT_ATTRIBUTES_ROCK_ON_RADIUS;		// ���b�N�I���͈͂̔��a
	this->iPlayerMaxHp						= INIT_ATTRIBUTES_HP_MAX;				// �v���C���[�̍ő�HP
	this->iPlayerMaxInvincibleTime			= INIT_ATTRIBUTES_INVINCIBLE_TIME_MAX;	// �v���C���[�̍ő喳�G����
}

// �f�X�g���N�^
DataList_PlayerStatus::~DataList_PlayerStatus()
{

}
