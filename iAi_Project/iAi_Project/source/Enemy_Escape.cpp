/* 2025.01.2�W �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Escape.h"

// �R���X�g���N�^
Enemy_Escape::Enemy_Escape() : Enemy_Basic()
{

	this->iXescapedistance = ENEMY_X_ESCAPE_DISTANCE;		// X���̋���
	this->iZescapedistance = ENEMY_Z_ESCAPE_DISTANCE;		// Z���̋���
	this->iEscapespeed = ENEMY_ESCAPE_SPEED;			// �ړ����x
	this->fGravity = ENEMY_GRAVITY_SREED;				// �d��


	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;
	this->iObjectType = OBJECT_TYPE_ENEMY;	// �I�u�W�F�N�g�̎��

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Escape/Enemy_Escape");
		this->pEffect = nullptr;
	}
	this->bHitEffectGenerated = false;	// �q�b�g�G�t�F�N�g�����t���O
	this->bEscapeEffectGenerated = true;	// �����G�t�F�N�g�����t���O
	this->iRunAttachIndex = MV1AttachAnim(this->iModelHandle, 7, -1, FALSE);
	this->fRunTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iRunAttachIndex);
}

// �f�X�g���N�^
Enemy_Escape::~Enemy_Escape()
{

}

// ������
void Enemy_Escape::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

void Enemy_Escape::MoveEnemy()
{
	this->stHorizontalCollision.fCapsuleRadius = 50;
	this->stHorizontalCollision.vecCapsuleTop = VAdd(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z),VGet(0, 50, 0));
	this->stHorizontalCollision.vecCapsuleBottom = VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z);
	// �v���C���[�̍��W���擾
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	// �d�͏���
	this->vecMove.y -= ENEMY_GRAVITY_SREED;
	this->vecPosition.y += this->vecMove.y;

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_ESCAPE_DISTANCE && distanceToPlayerZ < ENEMY_Z_ESCAPE_DISTANCE)// x����z���̋�����600�����̏ꍇ
	{
		if (this->bEscapeEffectGenerated == true)
		{
			// �����G�t�F�N�g�����t���O��true�̏ꍇ
			// �����G�t�F�N�g���Đ������m�F
			// �G�t�F�N�g���Đ������ǂ����m�F
			//if (IsEffekseer3DEffectPlaying(this->pEffect->iGetEffectHandle()))
			//{
			//	// �G�t�F�N�g���Đ��I�����Ă���ꍇ
			//	// �����G�t�F�N�g�𐶐�
			//	this->pEffect = new EffectManualDelete();
			//}

			// �G�t�F�N�g�̓ǂݍ���




			if (this->pEffect != nullptr)
			{
				// �G�t�F�N�g���Đ������ǂ����m�F
				if (IsEffekseer3DEffectPlaying(this->pEffect->iGetEffectHandle()))
				{
					// �G�t�F�N�g�𐶐�
					this->pEffect = new EffectManualDelete();

					// �G�t�F�N�g�̓ǂݍ���
					this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_glitter/FX_e_glitter")));

					// �G�t�F�N�g�̍��W�ݒ�
					this->pEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

					// �G�t�F�N�g�̉�]�ʐݒ�
					this->pEffect->SetRotation(this->vecRotation);

					// �G�t�F�N�g�̏�����
					this->pEffect->Initialization();

					// �G�t�F�N�g�����X�g�ɓo�^
					{
						// "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾
						DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
						// �G�t�F�N�g�����X�g�ɓo�^
						ObjectListHandle->SetEffect(pEffect);
					}
				}
			}
			else
			{

				// �G�t�F�N�g�𐶐�
		this->pEffect = new EffectManualDelete();

		// �G�t�F�N�g�̓ǂݍ���
		this->pEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_glitter/FX_e_glitter")));

		// �G�t�F�N�g�̍��W�ݒ�
		this->pEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

		// �G�t�F�N�g�̉�]�ʐݒ�
		this->pEffect->SetRotation(this->vecRotation);

		// �G�t�F�N�g�̏�����
		this->pEffect->Initialization();

		// �G�t�F�N�g�����X�g�ɓo�^
		{
			// "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾
			DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
			// �G�t�F�N�g�����X�g�ɓo�^
			ObjectListHandle->SetEffect(pEffect);
		}
			}
			
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
		// �v���C���[���瓦����
		VECTOR directionAwayFromPlayer = VNorm(VSub(VGet(this->vecPosition.x, 0, this->vecPosition.z), VGet(playerPos.x, 0, playerPos.z)));

		// �v���C���[���瓦��������Ƒ��x��ݒ�
		this->vecPosition = VAdd(this->vecPosition, VScale(directionAwayFromPlayer, this->iEscapespeed));

		// �G�l�~�[�̌���������������
		VRot = VGet(0, 0, 0);

		// �v���C���[�̕����������悤�ɃG�l�~�[�̌������`
		VRot.y = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z);

		// �G�l�~�[�̌�����ݒ�
		this->vecRotation = VRot;
	}
}
}

void Enemy_Escape::Enemy_Gravity()
{
	// �ړ���̍��W���擾(��������)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	// ��l���̏㕔���̓����蔻�肩�牺�����֌������������쐬
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 9999;

	// ������擾
	auto& PlatformList = ObjectList->GetCollisionList();

	// ���n������W
	// �����l���ړ���̍��W�ɐݒ�
	float fStandPosY = vecNextPosition.y;

	// ����ƐڐG���邩�m�F
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// �ڐG���Ă��邩�m�F
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ

			// �q�b�g�������W�����݂̒��n���W��荂���ʒu�ł��邩�m�F
			if (stHitPolyDim.HitPosition.y >= fStandPosY)
			{
				// �G�l�~�[��y���W�����Z
				this->vecPosition.y = stHitPolyDim.HitPosition.y;
				this->vecMove.y = 0; // �������x�����Z�b�g

				// �q�b�g�������W���v���C���[�������ēo���ʒu���Ⴂ�ʒu�ł��邩�m�F
				if (fStandPosY < this->vecPosition.y + PLAYER_CLIMBED_HEIGHT)
				{
					// ���n���W���v���C���[�̌��݈ʒu���Ⴂ�ꍇ
					// �n�ʂɒ��n�����Ɣ��肷��
					// ���n���W�𒅒n�������W�ɍX�V
					fStandPosY = stHitPolyDim.HitPosition.y;
				}
				else
				{
					// ���n���W���v���C���[�̌��݈ʒu��荂���ꍇ
					// ���n���W���v���C���[���V��ɂ߂荞�܂Ȃ������ɍX�V
					fStandPosY = stHitPolyDim.HitPosition.y - PLAYER_HEIGHT - PLAYER_CLIMBED_HEIGHT;

					// ���[�v�𔲂���
					break;
				}
			}
		}
	}
}

//�R���W�����`��
void Enemy_Escape::CollisionDraw()
{
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}

// �G�l�~�[���f���A�j���[�V����
void Enemy_Escape::Enemy_Model_Animation()
{

	this->fRunPlayTime += 1.0f;
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

	//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
	if (this->fRunPlayTime >= this->fRunTotalTime)
	{
		// �A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
		// �Đ����Ԃ�����������
		this->fRunPlayTime = 0.0f;
	}
}

// �ړ�����(��������)
void Enemy_Escape::Movement_Horizontal()
{
	/* �ړ���̍��W���擾(��������) */
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x + this->vecMove.x;
	vecNextPosition.y = this->vecPosition.y;
	vecNextPosition.z = this->vecPosition.z + this->vecMove.z;

	/* 1�t���[���ł̈ړ��ʂ𕪊����Ĕ��肷��� */
	/* ���ړ��ʂɉ����ĕ�����ݒ肷�� */
	int iMoveHitCheckCount = (int)VSize(VGet(this->vecMove.x, 0, this->vecMove.z));

	/* ���������ړ��� */
	VECTOR vecDevisionMove = VScale(this->vecMove, 1.0f / iMoveHitCheckCount);

	/* �������Ĉړ�������̍��W */
	VECTOR vecDevisionMovePosition = this->vecPosition;

	/* �����ŃI�u�W�F�N�g�ɐڐG���Ă��邩���� */

	{

		/* ������擾 */
		auto& PlatformList = ObjectList->GetCollisionList();

		/* ����ƐڐG���邩�m�F */
		for (auto* platform : PlatformList)
		{
			/* ����Ƃ̐ڐG���� */
			for (int i = 0; i < PLAYER_MOVE_COLLISION_MAX; i++)
			{
				/* �I�u�W�F�N�g�ƐڐG���Ă��邩�m�F */
				MV1_COLL_RESULT_POLY_DIM stHitPolyDim = platform->HitCheck_Capsule(this->stHorizontalCollision);

				/* �ڐG���Ă��邩�m�F */
				if (stHitPolyDim.HitNum > 0)
				{
					this->bEscapeEffectGenerated = false;

				}

			}
		}
	}

	/* �v���C���[�̍��W���ړ������� */
	this->vecPosition = vecNextPosition;
}

