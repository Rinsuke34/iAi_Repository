/* 2025.03.19 �ΐ�q�� �t�@�C���쐬 */

#include "GimmickDisappearSpawnPoint.h"

/* �G�l�~�[(�m�[�}��)�X�|�i�[�N���X�̒�` */
// �R���X�g���N�^
GimmickDisappearSpawnPoint::GimmickDisappearSpawnPoint() : SpawnPoint_Base()
{
	/* �ϐ������� */
	this->bAddObjectFlg = false;

	/* ���X�|�[���J�E���g */
	this->iRespawnDelay = 0;
}

// ������
void GimmickDisappearSpawnPoint::Initialization()
{
	Update();
}

// �X�V
void GimmickDisappearSpawnPoint::Update()
{
	/* �I�u�W�F�N�g�����t���O�������ł��邩�m�F */
	if (this->bAddObjectFlg == false)
	{
		// �����ł���ꍇ
		/* ���X�|�[���ҋ@���Ԓ��ł��邩�m�F */
		if (this->iRespawnDelay <= 0)
		{
			// 0�ȉ�(�ҋ@���Ԃ��������Ă���)�ꍇ
			/* �G�l�~�[(�m�[�}��)�������� */
			{
				/* "�I�u�W�F�N�g�Ǘ�"�ɏ�������ǉ� */
				GimmickDisappear* pPlatform = new GimmickDisappear();
				this->ObjectList->SetPlatform(pPlatform);

				/* ���W */
				pPlatform->SetPosition(vecPosition);

				/* ��]�� */
				pPlatform->SetRotation(vecRotation);

				/* �g�嗦 */
				pPlatform->SetScale(vecScale);

				pPlatform->Initialization();

				pPlatform->SetSpawnPoint(this);

				this->bAddObjectFlg = true;

				this->iRespawnDelay = 60 * 3;
			}
		}
		else
		{
			// �ҋ@���Ԓ��ł���ꍇ
			/* �ҋ@���Ԃ����Z */
			this->iRespawnDelay--;
		}
	}
}