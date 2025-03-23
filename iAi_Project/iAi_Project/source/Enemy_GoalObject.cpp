/* 2025.01.21 ��򕗏� �t�@�C���쐬 */

#include "Enemy_GoalObject.h"

/* �S�[���I�u�W�F�N�g�N���X�̒�` */

// �R���X�g���N�^
Enemy_GoalObject::Enemy_GoalObject() : Enemy_Basic()
{
	/* ������ */
	this->iMaxHp			= 1;
	this->iNowHp			= 1;
	this->iObjectType		= OBJECT_TYPE_ENEMY;	// �I�u�W�F�N�g�̎��
	this->bStageChangeFlg	= false;
	this->pEffect_Glory		= nullptr;		// �����G�t�F�N�g
	this->pEffect_Clear		= nullptr;		// ���j���G�t�F�N�g
	this->bPlayeSeFlg		= false;		// SE���Đ��J�n�������̃t���O(�Q�[���J�n��Ɏ��s���Ȃ��Ƒ��̃V�[�����ɍĐ�����邽��)


	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�Q�[����ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Goal_Object/Goal_Object");
	}
}

// �f�X�g���N�^
Enemy_GoalObject::~Enemy_GoalObject()
{
	/* �G�t�F�N�g���폜���� */
	{
		if (this->pEffect_Glory != nullptr)	{ this->pEffect_Glory->SetDeleteFlg(true); }
		if (this->pEffect_Clear != nullptr) { this->pEffect_Clear->SetDeleteFlg(true); }
	}

	/* ���[�v���鋰��̂���SE���~���� */
	gpDataList_Sound->SE_PlaySound_Stop(SE_GOAL);
}

// ������
void Enemy_GoalObject::Initialization()
{
	Enemy_Basic::Initialization();

	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.vecCapsuleBottom	= this->vecPosition;
	this->stCollisionCapsule.vecCapsuleTop		= VAdd(this->vecPosition, VGet(0.f, ENEMY_GOAL_OBJECT_HEIGHT, 0.f));
	this->stCollisionCapsule.fCapsuleRadius		= 100.0f;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();

	/* �G�t�F�N�g(����)���� */
	{
		/* �G�t�F�N�g(����)�𐶐� */
		this->pEffect_Glory = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffect_Glory->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_o_goal/FX_o_goal")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffect_Glory->SetPosition(VAdd(this->vecPosition, VGet(0.f, ENEMY_GOAL_OBJECT_HEIGHT / 2.f, 0.f)));

		// �G�t�F�N�g�̏�����
		this->pEffect_Glory->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(pEffect_Glory);
		}
	}
}

// �X�V
void Enemy_GoalObject::Update()
{
	/* SE���Đ��J�n�������̊m�F */
	if (this->bPlayeSeFlg == false)
	{
		// �Đ����Ă��Ȃ��ꍇ
		/* "�S�[���������鉹"��SE�����[�v�Đ� */
		gpDataList_Sound->SE_PlaySound_Loop_3D(SE_GOAL, this->vecPosition, SE_3D_SOUND_RADIUS);

		/* �Đ��t���O��L���ɂ��� */
		this->bPlayeSeFlg = true;
	}

	/* �o���b�g���X�g���擾 */
	auto& BulletList = ObjectList->GetBulletList();

	/* �v���C���[�̍U���ƐڐG���邩�m�F */
	for (auto* bullet : BulletList)
	{
		/* �I�u�W�F�N�g�^�C�v��"�ߐڍU��(�v���C���[)"�ł��邩�m�F */
		if (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER)
		{
			// �ߐڍU��(�v���C���[)�̏ꍇ
			/* �ߐڍU���Ƃ̐ڐG���� */
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
		/* �Q�[����Ԃ�"�X�e�[�W�N���A"�ɕύX���� */
		this->StageStatusList->SetGameStatus(GAMESTATUS_STAGE_CLEAR_SETUP);

		/* �G�t�F�N�g(���j��)���� */
		{
			/* �G�t�F�N�g(���j��)�𐶐� */
			this->pEffect_Clear = new EffectManualDelete();

			/* �G�t�F�N�g�̓ǂݍ��� */
			this->pEffect_Clear->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_suicide_light/FX_e_suicide_light")));

			/* �G�t�F�N�g�̍��W�ݒ� */
			this->pEffect_Clear->SetPosition(VAdd(this->vecPosition, VGet(0.f, ENEMY_GOAL_OBJECT_HEIGHT / 2.f, 0.f)));

			// �G�t�F�N�g�̏�����
			this->pEffect_Clear->Initialization();

			/* �G�t�F�N�g�����X�g�ɓo�^ */
			{
				/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
				DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

				/* �G�t�F�N�g�����X�g�ɓo�^ */
				ObjectListHandle->SetEffect(pEffect_Clear);
			}
		}

		/* "�S�[���������鉹"��SE���~ */
		gpDataList_Sound->SE_PlaySound_Stop(SE_GOAL);

		/* "�S�[�����o(�����ӂ��)"��SE���Đ� */
		gpDataList_Sound->SE_PlaySound_3D(SE_GOAL_SHINE, this->vecPosition, SE_3D_SOUND_RADIUS);
	}
}
