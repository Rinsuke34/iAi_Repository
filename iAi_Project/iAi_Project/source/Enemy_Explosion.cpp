/* 2025.01.28 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Explosion.h"

// �R���X�g���N�^
Enemy_Explosion::Enemy_Explosion() : Enemy_Basic()
{
	//������

	//X���̋���
	this->iXdistance = ENEMY_X_DISTANCE;

	//Z���̋���
	this->iZdistance = ENEMY_Z_DISTANCE;

	// �ړ����x
	this->fSpeed = ENEMY_CHASE_SPEED;

	//�N���͈͓�
	this->iDetonationRange = ENEMY_DETONATION_RANGE;

	//�d��
	this->fGravity = ENEMY_GRAVITY_SREED;

	//�����͈͓�
	this->iBlastRange		= ENEMY_EXPLOSION_RANGE;

	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;

	// �I�u�W�F�N�g�̎�ނ�TypeEnemy�ɐݒ�
	this->iObjectType = OBJECT_TYPE_ENEMY;

	// �o������u���b�h�ʂ�ݒ�
	this->iBloodAmount = 10;


	// �X�g�b�v�J�E���g��������
	this->iStopCount = 0;

	// �G�t�F�N�g��nullptr�ɐݒ�
	this->pEffect = nullptr;

	// �N���\���G�t�F�N�g�����t���O
	this->bEffectGenerated = false;

	// �����t���O
	this->bFallFlg = true;

	// �X�g�b�v�t���O
	this->bStopFlg = true;

	//�J�E���g�t���O
	this->bCountFlg = false;

	// �����t���O
	this->bBlastFlg = false;

	//�q�b�g�G�t�F�N�g�����t���O
	this->bHitEffectGenerated = false;	

	//�����Œ�t���O
	this->bDirectionFlg = true;

	//�ǐՃt���O
	this->bChaseFlg = true;

	//���W�ۑ��t���O
	this->bSavePositionFlg = true;

	//���^�[���J�E���g
	this->iReturnCount = ENEMY_RETURN_TIME;

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

		/* "�G�t�F�N�g���\�[�X�Ǘ�"���擾 */
		this->EffectList = dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"));

		/* "�X�e�[�W��ԊǗ�"���擾 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));;

	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Explosion/Enemy_Explosion");
	}

	


	//�G�l�~�[�̏������W��ۑ�
	this->vecStartPosition = this->vecPosition;
}

// �f�X�g���N�^
Enemy_Explosion::~Enemy_Explosion()
{

}

// ������
void Enemy_Explosion::Initialization()
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

	//��������t���[���̏���
	UpdataLightFrame();
}

// �G�̈ړ�
void Enemy_Explosion::MoveEnemy()
{
	// �G�l�~�[�̕ǂ̓����蔻��p�̃J�v�Z���R���W������ݒ�
	// �J�v�Z���̔��a
	this->stHorizontalCollision.fCapsuleRadius = 50;

	// �J�v�Z���̏�̍��W
	this->stHorizontalCollision.vecCapsuleTop = VAdd(VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z), VGet(0, 50, 0));

	// �J�v�Z���̉��̍��W
	this->stHorizontalCollision.vecCapsuleBottom = VGet(vecPosition.x, vecPosition.y + PLAYER_HEIGHT / 2, vecPosition.z);

	//�G�l�~�[�̍��W��ۑ��t���O���L�����m�F
	if (this->bSavePositionFlg == true)
	{
		//���W�ۑ��t���O���L���ȏꍇ
		//�G�l�~�[�̏������W��ۑ�
		this->vecStartPosition = this->vecPosition;

		//���W�ۑ��t���O�𖳌��ɂ���
		this->bSavePositionFlg = false;
	}

	// �v���C���[�̍��W���擾
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//�G�l�~�[���������Ă��邩�m�F
	if (this->bFallFlg == false)
	{
		//�G�l�~�[���������Ă���ꍇ
		//�������x��40�ɐݒ�
		fSpeed = 40;

		//�G�l�~�[���v���C���[�Ɍ������Ĉړ�����
		this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(this->vecPosition, playerPos)), fSpeed));

		//�������x��������
		fSpeed = 0;

		//�J�E���g�t���O��L���ɂ���
		this->bCountFlg = true;
	}

	//�J�E���g�t���O���L�����m�F
	if (this->bCountFlg = true)
	{
		//�J�E���g�t���O���L���ȏꍇ
		//�X�g�b�v�J�E���g�����Z
		iStopCount++;
	}

	//�X�g�b�v�J�E���g��60�𒴂������m�F
	if (iStopCount > 60)
	{
		//�X�g�b�v�J�E���g��60�𒴂����ꍇ
		//�X�g�b�v�t���O��L���ɂ���
		this->bStopFlg = true;

		//�X�g�b�v�J�E���g��������
		iStopCount = 0;

		//�ړ����x��ݒ�
		this->fSpeed = ENEMY_CHASE_SPEED;
	}

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	// �d�͏���
	this->vecMove.y -= ENEMY_GRAVITY_SREED;
	this->vecPosition.y += this->vecMove.y;

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌����Œ�t���O���L�����m�F
	if (this->bDirectionFlg == true)
	{
		//�G�l�~�[�̌����Œ�t���O���L���ȏꍇ
		//�G�l�~�[�̌�����ݒ�
		this->vecRotation = VRot;
		//�G�l�~�[�̌�����ݒ�
		MV1SetRotationXYZ(iModelHandle, VRot);
	}

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerY = fabs(this->vecPosition.y - playerPos.y);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//�`�F�C�X�t���O���L�����m�F
	if (bChaseFlg == TRUE)
	{
		//�`�F�C�X�t���O���L���ȏꍇ
		// �v���C���[�ƃG�l�~�[�̋����̕������v�Z
		float distanceToPlayerSquared = (this->vecPosition.x - playerPos.x) * (this->vecPosition.x - playerPos.x) +
			(this->vecPosition.y - playerPos.y) * (this->vecPosition.y - playerPos.y) +
			(this->vecPosition.z - playerPos.z) * (this->vecPosition.z - playerPos.z);

		// ���G�͈͂̔��a�̕���
		float detectionRadiusSquared = ENEMY_Y_DISTANCE * ENEMY_Y_DISTANCE;

		// �v���C���[�����G�͈͓��ɂ��邩�m�F
		if (distanceToPlayerSquared < detectionRadiusSquared)
		{
			// �v���C���[���T�m�͈͓��ɂ���ꍇ
			// �T�m�͈͓��ɂ���G�l�~�[�̂ݏ������s��
			// �G�l�~�[���N������Ă��Ȃ����m�F
			if (bEffectGenerated == false)
			{
				//�G�l�~�[���N������Ă��Ȃ��ꍇ
				//�ҋ@���[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);

				//���胂�[�V�������A�^�b�`����
				this->iRunAttachIndex = MV1AttachAnim(this->iModelHandle, 7, -1, FALSE);

				//���胂�[�V�����̑��Đ����Ԃ��擾����
				this->fRunTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iRunAttachIndex);

				//�Đ����x�����Z
				this->fRunPlayTime += 1.0f;

				//�Đ����Ԃ��Z�b�g����
				MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

				//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
				if (this->fRunPlayTime >= this->fRunTotalTime)
				{
					//�A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
					//�Đ����Ԃ�����������
					this->fRunPlayTime = 0.0f;
				}


				// �G�l�~�[���v���C���[�ɋ߂Â���
				VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

				// �v���C���[�Ɍ����������Ƒ��x���擾
				this->vecPosition = VAdd(this->vecPosition, VScale(direction, fSpeed));

				// �v���C���[���G�l�~�[�̋N���͈͓��ɓ��������ǂ������m�F
				if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
				{
					// �v���C���[���G�l�~�[�̋N���͈͓��ɓ������ꍇ
					//�����t���O��L���ɂ���
					this->bBlastFlg = true;

				}
			}
		}

		//�N���\���G�t�F�N�g���������t���O���L�����m�F
		if (bEffectGenerated == false)
		{
			//�N���\���G�t�F�N�g���������t���O���L���ȏꍇ
			//�����t���O���L�����m�F
			if (this->bBlastFlg == true)
			{
				//�����t���O���L���ȏꍇ
				//���胂�[�V�������f�^�b�`����
				MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);

				//�������[�V�������A�^�b�`����
				this->iExplosionAttachIndex = MV1AttachAnim(this->iModelHandle, 5, -1, FALSE);

				// �N���\���G�t�F�N�g�𐶐�
				this->pEffectDetonation = new EffectManualDelete();

				// �G�t�F�N�g�̓ǂݍ���
				this->pEffectDetonation->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_suicide_light/FX_e_suicide_light")));

				// �G�t�F�N�g�̍��W�ݒ�
				this->pEffectDetonation->SetPosition(this->vecPosition);

				// �G�t�F�N�g�̉�]�ʐݒ�
				this->pEffectDetonation->SetRotation(this->vecRotation);

				// �G�t�F�N�g�̏�����
				this->pEffectDetonation->Initialization();

				// �G�t�F�N�g�����X�g�ɓo�^
				{
					// "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾
					DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
					// �G�t�F�N�g�����X�g�ɓo�^
					ObjectListHandle->SetEffect(pEffectDetonation);
				}

				//�N��SE�Đ�
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_WARNING_EXPLOSION, this->vecPosition, SE_3D_SOUND_RADIUS);

				// �N���\���G�t�F�N�g���������t���O��L��������
				bEffectGenerated = true;
			}
		}
		else
		{
			// �N���\���G�t�F�N�g���Đ������ǂ����m�F
			if (IsEffekseer3DEffectPlaying(this->pEffectDetonation->iGetEffectHandle()))
			{
				// �G�t�F�N�g���Đ��I�����Ă���ꍇ
				/* �f�[�^���X�g�擾 */
				DataList_PlayerStatus* PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

				/* �����G�t�F�N�g���� */
				{
					/* ���Ԍo�߂ō폜�����G�t�F�N�g��ǉ� */
					EffectSelfDelete* AddEffect = new EffectSelfDelete();

					/* �G�t�F�N�g�ǂݍ��� */
					AddEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die/FX_e_die")));

					/* �G�t�F�N�g�̍��W�ݒ� */
					AddEffect->SetPosition(this->vecPosition);

					/* �G�t�F�N�g�̉�]�ʐݒ� */
					AddEffect->SetRotation(this->vecRotation);

					/* �G�t�F�N�g�̍폜�����܂ł̎��Ԃ�ݒ� */
					AddEffect->SetDeleteCount(75);

					/* �G�t�F�N�g�̏����� */
					AddEffect->Initialization();

					/* ���X�g�ɓo�^ */
					{
						/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
						DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));

						/* �G�t�F�N�g�����X�g�ɓo�^ */
						ObjectListHandle->SetEffect(AddEffect);
					}
				}

				/* �G�l�~�[�̍폜�t���O��L���ɂ��� */
				this->bDeleteFlg = true;

				//����SE�Đ�
				gpDataList_Sound->SE_PlaySound_3D(SE_ENEMY_DAMAGE, this->vecPosition, SE_3D_SOUND_RADIUS);

				//�v���C���[�������͈͓��ɂ��邩�ǂ������m�F
				if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_EXPLOSION_RANGE)
				{
					//�v���C���[�������͈͓��ɂ���ꍇ
				//�v���C���[�𐁂���΂�
					this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);
					// �������Ă���ꍇ
					/* �v���C���[��HP������ */
					this->PlayerStatusList->SetPlayerNowHp(this->PlayerStatusList->iGetPlayerNowHp() - 1);

					/* ��_���[�W�J�E���g�����Z���� */
					this->PlayerStatusList->SetPlayerDamageCount(this->PlayerStatusList->iGetPlayerDamageCount() + 1);

					/* �v���C���[�̖��G���Ԃ�ݒ� */
					this->PlayerStatusList->SetPlayerNowInvincibleTime(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());


					/* "��_���[�W"��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE);

					/* "��_���[�W�r���r��"��SE���Đ� */
					gpDataList_Sound->SE_PlaySound(SE_PLAYER_DAMAGE_ELEC);

					/* ��_���[�W�{�C�X���Đ� */
					gpDataList_Sound->VOICE_PlaySound(VOICE_PLAYER_DAMAGE);

					/* ��_���[�W�̃G�t�F�N�g�𐶐� */
					{
						/* �_���[�W�������G�t�F�N�g */
						{
							/* ��_���[�W�̏u�Ԃɔ�������G�t�F�N�g��ǉ� */
							EffectSelfDelete* pDamageEffect = new EffectSelfDelete();

							/* ���W��ݒ� */
							pDamageEffect->SetPosition(VAdd(this->vecPosition, VGet(0, PLAYER_HEIGHT / 2, 0)));

							/* �G�t�F�N�g���擾 */
							pDamageEffect->SetEffectHandle(this->EffectList->iGetEffect("FX_damaged/FX_damaged"));

							/* �g�嗦��ݒ� */
							pDamageEffect->SetScale(VGet(1.f, 1.f, 1.f));

							/* �폜�J�E���g��ݒ� */
							// ������1�b��
							pDamageEffect->SetDeleteCount(60);

							/* �G�t�F�N�g���������� */
							pDamageEffect->Initialization();

							/* �I�u�W�F�N�g���X�g�ɓo�^ */
							this->ObjectList->SetEffect(pDamageEffect);
						}

						/* ���d�G�t�F�N�g */
						{
							/* ���d�G�t�F�N�g�𐶐� */
							EffectSelfDelete_PlayerFollow* pShockEffect = new EffectSelfDelete_PlayerFollow(false);

							/* ���d�G�t�F�N�g�̓ǂݍ��� */
							pShockEffect->SetEffectHandle((this->EffectList->iGetEffect("FX_eshock/FX_eshock")));

							/* ���d�G�t�F�N�g�̏����� */
							pShockEffect->Initialization();

							/* ���d�G�t�F�N�g�̎��Ԃ�ݒ� */
							pShockEffect->SetDeleteCount(this->PlayerStatusList->iGetPlayerMaxInvincibleTime());

							/* ���d�G�t�F�N�g�����X�g�ɓo�^ */
							this->ObjectList->SetEffect(pShockEffect);
						}

						/* ��ʃG�t�F�N�g(��_���[�W)�쐬 */
						this->StageStatusList->SetScreenEffect(new ScreenEffect_Damage());

					}
				}
			}
		}
	}

	//�`�F�C�X�t���O���������m�F
	if (this->bChaseFlg == false)
	{
		//�`�F�C�X�t���O�������ȏꍇ
		//���^�[���J�E���g�����Z
		iReturnCount--;

		//���^�[���J�E���g��0�ȉ����m�F
		if (this->iReturnCount <= 0)
		{
			//���^�[���J�E���g��0�ȉ��̏ꍇ
			//�G�l�~�[�̍��W���������W�ɖ߂�
			// �v���C���[�Ɍ����������Ƒ��x���擾
			VECTOR direction = VNorm(VSub(this->vecStartPosition, this->vecPosition));

			// �v���C���[�Ɍ����������Ƒ��x��ݒ�
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, 5));

			//�G�l�~�[�̌���������������
			VECTOR VRot = VGet(0, 0, 0);

			//�G�l�~�[�̌������������W�Ɍ�����
			VRot.y = atan2f(this->vecPosition.x - this->vecStartPosition.x, this->vecPosition.z - this->vecStartPosition.z);

			//�G�l�~�[�̌�����ݒ�
			this->vecRotation = VRot;

			//���ׂẴA�j���[�V�������f�^�b�`����
			MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

			//���胂�[�V�������A�^�b�`����
			this->iRunAttachIndex = MV1AttachAnim(this->iModelHandle, 7, -1, FALSE);

			//���胂�[�V�����̑��Đ����Ԃ��擾����
			this->fRunTotalTime = MV1GetAttachAnimTotalTime(this->iModelHandle, this->iRunAttachIndex);

			//�Đ����x�����Z
			this->fRunPlayTime += 1.0f;

			//�Đ����Ԃ��Z�b�g����
			MV1SetAttachAnimTime(this->iModelHandle, this->iRunAttachIndex, this->fRunPlayTime);

			//�Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�������m�F
			if (this->fRunPlayTime >= this->fRunTotalTime)
			{
				//�A�j���[�V�����̍Đ����Ԃ����Đ����ԂɒB�����ꍇ
				//�Đ����Ԃ�����������
				this->fRunPlayTime = 0.0f;
			}
		}
	}
	//�G�l�~�[�̍��W���������W�ɖ߂������ǂ������m�F
	if (VSize(VSub(this->vecStartPosition, this->vecPosition)) < 10)
	{
		//�G�l�~�[�̍��W���������W�ɖ߂����ꍇ
		//�`�F�C�X�t���O��L���ɂ���
		this->bChaseFlg = true;

		//���ׂẴA�j���[�V�������f�^�b�`����
		MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

		//�ҋ@���[�V�������A�^�b�`����
		this->iWaitAttachIndex = MV1AttachAnim(this->iModelHandle, 6, -1, FALSE);

		//�ҋ@���[�V�����̑��Đ����Ԃ��擾����
		this->iReturnCount = ENEMY_RETURN_TIME;
	}
}


