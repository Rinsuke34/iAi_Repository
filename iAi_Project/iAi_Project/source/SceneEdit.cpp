/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"

/* �V�[��"�G�f�B�b�g"�N���X�̒�` */

// �R���X�g���N�^
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* �摜���\�[�X�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �I���t���[�� */
		this->piGrHandle_SelectFrame	= ImageList->piGetImage("Test_Edit/Interface/SelectFrame");

		this->piGrHandle_SelectNext		= ImageList->piGetImage("Test_Edit/Interface/SelectNext");
	}

	/* ������ */
	// �e�X�g�p
	this->iUpgradeRate	= 0;					// �A�b�v�O���[�h�̃��[�g(0�`10)
	this->iSelectItem	= 0;					// �I�𒆂̍��ڂ̔ԍ�
	// �V�K�̃G�f�B�b�g���
	for (int i = 0; i < EDIT_UPGRADE_MAX; i++)
	{
		this->NewEditData[i].iEditRank		= EDIT_RANK_NONE;
		this->NewEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
	}

	this->iHoldSelectItem			= -1;
	this->iHoldSelectItemType		= -1;
	this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
	this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;

	/* ������ */
	Initialization();
}

// �f�X�g���N�^
SceneEdit::~SceneEdit()
{

}

// ������
void SceneEdit::Initialization()
{
	/* �X�e�[�W�N���A���̑����]���ɉ����ĐV�K�G�f�B�b�g��ǉ� */
	{
		/* �X�e�[�W�N���A���̑����]���擾 */
		int	iClearEvaluation_Total =  this->GameResourceList->iGetClearEvaluation();

		/* �����]���ɉ������擾 */
		int		iNewEditNumber	= 0;		// �G�f�B�b�g��
		bool	bGoaldConfirmed	= false;	// ���g�m��

		/* �����N�ɉ����Đݒ肷�� */
		switch (iClearEvaluation_Total)
		{
			case RESULT_EVALUAtiON_S:
				iNewEditNumber	= 5;
				bGoaldConfirmed	= true;
				break;

			case RESULT_EVALUAtiON_A:
				iNewEditNumber = 5;
				break;

			case RESULT_EVALUAtiON_B:
				iNewEditNumber = 4;
				break;

			case RESULT_EVALUAtiON_C:
			case RESULT_EVALUAtiON_D:
				iNewEditNumber = 3;
				break;
		}

		/* �G�f�B�b�g���������_���ȃG�f�B�b�g��V�K�G�f�B�b�g�ɓo�^ */
		for (int i = 0; i < iNewEditNumber; i++)
		{
			/* ���쐬 */
			this->NewEditData[i].iEditEffect	= EDIT_EFFECT_NORMAL_MOVE_SPEED_UP;
			this->NewEditData[i].iEditRank		= EDIT_RANK_CUPPER;
		}

		/* ���g�m��t���O���L���ł��邩 */
		if (bGoaldConfirmed == true)
		{
			// �L���ł���ꍇ
			/* NONE�ȊO�̃����_���ȃG�f�B�b�g�̃����N�����ɂ��� */
			this->NewEditData[GetRand(iNewEditNumber - 1)].iEditRank = EDIT_RANK_GOLD;
		}
	}
}

