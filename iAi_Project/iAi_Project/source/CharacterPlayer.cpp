/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "CharacterPlayer.h"

/* �v���C���[�N���X�̒�` */

// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	/* �f�[�^���X�g�擾 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* �������������J�n */
	this->iModelHandle = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");
}

// �X�V
void CharacterPlayer::Update()
{
	/* �g�p�� */
	// InputList�ɓ����Ă���֐����g�p����΂���Ȋ����œ��͂��擾�ł��܂��B
	// �����Ɋւ��ẮAInputList.h���Q�Ƃ��Ă��������B
	/* �W�����v */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_JUMP) == true)
	{
		this->vecPosition.y = 50.f;
	}
	else
	{
		this->vecPosition.y = 0.f;
	}

	/* �ړ� */
	/* �ړ����x(��) */
	float fSpeed = 2.0f;

	/* �ړ����� */
	VECTOR vecInput = this->InputList->vecGetGameInputMove();

	/* �J�����̌������擾(���������̂�) */
	float fCameraAngleX = this->PlayerStatusList->fGetCameraAngleX();

	/* �v���C���[�̐��ʕ����擾 */
	VECTOR vecMove;
	vecMove.x = sinf(fCameraAngleX) * vecInput.z - cosf(fCameraAngleX) * vecInput.x;
	vecMove.y = 0.0f;
	vecMove.z = -cosf(fCameraAngleX) * vecInput.z - sinf(fCameraAngleX) * vecInput.x;

	/* ���� */
	vecMove = VScale(vecMove, fSpeed);

	this->vecPosition = VAdd(this->vecPosition, vecMove);
}

// �`��
void CharacterPlayer::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����](�e�X�g) */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -this->PlayerStatusList->fGetCameraAngleX(), 0.0f));
	DrawFormatString(500, 16 * 12, GetColor(255, 255, 255), "���f����]�� : %f", this->PlayerStatusList->fGetCameraAngleX());

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);

	/* �e�X�g�p�`�� */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_JUMP) == true)
	{
		DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "JUMP");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "ATTACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		DrawFormatString(500, 16 * 2, GetColor(255, 255, 255), "AIM");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RESET) == true)
	{
		DrawFormatString(500, 16 * 3, GetColor(255, 255, 255), "RESET");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_DODGE) == true)
	{
		DrawFormatString(500, 16 * 4, GetColor(255, 255, 255), "DODGE");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) == true)
	{
		DrawFormatString(500, 16 * 5, GetColor(255, 255, 255), "FORWARD");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_BACK) == true)
	{
		DrawFormatString(500, 16 * 6, GetColor(255, 255, 255), "BACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_LEFT) == true)
	{
		DrawFormatString(500, 16 * 7, GetColor(255, 255, 255), "LEFT");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RIGHT) == true)
	{
		DrawFormatString(500, 16 * 8, GetColor(255, 255, 255), "RIGHT");
	}

	VECTOR vecMove = this->InputList->vecGetGameInputMove();
	DrawFormatString(500, 16 * 9, GetColor(255, 255, 255), "X:%f, Z:%f", vecMove.x, vecMove.z);


	/* �e�X�g�p */
	XINPUT_STATE stXInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	DrawFormatString(500, 16 * 10, GetColor(255, 255, 255), "���g���K : %u", stXInputState.LeftTrigger);
	DrawFormatString(500, 16 * 11, GetColor(255, 255, 255), "�E�g���K : %u", stXInputState.RightTrigger);
}
