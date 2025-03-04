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
	}
}

// �f�X�g���N�^
PickUpItem_ForcedJump::~PickUpItem_ForcedJump()
{
	
}

// ������
void PickUpItem_ForcedJump::Initialization()
{
	/* �R���W�����ݒ� */
	{
		this->stCollisionCapsule.fCapsuleRadius		= 100.0f;
		this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.0f, 400.0f, 0.0f));
		this->stCollisionCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0.0f, 100.0f, 0.0f));
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

		/* �G�t�F�N�g�̏����� */
		this->pEffectExplosion->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffectExplosion);
		}

		/* �v���C���[���ڐG���Ă���ꍇ */
		//�v���C���[�𐁂���΂�
		this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);

		//�v���C���[�̃W�����v�񐔂�1�ɐݒ�
		this->PlayerStatusList->SetPlayerNowJumpCount(1);

		/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		/* �������̃X�|�[���t���O��L���ɂ��� */
		this->pGimmick_ForcedJump_Spawn->SetSpawnObjectFlg(true);
	}
}
