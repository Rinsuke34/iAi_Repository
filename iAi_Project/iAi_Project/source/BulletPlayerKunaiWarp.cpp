/* 2025.03.13 �e�r�듹 �t�@�C���쐬 */

#include "BulletPlayerKunaiWarp.h"

/* �N�i�C(���[�v)�N���X�̒�` */

// �R���X�g���N�^
BulletPlayerKunaiWarp::BulletPlayerKunaiWarp()
{
	this->pTargetEnemy = nullptr;							// �G�Ǘ�
}

// �f�X�g���N�^
BulletPlayerKunaiWarp::~BulletPlayerKunaiWarp()
{

}

// ������
void BulletPlayerKunaiWarp::Initialization()
{
	/* �N�i�C�̐����n�_����^�[�Q�b�g�܂ł̃x�N�g�����N�i�C�̈ړ��x�N�g���ɐݒ� */
	this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

	/* �N�i�C�̎ː�����m�F��������R���W������ݒ� */
	COLLISION_LINE stCollisionLine;

	/* �ː��̊J�n�_��ݒ� */
	stCollisionLine.vecLineStart = this->StageStatusList->vecGetCameraPosition();

	/* �ː��̏I���_��ݒ� */
	stCollisionLine.vecLineEnd = this->vecKunaiTargetPosition;

	/* �N�i�C���˒n�_����^�[�Q�b�g�̍ŏ��x�N�g����ێ����� */
	VECTOR vecMinDirection = VSub(this->vecKunaiTargetPosition, this->StageStatusList->vecGetCameraPosition());

	/* �N�i�C���˒n�_����^�[�Q�b�g�̍ŏ�������ێ����� */
	float fMinDistance = VSize(vecMinDirection);

	/* �v���b�g�t�H�[�����擾 */
	auto& PlatformList = ObjectList->GetCollisionList();

	// �ː���Ƀv���b�g�t�H�[�������݂��邩�m�F����
	for (auto* platform : PlatformList)
	{
		/* �v���b�g�t�H�[���ƐڐG���Ă��邩�m�F */
		MV1_COLL_RESULT_POLY stHitPoly = platform->HitCheck_Line(stCollisionLine);

		/* �ڐG���Ă���ꍇ */
		if (stHitPoly.HitFlag == true)
		{
			/* �N�i�C���˒n�_����ڐG�n�_�̃x�N�g����ݒ� */
			VECTOR vecDirection = VSub(stHitPoly.HitPosition, this->StageStatusList->vecGetCameraPosition());

			/* �N�i�C���˒n�_����ڐG�n�_�̋�����ݒ� */
			float fDistance = VSize(vecDirection);

			/* �N�i�C�̎ː���̍ŏ��������m�F */
			if (fMinDistance >= fDistance)
			{
				/* �ڐG�������W���^�[�Q�b�g���W�ɐݒ� */
				vecKunaiTargetPosition = stHitPoly.HitPosition;

				/* �N�i�C�̈ړ��x�N�g�����Đݒ� */
				this->vecKunaiMoveDirection = VSub(this->vecKunaiTargetPosition, this->vecPosition);

				/* �N�i�C�̎ː���̍ŏ��������X�V */
				fMinDistance = fDistance;
			}
		}
	}

	/* �N�i�C�̈ړ�������ݒ� */
	this->fKunaiTargetDistance = VSize(this->vecKunaiMoveDirection);

	/* �N�i�C�̈ړ��x�N�g���𐳋K�� */
	this->vecKunaiMoveDirection = VNorm(this->vecKunaiMoveDirection);

	/* ���f����X����]�̌v�Z */
	/* ����(Y��)�̍� */
	float fHeightDiff = this->vecKunaiTargetPosition.y - this->vecPosition.y;
	/* X - Z ���ʏ�̋������v�Z */
	float fHorizontalDist = VSize(VGet(this->vecKunaiTargetPosition.x - this->vecPosition.x, 0, this->vecKunaiTargetPosition.z - this->vecPosition.z));

	/* X���̉�]�p�x�����߂�i���W�A���P�ʁj */
	fKunaiAngleX = atan2f(fHeightDiff, fHorizontalDist);

	/* ���f����Y����]�̌v�Z(X-Z ���ʏ�̕���) */
	fKunaiAngleY = atan2f(this->vecKunaiTargetPosition.x - this->vecPosition.x, this->vecKunaiTargetPosition.z - this->vecPosition.z);
}

