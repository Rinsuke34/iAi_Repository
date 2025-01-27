/* 2025.01.27 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "PublicInclude.h"

/* 基本エネミークラスの宣言 */

// 基本エネミークラス
class EnemyBasic : public EnemyBase
{
	public:
		EnemyBasic();				// コンストラクタ
		virtual ~EnemyBasic() {};	// デストラクタ

		int		iGetPlayerLockOnType()	{ return this->iPlayerLockOnType; }		// プレイヤー視点でのロックオン状態を取得

		void	SetPlayerLockOnType(int iPlayerLockOnType)	{ this->iPlayerLockOnType = iPlayerLockOnType; }	// プレイヤー視点でのロックオン状態を設定

	private:
	protected:
		/* 変数 */
		int		iPlayerLockOnType;	// プレイヤー視点でのロックオン状態
};
