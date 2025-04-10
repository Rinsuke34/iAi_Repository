/* 2025.03.13 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Normal_Air.h"

// �R���X�g���N�^
Enemy_Normal_Air::Enemy_Normal_Air() : Enemy_Basic()
{

	/* �I�u�W�F�N�g�̃n���h�� */
	this->pBulletRangeNormal = nullptr;	// �ߐڍU��(��)�̒e
	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;

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

	//�G�l�~�[�x���G�t�F�N�g���������ꂽ��
	this->pEffectWarning = nullptr;	

	// �q�b�g�G�t�F�N�g�����t���O
	this->bHitEffectGenerated = false;

	// �x���G�t�F�N�g�t���O
	this->bWarningEffectFlg = true;

	//�V���b�g�t���O
	this->bShotFlg = false;

	/*���[�V�����֘A*/

	// �G�l�~�[���f���ɋ󒆂̃A�j���[�V�������A�^�b�`����
	this->iNormalAirAttachIndex = MV1AttachAnim(this->iModelHandle, 5, -1, FALSE);

	// �A�^�b�`�����󒆃A�j���[�V�����̑��Đ����Ԃ��擾����
	this->fNormalAirTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iNormalAirAttachIndex);

	//�G�l�~�[�̌����Œ�t���O��������
	this->bDirectionFlg = true;
}

// �f�X�g���N�^
Enemy_Normal_Air::~Enemy_Normal_Air()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void Enemy_Normal_Air::Initialization()
{
	/* �R���W�����Z�b�g */

	//�G�l�~�[�̃J�v�Z���R���W�����̔��a
	this->stCollisionCapsule.fCapsuleRadius = 100;

	//�G�l�~�[�̃J�v�Z���R���W�����̏�̍��W
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));

	//�G�l�~�[�̃J�v�Z���R���W�����̉��̍��W
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();

	// ��������t���[���̏���
	UpdataLightFrame();
}

// �G���ړ�������
void Enemy_Normal_Air::MoveEnemy()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌����Œ�t���O���L�����m�F
	if (this->bDirectionFlg == true)
	{
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

		//���˃J�E���g�����炷
		iFiringCount--;

		// �v���C���[�����G�͈͓��ɂ��邩�m�F
		if (distanceToPlayerSquared < detectionRadiusSquared)
		{
			// �v���C���[���T�m�͈͓��ɂ���ꍇ
			//�U���J�E���g�����˃J�E���g���傫�����m�F
			if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
			{
				// �U���J�E���g�����˃J�E���g���傫���ꍇ
				// �x���G�t�F�N�g�t���O���L�����m�F
				if (this->bWarningEffectFlg == true)
				{
					// �x���G�t�F�N�g�t���O���L���̏ꍇ
					//�U���\���G�t�F�N�g�t���O�𖳌���
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
					}
				}
			}
			//���˃J�E���g��0�ȉ����m�F
			if (iFiringCount <= 0)
			{
				// ���˃J�E���g��0�ȉ��̏ꍇ
				// �m�[�}���e�𔭎˂���
				Player_Range_Normal_Shot();

				// ���˃J�E���g��������
				this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;

				// �V���b�g�t���O�𖳌���
				this->bShotFlg = false;
			}
		}
	}
}

// �m�[�}���e�̔���
void Enemy_Normal_Air::Player_Range_Normal_Shot()
{
	//�G�l�~�[�����j����Ă��Ȃ����m�F
	if (this->iNowHp > 0)
	{
		//�G�l�~�[�����j����Ă��Ȃ��ꍇ
		// �v���C���[�̍��W���擾
		VECTOR playerPos = pPlayer->vecGetPosition();

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
	}
}

// �X�V
void Enemy_Normal_Air::Update()
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
	// �G�l�~�[���ړ�������
	MoveEnemy();

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ
		/* ���S�t���O��L���� */
		this->bDeadFlg = true;

		//�q�b�g�G�t�F�N�g�����I���m�F�t���O���������m�F
		if (this->bHitEffectGenerated == FALSE)
		{
			//�q�b�g�G�t�F�N�g�����I���m�F�t���O�������̏ꍇ
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

				//��e���̏���
				DefeatAttack();

				//�q�b�g�G�t�F�N�g�����I���m�F�t���O��L����
				this->bHitEffectGenerated = TRUE;
			}
		}
		this->bDirectionFlg = false;
		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iNormalAirAttachIndex);

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
