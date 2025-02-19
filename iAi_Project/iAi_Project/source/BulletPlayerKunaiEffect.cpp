/* 2025.02.14 �e�r�듹 �t�@�C���쐬 */

#include "BulletPlayerKunaiEffect.h"

/* �N�i�C(�G�t�F�N�g)�N���X�̒�` */

// �R���X�g���N�^
BulletPlayerKunaiEffect::BulletPlayerKunaiEffect() : BulletBase()
{
	/* ������ */
	this->iObjectType					= OBJECT_TYPE_BULLET_PLAYER;		// �I�u�W�F�N�g�̎�ނ�"�e(�v���C���[)"�ɐݒ�
	this->vecKunaiTargetPosition		= VGet(0,0,0);						// �^�[�Q�b�g���W
	this->vecKunaiMoveDirection			= VGet(0, 0, 0);					// �N�i�C�̈ړ��������
	this->fKunaiTargetDistance			= 0.0f;								// �N�i�C�̔��˒n�_����^�[�Q�b�g�܂ł̋���
	this->fKunaiMoveDistance			= 0.0f;								// �N�i�C�̈ړ�����
	this->fKunaiAngleX					= 0.0f;								// �N�i�C��X����]�p�x
	this->fKunaiAngleY					= 0.0f;								// �N�i�C��Y����]�p�x
	this->iKunaiDeleteCount				= KUNAI_ATTACK_COUNT;				// �N�i�C�̍폜�J�E���g(�U������)
	this->bKunaiAttackFlg				= false;							// �N�i�C�̍U���t���O

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Bullet/Kunai_kari");
	}
}

// �f�X�g���N�^
BulletPlayerKunaiEffect::~BulletPlayerKunaiEffect()
{
	
}

// ������
void BulletPlayerKunaiEffect::Initialization()
{
	/* �N�i�C�̐����n�_����^�[�Q�b�g�܂ł̃x�N�g�����N�i�C�̈ړ��x�N�g���ɐݒ� */
	this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

	/* �N�i�C�̈ړ�������ݒ� */
	this->fKunaiTargetDistance = VSize(this->vecKunaiMoveDirection);

	/* �N�i�C�̈ړ��x�N�g���𐳋K�� */
	this->vecKunaiMoveDirection = VNorm(this->vecKunaiMoveDirection);

	/* X����]�̌v�Z�iY���̍����̍� / X-Z���ʏ�̋����j */
	/* �����̍� */ 
	float fHeightDiff = this->vecKunaiTargetPosition.y - this->vecPosition.y;
	/* X - Z ���ʏ�̋����݂̂��v�Z */ 
	float fHorizontalDist = VSize(VGet(this->vecKunaiTargetPosition.x - this->vecPosition.x, 0, this->vecKunaiTargetPosition.z - this->vecPosition.z));  

	/* X���̉�]�p�x�����߂�i���W�A���P�ʁj */
	fKunaiAngleX = atan2f(fHeightDiff, fHorizontalDist);

	/* Y����]�̌v�Z(X-Z ���ʏ�̕���) */
	fKunaiAngleY = atan2f(this->vecKunaiTargetPosition.x - this->vecPosition.x, this->vecKunaiTargetPosition.z - this->vecPosition.z); 
	
}

// �`��
void BulletPlayerKunaiEffect::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����](���̃��f�� + �v���C���[�̌����̕���]������) */
	MV1SetRotationXYZ(this->iModelHandle, VGet(DEG2RAD(90.0f) + fKunaiAngleX, DEG2RAD(180.0f) + fKunaiAngleY, 0.0f));

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}

// �X�V
void BulletPlayerKunaiEffect::Update()
{
	/* �N�i�C�̈ړ��x�N�g�����X�P�[�����Ĉړ� */
	this->vecPosition =  VAdd(this->vecPosition, VScale(vecKunaiMoveDirection,KUNAI_SPEED));;

	/* �N�i�C�̈ړ����������Z */
	this->fKunaiMoveDistance += KUNAI_SPEED;

	/* �N�i�C�̈ړ��������^�[�Q�b�g�܂ł̋����𒴂����� */ 
	if (this->fKunaiMoveDistance >= this->fKunaiTargetDistance)
	{
		/* �U���������s�� */
		this->Attack();
	}
}

// �U������
void BulletPlayerKunaiEffect::Attack()
{
	// �U�����̐ݒ���s��
	/* �N�i�C�̍U���t���O���m�F */
	if (this->bKunaiAttackFlg == false)
	{
		/* �N�i�C�̍U���t���O��ݒ� */
		this->bKunaiAttackFlg = true;

		/* �N�i�C�̍��W���^�[�Q�b�g���W�ɌŒ� */
		this->vecPosition = this->vecKunaiTargetPosition;

		/* ���f�����\���ɐݒ� */
		MV1SetVisible(this->iModelHandle, false);

		/* �����蔻��ݒ� */
		{
			this->stCollisionSqhere.vecSqhere = this->vecPosition;
			this->stCollisionSqhere.fSqhereRadius = KUNAI_ATTACK_RADIUS;
		}
	}

	// �N�i�C�̍폜����
	/* �N�i�C�̍폜�J�E���g(�U������)���c���Ă����ꍇ */
	if (iKunaiDeleteCount > 0)
	{
		/* �N�i�C�̍폜�J�E���g(�U������)�����Z */
		iKunaiDeleteCount--;
	}
	/* �N�i�C�̍폜�J�E���g(�U������)��0�ɂȂ����ꍇ */
	else
	{
		/* �N�i�C�̍폜�t���O��ݒ� */
		this->bDeleteFlg = true;
	}

}
