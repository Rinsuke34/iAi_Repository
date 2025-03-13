/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include "EditDefine.h"
#include "PublicInclude.h"
#include <map>
#include <vector>

/* �f�[�^���X�g */
#include "DataList_Image.h"

/* �Q�[�������\�[�X�Ǘ��N���X�̐錾 */
// ���ʉ݂�G�f�B�b�g���A�X�R�A�Ȃǂ̃��\�[�X���Ǘ�����N���X

// �Q�[�������\�[�X�Ǘ��N���X
class DataList_GameResource : public DataListBase
{
	public:
		DataList_GameResource();				// �R���X�g���N�^
		virtual ~DataList_GameResource() {};	// �f�X�g���N�^

		/* �f�[�^�擾 */
		// �u���b�h(�Q�[�����ʉ�)�֘A
		int		iGetHaveBlood() { return this->iHaveBlood; }		// �����u���b�h�擾

		// �G�f�B�b�g�֘A
		int* piGetGrHandle_EditEffect(int iEditEffect)			{ return this->pGrHandle_EditEffectList[iEditEffect]; }		// �G�f�B�b�g���ʉ摜�n���h���擾
		int* piGetGrHandle_EditFrame(int iEditRank)				{ return this->pGrHandle_EditFrameList[iEditRank]; }		// �G�f�B�b�g�t���[���摜�n���h���擾
		EDIT_DATA			stGetNowEditData(int iIndex)		{ return this->NowEditData[iIndex]; }						// ���݂̃G�f�B�b�g���擾
		EDIT_DATA			stGetKeepEditData()					{ return this->KeepEditData; }								// �L�[�v���̃G�f�B�b�g���擾
		EDIT_DATA*			pstGetNowEditData(int iIndex)		{ return &this->NowEditData[iIndex]; }						// ���݂̃G�f�B�b�g���̃|�C���^�擾
		EDIT_DATA*			pstGetKeepEditData()				{ return &this->KeepEditData; }								// �L�[�v���̃G�f�B�b�g���̃|�C���^�擾
		std::vector<EDIT_EFFECT_VALUE>	GetEffectValueList()	{ return this->EditEffectValueList; }						// �G�f�B�b�g���ʗʎ擾

		// �X�R�A�֘A
		int		iGetClearEvaluation()	{ return this->iClearTotalEvaluation; }		// �X�e�[�W�N���A���̍��v�]��(D�`S��5�i�K*3���)�擾

		/* �f�[�^�ݒ� */
		// �u���b�h(�Q�[�����ʉ�)�֘A
		void	SetHaveBlood(int iBlood)	{ this->iHaveBlood	= iBlood; }			// �����u���b�h�ݒ�

		// �G�f�B�b�g�֘A
		void	SetNowEditData(int iEditNum, int iEditEffect, int iEditRank);								// ���݂̃G�f�B�b�g���ݒ�
		void	SetKeepEditData(EDIT_DATA KeepEditData)			{ this->KeepEditData = KeepEditData; };		// �L�[�v���̃G�f�B�b�g���擾

		// �X�R�A�֘A
		void	SetClearEvaluation(int iClearTotalEvaluation)	{ this->iClearTotalEvaluation = iClearTotalEvaluation; }	// �X�e�[�W�N���A���̍��v�]��(D�`S��5�i�K*3���)�ݒ�

	private:
		/* �ϐ�(�Ǘ��p) */
		std::map<int, int*>	pGrHandle_EditEffectList;	// �摜�n���h��
		std::map<int, int*>	pGrHandle_EditFrameList;	// �G�f�B�b�g��񃊃X�g

		/* �֐� */
		void	JsonLoadEditEffectValue();			// �G�f�B�b�g���ʗʓǂݍ���

		/* �ϐ� */
		/* �u���b�h(�Q�[�����ʉ�)�֘A */
        int iHaveBlood;									// �����u���b�h

		/* �G�f�B�b�g�֘A */
		EDIT_DATA						NowEditData[EDIT_MAX];	// ���݂̃G�f�B�b�g���
		EDIT_DATA						KeepEditData;			// �L�[�v���̃G�f�B�b�g���
		std::vector<EDIT_EFFECT_VALUE>	EditEffectValueList;	// �G�f�B�b�g�̌��ʗ�

		/* �X�R�A�֘A */
		int		iClearTotalEvaluation;					// �X�e�[�W�N���A���̍��v�]��(D�`S��5�i�K*3���)
};
