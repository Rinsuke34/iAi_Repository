/* 2025.01.30 �ΐ�q�� �t�@�C���쐬 */

#include "BulletEnemyRangeMissile.h"

/* �~�T�C���e�N���X�̒�` */

// �R���X�g���N�^
BulletEnemyRangeMissile::BulletEnemyRangeMissile() : BulletBase()
{
	/* ������ */
	this->iObjectType = OBJECT_TYPE_BULLET_ENEMY;	// �I�u�W�F�N�g�̎�ނ�"�e(�G�l�~�[)"�ɐݒ�
	this->pEffect = nullptr;
	this->pEffectGuidance = nullptr;

	this->iDurationCount = ENEMY_MISSILE_DURATION_COUNT;				// �~�T�C���e�̎����J�E���g
	this->iBulletUPCount = ENEMY_MISSILE_BULLET_UP_COUNT;				// �~�T�C���e�ł��グ�J�E���g
	this->iBulletDownCount = ENEMY_MISSILE_BULLET_DOWN_COUNT;			// �~�T�C���e�ł������J�E���g
	this->iBulletGuidanceCount = ENEMY_MISSILE_BULLET_GUIDANCE_COUNT;	// �~�T�C���U���J�E���g
	this->iEnemyMissileDurationCount = ENEMY_MISSILE_DURATION_COUNT;	// �~�T�C���e�̎����J�E���g

	this->bPredictedLandingFlg = false;
	this->bSaveFlg = false;

	this->vecHitPosition = VGet(0, 0, 0);

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Missilepoint/Missilepoint");
	}
}

// �f�X�g���N�^
BulletEnemyRangeMissile::~BulletEnemyRangeMissile()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
	this->pEffect->SetDeleteFlg(true);
	this->pEffectGuidance->SetDeleteFlg(true);
}

