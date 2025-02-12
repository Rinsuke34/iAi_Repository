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
// �v���b�g�t�H�[��
#include "PlatformBasic.h"
// �X�J�C�X�t�B�A
#include "SkySqhereBasic.h"
// �M�~�b�N
//#include "GimmickDisappear.h"
#include "GimmickJump.h"
#include "Gimmick_ForcedJump_Spawn.h"

/* �X�e�[�W�N���X�̒�`(�}�b�v�ǂݍ��ݕ���) */

// �}�b�v�f�[�^�̃��[�h
void SceneStage::LoadMapData()
{
	/* ���݂̃X�e�[�W�ԍ����擾 */
	int iStageNo = this->GameStatusList->iGetNowStageNo();

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

				/* �}�[�J�[�^�C�v�m�F */
				if (name == "S_Marker_StartPoint")
				{
					// �v���C���[�X�^�[�g�n�_�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���C���[��ǉ� */
					CharacterPlayer* pPlayer = new CharacterPlayer();
					ObjectList->SetCharacterPlayer(pPlayer);

					/* ���W */
					VECTOR vecPos;
					// �ǂݍ���
					data.at("translate").at("x").get_to(vecPos.x);
					data.at("translate").at("z").get_to(vecPos.y);
					data.at("translate").at("y").get_to(vecPos.z);
					// Z���W���]
					vecPos.z *= -1;
					// �ݒ�
					pPlayer->SetPosition(vecPos);

					/* ��]�� */
					// ��قǒǉ�

				}
				else if (name == "S_Marker_Goal")
				{
					// �S�[���n�_�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃS�[���I�u�W�F�N�g��ǉ� */
					EnemyBasic* pGoal = new EnemyGoalObject();
					ObjectList->SetEnemy(pGoal);

					/* ���W */
					VECTOR vecPos;
					// �ǂݍ���
					data.at("translate").at("x").get_to(vecPos.x);
					data.at("translate").at("z").get_to(vecPos.y);
					data.at("translate").at("y").get_to(vecPos.z);
					// Z���W���]
					vecPos.z *= -1;
					// �ݒ�
					pGoal->SetPosition(vecPos);
				}
			}
		}

		/* �G�l�~�[�ǂݍ��� */
		{
			/* Json�t�@�C������ǂݍ��� */
			std::string Type = "/Enemy";
			std::string GetName = MapName + Type;
			nlohmann::json stage = json.at(GetName);

			for (auto& data : stage)
			{
				/* �G�l�~�[���擾 */
				std::string	name;
				data.at("objectName").get_to(name);

				/* �G�l�~�[�^�C�v�m�F */
				if (name == "Substance2" ||
					name == "Substance")
				{
					// �G�l�~�[(��)�̏ꍇ
					/* "�I�u�W�F�N�g�Ǘ�"�ɃG�l�~�[(��)��ǉ� */
					BeamEnemy* AddEnemy = new BeamEnemy();
					ObjectList->SetEnemy(AddEnemy);

					/* ���W */
					VECTOR vecPos;
					// �ǂݍ���
					data.at("translate").at("x").get_to(vecPos.x);
					data.at("translate").at("z").get_to(vecPos.y);
					data.at("translate").at("y").get_to(vecPos.z);
					// Z���W���]
					vecPos.z *= -1;
					// �ݒ�
					AddEnemy->SetPosition(vecPos);

					/* ��]�� */
					// ��قǒǉ�
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
		}
		/*�M�~�b�N�ǉ�(��)*/
		{
			//GimmickJump* pGimmickDisappear = new GimmickJump();
			//ObjectList->SetPlatform(pGimmickDisappear);
			//pGimmickDisappear->SetPosition(VGet(22.f,160.f,22.f));

			PlatformBasic* pAddGimick = new Gimmick_ForcedJump_Spawn();
			pAddGimick->SetPosition(VGet(22.f, 160.f, 22.f));
			ObjectList->SetPlatform(pAddGimick);
		}
	}

	/* ���ׂẴI�u�W�F�N�g�̏��������s�� */
	ObjectList->InitializationAll();
}