// �v�Z
void SceneEdit::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

	/* �Q�[����Ԃɉ����ď�����ύX */
	switch (iGameStatus)
	{
		/* "�G�f�B�b�g"��� */
		case GAMESTATUS_EDIT:
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

// ���C������
void SceneEdit::Process_Main()
{
	/* ������͎��̏��� */
	Process_Decid();

	/* �������͎��̏��� */
	Process_Select();

	/* ���݂̃G�f�B�b�g���̍X�V */
	Process_NowEditUpdate();
}

// ������͎��̏���
void SceneEdit::Process_Decid()
{
	/* "����"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// ���͂���Ă���ꍇ
		/* ���݂̑I�����ڂ�"����"�ł��邩 */
		if (this->iSelectItem == SELECT_ITEM_NEXT - 1)
		{
			// "����"�ł���ꍇ
			/* �Q�[����Ԃ�"���̃X�e�[�W�֑J��"�ɕύX���� */
			this->GameStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);

			/* ���莞�̏������I������ */
			return;
		}

		/* �G�f�B�b�g���z�[���h���ł��邩�m�F */
		if (this->iHoldSelectItem != -1)
		{
			// �z�[���h���ł���ꍇ
			/* ���݂̑I�����ڂɉ����ď�����ύX���� */
			if (SELECT_ITEM_KEEP >= this->iSelectItem)
			{
				// "�L�[�v���̃G�f�B�b�g�ł���ꍇ
				/* �G�f�B�b�g���o�^����Ă��邩�m�F */
				if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// �o�^����Ă���ꍇ
					/* ���݃z�[���h���̃G�f�B�b�g��ێ� */
					EDIT_DATA stNowHoldEditData;
					stNowHoldEditData.iEditEffect	= this->HoldEditData.iEditEffect;
					stNowHoldEditData.iEditRank		= this->HoldEditData.iEditRank;

					/* �ݒ肳��Ă���G�f�B�b�g��ێ����ɂ��� */
					this->HoldEditData.iEditEffect	= this->GameResourceList->pGetKeepEditData().iEditEffect;
					this->HoldEditData.iEditRank	= this->GameResourceList->pGetKeepEditData().iEditRank;

					/* �ێ����Ă��錻�݃z�[���h���̃G�f�B�b�g���L�[�v���̃G�f�B�b�g�ɓo�^ */
					this->GameResourceList->SetKeepEditData(stNowHoldEditData);
				}
				else
				{
					// �o�^����Ă��Ȃ��ꍇ
					/* �ێ����Ă��錻�݃z�[���h���̃G�f�B�b�g���L�[�v���̃G�f�B�b�g�ɓo�^ */
					this->GameResourceList->SetKeepEditData(this->HoldEditData);
				}
			}
			else if (SELECT_ITEM_NEW_EDIT >= this->iSelectItem)
			{
				// "�V�K�̃G�f�B�b�g"�ł���ꍇ
				/* �G�f�B�b�g���o�^����Ă��邩�m�F */
				if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// �o�^����Ă���ꍇ
					/* ���݃z�[���h���̃G�f�B�b�g��ێ� */
					EDIT_DATA stNowHoldEditData;
					stNowHoldEditData.iEditEffect = this->HoldEditData.iEditEffect;
					stNowHoldEditData.iEditRank = this->HoldEditData.iEditRank;

					/* �ݒ肳��Ă���G�f�B�b�g��ێ����ɂ��� */
					this->HoldEditData.iEditEffect = this->NewEditData[this->iSelectItem - 1].iEditEffect;
					this->HoldEditData.iEditRank = this->NewEditData[this->iSelectItem - 1].iEditRank;

					/* �ێ����Ă��錻�݃z�[���h���̃G�f�B�b�g��V�K�̃G�f�B�b�g�ɓo�^ */
					this->NewEditData[this->iSelectItem - 1] = stNowHoldEditData;
				}
				else
				{
					// �o�^����Ă��Ȃ��ꍇ
					/* �ێ����Ă��錻�݃z�[���h���̃G�f�B�b�g��V�K�̃G�f�B�b�g�ɓo�^ */
					this->NewEditData[this->iSelectItem - 1] = this->HoldEditData;
				}
			}
			else if (SELECT_ITEM_DELETE >= this->iSelectItem)
			{
				// "�폜"�ł���ꍇ
				
			}
			else if (SELECT_ITEM_NOW_EDIT >= this->iSelectItem)
			{
				// ���݂̃G�f�B�b�g"�ł���ꍇ
				
			}
		}
		else
		{
			// �z�[���h���łȂ��ꍇ
			/* ���݂̑I�����ڂɉ����ď�����ύX���� */
			if (SELECT_ITEM_KEEP >= this->iSelectItem)
			{
				// "�L�[�v���̃G�f�B�b�g�ł���ꍇ
				/* �G�f�B�b�g���o�^����Ă��邩�m�F */
				if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// �o�^����Ă���ꍇ
					/* �o�^����Ă���f�[�^���z�[���h���̃G�f�B�b�g���ɓo�^ */
					this->HoldEditData.iEditEffect	= this->GameResourceList->pGetKeepEditData().iEditEffect;
					this->HoldEditData.iEditRank	= this->GameResourceList->pGetKeepEditData().iEditRank;

					/* �L�[�v���̃G�f�B�b�g���������� */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->GameResourceList->SetKeepEditData(stSetData);

					/* �z�[���h���̑I�����ڂ�ݒ� */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_KEEP;
				}
			}
			else if(SELECT_ITEM_NEW_EDIT >= this->iSelectItem)
			{
				// "�V�K�̃G�f�B�b�g"�ł���ꍇ
				/* �G�f�B�b�g���o�^����Ă��邩�m�F */
				if (this->NewEditData[this->iSelectItem - 1].iEditEffect != EDIT_EFFECT_NONE)
				{
					// �o�^����Ă���ꍇ
					/* �o�^����Ă���f�[�^���z�[���h���̃G�f�B�b�g���ɓo�^ */
					this->HoldEditData.iEditEffect = this->NewEditData[this->iSelectItem - 1].iEditEffect;
					this->HoldEditData.iEditRank = this->NewEditData[this->iSelectItem - 1].iEditRank;

					/* �V�K�̃G�f�B�b�g���������� */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->NewEditData[this->iSelectItem - 1] = stSetData;

					/* �z�[���h���̑I�����ڂ�ݒ� */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_NEW_EDIT;
				}
			}
			else if (SELECT_ITEM_DELETE >= this->iSelectItem)
			{
				// "�폜"�ł���ꍇ
				/* �G�f�B�b�g���o�^����Ă��邩�m�F */
				if (this->DeleteEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// �o�^����Ă���ꍇ
					/* �o�^����Ă���f�[�^���z�[���h���̃G�f�B�b�g���ɓo�^ */
					this->HoldEditData.iEditEffect	= this->DeleteEditData.iEditEffect;
					this->HoldEditData.iEditRank	= this->DeleteEditData.iEditRank;

					/* �폜�\��̃G�f�B�b�g���������� */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->DeleteEditData	= stSetData;

					/* �z�[���h���̑I�����ڂ�ݒ� */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_DELETE;
				}
			}
			else if (SELECT_ITEM_NOW_EDIT >= this->iSelectItem)
			{
				// ���݂̃G�f�B�b�g"�ł���ꍇ
				/* �G�f�B�b�g���o�^����Ă��邩�m�F */
				if (this->GameResourceList->pGetNowEditData(this->iSelectItem - 6).iEditEffect != EDIT_EFFECT_NONE)
				{
					// �o�^����Ă���ꍇ
					/* �o�^����Ă���f�[�^���z�[���h���̃G�f�B�b�g���ɓo�^ */
					this->HoldEditData.iEditEffect	= this->GameResourceList->pGetNowEditData(this->iSelectItem - 6).iEditEffect;
					this->HoldEditData.iEditRank	= this->GameResourceList->pGetNowEditData(this->iSelectItem - 6).iEditRank;

					/* ���݂̃G�f�B�b�g���������� */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->GameResourceList->SetNowEditData(this->iSelectItem - 6, stSetData.iEditEffect, stSetData.iEditRank);

					/* �z�[���h���̑I�����ڂ�ݒ� */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_NOW_EDIT;
				}
			}
		}


		///* ���݂̑I�����ڂ�"�V�K�̃G�f�B�b�g"�ł��邩 */
		//if (this->iSelectItem < SELECT_ITEM_NEW_EDIT)
		//{
		//	// "�V�K�̃G�f�B�b�g"�ł���ꍇ
		//	/* �I�������G�f�B�b�g�̍��ڂ��擾 */
		//	EDIT_DATA stSetData;
		//	stSetData.iEditEffect	= this->NewEditData[this->iSelectItem].iEditEffect;
		//	stSetData.iEditRank		= this->NewEditData[this->iSelectItem].iEditRank;

		//	/* �I�������G�f�B�b�g���ڂ̌��ʂ�"NONE"�ł��邩 */
		//	if (stSetData.iEditEffect == EDIT_EFFECT_NONE)
		//	{
		//		// "NONE"�ł���ꍇ
		//		/* ���莞�̏������I������ */
		//		return;
		//	}

		//	/* �I�������G�f�B�b�g�����݂̃G�f�B�b�g�œo�^����Ă��Ȃ��ӏ��ɐݒ肷�� */
		//	bool bSetFlg = false;		// �o�^�����t���O
		//	for (int i = 0; i < EDIT_MAX; i++)
		//	{
		//		/* �G�f�B�b�g���o�^�ς݂ł��邩�m�F */
		//		if (this->GameResourceList->pGetNowEditData(i).iEditEffect == EDIT_EFFECT_NONE)
		//		{
		//			// �o�^�ς݂łȂ��ꍇ
		//			/* �I�������G�f�B�b�g�̏���ݒ肷�� */
		//			this->GameResourceList->SetNowEditData(i, stSetData.iEditEffect, stSetData.iEditRank);

		//			/* �o�^�����t���O��L���ɂ��� */
		//			bSetFlg = true;
		//			break;
		//		}
		//	}

		//	/* �o�^�������������m�F */
		//	if (bSetFlg == true)
		//	{
		//		// ���������ꍇ
		//		/* �I�������V�K�G�f�B�b�g���ڂ����������� */
		//		this->NewEditData[this->iSelectItem].iEditEffect	= EDIT_EFFECT_NONE;
		//		this->NewEditData[this->iSelectItem].iEditRank		= EDIT_RANK_NONE;
		//	}

		//}
	}
}