// �G�l�~�[�̏d�͏���
void Enemy_Explosion::Enemy_Gravity()
{
	// �ړ���̍��W���擾(��������)
	VECTOR vecNextPosition;
	vecNextPosition.x = this->vecPosition.x;
	vecNextPosition.y = this->vecPosition.y + this->vecMove.y;
	vecNextPosition.z = this->vecPosition.z;

	// �G�l�~�[�̏㕔���̓����蔻�肩�牺�����֌������������쐬
	this->stVerticalCollision.vecLineStart = this->vecPosition;
	this->stVerticalCollision.vecLineStart.y += PLAYER_HEIGHT;
	this->stVerticalCollision.vecLineEnd = stVerticalCollision.vecLineStart;
	this->stVerticalCollision.vecLineEnd.y -= 300;

	// ������擾
	auto& PlatformList = ObjectList->GetPlatformList();

	// �ڐG�t���O
	bool bHitFlg = false;

	// ����ƐڐG���邩�m�F
	for (auto* platform : PlatformList)
	{
		// ����Ƃ̐ڐG����
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// �ڐG���Ă��邩�m�F
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ
			// �ړ���̍��W��ڐG���W�ɐݒ�
			this->vecPosition.y = stHitPolyDim.HitPosition.y;

			// �d�͂����Z�b�g
			this->vecMove.y = 0;

			// �����t���O��L���ɂ���
			this->bFallFlg = true;

			// �X�g�b�v�t���O��L���ɂ���
			this->bStopFlg = true;

			// �ڐG�t���O��L���ɂ���
			bHitFlg = true;

			break;
		}

		//�ڐG�t���O���������m�F
		if (!bHitFlg)
		{
			//�ڐG�t���O�������̏ꍇ

			//�d�͂�������
			this->fGravity = 0;

			//�G�l�~�[�̂����W���ړ����Ȃ��悤�ݒ�
			this->vecMove.y = 0;

			//�����t���O�𖳌��ɂ���
			this->bFallFlg = false;

			//�X�g�b�v�t���O�𖳌��ɂ���
			this->bStopFlg = false;
		}
	}
}

