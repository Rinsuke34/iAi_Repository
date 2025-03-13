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

	/* �摜���\�[�X�擾 */
	{
		/* �f�[�^���X�g"�摜�n���h���Ǘ�"���擾 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* �u���b�h */
		this->piGrHandle_Blood = ImageList->piGetImage("/Test/Blood");
	}

	/* �ړ������������_�������ɐݒ� */
	{
		this->vecMoveDirection = VGet((float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f);
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
			if (VSize(VSub(vecPlayerPos, this->vecPosition)) < MOVE_SPEED_PLAYER)
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
			}
			break;
	}
	
	/* �J�E���g��i�߂� */
	this->iMoveCount -= 1;
}

// �`��
void EffectItem_Blood::Draw()
{
	/* �`�� */
	DrawBillboard3D(this->vecPosition, 0.5f, 0.5f, 25.f, 0.f, *this->piGrHandle_Blood, TRUE);

}

// ���Z�b�g����
void EffectItem_Blood::Reset()
{
	/* ���̃I�u�W�F�N�g�̍폜�t���O��L���ɂ��� */
	this->bDeleteFlg = true;
}
