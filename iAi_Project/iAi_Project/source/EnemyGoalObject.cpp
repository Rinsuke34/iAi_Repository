/* 2025.01.21 ��򕗏� �t�@�C���쐬 */

#include "EnemyGoalObject.h"

/* �S�[���I�u�W�F�N�g�N���X�̒�` */

// �R���X�g���N�^
EnemyGoalObject::EnemyGoalObject() : EnemyBasic()
{
	/* ������ */
	this->iMaxHp			= 1;
	this->iNowHp			= 1;
	this->iObjectType		= OBJECT_TYPE_ENEMY;	// �I�u�W�F�N�g�̎��
	this->bStageChangeFlg	= false;

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Goal_Object_Kari");
	}
}

// �f�X�g���N�^
EnemyGoalObject::~EnemyGoalObject()
{

}

// ������
void EnemyGoalObject::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.vecCapsuleBottom	= this->vecPosition;
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.f, 100.f, 0.f));
	this->stCollisionCapsule.fCapsuleRadius		= 100.0f;
}

// �X�V
void EnemyGoalObject::Update()
{
	/* �o���b�g���X�g���擾 */
	auto& BulletList = ObjectList->GetBulletList();

	/* �v���C���[�̍U���ƐڐG���邩�m�F */
	for (auto* bullet : BulletList)
	{
		/* �I�u�W�F�N�g�^�C�v��"�e(�v���C���[)"�ł��邩�m�F */
		if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER)
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

	/* HP��0�ɂȂ��Ă��邩�m�F */
	if (this->iGetNowHP() <= 0)
	{
		// HP��0�ȉ��̏ꍇ
		/* �Q�[����Ԃ�"�G�f�B�b�g"�ɕύX���� */
		this->GameStatusList->SetGameStatus(GAMESTATUS_EDIT);
	}
}
