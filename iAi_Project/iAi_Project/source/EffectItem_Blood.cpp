/* 2025.02.11 ��򕗏� �t�@�C���쐬 */

#include "EffectItem_Blood.h"

/* �u���b�h(�Q�[�����ʉ�)�N���X�̒�` */
// �R���X�g���N�^
EffectItem_Blood::EffectItem_Blood() : EffectItemBase()
{
	/* �f�[�^���X�g���擾 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* ������ */
	{
		this->iMoveCount = 30;
		this->iMoveFaze = MOVE_FAZE_RUNDOM;
	}

	/* �ړ������������_�������ɐݒ� */
	{
		this->vecMoveDirection = VGet((float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f);
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Item/Blood/Blood");

		/* ���f���k�� */
		MV1SetScale(this->iModelHandle, VGet(0.2f, 0.2f, 0.2f));

		UpdataLightFrame();
	}
}

// �X�V
void EffectItem_Blood::Update()
{
	/* ���݂̃t�F�[�Y�ɉ����ď�����ύX���� */
	switch (this->iMoveFaze)
	{
		/* �����_�������ֈړ� */
		case MOVE_FAZE_RUNDOM:
			/* �ړ������ɐݒ肳�ꂽ�����ֈړ� */
			this->vecPosition = VAdd(this->vecPosition, VScale(this->vecMoveDirection, MOVE_SPEED_RUNDOM));

			/* �ړ��J�E���g���ȉ��ɂȂ����ꍇ */
			if (this->iMoveCount < 0)
			{
				/* �v���C���[�Ɍ������Ĉړ�����t�F�[�Y�ֈڍs */
				this->iMoveFaze = MOVE_FAZE_PLAYER;
			}
			break;

		/* �v���C���[�Ɍ������Ĉړ� */
		case MOVE_FAZE_PLAYER:
			/* �v���C���[�̒��S���W���擾 */
			VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();
			vecPlayerPos.y += PLAYER_HEIGHT / 2;

			/* �v���C���[�̍��W�Ɍ������Ĉړ� */
			this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(vecPlayerPos, this->vecPosition)), MOVE_SPEED_PLAYER));

			/* �v���C���[�̍��W�ɓ��B�����ꍇ */
			if (VSize(VSub(vecPlayerPos, this->vecPosition)) <= MOVE_SPEED_PLAYER * 1.5f)
			{
				/* �폜�t���O��L���� */
				this->bDeleteFlg = true;

				/* �u���b�h���v���C���[�ɉ��Z */
				{
					/* �f�[�^���X�g�擾 */
					DataList_GameResource* GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));

					/* �u���b�h���v���C���[�ɉ��Z */
					int iNowBlood = GameResourceList->iGetHaveBlood();
					GameResourceList->SetHaveBlood(iNowBlood + 1);
				}

				/* "�u���b�h�擾"��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_GET_BLOOD);
			}
			break;
	}
	
	/* �J�E���g��i�߂� */
	this->iMoveCount -= 1;
}

// ���Z�b�g����
void EffectItem_Blood::Reset()
{
	/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
	this->bDeleteFlg = true;
}
