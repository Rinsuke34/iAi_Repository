/* 2024.01.07 ��򕗏� �t�@�C���쐬 */

#include "DataList_Model.h"

/* 3D���f���Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_Model::DataList_Model() : DataListBase("DataList_Model")
{

}

// �f�X�g���N�^
DataList_Model::~DataList_Model()
{
	/* ���X�g����3D���f�����폜 */
	for (const auto& pair : pModelHandleList)
	{
		/* ���f�����폜 */
		MV1DeleteModel(pair.second);
	}

	/* map���N���A���� */
	pModelHandleList.clear();
}

// 3D���f�����[�h(���O�ǂݍ��ݗp)
void DataList_Model::LoadModel(std::string modelName)
{
	// ����
	// modelName	: 3D���f����

	/* 3D���f����ǂݍ��� */
	// �������͍s��Ȃ�

	/* �Ώۂ�3D���f�������݂��邩�m�F */
	if (bCheckModel(modelName) == false)
	{
		// ���݂��Ȃ��ꍇ
		/* 3D���f���̃t�@�C���p�X���擾 */
		std::string FileName = "resource/ModelData/" + modelName + ".mv1";

		/* 3D���f����ǂݍ��� */
		int iHandle = MV1LoadModel(FileName.c_str());

		/* 3D���f�������X�g�ɒǉ� */
		this->pModelHandleList[modelName] = iHandle;
	}
	return;
}

// 3D���f���擾
int	DataList_Model::iGetModel(std::string modelName)
{
	// ����
	// modelName	: 3D���f����
	// �߂�l
	// int			: 3D���f���n���h��(�����������̂�n��)

	int iReturn = 0;

	/* �Ώۂ�3D���f�����擾���� */
	// �����łɂ���Ȃ畡���A�Ȃ��Ȃ�ǂݍ���

	/* �Ώۂ�3D���f�������݂��邩�m�F */
	if (bCheckModel(modelName) == false)
	{
		// ���݂��Ȃ��ꍇ
		/* 3D���f����ǂݍ��� */

		/* 3D���f���̃t�@�C���p�X���擾 */
		std::string FileName = "resource/ModelData/" + modelName + ".mv1";

		/* 3D���f����ǂݍ��� */
		iReturn = MV1LoadModel(FileName.c_str());

		/* 3D���f�������X�g�ɒǉ� */
		this->pModelHandleList[modelName] = iReturn;

		/* �ǂݍ���3D���f���𕡐� */
		iReturn = MV1DuplicateModel(iReturn);
	}
	else
	{
		// ���݂��Ă���ꍇ
		/* �Ώ��̃��f���𕡐� */
		iReturn = MV1DuplicateModel(this->pModelHandleList[modelName]);
	}

	return iReturn;
}

// 3D���f�����݊m�F
bool DataList_Model::bCheckModel(std::string modelName)
{
	// ����
	// modelName	: 3D���f����
	// �߂�l
	// bool			: 3D���f�����o�^����Ă��邩(true:�o�^����Ă��� / false:�o�^����Ă��Ȃ�)

	/* �Ώۂ�3D���f�������X�g�ɓo�^����Ă��邩�m�F */

	bool bReturn = false;

	/* �Ώۂ�3D���f�����o�^����Ă��邩 */
	if (this->pModelHandleList.count(modelName) != 0)
	{
		// �o�^����Ă���ꍇ
		bReturn = true;
	}

	return bReturn;
}
