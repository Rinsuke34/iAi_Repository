/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include "PublicInclude.h"

/* オブジェクト */
#include "Enemy_Basic.h"
#include "EnemySpawnPoint_Base.h"

/* 前方参照 */
// ※AppFrameで定義されていないクラスを使用する場合、循環参照対策に実施する。
class Enemy_Basic;
class EnemySpawnPoint_Base;

/* オブジェクト管理クラスの宣言 */

// オブジェクト管理クラス
class DataList_Object : public DataListBase
{
	public:
		DataList_Object();				// コンストラクタ
		virtual ~DataList_Object();		// デストラクタ

		/* リスト内オブジェクト初期化 */
		void	InitializationAll();				// 全オブジェクト初期化
		void	InitializationPlayer();				// プレイヤー初期化
		void	InitializationSkySqhere();			// スカイスフィア初期化
		void	InitializationEnemy();				// エネミー初期化
		void	InitializationEffect();				// エフェクト初期化
		void	InitializationBullet();				// 弾初期化
		void	InitializationPlatform();			// プラットフォーム初期化
		void	InitializationEffectItem();			// アイテム(実体なし)初期化
		void	InitializationPickUpItem();			// アイテム(実体あり)初期化
		void	InitializationEnemySpawnPoint();	// エネミースポナー初期化

		/* リスト内オブジェクト更新 */
		void	UpdateAll();			// 全オブジェクト更新
		void	UpdatePlayer();			// プレイヤー更新
		void	UpdateSkySqhere();		// スカイスフィア更新
		void	UpdateEnemy();			// エネミー更新
		void	UpdateEffect();			// エフェクト更新
		void	UpdateBullet();			// 弾更新
		void	UpdatePlatform();		// プラットフォーム更新
		void	UpdateEffectItem();		// アイテム(実体なし)更新
		void	UpdatePickUpItem();		// アイテム(実体あり)更新

		/* リスト内オブジェクト描写 */
		void	DrawAll();				// 全オブジェクト描写(エフェクトを除く)
		void	DrawPlayer();			// プレイヤー描写
		void	DrawSkySqhere();		// スカイスフィア描写
		void	DrawEnemy();			// エネミー描写
		void	DrawBullet();			// 弾描写
		void	DrawPlatform();			// プラットフォーム描写
		void	DrawEffect();			// エフェクト描写
		void	DrawEffectItem();		// アイテム(実体なし)描写
		void	DrawPickUpItem();		// アイテム(実体あり)描写

		/* リスト内オブジェクトコリジョン描写 */
		void	DrawAll_Collision();		// 全オブジェクトコリジョン描写
		void	DrawPlayer_Collision();		// プレイヤーコリジョン描写
		void	DrawSkySqhere_Collision();	// スカイスフィアコリジョン描写
		void	DrawEnemy_Collision();		// エネミーコリジョン描写
		void	DrawBullet_Collision();		// 弾コリジョン描写
		void	DrawPlatform_Collision();	// プラットフォームコリジョン描写
		void	DrawEffectItem_Collision();	// アイテム(実体なし)コリジョン描写
		void	DrawPickUpItem_Collision();	// アイテム(実体あり)コリジョン描写

		/* リスト内オブジェクト発光描写 */
		void	DrawAll_Bloom();		// 全オブジェクト発光描写
		void	DrawPlayer_Bloom();		// プレイヤー発光描写
		void	DrawSkySqhere_Bloom();	// スカイスフィア発光描写
		void	DrawEnemy_Bloom();		// エネミー発光描写
		void	DrawBullet_Bloom();		// 弾発光描写
		void	DrawPlatform_Bloom();	// プラットフォーム発光描写
		void	DrawEffectItem_Bloom();	// アイテム(実体なし)発光描写
		void	DrawPickUpItem_Bloom();	// アイテム(実体あり)発光描写		

		/* オブジェクト削除 */
		// ※単独のデータはデストラクタで開放されるため、リストで管理しているデータのみ対象とする。
		void	DeleteAll();			// 削除フラグが有効な全オブジェクト削除
		void	DeleteEnemy();			// 削除フラグが有効なエネミーを削除
		void	DeleteEffect();			// 削除フラグが有効なエフェクトを削除
		void	DeleteBullet();			// 削除フラグが有効な弾を削除
		void	DeletePlatform();		// 削除フラグが有効なプラットフォームを削除
		void	DeleteEffectItem();		// 削除フラグが有効なアイテム(実体なし)を削除
		void	DeletePickUpItem();		// 削除フラグが有効なアイテム(実体あり)を削除

