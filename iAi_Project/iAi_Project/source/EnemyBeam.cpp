/* 2025.01.29 �ΐ�q�� �t�@�C���쐬 */
#include "EnemyBeam.h"

// �R���X�g���N�^
BeamEnemy::BeamEnemy() : EnemyBasic()
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Kari_0127");

		/* �G�l�~�[�������f���n���h���擾 */
		this->iModelFootHandle = ModelListHandle->iGetModel("Enemy_Kari_0127");

		// �G�l�~�[�������f���̃t���[���O�Ԃ��\��
		MV1SetFrameVisible(iModelFootHandle, 0, FALSE);

		// �G�l�~�[�������f���̃t���[���Q�Ԃ��\��
		MV1SetFrameVisible(iModelFootHandle, 2, FALSE);
	}

	this->pPlayer = ObjectList->GetCharacterPlayer();
	this->pEffect = nullptr;
	this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;	// ���˃J�E���g

	this->iDurationCount = ENEMY_NORMAL_DURATION_COUNT;	// �r�[���̎����J�E���g

	this->iChargeCount = ENEMY_BEAM_CHARGE_COUNT;		// �r�[���̃`���[�W�J�E���g
}

// �f�X�g���N�^
BeamEnemy::~BeamEnemy()
{
	/* �R�Â��Ă���G�t�F�N�g�̍폜�t���O��L���� */
}

// ������
void BeamEnemy::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

// �G���ړ�������
void BeamEnemy::MoveEnemy()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�U���\���G�t�F�N�g�̍��W��ݒ�
	VECTOR vecWarning = VGet(vecPosition.x, vecPosition.y + vecPosition.y / 2, vecPosition.z);

	//�v���C���[��Z���W���G�l�~�[��Z���W���傫�����m�F
	if (vecPosition.z > playerPos.z)
	{
		//�v���C���[��Z���W���G�l�~�[��Z���W���傫���ꍇ
		//�G�l�~�[�̏c������ݒ�
		VRot.x = atan2f(this->vecPosition.y - playerPos.y, this->vecPosition.z - playerPos.z) * -1;
	}
	//�v���C���[��Z���W���G�l�~�[��Z���W��菬�������m�F
	if (vecPosition.z < playerPos.z)
	{
		//�v���C���[��Z���W���G�l�~�[��Z���W��菬�����ꍇ
		//�G�l�~�[�̏c������ݒ�
		VRot.x = atan2f(playerPos.y - this->vecPosition.y, playerPos.z - this->vecPosition.z);
	}

	//�G�l�~�[�̌�����ݒ�
	this->vecRotation = VRot;

	//�G�l�~�[�̏c�������擾
	MV1SetRotationXYZ(iModelHandle, VRot);

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	iFiringCount--;

	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ

		//�U���J�E���g�����˃J�E���g���傫�����m�F
		if (iFiringCount <= ENEMY_NORMAL_BULLET_GUIDANCE_INTERVAL)
		{
			// �U���J�E���g�����˃J�E���g���傫���ꍇ
			/* �U���\���G�t�F�N�g�ǉ� */
			{
				/* �U���\���G�t�F�N�g�𐶐� */
				this->pEffectWarning = new EffectManualDelete();

				/* �G�t�F�N�g�̓ǂݍ��� */
				this->pEffectWarning->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_bullet_warning/FX_e_bullet_warning")));

				/* �G�t�F�N�g�̍��W�ݒ� */
				this->pEffectWarning->SetPosition(this->vecWarning);

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
		//���˃J�E���g��0�ȉ����m�F
		if (iFiringCount <= 0)
		{

			// ���f���̃t���[���O�Ԃ�\��
			MV1SetFrameVisible(iModelHandle, 0, TRUE);

			// ���f���̃t���[���Q�Ԃ�\��
			MV1SetFrameVisible(iModelHandle, 2, TRUE);
			// ���˃J�E���g��0�ȉ��̏ꍇ
			// �m�[�}���e�𔭎˂���
			Player_Range_Beam_Shot();

			// ���˃J�E���g��������
			this->iFiringCount = ENEMY_NORMAL_BULLET_INTERVAL;
		}
	}


}

// �r�[���̔���
void BeamEnemy::Player_Range_Beam_Shot()
{
	// �v���C���[�̍��W���擾
	VECTOR playerPos = pPlayer->vecGetPosition();

	// �r�[���𐶐�
	this->pBulletRangeBeam = new BulletEnemyRangeBeam;

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

// �X�V
void BeamEnemy::Update()
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

	if (this->iGetNowHP() <= 0)
	{
		// �폜�t���O��L���ɂ���
		this->SetDeleteFlg(true);
	}

	// �G�l�~�[���ړ�������
	MoveEnemy();

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
