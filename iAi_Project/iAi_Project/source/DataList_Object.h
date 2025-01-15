/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <vector>

/* オブジェクト管理クラスの宣言 */

// オブジェクト管理クラス
class DataList_Object : public DataListBase
{
	public:
		DataList_Object();				// コンストラクタ
		virtual ~DataList_Object();		// デストラクタ

		/* リスト内オブジェクト初期化 */
		void	InitializationAll();		// 全オブジェクト初期化
		void	InitializationPlayer();		// プレイヤー初期化
		void	InitializationEnemy();		// エネミー初期化
		void	InitializationEffect();		// エフェクト初期化
		void	InitializationBullet();		// 弾初期化
		void	InitializationPlatform();	// プラットフォーム初期化

		/* リスト内オブジェクト更新 */
		void	UpdateAll();			// 全オブジェクト更新
		void	UpdatePlayer();			// プレイヤー更新
		void	UpdateEnemy();			// エネミー更新
		void	UpdateEffect();			// エフェクト更新
		void	UpdateBullet();			// 弾更新
		void	UpdatePlatform();		// プラットフォーム更新

		/* リスト内オブジェクト描写 */
		void	DrawAll();				// 全オブジェクト描写
		void	DrawPlayer();			// プレイヤー描写
		void	DrawEnemy();			// エネミー描写
		void	DrawBullet();			// 弾描写
		void	DrawPlatform();			// プラットフォーム描写

		/* リスト内オブジェクト発光描写 */
		void	BloomDrawAll();			// 全オブジェクト発光描写
		void	BloomDrawPlayer();		// プレイヤー発光描写
		void	BloomDrawEnemy();		// エネミー発光描写
		void	BloomDrawBullet();		// 弾発光描写
		void	BloomDrawPlatform();	// プラットフォーム発光描写

		/* オブジェクト削除 */
		void	DeleteAll();			// 削除フラグが有効な全オブジェクト削除
		void	DeleteEnemy();			// 削除フラグが有効なエネミーを削除
		void	DeleteEffect();			// 削除フラグが有効なエフェクトを削除
		void	DeleteBullet();			// 削除フラグが有効な弾を削除
		void	DeletePlatform();		// 削除フラグが有効なプラットフォームを削除

		/* データ取得 */
		// 単独
		CharacterBase* GetCharacterPlayer()	{ return this->pCharacterPlayer; }	// プレイヤー取得

		// リスト
		std::vector<EnemyBase*>&	GetEnemyList()		{ return this->pEnemyList; }		// エネミー取得
		std::vector<EffectBase*>&	GetEffectList()		{ return this->pEffectList; }		// エフェクト取得
		std::vector<BulletBase*>&	GetBulletList()		{ return this->pBulletList; }		// 弾取得
		std::vector<PlatformBase*>&	GetPlatformList()	{ return this->pPlatformList; }		// プラットフォーム取得
		
		/* データ設定 */
		// 単独
		void	SetCharacterPlayer(CharacterBase* pCharacter)	{ this->pCharacterPlayer = pCharacter; }	// プレイヤー設定

		// リスト
		void	SetEnemy(EnemyBase* pEnemy)				{ pEnemyList.emplace_back(pEnemy); };			// エネミー追加
		void	SetEffect(EffectBase* pEffect)			{ pEffectList.emplace_back(pEffect); };			// エフェクト追加
		void	SetBullet(BulletBase* pBullet)			{ pBulletList.emplace_back(pBullet); };			// 弾追加
		void	SetPlatform(PlatformBase* pPlatform)	{ pPlatformList.emplace_back(pPlatform); };		// プラットフォーム追加

	private:
		/* 管理するデータ */
		// 単独
		CharacterBase*					pCharacterPlayer;	// プレイヤー

		// リスト
		std::vector<EnemyBase*>			pEnemyList;			// エネミー
		std::vector<EffectBase*>		pEffectList;		// エフェクト
		std::vector<BulletBase*>		pBulletList;		// 弾
		std::vector<PlatformBase*>		pPlatformList;		// プラットフォーム

	protected:
};
