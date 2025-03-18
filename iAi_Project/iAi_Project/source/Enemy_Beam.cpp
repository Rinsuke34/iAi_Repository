/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Beam.h"

// �R���X�g���N�^
Enemy_Beam::Enemy_Beam() : Enemy_Basic()
{

	/* �I�u�W�F�N�g�̃n���h�� */
	this->pBulletRangeBeam = nullptr;	// �r�[���̒e
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Beam/Enemy_Beam");
	}

	this->pPlayer = ObjectList->GetCharacterPlayer();// �v���C���[
	this->iFiringCount = ENEMY_BEAM_INTERVAL;	// ���˃J�E���g
	this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;			// �r�[���`���[�W�J�E���g
	this->iBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;	//�r�[���̎����J�E���g
	this->bEffectGenerated		 = false;					// �x���G�t�F�N�g�����t���O
	this->bHitEffectGenerated	 = false;					// �q�b�g�G�t�F�N�g�����t���O
	this->bChargeFlg			 = false;					// �`���[�W�t���O
	this->bFiringFlg			 = false;					// ���˃t���O
	this->bDirectionFlg			 = true;					// �����Œ�t���O
	this->bBeamSEFlg			 = false;					// �r�[��SE�t���O
	this->bShotFlg				 = true;					// �V���b�g�t���O
	this->bWarningEffectFlg		 = true;					// �x���G�t�F�N�g�t���O

	/*���[�V�����֘A*/
// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
	this->iBeamAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);
	// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
	this->fBeamAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackAttachIndex);

	this->bBeamAttackMotionFlg			= false;			// �U�����[�V�����t���O
	this->bBeamAttackNowMotionFlg		= false;			// �U�������[�V�����t���O
	this->bBeamAttackEndMotionFlg		= false;			// �U���I�����[�V�����t���O
	this->bBeamAttackEndLoopMotionFlg	= false;			// �U���I�����[�v���[�V�����t���O
}

// �f�X�g���N�^
Enemy_Beam::~Enemy_Beam()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Beam::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();

	UpdataLightFrame();
}

// �G���ړ�������
void Enemy_Beam::MoveEnemy()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�U���\���G�t�F�N�g�̍��W��ݒ�
	VECTOR vecWarning = VGet(vecPosition.x, vecPosition.y + vecPosition.y / 2, vecPosition.z);

	

	if (this->bDirectionFlg == true)
	{
		//�G�l�~�[�̌�����ݒ�
		this->vecRotation = VRot;
		//�G�l�~�[�̌������擾
		MV1SetRotationXYZ(iModelHandle, VRot);
	}

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	

	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerY < ENEMY_Y_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
		iFiringCount--;

		//�U���J�E���g�����˃J�E���g���傫�����m�F
		if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
		{
			// �U���J�E���g�����˃J�E���g���傫���ꍇ
			if (this->bWarningEffectFlg == true)	// �x���G�t�F�N�g�t���O���L���̏ꍇ
			{
				this->bWarningEffectFlg = false;

				this->bShotFlg = true;
			/* �U���\���G�t�F�N�g�ǉ� */
			{
				/* �U���\���G�t�F�N�g�𐶐� */
				this->pEffectWarning = new EffectManualDelete();

				/* �G�t�F�N�g�̓ǂݍ��� */
				this->pEffectWarning->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet_warning/FX_e_bullet_warning")));

				/* �G�t�F�N�g�̍��W�ݒ� */
				this->pEffectWarning->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT, vecPosition.z));

				/* �G�t�F�N�g�̉�]�ʐݒ� */
				this->pEffectWarning->SetRotation(this->vecRotation);

				/* �G�t�F�N�g�̏����� */
				this->pEffectWarning->Initialization();

				/* �G�t�F�N�g�����X�g�ɓo�^ */
				{
					/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					/* �G�t�F�N�g�����X�g�ɓo�^ */
					ObjectListHandle->SetEffect(this->pEffectWarning);
				}
			}
		}
		}
	}
	//�G�t�F�N�g��nullptr�łȂ����m�F
	if (this->pEffectWarning != nullptr)
		{
		// �G�t�F�N�g���Đ������ǂ����m�F
		if (IsEffekseer3DEffectPlaying(this->pEffectWarning->iGetEffectHandle()))
		{
			if (this->bShotFlg == true)
			{
				// �G�t�F�N�g���Đ��I�����Ă���ꍇ
			// �r�[���𔭎˂���
			Player_Range_Beam_Shot();

			// ���˃J�E���g��������
			this->iFiringCount = ENEMY_BEAM_INTERVAL;

				this->bWarningEffectFlg = true;
			}
			this->bShotFlg = false;
		}
	}


}

