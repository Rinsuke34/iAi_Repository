/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include "DataListBase.h"

/* ���ׂẴf�[�^���䏈���̃x�[�X�ƂȂ�N���X�̒�` */

// �R���X�g���N�^
DataListBase::DataListBase(const std::string& cName)
{
	// ����
	// cName					<- �f�[�^���X�g�̖��O

	/* ���������� */
	// DataListServer�ł̊Ǘ��p�f�[�^
	this->stDataListName	= cName;					// �f�[�^���X�g����ݒ�
}
