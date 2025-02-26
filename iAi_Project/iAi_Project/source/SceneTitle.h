/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[�� */
#include "SceneStage.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"

/* �V�[���u�^�C�g���v�̐錾 */

// �V�[�� "�^�C�g�����"
class SceneTitle : public SceneBase
{
	public:
		SceneTitle();							// �R���X�g���N�^
		virtual ~SceneTitle();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus* StageStatusList;	// �Q�[����ԊǗ�

		//�ϐ�
		int iTitleLogoHandle;					// �^�C�g�����S�n���h��
		int iTitleBackGroundHandle;				// �^�C�g���w�i�n���h��
};
