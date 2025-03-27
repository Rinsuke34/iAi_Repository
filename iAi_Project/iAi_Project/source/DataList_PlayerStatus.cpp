/* 2024.12.26 ��򕗏� �t�@�C���쐬 */
/* 2025.01.10 �e�r�듹 �����������ǉ�  */
/* 2025.01.22 �e�r�듹 �����������ǉ�  */
/* 2025.02.10 �e�r�듹 �����������ǉ� */
/* 2025.02.11 �e�r�듹 �����������ǉ� */
/* 2025.02.22 �e�r�듹 �����������ǉ� */
/* 2025.02.26 �e�r�듹 �����������ǉ� */
/* 2025.03.03 �e�r�듹 �����������ǉ� */
/* 2025.03.11 �e�r�듹 �����������ǉ� */
/* 2025.03.17 �e�r�듹 �����������ǉ� */
/* 2025.03.19 �e�r�듹 �����������ǉ� */
/* 2025.03.23 �e�r�듹 �����������ǉ� */

#include "DataList_PlayerStatus.h"
#include <vector>
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
	this->vecPlayerDodgeDirection			= { 0, 0, 0 };						//�v���C���[������												/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerDodgeWhileJumpingCount		= 0;								//�v���C���[�W�����v���̉����									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->iPlayerNowDodgeFlame				= 0;								//�v���C���[�̌��݂̉���t���[����									/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->fPlayerDodgeSpeed					= 0;								//�v���C���[��𑬓x												/* 2025.01.10 �e�r�듹 �����������ǉ� */
	this->bPlayerWallTouchFlg				= false;							//�v���C���[���ǂɐڐG�������̃t���O								/* 2025.03.17 �e�r�듹 �����������ǉ� */
	this->iPlayerAfterWallTouchCount		= 0;								//�v���C���[���ǂɐڐG���Ă���̌o�߃t���[����						/* 2025.03.17 �e�r�듹 �����������ǉ� */
	this->bPlayerKickWallFlg				= false;							//�v���C���[���ǂ��R�������̃t���O									/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->iPlayerAfterKickWallCount			= 0;								//�v���C���[���ǂ��R������̃J�E���g								/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->bPlayerAfterKickWallFlg			= false;							//�v���C���[���ǂ��R������̃t���O									/* 2025.02.22 �e�r�듹 �����������ǉ� */
	this->iPlayerNowAttakChargeFlame		= 0;								//���݂̃v���C���[���ߍU���`���[�W�t���[����						/* 2025.01.22 �e�r�듹 �����������ǉ� */
	this->vecPlayerChargeAttakTargetMove	= { 0, 0, 0 };						//�v���C���[���ߍU���̖ړI�n										/* 2025.01.22 �e�r�듹 �����������ǉ� */
	this->iPlayerMeleeStrongChargeCount		= 0;								// �v���C���[���ߋ����U��(��)��ԂɂȂ��Ă���̃`���[�W�t���[����
	this->iPlayerMeleeStrongAirCount		= 0;								// �v���C���[���󒆂ŋߋ����U��(��)���s������(���G���U�����Ă��Ȃ��ꍇ)		/* 2025.02.26 �e�r�듹 �����������ǉ� */
	this->bPlayerMeleeStrongEnemyAttackFlg	= false;							// �v���C���[���ߋ����U��(��)�œG���U���������̃t���O							/* 2025.03.03 �e�r�듹 �����������ǉ� */
	this->iPlayerMeleeStrongAfterCount		= 0;								// �v���C���[���ߋ����U��(��)�œG���U��������̃t���[����						/* 2025.03.03 �e�r�듹 �����������ǉ� */
	this->iMeleeStrongDestroyCount			= 0;								// �v���C���[���ߋ����U��(��)�Ō��j�����G�̐�									/* 2025.03.18 �e�r�듹 �����������ǉ� */
	this->bPlayerMeleeStrongContinuousFlg	= false;							// �v���C���[���A���ŋߋ����U��(��)�ł��邩�̃t���O								/* 2025.03.17 �e�r�듹 �����������ǉ� */
	this->bPlayerLandingAfterMeleeStrongFlg = false;							// �v���C���[���ߋ����U��(��)��ɒ��n���Ă��邩�̃t���O							/* 2025.03.23 �e�r�듹 �����������ǉ� */
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
	this->iNowHaveKunai						= 0;								// ���ݎ����Ă���N�i�C�̐�
	this->bStartFastMotion					= false;							// �J�n�����[�V�����J�n�t���O
	this->iFastMotionCount					= 0;								// �J�n�����[�V�����J�E���g
	this->iPlayerComboRunk					= 0;								// ���݂̃R���{�����N

	/* �v���C���[���[�V�����֘A */
	this->iPlayerMotion_Move				= MOTION_ID_MOVE_WAIT;			// �v���C���[���[�V����(�ړ��n)
	this->iPlayerMotion_Move_Old			= MOTION_ID_MOVE_WALK;			// �ύX�O�v���C���[���[�V����(�ړ��n)
	this->fMotionTimer_Move					= 0;							// ���[�V�����^�C�}�[(�ړ��n)
	this->fMotionTimer_Move_Old				= 0;							// �ύX�O���[�V�����^�C�}�[(�ړ��n)
	this->fMotionTimer_Move_End				= 0;							// ���[�V�����^�C�}�[(�ړ��n/�I������)
	this->fMotionTimer_Move_Old_End			= 0;							// �ύX�O���[�V�����^�C�}�[(�ړ��n/�I������)
	this->iPlayerMotionAttachIndex_Move		= 0;							// �v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�		
	this->iPlayerMotionAttachIndex_Move_Old	= 0;							// �ύX�O�v���C���[���[�V����(�ړ��n)�̃A�^�b�`�ԍ�
	this->fNowMoveMotionBlendRate			= 0;							// ���݂̈ړ����[�V�����̃u�����h��

	this->iPlayerMotion_Attack					= MOTION_ID_ATTACK_NONE;	// �v���C���[���[�V����(�U���n)
	this->iPlayerMotion_Attack_Old				= MOTION_ID_ATTACK_NONE;	// �ύX�O�v���C���[���[�V����(�U���n)
	this->fMotionTimer_Attack					= 0;						// ���[�V�����^�C�}�[(�U���n)
	this->fMotionTimer_Attack_Old				= 0;						// �ύX�O���[�V�����^�C�}�[(�U���n)
	this->fMotionTimer_Attack_End				= 0;						// ���[�V�����^�C�}�[(�U���n/�I������)
	this->fMotionTimer_Attack_Old_End			= 0;						// �ύX�O���[�V�����^�C�}�[(�U���n/�I������)
	this->iPlayerMotionAttachIndex_Attack		= 0;						// �v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�	
	this->iPlayerMotionAttachIndex_Attack_Old	= 0;						// �ύX�O�v���C���[���[�V����(�U���n)�̃A�^�b�`�ԍ�
	this->fNowAttackMotionBlendRate				= 0;						// ���݂̍U�����[�V�����̃u�����h��

	/* ���菈���p�R���W���� */
	this->bMeleeSearchCollisionUseFlg		= false;

	/* �\�͒l�֘A(���v���C���[�̑������ɂ���ď㉺����\���̂���X�e�[�^�X))*/
	this->fPlayerMoveAcceleration			= 0;	// �v���C���[�̈ړ������x
	this->fPlayerJumpSpeed					= 0;	// �v���C���[�W�����v���x
	this->fPlayerFallAcceleration			= 0;	// �v���C���[�̗��������x
	this->fPlayerMaxFallSpeed				= 0;	// �v���C���[�̍ő嗎�����x
	this->iPlayerMaxJumpCount				= 0;	// �v���C���[�̃W�����v��(�ő吔)
	this->iPlayerJumpCoolTime					= 0;	// �v���C���[�̃W�����v�̃N�[���^�C��											/* 2025.03.23 �e�r�듹 �����������ǉ� */
	this->fPlayerDodgeSpeed					= 0;	// �v���C���[��𑬓x															/* 2025.01.10 �e�r�듹 �����������ǉ�  */
	this->iPlayerDodgeCoolTime					= 0;	// �v���C���[�̉���̃N�[���^�C��												/* 2025.03.23 �e�r�듹 �����������ǉ� */
	this->iPlayerMaxDodgeFlame				= 0;	// �v���C���[�̉���ő�t���[����												/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->fPlayerKickWallHorizontalSpeed	= 0;	// �v���C���[�̕ǃL�b�N���x(��������)											/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->fPlayerKickWallVerticalSpeed		= 0;	// �v���C���[�̕ǃL�b�N���x(��������)											/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->iPlayerKickWallFlame				= 0;	// �v���C���[�̕ǃL�b�N�p���t���[����											/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->iPlayerKickWallInputMaxFlame		= 0;	// �v���C���[�̕ǃL�b�N���͗P�\�t���[����
	this->iPlayerMeleeWeakCoolTime				= 0;	// �v���C���[�̋ߋ����U��(��)�̃N�[���^�C��										/* 2025.03.23 �e�r�듹 �����������ǉ� */
	this->iPlayerMelleStrongChangeChargeFrame	= 0;	// �v���C���[�̋ߋ����U��(��)�ɐ؂�ւ��`���[�W�t���[����						/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->iPlayerMelleStrongMaxChargeFrame		= 0;	// �v���C���[�̋ߋ����U��(��)�̍ő�`���[�W�t���[����							/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->fPlayerMelleStrongMoveScale			= 0;	// �v���C���[�̋ߋ����U��(��)�̈ړ������̃X�P�[��								/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->fPlayerMelleStrongMoveSpeed			= 0;	// �v���C���[�̋ߋ����U��(��)�̈ړ����x											/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->iPlayerMeleeStrongContinusMaxFrame	= 0;	// �v���C���[�̋ߋ����U��(��)�̘A���ő�t���[����								/* 2025.03.19 �e�r�듹 �����������ǉ� */
	this->iPlayerMeleeStrongAirMaxCount			= 0;	// �v���C���[�̋󒆂ł̋ߋ����U��(��)��(���G���U�����Ă��Ȃ��ꍇ�̍ő吔)		/* 2025.02.26 �e�r�듹 �����������ǉ� */
	this->fPlayerMeleeStrongNextSearchRange		= 0;	// �v���C���[�̋ߋ����U��(��)��̍��G�͈�										/* 2025.03.23 �e�r�듹 �����������ǉ� */
	this->fPlayerRockOnRadius				= 0;	// ���b�N�I���͈͂̔��a
	this->iStartHaveKunai					= 0;	// ������ԂŎ����Ă���N�i�C�̐�
	this->iMaxhaveKunai						= 0;	// �ő�Ŏ��Ă�N�i�C�̐�
	this->iPlayerKunaiCoolTime					= 0;	// �N�i�C�̃N�[���^�C��															/* 2025.03.23 �e�r�듹 �����������ǉ� */
	this->iPlayerMaxHp							= 0;	// �v���C���[�̍ő�HP
	this->iPlayerMaxInvincibleTime				= 0;	// �v���C���[�̍ő喳�G����
	

	/* �v���C���[�o�t�֘A(�G�f�B�b�g����) */
	this->fAddMoveSpeedUp					= 0;		// �ړ����x�㏸�l(���x/�t���[��)
	this->iAddBlood							= 0;		// �u���b�h(�Q�[�����ʉ�)�̓����(��)
	this->iAddComboTime						= 0;		// �R���{���ԑ����l(�t���[��)
	this->iAddAttackChargeFrameShortening	= 0;		// �`���[�W���ԒZ�k�l(�t���[��)
	this->iAddJumpCount						= 0;		// �W�����v�񐔑����l(��)
	this->iAddMeleeStrongAirMaxCount		= 0;		// �󒆂ł̋ߋ����U��(��)�񐔑����l(��)
	this->iAddKunaiKeepProbability			= 0;		// �N�i�C�ێ��m��(%)
	this->iAddBarrier						= 0;		// �o���A��(��)
	this->bAddCounter						= false;	// �J�E���^�[�ǉ��t���O(�L��/����)
	this->bAddMaxHpOne						= false;	// �ő�HP1���t���O(�L��/����)
	this->iAddKunai							= 0;		// �N�i�C�{�������l(��)
	this->iAddFallSpeedDown					= 0;		// �������x����l(���x/�t���[��)

	/* �X�e�[�^�X�f�[�^�̓ǂݍ��� */
	LoadPlayerStatuxData();
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

	/* HP���ݒl��HP�ő�l�ɐݒ� */
	this->iPlayerNowHp = this->iPlayerMaxHp;

	/* �N�i�C�{����������Ԃł̃N�i�C�{���ɐݒ� */
	this->iNowHaveKunai = this->iStartHaveKunai;
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

