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

	// エフェクト
	this->pEffectList.clear();

	// プラットフォーム
	this->pPlatformList.clear();
}

// デストラクタ
DataList_Object::~DataList_Object()
{
	/* 解放 */
	// リストはvectorのため、自動解放される
	this->pCharacterPlayer	=	nullptr;
}

/* リスト内オブジェクト初期化 */
// 全オブジェクト初期化
void DataList_Object::InitializationAll()
{
	/* 登録されているすべてのオブジェクトの初期化 */
	InitializationPlayer();
	InitializationEnemy();
	InitializationEffect();
	InitializationBullet();
	InitializationPlatform();
}

// プレイヤー初期化
void DataList_Object::InitializationPlayer()
{
	/* プレイヤーの初期化を呼ぶ */
	this->pCharacterPlayer->Initialization();
}

// エネミー初期化
void DataList_Object::InitializationEnemy()
{
	/* すべてのエネミーの初期化を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Initialization();
	}
}

// エフェクト初期化
void DataList_Object::InitializationEffect()
{
	/* すべてのエフェクトの初期化を呼ぶ */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Initialization();
	}
}

// 弾初期化
void DataList_Object::InitializationBullet()
{
	/* すべての弾の初期化を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Initialization();
	}
}

// プラットフォーム初期化
void DataList_Object::InitializationPlatform()
{
	/* 稼働プラットフォームの初期化を呼ぶ */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Initialization();
	}
}

/* リスト内オブジェクト更新 */
// 全オブジェクト更新
void DataList_Object::UpdateAll()
{
	/* 登録されているすべてのオブジェクトの更新 */
	UpdatePlayer();
	UpdateEnemy();
	UpdateEffect();
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

// エフェクト更新
void DataList_Object::UpdateEffect()
{
	/* すべてのエフェクトの更新を呼ぶ */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Update();
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

/* リスト内オブジェクト発光描写 */
// 全オブジェクト発光描写
void DataList_Object::BloomDrawAll()
{
	/* 登録されているすべてのオブジェクトの発光描写 */
	BloomDrawPlayer();
	BloomDrawEnemy();
	BloomDrawBullet();
	BloomDrawPlatform();
}

// プレイヤー発光描写
void DataList_Object::BloomDrawPlayer()
{
	/* プレイヤーの発光描写を呼ぶ */
	this->pCharacterPlayer->BloomDraw();
}

// エネミー発光描写
void DataList_Object::BloomDrawEnemy()
{
	/* すべてのエネミーの発光描写を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->BloomDraw();
	}
}

// 弾発光描写
void DataList_Object::BloomDrawBullet()
{
	/* すべての弾の発光描写を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->BloomDraw();
	}
}

// プラットフォーム発光描写
void DataList_Object::BloomDrawPlatform()
{
	/* すべてのプラットフォームの発光描写を呼ぶ */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->BloomDraw();
	}
}

/* リスト内オブジェクト削除 */
// 削除フラグが有効な全オブジェクト削除
void DataList_Object::DeleteAll()
{
	DeleteEnemy();
	DeleteEffect();
	DeleteBullet();
	DeletePlatform();
}

// 削除フラグが有効なエネミーを削除
void DataList_Object::DeleteEnemy()
{
	/* 削除フラグが有効なエネミーを削除 */
	pEnemyList.erase(std::remove_if(pEnemyList.begin(), pEnemyList.end(), [](EnemyBase* pEnemy)
		{
			/* 削除フラグが有効であるか確認　*/
			if (pEnemy->bGetDeleteFlg() == true)
			{
				// 有効である場合
				delete pEnemy;
				return true;
			}
			else
			{
				// 無効である場合
				return false;
			}
		}), pEnemyList.end());
}

// 削除フラグが有効なエフェクトを削除
void DataList_Object::DeleteEffect()
{
	/* 削除フラグが有効なエフェクトを削除 */
	pEffectList.erase(std::remove_if(pEffectList.begin(), pEffectList.end(), [](EffectBase* pEffect)
		{
			/* 削除フラグが有効であるか確認　*/
			if (pEffect->bGetDeleteFlg() == true)
			{
				// 有効である場合
				/* メモリ解放 */
				delete pEffect;
				return true;
			}
			else
			{
				// 無効である場合
				return false;
			}
		}), pEffectList.end());
}

// 削除フラグが有効な弾を削除
void DataList_Object::DeleteBullet()
{
	/* 削除フラグが有効な弾を削除 */
	pBulletList.erase(std::remove_if(pBulletList.begin(), pBulletList.end(), [](BulletBase* pBullet)
		{
			/* 削除フラグが有効であるか確認　*/
			if (pBullet->bGetDeleteFlg() == true)
			{
				// 有効である場合
				/* メモリ解放 */
				delete pBullet;
				return true;
			}
			else
			{
				// 無効である場合
				return false;
			}
		}), pBulletList.end());
}

// 削除フラグが有効なプラットフォームを削除
void DataList_Object::DeletePlatform()
{
	/* 削除フラグが有効なプラットフォームを削除 */
	pPlatformList.erase(std::remove_if(pPlatformList.begin(), pPlatformList.end(), [](PlatformBase* pPlatform)
		{
			/* 削除フラグが有効であるか確認　*/
			if (pPlatform->bGetDeleteFlg() == true)
			{
				// 有効である場合
				/* メモリ解放 */
				delete pPlatform;
				return true;
			}
			else
			{
				// 無効である場合
				return false;
			}
		}), pPlatformList.end());
}
