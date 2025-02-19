/* 2025.01.27 ��򕗏� �t�@�C���쐬 */

#include "EnemyBasic.h"

/* ��{�G�l�~�[�N���X�̒�` */

// �R���X�g���N�^
EnemyBasic::EnemyBasic() : EnemyBase()
{
	/* ������ */
	this->iPlayerLockOnType	= PLAYER_LOCKON_NONE;	// ���b�N�I������Ă��Ȃ���Ԃɂ���
	this->iCoreFrameNo		= -1;					// �R�A�t���[���ԍ���������
}

// �f�X�g���N�^
EnemyBasic::~EnemyBasic()
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

	/* ������ */
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
}

// �R�A�t���[���ԍ��擾
void EnemyBasic::LoadCoreFrameNo()
{
	/* �R�A�t���[���ԍ����擾 */
	this->iCoreFrameNo = MV1SearchFrame(this->iModelHandle, "Core");
}
