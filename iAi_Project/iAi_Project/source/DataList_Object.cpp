/* 2024.12.15 駒沢風助 ファイル作成 */

#include "DataList_Object.h"

/* オブジェクト管理クラスの定義 */

// コンストラクタ
DataList_Object::DataList_Object() : DataListBase("DataList_Object")
{
	/* 初期化 */
	// プレイヤー
	this->pCharacterPlayer	=	nullptr;

	// エネミー
	this->pEnemyList.clear();
	
	// 弾
	this->pBulletList.clear();

	// プラットフォーム
	this->pPlatformList.clear();
}

// デストラクタ
DataList_Object::~DataList_Object()
{
	/* 解放 */
	this->pCharacterPlayer	=	nullptr;
}

// Jsonからデータをロード
void DataList_Object::JsonDataLoad()
{
	/* Jsonファイルからデータ読み込み */
	// ※現状は未実装
}


/* リスト内オブジェクト更新 */
// 全オブジェクト更新
void DataList_Object::UpdateAll()
{
	/* 登録されているすべてのオブジェクトの更新 */
	UpdatePlayer();
	UpdateEnemy();
	UpdateBullet();
	UpdatePlatform();
}

// プレイヤー更新
void DataList_Object::UpdatePlayer()
{
	/* プレイヤーの更新を呼ぶ */
	this->pCharacterPlayer->Update();
}

// エネミー更新
void DataList_Object::UpdateEnemy()
{
	/* すべてのエネミーの更新を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Update();
	}
}

// 弾更新
void DataList_Object::UpdateBullet()
{
	/* すべての弾の更新を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Update();
	}
}

// プラットフォーム更新
void DataList_Object::UpdatePlatform()
{
	/* 稼働プラットフォームの更新を呼ぶ(予定) */
}

/* リスト内オブジェクト描写 */
// 全オブジェクト描写
void DataList_Object::DrawAll()
{
	/* 登録されているすべてのオブジェクトの描写 */
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawPlatform();
}

// プレイヤー描写
void DataList_Object::DrawPlayer()
{
	/* プレイヤーの描写を呼ぶ */
	this->pCharacterPlayer->Draw();
}

// エネミー描写
void DataList_Object::DrawEnemy()
{
	/* すべてのエネミーの描写を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Draw();
	}
}

// 弾描写
void DataList_Object::DrawBullet()
{
	/* すべての球の描写を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Draw();
	}
}

// プラットフォーム描写
void DataList_Object::DrawPlatform()
{
	/* すべてのプラットフォームの描写を呼ぶ */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Draw();
	}
}