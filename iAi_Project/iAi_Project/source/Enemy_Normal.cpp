/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Normal.h"

// �R���X�g���N�^
Enemy_Normal::Enemy_Normal() : Enemy_Basic()
{

	/* �I�u�W�F�N�g�̃n���h�� */
	this->pBulletRangeNormal = nullptr;	// �ߐڍU��(��)�̒e
	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;

	/* �I�u�W�F�N�g�̐ݒ� */

	//�I�u�W�F�N�g�̎�ނ�TypeEnemy�ɐݒ�
	this->iObjectType = OBJECT_TYPE_ENEMY;

	//�o������u���b�h�ʂ�ݒ�
	this->iBloodAmount = 10;

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Normal/Enemy_Normal");
	}

	/* �I�u�W�F�N�g�擾 */
	// �v���C���[���擾
	this->pPlayer = ObjectList->GetCharacterPlayer();


	/* ������ */

	// ���˃J�E���g
	this->iFiringCount = 0;

	// �U���J�E���g
	this->iGuidanceCount = ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL;

	// �v���C���[�U���q�b�g�G�t�F�N�g�����t���O
	this->bHitEffectGenerated = false;

	//�G�l�~�[�x���G�t�F�N�g�t���O
	this->bWarningEffectFlg = true;

	// �V���b�g�t���O
	this->bShotFlg = false;



	/*���[�V�����֘A*/

	// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
	this->iNormalAttackAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, FALSE);

	// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
	this->fNormalAttackTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackAttachIndex);

	/*���[�V�����֘A������*/

	//�U�����[�V�����t���O
	this->bNormalAttackMotionFlg = false;

	//�U�������[�V�����t���O
	this->bNormalAttackNowMotionFlg = false;

	//�U���I�����[�V�����t���O
	this->bNormalAttackEndMotionFlg = false;

	//�U���I�����[�v���[�V�����t���O
	this->bNormalAttackEndLoopMotionFlg = false;

	//�����Œ�t���O
	this->bDirectionFlg = true;
}

// �f�X�g���N�^
Enemy_Normal::~Enemy_Normal()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Normal::Initialization()
{
	/* �R���W�����Z�b�g */

	//�G�l�~�[�̃J�v�Z���R���W�����̔��a��ݒ�
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//�G�l�~�[�̃J�v�Z���R���W�����̏�̍��W��ݒ�
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//�G�l�~�[�̃J�v�Z���R���W�����̉��̍��W��ݒ�
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();

	//�����t���[������
	UpdataLightFrame();
}

// �G���ړ�������
void Enemy_Normal::MoveEnemy()
{
	// �d�͏���
	this->vecMove.y -= ENEMY_GRAVITY_SREED;

	// �G�l�~�[��y���W���X�V
	this->vecPosition.y += this->vecMove.y;

	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌����Œ�t���O���L�����m�F
	if (this->bDirectionFlg == true)
	{
		//�G�l�~�[�̌����Œ�t���O���L���̏ꍇ
		//�G�l�~�[�̌�����ݒ�
		this->vecRotation = VRot;

		//�G�l�~�[�̌������擾
		MV1SetRotationXYZ(iModelHandle, VRot);
	}

	//�v���C���[�ƃG�l�~�[�̎��̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//�G�l�~�[�����j����Ă��Ȃ����m�F
	if (this->iNowHp > 0)
	{
		//�G�l�~�[�����j����Ă��Ȃ��ꍇ
		// �v���C���[�ƃG�l�~�[�̋����̕������v�Z
		float distanceToPlayerSquared = (this->vecPosition.x - playerPos.x) * (this->vecPosition.x - playerPos.x) +
			(this->vecPosition.y - playerPos.y) * (this->vecPosition.y - playerPos.y) +
			(this->vecPosition.z - playerPos.z) * (this->vecPosition.z - playerPos.z);

		// ���G�͈͂̔��a�̕���
		float detectionRadiusSquared = ENEMY_Y_DISTANCE * ENEMY_Y_DISTANCE;

		// ���˃J�E���g������
		iFiringCount--;

		// �v���C���[�����G�͈͓��ɂ��邩�m�F
		if (distanceToPlayerSquared < detectionRadiusSquared)
		{
			// �v���C���[�����G�͈͓��ɂ���ꍇ�̏���
			//�U���J�E���g�����˃J�E���g���傫�����m�F
			if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
			{
				// �U���J�E���g�����˃J�E���g���傫���ꍇ
				//�G�l�~�[�U���\���G�t�F�N�g�t���O���L�����m�F
				if (this->bWarningEffectFlg == true)
				{
					//�G�l�~�[�U���\���G�t�F�N�g�t���O���L���̏ꍇ
					//�G�l�~�[�U���\���G�t�F�N�g�t���O�𖳌���
					this->bWarningEffectFlg = false;

					//�V���b�g�t���O��L����
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

						//�U���\��SE�Đ�
						gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_WARNING, this->vecPosition, SE_3D_SOUND_RADIUS);

						//�U���\���G�t�F�N�g�t���O���L���̏ꍇ
						if (this->bShotFlg == true)
						{
							//�U���\���G�t�F�N�g�t���O���L���̏ꍇ
							// �m�[�}���e�𔭎˂���
							Player_Range_Normal_Shot();

							// ���˃J�E���g��������
							this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;
						}

						//�V���b�g�t���O�𖳌���
						this->bShotFlg = false;
					}
				}
			}
		}
	}
}

