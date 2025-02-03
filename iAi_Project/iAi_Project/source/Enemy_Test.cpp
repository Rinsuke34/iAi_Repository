/* 2025.01.28 �ΐ�q�� �t�@�C���쐬 */
#include "Enemy_Test.h"

// �R���X�g���N�^
TestEnemy::TestEnemy() : EnemyBasic()
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
		this->iModelHandle = ModelListHandle->iGetModel("Enemy/Enemy_Kari_0127");
	}
	
	this->eEffect	= nullptr;
}

// �f�X�g���N�^
TestEnemy::~TestEnemy()
{

}

// ������
void TestEnemy::Initialization()
{
	/* �R���W�����Z�b�g */
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition,VGet(0,100,0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;

	/* �R�A�t���[���ԍ��擾 */
	LoadCoreFrameNo();
}

void TestEnemy::MoveEnemy()
{

	CharacterBase* player = this->ObjectList->GetCharacterPlayer();
	VECTOR playerPos = player->vecGetPosition();
	// ���݂̎��Ԃ��擾
	int nowTime = GetNowCount();
	static bool effectPlayed = false; // �G�t�F�N�g���Đ����ꂽ���ǂ�����ǐՂ���t���O
	// actioncount �ϐ��Ɋ�Â�����
	VECTOR VRot = VGet(0, 0, 0); // ��]��
	VRot.y = atan2f(this->vecPosition.x - playerPos.x, this->vecPosition.z - playerPos.z); // �v���C���[�̕���������
	this->vecRotation = VRot; // ��]�ʂ�ݒ�
	if (actioncount == 0 && !effectPlayed) {
		//	// �L�����N�^�[���v���C���[�ɋ߂Â���
		VECTOR direction = VNorm(VSub(playerPos,this->vecPosition));
		this->vecPosition = VAdd(this->vecPosition, VScale(direction, 5.0f)); // ���x�𒲐�
		// �v���C���[�ɋ߂Â�����J�E���g�𑝂₷
		if (VSize(VSub(playerPos, this->vecPosition)) < 50.0f) { // ������臒l��ݒ�
			actioncount = 2;
		}
	}
	else if (actioncount == 2 && !effectPlayed) {
		// ��莞�Ԍ�ɔ���
		static int startTime = nowTime;
		// 3�b��ɔ���
		if (nowTime - startTime > 3000) { // 3�b��ɔ���
			this->bDeleteFlg = true;
			effectPlayed = true; // �G�t�F�N�g���Đ����ꂽ���Ƃ��L�^
			startTime = nowTime; // �^�C�}�[�����Z�b�g

		}
	}
}

// �X�V
void TestEnemy::Update()
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
	MoveEnemy();
	
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition, VGet(0, 100, 0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}
