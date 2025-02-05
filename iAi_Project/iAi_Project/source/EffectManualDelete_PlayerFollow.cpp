/* 2025.02.05 ��򕗏� �t�@�C���쐬 */

#include "EffectManualDelete_PlayerFollow.h"

/* �蓮�ō폜�^�C�~���O��ݒ肷��G�t�F�N�g�N���X�̒�` */
// ���v���C���[�Ɏ����Ǐ]
// �R���X�g���N�^
EffectManualDelete_PlayerFollow::EffectManualDelete_PlayerFollow(bool bCenterFollowFlg) : EffectManualDelete()
{
	// ����
	// bCenterFollowFlg		<- �v���C���[�̒����ɒǏ]���邩�̃t���O(true:�����ɒǏ] / false:�����ɒǏ])

	/* �����Ǐ]�t���O�̐ݒ� */
	this->bCenterFollowFlg = bCenterFollowFlg;

	/* �v���C���[�擾 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
}

// �X�V
void EffectManualDelete_PlayerFollow::Update()
{
	/* ���W�X�V(�v���C���[���W��) */
	this->vecPosition = this->pCharacterPlayer->vecGetPosition();

	/* �����Ǐ]�t���O���L���ł��邩 */
	if (this->bCenterFollowFlg == true)
	{
		// �L���ł���ꍇ
		this->vecPosition.y += PLAYER_HEIGHT / 2;
	}

	/* �G�t�F�N�g���W�X�V */
	Effect_PosUpdate();

	/* �G�t�F�N�g��]�ʍX�V */
	Effect_RotationUpdate();
}
