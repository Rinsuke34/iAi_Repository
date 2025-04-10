/* 2025.03.17 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Fixed.h"

// �R���X�g���N�^
Enemy_Fixed::Enemy_Fixed() : Enemy_Basic()
{

	/* �I�u�W�F�N�g�̃n���h�� */
	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;
	//�@�I�u�W�F�N�g�̎�ނ�TypeEnemy�ɐݒ�
	this->iObjectType = OBJECT_TYPE_ENEMY;

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = this->iModelscaffoldHandle = ModelListHandle->iGetModel("Enemy/Enemy_Fixed/Enemy_Fixed");

	}
}

// �f�X�g���N�^
Enemy_Fixed::~Enemy_Fixed()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Fixed::Initialization()
{
	/* �R���W�����Z�b�g */
	//�G�l�~�[�̃J�v�Z�����a
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//�J�v�Z���R���W�����̏�̍��W
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//�J�v�Z���R���W�����̉��̍��W
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();

	//��������t���[���̏���
	UpdataLightFrame();
}

// �G���ړ�������
void Enemy_Fixed::MoveEnemy()
{
	// �d�͏���
	this->vecMove.y -= ENEMY_GRAVITY_SREED;

	// �G�l�~�[�̍��W���X�V
	this->vecPosition.y += this->vecMove.y;

}


// �X�V
void Enemy_Fixed::Update()
{
	/* �o���b�g���X�g���擾 */
	auto& BulletList = ObjectList->GetBulletList();

	/* �v���C���[�U���ƐڐG���邩�m�F */
	for (auto* bullet : BulletList)
	{
		/* �I�u�W�F�N�g�^�C�v��"�e(�v���C���[)"���邢��"�ߐڍU��(�v���C���[)"�ł��邩�m�F */
		if ((bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER) || (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER))
		{
			// �e(�v���C���[)�̏ꍇ
			/* �e�Ƃ̐ڐG���� */
			if (bullet->HitCheck(this->stCollisionCapsule) == true)
			{
				// �ڐG���Ă���ꍇ
				/* �_���[�W���� */
				this->iNowHp -= 1;
			}
		}
	}
	// �G�l�~�[���ړ�������
	MoveEnemy();

	//�d�͏���
	Enemy_Gravity();

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ

		//�폜�t���O��L���ɂ���
		this->bDeleteFlg = true;
	}
}
