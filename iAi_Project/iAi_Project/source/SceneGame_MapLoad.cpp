/* 2025.01.07 �t�@�C���ǉ� ��򕗏� */

#include "SceneGame.h"

/* �I�u�W�F�N�g */
#include "CharacterPlayer.h"
#include "PlatformBasic.h"
#include "Enemy_Test.h"
#include "PlatformLight_Test.h"

/* �V�[���u�Q�[���v�̒�`(�}�b�v�ǂݍ���) */

// �}�b�v�f�[�^�̃��[�h
void SceneGame::LoadMapData()
{
	/* �ǂݍ��ރ}�b�v�f�[�^�̔ԍ����擾 */
	{
		/* �}�b�v�f�[�^�̃��[�h���� */
	}

	/* �}�b�v�f�[�^�̓ǂݍ��� */
	{
		/* �ǂݍ��݂����}�b�v�f�[�^�̃p�X�ݒ� */
		std::string path = "resource/MapData/";
		std::string jsonFile = "Island.json";
		std::ifstream file(path + jsonFile);

		/* �f�[�^�̓����Ă���ꏊ�̖��̐ݒ� */
		std::string jsonObjName = "Island";

		/* Json�t�@�C���ǂݍ��� */
		nlohmann::json json;
		file >> json;

		nlohmann::json stage = json.at(jsonObjName);

		for (auto& data : stage)
		{
			/* �v���b�g�t�H�[���ǉ�(��) */
			{
				/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���b�g�t�H�[����ǉ� */
				PlatformBase* pPlatform = new PlatformBasic();
				this->ObjectList->SetPlatform(pPlatform);

				/* ���f�� */
				std::string	name;
				data.at("objectName").get_to(name);
				pPlatform->SetModelHandle(this->ModelList->iGetModel(name));

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
				// �ݒ�
				pPlatform->SetRotate(vecRot);

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
	}

	/* �e�X�g�p���I�u�W�F�N�g�ǉ����� */
	{
		/* �v���C���[�ǉ�(��) */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���C���[��ǉ� */
			ObjectList->SetCharacterPlayer(new CharacterPlayer());
		}

		/* �G�l�~�[�ǉ�(��) */
		{
			TestEnemy* AddEnemy = new TestEnemy();
			ObjectList->SetEnemy(AddEnemy);

			AddEnemy->SetPosition(VGet(100, 100, 100));
		}

		/* ���鑫��ǉ�(��) */
		{
			PlatformLight_Test* pPlatform = new PlatformLight_Test();
			this->ObjectList->SetPlatform(pPlatform);

			/* ���f�� */
			std::string	name = "Test/LightBlock/Test_Cube_1";
			pPlatform->SetModelHandle(this->ModelList->iGetModel(name));

			/* ���W */
			VECTOR vecPos = VGet(500.f, 100.f, 0.f);
			pPlatform->SetPosition(vecPos);

			/* ��]�� */
			VECTOR vecRot = VGet(0.f, 0.f, 0.f);
			pPlatform->SetRotate(vecRot);

			/* �g�嗦 */
			VECTOR vecScale = VGet(10.f, 1.f, 10.f);
			pPlatform->SetScale(vecScale);
		}

		/* ���鑫��(2��) */
		{
			PlatformLight_Test* pPlatform = new PlatformLight_Test();
			this->ObjectList->SetPlatform(pPlatform);

			/* ���f�� */
			std::string	name = "Test/LightBlock/Test_Cube";
			pPlatform->SetModelHandle(this->ModelList->iGetModel(name));

			/* ���W */
			VECTOR vecPos = VGet(300.f, 200.f, 300.f);
			pPlatform->SetPosition(vecPos);

			/* ��]�� */
			VECTOR vecRot = VGet(0.f, 0.f, 0.f);
			pPlatform->SetRotate(vecRot);

			/* �g�嗦 */
			VECTOR vecScale = VGet(10.f, 1.f, 10.f);
			pPlatform->SetScale(vecScale);
		}
	}

	/* ���ׂẴI�u�W�F�N�g�̏��������s�� */
	ObjectList->InitializationAll();
}
