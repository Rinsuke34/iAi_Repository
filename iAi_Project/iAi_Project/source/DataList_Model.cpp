/* 2024.01.07 ��򕗏� �t�@�C���쐬 */

#include "DataList_Model.h"

/* 3D���f���Ǘ��N���X�̒�` */

// �R���X�g���N�^
DataList_Model::DataList_Model() : DataListBase("DataList_Model")
{
	/* ������(��) */
}

// �f�X�g���N�^
DataList_Model::~DataList_Model()
{

}

// Json����f�[�^�����[�h"�����쐬"
void DataList_Model::JsonDataLoad()
{

}

// 3D���f���擾
int	DataList_Model::iGetModel(std::string modelName, ObjectBase* pSetObject)
{
	// ����
	// modelName	: 3D���f����
	// pSetObject	: 3D���f����ݒ肷��I�u�W�F�N�g(this)
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

		/* �ǂݍ��񂾃��f����ݒ肷��I�u�W�F�N�g�̃p�X���擾 */
		this->pModelHandleList[modelName] = pSetObject;
	}
	else
	{
		// ���݂��Ă���ꍇ
		/* �Ώۂ̃��f������������I�u�W�F�N�g���擾 */
		ObjectBase* pModel = this->pModelHandleList[modelName];

		/* ���̃��f�����A�N�^�ł��邩�m�F */
		ActorBase* pActor = dynamic_cast<ActorBase*>(pModel);

		/* �L���X�g�������������m�F */
		if (pActor != nullptr)
		{
			// ��������(�A�N�^�ł�����)�ꍇ
			/* ���f���n���h���𕡐����Ď擾 */
			iReturn = MV1DuplicateModel(pActor->iGetModelHandle());
		}
		
		/* ���̃��f�����v���b�g�t�H�[���ł��邩�m�F */
		PlatformBase* pPlatform = dynamic_cast<PlatformBase*>(pModel);

		/* �L���X�g�������������m�F */
		if (pPlatform != nullptr)
		{
			// ��������(�v���b�g�t�H�[���ł�����)�ꍇ
			/* ���f���n���h�����擾 */
			iReturn = MV1DuplicateModel(pPlatform->iGetModelHandle());
		}
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
	else
	{
		// �o�^����Ă��Ȃ��ꍇ
		bReturn = false;
	}

	return bReturn;
}
