/* 2025.01.21 ��򕗏� �t�@�C���쐬 */

#pragma once
#include "Appframe.h"

/* �f�[�^���X�g */
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "DataList_StageStatus.h"

/* �I�u�W�F�N�g */
#include "EnemyBasic.h"
#include "EffectManualDelete.h"

/* �S�[���I�u�W�F�N�g�N���X�̐錾 */

// �S�[���N���X
class EnemyGoalObject : public EnemyBasic
{
	public:
		EnemyGoalObject();				// �R���X�g���N�^
		virtual ~EnemyGoalObject();		// �f�X�g���N�^

		virtual void	Initialization()	override;		// ������
		virtual void	Update()			override;		// �X�V
		virtual void	BloomDraw()			override;		// �����`��

		/* �f�[�^�擾 */
		bool	bGetStageChangeFlg()	{ return this->bStageChangeFlg; };		// ���̃X�e�[�W�ɑJ�ڂ��邩�̃t���O���擾

		/* �f�[�^�ݒ� */
		void	SetStageChangeFlg(bool bStageChangeFlg)	{ this->bStageChangeFlg = bStageChangeFlg; }	// ���̃X�e�[�W�ɑJ�ڂ��邩�̃t���O��ݒ�

	private:
		/* �g�p����f�[�^���X�g */
		DataList_Object*		ObjectList;			// �I�u�W�F�N�g�Ǘ�
		DataList_StageStatus*	StageStatusList;	// �Q�[����ԊǗ�

		/* �ϐ� */
		bool	bStageChangeFlg;	/* ���̃X�e�[�W�ɑJ�ڂ��邩�̃t���O */

		/* �G�t�F�N�g */
		EffectManualDelete* pEffect_Glory;		// �����G�t�F�N�g
		EffectManualDelete* pEffect_Clear;		// ���j���G�t�F�N�g
};