// �m�[�}���e�̔���
void Enemy_Normal::Player_Range_Normal_Shot()
{
	//�G�l�~�[�����j����Ă��Ȃ����m�F
	if (this->iNowHp > 0)
	{
		//�G�l�~�[�����j����Ă��Ȃ��ꍇ
		// �v���C���[�̍��W���擾
		VECTOR playerPos = pPlayer->vecGetPosition();

		//�U���I�����[�v���[�V�����t���O�𖳌���
		this->bNormalAttackEndLoopMotionFlg = false;

		//�U�����[�V�����t���O��L����
		this->bNormalAttackMotionFlg = true;

		this->bWarningEffectFlg = true;
	}
}

// �G�l�~�[���f���A�j���[�V����
void Enemy_Normal::Enemy_Model_Animation()
{
	//�G�l�~�[�����j����Ă��Ȃ����m�F
	if (this->iNowHp > 0)
	{
		//�G�l�~�[�����j����Ă��Ȃ��ꍇ
		// �U�����[�V�����t���O���L�����m�F
		if (this->bNormalAttackMotionFlg)
		{
			// �U�����[�V�����t���O���L���̏ꍇ
			// �Đ����Ԃ����Z����
			this->fNormalAttackPlayTime += 0.5f;
			// �Đ����Ԃ��Z�b�g����
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackAttachIndex, this->fNormalAttackPlayTime);

			// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
			if (this->fNormalAttackPlayTime >= this->fNormalAttackTotalTime)
			{
				// �A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
				// �m�[�}���e�𐶐�
				this->pBulletRangeNormal = new BulletEnemyRangeNormal;
				//���ʉ��Đ�
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_IKURA_ATTACK, this->vecPosition, SE_3D_SOUND_RADIUS);

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
				this->pBulletRangeNormal->SetPosition(VAdd(this->vecPosition, vecAdd));

				// �ړ�����e�̌�����ݒ�
				this->pBulletRangeNormal->SetRotation(VGet(0.0f, -(this->vecRotation.y), 0.0f));

				//������
				this->pBulletRangeNormal->Initialization();

				//�o���b�g���X�g�ɒǉ�
				ObjectList->SetBullet(this->pBulletRangeNormal);

				// �A�^�b�`�����U���A�j���[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, iNormalAttackAttachIndex);

				// �Đ����Ԃ�����������
				this->fNormalAttackPlayTime = 0.0f;

				// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
				this->iNormalAttackNowAttachIndex = MV1AttachAnim(this->iModelHandle, 1, -1, FALSE);

				// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
				this->fNormalAttackNowTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackNowAttachIndex);

				// �U�������[�V�����t���O��L����
				this->bNormalAttackNowMotionFlg = true;

				// �U�����[�V�����t���O�𖳌���
				this->bNormalAttackMotionFlg = false;
			}
		}

		// �U�������[�V�����t���O���L�����m�F
		if (this->bNormalAttackNowMotionFlg)
		{
			// �U�������[�V�����t���O���L���̏ꍇ
			// �U�����̃A�j���[�V�����Đ����Ԃ����Z����
			this->fNormalAttackNowPlayTime += 0.5f;

			// �U�����̃A�j���[�V�����Đ����Ԃ��Z�b�g����
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackNowAttachIndex, this->fNormalAttackNowPlayTime);

			// �U�����̃A�j���[�V�����Đ����Ԃ����Đ����ԂɒB�������m�F
			if (this->fNormalAttackNowPlayTime >= this->fNormalAttackNowTotalTime)
			{
				// �U�����̃A�j���[�V�����Đ����Ԃ����Đ����ԂɒB�����ꍇ
				// �A�^�b�`�����A�j���[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, iNormalAttackNowAttachIndex);

				// �Đ����Ԃ�����������
				this->fNormalAttackNowPlayTime = 0.0f;

				// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
				this->iNormalAttackEndAttachIndex = MV1AttachAnim(this->iModelHandle, 4, -1, FALSE);

				// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
				this->fNormalAttackEndTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackEndAttachIndex);

				// �U���I�����[�V�����t���O��L����
				this->bNormalAttackNowMotionFlg = false;

				// �U���I�����[�V�����t���O��L����
				this->bNormalAttackEndMotionFlg = true;
			}
		}

		// �U���I�����[�V�����t���O���L�����m�F
		if (this->bNormalAttackEndMotionFlg)
		{
			// �U���I�����[�V�����t���O���L���̏ꍇ
			// �U���I���̃A�j���[�V�����Đ����Ԃ����Z����
			this->fNormalAttackEndPlayTime += 0.5f;

			// �U���I���̃A�j���[�V�����Đ����Ԃ��Z�b�g����
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackEndAttachIndex, this->fNormalAttackEndPlayTime);

			// �U���I���̃A�j���[�V�����Đ����Ԃ����Đ����ԂɒB�������m�F
			if (this->fNormalAttackEndPlayTime >= this->fNormalAttackEndTotalTime)
			{
				// �U���I���̃A�j���[�V�����Đ����Ԃ����Đ����ԂɒB�����ꍇ
				// �A�^�b�`�����A�j���[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, iNormalAttackEndAttachIndex);

				// �Đ����Ԃ�����������
				this->fNormalAttackEndPlayTime = 0.0f;

				// �G�l�~�[���f���ɍU���̃A�j���[�V�������A�^�b�`����
				this->iNormalAttackEndLoopAttachIndex = MV1AttachAnim(this->iModelHandle, 0, -1, TRUE);

				// �A�^�b�`�����U���A�j���[�V�����̑��Đ����Ԃ��擾����
				this->fNormalAttackEndLoopTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex);

				// �U���I�����[�v���[�V�����t���O��L����
				this->bNormalAttackEndMotionFlg = false;

				// �U���I�����[�v���[�V�����t���O��L����
				this->bNormalAttackEndLoopMotionFlg = true;
			}
		}

		// �U���I�����[�v���[�V�����t���O���L�����m�F
		if (this->bNormalAttackEndLoopMotionFlg)
		{
			// �U���I�����[�v���[�V�����t���O���L���̏ꍇ
			// �U���I�����[�v�̃A�j���[�V�����Đ����Ԃ����Z����
			this->fNormalAttackEndLoopPlayTime += 0.5f;

			// �U���I�����[�v�̃A�j���[�V�����Đ����Ԃ��Z�b�g����
			MV1SetAttachAnimTime(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex, this->fNormalAttackEndPlayTime);

			// �U���I�����[�v�̃A�j���[�V�����Đ����Ԃ����Đ����ԂɒB�������m�F
			if (this->fNormalAttackEndPlayTime >= this->fNormalAttackEndLoopTotalTime)
			{
				// �U���I�����[�v�̃A�j���[�V�����Đ����Ԃ����Đ����ԂɒB�����ꍇ
				// �A�^�b�`�����A�j���[�V�������f�^�b�`����
				this->fNormalAttackEndLoopPlayTime = 0.0f;

				// �U���I�����[�v���[�V�����t���O�𖳌���
				this->bNormalAttackEndLoopMotionFlg = false;

				// �A�j���[�V�����̃��[�v���I��������A�ŏ��̍U�����[�V�����t���O���ēx�L����
				this->bNormalAttackMotionFlg = true;
			}
		}
	}
}

// �X�V
void Enemy_Normal::Update()
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

	// �d�͏���
	Enemy_Gravity();

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

				/* �U���q�b�g��SE���Đ� */
				gpDataList_Sound->SE_PlaySound(SE_PLAYER_SLASH_HIT);

				// �G�l�~�[��e���̏��������s
				DefeatAttack();

				// �v���C���[�U���q�b�g�G�t�F�N�g�����t���O��L����
				this->bHitEffectGenerated = TRUE;
			}
		}

		//�G�l�~�[�̌����Œ�t���O�𖳌���
		this->bDirectionFlg = false;


		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackNowAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackEndAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iNormalAttackEndLoopAttachIndex);

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
		gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);
		}
		return;
	}
}