// �r�[���̔���
void Enemy_Beam::Player_Range_Beam_Shot()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	// �r�[���𐶐�
	this->pBulletRangeBeam = new BulletEnemyRangeBeam;

	//���ʉ��Đ�
	gpDataList_Sound->SE_PlaySound(SE_ENEMY_BEAM_CHARGE);

	//�`���[�W�t���O��L����
	this->bChargeFlg = true;

	/* �U���̐��������̐ݒ� */
	/* �U�����W���Z�o */

	//�G�l�~�[�̌�����������
	VECTOR vecAdd = VGet(0, 0, 0);

	// ���˂����������ݒ�
	vecAdd = VNorm(vecAdd);

	// ���˂����鍂���ƕ���ݒ�
	vecAdd.y = PLAYER_HEIGHT / 2.f;
	vecAdd.x = PLAYER_WIDE / 2.f;

	// �U���������W���G�l�~�[�������Ă�������ɐݒ�
	this->pBulletRangeBeam->SetPosition(VAdd(this->vecPosition, vecAdd));

	// �ړ�����e�̌�����ݒ�
	this->pBulletRangeBeam->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));

	//������
	this->pBulletRangeBeam->Initialization();

	//�o���b�g���X�g�ɒǉ�
	ObjectList->SetBullet(this->pBulletRangeBeam);

}

//�`���[�W
void Enemy_Beam::Charge()
{
	if (this->bChargeFlg == TRUE)
	{
		iChargeCount--;	// �`���[�W�J�E���g�����Z

		this->bDirectionFlg = true;

		// �`���[�W�J�E���g��0�ȉ����m�F
		if (this->iChargeCount <= 0)
		{
			// �`���[�W�J�E���g��0�ȉ��̏ꍇ
			//�U���I�����[�v���[�V�����t���O�𖳌���
			this->bBeamAttackEndLoopMotionFlg = false;

			//�U�����[�V�����t���O��L����
			this->bBeamAttackMotionFlg = true;

			// �`���[�W�J�E���g��������
			this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;

			this->bChargeFlg = false;

			this->bFiringFlg = true;

			this->bDirectionFlg = false;

			this->bBeamSEFlg = true;
		}
	}
	if (this->bFiringFlg == TRUE)
	{
		if (this->bBeamSEFlg == TRUE)
		{
			//���ʉ��Đ�
			gpDataList_Sound->SE_PlaySound(SE_ENEMY_BEAM_SHOT);

			this->bBeamSEFlg = false;
		}

		// �r�[���̎����J�E���g�����Z
		this->iBeamDurationCount--;
		// �r�[���̎����J�E���g��0�ȉ����m�F
		if (this->iBeamDurationCount <= 0)
		{
			// �r�[���̎����J�E���g��0�ȉ��̏ꍇ
			this->bFiringFlg = false;

			this->iBeamDurationCount = ENEMY_BEAM_DURATION_COUNT;
		}
	}
}

