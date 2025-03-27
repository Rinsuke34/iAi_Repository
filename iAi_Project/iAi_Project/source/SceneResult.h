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
		int*	piGrHandle_ResultBackGround;							// ���U���g��ʂ̔w�i
		int*	apiGrHandle_Alphabet_Section[RESULT_EVALUATION_MAX];	// �e�]���̃A���t�@�x�b�g
		int*	apiGrHandle_Alphabet[RESULT_EVALUATION_MAX];			// �����]���A���t�@�x�b�g(�R���{�p�̕��𗬗p)

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
		int		iDrawFaze;									// �`�ʃt�F�[�Y
		int		iDrawTimeMinute;							// �N���A�^�C��(��)(�`�ʗp)
		int		iDrawTimeSecond;							// �N���A�^�C��(�b)(�`�ʗp)
		int		iDrawTimeFractionalSecond;					// �N���A�^�C��(�����b)(�`�ʗp)
		int		iDrawMaxCombo;								// �ő�R���{(�`�ʗp)
		int		iDrawTakeDamage;							// ��_���[�W(�`�ʗp)
		int		iDrawTotalGetBlood;							// �l���u���b�h(�`�ʗp)
		int		iDrawDelayTime;								// �`�ʒx������
		bool	bPlaySoundCount;							// SE"���U���g�J�E���g"���Đ����ł��邩�̃t���O
};
