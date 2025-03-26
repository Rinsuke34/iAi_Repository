/* 2025.03.27 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"
#include "DataList_Image.h"

/* UI(�`���[�g���A��)�N���X�̐錾 */

// UI(�`���[�g���A��)�N���X
class SceneUi_Tutorial : public SceneBase
{
	public:
		SceneUi_Tutorial();					// �R���X�g���N�^
		virtual ~SceneUi_Tutorial();		// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

		/* �f�[�^�擾 */
		int iGetTutorialNo()				{ return this->iTutorialNo; };			// �`�ʂ���`���[�g���A���ԍ����擾

		/* �f�[�^�ݒ� */
		void SetTutorialNo(int iTutorialNo)	{ this->iTutorialNo	=	iTutorialNo; };	// �`�ʂ���`���[�g���A���ԍ���ݒ�

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus*	StageStatusList;		// �Q�[����ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int*				piGrHandle_Tutorial_Window;				// �`���[�g���A���E�B���h�E
		std::vector<int*>	apiGrHandle_Tutorial_Cg;				// �`���[�g���A���`�ʉ摜

		/* �ϐ� */
		int iTutorialNo;								// �`�ʂ���`���[�g���A���̔ԍ�
		int iStopStartTime;								// ��~�J�n���̎���
		int iMaxItemNo;									// ���݂̃`���[�g���A���̍ő區�ڐ�
		int iNowItemNo;									// ���݂̃`���[�g���A���̕`�ʒ��̍��ڐ�
		std::vector<std::string>	aText;				// �`�ʃe�L�X�g
};
