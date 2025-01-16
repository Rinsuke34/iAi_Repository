
#include "Enemy_Test.h"
#include "EffectTest.h"
#include "Bullet.h"


// �R���X�g���N�^
Bullet::Bullet() : BulletBase()
{


}

// �f�X�g���N�^
Bullet::~Bullet()
{

}

// ������
void Bullet::Initialization()
{

}


void Bullet::Prosses()
{
	// �e�̍X�V����
	for (auto it = _vBall.begin(); it != _vBall.end();) {
		(*it)->Update();
		++it;
	}

	for (auto it = _vBall2.begin(); it != _vBall2.end();) {
		(*it)->Update();
		++it;
	}


	// �ʂ̈ʒu���X�V
	for (Ball* ball : _vBall) {
		ball->_vPos = VAdd(ball->_vPos, VScale(ball->_vDir, ball->_speed));
		ball->_vPos2 = VAdd(ball->_vPos2, VScale(ball->_vDir, ball->_speed));
		ball->_life--;
	}

	// �ʂ̎������s������폜
	_vBall.erase(std::remove_if(_vBall.begin(), _vBall.end(), [](Ball* ball) {
		if (ball->_life <= 0) {
			StopEffekseer3DEffect(ball->_effectHandle);
			delete ball;
			return true;
		}
		return false;
		}), _vBall.end());
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

	/* ���W�ݒ� */
	MV1SetPosition(_handleEnemy, VGet(0, 300, 0));
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);
}