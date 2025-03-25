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
		this->stCollisionCapsule.fCapsuleRadius = 100.0f;
		this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0.0f, 400.0f, 0.0f));
		this->stCollisionCapsule.vecCapsuleBottom = VAdd(this->vecPosition, VGet(0.0f, 100.0f, 0.0f));
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

		/* �v���C���[�̏����u���b�h���擾 */
		int iHaveBlood = this->GameResourceList->iGetHaveBlood();

		/* �v���C���[�̏����u���b�h�����Z */
		iHaveBlood += 10;

		/* �v���C���[�̏����u���b�h��ݒ� */
		this->GameResourceList->SetHaveBlood(iHaveBlood);

		/* "�u���b�h�擾"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_GET_BLOOD);
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
