/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#include "Enemy_Basic.h"

/* ��{�G�l�~�[�N���X�̒�` */

// �R���X�g���N�^
Enemy_Basic::Enemy_Basic() : EnemyBase()
{
	/* �f�[�^���X�g���擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�I�v�V�����ݒ�Ǘ�"���擾 */
		this->OptionList = dynamic_cast<DataList_Option*>(gpDataListServer->GetDataList("DataList_Option"));

		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* ������ */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ���b�N�I������Ă��Ȃ���Ԃɂ���
	this->iCoreFrameNo		= -1;					// �R�A�t���[���ԍ���������
	this->bDeadFlg			= false;				// ���S�t���O
	this->iBloodAmount		= 0;					// �u���b�h��
}

// �����`��
void Enemy_Basic::BloomDraw()
{
	/* �J�����ʒu����̋������擾 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* �J��������̋����Ƃ̋������G�l�~�[�`�ʋ����͈͓̔��ł��邩 */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* ���������̕`�� */
		CharacterBase::BloomDraw();
	}
}

// �����蔻��`��
void Enemy_Basic::CollisionDraw()
{
	/* �J�����ʒu����̋������擾 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* �J��������̋����Ƃ̋������G�l�~�[�`�ʋ����͈͓̔��ł��邩 */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* �����蔻��̕`�� */
		CharacterBase::CollisionDraw();
	}
}

// �`��
void Enemy_Basic::Draw()
{
	/* �J�����ʒu����̋������擾 */
	float fDistance = VSize(VSub(this->vecPosition, this->StageStatusList->vecGetCameraPosition()));

	/* �J��������̋����Ƃ̋������G�l�~�[�`�ʋ����͈͓̔��ł��邩 */
	if (fDistance < OptionList->fGetEnemyDrawDistance())
	{
		/* �`�� */
		CharacterBase::Draw();
	}
}

// ���Z�b�g����
void Enemy_Basic::Reset()
{
	/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
	this->bDeleteFlg = true;
}

// �G���j���̏���
void Enemy_Basic::Defeat()
{
	/* �f�[�^���X�g�擾 */
	DataList_PlayerStatus* PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* �f�[�^���X�g�����݂��Ȃ�(�����I�����ꂽ)�ꍇ�͏������I������ */
	if (PlayerStatusList == nullptr)
	{
		return;
	}

	/* �v���C���[�̃R���{�����Z���p�����ԃ��Z�b�g */
	{
		/* �v���C���[�̃R���{�����Z */
		PlayerStatusList->SetPlayerComboNowCount(PlayerStatusList->iGetPlayerComboNowCount() + 1);

		/* �v���C���[�̃R���{�p�����ԃ��Z�b�g */
		PlayerStatusList->SetPlayerComboDuration(INIT_ATTRIBUTES_COMBO_DURATION);
	}

	/* �����G�t�F�N�g���� */
	{
		/* ���Ԍo�߂ō폜�����G�t�F�N�g��ǉ� */
		EffectSelfDelete* AddEffect = new EffectSelfDelete();

		/* �G�t�F�N�g�ǂݍ��� */
		AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die/FX_e_die")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		AddEffect->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		AddEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̍폜�����܂ł̎��Ԃ�ݒ� */
		AddEffect->SetDeleteCount(75);

		/* �G�t�F�N�g�̏����� */
		AddEffect->Initialization();

		/* ���X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(AddEffect);
		}
	}

	/* �u���b�h(�Q�[�����ʉ�)���쐬 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
		DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* �v���C���[�̃R���{�����N���擾 */
		int iComboRank = PlayerStatusList->iGetPlayerComboRunk();

		/* �u���b�h�̐��������Z�o */
		// ��{�̃u���b�h������
		int iBloodAmount = this->iBloodAmount;
		// �v���C���[�̃G�f�B�b�g�ɂ��u���b�h�������̉��Z
		iBloodAmount += PlayerStatusList->iGetAddBlood();

		/* �R���{�����N��"����"�ȊO�ł��邩�m�F */
		if (iComboRank != COMBO_RANK_NONE)
		{
			// �R���{�����N��"����"�ȊO�ł���ꍇ
			// �R���{�����N�ɉ������u���b�h����������Z
			iBloodAmount *= COMBO_RANK_MAX - iComboRank;
		}

		/* �u���b�h�̐��� */
		for (int i = 0; i < iBloodAmount; i++)
		{
			/* ���Ԍo�߂ō폜�����A�C�e����ǉ� */
			EffectItemBase* AddItem = new EffectItem_Blood();

			/* �G�t�F�N�g�̍��W�ݒ� */
			AddItem->SetPosition(this->vecPosition);

			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffectItem(AddItem);
		}
	}

	/* �G�l�~�[�̍폜�t���O��L���ɂ��� */
	this->bDeleteFlg = true;
}

// �R�A�t���[���ԍ��擾
void Enemy_Basic::LoadCoreFrameNo()
{
	/* �R�A�t���[���ԍ����擾 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}

void Enemy_Basic::Enemy_Gravity()
{
	// �ړ���̍��W���擾(��������)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	// ��l���̏㕔���̓����蔻�肩�牺�����֌������������쐬
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;

	// ������擾
	auto& PlatformList = ObjectList->GetPlatformList();

	// ���n������W
	// �����l���ړ���̍��W�ɐݒ�
	float fStandPosY = vecNextPosition.y;

	// ����ƐڐG���邩�m�F
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// �ڐG���Ă��邩�m�F
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ

			// �q�b�g�������W�����݂̒��n���W��荂���ʒu�ł��邩�m�F
			if (stHitPolyDim.HitPosition.y >= fStandPosY)
			{
				// �G�l�~�[��y���W�����Z
				this->vecPosition.y = stHitPolyDim.HitPosition.y;
				this->vecMove.y = 0; // �������x�����Z�b�g

				// �q�b�g�������W���v���C���[�������ēo���ʒu���Ⴂ�ʒu�ł��邩�m�F
				if (fStandPosY < this->vecPosition.y + PLAYER_CLIMBED_HEIGHT)
				{
					// ���n���W���v���C���[�̌��݈ʒu���Ⴂ�ꍇ
					// �n�ʂɒ��n�����Ɣ��肷��
					// ���n���W�𒅒n�������W�ɍX�V
					fStandPosY = stHitPolyDim.HitPosition.y;
				}
				else
				{
					// ���n���W���v���C���[�̌��݈ʒu��荂���ꍇ
					// ���n���W���v���C���[���V��ɂ߂荞�܂Ȃ������ɍX�V
					fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

					// ���[�v�𔲂���
					break;
				}
			}
		}
	}
}