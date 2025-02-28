/* 2025.01.16 �t�@�C���쐬 ��򕗏� */

#include "SceneStage.h"

/* �I�u�W�F�N�g */
// ��������(�������肷��\������)
// �v���C���[
#include "CharacterPlayer.h"
// �G�l�~�[
#include "EnemyNormal.h"
#include "EnemyEscape.h"
#include "EnemyGoalObject.h"
#include "EnemyNormal.h"
#include "EnemyMissile.h"
#include "EnemyBeam.h"
#include "Enemy_Explosion.h"
// �v���b�g�t�H�[��
#include "PlatformBasic.h"
// �X�J�C�X�t�B�A
#include "SkySqhereBasic.h"
// �M�~�b�N
#include "GimmickDisappear.h"
#include "Gimmick_ForcedJump_Spawn.h"

/* �X�e�[�W�N���X�̒�`(�}�b�v�ǂݍ��ݕ���) */

// �}�b�v�f�[�^�̃��[�h
void SceneStage::LoadMapData()
{
	/* ���݂̃X�e�[�W�ԍ����擾 */
	int iStageNo = this->StageStatusList->iGetNowStageNo();

	/* �}�b�v�����擾 */
	std::string MapName = STAGE_NAME[iStageNo];

	/* �}�b�v�f�[�^�̓ǂݍ��� */
	{
		/* �ǂݍ��݂����}�b�v�f�[�^�̃p�X�ݒ� */
		// ���t�@�C�����ƃX�e�[�W������v����悤�ɂ���
		std::string Path = "resource/MapData/";
		std::string Format = MapName + ".json";
		std::ifstream file(Path + Format);

		/* Json�t�@�C���ǂݍ��� */
		nlohmann::json json;
		file >> json;

		/* �v���b�g�t�H�[��(�`�ʃI�u�W�F�N�g)�ǂݍ��� */
		{
			/* Json�t�@�C������ǂݍ��� */
			std::string Type = "/Object";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
			{
				/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���b�g�t�H�[����ǉ� */
				PlatformBase* pPlatform = new PlatformBase();
				this->ObjectList->SetPlatform(pPlatform);

				/* ���f�� */
				std::string	name;
				data.at("objectName").get_to(name);
				std::string Path = "Object/" + name + "/" + name;
				pPlatform->SetModelHandle(this->ModelList->iGetModel(Path));

				/* ���W */
				VECTOR vecPos;
				// �ǂݍ���
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z���W���]
				vecPos.z *= -1;
				// �ݒ�
				pPlatform->SetPosition(vecPos);

				/* ��]�� */
				VECTOR vecRot;
				// �ǂݍ���
				data.at("rotate").at("x").get_to(vecRot.x);
				data.at("rotate").at("z").get_to(vecRot.y);
				data.at("rotate").at("y").get_to(vecRot.z);
				// degree -> radian�ϊ�
				vecRot.x = DEG2RAD(vecRot.x);
				vecRot.y = DEG2RAD(vecRot.y);
				vecRot.z = DEG2RAD(vecRot.z);
				// X���̉�]�����𔽓]
				// �����������s���ȏ���
				vecRot.x *= -1;
				// �ݒ�
				pPlatform->SetRotation(vecRot);

				/* �g�嗦 */
				VECTOR vecScale;
				// �ǂݍ���
				data.at("scale").at("x").get_to(vecScale.x);
				data.at("scale").at("z").get_to(vecScale.y);
				data.at("scale").at("y").get_to(vecScale.z);
				// �ݒ�
				pPlatform->SetScale(vecScale);
			}
		}

		/* �}�[�J�[�ǂݍ��� */
		{
			/* Json�t�@�C������ǂݍ��� */
			std::string Type = "/Marker";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
			{
				/* �}�[�J�[���擾 */
				std::string	name;
				data.at("objectName").get_to(name);

				/* ���W���擾 */
				VECTOR vecPos;
				// �ǂݍ���
				data.at("translate").at("x").get_to(vecPos.x);
				data.at("translate").at("z").get_to(vecPos.y);
				data.at("translate").at("y").get_to(vecPos.z);
				// Z���W���]
				vecPos.z *= -1;

				/* ��]�ʂ��擾 */
				VECTOR vecRot;
				// �ǂݍ���
				data.at("rotate").at("x").get_to(vecRot.x);
				data.at("rotate").at("z").get_to(vecRot.y);
				data.at("rotate").at("y").get_to(vecRot.z);
				// degree -> radian�ϊ�
				vecRot.x = DEG2RAD(vecRot.x);
				vecRot.y = DEG2RAD(vecRot.y);
				vecRot.z = DEG2RAD(vecRot.z);
				// X���̉�]�����𔽓]
				// �����������s���ȏ���
				vecRot.x *= -1;

				/* �}�[�J�[�^�C�v�m�F */
				if (name == "Marker_Player_Start")
				{
					// �v���C���[�X�^�[�g�n�_�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���C���[��ǉ� */
					CharacterPlayer* pPlayer = new CharacterPlayer();
					ObjectList->SetCharacterPlayer(pPlayer);

					/* ���W�ݒ� */
					pPlayer->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pPlayer->SetRotation(vecRot);
				}
				else if (name == "Marker_Goal_Object")
				{
					// �S�[���n�_�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃS�[���I�u�W�F�N�g��ǉ� */
					EnemyBasic* pGoal = new EnemyGoalObject();
					ObjectList->SetEnemy(pGoal);

					/* ���W�ݒ� */
					pGoal->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pGoal->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Beam")
				{
					// �G�l�~�[(�r�[��)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(�r�[��)��ǉ� */
					BeamEnemy* AddEnemy = new BeamEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Escape")
				{
					// �G�l�~�[(����)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(����)��ǉ� */
					EscapeEnemy* AddEnemy = new EscapeEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Explosion")
				{
					// �G�l�~�[(����)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(����)��ǉ� */
					ExplosionEnemy* AddEnemy = new ExplosionEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Missile")
				{
					// �G�l�~�[(�~�T�C��)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(�~�T�C��)��ǉ� */
					MissileEnemy* AddEnemy = new MissileEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Enemy_Normal")
				{
					// �G�l�~�[(�ʏ�)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(�ʏ�)��ǉ� */
					NormalEnemy* AddEnemy = new NormalEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W�ݒ� */
					AddEnemy->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					AddEnemy->SetRotation(vecRot);
				}
				else if (name == "Marker_Spawn_Gimmick_Jump")
				{
					// �M�~�b�N(�����W�����v)�̏ꍇ
					PlatformBasic* pAddGimick = new Gimmick_ForcedJump_Spawn();
					ObjectList->SetPlatform(pAddGimick);

					/* ���W�ݒ� */
					pAddGimick->SetPosition(vecPos);

					/* ��]�ʐݒ� */
					pAddGimick->SetRotation(vecRot);
				}
				else if (name == "Marker_Camera_Position_Start")
				{
					// �J�����ʒu(�X�^�[�g)�̏ꍇ
					/* ���W�ݒ�(�J�������W) */
					StageStatusList->SetCameraPosition(vecPos);				// �J�����̍��W�ݒ�(���ݒn�_)
					StageStatusList->SetCameraPosition_Start(vecPos);		// �J�����̍��W�ݒ�(�ړ��O�n�_)
					StageStatusList->SetCameraPosition_Target(vecPos);		// �J�����̍��W�ݒ�(�ړ���n�_)

					/* ���W�ݒ�(�Œ���W(�J�n�n�_)) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosA")
				{
					// �J�����ʒu(�|�W�V����A)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����A) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosB")
				{
					// �J�����ʒu(�|�W�V����B)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����B) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosC")
				{
					// �J�����ʒu(�|�W�V����C)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����C) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosD")
				{
					// �J�����ʒu(�|�W�V����D)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����D) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Position_PosE")
				{
					// �J�����ʒu(�|�W�V����E)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����E) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].bUseFlg		= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].vecPosition	= vecPos;
				}
				else if (name == "Marker_Camera_Target_Start")
				{
					// �J���������_(�X�^�[�g)�̏ꍇ
					/* ���W�ݒ�(�J���������_) */
					StageStatusList->SetCameraTarget(vecPos);				// �J�����̒����_�ݒ�(���ݒn�_)

					/* ���W�ݒ�(�Œ���W(�J�n�n�_)) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_START].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosA")
				{
					// �J���������_(�|�W�V����A)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����A) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_A].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosB")
				{
					// �J���������_(�|�W�V����B)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����B) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_B].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosC")
				{
					// �J���������_(�|�W�V����C)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����C) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_C].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosD")
				{
					// �J���������_(�|�W�V����D)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����D) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_D].vecTarget	= vecPos;
				}
				else if (name == "Marker_Camera_Target_PosE")
				{
					// �J���������_(�|�W�V����E)�̏ꍇ
					/* ���W�ݒ�(�|�W�V����E) */
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].bUseFlg	= true;
					this->vecCameraPositionInfo[CAMERA_FIXED_POSITION_E].vecTarget	= vecPos;
				}
			}
		}

		/* �X�J�C�X�t�B�A�ǉ� */
		// ���W���Œǉ�����
		{
			/* "�I�u�W�F�N�g�Ǘ�"�ɃX�J�C�X�t�B�A��ǉ� */
			SkySqhereBasic* pSkySqhere = new SkySqhereBasic();
			ObjectList->SetSkySqhere(pSkySqhere);

			/* ���f�� */
			pSkySqhere->SetModelHandle(this->ModelList->iGetModel("SkySqhere/skysphere"));

			/* �T�C�Y */
			pSkySqhere->SetScale(VGet(5.f, 5.f, 5.f));
		}
	}

	/* ���ׂẴI�u�W�F�N�g�̏��������s�� */
	ObjectList->InitializationAll();

	/* �J�����Œ���W�̑������擾 */
	{
		/* ���������������� */
		this->iMaxCameraFixedPositionNo = 0;

		/* �J�����Œ���W�̑������擾���� */
		for (int i = 0; i < CAMERA_FIXED_POSITION_MAX; ++i)
		{
			/* �g�p��Ԃ��L���ł��邩�m�F */
			if (this->vecCameraPositionInfo[i].bUseFlg == true)
			{
				// �L���ł���ꍇ
				/* ���������Z���� */
				this->iMaxCameraFixedPositionNo += 1;
			}
			else
			{
				// �����ł���ꍇ
				/* ���[�v�𔲂��� */
				break;
			}
		}
	}
}
