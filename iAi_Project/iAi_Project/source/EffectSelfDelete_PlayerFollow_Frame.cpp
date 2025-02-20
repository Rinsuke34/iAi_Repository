/* 2025.02.20 �e�r�듹 �t�@�C���쐬 */

#include "EffectSelfDelete_PlayerFollow_Frame.h"

/* ���Ԍo�߂ō폜�����G�t�F�N�g�N���X�̒�` */
// �R���X�g���N�^
EffectSelfDelete_PlayerFollow_Frame::EffectSelfDelete_PlayerFollow_Frame(int iFrameHandle) : EffectSelfDelete()
{
	/* �t���[���n���h���ԍ���ݒ� */
	this->iFrameHandle = iFrameHandle;

	/* �v���C���[�擾 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* �v���C���[���f���̃n���h�����擾 */
	this->iModelHandle = this->pCharacterPlayer->iGetModelHandle();
}

// �X�V
void EffectSelfDelete_PlayerFollow_Frame::Update()
{
	/* �폜�J�E���g���m�F */
	if (this->iDeleteCount > 0)
	{
		/* �J�E���g�����Z */
		this->iDeleteCount--;
	}
	else
	{
		/* �폜�t���O��L���� */
		this->bDeleteFlg = true;
	}

	/* ���W�X�V(�ݒ肵���t���[�����W��) */
	this->vecPosition = MV1GetFramePosition(this->iModelHandle, this->iFrameHandle);

	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}
