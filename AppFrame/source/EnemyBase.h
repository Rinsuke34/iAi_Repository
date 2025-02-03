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

		int		iGetMaxHP()				{ return this->iMaxHp; }			// 最大HPを取得
		int		iGetNowHP()				{ return this->iNowHp; }			// 現在HPを取得

		void	SetMaxHP(int iMaxHp)						{ this->iMaxHp				= iMaxHp; }					// 最大HPを設定
		void	SetNowHP(int iNowHP)						{ this->iNowHp				= iNowHP; }					// 現在HPを設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int		iMaxHp;				// 最大HP
		int		iNowHp;				// 現在HP
};
