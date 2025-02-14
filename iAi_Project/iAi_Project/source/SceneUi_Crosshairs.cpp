/* 2025.01.27 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Crosshairs.h"

/* UI(�N���X�w�A)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Crosshairs::SceneUi_Crosshairs() : SceneBase("UI_Crosshairs", 100, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList	= dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* �摜���\�[�X�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* ���S�N���X�w�A */
		this->ipCgHandle_Flont			= ImageList->piGetImage("Test/Front");

		/* ���b�N�I���Ώ�(���C��)�N���X�w�A */
		this->ipCgHandle_Target_Main	= ImageList->piGetImage("Test/Target_Main");

		/* ���b�N�I���Ώ�(�T�u)�N���X�w�A */
		this->ipCgHandle_Target_Sub		= ImageList->piGetImage("Test/Target_Sub");
	}
}

// �v�Z
void SceneUi_Crosshairs::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->GameStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}

	/* �ł���ʂ̒��S�_����߂��G�l�~�[���擾���� */
	NearEnemy stNearEnemy = { nullptr, 0.f };

	/* ���U�����b�N�I���g�p�t���O���m�F */
	if (this->PlayerStatusList->bGetMeleeSearchCollisionUseFlg() == true)
	{
		// �g�p����ꍇ
		/* �G�l�~�[���X�g���擾 */
		auto& EnemyList = ObjectList->GetEnemyList();

		/* ���b�N�I���͈͓��̃G�l�~�[�̂����ł���ʒ����ɋ߂��G�l�~�[�����b�N�I���Ώۂɐݒ� */
		for (auto* enemy : EnemyList)
		{
			/* ���b�N�I���͈͂ɐڐG���Ă��邩�m�F */
			if (enemy->HitCheck(this->PlayerStatusList->stGetMeleeSearchCollision()) == true)
			{
				// �ڐG���Ă���ꍇ
				/* �v���C���[���_�ł̃��b�N�I����Ԃ�"���b�N�I���͈͓��ł���"�ɐݒ� */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_RANGE);

				// ���b�N�I���͈͓��ł���ꍇ
				/* �R�A�̃��[���h���W���擾 */
				VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* �R�A�̍��W���X�N���[�����W�ɕϊ� */
				VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

				/* �X�N���[�����W���L���ł��邩�m�F */
				// ���X�N���[�����W��Z����0.0f�ȉ��A���邢��1.0f�ȏ�ł���Ȃ�Ζ����ƂȂ�
				if (0.f < vecCoreScreen.z && vecCoreScreen.z < 1.f)
				{
					// �L���ł���ꍇ
					/* ��ʂ̒��S�Ƃ̍������߂� */
					float fx = vecCoreScreen.x - (SCREEN_SIZE_WIDE / 2.f);
					float fy = vecCoreScreen.y - (SCREEN_SIZE_HEIGHT / 2.f);
					float fDistance = (fx * fx) + (fy * fy);

					/* ���݂̍ł���ʂ̒��S�_����߂��G�l�~�[������ʒ����ɋ߂����m�F */
					if (fDistance < stNearEnemy.fDistance || stNearEnemy.pEnemy == nullptr)
					{
						// �߂��ꍇ
						/* �ł���ʂ̒��S�_����߂��G�l�~�[���X�V */
						stNearEnemy.pEnemy = enemy;
						stNearEnemy.fDistance = fDistance;
					}
				}
				else
				{
					// �����ł���ꍇ
					/* �v���C���[���_�ł̃��b�N�I����Ԃ�"���b�N�I������Ă��Ȃ�"�ɐݒ� */
					enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
				}
			}
			else
			{
				// �ڐG���Ă��Ȃ��ꍇ
				/* �v���C���[���_�ł̃��b�N�I����Ԃ�"���b�N�I������Ă��Ȃ�"�ɐݒ� */
				enemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);
			}
		}

		/* �ł���ʂ̒��S�_����߂��G�l�~�[�����b�N�I���ΏۂɎw�� */
		if (stNearEnemy.pEnemy != nullptr)
		{
			// ���b�N�I���Ώۂ����݂���ꍇ
			/* �v���C���[���_�ł̃��b�N�I����Ԃ�"���b�N�I������Ă���"�ɐݒ� */
			stNearEnemy.pEnemy->SetPlayerLockOnType(PLAYER_LOCKON_TARGET);
		}
	}
	else
	{
		// �g�p���Ȃ��ꍇ
		/* ���b�N�I���Ώۂ̃G�l�~�[���擾 */
		EnemyBasic* pLockOnEnemy = this->PlayerStatusList->pGetPlayerLockOnEnemy();

		/* ���b�N�I���Ώۂ̃G�l�~�[�����݂��邩�m�F */
		if (pLockOnEnemy != nullptr)
		{
			/* ���b�N�I���Ώۂ̃G�l�~�[�����b�N�I���ΏۊO�ɕύX */
			pLockOnEnemy->SetPlayerLockOnType(PLAYER_LOCKON_NONE);

			/* ���b�N�I���Ώۂ̃G�l�~�[���Y��������Ԃɂ��� */
			this->PlayerStatusList->SetPlayerLockOnEnemy(nullptr);
		}
	}

	/* ���b�N�I���Ώۂ̃G�l�~�[���f�[�^���X�g�ɐݒ肷�� */
	this->PlayerStatusList->SetPlayerLockOnEnemy(stNearEnemy.pEnemy);
}

