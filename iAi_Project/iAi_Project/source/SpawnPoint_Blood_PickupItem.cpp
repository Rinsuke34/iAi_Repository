/* 2025.03.14 ��򕗏� �t�@�C���쐬 */

#include "SpawnPoint_Blood_PickupItem.h"

/* �u���b�h(�s�b�N�A�b�v�A�C�e��)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
SpawnPoint_Blood_PickupItem::SpawnPoint_Blood_PickupItem() : SpawnPoint_Base()
{

}

// ������
void SpawnPoint_Blood_PickupItem::Initialization()
{
	/* �u���b�h(�s�b�N�A�b�v�A�C�e��)�������� */
	{
		/* �u���b�h(�s�b�N�A�b�v�A�C�e��)���쐬 */
		PickUpItemBase* AddPickUpItem = new PickUpItem_Blood();

		/* ���������u���b�h(�s�b�N�A�b�v�A�C�e��)�����X�g�ɒǉ� */
		this->ObjectList->SetPickUpItem(AddPickUpItem);

		/* ���������u���b�h(�s�b�N�A�b�v�A�C�e��)�̍��W��ݒ� */
		AddPickUpItem->SetPosition(this->vecPosition);

		/* ���������u���b�h(�s�b�N�A�b�v�A�C�e��)�̉�]�ʂ�ݒ� */
		AddPickUpItem->SetRotation(this->vecRotation);

		/* ���������u���b�h(�s�b�N�A�b�v�A�C�e��)�̏��������� */
		AddPickUpItem->Initialization();
	}
}
