/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.10 �e�r�듹 �����������ǉ�  */
/* 2025.01.22 �e�r�듹 �����������ǉ�  */
/* 2025.02.10 �e�r�듹 �����������ǉ� */
/* 2025.02.11 �e�r�듹 �����������ǉ� */
/* 2025.02.22 �e�r�듹 �����������ǉ� */
/* 2025.02.26 �e�r�듹 �����������ǉ� */
/* 2025.03.03 �e�r�듹 �����������ǉ� */
/* 2025.03.11 �e�r�듹 �����������ǉ� */

#include "DataList_PlayerStatus.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �v���C���[�X�e�[�^�X�Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_PlayerStatus::DataList_PlayerStatus() : DataListBase("DataList_PlayerStatus")
{
	/* ������ */
	/* �v���C���[��Ԋ֘A */
	this->iPlayerMoveState					= PLAYER_MOVESTATUS_FREE;			// �v���C���[�̈ړ����
	this->iPlayerAttackState				= PLAYER_ATTACKSTATUS_FREE;			// �v���C���[�̍U�����
	this->bPlayerLandingFlg					= false;							// �v���C���[�����n���Ă��邩
	this->fPlayerNowMoveSpeed				= 0;								// �v���C���[�̌��݂̈ړ����x
	this->fPlayerAngleX						= 0;								// �v���C���[��X����]��(���W�A��)
	this->fPlayerTurnSpeed					= PLAYER_TURN_SPEED;				// �v���C���[�̕����]���̑��x	/* 2025.02.10 �e�r�듹 �����������ǉ� */
	this->fPlayerNowFallSpeed				= 0;								// �v���C���[�̌��݂̗������x
	this->iPlayerNowJumpCount				= 0;								// �v���C���[�̃W�����v��(���ݐ�)
	this->bPlayerJumpingFlag				= false;							//�v���C���[���W�����v�����̃t���O									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerJumpCount					= 0;								//�v���C���[�̌��݂̃W�����v��									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->fPlayerDodgeProgress				= 0.0f;								//�v���C���[������[�V�����i�s�x									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };						//�v���C���[������												/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerDodgeWhileJumpingCount		= 0;								//�v���C���[�W�����v���̉����									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->fPlayerJumpSpeed					= 0;								//�v���C���[�W�����v���x											/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerNowDodgeFlame				= 0;								//�v���C���[�̌��݂̉���t���[����									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->fPlayerDodgeSpeed					= 0;								//�v���C���[��𑬓x												/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->bPlayerKickWallFlg				= false;							//�v���C���[���ǂ��R�������̃t���O									/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->iPlayerAfterKickWallCount			= 0;								//�v���C���[���ǂ��R������̃J�E���g								/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->bPlayerAfterKickWallFlg			= false;							//�v���C���[���ǂ��R������̃t���O									/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->iPlayerNowAttakChargeFlame		= 0;								//���݂̃v���C���[���ߍU���`���[�W�t���[����						/* 2025.01.22 �e�r�듹 �����������ǉ� */
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };						//�v���C���[���ߍU���̖ړI�n										/* 2025.01.22 �e�r�듹 �����������ǉ� */
	this->iPlayerMeleeStrongChargeCount		= 0;								// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[����
	this->iPlayerMeleeStrongAirCount		= 0;								// �v���C���[���󒆂ŋߋ����U��(��)���s������(���G���U�����Ă��Ȃ��ꍇ)		/* 2025.02.26 �e�r�듹 �����������ǉ� */
	this->bPlayerMeleeStrongEnemyAttackFlg	= false;							// �v���C���[���ߋ����U��(��)�œG���U���������̃t���O							/* 2025.03.03 �e�r�듹 �����������ǉ� */
	this->iPlayerMeleeStrongAfterCount		= 0;								// �v���C���[���ߋ����U��(��)�œG���U��������̃J�E���g							/* 2025.03.03 �e�r�듹 �����������ǉ� */
	this->iPlayerSlowMotionCount			= 0;								// �v���C���[�̃X���[���[�V�����J�E���g											/* 2025.03.11 �e�r�듹 �����������ǉ� */
	this->pLockOnEnemy						= nullptr;							// ���b�N�I���Ώۂ̃G�l�~�[
	this->iPlayerNowInvincibleTime			= 0;								// �v���C���[�̌��݂̎c�薳�G����
	this->iPlayerComboNowCount				= 0;								// �v���C���[�̌��݂̃R���{��
	this->iPlayerComboMaxCount				= 0;								// �v���C���[�̍ő�R���{��
	this->iPlayerComboDuration				= 0;								// �v���C���[�̃R���{�̎c�莝������
	this->bPlayerAimCancelledFlg			= false;							// �������U��(�\��)���L�����Z�����ꂽ���̃t���O		/* 2025.02.11 �e�r�듹 �����������ǉ� */
	this->bPlayerDeadFlg					= false;							// �v���C���[���S�t���O
	this->iPlayerDamageCount				= 0;								// ��_���[�W��
	this->bFallFlg							= false;							// �����t���O

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

	/* �X�e�[�^�X�f�[�^�̓ǂݍ��� */
	LoadPlayerStatuxData();

	/* HP���ݒl��HP�ő�l�ɐݒ� */
	this->iPlayerNowHp = this->iPlayerMaxHp;
}

// �f�X�g���N�^
DataList_PlayerStatus::~DataList_PlayerStatus()
{
	/* �X�e�[�^�X�f�[�^�̕ۑ� */
	SavePlayerStatuxData();
}

// �X�e�[�^�X�f�[�^�ǂݍ���
void DataList_PlayerStatus::LoadPlayerStatuxData()
{
	/* Json�t�@�C���W�J */
	std::ifstream inputFile(FILE_PATH_STATUS);

	/* �t�@�C���̓W�J�������������m�F */
	if (inputFile.is_open() == true)
	{
		// �t�@�C�������݂���ꍇ
		/* ���݂̃X�e�[�W�̊e�]���̊�l���擾���� */
		nlohmann::json	json;
		inputFile >> json;

		for (auto& option : this->astPlayerStatusList)
		{
			if (json.contains(option.Name) && json[option.Name].contains("value"))
			{
				if (option.Type == DATA_TYPE_BOOL)
				{
					*static_cast<bool*>(option.pValue) = json[option.Name]["value"].get<bool>();
				}
				else if (option.Type == DATA_TYPE_INT)
				{
					*static_cast<int*>(option.pValue) = json[option.Name]["value"].get<int>();
				}
				else if (option.Type == DATA_TYPE_FLOAT)
				{
					*static_cast<float*>(option.pValue) = json[option.Name]["value"].get<float>();
				}
			}
		}
	}
}

// �X�e�[�^�X�f�[�^�ۑ�
void DataList_PlayerStatus::SavePlayerStatuxData()
{
	/* Json�t�@�C���ǂݍ��� */
	nlohmann::json json;

	/* �ϐ����X�g�����[�v���� JSON �ɏ������� */
	for (auto& option : this->astPlayerStatusList)
	{
		if (option.Type == DATA_TYPE_BOOL)
		{
			json[option.Name]["value"] = *static_cast<bool*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_INT)
		{
			json[option.Name]["value"] = *static_cast<int*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_FLOAT)
		{
			json[option.Name]["value"] = *static_cast<float*>(option.pValue);
		}
	}

	/* Json�t�@�C���W�J */
	std::ofstream outputFile(FILE_PATH_STATUS);

	/* Json�t�@�C���������� */
	outputFile << json.dump(4);
}
