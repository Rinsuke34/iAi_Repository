/* 2025.01.2�W �ΐ�q�� �t�@�C���쐬 */
#include "EnemyEscape.h"

// �R���X�g���N�^
EscapeEnemy::EscapeEnemy() : EnemyBasic()
{
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
}

// �f�X�g���N�^
EscapeEnemy::~EscapeEnemy()
{

}

// ������
void EscapeEnemy::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition,VGet(0,100,0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

void EscapeEnemy::MoveEnemy()
{
	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	// ���݂̎��Ԃ��擾
	int nowTime = GetNowCount();
	// �o�ߎ��Ԃ��v�Z
	float deltaTime = (nowTime - _lastTime) / 1000.0f; // �~���b��b�ɕϊ�
	_lastTime = nowTime;

	VECTOR VRot = VGet(0, 0, 0); // ��]��
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z); // �v���C���[�̕���������
	this->vecRotation = VRot; // ��]�ʂ�ݒ�
	float distanceToPlayerX = fabs(this->vecPosition.x - playerPos.x);
	float distanceToPlayerZ = fabs(this->vecPosition.z - playerPos.z);
	if (distanceToPlayerX < 600.0f && distanceToPlayerZ < 600.0f) { // x����z���̋�����100�����̏ꍇ
		VECTOR directionAwayFromPlayer = VNorm(VSub(VGet(this->vecPosition.x, 0, this->vecPosition.z), VGet(playerPos.x, 0, playerPos.z)));
		this->vecPosition = VAdd(this->vecPosition, VScale(directionAwayFromPlayer, 5.0f));
		VECTOR VRot = VGet(0, 0, 0); // ��]��
		VRot.y = atan2f(playerPos.x - this->vecPosition.x, playerPos.z - this->vecPosition.z); // �v���C���[�̕���������
		this->vecRotation = VRot; // ��]�ʂ�ݒ�
	}
}

// �X�V
void EscapeEnemy::Update()
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
		/* �G�t�F�N�g�ǉ� */
		{
			/* �ߐڍU��(��)�̃G�t�F�N�g�𐶐� */
			this->eEffect = new EffectManualDelete();

			/* �G�t�F�N�g�̓ǂݍ��� */
			this->eEffect->SetEffectHandle((dynamic_cast<DataList_Effect*>(gpDataListServer->GetDataList("DataList_Effect"))->iGetEffect("FX_e_die03")));

			/* �G�t�F�N�g�̍��W�ݒ� */
			this->eEffect->SetPosition(this->vecPosition);

			/* �G�t�F�N�g�̉�]�ʐݒ� */
			this->eEffect->SetRotation(this->vecRotation);

			/* �G�t�F�N�g�̏����� */
			this->eEffect->Initialization();

			/* �G�t�F�N�g�����X�g�ɓo�^ */
			{
				/* "�I�u�W�F�N�g�Ǘ�"�f�[�^���X�g���擾 */
				DataList_Object* ObjectListHandle = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
				/* �G�t�F�N�g�����X�g�ɓo�^ */
				ObjectListHandle->SetEffect(this->eEffect);

			}
		}
	}
	MoveEnemy();
	
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
