/* 2025.02.04 �e�r�듹	�t�@�C���쐬 */

#include "CharacterPlayer.h"

// �`��
void CharacterPlayer::Draw()
{
	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);

	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����] */
	MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -(this->PlayerStatusList->fGetPlayerAngleX()), 0.0f));

	/* ���[�V�����̍Đ����Ԃ�ݒ� */
	MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(), this->PlayerStatusList->fGetMotionTimer_Move());
	MV1SetAttachAnimTime(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), this->PlayerStatusList->fGetMotionTimer_Attack());

	/* ���[�V�����̃u�����h����ݒ� */
	MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Move(), 0.3f);
	MV1SetAttachAnimBlendRate(this->iModelHandle, this->PlayerStatusList->iGetPlayerMotionAttachIndex_Attack(), 0.7f);

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);


	/* �e�X�g�p */
	DrawFormatString(200, 500 + 16 * 0, GetColor(255, 255, 255), "�ړ��n");
	DrawFormatString(200, 500 + 16 * 1, GetColor(255, 255, 255), "���݃��[�V�����ԍ� : %f", this->PlayerStatusList->iGetPlayerMotion_Move());
	DrawFormatString(200, 500 + 16 * 2, GetColor(255, 255, 255), "�ύX�O���[�V�����ԍ� : %f", this->PlayerStatusList->iGetPlayerMotion_Move_Old());
	DrawFormatString(200, 500 + 16 * 3, GetColor(255, 255, 255), "�Đ����� : %f", this->PlayerStatusList->fGetMotionTimer_Move());
	DrawFormatString(200, 500 + 16 * 4, GetColor(255, 255, 255), "�ŏI�Đ����� : %f", this->PlayerStatusList->fGetMotionTimer_Move_End());
	DrawFormatString(200, 500 + 16 * 5, GetColor(255, 255, 255), "�U���n");
	DrawFormatString(200, 500 + 16 * 6, GetColor(255, 255, 255), "���݃��[�V�����ԍ� : %f", this->PlayerStatusList->iGetPlayerMotion_Attack());
	DrawFormatString(200, 500 + 16 * 7, GetColor(255, 255, 255), "�ύX�O���[�V�����ԍ� : %f", this->PlayerStatusList->iGetPlayerMotion_Attack_Old());
	DrawFormatString(200, 500 + 16 * 8, GetColor(255, 255, 255), "�Đ����� : %f", this->PlayerStatusList->fGetMotionTimer_Attack());
	DrawFormatString(200, 500 + 16 * 9, GetColor(255, 255, 255), "�ŏI�Đ����� : %f", this->PlayerStatusList->fGetMotionTimer_Attack_End());
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
	DrawLine3D(VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(+50, 0, 0)), VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(-50, 0, 0)), iColor);
	DrawLine3D(VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(0, 0, +50)), VAdd(this->PlayerStatusList->vecGetCameraTarget(), VGet(0, 0, -50)), iColor);
}