// �G�l�~�[�̐�������
void Enemy_Explosion::Movement_Horizontal()
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
		auto& PlatformList = ObjectList->GetPlatformList();

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
					// �ڐG���Ă���ꍇ
					//�`�F�C�X�t���O�𖳌��ɂ���
					this->bChaseFlg = false;

					break;
				}
			}
		}
	}

	/* �v���C���[�̍��W���ړ������� */
	this->vecPosition = vecNextPosition;
}

// �X�V
void Enemy_Explosion::Update()
{
	// �o���b�g���X�g���擾
	auto& BulletList = ObjectList->GetBulletList();

	// �v���C���[�U���ƐڐG���邩�m�F
	for (auto* bullet : BulletList)
	{
		/* �I�u�W�F�N�g�^�C�v��"�e(�v���C���[)"���邢��"�ߐڍU��(�v���C���[)"�ł��邩�m�F */
		if ((bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER) || (bullet->iGetObjectType() == OBJECT_TYPE_MELEE_PLAYER))
		{
			// �e(�v���C���[)�̏ꍇ
			// �e�Ƃ̐ڐG����
			if (bullet->HitCheck(this->stCollisionCapsule) == true)
			{
				// �ڐG���Ă���ꍇ
				// �_���[�W����
				this->iNowHp -= 1;
			}
		}
	}

	// HP��0�ȉ��ł��邩�m�F
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ
		/* ���S�t���O��L���� */
		this->bDeadFlg = true;

		/* �����\���G�t�F�N�g����x�ł��������������m�F */
		if (this->pEffectDetonation != nullptr)
		{
			// ��x�ł����������ꍇ
			//�����\���G�t�F�N�g�̍폜�t���O��L����
			this->pEffectDetonation->SetDeleteFlg(true);

			//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
			MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
			MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

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
			}
		}
	}

	/* HP��0�ȉ��ł��邩�m�F */
	if (this->iNowHp <= 0)
	{
		// HP��0�ȉ��ł���ꍇ
		//�q�b�g�G�t�F�N�g�����t���O���������m�F
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

				//��e���̏���
				DefeatAttack();

				//�q�b�g�G�t�F�N�g���������t���O��L���ɂ���
				this->bHitEffectGenerated = TRUE;
			}
		}

		//�����Œ�t���O�𖳌��ɂ���
		this->bDirectionFlg = false;

		//���S���[�V�����ȊO�̃��[�V�������f�^�b�`
		MV1DetachAnim(this->iModelHandle, this->iWaitAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iRunAttachIndex);
		MV1DetachAnim(this->iModelHandle, this->iExplosionAttachIndex);

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

	// �G�l�~�[���ړ�������
	MoveEnemy();

	// �G�l�~�[�̏d�͏���
	Enemy_Gravity();

	// �G�l�~�[�̐�������
	Movement_Horizontal();

	//�G�l�~�[���������蔻��p�̃R���W�����`��
	CollisionDraw();

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}


//�R���W�����`��
void Enemy_Explosion::CollisionDraw()
{
	//�G�l�~�[�̐������������蔻��p�̃R���W�����`��
	DrawLine3D(this->stVerticalCollision.vecLineStart, this->stVerticalCollision.vecLineEnd, GetColor(255, 0, 0));

	DrawCapsule3D(this->stCollisionCapsule.vecCapsuleTop, this->stCollisionCapsule.vecCapsuleBottom, this->stCollisionCapsule.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

	DrawCapsule3D(this->stHorizontalCollision.vecCapsuleTop, this->stHorizontalCollision.vecCapsuleBottom, this->stHorizontalCollision.fCapsuleRadius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
}