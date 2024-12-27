/* 2024.12.12 ��򕗏� �t�@�C���쐬 */

#include "DataListServer.h"
#include "AppFunctionDefine.h"

/* �f�[�^���X�g�T�[�o�[�̒�` */

// �R���X�g���N�^
DataListServer::DataListServer()
{
	/* ������ */
}

// �f�X�g���N�^
DataListServer::~DataListServer()
{
	/* �I������ */
	// ���X�g���̂��ׂẴV�[�����폜
	DeleteAllDataList();			// ���ׂẴf�[�^���X�g�폜
}

// �f�[�^���X�g�`��(�f�o�b�O�p)
void DataListServer::DrawDataList()
{
	/* �f�[�^���X�g�T�[�o�[�ɓo�^����Ă���f�[�^���X�g���̂̕`�� */
	// ����Ƀf�o�b�O�p�r
	int iIndex			= 0;
	int iFrameColor		= GetColor(0, 0, 0);			// �g�̐F
	int iStringColor	= GetColor(255, 255, 255);		// �����̐F

	DrawBox(0, iIndex * 20, 200, iIndex * 20 + 20, iFrameColor, TRUE);
	DrawString(0, 0, "�f�[�^���X�g��", iStringColor);
	iIndex++;

	/* �f�[�^���X�g�T�[�o�[�ɓo�^����Ă��邷�ׂẴf�[�^���X�g��`�� */
	for (auto& Data : pstDataList)
	{
		DrawBox(0, iIndex * 20, 200, iIndex * 20 + 20, iFrameColor, TRUE);

		/* �f�[�^���X�g���̂̕`�� */
		DrawString(0, iIndex * 20, Data->stGetDataListName().c_str(), iStringColor);

		iIndex++;
	}
}

// �f�[�^���X�g�ǉ��\��
void DataListServer::AddDataList(DataListBase* NewDataList)
{
	// ���f�[�^���X�g�̒ǉ����̂�"AddDataList"�֐��ōs��
	// ����
	// NewDataList		<-	�V�����f�[�^���X�g�ꗗ�ɒǉ�����f�[�^���X�g

	this->pstDataList.push_back(NewDataList);	// �f�[�^���X�g��ǉ�
}

// �f�[�^���X�g�擾
DataListBase* DataListServer::GetDataList(const std::string& cName)
{
	// ����
	// cName		<-	�擾�������f�[�^���X�g�̖���

	/* �f�[�^���X�g�ꗗ����f�[�^���X�g���擾���� */
	for (auto& DataList : pstDataList)
	{
		/* �f�[�^���X�g�̖��̂���v���邩�m�F���� */
		if (DataList->stGetDataListName() == cName)
		{
			// �f�[�^���X�g�̖��̂���v����Ȃ��
			/* �f�[�^���X�g�̃C���X�^���X��Ԃ� */
			return DataList;
		}
	}

	// �f�[�^���X�g��������Ȃ������ꍇ
	/* nullptr��߂�l�Ƃ��ĕԂ� */
	return nullptr;
}

// �f�[�^���X�g�폜
void DataListServer::DeleteDataList(const std::string& cName)
{
	// ����
	// cName	<-	�폜�������V�[���̖���

	/* �w��̖��̂̃f�[�^���X�g���폜 */
	pstDataList.erase(std::remove_if(pstDataList.begin(),pstDataList.end(),[&](auto* DataList)
	{
		/* �f�[�^���X�g�̖��̂���v���邩�m�F */
		if (DataList->stGetDataListName() == cName)
		{
			// ��v���Ă���ꍇ
			/* �f�[�^���X�g���폜���A���������J������ */
			delete DataList;
			return true;
		}
		else
		{
			// ��v���Ă��Ȃ��ꍇ
			/* �f�[�^���X�g�̍폜���s��Ȃ� */
			return false;
		}
	}),pstDataList.end());
}

// �f�[�^���X�g�폜(�f�[�^���X�g�ꗗ���̂��ׂẴf�[�^���X�g�ɑ΂���)
void DataListServer::DeleteAllDataList()
{
	/* �f�[�^���X�g�ꗗ���̑S�Ẵf�[�^���X�g���폜���� */
	// �f�[�^���X�g�ꗗ�ɓo�^����Ă���S�Ẵf�[�^���X�g���폜����
	for (auto& DataList : pstDataList)
	{
		delete DataList;	// ���������J������
	}

	/* �f�[�^���X�g�̃N���A���s�� */
	pstDataList.clear();
}

