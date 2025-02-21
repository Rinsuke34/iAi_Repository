/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>
#include <vector>
#include <algorithm>
#include "AppStructDefine.h"
#include "AppFunctionDefine.h"

/* すべてのオブジェクトのベースとなるクラスの宣言 */

// オブジェクトベースクラス
class ObjectBase
{
	public:
		ObjectBase();					// コンストラクタ
		virtual ~ObjectBase() {};		// デストラクタ

		virtual void	Initialization()	{};	// 初期化
		virtual void	Update()			{};	// 更新
		virtual void	Draw()				{};	// 描写
		virtual void	BloomDraw()			{};	// 発光描写
		virtual void	CollisionDraw()		{};	// 当たり判定描写


		bool	bGetDeleteFlg()		{ return this->bDeleteFlg; };		// 削除フラグを取得
		VECTOR	vecGetPosition()	{ return this->vecPosition; };		// 座標を取得
		VECTOR	vecGetRotation()	{ return this->vecRotation; };		// オブジェクトの回転量を取得
		VECTOR	vecGetScale()		{ return this->vecScale; };			// オブジェクト拡大率を取得

		void	SetDeleteFlg(bool bDeleteFlg)		{ this->bDeleteFlg	= bDeleteFlg; };	// 削除フラグを設定
		void	SetPosition(VECTOR vecPostion)		{ this->vecPosition	= vecPostion; };	// オブジェクトの座標を設定
		void	SetRotation(VECTOR vecRotation)		{ this->vecRotation = vecRotation; };	// オブジェクトの向きを設定
		void	SetScale(VECTOR vecScale)			{ this->vecScale	= vecScale; };		// オブジェクトの拡大率を設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		bool	bDeleteFlg;				// 削除フラグ(有効ならオブジェクトを削除)
		VECTOR	vecPosition;			// オブジェクトの座標
		VECTOR	vecRotation;			// オブジェクトの回転量
		VECTOR	vecScale;				// オブジェクトの拡大率(x,y,z方向それぞれの拡大倍率)
};
