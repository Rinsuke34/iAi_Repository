/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "ObjectBase.h"

/* 名前空間省略 */
using namespace Struct_Collision;

/* すべてのプラットフォームのベースとなるクラスの宣言 */

// プラットフォームベースクラス
class PlatformBase : public ObjectBase
{
	public:
		PlatformBase();				// コンストラクタ
		virtual ~PlatformBase();	// デストラクタ

		virtual void	Draw() {};	// 描写

		/* 接触判定 */
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// モデル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// モデル - 球体

		int		iGetModelHandle() { return this->iModelHandle; };		// モデルハンドルを取得

		void	SetModelHandle(int iModelHandle) { this->iModelHandle = iModelHandle; };	// モデルハンドルを設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int		iModelHandle;		// モデルハンドル
		int		iCollisionFrameNo;	// コリジョンの設定されたモデルのフレーム番号	
		VECTOR	vecRotate;		// 回転
		VECTOR	vecScale;		// 拡大
};
