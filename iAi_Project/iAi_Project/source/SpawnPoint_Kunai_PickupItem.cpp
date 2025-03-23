/* 2025.03.22 ��򕗏� �t�@�C���쐬 */

#include "SpawnPoint_Kunai_PickupItem.h"

/* �N�i�C(�s�b�N�A�b�v�A�C�e��)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
SpawnPoint_Kunai_PickupItem::SpawnPoint_Kunai_PickupItem() : SpawnPoint_Base()
{

}

// ������
void SpawnPoint_Kunai_PickupItem::Initialization()
{
	/* �N�i�C(�s�b�N�A�b�v�A�C�e��)�������� */
	{
		/* �N�i�C(�s�b�N�A�b�v�A�C�e��)���쐬 */
		PickUpItemBase* AddPickUpItem = new PickUpItem_Kunai();

		/* ���������N�i�C(�s�b�N�A�b�v�A�C�e��)�����X�g�ɒǉ� */
		this->ObjectList->SetPickUpItem(AddPickUpItem);

		/* ���������N�i�C(�s�b�N�A�b�v�A�C�e��)�̍��W��ݒ� */
		AddPickUpItem->SetPosition(this->vecPosition);

		/* ���������N�i�C(�s�b�N�A�b�v�A�C�e��)�̉�]�ʂ�ݒ� */
		AddPickUpItem->SetRotation(this->vecRotation);

		/* ���������N�i�C(�s�b�N�A�b�v�A�C�e��)�̏��������� */
		AddPickUpItem->Initialization();
	}
}
