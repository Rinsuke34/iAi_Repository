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

		virtual void	Initialization()		{};	// 初期化
		virtual void	Update()				{};	// 更新
		virtual void	Draw()					{};	// 描写
		virtual void	BloomDraw()				{};	// 発光描写
		virtual void	CollisionDraw()			{};	// 当たり判定描写
		virtual void	Reset()					{};	// リセット処理
		virtual void	SetupInitialPosition();		// 初期位置設定

		bool	bGetDeleteFlg()				{ return this->bDeleteFlg; };			// 削除フラグを取得
		VECTOR	vecGetPosition()			{ return this->vecPosition; };			// 座標を取得
		VECTOR	vecGetRotation()			{ return this->vecRotation; };			// オブジェクトの回転量を取得
		VECTOR	vecGetScale()				{ return this->vecScale; };				// オブジェクト拡大率を取得
		VECTOR	vecGetPosition_Initial()	{ return this->vecPosition_Initial; };	// 初期状態でのオブジェクトの座標を取得
		VECTOR	vecGetRotation_Initial()	{ return this->vecRotation_Initial; };	// 初期状態でのオブジェクトの回転量を取得
		VECTOR	vecGetScale_Initial()		{ return this->vecScale_Initial; };		// 初期状態でのオブジェクトの拡大率を取得
		bool	bGetBloomStopFlg()			{ return this->bBloomStopFlg; };		// 発光停止フラグを取得
		bool	bGetSpBloomCollorFlg()		{ return this->bSpBloomCollorFlg; };	// 特殊発光色使用フラグを取得
		COLOR_F stGetSpBloomColor()			{ return this->stSpBloomColor; };		// 特殊発光色を取得

		void	SetDeleteFlg(bool bDeleteFlg)					{ this->bDeleteFlg			= bDeleteFlg; };			// 削除フラグを設定
		void	SetPosition(VECTOR vecPostion)					{ this->vecPosition			= vecPostion; };			// オブジェクトの座標を設定
		void	SetRotation(VECTOR vecRotation)					{ this->vecRotation			= vecRotation; };			// オブジェクトの向きを設定
		void	SetScale(VECTOR vecScale)						{ this->vecScale			= vecScale; };				// オブジェクトの拡大率を設定
		void	SetPosition_Initial(VECTOR vecPostion_Initial)	{ this->vecPosition_Initial	= vecPostion_Initial; };	// 初期状態でのオブジェクトの座標を設定
		void	SetRotation_Initial(VECTOR vecRotation_Initial)	{ this->vecRotation_Initial	= vecRotation_Initial; };	// 初期状態でのオブジェクトの向きを設定
		void	SetScale_Initial(VECTOR vecScale_Initial)		{ this->vecScale_Initial	= vecScale_Initial; };		// 初期状態でのオブジェクトの拡大率を設定
		void	SetBloomStopFlg(bool bBloomStopFlg)				{ this->bBloomStopFlg		= bBloomStopFlg; };			// 発光停止フラグを設定
		void	SetSpBloomCollorFlg(bool bSpBloomCollorFlg)		{ this->bSpBloomCollorFlg	= bSpBloomCollorFlg;};		// 特殊発光色仕様フラグを設定
		void	SetSpBloomColor(COLOR_F stSpBloomColor)			{ this->stSpBloomColor		= stSpBloomColor; };		// 特殊発光色を設定

	protected:
		/* 変数 */
		bool	bDeleteFlg;				// 削除フラグ(有効ならオブジェクトを削除)
		VECTOR	vecPosition;			// オブジェクトの座標
		VECTOR	vecRotation;			// オブジェクトの回転量
		VECTOR	vecScale;				// オブジェクトの拡大率(x,y,z方向それぞれの拡大倍率)
		VECTOR	vecPosition_Initial;	// 初期状態でのオブジェクトの座標
		VECTOR	vecRotation_Initial;	// 初期状態でのオブジェクトの回転量
		VECTOR	vecScale_Initial;		// 初期状態でのオブジェクトの拡大率(x,y,z方向それぞれの拡大倍率)
		bool	bBloomStopFlg;			// 発光停止フラグ
		bool	bSpBloomCollorFlg;		// 特殊発光色仕様フラグ
		COLOR_F stSpBloomColor;			// 特殊発光色
};
