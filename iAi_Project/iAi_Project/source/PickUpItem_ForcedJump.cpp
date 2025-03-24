/* 2025.02.10 �ΐ�q�� �t�@�C���쐬 */

#include "PickUpItem_ForcedJump.h"

/* �����W�����v�A�C�e��(�M�~�b�N)�N���X�̒�` */
// �R���X�g���N�^
PickUpItem_ForcedJump::PickUpItem_ForcedJump() : PickUpItemBase()
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

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
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/ForcedJump/ForcedJump");

		// �R�c���f���̃X�P�[���𒲐�
		MV1SetScale(this->iModelHandle, VGet(0.25f, 0.25f, 0.25f));
	}
}

// ������
void PickUpItem_ForcedJump::Initialization()
{
	/* ��������t���[�����擾 */
	UpdataLightFrame();

	/* �R���W�����ݒ� */
	{
		this->stCollisionCapsule.fCapsuleRadius		= 65.0f;
		this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.0f, 100.0f, 0.0f));
		this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0.0f, 25.0f, 0.0f));
	}

	//���G�t�F�N�g�𐶐�
	this->pEffectLight = new EffectManualDelete();

	/* �G�t�F�N�g�̓ǂݍ��� */
	this->pEffectLight->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_g_mine_sine/FX_g_mine_sine")));

	/* �G�t�F�N�g�̍��W�ݒ� */
	this->pEffectLight->SetPosition(VGet(this->vecPosition.x, this->vecPosition.y + 118.0f, this->vecPosition.z));

	/* �G�t�F�N�g�̉�]�ʐݒ� */
	this->pEffectLight->SetRotation(this->vecRotation);

	/*�G�t�F�N�g�̊g�嗦�ݒ�*/
	this->pEffectLight->SetScale(VGet(6.0f, 6.0f, 6.0f));

	/* �G�t�F�N�g�̏����� */
	this->pEffectLight->Initialization();

	/* �G�t�F�N�g�����X�g�ɓo�^ */
	{
		/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
		DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		/* �G�t�F�N�g�����X�g�ɓo�^ */
		ObjectListHandle->SetEffect(this->pEffectLight);
	}
}

// �X�V
void PickUpItem_ForcedJump::Update()
{
	/* �v���C���[�Ƃ��̃M�~�b�N���ڐG���Ă��邩�m�F */
	if (this->pPlayer->HitCheck(this->stCollisionCapsule))
	{
		/* �G�t�F�N�g�ǉ� */

		/*�����G�t�F�N�g�𐶐� */
		this->pEffectExplosion = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffectExplosion->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_g_mine_explosion/FX_g_mine_explosion")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffectExplosion->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffectExplosion->SetRotation(this->vecRotation);

		/*�G�t�F�N�g�̊g�嗦�ݒ�*/
		this->pEffectExplosion->SetScale(VGet(4.5f, 4.5f, 4.5f));

		/* �G�t�F�N�g�̏����� */
		this->pEffectExplosion->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffectExplosion);
		}

		/* "�W�����v�M�~�b�N����"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound_3D(SE_GIMMIC_JUMPEXPLP, this->vecPosition, SE_3D_SOUND_RADIUS);

		/* �v���C���[���ڐG���Ă���ꍇ */
		//�v���C���[�𐁂���΂�
		this->PlayerStatusList->SetPlayerNowFallSpeed(-40.0f);

		//�v���C���[�̃W�����v�񐔂�1�ɐݒ�
		this->PlayerStatusList->SetPlayerNowJumpCount(1);

		/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		/* �������̃X�|�[���t���O��L���ɂ��� */
		this->pGimmick_ForcedJump_Spawn->SetSpawnObjectFlg(true);

		//���G�t�F�N�g���폜
		this->pEffectLight->SetDeleteFlg(true);
	}
}

// ���Z�b�g����
void PickUpItem_ForcedJump::Reset()
{
	/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
	this->bDeleteFlg = true;
}
