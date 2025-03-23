/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#include "DataList_GameResource.h"
#include <nlohmann/json.hpp>
#include <fstream>

/* �Q�[�������\�[�X�Ǘ��N���X�̒�` */
// �R���X�g���N�^
DataList_GameResource::DataList_GameResource() : DataListBase("DataList_GameResource")
{
	/* ������ */
	{
		/* �摜�n���h���擾 */
		{
			/* �f�[�^���X�g"�摜���\�[�X�Ǘ�"�擾 */
			DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

			/* �G�f�B�b�g�t���[�� */
			for (int i = 0; i < EDIT_RANK_MAX; i++)
			{
				/* �G�f�B�b�g�t���[���̉摜�n���h���擾 */
				this->pGrHandle_EditFrameList[i] = ImageList->piGetImage(EDIT_RANK_NAME[i].strGrName);
			}

			/* �G�f�B�b�g���� */
			for (int i = 0; i < EDIT_EFFECT_MAX; i++)
			{
				/* �G�f�B�b�g���ʂ̉摜�n���h���擾 */
				this->pGrHandle_EditEffectList[i] = ImageList->piGetImage(EDIT_EFFECT_NAME[i].strGrName);
			}
		}

		/* �����l�ݒ� */

		/* �u���b�h(�Q�[�����ʉ�)�֘A */
		this->iHaveBlood	= 0;
		this->iStartBlood	= 0;

		/* �G�f�B�b�g�֘A */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* ���݂̃G�f�B�b�g��񏉊��� */
			this->NowEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
			this->NowEditData[i].iEditRank		= EDIT_RANK_NONE;
			this->NowEditData[i].iEditCost		= 0;
		}

		// �L�[�v���G�f�B�b�g��񏉊���
		this->KeepEditData.iEditEffect	= EDIT_EFFECT_NONE;
		this->KeepEditData.iEditRank	= EDIT_RANK_NONE;
		this->KeepEditData.iEditCost	= 0;
	
		/* �X�R�A�֘A */
		this->iClearTotalEvaluation = 0;
	}

	JsonLoadEditEffectValue();
}

/* �f�[�^�ݒ� */
// ���݂̃G�f�B�b�g���ݒ�
void DataList_GameResource::SetNowEditData(int iEditNum, EDIT_DATA EditData)
{
	// ����
	// iEditNum		<-	�ԍ�(�ő吔����)
	// EditData		<-	�G�f�B�b�g�̏��

	this->NowEditData[iEditNum] = EditData;
}

// �G�f�B�b�g���ʗʓǂݍ���
void DataList_GameResource::JsonLoadEditEffectValue()
{
	// �t�@�C�������݂���ꍇ
	/* �p�X�ƃt�@�C�����̐ݒ� */
	std::string FilePath = "resource/SetupData/";	// �ۑ��ꏊ
	std::string jsonFileName = "EditDataBase.json";		// �t�@�C����

	/* �t�@�C���W�J */
	std::ifstream inputFile(FilePath + jsonFileName);

	/* �t�@�C���̓W�J�������������m�F */
	if (inputFile.is_open())
	{
		// �t�@�C�������݂���ꍇ
		/* ���݂̃X�e�[�W�̊e�]���̊�l���擾���� */
		nlohmann::json	json;
		inputFile >> json;

		/* ���ׂĂ̗v�f��ǂݍ��� */
		for (auto& data : json)
		{
			/* �G�f�B�b�g�����擾 */
			EDIT_EFFECT_VALUE stEditEffectValue;
			data.at("Rank").get_to(stEditEffectValue.iEditRank);
			data.at("Effect").get_to(stEditEffectValue.iEditEffect);
			data.at("Value").get_to(stEditEffectValue.iValue);

			/* �G�f�B�b�g�̌��ʗʓo�^ */
			EditEffectValueList.push_back(stEditEffectValue);
		}
	}
}
