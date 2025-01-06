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
	/* �d�͏��� */
	Player_Gravity();

	/* �W�����v���� */
	Player_Jump();

	/* �ړ����� */
	Player_Move();
}

// �`��
void CharacterPlayer::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

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

	XINPUT_STATE stXInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &stXInputState);

	DrawFormatString(500, 16 * 10, GetColor(255, 255, 255), "���g���K : %u", stXInputState.LeftTrigger);
	DrawFormatString(500, 16 * 11, GetColor(255, 255, 255), "�E�g���K : %u", stXInputState.RightTrigger);

	float fSpeed = this->PlayerStatusList->fGetPlayerNowMoveSpeed();
	DrawFormatString(500, 16 * 12, GetColor(255, 255, 255), "�ړ����x : %f", fSpeed);
}

// �ړ�
void CharacterPlayer::Player_Move()
{
	/* �v���C���[�̈ړ����� */

	/* ���͂ɂ��ړ��ʂ��擾 */
	VECTOR vecInput = this->InputList->vecGetGameInputMove();

	/* �ړ����͂�����Ă��邩�m�F */
	if (vecInput.x != 0 || vecInput.z != 0)
	{
		// �ړ����͂�����Ă���ꍇ
		/* ���݂̈ړ����x�擾 */
		float fSpeed	= this->PlayerStatusList->fGetPlayerNowMoveSpeed();

		/* �����x��K�p */
		fSpeed += this->PlayerStatusList->fGetPlayerMoveAcceleration();

		/* �ő呬�x�𒴂��Ă��Ȃ����m�F */
		float fMaxSpeed = this->PlayerStatusList->fGetPlayerMaxMoveSpeed();
		if (fSpeed > fMaxSpeed)
		{
			// �ő呬�x�𒴂��Ă���ꍇ
			/* �ő呬�x�ɐݒ� */
			fSpeed = fMaxSpeed;
		}

		/* ���ݑ��x���X�V */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(fSpeed);

		/* �J�����̐��������̌������ړ��p�̌����ɐݒ� */
		float fAngleX = this->PlayerStatusList->fGetCameraAngleX();

		/* �ړ��ʂ��Z�o */
		VECTOR vecMove;
		vecMove.x	= +(sinf(fAngleX) * vecInput.z) - (cosf(fAngleX) * vecInput.x);
		vecMove.y	= 0.0f;
		vecMove.z	= -(cosf(fAngleX) * vecInput.z) - (sinf(fAngleX) * vecInput.x);
		vecMove		= VScale(vecMove, fSpeed);

		/* �ړ���̍��W���Z�o */
		VECTOR vecNextPosition = VAdd(this->vecPosition, vecMove);

		/* �����ŃI�u�W�F�N�g�ɐڐG���Ă��邩���� */
		// ����\��

		/* �v���C���[�̍��W���ړ������� */
		this->vecPosition = vecNextPosition;

		/* �v���C���[�̌������ړ������ɍ��킹�� */
		float fPlayerAngle = atan2f(vecInput.x, vecInput.z);	// �ړ������̊p�x(���W�A��)���擾
		fPlayerAngle = fAngleX - fPlayerAngle;					// �J�����̌����ƍ���
		this->PlayerStatusList->SetPlayerAngleX(fPlayerAngle);	// �v���C���[�̌�����ݒ�
	}
	else
	{
		// �ړ����͂�����Ă��Ȃ��ꍇ
		/* �ړ����x��0�ɂ��� */
		this->PlayerStatusList->SetPlayerNowMoveSpeed(0);
	}
}

// �W�����v
void CharacterPlayer::Player_Jump()
{
	/* �v���C���[�̃W�����v���� */

	/* �W�����v���͂�����Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_JUMP) == true)
	{
		// �W�����v���͂�����Ă���ꍇ
		/* �W�����v���� */
	}
}

// �d��
void CharacterPlayer::Player_Gravity()
{
	/* �v���C���[�̏d�͏��� */

}