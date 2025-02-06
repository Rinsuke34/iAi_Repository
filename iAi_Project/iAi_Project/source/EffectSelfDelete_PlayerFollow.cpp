/* 2025.02.05 ��򕗏� �t�@�C���쐬 */

#include "EffectSelfDelete_PlayerFollow.h"

/* ���Ԍo�߂ō폜�����G�t�F�N�g�N���X�̒�` */
// �R���X�g���N�^
EffectSelfDelete_PlayerFollow::EffectSelfDelete_PlayerFollow(bool bCenterFollowFlg) : EffectSelfDelete()
{
	// ����
	// bCenterFollowFlg		<- �v���C���[�̒����ɒǏ]���邩�̃t���O(true:�����ɒǏ] / false:�����ɒǏ])

	/* �����Ǐ]�t���O�̐ݒ� */
	this->bCenterFollowFlg = bCenterFollowFlg;

	/* �v���C���[�擾 */
	this->pCharacterPlayer = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
}

// �X�V
void EffectSelfDelete_PlayerFollow::Update()
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
