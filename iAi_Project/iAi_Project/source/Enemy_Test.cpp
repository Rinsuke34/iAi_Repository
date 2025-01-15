
#include "Enemy_Test.h"
#include "EffectTest.h"


// コンストラクタ
TestEnemy::TestEnemy(): EnemyBase()
{

	// 敵のモデルをロード
	_handleEnemy = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");
	_vEnemyPos = VGet(-500, -100, 1000); // 敵の初期位置を設定

	_handleEnemy2 = MV1LoadModel("res/Enemy.mv1");
	_vEnemy2Pos = VGet(-700, -100, 1000); // 敵の初期位置を設定

	_handleEnemy3 = MV1LoadModel("res/zako/Enemy.mv1");
	_vEnemy3Pos = VGet(-200, 300, 1000); // 敵の初期位置を設定

	_handleEnemy4 = MV1LoadModel("res/Enemy.mv1");
	_vEnemy4Pos = VGet(-200, -100, 1000); // 敵の初期位置を設定

	_handleEnemy5 = MV1LoadModel("res/Enemy.mv1");
	_vEnemy5Pos = VGet(-0, -100, 1000); // 敵の初期位置を設定
	// HPを設定
	this->SetMaxHP(1);
	this->SetNowHP(1);
}

// デストラクタ
TestEnemy::~TestEnemy()
{

}

// 初期化
void TestEnemy::Initialization()
{

}

//void TestEnemy::FireBallFromEnemy() {
//	if (_isFiringBall) {
//		Ball* newBall = new Ball();
//		newBall->_vPos = VGet(_vEnemyPos.x, _vEnemyPos.y + 100 + 30, _vEnemyPos.z + 45); // 敵の位置から発射
//		newBall->_vDir = { 0.0f, 0.0f, -1.0f }; // 玉の向きを設定（例: Z方向）
//		newBall->_speed = 15.0f; // 玉の速度を設定
//		newBall->_life = 200; // 玉の生存カウンタを設定
//		// エフェクトの生成
//		EffectBase* Effect_Test = new TestEffect();
//		Effect_Test->Effect_Load("FX_e_bullet");
//		Effect_Test->SetPosition(VAdd(this->vecPosition, VGet(newBall->_vPos.x, newBall->_vPos.y, newBall->_vPos.z)));
//
//		_vBall.push_back(newBall);
//	}
//
//	// 弾の更新と削除
//	for (auto it = _vBall.begin(); it != _vBall.end();) {
//		Ball* ball = *it;
//		ball->_vPos = VAdd(ball->_vPos, VScale(ball->_vDir, ball->_speed));
//		ball->Update();
//		ball->_life--;
//		++it;
//	}
//}

// 更新
void TestEnemy::Update()
{
	if (this->iGetNowHP() <= 0)
	{
		// 削除フラグを有効にする
		this->SetDeleteFlg(true);
	}
}

// 描写
void TestEnemy::Draw()
{

	/* 座標設定 */
	MV1SetPosition(_handleEnemy, VGet(0, 300, 0));
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);
}