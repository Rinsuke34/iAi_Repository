/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#include "DataList_GameResource.h"

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
		this->iHaveBlood = 0;

		/* �G�f�B�b�g�֘A */
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* ���݂̃G�f�B�b�g��񏉊��� */
			this->NowEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
			this->NowEditData[i].iEditRank		= EDIT_RANK_NONE;
		}

		// ���݂̃G�f�B�b�g��񏉊���
		for (int i = 0; i < EDIT_MAX; i++)
		{
			/* ������Ԃł͂��ׂ�"���ʂȂ�"�ɐݒ� */
			this->NowEditData[i].iEditEffect	= EDIT_EFFECT_NONE;

			/* �����N��"�Ȃ�"�ɐݒ� */
			this->NowEditData[i].iEditRank		= EDIT_RANK_NONE;
		}

		// �L�[�v���G�f�B�b�g��񏉊���
		this->KeepEditData.iEditEffect	= EDIT_EFFECT_NONE;
		this->KeepEditData.iEditRank	= EDIT_RANK_NONE;
	

		/* �X�R�A�֘A */
		this->iClearTotalEvaluation = 0;
	}
}

// �f�X�g���N�^
DataList_GameResource::~DataList_GameResource()
{

}

/* �f�[�^�ݒ� */
// ���݂̃G�f�B�b�g���ݒ�
void DataList_GameResource::SetNowEditData(int iEditNum, int iEditEffect, int iEditRank)
{
	// ����
	// iEditNum		<-	�ԍ�(�ő吔����)
	// iEditEffect	<-	�G�f�B�b�g����ID
	// iEditRank	<-	�G�f�B�b�g�����NID

	this->NowEditData[iEditNum].iEditEffect	= iEditEffect;
	this->NowEditData[iEditNum].iEditRank	= iEditRank;
}
