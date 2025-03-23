/* 2025.03.04 ��򕗏� �t�@�C���쐬 */

#include "Gimmick_FallJudgment.h"

/* ��������N���X�̒�` */
// �R���X�g���N�^
Gimmick_FallJudgment::Gimmick_FallJudgment() : PlatformBase()
{
	/* �f�[�^���X�g���擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[��ԊǗ�"���擾 */
		this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/FallJudgment/FallJudgment");
	}	
}

// �X�V
void Gimmick_FallJudgment::Update()
{
	/* �v���C���[���擾 */
	CharacterBase* pPlayer = ObjectList->GetCharacterPlayer();

	/* �v���C���[�����݂��Ă��邩�m�F */
	if (pPlayer != nullptr)
	{
		//�v���C���[�����݂��Ă���ꍇ
		/* �v���C���[�ƐڐG���Ă��邩�m�F */
		if (pPlayer->HitCheck(this->iModelHandle, this->iCollisionFrameNo))
		{
			// �ڐG���Ă���ꍇ
			/* �v���C���[�̗��������L���ɂ��� */
			this->PlayerStatusList->SetFallFlg(true);
		}
	}
	

	/* �G�l�~�[�ƐڐG���Ă��邩�m�F */
	for (auto& enemy : this->ObjectList->GetEnemyList())
	{
		if (enemy->HitCheck(this->iModelHandle, this->iCollisionFrameNo))
		{
			// �ڐG���Ă���ꍇ
			/* �G�l�~�[�̍폜�t���O��L���ɂ��� */
			enemy->SetDeleteFlg(true);
		}
	}
}
