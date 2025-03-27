/* 2025.03.05 �t�@�C���ǉ� ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneOptionDefine.h"
#include <vector>

/* �f�[�^���X�g */
#include "DataList_Image.h"
#include "DataList_Option.h"

/* �V�[���u�I�v�V�����v�̐錾 */

// �V�[�� "�I�v�V�������"
class SceneOption : public SceneBase
{
	public:
		SceneOption();							// �R���X�g���N�^
		virtual ~SceneOption();					// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Option* OptionList;			// �I�v�V�����ݒ�Ǘ�

		/* �摜�n���h�� */
		int* piGrHandle_ResultFrame;			// ���U���g�p�t���[��

		/* �ϐ� */
		std::vector<OPTION_LIST>*	astOptionNameList;	// �I�v�V���������X�g
		int							iSelectItem;		// �I�𒆂̍��ڂ̔ԍ�
};
