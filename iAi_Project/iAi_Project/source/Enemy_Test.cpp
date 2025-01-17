
#include "Enemy_Test.h"
#include "EffectTest.h"
#include "Bullet.h"
#include "DataList_Object.h"

// �R���X�g���N�^
TestEnemy::TestEnemy(): EnemyBase()
{
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	// �G�̃��f������[�h
	_handleEnemy = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");
	_vEnemyPos = VGet(0, 300, 0); // �G�̏����ʒu��ݒ�


	//_handleEnemy2 = MV1LoadModel("res/Enemy.mv1");
	//_vEnemy2Pos = VGet(-700, -100, 1000); // �G�̏����ʒu��ݒ�

	//_handleEnemy3 = MV1LoadModel("res/zako/Enemy.mv1");
	//_vEnemy3Pos = VGet(-200, 300, 1000); // �G�̏����ʒu��ݒ�

	//_handleEnemy4 = MV1LoadModel("res/Enemy.mv1");

	//_vEnemy4Pos = VGet(-200, -100, 1000); // �G�̏����ʒu��ݒ�

	//_handleEnemy5 = MV1LoadModel("res/Enemy.mv1");
	//_vEnemy5Pos = VGet(-0, -100, 1000); // �G�̏����ʒu��ݒ�
	 
	
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

void TestEnemy::FireBallFromEnemy() 
{
	if (CheckHitKey(KEY_INPUT_P)) {
		Bullet* newBullet = new Bullet();
		newBullet->_vPos = VGet(_vEnemyPos.x, _vEnemyPos.y , _vEnemyPos.z ); // �G�̈ʒu���甭��
		newBullet->_vDir = { 0.0f, 0.0f, -1.0f }; // �ʂ̌�����ݒ�i��: Z�����j
		newBullet->_speed = 15.0f; // �ʂ̑��x��ݒ�
		// �G�t�F�N�g�̐���
		EffectBase* Effect_Test = new TestEffect();
		Effect_Test->Effect_Load("FX_e_bullet");
		Effect_Test->SetPosition(VAdd(this->vecPosition, VGet(newBullet->_vPos.x, newBullet->_vPos.y, newBullet->_vPos.z)));

		dynamic_cast<TestEffect*>(Effect_Test)->Initialization();


		ObjectList->SetEffect(Effect_Test);
		ObjectList->SetBullet(newBullet);
		_vBullet.push_back(newBullet);
	}

	// �e�̍X�V�ƍ폜
	for (auto it = _vBullet.begin(); it != _vBullet.end();) {
		Bullet* newBullet = *it;
		newBullet->_vPos = VAdd(newBullet->_vPos, VScale(newBullet->_vDir, newBullet->_speed));
		newBullet->Prosses();
		++it;
	}
}

void TestEnemy::MoveEnemy() 
{
	// ���݂̎��Ԃ�擾
	int nowTime = GetNowCount();
	// �o�ߎ��Ԃ�v�Z
	float deltaTime = (nowTime - _lastTime) / 1000.0f; // �~���b��b�ɕϊ�
	_lastTime = nowTime;
	_timeSinceLastFire += deltaTime;
	_timeSinceLastFire2 += deltaTime;
	// �G�̈ʒu��^�[�Q�b�g�ʒu�Ɍ������Ċ��炩�Ɉړ�
	_vEnemyPos = VAdd(_vEnemyPos, VScale(VSub(_vEnemyTargetPos, _vEnemyPos), deltaTime));


	// �^�[�Q�b�g�ʒu�ɓ��B������V�����^�[�Q�b�g�ʒu��ݒ�
	if (VSize(VSub(_vEnemyTargetPos, _vEnemyPos)) < 1.0f) {
		_vEnemyTargetPos = VGet(rand() % 1201 - 1000, _vEnemyPos.y, rand() % 301 + 1200);
	}
}


void TestEnemy::EnemyBulletMove() 
{
	//// �e�̍X�V����
	for (auto it = _vBullet.begin(); it != _vBullet.end();) {

		++it;
	}

	//// �ʂ̈ʒu��X�V
	//for (Bullet* Bullet : _vBullet) {
	//	Bullet->_vPos = VAdd(Bullet->_vPos, VScale(Bullet->_vDir, Bullet->_speed));
	//	Bullet->_life--;
	//}

	//// �ʂ̎������s������폜
	//_vBullet.erase(std::remove_if(_vBullet.begin(), _vBullet.end(), [](Bullet* Bullet) {
	//	if (Bullet->_life <= 0) {
	//		delete Bullet;
	//		return true;
	//	}
	//	return false;
	//	}), _vBullet.end());


}

// �X�V
void TestEnemy::Update()
{
	if (this->iGetNowHP() <= 0)
	{
		// �폜�t���O��L���ɂ���
		this->SetDeleteFlg(true);
	}
	//MoveEnemy();
	FireBallFromEnemy();
	EnemyBulletMove();
}

// �`��
void TestEnemy::Draw()
{

	/* ���W�ݒ� */
	MV1SetPosition(_handleEnemy, _vEnemyPos);
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);
}