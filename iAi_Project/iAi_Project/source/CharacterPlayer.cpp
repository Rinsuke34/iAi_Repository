/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#include "CharacterPlayer.h"

/* �I�u�W�F�N�g */
#include "EffectTest.h"

/* �v���C���[�N���X�̒�` */

// �R���X�g���N�^
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* ������ */
	/* �f�[�^���X�g�擾 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	this->ObjectList		= dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

	/* �������������J�n */
	this->iModelHandle = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");

	/* �R���W�������X�V */
	CollisionUpdate();
}

// ������
void CharacterPlayer::Initialization()
{

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

	/* �U������(�e�X�g) */
	Player_Attack();
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

	/* �R���W�������X�V */
	CollisionUpdate();
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
		// ���ŗ������x��-�ɂ��鏈�����s��
		this->PlayerStatusList->SetPlayerNowFallSpeed(-10.0f);
	}

	/* �R���W�������X�V */
	CollisionUpdate();
}

// �d��
void CharacterPlayer::Player_Gravity()
{
	/* �v���C���[�̏d�͏��� */

	/* �����ʎ擾 */
	float fFallSpeed	=	this->PlayerStatusList->fGetPlayerNowFallSpeed();		// �����_�ł̉����ʎ擾
	fFallSpeed			+=	this->PlayerStatusList->fGetPlayerFallAcceleration();	// �����x�����Z

	/* �d�͂ɂ��ړ���̍��W���擾 */
	VECTOR vecNextPosition	=	this->vecPosition;
	vecNextPosition.y		-=	this->PlayerStatusList->fGetPlayerNowFallSpeed();

	/* ��l���̏㕔���̓����蔻�肩�牺�����֌������������쐬 */
	COLLISION_LINE stCollision;
	stCollision.vecLineStart	=	this->vecPosition;
	stCollision.vecLineStart.y	+=	100;		// �����œo��鍂���̏��

	stCollision.vecLineEnd		=	stCollision.vecLineStart;
	stCollision.vecLineEnd.y	-=	9999;

	/* �ȉ��A������(�߂��I�u�W�F�N�g�̂ݑΏۂɂ���悤�ɂ���) */
	/* ������擾 */
	auto& PlatformList = ObjectList->GetPlatformList();

	/* ���n������W */
	float	fStandPosY		= vecNextPosition.y;	// �����l���ړ���̍��W�ɐݒ�

	/* ����ƐڐG���邩�m�F */
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stCollision);

		/* �ڐG���Ă��邩�m�F */
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ
			/* �q�b�g�������W�����݂̒��n���W��荂���ʒu�ł��邩�m�F */
			if (stHitPolyDim.HitPosition.y > fStandPosY)
			{
				// ���݂̒��n���W��荂���ʒu�ł���ꍇ
				/* ���n���W���X�V */
				fStandPosY = stHitPolyDim.HitPosition.y;

				/* �����̉����x������������ */
				fFallSpeed = 0.f;
			}
		}
	}

	/* ���n���W���X�V */
	vecNextPosition.y = fStandPosY;

	/* �v���C���[���W���X�V */
	this->vecPosition = vecNextPosition;

	/* �������x���X�V */
	this->PlayerStatusList->SetPlayerNowFallSpeed(fFallSpeed);

	/* �R���W�������X�V */
	CollisionUpdate();
}

// �R���W�����X�V
void CharacterPlayer::CollisionUpdate()
{
	/* �v���C���[�̃R���W�����X�V���� */

	/* �v���C���[�̃R���W�������X�V */
	COLLISION_CAPSULE stCapsule;
	stCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0, 100, 0));
	stCapsule.vecCapsuleBottom	= VAdd(this->vecPosition, VGet(0, 0, 0));
	stCapsule.fCapsuleRadius	= 50.0f;

	/* �R���W������ݒ� */
	this->SetCollision_Capsule(stCapsule);
}

// �����`��
void CharacterPlayer::BloomDraw()
{
	/* ���̐F��ۑ� */
	int iBackUpFrames = MV1GetFrameNum(this->iModelHandle);
	std::vector<COLOR_F> vecOriginalDifColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalSpcColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalEmiColor(iBackUpFrames);
	std::vector<COLOR_F> vecOriginalAmbColor(iBackUpFrames);

	for (int i = 0; i < iBackUpFrames; i++)
	{
		vecOriginalDifColor[i] = MV1GetFrameDifColorScale(this->iModelHandle, i);
		vecOriginalSpcColor[i] = MV1GetFrameSpcColorScale(this->iModelHandle, i);
		vecOriginalEmiColor[i] = MV1GetFrameEmiColorScale(this->iModelHandle, i);
		vecOriginalAmbColor[i] = MV1GetFrameAmbColorScale(this->iModelHandle, i);
	}

	/* ���ׂẴt���[�������F�ŕ`��(��) */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
		MV1SetFrameSpcColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
		MV1SetFrameEmiColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
		MV1SetFrameAmbColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
	}

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);

	/* ���̐F�ɖ߂� */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		MV1SetFrameDifColorScale(this->iModelHandle, i, vecOriginalDifColor[i]);
		MV1SetFrameSpcColorScale(this->iModelHandle, i, vecOriginalSpcColor[i]);
		MV1SetFrameEmiColorScale(this->iModelHandle, i, vecOriginalEmiColor[i]);
		MV1SetFrameAmbColorScale(this->iModelHandle, i, vecOriginalAmbColor[i]);
	}
}

// �v���C���[�U��(��)
void CharacterPlayer::Player_Attack()
{
	/* �e�X�g�p�U������ */

	/* �U�������͂���Ă��邩�m�F */
	if (this->InputList->bGetGameInputAction(INPUT_TRG, GAME_ATTACK) == true)
	{
		EffectBase* Effect_Test = new TestEffect();
		Effect_Test->Effect_Load("FX_e_bullet");
		Effect_Test->SetPosition(VAdd(this->vecPosition, VGet(0.f, 10.f, 0.f)));

		dynamic_cast<TestEffect*>(Effect_Test)->Initialization();

		
		ObjectList->SetEffect(Effect_Test);
	}
}