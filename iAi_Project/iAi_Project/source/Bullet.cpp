
#include "Enemy_Test.h"
#include "EffectTest.h"
#include "Bullet.h"


//// �R���X�g���N�^
//Bullet::Bullet() : BulletBase()
//{
//	// ��ѓ���r���{�[�h
//	_cgBall = LoadGraph("resource/Test/ball.png");
//
//}

//// �f�X�g���N�^
//Bullet::~Bullet()
//{
//
//}

// ������
void Bullet::Initialization()
{

	_cgBall = LoadGraph("resource/Test/ball.png");
}



// �X�V
void Bullet::Update()
{
	if (this->IGetlife() <= 0)
	{
		// �폜�t���O��L���ɂ���
		this->SetDeleteFlg(true);
	}
}

// �`��
void Bullet::Draw()
{
	/* �ʂ̕`�揈����ǉ�
	for (Bullet* Bullet : _vBullet)
	{
		 �ʂ̕`�揈��
		DrawBillboard3D(VGet(0, 300, 300), 50.5f, 50.5f, 3200.f, 0.f, _cgBall, TRUE);

	}*/
	/* ���W�ݒ� */
	/*MV1SetPosition(_handleEnemy, VGet(0, 300, 0));
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);*/
}