// �`��
void SceneUi_Crosshairs::Draw()
{
	/* �G�l�~�[�̃��b�N�I���`�� */
	Draw_RockOn();

	/* �J�������[�h���\��"�Y�[��"�ł��邩�m�F */	
	if (this->PlayerStatusList->iGetCameraMode() == CAMERA_MODE_AIM)
	{
		// �\��"�Y�[��"�ł���ꍇ
		/* ���ߍU���ɂ��ړ�����W��`�� */
		Draw_Move();
	}
}

// �`��(���b�N�I���G�l�~�[)
void SceneUi_Crosshairs::Draw_RockOn()
{
	/* �摜�T�C�Y�擾�p�ϐ� */
	int iCgSizeX, iCgSizeY;

	/* �G�l�~�[���X�g���擾 */
	auto& EnemyList = ObjectList->GetEnemyList();

	/* ���b�N�I���͈͓��A���b�N�I���Ώۂ̃G�l�~�[�̃R�A�ɃN���X�w�A�����킹�ĕ`�� */
	for (auto* enemy : EnemyList)
	{
		/* �v���C���[���_�ł̃��b�N�I����Ԃ��擾 */
		int iLockOnType = enemy->iGetPlayerLockOnType();
		VECTOR vecCoreWord;
		VECTOR vecCoreScreen;

		/* ���b�N�I����Ԃɂ���ĕ`�ʂ�ύX */
		switch (iLockOnType)
		{
			case PLAYER_LOCKON_NONE:
				// ���b�N�I������Ă��Ȃ��ꍇ
				break;

			case PLAYER_LOCKON_RANGE:
				// ���b�N�I���͈͓��ł���ꍇ
				/* �R�A�̃��[���h���W���擾 */
				vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* �R�A�̍��W���X�N���[�����W�ɕϊ� */
				vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

				/* �N���X�w�A(���b�N�I���Ώ�(�T�u))��`�� */
				GetGraphSize(*this->ipCgHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
				DrawGraph(vecCoreScreen.x - (iCgSizeX / 2), vecCoreScreen.y - (iCgSizeY / 2), *this->ipCgHandle_Target_Sub, TRUE);
				break;

			case PLAYER_LOCKON_TARGET:
				// ���b�N�I���Ώۂł���ꍇ
				/* �R�A�̃��[���h���W���擾 */
				vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

				/* �R�A�̍��W���X�N���[�����W�ɕϊ� */
				vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

				/* �N���X�w�A(���b�N�I���Ώ�(�T�u))��`�� */
				GetGraphSize(*this->ipCgHandle_Target_Sub, &iCgSizeX, &iCgSizeY);
				DrawGraph(vecCoreScreen.x - (iCgSizeX / 2), vecCoreScreen.y - (iCgSizeY / 2), *this->ipCgHandle_Target_Sub, TRUE);

				/* �N���X�w�A(���b�N�I���Ώ�(���C��))��`�� */
				GetGraphSize(*this->ipCgHandle_Target_Main, &iCgSizeX, &iCgSizeY);
				DrawGraph(vecCoreScreen.x - (iCgSizeX / 2), vecCoreScreen.y - (iCgSizeY / 2), *this->ipCgHandle_Target_Main, TRUE);
				break;
		}
	}

	/* �N���X�w�A(���S)��`�� */
	GetGraphSize(*this->ipCgHandle_Flont, &iCgSizeX, &iCgSizeY);
	DrawGraph((SCREEN_SIZE_WIDE / 2) - (iCgSizeX / 2), (SCREEN_SIZE_HEIGHT / 2) - (iCgSizeY / 2), *this->ipCgHandle_Flont, TRUE);
}

// �`��(���ߍU���̈ړ�����W)
void SceneUi_Crosshairs::Draw_Move()
{
	///* �v���C���[�̍��W���擾 */
	//VECTOR vecPlayer = this->ObjectList->GetCharacterPlayer()->vecGetPosition();

	///* �ړ���̍��W�̍��W���擾 */
	//VECTOR vecTarget = VAdd(this->PlayerStatusList->vecGetPlayerChargeAttakTargetMove(), vecPlayer);

	///* ���݂̍��W�ƈړ���̍��W�Ԃ̎l�p�`��`�� */
	//// �����쐬(�|���S���ɂ���\��)
	//VECTOR Pos[4];

	//Pos[0] = VAdd(vecPlayer, VGet(PLAYER_WIDE, 0, PLAYER_WIDE));
	//Pos[1] = VAdd(vecPlayer, VGet(-PLAYER_WIDE, 0, -PLAYER_WIDE));

	//Pos[2] = VAdd(vecTarget, VGet(PLAYER_WIDE, 0, PLAYER_WIDE));
	//Pos[3] = VAdd(vecTarget, VGet(-PLAYER_WIDE, 0, -PLAYER_WIDE));

	//DrawTriangle3D(Pos[0], Pos[1], Pos[2], GetColor(255, 255, 255), TRUE);
	//DrawTriangle3D(Pos[3], Pos[2], Pos[1], GetColor(255, 255, 255), TRUE);

	//DrawLine3D(vecPlayer, vecTarget, GetColor(255, 255, 255));
}
