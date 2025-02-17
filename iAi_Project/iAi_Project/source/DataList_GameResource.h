/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include "EditDefine.h"
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
		DataList_GameResource();			// �R���X�g���N�^
		virtual ~DataList_GameResource();	// �f�X�g���N�^

		/* �f�[�^�擾 */
		// �u���b�h(�Q�[�����ʉ�)�֘A
		int		iGetHaveBlood() { return this->iHaveBlood; }		// �����u���b�h�擾

		// �G�f�B�b�g�֘A
		int*		piGetGrHandle_EditEffect(int iEditEffect)	{ return this->pGrHandle_EditEffectList[iEditEffect]; }		// �G�f�B�b�g���ʉ摜�n���h���擾
		int*		piGetGrHandle_EditFrame(int iEditRank)		{ return this->pGrHandle_EditFrameList[iEditRank]; }		// �G�f�B�b�g�t���[���摜�n���h���擾
		EDIT_DATA	pGetNowEditData(int iIndex)					{ return this->NowEditData[iIndex]; }						// ���݂̃G�f�B�b�g���擾

		/* �f�[�^�ݒ� */
		// �u���b�h(�Q�[�����ʉ�)�֘A
		void	SetHaveBlood(int iBlood)					{ this->iHaveBlood			= iBlood; }	// �����u���b�h�ݒ�
		void	SetClearEvaluation(int iClearEvaluation)	{ this->iClearEvaluation	= iClearEvaluation; }

		// �G�f�B�b�g�֘A
		void	SetNowEditData(int iEditNum, int iEditEffect, int iEditRank);	// ���݂̃G�f�B�b�g���ݒ�

	private:
		/* �ϐ�(�Ǘ��p) */
		std::map<int, int*>	pGrHandle_EditEffectList;	// �摜�n���h��
		std::map<int, int*>	pGrHandle_EditFrameList;	// �G�f�B�b�g��񃊃X�g

		/* �ϐ� */
		/* �u���b�h(�Q�[�����ʉ�)�֘A */
        int iHaveBlood;									// �����u���b�h

		/* �G�f�B�b�g�֘A */
		EDIT_DATA	NowEditData[EDIT_MAX];				// ���݂̃G�f�B�b�g���

		/* �X�R�A�֘A */
		int		iClearEvaluation;						// �X�e�[�W�N���A���̕]��
};
