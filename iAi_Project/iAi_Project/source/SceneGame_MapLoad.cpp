/* 2025.01.07 �t�@�C���ǉ� ��򕗏� */

#include "SceneGame.h"

/* �I�u�W�F�N�g */
#include "CharacterPlayer.h"
#include "PlatformBasic.h"

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
				vecRot.x = vecRot.x / 180.f * PI;
				vecRot.y = vecRot.y / 180.f * PI;
				vecRot.z = vecRot.z / 180.f * PI;
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

	/* �v���C���[�ǉ�(��) */
	{
		/* "�I�u�W�F�N�g�Ǘ�"�Ƀv���C���[��ǉ� */
		ObjectList->SetCharacterPlayer(new CharacterPlayer());
	}
}
