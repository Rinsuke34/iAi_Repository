/* 2025.03.14 ��򕗏� �t�@�C���쐬 */

#include "PickUpItem_Blood.h"

/* �u���b�h(�Q�[�����ʉ�/�s�b�N�A�b�v�A�C�e��)�N���X�̒�` */
// �R���X�g���N�^
PickUpItem_Blood::PickUpItem_Blood() : PickUpItemBase()
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�Q�[�����\�[�X�Ǘ�"���擾 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* �I�u�W�F�N�g�擾 */
	{
		/* �v���C���[���擾 */
		this->pPlayer = dynamic_cast<CharacterPlayer*>(ObjectList->GetCharacterPlayer());
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Item/Blood/Blood");

		/* ���f���k�� */
		MV1SetScale(this->iModelHandle, VGet(0.2f, 0.2f, 0.2f));
	}

	/* ������ */
	this->iAddEffectDelay	= 0;			// �G�t�F�N�g�ǉ��ҋ@����
}

// ������
void PickUpItem_Blood::Initialization()
{
	/* ��������t���[�����擾 */
	UpdataLightFrame();

	/* �R���W�����ݒ� */
	{
		this->stCollisionCapsule.fCapsuleRadius		= 200.0f;
		this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.0f, +50.0f, 0.0f));
		this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0.0f, -50.0f, 0.0f));
	}
}

// �X�V
void PickUpItem_Blood::Update()
{
	/* �v���C���[�Ƃ��̃I�u�W�F�N�g���ڐG���Ă��邩�m�F */
	if (this->pPlayer->HitCheck(this->stCollisionCapsule))
	{
		/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		/* "�u���b�h�擾"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_GET_BLOOD);

		/* �_���[�W�������G�t�F�N�g */
		{
			/* "�G�t�F�N�g���\�[�X�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Effect* EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

			/* ��_���[�W�̏u�Ԃɔ�������G�t�F�N�g��ǉ� */
			EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

			/* ���W��ݒ� */
			pDamageEffect->SetPosition(this->vecPosition);

			/* �G�t�F�N�g���擾 */
			pDamageEffect->SetEffectHandle(EffectList->iGetEffect("FX_damaged/FX_damaged"));

			/* �g�嗦��ݒ� */
			pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

			/* �폜�J�E���g��ݒ� */
			// ������1�b��
			pDamageEffect->SetDeleteCount(60);

			/* �G�t�F�N�g���������� */
			pDamageEffect->Initialization();

			/* �I�u�W�F�N�g���X�g�ɓo�^ */
			this->ObjectList->SetEffect(pDamageEffect);
		}

		/* �u���b�h(�Q�[�����ʉ�)���쐬 */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

			/* �u���b�h�̐��� */
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

		/* �R���{�p�����Ԃ����� */
		// �f�t�H���g�̌p�����Ԃ̔����̎��Ԃ����Z
		{
			/* �v���C���[�̃R���{�p�����Ԃ��擾 */
			int iComboDuration		= PlayerStatusList->iGetPlayerComboDuration();

			/* �v���C���[�̍ő�R���{�p�����Ԃ��擾 */
			int iMaxComboDuration	= INIT_ATTRIBUTES_COMBO_DURATION + PlayerStatusList->iGetAddComboTime();

			/* �v���C���[�̃R���{�p�����Ԃ����Z */
			iComboDuration			+= INIT_ATTRIBUTES_COMBO_DURATION / 2;

			/* �v���C���[�̃R���{�p�����Ԃ��ő�R���{�p�����Ԃ𒴂��Ă��邩�m�F */
 			if (iComboDuration > iMaxComboDuration)
			{
				// �����Ă���ꍇ
				/* �v���C���[�̃R���{�p�����Ԃ��ő�R���{�p�����Ԃɐݒ� */
				iComboDuration = iMaxComboDuration;
			}

			/* �v���C���[�̃R���{�p�����Ԃ�ݒ� */
			PlayerStatusList->SetPlayerComboDuration(iComboDuration);
		}
	}

	/* �G�t�F�N�g�ҋ@���Ԃ��X�V */
	this->iAddEffectDelay -= 1;

	/* �G�t�F�N�g�ҋ@���Ԃ�0�ȉ��ł��邩�m�F */
	if (this->iAddEffectDelay <= 0)
	{
		// 0�ȉ��ł���ꍇ
		/* �G�t�F�N�g�𐶐� */
		EffectSelfDelete* pAddEffect = new EffectSelfDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		pAddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_glitter/FX_e_glitter")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		pAddEffect->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		pAddEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̍폜���Ԃ�ݒ� */
		pAddEffect->SetDeleteCount(30);

		/* �G�t�F�N�g�̏����� */
		pAddEffect->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		this->ObjectList->SetEffect(pAddEffect);

		/* �G�t�F�N�g�ҋ@���Ԃ����Z�b�g */
		this->iAddEffectDelay = 100;
	}
}

// ���Z�b�g����
void PickUpItem_Blood::Reset()
{
	/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
	this->bDeleteFlg = true;
}
