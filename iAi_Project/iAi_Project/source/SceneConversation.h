/* 2025.03.19 �t�@�C���ǉ� ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include <vector>

/* �f�[�^���X�g */
#include "DataList_Option.h"
#include "DataList_Image.h"

/* �V�[��"��b�p�[�g"�̐錾 */

// �V�[�� "��b�p�[�g"
class SceneConversation : public SceneBase
{
	public:
		SceneConversation();					// �R���X�g���N�^
		virtual ~SceneConversation();			// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

		int		iGetTextFileNo()				{ return this->iTextFileNo; }			// �e�L�X�g�t�@�C���ԍ����擾

		void	SetTextFileNo(int iTextFileNo)	{ this->iTextFileNo	=	iTextFileNo; }	// �e�L�X�g�t�@�C���ԍ���ݒ�

	private:
		/* �֐� */
		void	LoadTextData();					// �e�L�X�g�f�[�^�ǂݍ���

		/* �g�p����f�[�^���X�g */
		DataList_Option* OptionList;			// �I�v�V�����ݒ�Ǘ�

		/* �摜�n���h�� */
//		int* piGrHandle

		/* �ϐ� */
		std::vector<TEXT_DATA>		astTextDataList;	// ��b�p�[�g�p�̃e�L�X�g�f�[�^���X�g
		int	iTextFileNo;								// �e�L�X�g�t�@�C���ԍ�
		int iDrawText;									// �e�L�X�g�̕`�ʗ�
		int iNowTextNo;									// ���݂̃e�L�X�g�ԍ�
		int	iHoldTimer;									// ����������
};
