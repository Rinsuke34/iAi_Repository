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

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override	{};	// 更新

		int		iGetModelHandle()		{ return this->iModelHandle; };			// モデルハンドルを取得
		VECTOR	vecGetRotate()			{ return this->vecRotate; };			// 回転量を取得
		VECTOR	vecGetScale()			{ return this->vecScale; };				// 拡大率を取得

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// モデルハンドルを設定
		void	SetRotate(VECTOR vecRotate)					{ this->vecRotate			= vecRotate; };				// 回転量を設定
		void	SetScale(VECTOR vecScale)					{ this->vecScale			= vecScale; };				// 拡大率を設定

	private:
	protected:
		/* 変数 */
		int						iModelHandle;			// モデルハンドル
		VECTOR					vecRotate;				// 回転量(x,y,z方向それぞれのラジアン)
		VECTOR					vecScale;				// 拡大率(x,y,z方向それぞれの拡大倍率)
};
