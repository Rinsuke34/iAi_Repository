/* 2025.02.19 �e�r�듹 �t�@�C���쐬 */

#include "EffectManualDelete_PlayerFollow_Frame.h"

/* �蓮�ō폜�^�C�~���O��ݒ肷��G�t�F�N�g�N���X�̒�` */
// ���v���C���[�̃t���[���Ɏ����Ǐ]
// �R���X�g���N�^
EffectManualDelete_PlayerFollow_Frame::EffectManualDelete_PlayerFollow_Frame(int iFrameHandle) : EffectManualDelete()
{
	/* �t���[���n���h���ԍ���ݒ� */
	this->iFrameHandle = iFrameHandle;	

	/* �v���C���[�擾 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();

	/* �v���C���[���f���̃n���h�����擾 */
	this->iModelHandle = this->pCharacterPlayer->iGetModelHandle();
}

// �X�V
void EffectManualDelete_PlayerFollow_Frame::Update()
{
	/* ���W�X�V(�ݒ肵���t���[�����W��) */
	this->vecPosition = MV1GetFramePosition(this->iModelHandle, this->iFrameHandle);

	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}
