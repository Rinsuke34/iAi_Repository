
#include "Enemy_Test.h"

// コンストラクタ
TestEnemy::TestEnemy(): EnemyBase()
{
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
	DrawSphere3D(vecGetPosition(), 50.f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}