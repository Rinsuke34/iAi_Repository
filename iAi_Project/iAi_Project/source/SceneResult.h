/* 2025.02.16 �t�@�C���쐬 ��򕗏� */

#pragma once
#include "AppFrame.h"
#include "PublicInclude.h"
#include "SceneResultDefine.h"

/* �f�[�^���X�g */
#include "DataList_StageStatus.h"
#include "DataList_GameResource.h"
#include "DataList_PlayerStatus.h"
#include "DataList_Image.h"

/* �V�[�� */
#include "SceneConversation.h"

/* �V�[��"���U���g"�N���X�̐錾 */

// �V�[��"���U���g"
class SceneResult : public SceneBase
{
	public:
		SceneResult();							// �R���X�g���N�^
		virtual ~SceneResult() {};				// �f�X�g���N�^

		void	Process()			override;	// �v�Z
		void	Draw()				override;	// �`��

	private:
		/* �g�p����f�[�^���X�g */
		DataList_StageStatus*	StageStatusList;	// �Q�[����ԊǗ�
		DataList_GameResource*	GameResourceList;	// �Q�[�������\�[�X�Ǘ�
		DataList_PlayerStatus*	PlayerStatusList;	// �v���C���[��ԊǗ�

		/* �g�p����摜�̃n���h�� */
		int*	piGrHandle_ResultBackGround;					// ���U���g��ʂ̔w�i
		int*	piGrHandle_String_Result;						// ���U���g��ʂ̕���(���U���g)
		int*	piGrHandle_String_Rank;							// ���U���g��ʂ̕���(�����N)
		int*	piGrHandle_ResultFrame;							// ���U���g�t���[��
		int*	apiGrHandle_Alphabet[RESULT_EVALUATION_MAX];	// �A���t�@�x�b�g(�R���{�p�̕��𗬗p)

		/* �֐� */
		void	Process_Main();					// ���C������
		void	ResultCalculation_JsonLoad();	// �]����擾
		void	ClearEvaluation();				// �]���Z�o

		/* �ϐ� */
		int		iClearEvaluation_Combo;						// �]��(�ő�R���{)
		int		iClearEvaluation_Time;						// �]��(�N���A�^�C��)
		int		iClearEvaluation_Damage;					// �]��(��_���[�W)
		int		iClearEvaluation_Total;						// �]��(����)
		int		Calculation_Combo[RESULT_EVALUATION_MAX];	// �]���(�R���{��)
		int		Calculation_Time[RESULT_EVALUATION_MAX];	// �]���(�N���A�^�C��)
		int		Calculation_Damage[RESULT_EVALUATION_MAX];	// �]���(��_���[�W��)
		int		iAddTextNo;									// �ǉ�����e�L�X�g�ԍ�
};