// ������
void BulletEnemyRangeMissile::Initialization()
{
	/* �����蔻��ݒ� */
	{
		this->stCollisionSqhere.vecSqhere = this->vecPosition;
		this->stCollisionSqhere.fSqhereRadius = 50.0f;
	}
	/* �G�t�F�N�g�ǉ� */
	{
		/* �~�T�C���G�t�F�N�g�𐶐� */
		this->pEffect = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet/FX_e_bullet")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffect->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffect->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pEffect->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffect);
		}
	}
		/* �G�t�F�N�g�ǉ� */
	{
		/* �~�T�C���U���G�t�F�N�g�𐶐� */
		this->pEffectGuidance = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffectGuidance->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_missile_contrail/FX_e_missile_contrail")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffectGuidance->SetPosition(VGet(vecPosition.x, vecPosition.y, vecPosition.z));

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffectGuidance->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pEffectGuidance->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffectGuidance);
		}
	}
}
// �~�T�C���e�̈ړ�����
void BulletEnemyRangeMissile::BulletEnemyRangeMissileMove()
{
	/* �v���C���[�̍��W���擾 */
	CharacterBase* player = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	iEnemyMissileDurationCount--;	// �~�T�C���e�̎����J�E���g�����Z


	// �����J�E���g���ł��グ�J�E���g�𒴂��Ă��邩�m�F
	if (iEnemyMissileDurationCount >= ENEMY_MISSILE_BULLET_UP_COUNT)
	{
		// �����J�E���g���ł��グ�J�E���g�𒴂��Ă���ꍇ

		// �v���C���[�̍����̔�����y���W���擾
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// �~�T�C���̈ړ��������v���C���[����������ɍX�V
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

		// �~�T�C���̈ړ����W�ƈړ����x���X�V
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 18));

		// �~�T�C���̗U���G�t�F�N�g���W���~�T�C���G�t�F�N�g�̐��b��ɐݒ�
		static const float delayTime = 5.0f; // ���b��̎���
		VECTOR delayedPosition = VAdd(VGet(vecPosition.x,vecPosition.y+600, vecPosition.z), VScale(this->vecDirection, -this->fMoveSpeed * delayTime));
		this->pEffectGuidance->SetPosition(delayedPosition);

	}
	// �����J�E���g���ł������J�E���g�𒴂��Ă��邩�m�F
	else if (iEnemyMissileDurationCount >= ENEMY_MISSILE_BULLET_DOWN_COUNT)
	{
		// �����J�E���g���ł������J�E���g�𒴂��Ă���ꍇ

		// �~�T�C���̈ړ�������������ɐݒ�
		this->vecDirection = VGet(0, 1, 0);

		// �ēx�~�T�C���̈ړ����x���X�V
		//this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 30));

		// �~�T�C���̗U���G�t�F�N�g���W���~�T�C���G�t�F�N�g�̐��b��ɐݒ�
		static const float delayTime = 5.0f; // ���b��̎���
		VECTOR delayedPosition = VAdd(VGet(vecPosition.x,vecPosition.y-600, vecPosition.z), VScale(this->vecDirection, -this->fMoveSpeed * delayTime));
		this->pEffectGuidance->SetPosition(delayedPosition);
	}
	// �����J�E���g���U���J�E���g�𒴂��Ă��邩�m�F
	else if (iEnemyMissileDurationCount >= ENEMY_MISSILE_BULLET_GUIDANCE_COUNT)
	{
		// �����J�E���g���U���J�E���g�𒴂��Ă���ꍇ

		//���ʉ��Đ�
		gpDataList_Sound->SE_PlaySound(SE_ENEMY_MISSILE_DOWN);

		// �v���C���[�̍����̔�����y���W���擾
		playerPos.y += PLAYER_HEIGHT / 2.f;

		// �~�T�C���̈ړ��������v���C���[����������ɍX�V
		this->vecDirection = VNorm(VSub(playerPos, this->vecPosition));

		// �~�T�C���̈ړ����W�ƈړ����x���X�V
		this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 25));

		// �~�T�C���̗U���G�t�F�N�g���W���~�T�C���G�t�F�N�g�̐��b��ɐݒ�
		static const float delayTime = 5.0f; // ���b��̎���
		VECTOR delayedPosition = VAdd(VGet(vecPosition.x, vecPosition.y - 600, vecPosition.z), VScale(this->vecDirection, -this->fMoveSpeed * delayTime));
		this->pEffectGuidance->SetPosition(delayedPosition);
	}

	// �~�T�C���̍��W���X�V
	this->vecPosition = VAdd(this->vecPosition, VScale(this->vecDirection, this->fMoveSpeed = 50));

	// �~�T�C���̃R���W�������W���X�V
	this->stCollisionSqhere.vecSqhere = this->vecPosition;

	// �~�T�C���̃G�t�F�N�g���W���X�V
	this->pEffect->SetPosition(this->vecPosition);

	// �~�T�C���̗U���G�t�F�N�g���W���~�T�C���G�t�F�N�g�̍��W�̏������ɐݒ�
	this->pEffectGuidance->SetPosition(this->vecPosition);



	// �~�T�C���̗U���G�t�F�N�g�̌�����ݒ�
	VECTOR rotation = VGet(atan2(this->vecDirection.y, this->vecDirection.z), atan2(this->vecDirection.x, this->vecDirection.z), 0);

	this->pEffectGuidance->SetRotation(rotation);

	// �~�T�C���̒��S����~�T�C���̈ړ������ɐ������쐬
	this->stFallCollision.vecLineStart = this->vecPosition;
	this->stFallCollision.vecLineStart.y += 25;
	this->stFallCollision.vecLineEnd = this->vecPosition;
	this->stFallCollision.vecLineEnd.y -= 9999;

	// �ړ���̍��W���擾(��������)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z;

	// �~�T�C���̒��S���牺�����֔��a�̒������������쐬
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += 25;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 60;

	// ������擾
	auto& PlatformList = ObjectList->GetPlatformList();





	// ����ƐڐG���邩�m�F
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// �ڐG���Ă��邩�m�F
		if (stHitPolyDim.HitFlag == 1)
		{
			BulletEnemyRangeMissileExplosion();
			break;
		}
	}
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stFallCollision);
		// �ڐG���Ă��邩�m�F
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ
			// ���f���̕`�ʈʒu��ڐG�n�_�ɐݒ肩��y���W���R���W�����Ɣ��Ȃ��悤�ɐݒ�
			this->vecModelPosition = stHitPolyDim.HitPosition;
			this->vecModelPosition.y += 15;
			break;
		}
	}
}


