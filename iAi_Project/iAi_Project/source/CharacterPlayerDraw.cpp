/* 2025.02.04 �e�r�듹	�t�@�C���쐬 */

#include "CharacterPlayer.h"

// �`��
void CharacterPlayer::Draw()
{
	/* �U�����[�V�����g�p�t���O */
	bool	bUseAttackMotionFlg = false;

	/* �U�����[�V�������g�p���邩(�U�����[�V������"����"�ȊO�ł��邩)�m�F */
	if (this->PlayerStatusList->iGetPlayerMotion_Attack() != MOTION_ID_ATTACK_NONE)
	{
		// �U�����[�V�������g�p����ꍇ
		/* �U�����[�V�����g�p�t���O��L���ɂ��� */
		bUseAttackMotionFlg = true;
	}

	/* ���[�V�����̍Đ����Ԑݒ� */
	{
		/* �ړ��n���[�V�����̍Đ����Ԑݒ� */
		MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(), this->PlayerStatusList->fGetMotionTimer_Move());

		/* �U���n���[�V�����̍Đ����Ԑݒ� */
		/* �U�����[�V�����g�p�t���O���L���ł��邩�m�F */
		if (bUseAttackMotionFlg == true)
		{
			// �L���ł���ꍇ
			/* �U���n���[�V�����̍Đ����Ԑݒ� */
			MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), this->PlayerStatusList->fGetMotionTimer_Attack());
		}
	}

	/* ���[�V�����̃u�����h����ݒ� */
	{
		/* �S�g�̃��[�V�����u�����h�� */
		float	fWholeMoveBlendrate		= 1.f;		// �ړ����[�V����
		float	fWholeAttackBlendrate	= 0.f;		// �U�����[�V����

		/* �㔼�g�̃��[�V�����u�����h�� */
		float	fUpperMoveBlendRate		= 1.f;		// �ړ����[�V����
		float	fUpperAttackBlendRate	= 0.f;		// �U�����[�V����

		/* �U�����[�V�����g�p�t���O���L���ł��邩�m�F */
		if (bUseAttackMotionFlg == true)
		{
			// �L���ł���ꍇ
			/* �U�����[�V������"���U��(�I��)"�ł��邩�m�F */
			if (this->PlayerStatusList->iGetPlayerMotion_Attack() == MOTION_ID_ATTACK_STRONG_END)
			{
				// "���U��(�I��)"�ł���ꍇ
				/* �S�g�̃��[�V�����u�����h����ݒ� */
				// ���U�����[�V������100�p�[�Z���g�ɐݒ�
				fWholeMoveBlendrate		= 0.f;
				fWholeAttackBlendrate	= 1.f;
			}
			
			/* �㔼�g�̃��[�V�����u�����h����ݒ� */
			// ���U�����[�V������100�p�[�Z���g�ɐݒ�
			fUpperMoveBlendRate		= 0.f;
			fUpperAttackBlendRate	= 1.f;
		}

		/* �S�g�̃u�����h����ݒ� */
		// �ړ����[�V����
		float fBlendRate = this->PlayerStatusList->fGetNowMoveMotionBlendRate();
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(),		fWholeMoveBlendrate * (1.f - fBlendRate));
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move_Old(),	fWholeMoveBlendrate * fBlendRate);
		// �U�����[�V����
		fBlendRate = this->PlayerStatusList->fGetNowAttackMotionBlendRate();
		MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), fWholeAttackBlendrate);

		/* �㔼�g�̃u�����h����ݒ� */
		// �ړ����[�V����
		fBlendRate = this->PlayerStatusList->fGetNowMoveMotionBlendRate();
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(),		this->iUpperBodyFrameNo,	fUpperMoveBlendRate * (1.f - fBlendRate), TRUE);
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move_Old(),	this->iUpperBodyFrameNo,	fUpperMoveBlendRate * fBlendRate, TRUE);
		// �U�����[�V����
		fBlendRate = this->PlayerStatusList->fGetNowAttackMotionBlendRate();
		MV1SetAttachAnimBlendRateToFrame(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), this->iUpperBodyFrameNo, fUpperAttackBlendRate, TRUE);
	}

	/* �V�F�C�v��K�p */
	MV1SetShapeRate(this->iModelHandle, this->iShapeNo_Blink, this->fShapeRate);

	/* �v���C���[��Ԃ�"�ߐڍU����(��)"�ȊO�ł��邩�m�F */
	if (this->PlayerStatusList->iGetPlayerAttackState() != PLAYER_ATTACKSTATUS_MELEE_STRONG)
	{
		// �ߐڍU����(��)�ȊO�ł���ꍇ
		/* ���f���`�� */
		MV1DrawModel(this->iModelHandle);
	}
}

