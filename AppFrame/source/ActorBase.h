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

		virtual void	Initialization()	override	{};	// 初期化
		virtual void	Update()			override	{};	// 更新
		virtual void	Draw()							{};	// 描写
		virtual void	BloomDraw()						{};	// 発光描写

		int		iGetModelHandle()	{ return this->iModelHandle; };		// モデルハンドルを取得
		int		iGetLightFrameNo()	{ return this->iLightFrameNo; };	// 発光部分の設定されたモデルのフレーム番号を取得

		void	SetModelHandle(int iModelHandle)	{ this->iModelHandle	= iModelHandle; };	// モデルハンドルを設定
		void	SetLightFrameNo(int iLightFrameNo)	{ this->iLightFrameNo	= iLightFrameNo; };	// 発光部分の設定されたモデルのフレーム番号を取得

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int		iModelHandle;	// モデルハンドル
		int		iLightFrameNo;	// 発光部分の設定されたモデルのフレーム番号
};
