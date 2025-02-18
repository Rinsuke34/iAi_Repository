/* 2025.02.16 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"

/* �f�[�^���X�g */
#include "DataList_GameStatus.h"
#include "DataList_GameResource.h"

/* �V�[��"���U���g"�N���X�̐錾 */

// �V�[��"���U���g"
class SceneResult : public SceneBase
{
	public:
		SceneResult();							// �R���X�g���N�^
		virtual ~SceneResult();					// �f�X�g���N�^

		void	Initialization()	override;	// ������
		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_GameStatus* GameStatusList;		// �Q�[����ԊǗ�
		DataList_GameResource* GameResourceList;	// �Q�[�������\�[�X�Ǘ�

		/* �֐� */
		void	Process_Main();		// ���C������
		void	Process_Decid();	// ������͎��̏���

		/* �ϐ� */
		int		iClearEvaluation_Combo;		// �]��(�ő�R���{)
		int		iClearEvaluation_Time;		// �]��(�N���A�^�C��)
		int		iClearEvaluation_Damage;	// �]��(��_���[�W)
		int		iClearEvaluation_Total;		// �]��(����)
};
