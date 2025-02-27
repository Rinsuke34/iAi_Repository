/* 2025.01.19 �t�@�C���쐬 ��򕗏� */

#include "SceneEdit.h"

/* �V�[��"�G�f�B�b�g"�N���X�̒�` */

// �R���X�g���N�^
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�Q�[�������\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* �摜���\�[�X�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �I���t���[�� */
		this->piGrHandle_SelectFrame	= ImageList->piGetImage("Test_Edit/Interface/SelectFrame");

		/* "����"�{�^�� */
		this->piGrHandle_SelectNext		= ImageList->piGetImage("Test_Edit/Interface/SelectNext");

		/* �I�����ڂ̏�ԃt���[�� */
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_SET]		= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_PossibleSet");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_UPGRADE]	= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_PossibleUpgrade");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_INTERCHANGEABLE]	= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_Interchangeable");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_IMPOSSIBLE]		= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_Impossible");
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

	/* �z�[���h���̃G�f�B�b�g�̏�� */
	/* �z�[���h���̃G�f�B�b�g�������������� */
	this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
	this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
	this->iHoldSelectItemType		= SELECT_TYPE_NONE;
	this->iHoldSelectItemNo			= 0;

	/* �X�e�[�W�N���A���̑����]���ɉ����ĐV�K�G�f�B�b�g��ǉ� */
	{
		/* �X�e�[�W�N���A���̑����]���擾 */
		int	iClearEvaluation_Total = this->GameResourceList->iGetClearEvaluation();

		/* �����]���ɉ������擾 */
		int		iNewEditNumber = 0;		// �G�f�B�b�g��
		bool	bGoaldConfirmed = false;	// ���g�m��

		/* �����N�ɉ����Đݒ肷�� */
		switch (iClearEvaluation_Total)
		{
		case RESULT_EVALUAtiON_S:
			iNewEditNumber = 5;
			bGoaldConfirmed = true;
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
			this->NewEditData[i].iEditEffect = EDIT_EFFECT_NORMAL_MOVE_SPEED_UP;
			this->NewEditData[i].iEditRank = EDIT_RANK_CUPPER;
		}

		/* ���g�m��t���O���L���ł��邩 */
		if (bGoaldConfirmed == true)
		{
			// �L���ł���ꍇ
			/* NONE�ȊO�̃����_���ȃG�f�B�b�g�̃����N�����ɂ��� */
			this->NewEditData[GetRand(iNewEditNumber - 1)].iEditRank = EDIT_RANK_GOLD;
		}
	}

	/* �e���ڂ̏���I�����ڂɐݒ� */
	{
		int i = 0;
		// �L�[�v���̃G�f�B�b�g���o�^
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_KEEP_EDIT;
			this->astSelectItemList[i].pstEditData = this->GameResourceList->pstGetKeepEditData();
			i++;
		}
		// �V�K�G�f�B�b�g���o�^
		for (int j = 0; j < EDIT_UPGRADE_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NEW_EDIT;
			this->astSelectItemList[i].pstEditData = &this->NewEditData[j];
			i++;
		}
		// �폜���o�^
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_DELETE_EDIT;
			this->astSelectItemList[i].pstEditData = &this->DeleteEditData;
			i++;
		}
		// ���݂̃G�f�B�b�g���o�^
		for (int j = 0; j < EDIT_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NOW_EDIT;
			this->astSelectItemList[i].pstEditData = this->GameResourceList->pstGetNowEditData(j);
			i++;
		}
		// ����
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NEXT;
		}

		/* �`�ʍ��W�ꊇ�o�^ */
		{
			/* �`�ʍ��W�ݒ�(��) */
			st2DPosition stSelectItemPos[SELECT_ITEM_MAX] =
			{
				{ 500 + (128 + 64) * 0, 1080 - 128 * 6 },
				{ 500 + (128 + 64) * 1, 1080 - 128 * 6 },
				{ 500 + (128 + 64) * 2, 1080 - 128 * 6 },
				{ 500 + (128 + 64) * 3, 1080 - 128 * 6 },
				{ 500 + (128 + 64) * 4, 1080 - 128 * 6 },
				{ 500 + (128 + 64) * 5, 1080 - 128 * 6 },
				{ 500 + (128 + 64) * 0, 1080 - 128 * 3 },
				{ 500 + (128 + 64) * 1, 1080 - 128 * 3 },
				{ 500 + (128 + 64) * 2, 1080 - 128 * 3 },
				{ 500 + (128 + 64) * 3, 1080 - 128 * 3 },
				{ 500 + (128 + 64) * 4, 1080 - 128 * 3 },
				{ 500 + (128 + 64) * 5, 1080 - 128 * 3 },
				{ 500 + (128 + 64) * 6, 1080 - 128 * 3 },
			};

			/* ���W�ݒ� */
			for (int l = 0; l < SELECT_ITEM_MAX; l++)
			{
				/* ���W�ݒ� */
				this->astSelectItemList[l].stDrawPos = stSelectItemPos[l];

				/* �I�����ڂ̏�Ԃ�"��Ԗ���"�ɐݒ�(���ł�) */
				this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_NONE;
			}
		}
	}
}