// �X�V
void Enemy_Escape::Update()
{
	/* �o���b�g���X�g���擾 */
	auto& BulletList = ObjectList->GetBulletList();

	/* �v���C���[�U���ƐڐG���邩�m�F */
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

	MoveEnemy();

	Enemy_Gravity();

	Movement_Horizontal();

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ
		/* ���S�t���O��L���� */
		this->bDeadFlg = true;

		if (this->bHitEffectGenerated == FALSE)
		{
			/* Hit�G�t�F�N�g�ǉ� */
			{
				/* ���Ԍo�߂ō폜�����G�t�F�N�g��ǉ� */
				EffectSelfDelete* AddEffect = new EffectSelfDelete();

				/* �G�t�F�N�g�ǂݍ��� */
				AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_hit/FX_hit")));

				/* �G�t�F�N�g�̍��W�ݒ� */
				AddEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

				/* �G�t�F�N�g�̉�]�ʐݒ� */
				AddEffect->SetRotation(this->vecRotation);

				/* �G�t�F�N�g�̍폜�����܂ł̎��Ԃ�ݒ� */
				AddEffect->SetDeleteCount(25);

				/* �G�t�F�N�g�̏����� */
				AddEffect->Initialization();

				/* ���X�g�ɓo�^ */
				{
					/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					/* �G�t�F�N�g�����X�g�ɓo�^ */
					ObjectListHandle->SetEffect(AddEffect);
				}


				this->bHitEffectGenerated = TRUE;
			}
		}
		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		//MV1DetachAnim(this->iModelHandle, this->iBeamAttackAttachIndex);
		//MV1DetachAnim(this->iModelHandle, this->iBeamAttackNowAttachIndex);
		//MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndAttachIndex);
		//MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex);

		//���S���[�V�����̍Đ����Ԃ����Z
		this->fDiePlayTime += 2.5f;

		// ���S���[�V�������A�^�b�`
		this->iDieAttachIndex = MV1AttachAnim(this->iModelHandle, 6, -1, FALSE);

		//�A�^�b�`�������S���[�V�����̍Đ����Ԃ��Z�b�g
		MV1SetAttachAnimTime(this->iModelHandle, this->iDieAttachIndex, this->fDiePlayTime);

		// ���S���[�V�����̑��Đ����Ԃ��擾
		this->fDieTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iDieAttachIndex);


		// ���S���[�V�����̍Đ����Ԃ����Đ����ԂɒB�������m�F
		if (this->fDiePlayTime >= this->fDieTotalTime)
		{
		/* ���j���̏��������s */
		Defeat();

			//����SE�Đ�
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_DAMAGE);
		}
		return;
	}

	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