// �`��
void BulletPlayerKunaiWarp::Draw()
{
	/* ���W�ݒ� */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* ���f����](���̃��f���̌��� + �W�I�̌����̕���]������) */
	MV1SetRotationXYZ(this->iModelHandle, VGet(fKunaiAngleX, DEG2RAD(180.0f) + fKunaiAngleY, 0.0f));

	/* ���f���`�� */
	MV1DrawModel(this->iModelHandle);
}

// �X�V
void BulletPlayerKunaiWarp::Update()
{
	/* �N�i�C�̈ړ��x�N�g�����X�P�[�����Ĉړ� */
	this->vecPosition = VAdd(this->vecPosition, VScale(vecKunaiMoveDirection, KUNAI_SPEED));;

	/* �N�i�C�̈ړ����������Z */
	this->fKunaiMoveDistance += KUNAI_SPEED;

	/* �N�i�C�̈ړ��������^�[�Q�b�g�܂ł̋����𒴂����� */
	if (this->fKunaiMoveDistance >= this->fKunaiTargetDistance)
	{
		/* ���[�v�������s�� */
		this->Warp();
	}
}

// ���[�v����
void BulletPlayerKunaiWarp:: Warp()
{
	/* �^�[�Q�b�g�G�l�~�[�����݂��邩�m�F */
	if (this->pTargetEnemy != nullptr)
	{
		// �^�[�Q�b�g�G�l�~�[�����݂���ꍇ
		//�G�̌��Ƀ��[�v���A���j����
		/* �N�i�C�̍��W���^�[�Q�b�g���W�ɌŒ� */
		this->vecPosition = pTargetEnemy->vecGetPosition();

		/* ���f�����\���ɐݒ� */
		MV1SetVisible(this->iModelHandle, false);

		/* �N�i�C�̍U���t���O�������Ă��Ȃ����m�F */
		if (this->bKunaiAttackFlg == false)
		{
			/* �G�l�~�[�̊p�x����Y���̉�]�s������߂� */
			MATRIX matEnemyrRotation = MGetRotY((pTargetEnemy->vecGetRotation().y));

			/* �G�l�~�[�̌����̃x�N�g�� */
			VECTOR vecEnemyDirection = VGet(0, 0, 1);

			/* �s����x�N�g���ɕϊ� */
			vecEnemyDirection = VTransform(vecEnemyDirection, matEnemyrRotation);

			/* �G�l�~�[�̌����𐳋K�� */
			vecEnemyDirection = VNorm(vecEnemyDirection);

			/* �G�l�~�[�̌����̊p�x(���W�A��)���擾 */
			float fEnemyRotate = -atan2f(vecEnemyDirection.x, vecEnemyDirection.z);

			/* �v���C���[�̌�����G�Ƌt�ɐݒ� */
			this->PlayerStatusList->SetPlayerAngleX(fEnemyRotate - PI);

			/* �v���C���[�̃��[�v�ʒu��G�̌��ɐݒ� */
			VECTOR vecPlayerWarpPotition = VScale(vecEnemyDirection, 250);
			vecPlayerWarpPotition = VAdd(pTargetEnemy->vecGetPosition(), vecPlayerWarpPotition);

			/* �v���C���[�̍��W�����[�v�ʒu�ɐݒ� */
			this->ObjectList->GetCharacterPlayer()->SetPosition(vecPlayerWarpPotition);

			/* �v���C���[�̍U����Ԃ��擾 */
			int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

			/* �v���C���[�̍U����Ԃ��������U���\����Ԃł��邩�m�F */
			if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
			{
				// �������U���\����Ԃł���ꍇ
				/* �������U���\����Ԃ��L�����Z������ */
				this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
			}

			/* �v���C���[�̏�Ԃ�"���R���"�ɑJ�� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

			/* �v���C���[�̃��[�V������"�ߋ����U��(��)(�I��)"�ɕύX */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_STRONG_END);

			/* �X���[���[�V�����t���O���L���ł��邩�m�F */
			if (this->StageStatusList->bGetGameSlowFlg() == true)
			{
				// �L���ł���ꍇ
				/* �X���[���[�V�����t���O�𖳌��� */
				this->StageStatusList->SetGameSlowFlg(false);
			}

			/* �����蔻��ݒ� */
			{
				/* �G�̈ʒu�ɓ����蔻���ݒ� */
				this->stCollisionSqhere.vecSqhere = pTargetEnemy->vecGetPosition();

				/* �����蔻��̔��a��ݒ� */
				this->stCollisionSqhere.fSqhereRadius = 50;
			}

			/* �N�i�C�̍U���t���O��ݒ� */
			this->bKunaiAttackFlg = true;

			/* ���[�v��SE���Đ� */
			gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

			/* ���[�v�G�t�F�N�g�𐶐� */
			EffectSelfDelete_PlayerFollow* pWarpeEffect = new EffectSelfDelete_PlayerFollow(true);

			/* ���[�v�G�t�F�N�g�̓ǂݍ��� */
			pWarpeEffect->SetEffectHandle((this->EffectList->iGetEffect("charge_finish/FX_charge_finish")));

			/* ���[�v�G�t�F�N�g�̏����� */
			pWarpeEffect->Initialization();

			/* ���[�v�G�t�F�N�g�̎��Ԃ�ݒ� */
			pWarpeEffect->SetDeleteCount(90);

			/* ���[�v�G�t�F�N�g�����X�g�ɓo�^ */
			{
				/* ���[�v�G�t�F�N�g�����X�g�ɓo�^ */
				this->ObjectList->SetEffect(pWarpeEffect);
			}
		}
	}
	else
	{
		// �^�[�Q�b�g�G�l�~�[�����݂���ꍇ
		// �^�[�Q�b�g���W�Ƀ��[�v����
		/* �N�i�C�̍��W���^�[�Q�b�g���W�ɌŒ� */
		this->vecPosition = this->vecKunaiTargetPosition;

		/* �v���C���[���N�i�C�̍��W�Ɉړ� */
		this->ObjectList->GetCharacterPlayer()->SetPosition(this->vecPosition);

		/* �v���C���[�̍U����Ԃ��擾 */
		int iPlayerAttackState = this->PlayerStatusList->iGetPlayerAttackState();

		/* �v���C���[�̍U����Ԃ��������U���\����Ԃł��邩�m�F */
		if (iPlayerAttackState == PLAYER_ATTACKSTATUS_PROJECTILE_POSTURE)
		{
			// �������U���\����Ԃł���ꍇ
			/* �v���C���[�̏�Ԃ�"���R���"�ɑJ�� */
			this->PlayerStatusList->SetPlayerAttackState(PLAYER_ATTACKSTATUS_FREE);

			/* �v���C���[�̃��[�V�����𖳂��ɐݒ� */
			this->PlayerStatusList->SetPlayerMotion_Attack(MOTION_ID_ATTACK_NONE);

			/* �������U���\����Ԃ��L�����Z������ */
			this->PlayerStatusList->SetPlayerAimCancelledFlg(true);
		}

		/* �X���[���[�V�����t���O���L���ł��邩�m�F */
		if (this->StageStatusList->bGetGameSlowFlg() == true)
		{
			// �L���ł���ꍇ
			/* �X���[���[�V�����t���O�𖳌��� */
			this->StageStatusList->SetGameSlowFlg(false);
		}

		/* ���[�v��SE���Đ� */
		gpDataList_Sound->SE_PlaySound(SE_PLAYER_NIAI);

		/* ���[�v�G�t�F�N�g�𐶐� */
		EffectSelfDelete* pWarpeEffect = new EffectSelfDelete();

		/* ���[�v�G�t�F�N�g�̓ǂݍ��� */
		pWarpeEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_charge_finish/FX_charge_finish")));

		/* ���[�v�G�t�F�N�g�̏����� */
		pWarpeEffect->Initialization();

		/* ���[�v�G�t�F�N�g�̎��Ԃ�ݒ� */
		pWarpeEffect->SetDeleteCount(60);

		/* ���[�v�G�t�F�N�g�̍��W��ݒ� */
		pWarpeEffect->SetPosition(vecPosition);

		/* ���[�v�G�t�F�N�g�����X�g�ɓo�^ */
		{
			/* ���[�v�G�t�F�N�g�����X�g�ɓo�^ */
			this->ObjectList->SetEffect(pWarpeEffect);
		}

		/* �N�i�C�̍폜�t���O��ݒ� */
		this->bDeleteFlg = true;
	}

	/* �N�i�C�̍U���t���O�������Ă��邩�m�F */
	if (this->bKunaiAttackFlg == true)
	{
		// �N�i�C�̍U���t���O�������Ă���ꍇ
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
}
