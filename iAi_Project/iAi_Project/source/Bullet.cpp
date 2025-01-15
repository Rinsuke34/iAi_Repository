
#include "Enemy_Test.h"
#include "EffectTest.h"
#include "Bullet.h"


//// コンストラクタ
//Bullet::Bullet() : BulletBase()
//{
//	// 飛び道具ビルボード
//	_cgBall = LoadGraph("resource/Test/ball.png");
//
//}

//// デストラクタ
//Bullet::~Bullet()
//{
//
//}

// 初期化
void Bullet::Initialization()
{

	_cgBall = LoadGraph("resource/Test/ball.png");
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
	/* 玉の描画処理を追加
	for (Bullet* Bullet : _vBullet)
	{
		 玉の描画処理
		DrawBillboard3D(VGet(0, 300, 300), 50.5f, 50.5f, 3200.f, 0.f, _cgBall, TRUE);

	}*/
	/* 座標設定 */
	/*MV1SetPosition(_handleEnemy, VGet(0, 300, 0));
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	MV1DrawModel(_handleEnemy);*/
}