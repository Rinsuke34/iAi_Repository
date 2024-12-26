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

		void	JsonDataLoad();			// Jsonからデータをロード"※仮作成"

		/* リスト内オブジェクト更新 */
		void	UpdateAll();			// 全オブジェクト更新
		void	UpdatePlayer();			// プレイヤー更新
		void	UpdateEnemy();			// エネミー更新
		void	UpdateBullet();			// 弾更新
		void	UpdatePlatform();		// プラットフォーム更新

		/* リスト内オブジェクト描写 */
		void	DrawAll();				// 全オブジェクト描写
		void	DrawPlayer();			// プレイヤー描写
		void	DrawEnemy();			// エネミー描写
		void	DrawBullet();			// 弾描写
		void	DrawPlatform();			// プラットフォーム描写

		/* データ取得 */
		CharacterBase* GetCharacterPlayer()	{ return this->pCharacterPlayer; }	// プレイヤー取得
		
		/* データ設定 */
		// 単独
		void	SetCharacterPlayer(CharacterBase* pCharacter)	{ this->pCharacterPlayer = pCharacter; }	// プレイヤー設定

		// リスト
		void	SetEnemy(EnemyBase* pEnemy)				{ pEnemyList.emplace_back(pEnemy); };			// エネミー追加
		void	SetBullet(BulletBase* pBullet)			{ pBulletList.emplace_back(pBullet); };			// 弾追加
		void	SetPlatform(PlatformBase* pPlatform)	{ pPlatformList.emplace_back(pPlatform); };		// プラットフォーム追加

	private:
		/* 管理するデータ */
		// 単独
		CharacterBase*					pCharacterPlayer;	// プレイヤー

		// リスト
		std::vector<EnemyBase*>			pEnemyList;			// エネミー
		std::vector<BulletBase*>		pBulletList;		// 弾
		std::vector<PlatformBase*>		pPlatformList;		// プラットフォーム

	protected:
};