// �v���C���[�o�t�X�V
void DataList_PlayerStatus::StatusBuffUpdate()
{
	/* �X�e�[�^�X�f�[�^�̓ǂݍ��� */
	LoadPlayerStatuxData();

	/* ���݂̃G�f�B�b�g���ɉ����ăv���C���[�o�t�֘A���X�V���� */
	/* �S�X�e�[�^�X������ */
	this->fAddMoveSpeedUp					= 0;		// �ړ����x�㏸�l(���x/�t���[��)
	this->iAddBlood							= 0;		// �u���b�h(�Q�[�����ʉ�)�̓����(��)
	this->iAddComboTime						= 0;		// �R���{���ԑ����l(�t���[��)
	this->iAddAttackChargeFrameShortening	= 0;		// �`���[�W���ԒZ�k�l(�t���[��)
	this->iAddJumpCount						= 0;		// �W�����v�񐔑����l(��)
	this->iAddMeleeStrongAirMaxCount		= 0;		// �󒆂ł̋ߋ����U��(��)�񐔑����l(��)
	this->iAddKunaiKeepProbability			= 0;		// �N�i�C�ێ��m��(%)
	this->iAddBarrier						= 0;		// �o���A��(��)
	this->bAddCounter						= false;	// �J�E���^�[�ǉ��t���O(�L��/����)
	this->bAddMaxHpOne						= false;	// �ő�HP1���t���O(�L��/����)
	this->iAddKunai							= 0;		// �N�i�C�{�������l(��)
	this->iAddFallSpeedDown					= 0;		// �������x����l(���x/�t���[��)

	/* "�Q�[�������\�[�X�Ǘ�"���擾 */
	DataList_GameResource* GameResource = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

	/* ���݂̃G�f�B�b�g�����擾 */
	for (int i = 0; i < EDIT_MAX; i++)
	{
		/* �G�f�B�b�g���擾 */
		EDIT_DATA EditData = GameResource->stGetNowEditData(i);

		/* �G�f�B�b�g�̌��ʗʂ��擾 */
		int iEffectValue = 0;
		for (auto& data : GameResource->GetEffectValueList())
		{
			/* �G�f�B�b�g�̎�ނƃ����N�������ł��邩�m�F */
			if ((EditData.iEditEffect == data.iEditEffect) && (EditData.iEditRank == data.iEditRank))
			{
				// �����ł���ꍇ
				iEffectValue = data.iValue;
				break;
			}
		}
		
		/* �G�f�B�b�g���ɉ����ăv���C���[�o�t�֘A���X�V���� */
		switch (EditData.iEditEffect)
		{
			/* �ʏ� */
			// �ړ����x�A�b�v
			case EDIT_EFFECT_NORMAL_MOVE_SPEED_UP:
				/* ���ʗʕ����Z���� */
				this->fAddMoveSpeedUp += static_cast<float>(iEffectValue);
				break;

			// �u���b�h�擾�ʃA�b�v
			case EDIT_EFFECT_NORMAL_GET_BLOOD_UP:
				/* ���ʗʕ����Z���� */
				this->iAddBlood += iEffectValue;
				break;

			// �R���{�p�����ԃA�b�v
			case EDIT_EFFECT_NORMAL_COMBO_DURATION_UP:
				/* ���ʗʕ����Z���� */
				// ���P�ʂ�b���t���[���ɕϊ�
				this->iAddComboTime += (iEffectValue * 60);
				break;

			// �ߐڍU�����ߎ��Ԍ���
			case EDIT_EFFECT_NORMAL_MELEE_CHARGE_REDUCTION:
				/* ���ʗʕ����Z���� */
				this->iAddAttackChargeFrameShortening += iEffectValue;
				break;

			// �W�����v�񐔃A�b�v
			case EDIT_EFFECT_NORMAL_JUMP_COUNT_UP:
				/* ���ʗʕ����Z���� */
				this->iAddJumpCount += iEffectValue;
				break;

			// �󒆋����U���񐔃A�b�v
			case EDIT_EFFECT_NORMAL_AIR_MELEE_COUNT_UP:
				/* ���ʗʕ����Z���� */
				this->iAddMeleeStrongAirMaxCount += iEffectValue;
				break;

			// �N�i�C����m������
			case EDIT_EFFECT_NORMAL_KUNAI_KEEP:
				/* ���ʗʕ����Z���� */
				this->iAddKunaiKeepProbability += iEffectValue;
				break;

			// �o���A�񐔃A�b�v
			case EDIT_EFFECT_NORMAL_BARIER_COUNT_UP:
				/* ���ʗʕ����Z���� */
				this->iAddBarrier += iEffectValue;
				break;


			// �N�i�C�{������
			case EDIT_EFFECT_NORMAL_GET_KUNAI_UP:
				this->iAddKunai	+= iEffectValue;
				break;

			/* ���� */
			// �J�E���^�[�A�N�V�����ǉ�
			case EDIT_EFFECT_SPECIAL_COUNTER:
				/* �L���ɐݒ肷�� */
				this->bAddCounter = true;
				break;

			// �N�i�C���[�v��
			case EDIT_EFFECT_KUNAI_WARP:
				/* �L���ɐݒ肷�� */
				this->bAddKunaiWarp = true;
				break;

			// �������x�ቺ
			case EDIT_EFFECT_FALL_SPEED_DOWN:
				/* ���ʗʂɐݒ肷�� */
				// �����Z�͂��Ȃ�
				this->iAddFallSpeedDown = iEffectValue;
				break;

			/* �� */
			// HP1����
			case EDIT_EFFECT_CURCE_LIMIT_HP_ONE:
				/* �L���ɐݒ肷�� */
				this->bAddMaxHpOne = true;
				break;
		}
	}
}
