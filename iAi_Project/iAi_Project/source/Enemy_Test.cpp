
#include "Enemy_Test.h"
#include "EffectTest.h"


// �R���X�g���N�^
TestEnemy::TestEnemy(): EnemyBase()
{

	// �G�̃��f�������[�h
	_handleEnemy = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");
	_vEnemyPos = VGet(-500, -100, 1000); // �G�̏����ʒu��ݒ�

	_handleEnemy2 = MV1LoadModel("res/Enemy.mv1");
	_vEnemy2Pos = VGet(-700, -100, 1000); // �G�̏����ʒu��ݒ�

	_handleEnemy3 = MV1LoadModel("res/zako/Enemy.mv1");
	_vEnemy3Pos = VGet(-200, 300, 1000); // �G�̏����ʒu��ݒ�

	_handleEnemy4 = MV1LoadModel("res/Enemy.mv1");
	_vEnemy4Pos = VGet(-200, -100, 1000); // �G�̏����ʒu��ݒ�

	_handleEnemy5 = MV1LoadModel("res/Enemy.mv1");
	_vEnemy5Pos = VGet(-0, -100, 1000); // �G�̏����ʒu��ݒ�
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

}

//void TestEnemy::FireBallFromEnemy() {
//	if (_isFiringBall) {
//		Ball* newBall = new Ball();
//		newBall->_vPos = VGet(_vEnemyPos.x, _vEnemyPos.y + 100 + 30, _vEnemyPos.z + 45); // �G�̈ʒu���甭��
//		newBall->_vDir = { 0.0f, 0.0f, -1.0f }; // �ʂ̌�����ݒ�i��: Z�����j
//		newBall->_speed = 15.0f; // �ʂ̑��x��ݒ�
//		newBall->_life = 200; // �ʂ̐����J�E���^��ݒ�
//		// �G�t�F�N�g�̐���
//		EffectBase* Effect_Test = new TestEffect();
//		Effect_Test->Effect_Load("FX_e_bullet");
//		Effect_Test->SetPosition(VAdd(this->vecPosition, VGet(newBall->_vPos.x, newBall->_vPos.y, newBall->_vPos.z)));
//
//		_vBall.push_back(newBall);
//	}
//
//	// �e�̍X�V�ƍ폜
//	for (auto it = _vBall.begin(); it != _vBall.end();) {
//		Ball* ball = *it;
//		ball->_vPos = VAdd(ball->_vPos, VScale(ball->_vDir, ball->_speed));
//		ball->Update();
//		ball->_life--;
//		++it;
//	}
//}

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

	/* ���W�ݒ� */
	MV1SetPosition(_handleEnemy, VGet(0, 300, 0));
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);
}