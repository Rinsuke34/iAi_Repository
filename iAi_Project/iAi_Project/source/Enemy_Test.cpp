
#include "Enemy_Test.h"
#include "EffectTest.h"
#include "Bullet.h"
#include "DataList_Object.h"

// コンストラクタ
TestEnemy::TestEnemy() : EnemyBase()
{
	this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	// 敵のモデルをロード
	_handleEnemy = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");
	_vEnemyPos = VGet(0, 300, 0); // 敵の初期位置を設定


	//_handleEnemy2 = MV1LoadModel("res/Enemy.mv1");
	//_vEnemy2Pos = VGet(-700, -100, 1000); // 敵の初期位置を設定

	//_handleEnemy3 = MV1LoadModel("res/zako/Enemy.mv1");
	//_vEnemy3Pos = VGet(-200, 300, 1000); // 敵の初期位置を設定

	//_handleEnemy4 = MV1LoadModel("res/Enemy.mv1");

	//_vEnemy4Pos = VGet(-200, -100, 1000); // 敵の初期位置を設定

	//_handleEnemy5 = MV1LoadModel("res/Enemy.mv1");
	//_vEnemy5Pos = VGet(-0, -100, 1000); // 敵の初期位置を設定


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

void TestEnemy::FireBallFromEnemy()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		Bullet* newBullet = new Bullet();
		newBullet->_vPos = VGet(_vEnemyPos.x, _vEnemyPos.y, _vEnemyPos.z); // 敵の位置から発射
		newBullet->_vDir = { 0.0f, 0.0f, -1.0f }; // 玉の向きを設定（例: Z方向）
		newBullet->_speed = 15.0f; // 玉の速度を設定
		// エフェクトの生成
		EffectBase* Effect_Test = new TestEffect();
		Effect_Test->Effect_Load("FX_e_bullet");
		Effect_Test->SetPosition(VAdd(this->vecPosition, VGet(newBullet->_vPos.x, newBullet->_vPos.y, newBullet->_vPos.z)));

		dynamic_cast<TestEffect*>(Effect_Test)->Initialization();


		ObjectList->SetEffect(Effect_Test);
		ObjectList->SetBullet(newBullet);
		_vBullet.push_back(newBullet);
	}

	// 弾の更新と削除
	for (auto it = _vBullet.begin(); it != _vBullet.end();) {
		Bullet* newBullet = *it;
		newBullet->_vPos = VAdd(newBullet->_vPos, VScale(newBullet->_vDir, newBullet->_speed));
		newBullet->Prosses();
		++it;
	}
}

void TestEnemy::MoveEnemy()
{
	// 現在の時間を取得
	int nowTime = GetNowCount();
	// 経過時間を計算
	float deltaTime = (nowTime - _lastTime) / 1000.0f; // ミリ秒を秒に変換
	_lastTime = nowTime;
	_timeSinceLastFire += deltaTime;
	_timeSinceLastFire2 += deltaTime;
	// 敵の位置をターゲット位置に向かって滑らかに移動
	_vEnemyPos = VAdd(_vEnemyPos, VScale(VSub(_vEnemyTargetPos, _vEnemyPos), deltaTime));


	// ターゲット位置に到達したら新しいターゲット位置を設定
	if (VSize(VSub(_vEnemyTargetPos, _vEnemyPos)) < 1.0f) {
		_vEnemyTargetPos = VGet(rand() % 1201 - 1000, _vEnemyPos.y, rand() % 301 + 1200);
	}
}


void TestEnemy::EnemyBulletMove()
{
	//// 弾の更新処理
	for (auto it = _vBullet.begin(); it != _vBullet.end();) {
		/*	(*it)->Update();*/
		++it;
	}

	//// 玉の位置を更新
	//for (Bullet* Bullet : _vBullet) {
	//	Bullet->_vPos = VAdd(Bullet->_vPos, VScale(Bullet->_vDir, Bullet->_speed));
	//	Bullet->_life--;
	//}

	//// 玉の寿命が尽きたら削除
	//_vBullet.erase(std::remove_if(_vBullet.begin(), _vBullet.end(), [](Bullet* Bullet) {
	//	if (Bullet->_life <= 0) {
	//		delete Bullet;
	//		return true;
	//	}
	//	return false;
	//	}), _vBullet.end());


}

// 更新
void TestEnemy::Update()
{
	if (this->iGetNowHP() <= 0)
	{
		// 削除フラグを有効にする
		this->SetDeleteFlg(true);
	}
	//MoveEnemy();
	FireBallFromEnemy();
	EnemyBulletMove();
}

// 描写
void TestEnemy::Draw()
{

	/* 座標設定 */
	MV1SetPosition(_handleEnemy, _vEnemyPos);
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);
}