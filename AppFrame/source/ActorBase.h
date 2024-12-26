/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include "ObjectBase.h"

/* すべてのアクタのベースとなるクラスの宣言 */

// アクタベースクラス
class ActorBase : public ObjectBase
{
	public:
		ActorBase();			// コンストラクタ
		virtual ~ActorBase();	// デストラクタ

		virtual void	Update() {};	// 更新
		virtual void	Draw() {};		// 描写

		VECTOR	vecGetMovement()	{ return this->vecMovement; };		// 移動量を取得
		int		iGetModelHandle()	{ return this->iModelHandle; };		// モデルハンドルを取得

		void	SetMovement(VECTOR vecMovement)		{ this->vecMovement		= vecMovement; };	// 移動量を設定
		void	SetModelHandle(int iModelHandle)	{ this->iModelHandle	= iModelHandle; };	// モデルハンドルを設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		VECTOR	vecMovement;	// 移動量
		int		iModelHandle;	// モデルハンドル
};
