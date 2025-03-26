/* 2025.03.26 �t�@�C���쐬 ��򕗏� */

#include "SceneUi_Jump.h"

/* UI(�W�����v��)�N���X�̒�` */
// �R���X�g���N�^
SceneUi_Jump::SceneUi_Jump() : SceneBase("UI_Jump", 107, false)
{
	/* �f�[�^���X�g�擾 */
	{
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* �摜�ǂݍ��� */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �W�����v�A�C�R��(�L��) */
		this->piGrHandle_Jump_Icon_Valid = ImageList->piGetImage("UI_Player_Jump/UI_Jump_Count");

		/* �W�����v�A�C�R��(����) */
		this->piGrHandle_Jump_Icon_Invalid = ImageList->piGetImage("UI_Player_Jump/UI_Jump_Count_Empty");
	}
}

// �v�Z
void SceneUi_Jump::Process()
{
	/* �Q�[����Ԃ�"�Q�[�����s"�ȊO�ł���Ȃ�V�[�����폜 */
	if (this->StageStatusList->iGetGameStatus() != GAMESTATUS_PLAY_GAME)
	{
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
		return;
	}
}

// �`��
void SceneUi_Jump::Draw()
{
	/* �v���C���[���󒆂ɂ��邩�m�F */
	//if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
	//{
	//	// �󒆂ɂ���(���n���Ă��Ȃ�)�ꍇ
	//	/* �v���C���[�̓���̍��W���擾 */
	//	VECTOR vecPlayerHeadPos = VAdd(this->ObjectList->GetCharacterPlayer()->vecGetPosition(), VGet(0, PLAYER_HEIGHT, 0));

	//	/* �v���C���[�̓���̍��W���X�N���[�����W�ɕϊ� */
	//	VECTOR vecScreenPos = ConvWorldPosToScreenPos(vecPlayerHeadPos);

	//	/* �W�����v�񐔍ő吔���擾 */
	//	int iJumpMax = this->PlayerStatusList->iGetPlayerMaxJumpCount() + this->PlayerStatusList->iGetAddJumpCount();

	//	/* ���݂̃W�����v�\�񐔂��擾 */
	//	int iJumpNow = iJumpMax - this->PlayerStatusList->iGetPlayerJumpCount();

	//	/* �ő�W�����v�񐔕��W�����v�A�C�R����`�� */
	//	for (int i = 0; i < iJumpMax; i++)
	//	{
	//		/* �`�ʍ��W�擾 */
	//		st2DPosition stDrawPos;
	//		stDrawPos.ix = vecScreenPos.x - (iJumpMax * 64) + (i * 64);
	//		stDrawPos.iy = vecScreenPos.y - 32;

	//		/* �`�ʑΏۂ��L���ł��邩�m�F */
	//		if (i <= iJumpNow)
	//		{
	//			// �L���ł���ꍇ
	//			/* �W�����v�A�C�R��(�L��)��`�� */
	//			DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Valid, TRUE);
	//		}
	//		else
	//		{
	//			// �����ł���ꍇ
	//			/* �W�����v�A�C�R��(����)��`�� */
	//			DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Invalid, TRUE);
	//		}
	//	}
	//}
	// �󒆂ɂ���(���n���Ă��Ȃ�)�ꍇ
	/* �v���C���[���󒆂ɂ��邩�m�F */
	if (this->PlayerStatusList->bGetPlayerLandingFlg() == false)
	{
		// �󒆂ɂ���(���n���Ă��Ȃ�)�ꍇ
		/* �v���C���[�̓���̍��W���擾 */
		VECTOR vecPlayerHeadPos = VAdd(this->ObjectList->GetCharacterPlayer()->vecGetPosition(), VGet(0, PLAYER_HEIGHT, 0));

		/* �v���C���[�̓���̍��W���X�N���[�����W�ɕϊ� */
		VECTOR vecScreenPos = ConvWorldPosToScreenPos(vecPlayerHeadPos);

		/* �W�����v�񐔍ő吔���擾 */
		int iJumpMax = this->PlayerStatusList->iGetPlayerMaxJumpCount() + this->PlayerStatusList->iGetAddJumpCount();

		/* ���݂̃W�����v�\�񐔂��擾 */
		int iJumpNow = iJumpMax - this->PlayerStatusList->iGetPlayerNowJumpCount();

		/* �A�C�R���̕� */
		const int iIconWidth = 64;

		/* �`��J�n�ʒu�𒲐��i�����z�u�̂��ߍ��[�����炷�j */
		int iStartX = vecScreenPos.x - (iJumpMax * iIconWidth) / 2;

		/* �ő�W�����v�񐔕��W�����v�A�C�R����`�� */
		for (int i = 0; i < iJumpMax; i++)
		{
			/* �`�ʍ��W�擾 */
			st2DPosition stDrawPos;
			stDrawPos.ix = iStartX + (i * iIconWidth);
			stDrawPos.iy = vecScreenPos.y - 32;

			/* �E���珇�ɍ��F�A�C�R���ɕω� */
			if (i < iJumpNow)
			{
				// �c���Ă���W�����v�񐔕��͗L���A�C�R��
				DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Valid, TRUE);
			}
			else
			{
				// �g�����W�����v�񐔕��͍��F�A�C�R���i�����j
				DrawGraph(stDrawPos.ix, stDrawPos.iy, *this->piGrHandle_Jump_Icon_Invalid, TRUE);
			}
		}
	}


}


