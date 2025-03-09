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
	}

	/* ������ */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ���b�N�I������Ă��Ȃ���Ԃɂ���
	this->iCoreFrameNo		= -1;					// �R�A�t���[���ԍ���������
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
	/* �v���C���[�̃R���{�����Z���p�����ԃ��Z�b�g */
	{
		/* �f�[�^���X�g�擾 */
		DataList_PlayerStatus* PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* �f�[�^���X�g�����݂��Ȃ�(�����I�����ꂽ)�ꍇ�͏������I������ */
		if (PlayerStatusList == nullptr)
		{
			return;
		}

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
		AddEffect->SetDeleteCount(30);

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

		for (int i = 0; i < 10; i++)
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
