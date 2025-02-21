/* 2025.02.06 駒沢風助 ファイル作成 */

#pragma once
#include "ObjectBase.h"

/* すべてのスカイスフィア(空として描写する球体)のベースとなるクラスの宣言 */

// スカイスフィアベースクラス
class SkySqhereBase : public ObjectBase
{
	public:
		SkySqhereBase();				// コンストラクタ
		virtual ~SkySqhereBase();	// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Draw()				override;	// 描写

		int		iGetModelHandle()					{ return this->iModelHandle; };				// モデルハンドルを取得

		void	SetModelHandle(int iModelHandle)	{ this->iModelHandle = iModelHandle; };		// モデルハンドルを設定

	private:
	protected:
		/* 変数 */
		int						iModelHandle;			// モデルハンドル
};
