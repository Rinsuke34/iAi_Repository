/* 2025.03.05 ��򕗏� �t�@�C���쐬 */

#include "DataList_Option.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �I�v�V�����ݒ�Ǘ��N���X�̒�` */
// �R���X�g���N�^
DataList_Option::DataList_Option() : DataListBase("DataList_Option")
{
	/* �I�v�V�����f�[�^�̓ǂݍ��� */
	LoadOptionData();
}

// �I�v�V�����f�[�^�ǂݍ���
void DataList_Option::LoadOptionData()
{
	/* Json�t�@�C���W�J */
	std::ifstream inputFile(FILE_PATH_OPTION);

	/* �t�@�C���̓W�J�������������m�F */
	if (inputFile.is_open() == true)
	{
		// �t�@�C�������݂���ꍇ
		/* ���݂̃X�e�[�W�̊e�]���̊�l���擾���� */
		nlohmann::json	json;
		inputFile >> json;

		for (auto& option : this->astOptionNameList)
		{
			if (json.contains(option.Name_Json) && json[option.Name_Json].contains("value"))
			{
				if (option.Type == DATA_TYPE_BOOL)
				{
					*static_cast<bool*>(option.pValue) = json[option.Name_Json]["value"].get<bool>();
				}
				else if (option.Type == DATA_TYPE_INT)
				{
					*static_cast<int*>(option.pValue) = json[option.Name_Json]["value"].get<int>();
				}
				else if (option.Type == DATA_TYPE_FLOAT)
				{
					*static_cast<float*>(option.pValue) = json[option.Name_Json]["value"].get<float>();
				}
			}
		}
	}
}

// �I�v�V�����f�[�^�ۑ�
void DataList_Option::SaveOptionData()
{
	/* Json�t�@�C���ǂݍ��� */
	nlohmann::json json;

	/* �ϐ����X�g�����[�v���� JSON �ɏ������� */
	for (auto& option : this->astOptionNameList)
	{
		if (option.Type == DATA_TYPE_BOOL)
		{
			json[option.Name_Json]["value"] = *static_cast<bool*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_INT)
		{
			json[option.Name_Json]["value"] = *static_cast<int*>(option.pValue);
		}
		else if (option.Type == DATA_TYPE_FLOAT)
		{
			json[option.Name_Json]["value"] = *static_cast<float*>(option.pValue);
		}
	}

	/* Json�t�@�C���W�J */
	std::ofstream outputFile(FILE_PATH_OPTION);

	/* Json�t�@�C���������� */
	outputFile << json.dump(4);
}