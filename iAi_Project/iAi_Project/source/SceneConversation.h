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
		virtual ~SceneConversation() {};		// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

		int		iGetTextFileNo()				{ return this->iTextFileNo; }			// �e�L�X�g�t�@�C���ԍ����擾

		void	SetTextFileNo(int iTextFileNo)	{ this->iTextFileNo	=	iTextFileNo; }	// �e�L�X�g�t�@�C���ԍ���ݒ�

	private:
		/* �֐� */
		void	LoadTextData();					// �e�L�X�g�f�[�^�ǂݍ���
		void	Process_SkipCheck();			// �v�Z(�X�L�b�v��ʕ`�ʒ�)
		void	Process_Conversation();			// �v�Z(��b�p�[�g�`�ʒ�)

		/* �g�p����f�[�^���X�g */
		DataList_Option* OptionList;			// �I�v�V�����ݒ�Ǘ�

		/* �摜�n���h�� */
		int* piGrHandle_SkipWindow;				// �X�L�b�v�m�F��ʃE�B���h�E
		int* apiGrHandle_SkipWindow_Yes[2];		// �X�L�b�v�m�FYES(0:�I��/1:��I��)
		int* apiGrHandle_SkipWindow_No[2];		// �X�L�b�v�m�FNO(0:�I��/1:��I��)
		int* piGrHandle_Icon_Button_A;			// A�{�^���A�C�R��
		int* piGrHandle_Icon_Hold;				// �z�[���h�A�C�R��

		/* �ϐ� */
		std::vector<TEXT_DATA>		astTextDataList;	// ��b�p�[�g�p�̃e�L�X�g�f�[�^���X�g
		int		iTextDrawDelay;							// �e�L�X�g�X�V�ҋ@����
		int		iTextFileNo;							// �e�L�X�g�t�@�C���ԍ�
		int		iDrawText;								// �e�L�X�g�̕`�ʗ�
		int		iNowTextNo;								// ���݂̃e�L�X�g�ԍ�
		int		iHoldTimer;								// ����������
		bool	bAddSkipCheckFlg;						// �X�L�b�v�m�F��ʂ�`�ʒ��ł��邩
		bool	bSelectYes;								// YES��I�𒆂ł��邩(�X�L�b�v���)
};
