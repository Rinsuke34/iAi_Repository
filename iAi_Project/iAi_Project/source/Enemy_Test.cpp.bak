
#include "Enemy_Test.h"

// コンストラクタ
TestEnemy::TestEnemy(): EnemyBase()
{
	// HPを設定
	this->SetMaxHP(1);
	this->SetNowHP(1);
	stCollisionCapsule.vecCapsuleTop = VGet(100, 200, 100);
	stCollisionCapsule.vecCapsuleBottom = VGet(100, 0, 100);
	stCollisionCapsule.fCapsuleRadius = 50.f;
}

// デストラクタ
TestEnemy::~TestEnemy()
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
	DrawCapsule3D(stCollisionCapsule.vecCapsuleTop, stCollisionCapsule.vecCapsuleBottom, stCollisionCapsule.fCapsuleRadius, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}