// �������͎��̏���
void SceneEdit::Process_Select()
{
	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// ���͂���Ă���ꍇ
		this->iSelectItem -= 6;
	}

	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// ���͂���Ă���ꍇ
		this->iSelectItem += 6;
	}

	/* "��"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// ���͂���Ă���ꍇ
		this->iSelectItem -= 1;
	}

	/* "�E"�����͂���Ă��邩 */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// ���͂���Ă���ꍇ
		this->iSelectItem += 1;
	}

	/* �I�𒆂̍��ڂ̔ԍ���͈͓��Ɏ��߂� */
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= SELECT_ITEM_MAX)
	{
		this->iSelectItem = SELECT_ITEM_MAX - 1;
	}
}

// ���݂̃G�f�B�b�g���̍X�V
void SceneEdit::Process_NowEditUpdate()
{
	/* ����̃G�f�B�b�g������ꍇ�A�����������s�� */
	// ���������s���ƕЕ����폜����A�����Е��̃����N���オ��
	for (int i = 0; i < EDIT_MAX; i++)
	{
		/* �G�f�B�b�g�����擾 */
		EDIT_DATA stNowData = this->GameResourceList->pGetNowEditData(i);

		/* �����N���ő�(��)�ł���Ȃ珈���͍s��Ȃ� */
		if (stNowData.iEditRank == EDIT_RANK_GOLD)
		{
			continue;
		}

		/* ���ʂ�NONE(����)�ł���Ȃ珈���͍s��Ȃ� */
		if (stNowData.iEditEffect == EDIT_EFFECT_NONE)
		{
			continue;
		}

		/* ����̃G�f�B�b�g��񂪑��݂��邩 */
		for (int j = 0; j < EDIT_MAX; j++)
		{
			/* �m�F�ΏۂƓ������ڂł���Ȃ珈���͍s��Ȃ� */
			if (i == j)
			{
				continue;
			}

			/* �G�f�B�b�g�����擾 */
			EDIT_DATA stCheckData = this->GameResourceList->pGetNowEditData(j);

			/* �����N�ƌ��ʂ����v���Ă��邩�m�F */
			if (stNowData.iEditEffect == stCheckData.iEditEffect && stNowData.iEditRank == stCheckData.iEditRank)
			{
				// ���v���Ă���ꍇ
				/* ���̃G�f�B�b�g�̃����N���グ�� */
				this->GameResourceList->SetNowEditData(i, stNowData.iEditEffect, (stNowData.iEditRank + 1));

				/* �d�����Ă���G�f�B�b�g������������ */
				this->GameResourceList->SetNowEditData(j, EDIT_EFFECT_NONE, EDIT_RANK_NONE);

				continue;
			}
		}
	}
}

