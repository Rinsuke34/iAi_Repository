/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "AppFrame.h"
#include "EditDefine.h"

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
		int		iGetHaveBlood()				{ return this->iHaveBlood; }		// �����u���b�h�擾

		/* �f�[�^�ݒ� */
		// �u���b�h(�Q�[�����ʉ�)�֘A
		void	SetHaveBlood(int iBlood)	{ this->iHaveBlood	=	iBlood; }	// �����u���b�h�ݒ�

	private:
		/* �u���b�h(�Q�[�����ʉ�)�֘A */
		int iHaveBlood;		// �����u���b�h

		/* �G�f�B�b�g�֘A */

		/* �X�R�A�֘A */
};
