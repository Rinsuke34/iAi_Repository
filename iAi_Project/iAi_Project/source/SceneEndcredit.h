/* 2025.03.24 �t�@�C���ǉ� ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[�� */
#include "SceneAddTitleSetup.h"

/* �f�[�^���X�g */
#include "DataList_Option.h"
#include "DataList_Image.h"

/* �V�[��"�G���h�N���W�b�g"�̐錾 */

// �V�[�� "�G���h�N���W�b�g"
class SceneEndcredit : public SceneBase
{
	public:
		SceneEndcredit();				// �R���X�g���N�^
		virtual ~SceneEndcredit();		// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Option* OptionList;			// �I�v�V�����ݒ�Ǘ�

		/* �摜�n���h�� */
		int* piGrHandle_Icon_Button_Select[2];	// ����A�C�R��(0:�R���g���[���[/1:�L�[�{�[�h)
		int* piGrHandle_Icon_Hold;				// �z�[���h�A�C�R��
		int* piGrhandle_EndCredit;				// �G���h�N���W�b�g

		/* �ϐ� */
		int		iElapsedTime;					// �o�ߎ���
		int		iScrollEndTime;					// �X�N���[���I������
		int		iHoldTimer;						// ����������
};
