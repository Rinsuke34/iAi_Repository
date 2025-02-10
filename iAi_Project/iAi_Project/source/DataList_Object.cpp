/* 2024.12.15 駒沢風助 ファイル作成 */

#include "DataList_Object.h"

/* オブジェクト管理クラスの定義 */

// コンストラクタ
DataList_Object::DataList_Object() : DataListBase("DataList_Object")
{
	/* 初期化 */
	// プレイヤー
	this->pCharacterPlayer	=	nullptr;

	// スカイスフィア
	this->pSkySqhere		=	nullptr;

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
	// プレイヤー
	delete this->pCharacterPlayer;

	// スカイスフィア
	delete this->pSkySqhere;

	// エネミー
	for (auto& pEnemy : this->pEnemyList)
	{
		delete pEnemy;
	}

	// 弾
	for (auto& pBullet : this->pBulletList)
	{
		delete pBullet;
	}

	// エフェクト
	for (auto& pEffect : this->pEffectList)
	{
		delete pEffect;
	}

	// プラットフォーム
	for (auto& pPlatform : this->pPlatformList)
	{
		delete pPlatform;
	}
}

/* リスト内オブジェクト初期化 */
// 全オブジェクト初期化
void DataList_Object::InitializationAll()
{
	/* 登録されているすべてのオブジェクトの初期化 */
	InitializationPlayer();
	InitializationSkySqhere();
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

// スカイスフィア初期化
void DataList_Object::InitializationSkySqhere()
{
	/* スカイスフィアの初期化 */
	this->pSkySqhere->Initialization();
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
	/* プラットフォームの初期化 */
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
	UpdateSkySqhere();
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

// スカイスフィア更新
void DataList_Object::UpdateSkySqhere()
{
	/* スカイスフィアの更新を呼ぶ */
	this->pSkySqhere->Update();
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
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Update();
	}
}

/* リスト内オブジェクト描写 */
// 全オブジェクト描写(エフェクトを除く)
void DataList_Object::DrawAll()
{
	/* 登録されているすべてのオブジェクトの描写 */
	DrawPlayer();
	DrawSkySqhere();
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

// スカイスフィア描写
void DataList_Object::DrawSkySqhere()
{
	/* スカイスフィアの描写を呼ぶ */
	this->pSkySqhere->Draw();
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
	/*　バックグランド非表示フラグが無効であるか確認 */
	if (gbDrawDeleteBackGroundFlg == false)
	{
		// 無効である場合
		/* プラットフォームの描写を呼ぶ */
		for (auto& pPlatform : this->pPlatformList)
		{
			pPlatform->Draw();
		}
	}
}

// エフェクト描写
void DataList_Object::DrawEffect()
{
	/* すべてのエフェクトの描写を呼ぶ */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Draw();
	}
}

/* リスト内オブジェクトコリジョン描写 */
// 全オブジェクトコリジョン描写
void DataList_Object::DrawAll_Collision()
{
	/* 登録されているすべてのオブジェクトのコリジョン描写 */
	DrawPlayer_Collision();
	DrawSkySqhere_Collision();
	DrawEnemy_Collision();
	DrawBullet_Collision();
	DrawPlatform_Collision();
}

// プレイヤーコリジョン描写
void DataList_Object::DrawPlayer_Collision()
{
	/* プレイヤーコリジョン描写を呼ぶ */
	this->pCharacterPlayer->CollisionDraw();
}

// スカイスフィアコリジョン描写
void DataList_Object::DrawSkySqhere_Collision()
{
	/* スカイスフィアコリジョン描写を呼ぶ */
	this->pSkySqhere->CollisionDraw();
}

// エネミーコリジョン描写
void DataList_Object::DrawEnemy_Collision()
{
	/* すべてのエネミーコリジョン描写を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->CollisionDraw();
	}
}

// 弾コリジョン描写
void DataList_Object::DrawBullet_Collision()
{
	/* すべての弾コリジョン描写を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->CollisionDraw();
	}
}

// プラットフォームコリジョン描写
void DataList_Object::DrawPlatform_Collision()
{
	// 有効である場合
	/* プラットフォームの描写を呼ぶ */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->CollisionDraw();
	}
}

/* リスト内オブジェクト発光描写 */
// 全オブジェクト発光描写
void DataList_Object::DrawAll_Bloom()
{
	/* 登録されているすべてのオブジェクトの発光描写 */
	DrawPlayer_Bloom();
	DrawSkySqhere_Bloom();
	DrawEnemy_Bloom();
	DrawBullet_Bloom();
	DrawPlatform_Bloom();
}

// プレイヤー発光描写
void DataList_Object::DrawPlayer_Bloom()
{
	/* プレイヤーの発光描写を呼ぶ */
	this->pCharacterPlayer->BloomDraw();
}

// スカイスフィア発光描写
void DataList_Object::DrawSkySqhere_Bloom()
{
	/* スカイスフィアの発光描写を呼ぶ */
	this->pSkySqhere->BloomDraw();
}

// エネミー発光描写
void DataList_Object::DrawEnemy_Bloom()
{
	/* すべてのエネミーの発光描写を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->BloomDraw();
	}
}

// 弾発光描写
void DataList_Object::DrawBullet_Bloom()
{
	/* すべての弾の発光描写を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->BloomDraw();
	}
}

// プラットフォーム発光描写
void DataList_Object::DrawPlatform_Bloom()
{
	/*　バックグランド非表示フラグが無効であるか確認 */
	if (gbDrawDeleteBackGroundFlg == false)
	{
		// 無効である場合
		/* プラットフォームの発光描写を呼ぶ */
		for (auto& pPlatform : this->pPlatformList)
		{
			pPlatform->BloomDraw();
		}
	}
}

/* リスト内オブジェクト削除 */
// 削除フラグが有効な全オブジェクト削除
// ※単独のデータはデストラクタで開放されるため、リストで管理しているデータのみ対象とする。
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
