/* 2025.02.16 �t�@�C���쐬 ��򕗏� */

#include "SceneResult.h"

/* �V�[��"���U���g"�N���X�̒�` */

// �R���X�g���N�^
SceneResult::SceneResult() : SceneBase("Edit", 80, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* ���������� */
	Initialization();
}

// �f�X�g���N�^
SceneResult::~SceneResult()
{

}

// ������
void SceneResult::Initialization()
{
	/* �e�]�����擾(��) */
	{
		/* �ő�R���{ */
		this->iClearEvaluation_Combo	= RESULT_EVALUAtiON_S;	// �]��(�ő�R���{)

		/* �N���A�^�C�� */
		this->iClearEvaluation_Time		= RESULT_EVALUAtiON_S;	// �]��(�N���A�^�C��)

		/* ��_���[�W */
		this->iClearEvaluation_Damage	= RESULT_EVALUAtiON_S;	// �]��(��_���[�W)
	}

	/* �����]�������{ */
	{
		/* �e�]�������Z */
		int iEvaluationTotal = 0;
		iEvaluationTotal += this->iClearEvaluation_Combo;
		iEvaluationTotal += this->iClearEvaluation_Time;
		iEvaluationTotal += this->iClearEvaluation_Damage;

		/* �����l�ɉ����Đݒ� */
		// �� �����]���͉��L�̒ʂ�
		//	���Z�l,	 �]��
		//	12		: S
		//	11 �` 9	: A
		//	8  �` 4 : B
		//	3  �` 2 : C
		//  1  �` 0 : D

		if (iEvaluationTotal >= 12)
		{
			// S
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_S;
		}
		else if (iEvaluationTotal >= 9)
		{
			// A
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_A;
		}
		else if (iEvaluationTotal >= 4)
		{
			// B
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_B;
		}
		else if (iEvaluationTotal >= 2)
		{
			// C
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_C;
		}
		else
		{
			// D
			this->iClearEvaluation_Total = RESULT_EVALUAtiON_D;
		}
	}
	
}

// �v�Z
void SceneResult::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "���U���g"��� */
		case GAMESTATUS_RESULT:
			/* ���C���̏��������{ */
			Process_Main();
			break;

		/* �Y������ */
		default:
			/* �V�[���̍폜�t���O��L���ɂ��� */
			this->bDeleteFlg = true;
			break;
	}
}

// �`��
void SceneResult::Draw()
{
	DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "����			�F�G�f�B�b�g��ʂ�");
}

// ���C������
void SceneResult::Process_Main()
{
	/* ������͎��̏��� */
	Process_Decid();
}

// ������͎��̏���
void SceneResult::Process_Decid()
{
	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* �Q�[����Ԃ�"�G�f�B�b�g"�ɕύX���� */
		this->GameStatusList->SetGameStatus(GAMESTATUS_EDIT);

		/* �e�]���̑����l���Q�[�������\�[�X�T�[�o�[�ɓo�^ */
		this->GameResourceList->SetClearEvaluation(this->iClearEvaluation_Total);
	}
}

