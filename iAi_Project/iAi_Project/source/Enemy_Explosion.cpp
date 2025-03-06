/* 2025.01.28 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Explosion.h"

// �R���X�g���N�^
ExplosionEnemy::ExplosionEnemy() : EnemyBasic()
{


	this->iXdistance = ENEMY_X_DISTANCE;		// X���̋���
	this->iZdistance = ENEMY_Z_DISTANCE;		// Z���̋���
	this->fSpeed = ENEMY_CHASE_SPEED;				// �ړ����x
	this->iDetonationRange = ENEMY_DETONATION_RANGE;	//�N���͈͓�
	this->fGravity = ENEMY_GRAVITY_SREED;				// �d��
	this->iBlastRange		= ENEMY_EXPLOSION_RANGE;	// �����͈͓�

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
	this->iStopCount = 0;
	this->pEffect = nullptr;
    this->bEffectGenerated = false;
	this->bFallFlg = true;
	this->bStopFlg = true;
	this->bCountFlg = false;
	this->bBlastFlg = false;
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

	//�G�l�~�[���������Ă��邩�m�F
	if (this->bFallFlg == false)
	{
		//�G�l�~�[���������Ă���ꍇ
		//�G�l�~�[���ړ����Ă��������̋t������10f�ړ�
		fSpeed = 40;
		this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(this->vecPosition, playerPos)), fSpeed));
		fSpeed = 0;
		this->bCountFlg = true;
	}
	if (this->bCountFlg = true)
	{
		iStopCount++;
	}
	if (iStopCount > 180)
	{
		this->bStopFlg = true;
		iStopCount = 0;
		this->fSpeed = ENEMY_CHASE_SPEED;
	}
	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	// �d�͏���
	this->vecMove.y -= fGravity;
	this->vecPosition.y += this->vecMove.y;

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌�����ݒ�
	this->vecRotation = VRot;

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE && this->bStopFlg == true)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
        // �T�m�͈͓��ɂ���G�l�~�[�̂ݏ������s��
        if (!bEffectGenerated)
		{
			// �G�l�~�[���v���C���[�ɋ߂Â���
			VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

			// �v���C���[�Ɍ����������Ƒ��x���擾
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, fSpeed));

			// �v���C���[���G�l�~�[�̋N���͈͓��ɓ��������ǂ������m�F
			if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
			{
				this->bBlastFlg = true;
				
			}
		}
	}
	if (!bEffectGenerated)
	{
		if (this->bBlastFlg == true)
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

				//�v���C���[�������͈͓��ɂ��邩�ǂ������m�F
				if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_EXPLOSION_RANGE)
				{
					//�v���C���[�������͈͓��ɂ���ꍇ
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





	//// ����ƐڐG���邩�m�F
	bool bHitFlg = false;
	for (auto* platform : PlatformList)
	{
		MV1_COLL_RESULT_POLY stHitPolyDim = platform->HitCheck_Line(stVerticalCollision);

		// �ڐG���Ă��邩�m�F
		if (stHitPolyDim.HitFlag == 1)
		{
			// �ڐG���Ă���ꍇ
				this->vecPosition.y = stHitPolyDim.HitPosition.y;
				this->vecMove.y = 0; // �������x�����Z�b�g
			this->bFallFlg = true;
			this->bStopFlg = true;
			bHitFlg = true;//�ڐG�t���O��L���ɂ���
					break;
				}
		//�ڐG�t���O���������m�F
		if (!bHitFlg)
		{
			//�ڐG�t���O�������̏ꍇ
			////�ڐG�t���O�������̏ꍇ
			this->fGravity = 0;
			this->vecMove.y = 0;
			this->bFallFlg = false;
			this->bStopFlg = false;
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