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

	/* �R���W�����ݒ� */
	{
		this->stCollisionCapsule.fCapsuleRadius		= 50.0f;
		this->stCollisionCapsule.vecCapsuleTop		= VGet(0.0f, 50.0f, 0.0f);
		this->stCollisionCapsule.vecCapsuleBottom	= VGet(0.0f, -50.0f, 0.0f);
	}
}

// �f�X�g���N�^
PickUpItem_ForcedJump::~PickUpItem_ForcedJump()
{

}

// �X�V
void PickUpItem_ForcedJump::Update()
{
	/* �v���C���[�Ƃ��̃M�~�b�N���ڐG���Ă��邩�m�F */
	if (this->pPlayer->HitCheck(this->stCollisionCapsule))
	{
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

// �`��
void PickUpItem_ForcedJump::Draw()
{
	/* ���`��(�{�Ԃł̓��f��) */
	int iColor = GetColor(255, 255, 0);
	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 16, iColor, iColor, FALSE);
}
