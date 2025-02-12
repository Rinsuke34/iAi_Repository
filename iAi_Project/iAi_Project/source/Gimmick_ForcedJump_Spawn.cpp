/* 2025.02.12 ��򕗏� �t�@�C���쐬 */

#include "Gimmick_ForcedJump_Spawn.h"

/* �����W�����v�M�~�b�N�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
Gimmick_ForcedJump_Spawn::Gimmick_ForcedJump_Spawn() : PlatformBasic()
{
	/* �f�[�^���X�g���擾 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* ������ */
	{
		this->bSpawnObjectFlg	= true;
		this->iSpawnCoolTime	= 0;
	}
}

// �f�X�g���N�^
Gimmick_ForcedJump_Spawn::~Gimmick_ForcedJump_Spawn()
{

}

// �X�V
void Gimmick_ForcedJump_Spawn::Update()
{
	/* �I�u�W�F�N�g�̃X�|�[���t���O���L�����A�N�[���^�C�����I�����Ă��邩�m�F */
	if (this->bSpawnObjectFlg == true && this->iSpawnCoolTime <= 0)
	{
		// �L�����N�[���^�C�����I�����Ă���Ȃ��
		/* �A�C�e��"�����W�����v(�M�~�b�N)"�𐶐� */
		PickUpItemBase* AddItem = new PickUpItem_ForcedJump();

		/* ���������A�C�e���̐������ɂ��̃I�u�W�F�N�g��ǉ�*/
		dynamic_cast<PickUpItem_ForcedJump*>(AddItem)->SetGimmick_ForcedJump_Spawn(this);

		/* ���������A�C�e�������X�g�ɒǉ� */
		this->ObjectList->SetPickUpItem(AddItem);

		/* �I�u�W�F�N�g�̃X�|�[���t���O�𖳌��ɐݒ� */
		this->bSpawnObjectFlg = false;

		/* �N�[���^�C����ݒ� */
		this->iSpawnCoolTime = 60 * 3;
	}

	/* �X�|�[���̃N�[���^�C����0���傫�����m�F */
	if (this->iSpawnCoolTime > 0)
	{
		// 0���傫���Ȃ��
		/* �N�[���^�C�������� */
		this->iSpawnCoolTime--;
	}
}