// �f�X�g���N�^
SceneEdit::~SceneEdit()
{

}

// ������
void SceneEdit::Initialization()
{
	
}

// �v�Z
void SceneEdit::Process()
{
	/* �Q�[����Ԃ��m�F */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

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
		

		/* �G�f�B�b�g���z�[���h���ł��邩�m�F */
		if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
		{
			// �z�[���h���ł���ꍇ
			/* �Ώۂ̑I�����ڂ̏�Ԃɉ����ď�����ύX���� */
			switch (this->astSelectItemList[this->iSelectItem].iSelectStatus)
			{
				/* ��ԂȂ� */
				case SELECT_STATUS_NONE:
					/* �z�[���h����"��ԂȂ�"�ɂȂ�Ȃ��͂��Ȃ̂ł�����ʂ�����G���[ */
					break;

				/* �Z�b�g�\ */
				case SELECT_STATUS_POSSIBLE_SET:
					/* �z�[���h���̃G�f�B�b�g�������݂̑I�����ڂɐݒ肷�� */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;

					/* �z�[���h���̃G�f�B�b�g�������������� */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;
					break;

				/* �����\ */
				case SELECT_STATUS_POSSIBLE_UPGRADE:
					/* �o�^����Ă���G�f�B�b�g�̃����N���㏸������ */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank += 1;

					/* �z�[���h���̃G�f�B�b�g�������������� */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;
					break;

				/* �����\ */
				case SELECT_STATUS_INTERCHANGEABLE:
					{
						/* ���ݓo�^����Ă���G�f�B�b�g����ϐ��ŕۑ� */
						EDIT_DATA stEditData = *this->astSelectItemList[this->iSelectItem].pstEditData;

						/* �z�[���h���̃G�f�B�b�g�������݂̑I�����ڂɐݒ肷�� */
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;

						/* �ϐ��ɕۑ������G�f�B�b�g�����z�[���h���̃G�f�B�b�g���ɐݒ肷�� */
						this->HoldEditData			= stEditData;
						this->iHoldSelectItemType	= this->astSelectItemList[this->iSelectItem].iSelectItemType;
					}
					break;

				/* �I��s�� */
				case SELECT_STATUS_IMPOSSIBLE:
					/* �������s��Ȃ�(�����o��) */
					break;
			}
		}
		else
		{
			// �z�[���h���ł͂Ȃ��ꍇ
			/* ���݂̑I�����ڂ�"����"�ł��邩 */
			if (this->iSelectItem == SELECT_ITEM_NEXT)
			{
				// "����"�ł���ꍇ
				/* �Q�[����Ԃ�"���̃X�e�[�W�֑J��"�ɕύX���� */
				this->StageStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);

				/* ���莞�̏������I������ */
				return;
			}
			else
			{
				// "����"�łȂ��ꍇ
				/* �o�^����Ă���G�f�B�b�g�̎擾���������{ */

				/* �I�����ڂɐݒ肳�ꂽ�G�f�B�b�g�����z�[���h���̃G�f�B�b�g�ɑ������ */
				this->HoldEditData.iEditEffect	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect;
				this->HoldEditData.iEditRank	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank;

				/* �I�����ڂ̎�ނ�ݒ肷�� */
				this->iHoldSelectItemType = this->astSelectItemList[this->iSelectItem].iSelectItemType;

				/* �G�f�B�b�g������������I�����ڂ̃G�f�B�b�g�������������� */
				this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= EDIT_EFFECT_NONE;
				this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= EDIT_RANK_NONE;
			}
		}
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
	/* �G�f�B�b�g���z�[���h���ł��邩�m�F */
	if (this->iHoldSelectItemType != SELECT_TYPE_NONE)
	{
		// �z�[���h���ł���ꍇ
		/* ���݃z�[���h���̑I�����ڂ̎�ނɉ����ď�����ύX���� */
		switch (this->iHoldSelectItemType)
		{
			/* �L�[�v���̃G�f�B�b�g */
			case SELECT_TYPE_KEEP_EDIT:
			/* �V�K�̃G�f�B�b�g */
			case SELECT_TYPE_NEW_EDIT:
				/* �L�[�v���̃G�f�B�b�g�����ւ��\�Ƃ��� */
				this->astSelectItemList[SELECT_TYPE_KEEP_EDIT].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;

				/* �V�K�̃G�f�B�b�g�����ւ��\�Ƃ��� */
				for (int i = SELECT_ITEM_NEW_EDIT_START; i <= SELECT_ITEM_NEW_EDIT_END; i++)
				{
					this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
				}

				/* �폜��I��s�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_DELETE].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;

				/* ���݂̃G�f�B�b�g�������t���Z�b�g�\�A����ւ��\�A�A�b�v�O���[�h�\�Ƃ���Ƃ��� */
				for (int i = SELECT_ITEM_NOW_EDIT_START; i <= SELECT_ITEM_NOW_EDIT_END; i++)
				{
					/* �����u���b�h��10(��)�����ł���Ȃ�I��s�ɐݒ� */
					if (this->GameResourceList->iGetHaveBlood() < 10)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
						continue;
					}

					/* �G�f�B�b�g���o�^����Ă��Ȃ��Ȃ�Z�b�g�\�Ƃ��� */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == EDIT_EFFECT_NONE)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;
						continue;;
					}

					/* ���ʂ�����ł��邩�m�F */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == this->HoldEditData.iEditEffect)
					{
						// ���ʂ�����ł���Ȃ��
						/* �����N������ł��邩�m�F */
						if (this->astSelectItemList[i].pstEditData->iEditRank == this->HoldEditData.iEditRank)
						{
							// �����N������ł���Ȃ��
							/* �����N�����ȊO�ł��邩 */
							if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_GOLD)
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_UPGRADE;
							}
							else
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
							}
						}
					}
					else
					{
						/* �����\�ɐݒ� */
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
					}
				}

				/* ���ւ�I��s�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_NEXT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;

			/* �폜 */
			case SELECT_TYPE_DELETE_EDIT:
			/* ���݂̃G�f�B�b�g */
			case SELECT_TYPE_NOW_EDIT:
				/* �L�[�v���̃G�f�B�b�g��I��s�Ƃ��� */
				this->astSelectItemList[SELECT_TYPE_KEEP_EDIT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;

				/* �V�K�̃G�f�B�b�g��I��s�Ƃ��� */
				for (int i = SELECT_ITEM_NEW_EDIT_START; i <= SELECT_ITEM_NEW_EDIT_END; i++)
				{
					this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				}

				/* �폜���Z�b�g�\�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_DELETE].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;

				/* ���݂̃G�f�B�b�g���Z�b�g�\�A����ւ��\�A�A�b�v�O���[�h�\�Ƃ��� */
				for (int i = SELECT_ITEM_NOW_EDIT_START; i <= SELECT_ITEM_NOW_EDIT_END; i++)
				{
					/* �G�f�B�b�g���o�^����Ă��Ȃ��Ȃ�Z�b�g�\�Ƃ��� */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == EDIT_EFFECT_NONE)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;
						continue;;
					}

					/* ���ʂ�����ł��邩�m�F */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == this->HoldEditData.iEditEffect)
					{
						// ���ʂ�����ł���Ȃ��
						/* �����N������ł��邩�m�F */
						if (this->astSelectItemList[i].pstEditData->iEditRank == this->HoldEditData.iEditRank)
						{
							// �����N������ł���Ȃ��
							/* �����N�����ȊO�ł��邩 */
							if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_GOLD)
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_UPGRADE;
							}
							else
							{
								/* �����\�ɐݒ� */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
							}
						}
					}
					else
					{
						/* �����\�ɐݒ� */
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
					}
				}

				/* ���ւ�I��s�Ƃ��� */
				this->astSelectItemList[SELECT_ITEM_NEXT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;
		}
	}
	else
	{
		// �z�[���h���ł͂Ȃ��ꍇ
		/* �S�Ă̑I�����ڂ̏�Ԃ�"�I�����ڂȂ�"�ɐݒ� */
		for (int i = 0; i < SELECT_ITEM_MAX; i++)
		{
			/* �e�X�g���� */
			this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_NONE;
		}
	}

	///* ����̃G�f�B�b�g������ꍇ�A�����������s�� */
	//// ���������s���ƕЕ����폜����A�����Е��̃����N���オ��
	//for (int i = 0; i < EDIT_MAX; i++)
	//{
	//	/* �G�f�B�b�g�����擾 */
	//	EDIT_DATA stNowData = this->GameResourceList->stGetNowEditData(i);

	//	/* �����N���ő�(��)�ł���Ȃ珈���͍s��Ȃ� */
	//	if (stNowData.iEditRank == EDIT_RANK_GOLD)
	//	{
	//		continue;
	//	}

	//	/* ���ʂ�NONE(����)�ł���Ȃ珈���͍s��Ȃ� */
	//	if (stNowData.iEditEffect == EDIT_EFFECT_NONE)
	//	{
	//		continue;
	//	}

	//	/* ����̃G�f�B�b�g��񂪑��݂��邩 */
	//	for (int j = 0; j < EDIT_MAX; j++)
	//	{
	//		/* �m�F�ΏۂƓ������ڂł���Ȃ珈���͍s��Ȃ� */
	//		if (i == j)
	//		{
	//			continue;
	//		}

	//		/* �G�f�B�b�g�����擾 */
	//		EDIT_DATA stCheckData = this->GameResourceList->stGetNowEditData(j);

	//		/* �����N�ƌ��ʂ����v���Ă��邩�m�F */
	//		if (stNowData.iEditEffect == stCheckData.iEditEffect && stNowData.iEditRank == stCheckData.iEditRank)
	//		{
	//			// ���v���Ă���ꍇ
	//			/* ���̃G�f�B�b�g�̃����N���グ�� */
	//			this->GameResourceList->SetNowEditData(i, stNowData.iEditEffect, (stNowData.iEditRank + 1));

	//			/* �d�����Ă���G�f�B�b�g������������ */
	//			this->GameResourceList->SetNowEditData(j, EDIT_EFFECT_NONE, EDIT_RANK_NONE);

	//			continue;
	//		}
	//	}
	//}
}