// �����`��
void CharacterPlayer::BloomDraw()
{
	/* �v���C���[��Ԃ�"�ߐڍU����(��)"�ȊO�ł��邩�m�F */
	if (this->PlayerStatusList->iGetPlayerAttackState() != PLAYER_ATTACKSTATUS_MELEE_STRONG)
	{
		// �ߐڍU����(��)�ȊO�ł���ꍇ
		/* ���f���`�� */
		CharacterBase::BloomDraw();
	}
}

// �����蔻��`��
void CharacterPlayer::CollisionDraw()
{
	CharacterBase::CollisionDraw();

	/* �v���C���[���W */
	int iColor = GetColor(255, 0, 0);
	DrawLine3D(VAdd(this->vecPosition, VGet(+50, 0, 0)), VAdd(this->vecPosition, VGet(-50, 0, 0)), iColor);
	DrawLine3D(VAdd(this->vecPosition, VGet(0, 0, +50)), VAdd(this->vecPosition, VGet(0, 0, -50)), iColor);

	/* ���������̃R���W���� */
	iColor = GetColor(0, 255, 0);
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, iColor);

	/* ���s�����̃R���W���� */
	iColor = GetColor(0, 0, 255);
	DrawCapsule3D(this->stHorizontalCollision[0].vecCapsuleTop, this->stHorizontalCollision[0].vecCapsuleBottom, this->stHorizontalCollision[0].fCapsuleRadius, 16, iColor, iColor, FALSE);
	DrawCapsule3D(this->stHorizontalCollision[1].vecCapsuleTop, this->stHorizontalCollision[1].vecCapsuleBottom, this->stHorizontalCollision[1].fCapsuleRadius, 16, iColor, iColor, FALSE);

	/* ���U�����g�p����ꍇ */
	if (this->PlayerStatusList->bGetMeleeSearchCollisionUseFlg() == true)
	{
		/* ���U�����b�N�I���͈� */
		iColor = GetColor(255, 0, 255);
		COLLISION_CAPSULE stMeleeCollision = this->PlayerStatusList->stGetMeleeSearchCollision();
		DrawCapsule3D(stMeleeCollision.vecCapsuleTop, stMeleeCollision.vecCapsuleBottom, stMeleeCollision.fCapsuleRadius, 16, iColor, iColor, FALSE);

		/* ���U���ړ�����W */
		iColor = GetColor(255, 255, 0);
		DrawCapsule3D(this->stMeleeStrongMoveCollsion.vecCapsuleTop, this->stMeleeStrongMoveCollsion.vecCapsuleBottom, this->stMeleeStrongMoveCollsion.fCapsuleRadius, 16, iColor, iColor, FALSE);
	}

	/* �J���������_ */
	iColor = GetColor(0, 255, 255);
	DrawLine3D(VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(+50, 0, 0)), VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(-50, 0, 0)), iColor);
	DrawLine3D(VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(0, 0, +50)), VAdd(this->StageStatusList->vecGetCameraTarget(), VGet(0, 0, -50)), iColor);
}