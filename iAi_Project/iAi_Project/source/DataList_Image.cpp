/* 2025.02.12 ��򕗏� �t�@�C���쐬 */

#include "DataList_Image.h"

/* �摜���\�[�X�Ǘ��N���X�̒�` */
// �R���X�g���N�^
DataList_Image::DataList_Image() : DataListBase("DataList_Image")
{

}

// �f�X�g���N�^
DataList_Image::~DataList_Image()
{
	/* ���X�g���̉摜�n���h�����폜 */
	for (const auto& pair : pImageList)
	{
		/* �摜�n���h�����폜 */
		DeleteGraph(pair.second);
	}

	/* map���N���A���� */
	pImageList.clear();
}

// �摜�擾(�|�C���^�ŕԂ�)
int* DataList_Image::piGetImage(std::string imageName)
{
	// ����
	// imageName	: �摜��
	// �߂�l
	// int*			: �摜�n���h��(�|�C���^)

	int* piReturn = nullptr;

	/* �Ώۂ̉摜���擾���� */
	// �����łɂ���Ȃ�|�C���^��Ԃ��A�Ȃ��Ȃ�ǂݍ���
	/* �Ώۂ̉摜�����݂��邩�m�F */
	if (bCheckImage(imageName) == false)
	{
		// ���݂��Ȃ��ꍇ
		/* �摜�̃t�@�C���p�X���擾 */
		std::string FileName = "resource/ImageData/" + imageName + ".png";

		/* �摜��ǂݍ��� */
		int iHandle = LoadGraph(FileName.c_str());

		/* �摜�����X�g�ɒǉ� */
		this->pImageList[imageName] = iHandle;

		/* �ǂݍ��񂾉摜���|�C���^�ŕԂ� */
		piReturn = &this->pImageList[imageName];
	}
	else
	{
		// ���݂��Ă���ꍇ
		/* �Ώ��̉摜���|�C���^�ŕԂ� */
		piReturn = &this->pImageList[imageName];
	}

	/* �摜�n���h����Ԃ� */
	return piReturn;
}

// �摜���\�[�X���݊m�F
bool DataList_Image::bCheckImage(std::string imageName)
{
	// ����
	// imageName	: �摜��
	// �߂�l
	// bool		: �摜�����݂��邩(true:���݂��� / false:���݂��Ȃ�)

	/* �Ώۂ̉摜�����X�g�ɓo�^����Ă��邩�m�F */

	bool bReturn = false;

	/* �摜���\�[�X���o�^����Ă��邩 */
	if (this->pImageList.count(imageName) != 0)
	{
		// �o�^����Ă���ꍇ
		bReturn = true;
	}

	return bReturn;
}
