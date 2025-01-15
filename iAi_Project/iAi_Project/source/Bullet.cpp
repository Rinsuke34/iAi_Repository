
#include "Enemy_Test.h"
#include "EffectTest.h"
#include "Bullet.h"


// コンストラクタ
Bullet::Bullet() : BulletBase()
{


}

// デストラクタ
Bullet::~Bullet()
{

}

// 初期化
void Bullet::Initialization()
{

}


void Bullet::Prosses()
{
	// 弾の更新処理
	for (auto it = _vBall.begin(); it != _vBall.end();) {
		(*it)->Update();
		++it;
	}

	for (auto it = _vBall2.begin(); it != _vBall2.end();) {
		(*it)->Update();
		++it;
	}


	// 玉の位置を更新
	for (Ball* ball : _vBall) {
		ball->_vPos = VAdd(ball->_vPos, VScale(ball->_vDir, ball->_speed));
		ball->_vPos2 = VAdd(ball->_vPos2, VScale(ball->_vDir, ball->_speed));
		ball->_life--;
	}

	// 玉の寿命が尽きたら削除
	_vBall.erase(std::remove_if(_vBall.begin(), _vBall.end(), [](Ball* ball) {
		if (ball->_life <= 0) {
			StopEffekseer3DEffect(ball->_effectHandle);
			delete ball;
			return true;
		}
		return false;
		}), _vBall.end());
}
// 更新
void Bullet::Update()
{
	if (this->IGetlife() <= 0)
	{
		// 削除フラグを有効にする
		this->SetDeleteFlg(true);
	}
}

// 描写
void Bullet::Draw()
{

	/* 座標設定 */
	MV1SetPosition(_handleEnemy, VGet(0, 300, 0));
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);
}