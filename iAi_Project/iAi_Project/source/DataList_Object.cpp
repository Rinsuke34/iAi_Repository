/* 2024.12.15 駒沢風助 ファイル作成 */

#include "DataList_Object.h"

/* オブジェクト管理クラスの定義 */

// コンストラクタ
DataList_Object::DataList_Object() : DataListBase("DataList_Object")
{
	/* 初期化 */
	{
		this->pCharacterPlayer	=	nullptr;	// プレイヤー
		this->pSkySqhere		=	nullptr;	// スカイスフィア
		this->pEnemyList.clear();				// エネミー
		this->pBulletList.clear();				// 弾
		this->pEffectList.clear();				// エフェクト
		this->pPlatformList.clear();			// プラットフォーム
		this->pEffectItemList.clear();			// アイテム(実体なし)
		this->pPickUpItemList.clear();			// アイテム(実体あり)
		this->pEnemySpawnPointList.clear();		// エネミースポナー
	}
}

// デストラクタ
DataList_Object::~DataList_Object()
{
	/* メモリ解放 */
	{
		delete this->pCharacterPlayer;											// プレイヤー
		delete this->pSkySqhere;												// スカイスフィア
		for (auto& pEnemy : this->pEnemyList)			{ delete pEnemy; }		// エネミー
		for (auto& pBullet : this->pBulletList)			{ delete pBullet; }		// 弾		
		for (auto& pEffect : this->pEffectList)			{ delete pEffect; }		// エフェクト
		for (auto& pPlatform : this->pPlatformList)		{ delete pPlatform; }	// プラットフォーム
		for (auto& pEffectItem : this->pEffectItemList)	{ delete pEffectItem; }	// アイテム(実体なし)
		for (auto& pPickUpItem : this->pPickUpItemList)	{ delete pPickUpItem; }	// アイテム(実体あり)
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
	InitializationEffectItem();
	InitializationPickUpItem();
	InitializationEnemySpawnPoint();
}

// プレイヤー初期化
void DataList_Object::InitializationPlayer()
{
	/* プレイヤーが存在するか確認 */
	// ※ タイトル画面等プレイヤーが存在しない場合はnullptrとなる
	if (this->pCharacterPlayer != nullptr)
	{
		// プレイヤーが存在する場合
		/* プレイヤーの初期化処理 */
		this->pCharacterPlayer->Initialization();
		this->pCharacterPlayer->SetupInitialPosition();
	}
}

// スカイスフィア初期化
void DataList_Object::InitializationSkySqhere()
{
	/* スカイスフィアの初期化処理 */
	this->pSkySqhere->Initialization();
	this->pSkySqhere->SetupInitialPosition();
}

// エネミー初期化
void DataList_Object::InitializationEnemy()
{
	/* すべてのエネミーの初期化を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Initialization();
		pEnemy->SetupInitialPosition();
	}
}

// エフェクト初期化
void DataList_Object::InitializationEffect()
{
	/* すべてのエフェクトの初期化を呼ぶ */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Initialization();
		pEffect->SetupInitialPosition();
	}
}

// 弾初期化
void DataList_Object::InitializationBullet()
{
	/* すべての弾の初期化を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Initialization();
		pBullet->SetupInitialPosition();
	}
}

// プラットフォーム初期化
void DataList_Object::InitializationPlatform()
{
	/* プラットフォームの初期化 */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Initialization();
		pPlatform->SetupInitialPosition();
	}
}

// アイテム(実体なし)初期化
void DataList_Object::InitializationEffectItem()
{
	/* すべてのアイテム(実体なし)の初期化を呼ぶ */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Initialization();
		pEffectItem->SetupInitialPosition();
	}
}

// アイテム(実体あり)初期化
void DataList_Object::InitializationPickUpItem()
{
	/* すべてのアイテム(実体あり)の初期化を呼ぶ */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Initialization();
		pPickUpItem->SetupInitialPosition();
	}
}

