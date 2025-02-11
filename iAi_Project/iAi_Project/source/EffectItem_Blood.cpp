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
		this->iMoveCount	= 30;
		this->iMoveFaze		= MOVE_FAZE_RUNDOM;
	}

	/* �ړ������������_�������ɐݒ� */
	{
		this->vecMoveDirection = VGet((float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f);
	}
}

// �f�X�g���N�^
EffectItem_Blood::~EffectItem_Blood()
{

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
			if (VSize(VSub(vecPlayerPos, this->vecPosition)) < 10.f)
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
	/* ���`��(�{�Ԃł̓r���{�[�h) */
	//DrawModiBillboard3D(VECTOR Pos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int GrHandle, int TransFlag);
	int iColor = GetColor(255, 0, 0);
	DrawSphere3D(this->vecPosition, 10.f, 16, iColor, iColor, TRUE);
}
