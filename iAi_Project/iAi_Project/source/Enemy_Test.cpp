
#include "Enemy_Test.h"

// �R���X�g���N�^
TestEnemy::TestEnemy(): EnemyBase()
{
	// HP��ݒ�
	this->SetMaxHP(1);
	this->SetNowHP(1);
}

// �f�X�g���N�^
TestEnemy::~TestEnemy()
{

}

// ������
void TestEnemy::Initialization()
{
	this->stCollisionCapsule.fCapsuleRadius = 100;
	this->stCollisionCapsule.vecCapsuleTop = VAdd(this->vecPosition,VGet(0,100,0));
	this->stCollisionCapsule.vecCapsuleBottom = this->vecPosition;
}

// �X�V
void TestEnemy::Update()
{
	if (this->iGetNowHP() <= 0)
	{
		// �폜�t���O��L���ɂ���
		this->SetDeleteFlg(true);
	}
}

// �`��
void TestEnemy::Draw()
{
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}