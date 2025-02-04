/* 2025.01.28 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Explosion.h"

// �R���X�g���N�^
ExplosionEnemy::ExplosionEnemy() : EnemyBasic()
{


	this->iXdistance = ENEMY_X_DISTANCE;		// X���̋���
	this->iZdistance = ENEMY_Z_DISTANCE;		// Z���̋���
	this->fSpeed = ENEMY_SPEED;				// �ړ����x
	this->iDetonationRange = ENEMY_DETONATION_RANGE;	//�N���͈͓�
	this->iLastTime = ENEMY_DETONATION_TIME;	//�N���^�C�}�[

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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy_Kari_0127");
	}

	this->pEffect = nullptr;
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


	// ���݂̎��Ԃ��擾
	int nowTime = GetNowCount();

	//�G�l�~�[�̌���������������
	VECTOR VRot = VGet(0, 0, 0);

	//�v���C���[�̕����������悤�ɃG�l�~�[�̌������`
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z);

	//�G�l�~�[�̌�����ݒ�
	this->vecRotation = VRot;

	//�v���C���[�ƃG�l�~�[��XZ���̋������擾
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);

	//�N���J�E���g��������
	static bool iActioncount = false;

	//�v���C���[���T�m�͈͓��ɂ��邩�m�F
	if (distanceToPlayerX < ENEMY_X_DISTANCE && distanceToPlayerZ < ENEMY_Z_DISTANCE)  // x����z���̋�����1000�����̏ꍇ
	{
		// �v���C���[���T�m�͈͓��ɂ���ꍇ
		// �N���J�E���g���i��ł��邩�m�F
		if (iActioncount == false)
		{
			// �N���J�E���g���i��ł���ꍇ
			// �G�l�~�[���v���C���[�ɋ߂Â���
			VECTOR direction = VNorm(VSub(playerPos, this->vecPosition));

			// �v���C���[�Ɍ����������Ƒ��x���擾
			this->vecPosition = VAdd(this->vecPosition, VScale(direction, ENEMY_SPEED));

			// �v���C���[���G�l�~�[�̋N���͈͓��ɓ��������ǂ������m�F
			if (VSize(VSub(playerPos, this->vecPosition)) < ENEMY_DETONATION_RANGE)
			{
				// �v���C���[���G�l�~�[�̋N���͈͓��ɓ������ꍇ
				//�N���J�E���g���J�n
				iActioncount = true;
			}
		}
		//�v���C���[���T�m�͈͓�����N���J�E���g���i��ł���ꍇ�ł��邩�m�F
		else if (iActioncount == true)
		{
			//�v���C���[���T�m�͈͓�����N���J�E���g���i��ł���ꍇ
			//�^�C�}�[���擾
			static int startTime = nowTime;

			// �^�C�}�[��3�b�ȏ�o�߂��Ă��邩�ǂ������m�F
			if (nowTime - startTime > ENEMY_DETONATION_TIME)
			{
				//�^�C�}�[��3�b�ȏ�o�߂��Ă���ꍇ
				//�G�l�~�[�̍폜�t���O��L���ɂ���
				this->bDeleteFlg = true;

				//�^�C�}�[�����Z�b�g����
				startTime = nowTime;

			}
		}
	}
}

// �X�V
void ExplosionEnemy::Update()
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
		this->bDeleteFlg = true;
	}

	// �G�l�~�[���ړ�������
	MoveEnemy();

	// �R���W�����Z�b�g
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
