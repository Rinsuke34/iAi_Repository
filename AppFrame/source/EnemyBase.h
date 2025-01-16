/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "CharacterBase.h"

/* すべてのエネミーのベースとなるクラスの宣言 */

// エネミーベースクラス
class EnemyBase : public CharacterBase
{
	public:
		EnemyBase();				// コンストラクタ
		virtual ~EnemyBase() {};	// デストラクタ

		virtual void	Initialization()	override {};	// 初期化
		virtual void	Update()			override {};	// 更新
		virtual void	Draw()				override {};	// 描写
		virtual void	BloomDraw()			override {};	// 発光描写

		int		iGetMaxHP()	{ return this->iMaxHp; };		// 最大HPを取得
		int		iGetNowHP()	{ return this->iNowHP; };		// 現在HPを取得

		void	SetMaxHP(int iMaxHp)	{ this->iMaxHp = iMaxHp; };		// 最大HPを設定
		void	SetNowHP(int iNowHP)	{ this->iNowHP = iNowHP; };		// 現在HPを設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int		iMaxHp;			// 最大HP
		int		iNowHP;			// 現在HP
};