void BulletEnemyRangeMissile::BulletEnemyRangeMissileExplosion()
{
	// �ڐG���Ă���ꍇ
	if (bSaveFlg == FALSE)
	{
		//���ʉ��Đ�
		gpDataList_Sound->SE_PlaySound(SE_ENEMY_MISSILE_HIT);

		//���ʉ��Đ�
		gpDataList_Sound->SE_PlaySound(SE_ENEMY_MISSILE_EXPLOSION);

		//�~�T�C���G�t�F�N�g���폜
		this->pEffect->SetDeleteFlg(true);
		bSaveFlg = TRUE;
		/* �G�t�F�N�g�ǉ� */
		/*�����G�t�F�N�g�𐶐� */
		this->pEffectExplosion = new EffectManualDelete();

		/* �G�t�F�N�g�̓ǂݍ��� */
		this->pEffectExplosion->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_missile_explosion/FX_e_missile_explosion")));

		/* �G�t�F�N�g�̍��W�ݒ� */
		this->pEffectExplosion->SetPosition(this->vecPosition);

		/* �G�t�F�N�g�̉�]�ʐݒ� */
		this->pEffectExplosion->SetRotation(this->vecRotation);

		/* �G�t�F�N�g�̏����� */
		this->pEffectExplosion->Initialization();

		/* �G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			/* �G�t�F�N�g�����X�g�ɓo�^ */
			ObjectListHandle->SetEffect(this->pEffectExplosion);
		}

		// �G�t�F�N�g���Đ������ǂ����m�F
		if (IsEffekseer3DEffectPlaying(this->pEffectExplosion->iGetEffectHandle()))
		{
			// �G�t�F�N�g���Đ��I�����Ă���ꍇ
			this->bDeleteFlg = true;
		}
		else
		{
			//�e����0�ɂ���
			this->vecDirection = VGet(0, 0, 0);
			//�~�T�C���̐ڐG�����𒆐S�ɋ��̔��������蔻����쐬
			this->vecPosition = this->vecPosition;
			this->stCollisionSqhere.vecSqhere = this->vecPosition;
			this->stCollisionSqhere.fSqhereRadius = 570.0f;
			bSaveFlg = TRUE;

		}
	}
	}

//�R���W�����`��
void BulletEnemyRangeMissile::CollisionDraw()
{
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawLine3D(this->stFallCollision.vecLineStart, this->stFallCollision.vecLineEnd, GetColor(255, 0, 0));

	//�����̓����蔻���`��
	DrawSphere3D(this->stCollisionSqhere.vecSqhere, this->stCollisionSqhere.fSqhereRadius, 12, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);


}

// �`��
void BulletEnemyRangeMissile::Draw()
{
	// ���f���̍��W��ݒ�
	MV1SetPosition(this->iModelHandle, this->vecModelPosition);

	// ���f���̕`��
	MV1DrawModel(this->iModelHandle);
}

// �X�V
void BulletEnemyRangeMissile::Update()
{
	/* ������ */


	// �{���̓v���C���[���ō폜�t���O��ݒ肷��\��

	// �����J�E���g��0���傫�����m�F
	if (iEnemyMissileDurationCount > 0)
	{
		// �����J�E���g��0���傫���ꍇ

		// �����J�E���g�����Z
		iEnemyMissileDurationCount--;
	}
	else
	{
		// �����J�E���g��0�ȉ��̏ꍇ

		// �폜�t���O��L����
		this->bDeleteFlg = true;
	}

	// �~�T�C���̈ړ�����
	BulletEnemyRangeMissileMove();
}
