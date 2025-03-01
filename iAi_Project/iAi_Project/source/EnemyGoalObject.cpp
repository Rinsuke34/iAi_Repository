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
	this->pEffect_Glory		= nullptr;		// �����G�t�F�N�g
	this->pEffect_Clear		= nullptr;		// ���j���G�t�F�N�g

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/GoalObject/GoalObject/Goal_Object");
	}
}

// �f�X�g���N�^
EnemyGoalObject::~EnemyGoalObject()
{
	/* �G�t�F�N�g���폜���� */
	{
		if (this->pEffect_Glory != nullptr)	{ this->pEffect_Glory->SetDeleteFlg(true); }
		if (this->pEffect_Clear != nullptr) { this->pEffect_Clear->SetDeleteFlg(true); }
	}
}

// ������
void EnemyGoalObject::Initialization()
{
	EnemyBasic::Initialization();

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
		/* �Q�[����Ԃ�"�X�e�[�W�N���A"�ɕύX���� */
		this->StageStatusList->SetGameStatus(GAMESTATUS_STAGE_CLEAR);

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
	}
}

// �����`��
void EnemyGoalObject::BloomDraw()
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

	/* ���C�g�t���[��No�ɐݒ肳�ꂽ�ԍ��ȊO�����F�łɐݒ� */
	for (int i = 0; i < iBackUpFrames; i++)
	{
		/* �����t���[���ł��邩�m�F */
		if (std::find(aiLightFrameNo.begin(), aiLightFrameNo.end(), i) != aiLightFrameNo.end())
		{
			// �����t���[���ł���ꍇ
			/* �Ώۃt���[����ԐF�ŕ`�� */
			MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(1.f, 0.f, 0.f, 1.f));
		}
		else
		{
			// �����t���[���łȂ��ꍇ
			/* �Ώۃt���[�������F�ŕ`�� */
			MV1SetFrameDifColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameSpcColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameEmiColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
			MV1SetFrameAmbColorScale(this->iModelHandle, i, GetColorF(0.f, 0.f, 0.f, 1.f));
		}
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