		/* リスト内オブジェクトリセット処理 */
		void	ResetAll();				// 全オブジェクトリセット処理
		void	ResetPlayer();			// プレイヤーリセット処理
		void	ResetSkySqhere();		// スカイスフィアリセット処理
		void	ResetEnemy();			// エネミーリセット処理
		void	ResetEffect();			// エフェクトリセット処理
		void	ResetBullet();			// 弾リセット処理
		void	ResetPlatform();		// プラットフォームリセット処理
		void	ResetEffectItem();		// アイテム(実体なし)リセット処理
		void	ResetPickUpItem();		// アイテム(実体あり)リセット処理
		void	ResetEnemySpawnPoint();	// エネミースポナーリセット処理

		/* データ取得 */
		// 単独
		CharacterBase* GetCharacterPlayer()	{ return this->pCharacterPlayer; }	// プレイヤー取得
		SkySqhereBase* GetSkySqhere()		{ return this->pSkySqhere; }		// スカイスフィア取得

		// リスト
		std::vector<Enemy_Basic*>&			GetEnemyList()				{ return this->pEnemyList; }			// エネミー取得
		std::vector<EffectBase*>&			GetEffectList()				{ return this->pEffectList; }			// エフェクト取得
		std::vector<BulletBase*>&			GetBulletList()				{ return this->pBulletList; }			// 弾取得
		std::vector<PlatformBase*>&			GetCollisionList()			{ return this->pPlatformList; }			// プラットフォーム
		std::vector<EffectItemBase*>&		GetEffectItemList()			{ return this->pEffectItemList; }		// アイテム(実体なし)
		std::vector<PickUpItemBase*>&		GetPickUpItemList()			{ return this->pPickUpItemList; }		// アイテム(実体あり)
		std::vector<EnemySpawnPoint_Base*>&	GetEnemySpawnPointList()	{ return this->pEnemySpawnPointList; }	// エネミースポーンポイント
		
		/* データ設定 */
		// 単独
		void	SetCharacterPlayer(CharacterBase* pCharacter)	{ this->pCharacterPlayer	= pCharacter; }		// プレイヤー設定
		void	SetSkySqhere(SkySqhereBase* pSkySqhere)			{ this->pSkySqhere			= pSkySqhere; }		// スカイスフィア設定

		// リスト
		void	SetEnemy(Enemy_Basic* pEnemy)								{ pEnemyList.emplace_back(pEnemy); };						// エネミー追加
		void	SetEffect(EffectBase* pEffect)								{ pEffectList.emplace_back(pEffect); };						// エフェクト追加
		void	SetBullet(BulletBase* pBullet)								{ pBulletList.emplace_back(pBullet); };						// 弾追加
		void	SetPlatform(PlatformBase* pPlatform)						{ pPlatformList.emplace_back(pPlatform); };					// プラットフォーム追加
		void	SetEffectItem(EffectItemBase* pEffectItem)					{ pEffectItemList.emplace_back(pEffectItem); };				// アイテム(実体なし)追加
		void	SetPickUpItem(PickUpItemBase* pPickUpItem)					{ pPickUpItemList.emplace_back(pPickUpItem); };				// アイテム(実体なし)追加
		void	SetEnemySpawnPoint(EnemySpawnPoint_Base* pEnemySpawnPoint)	{ pEnemySpawnPointList.emplace_back(pEnemySpawnPoint); };	// エネミースポーンポイント追加

	private:
		/* 管理するデータ */
		// 単独
		CharacterBase*					pCharacterPlayer;	// プレイヤー
		SkySqhereBase*					pSkySqhere;			// スカイスフィア

		// リスト
		std::vector<Enemy_Basic*>			pEnemyList;				// エネミー
		std::vector<EffectBase*>			pEffectList;			// エフェクト
		std::vector<BulletBase*>			pBulletList;			// 弾
		std::vector<PlatformBase*>			pPlatformList;			// プラットフォーム
		std::vector<EffectItemBase*>		pEffectItemList;		// アイテム(実体なし)
		std::vector<PickUpItemBase*>		pPickUpItemList;		// アイテム(実体あり)
		std::vector<EnemySpawnPoint_Base*>	pEnemySpawnPointList;	// エネミースポーンポイント
};