// �G�l�~�[���f���A�j���[�V����
void Enemy_Beam::Enemy_Model_Animation()
{

	// �U�����[�V�����t���O���L�����m�F
	if (this->bBeamAttackMotionFlg)
	{
		// �U�����[�V�����t���O���L���̏ꍇ
		this->fBeamAttackPlayTime += 0.5f;
		// �Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackAttachIndex, this->fBeamAttackPlayTime);

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
		if (this->fBeamAttackPlayTime >= this->fBeamAttackTotalTime)
		{
			// �A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
			// �A�^�b�`�����U���A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iBeamAttackAttachIndex);
			// �Đ����Ԃ�����������
			this->fBeamAttackPlayTime = 0.0f;
			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iBeamAttackNowAttachIndex = MV1AttachAnim(this->iModelHandle, 1, -1, FALSE);
			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fBeamAttackNowTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackNowAttachIndex);

			this->bBeamAttackNowMotionFlg = true;
			// �U�����[�V�����t���O�𖳌���
			this->bBeamAttackMotionFlg = false;
		}
	}

	if (this->bBeamAttackNowMotionFlg)
	{
		this->fBeamAttackNowPlayTime += 1.0f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackNowAttachIndex, this->fBeamAttackNowPlayTime);

		if (this->fBeamAttackNowPlayTime >= this->fBeamAttackNowTotalTime)
		{
			if (this->iBeamDurationCount <= this->iChargeCount)
			{
				// �A�^�b�`�����A�j���[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, iBeamAttackNowAttachIndex);
				this->fBeamAttackNowPlayTime = 0.0f;
				// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
				this->iBeamAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);
				// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
				this->fBeamAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackEndAttachIndex);

				this->bBeamAttackNowMotionFlg = false;
				this->bBeamAttackEndMotionFlg = true;

				
			}
		}
	}

	if (this->bBeamAttackEndMotionFlg)
	{
		this->fBeamAttackEndPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackEndAttachIndex, this->fBeamAttackEndPlayTime);

		if (this->fBeamAttackEndPlayTime >= this->fBeamAttackEndTotalTime)
		{
			// �A�^�b�`�����A�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, iBeamAttackEndAttachIndex);
			this->fBeamAttackEndPlayTime = 0.0f;
			// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
			this->iBeamAttackEndLoopAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, TRUE);
			// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
			this->fBeamAttackEndLoopTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex);

			this->bBeamAttackEndMotionFlg = false;
			this->bBeamAttackEndLoopMotionFlg = true;

			this->bDirectionFlg = true;
		}
	}

	if (this->bBeamAttackEndLoopMotionFlg)
	{
		this->fBeamAttackEndLoopPlayTime += 0.5f;
		MV1SetAttachAnimTime(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex, this->fBeamAttackEndPlayTime);

		if (this->fBeamAttackEndPlayTime >= this->fBeamAttackEndLoopTotalTime)
		{
			this->fBeamAttackEndLoopPlayTime = 0.0f;
			this->bBeamAttackEndLoopMotionFlg = false;
			// �A�j���[�V�����̃��[�v���I��������A�ŏ��̍U�����[�V�����t���O���ēx�L����
			this->bBeamAttackMotionFlg = true;
		}
	}
}

// �X�V
void Enemy_Beam::Update()
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

	// �G�l�~�[���f���A�j���[�V����
	Enemy_Model_Animation();

	// �`���[�W
	Charge();

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
				EffectManualDelete* AddEffect = new EffectManualDelete();

				/* �G�t�F�N�g�ǂݍ��� */
				AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_hit/FX_hit")));

				/* �G�t�F�N�g�̍��W�ݒ� */
				AddEffect->SetPosition(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z));

				/* �G�t�F�N�g�̉�]�ʐݒ� */
				AddEffect->SetRotation(this->vecRotation);

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
		this->bDirectionFlg = false;
		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iBeamAttackEndLoopAttachIndex);

		//�r�[���G�t�F�N�g���폜
		if (this->pBulletRangeBeam != nullptr)
		{
			this->pBulletRangeBeam->SetDeleteFlg(true);
		}

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

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
