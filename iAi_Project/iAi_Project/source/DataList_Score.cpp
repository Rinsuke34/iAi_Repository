/* 2025.01.30 ��򕗏� �t�@�C���쐬 */

#include "DataList_Score.h"

/* �X�R�A�֘A�Ǘ��f�[�^���X�g�̒�` */

// �R���X�g���N�^
DataList_Score::DataList_Score() : DataListBase("DataList_Score")
{
	/* ������ */
	this->iPlayerComboNowCount = 0;			// �v���C���[�̌��݂̃R���{��
	this->iPlayerComboMaxCount = 0;			// �v���C���[�̍ő�R���{��
	this->iPlayerComboDuration = 0;			// �v���C���[�̃R���{�̎c�莝������
}

// �f�X�g���N�^
DataList_Score::~DataList_Score()
{

}
