/* 2025.03.10 ��򕗏� �t�@�C���쐬 */

#include "Gimmick_MoveFloor.h"

/* �ړ����N���X�̒�` */
// �R���X�g���N�^
Gimmick_MoveFloor::Gimmick_MoveFloor() : PlatformBase()
{
	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/MoveFloor/MoveFloor");
	}

	/* ������ */
	this->vecMovePos	= VGet(0.f, 0.f, 0.f);		// �ړ����̈ړ�����W
	this->bTargetMove	= true;						// �ړ����̈ړ�����W�Ɍ������Ă��邩(true:�ړ�����W�� / false:�������W��)
}

// �X�V
void Gimmick_MoveFloor::Update()
{
	/* �����_�ł̍��W��ۑ� */
	VECTOR vecPositionOld = this->vecPosition;

	/* �ړ�����W�Ɍ������Ă��邩�m�F */
	if (this->bTargetMove)
	{
		// �ړ�����W�Ɍ������Ă���ꍇ
		/* �ړ��������Z�o */
		VECTOR vecMoveDir = VSub(this->vecMovePos, this->vecPosition);
		float distance = VSize(vecMoveDir);

		/* �ڕW�n�_�֓��B���Ă��邩�m�F */
		if (distance <= GIMMICK_MOVEFLOOR_MOVE_SPEED)
		{

			// ���B�����ꍇ
			/* ���݂̍��W���ړ�����W�ɍ��킹�� */
			this->vecPosition = this->vecMovePos;

			/* �ړ�����W�Ɍ������Ă��Ȃ���Ԃɐݒ� */
			this->bTargetMove = false;
		}
		else
		{
			// ���B���Ă��Ȃ��ꍇ
			/* �ړ����s�� */
			this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(vecMoveDir), GIMMICK_MOVEFLOOR_MOVE_SPEED));
		}
	}
	else
	{
		// �������W�Ɍ������Ă���ꍇ
		/* �ړ��������Z�o */
		VECTOR vecMoveDir = VSub(this->vecPosition_Initial, this->vecPosition);
		float distance = VSize(vecMoveDir);

		/* �ڕW�n�_�֓��B���Ă��邩�m�F */
		if (distance <= GIMMICK_MOVEFLOOR_MOVE_SPEED)
		{
			// ���B�����ꍇ
			/* ���݂̍��W���������W�ɍ��킹�� */
			this->vecPosition = this->vecPosition_Initial;

			/* �ړ�����W�Ɍ������Ă����Ԃɐݒ� */
			this->bTargetMove = true;
		}
		else
		{
			// ���B���Ă��Ȃ��ꍇ
			/* �ړ����s�� */
			this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(vecMoveDir), GIMMICK_MOVEFLOOR_MOVE_SPEED));
		}
	}

	/* �ړ����̈ړ��ʂ�ݒ� */
	this->vecPlatformMove = VSub(this->vecPosition, vecPositionOld);

	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* �R���W��������n�� */
	MV1TerminateCollInfo(this->iModelHandle, this->iCollisionFrameNo);

	/* �R���W�����X�V */
	//MV1RefreshCollInfo(this->iModelHandle, this->iCollisionFrameNo, TRUE);

	UpdateCollisionFrame();
}

// �ړ�������ݒ�
void  Gimmick_MoveFloor::SetupMoveDirection(bool bVerticalDirection, int iMoveDistance)
{
	// ����
	// bVerticalDirection	:	���������Ɉړ����邩(true:�������� / false:��������)
	// iMoveDistance		:	�ړ�����(0:�Z���� / 1:������ / 2������)

	/* �ړ������擾 */
	float fMoveDistance = 0.f;

	/* �ړ������^�C�v�ɉ������l��ݒ� */
	switch (iMoveDistance)
	{
		/* �Z���� */
		case GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_SHORT:
			fMoveDistance = GIMMICK_MOVEFLOOR_MOVE_DISTANCE_SHORT;
			break;

		/* ������ */
		case GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_NORMAL:
			fMoveDistance = GIMMICK_MOVEFLOOR_MOVE_DISTANCE_NORMAL;
			break;

		/* ������ */
		case GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_LONG:
			fMoveDistance = GIMMICK_MOVEFLOOR_MOVE_DISTANCE_LONG;
			break;
	}

	/* �ړ�������ݒ� */
	{
		/* �������� */
		if (bVerticalDirection == true)
		{
			// ���������Ɉړ�����ꍇ
			/* �ړ�����W�����ݍ��W���������֐ݒ� */
			this->vecMovePos = VGet(this->vecPosition.x, this->vecPosition.y + fMoveDistance, this->vecPosition.z);
		}
		else
		{
			// ���������Ɉړ�����ꍇ
			/* ���݂̉������̉�]�ʂ��擾 */
			float fRotationY = this->vecRotation.y;

			/* �ړ�����W���擾������]��̕����ɂȂ�悤�ݒ� */
			this->vecMovePos = VGet(this->vecPosition.x + fMoveDistance * cosf(fRotationY), this->vecPosition.y, this->vecPosition.z + fMoveDistance * sinf(fRotationY));
		}
	}
}