// エネミースポナー初期化
void DataList_Object::InitializationEnemySpawnPoint()
{
	/* すべてのエネミースポナーの初期化を呼ぶ */
	for (auto& pEnemySpawnPoint : this->pEnemySpawnPointList)
	{
		pEnemySpawnPoint->Initialization();
		pEnemySpawnPoint->SetupInitialPosition();
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
	UpdateEffectItem();
	UpdatePickUpItem();
}

// プレイヤー更新
void DataList_Object::UpdatePlayer()
{
	/* プレイヤーが存在するか確認 */
	// ※ タイトル画面等プレイヤーが存在しない場合はnullptrとなる
	if (this->pCharacterPlayer != nullptr)
	{
		// プレイヤーが存在する場合
		/* プレイヤーの更新を呼ぶ */
		this->pCharacterPlayer->Update();
	}
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

// アイテム(実体なし)更新
void DataList_Object::UpdateEffectItem()
{
	/* すべてのアイテム(実体なし)の更新を呼ぶ */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Update();
	}
}

// アイテム(実体あり)更新
void DataList_Object::UpdatePickUpItem()
{
	/* すべてのアイテム(実体あり)の更新を呼ぶ */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Update();
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
	DrawEffectItem();
	DrawPickUpItem();
}

// プレイヤー描写
void DataList_Object::DrawPlayer()
{
	/* プレイヤーが存在するか確認 */
	// ※ タイトル画面等プレイヤーが存在しない場合はnullptrとなる
	if (this->pCharacterPlayer != nullptr)
	{
		// プレイヤーが存在する場合
		/* プレイヤーの描写を呼ぶ */
		this->pCharacterPlayer->Draw();
	}
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

// アイテム(実体なし)描写
void DataList_Object::DrawEffectItem()
{
	/* すべてのアイテム(実体なし)の描写を呼ぶ */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Draw();
	}
}

// アイテム(実体あり)描写
void DataList_Object::DrawPickUpItem()
{
	/* すべてのアイテム(実体あり)の描写を呼ぶ */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Draw();
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
	DrawEffectItem_Collision();
	DrawPickUpItem_Collision();
}

// プレイヤーコリジョン描写
void DataList_Object::DrawPlayer_Collision()
{
	/* プレイヤーが存在するか確認 */
	// ※ タイトル画面等プレイヤーが存在しない場合はnullptrとなる
	if (this->pCharacterPlayer != nullptr)
	{
		// プレイヤーが存在する場合
		/* プレイヤーコリジョン描写を呼ぶ */
		this->pCharacterPlayer->CollisionDraw();
	}
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

// アイテム(実体なし)コリジョン描写
void DataList_Object::DrawEffectItem_Collision()
{
	// ※アイテム(実体なし)はコリジョンを持たないため、描写は行わない。
}

// アイテム(実体あり)コリジョン描写
void DataList_Object::DrawPickUpItem_Collision()
{
	/* すべてのアイテム(実体あり)のコリジョン描写を呼ぶ */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->CollisionDraw();
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
	DrawEffectItem_Bloom();
	DrawPickUpItem_Bloom();
}

// プレイヤー発光描写
void DataList_Object::DrawPlayer_Bloom()
{
	/* プレイヤーが存在するか確認 */
	// ※ タイトル画面等プレイヤーが存在しない場合はnullptrとなる
	if (this->pCharacterPlayer != nullptr)
	{
		// プレイヤーが存在する場合
		/* プレイヤーの発光描写を呼ぶ */
		this->pCharacterPlayer->BloomDraw();
	}
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

// アイテム(実体なし)発光描写
void DataList_Object::DrawEffectItem_Bloom()
{
	/* すべてのアイテム(実体なし)の発光描写を呼ぶ */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->BloomDraw();
	}
}

// アイテム(実体あり)発光描写
void DataList_Object::DrawPickUpItem_Bloom()
{
	/* すべてのアイテム(実体あり)の発光描写を呼ぶ */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->BloomDraw();
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
	DeleteEffectItem();
	DeletePickUpItem();
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

// 削除フラグが有効なアイテム(実体なし)を削除
void DataList_Object::DeleteEffectItem()
{
	/* 削除フラグが有効なアイテム(実体なし)を削除 */
	pEffectItemList.erase(std::remove_if(pEffectItemList.begin(), pEffectItemList.end(), [](EffectItemBase* pEffectItem)
	{
		/* 削除フラグが有効であるか確認　*/
		if (pEffectItem->bGetDeleteFlg() == true)
		{
			// 有効である場合
			/* メモリ解放 */
			delete pEffectItem;
			return true;
		}
		else
		{
			// 無効である場合
			return false;
		}
	}), pEffectItemList.end());
}

// 削除フラグが有効なアイテム(実体あり)を削除
void DataList_Object::DeletePickUpItem()
{
	/* 削除フラグが有効なアイテム(実体あり)を削除 */
	pPickUpItemList.erase(std::remove_if(pPickUpItemList.begin(), pPickUpItemList.end(), [](PickUpItemBase* pPickUpItem)
	{
		/* 削除フラグが有効であるか確認　*/
		if (pPickUpItem->bGetDeleteFlg() == true)
		{
			// 有効である場合
			/* メモリ解放 */
			delete pPickUpItem;
			return true;
		}
		else
		{
			// 無効である場合
			return false;
		}
	}), pPickUpItemList.end());
}

// 全オブジェクトリセット処理
void DataList_Object::ResetAll()
{
	/* 登録されているすべてのオブジェクトのリセット処理 */
	ResetPlayer();
	ResetSkySqhere();
	ResetEnemy();
	ResetEffect();
	ResetBullet();
	ResetPlatform();
	ResetEffectItem();
	ResetPickUpItem();
	ResetEnemySpawnPoint();
}

// プレイヤーリセット処理
void DataList_Object::ResetPlayer()
{
	/* プレイヤーが存在するか確認 */
	// ※ タイトル画面等プレイヤーが存在しない場合はnullptrとなる
	if (this->pCharacterPlayer != nullptr)
	{
		// プレイヤーが存在する場合
		/* プレイヤーのリセット処理を呼ぶ */
		this->pCharacterPlayer->Reset();
	}
}

// スカイスフィアリセット処理
void DataList_Object::ResetSkySqhere()
{
	/* スカイスフィアのリセット処理を呼ぶ */
	this->pSkySqhere->Reset();
}

// エネミーリセット処理
void DataList_Object::ResetEnemy()
{
	/* すべてのエネミーのリセット処理を呼ぶ */
	for (auto& pEnemy : this->pEnemyList)
	{
		pEnemy->Reset();
	}
}

// エフェクトリセット処理
void DataList_Object::ResetEffect()
{
	/* すべてのエフェクトのリセット処理を呼ぶ */
	for (auto& pEffect : this->pEffectList)
	{
		pEffect->Reset();
	}
}

// 弾リセット処理
void DataList_Object::ResetBullet()
{
	/* すべての弾のリセット処理を呼ぶ */
	for (auto& pBullet : this->pBulletList)
	{
		pBullet->Reset();
	}
}

// プラットフォームリセット処理
void DataList_Object::ResetPlatform()
{
	/* すべてのプラットフォームのリセット処理 */
	for (auto& pPlatform : this->pPlatformList)
	{
		pPlatform->Reset();
	}
}

// アイテム(実体なし)リセット処理
void DataList_Object::ResetEffectItem()
{
	/* すべてのアイテム(実体なし)のリセット処理を呼ぶ */
	for (auto& pEffectItem : this->pEffectItemList)
	{
		pEffectItem->Reset();
	}
}

// アイテム(実体あり)リセット処理
void DataList_Object::ResetPickUpItem()
{
	/* すべてのアイテム(実体あり)のリセット処理を呼ぶ */
	for (auto& pPickUpItem : this->pPickUpItemList)
	{
		pPickUpItem->Reset();
	}
}

// エネミースポナーリセット処理
void DataList_Object::ResetEnemySpawnPoint()
{
	/* すべてのエネミースポナーのリセット処理を呼ぶ */
	for (auto& pEnemySpawnPoint : this->pEnemySpawnPointList)
	{
		pEnemySpawnPoint->Reset();
	}
}
