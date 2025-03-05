/* 2024.12.XX YYYY ZZZZ */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �V�[�� */
#include "SceneStage.h"
#include "SceneAddGameSetup.h"
#include "Screen.h"


/* �f�[�^���X�g */
#include "DataList_StageStatus.h"
#include "DataList_Input.h"
#include "DataList_Model.h"
#include "DataList_Object.h"

/* �z�Q�Ƒ΍� */
class SceneStage;

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
		DataList_Input* InputList;			// ���͊Ǘ�/* �g�p����f�[�^���X�g */
		DataList_Object* ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_Model* ModelList;			// 3D���f���Ǘ�

		/* �V�[��"�X�e�[�W"�̃|�C���^ */
		SceneStage* pSceneStage;

		/* �g�p����摜�̃n���h�� */
		int* piGrHandle_TitleLogo;		// �^�C�g�����S
		//�ϐ�
		int UICount;	//UI�̃J�E���g

		bool bGameStartFlg;					//�X�^�[�g�t���O

};
