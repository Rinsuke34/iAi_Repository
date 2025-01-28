/* 2025.01.27 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Crosshairs.h"

/* UI(�N���X�w�A)�N���X�̒�` */

// �R���X�g���N�^
SceneUi_Crosshairs::SceneUi_Crosshairs() : SceneBase("UI_Crosshairs", 10, false)
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

	/* ���b�N�I���Ώۂ̃G�l�~�[���f�[�^���X�g�ɐݒ肷�� */
	this->PlayerStatusList->SetPlayerLockOnEnemy(stNearEnemy.pEnemy);
}

// �`��
void SceneUi_Crosshairs::Draw()
{
	/* �G�l�~�[���X�g���擾 */
	auto& EnemyList = ObjectList->GetEnemyList();

	/* ���b�N�I���͈͓��A���b�N�I���Ώۂ̃G�l�~�[�̃R�A�ɃN���X�w�A�����킹�ĕ`�� */
	for (auto* enemy : EnemyList)
	{
		/* �v���C���[���_�ł̃��b�N�I����Ԃ��擾 */
		int iLockOnType = enemy->iGetPlayerLockOnType();

		/* ���b�N�I����Ԃɂ���ĕ`�ʂ�ύX */
		switch (iLockOnType)
		{
			case PLAYER_LOCKON_NONE:
				// ���b�N�I������Ă��Ȃ��ꍇ
				break;

			case PLAYER_LOCKON_RANGE:
				// ���b�N�I���͈͓��ł���ꍇ
				{
					/* �R�A�̃��[���h���W���擾 */
					VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

					/* �R�A�̍��W���X�N���[�����W�ɕϊ� */
					VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

					/* �N���X�w�A�̑���ɏ\���˂�`�� */
					DrawBox((int)vecCoreScreen.x - 20, (int)vecCoreScreen.y - 2, (int)vecCoreScreen.x + 20, (int)vecCoreScreen.y + 2, GetColor(100, 0, 0), TRUE);
					DrawBox((int)vecCoreScreen.x - 2, (int)vecCoreScreen.y - 20, (int)vecCoreScreen.x + 2, (int)vecCoreScreen.y + 20, GetColor(100, 0, 0), TRUE);
				}
				break;

			case PLAYER_LOCKON_TARGET:
				// ���b�N�I���Ώۂł���ꍇ
				{
					/* �R�A�̃��[���h���W���擾 */
					VECTOR vecCoreWord = MV1GetFramePosition(enemy->iGetModelHandle(), enemy->iGetCoreFrameNo());

					/* �R�A�̍��W���X�N���[�����W�ɕϊ� */
					VECTOR vecCoreScreen = ConvWorldPosToScreenPos(vecCoreWord);

					/* �N���X�w�A�̑���ɏ\���˂�`�� */
					DrawBox((int)vecCoreScreen.x - 20, (int)vecCoreScreen.y - 2, (int)vecCoreScreen.x + 20, (int)vecCoreScreen.y + 2, GetColor(255, 0, 0), TRUE);
					DrawBox((int)vecCoreScreen.x - 2, (int)vecCoreScreen.y - 20, (int)vecCoreScreen.x + 2, (int)vecCoreScreen.y + 20, GetColor(255, 0, 0), TRUE);
				}
				break;
		}
	}

	/* ��ʒ����ɂ��\���˂��쐬 */
	DrawBox((SCREEN_SIZE_WIDE / 2) - 20, (SCREEN_SIZE_HEIGHT / 2) - 2, (SCREEN_SIZE_WIDE / 2) + 20, (SCREEN_SIZE_HEIGHT / 2) + 2, GetColor(0, 100, 0), TRUE);
	DrawBox((SCREEN_SIZE_WIDE / 2) - 2, (SCREEN_SIZE_HEIGHT / 2) - 20, (SCREEN_SIZE_WIDE / 2) + 2, (SCREEN_SIZE_HEIGHT / 2) + 20, GetColor(0, 100, 0), TRUE);
}
