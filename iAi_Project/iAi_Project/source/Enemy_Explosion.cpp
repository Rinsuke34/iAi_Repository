/* 2025.01.28 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Explosion.h"

// �R���X�g���N�^
ExplosionEnemy::ExplosionEnemy() : EnemyBasic()
{


	this->iXdistance = ENEMY_X_DISTANCE;		// X���̋���
	this->iZdistance = ENEMY_Z_DISTANCE;		// Z���̋���
	this->fSpeed = ENEMY_SPEED;				// �ړ����x
	this->iDetonationRange = ENEMY_DETONATION_RANGE;	//�N���͈͓�
	this->fGravity = ENEMY_GRAVITY_SREED;				// �d��

	// HP��ݒ�
	this->iMaxHp = 1;
	this->iNowHp = 1;
	this->iObjectType = OBJECT_TYPE_ENEMY;	// �I�u�W�F�N�g�̎��

	/* �f�[�^���X�g�擾 */
	{
		/* "�I�u�W�F�N�g�Ǘ�"���擾 */
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		/* "�v���C���[���"���擾 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* ���f���擾 */
	{
		/* "3D���f���Ǘ�"�f�[�^���X�g���擾 */
		// ����x�����g�p���Ȃ����߁A�擾�����f�[�^���X�g�̃n���h���͕ێ����Ȃ�
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));

		/* ���f���n���h���擾 */
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy");
	}

	this->pEffect = nullptr;
    this->bEffectGenerated = false;
}

// �f�X�g���N�^
ExplosionEnemy::~ExplosionEnemy()
{

}

// ������
void ExplosionEnemy::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

void ExplosionEnemy::MoveEnemy()
{
	// �v���C���[�̍��W���擾
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	// �d�͏���
	this->vecMove.y -= ENEMY_GRAVITY_SREED;
	this->vecPosition.y += this->vecMove.y;

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌�����ݒ�
	this->vecRotation = VRot;

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
        // �T�m�͈͓��ɂ���G�l�~�[�̂ݏ������s��
        if (!bEffectGenerated)
		{
			// �G�l�~�[���v���C���[�ɋ߂Â���
			VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

			// �v���C���[�Ɍ����������Ƒ��x���擾
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, ENEMY_SPEED));

			// �v���C���[���G�l�~�[�̋N���͈͓��ɓ��������ǂ������m�F
			if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
			{
				// �v���C���[���G�l�~�[�̋N���͈͓��ɓ������ꍇ
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

                // �G�t�F�N�g�����t���O��ݒ�
                bEffectGenerated = true;
			}
		}
        else
		{
            // �G�t�F�N�g���Đ������ǂ����m�F
            if (IsEffekseer3DEffectPlaying(this->pEffectDetonation->iGetEffectHandle()))
			{
                // �G�t�F�N�g���Đ��I�����Ă���ꍇ
				//�G�l�~�[�̍폜�t���O��L���ɂ���
				this->bDeleteFlg = true;

				//�v���C���[�𐁂���΂�
				this->PlayerStatusList->SetPlayerNowFallSpeed(-30.0f);
			}
		}
	}
}

void ExplosionEnemy::Enemy_Gravity()
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

// �X�V
void ExplosionEnemy::Update()
{
    // �o���b�g���X�g���擾
	auto& BulletList = ObjectList->GetBulletList();

    // �v���C���[�U���ƐڐG���邩�m�F
	for (auto* bullet : BulletList)
	{
        // �I�u�W�F�N�g�^�C�v��"�e(�v���C���[)"�ł��邩�m�F
		if (bullet->iGetObjectType() == OBJECT_TYPE_BULLET_PLAYER)
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

	if (this->iGetNowHP() <= 0)
	{
		// �폜�t���O��L���ɂ���
		this->bDeleteFlg = true;
		/* �����\���G�t�F�N�g����x�ł��������������m�F */
		if (this->pEffectDetonation != nullptr)
		{
			// ��x�ł����������ꍇ
			//�����\���G�t�F�N�g�̍폜�t���O��L����
			this->pEffectDetonation->SetDeleteFlg(true);
		}
	}

	// �G�l�~�[���ړ�������
	MoveEnemy();

	Enemy_Gravity();

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}