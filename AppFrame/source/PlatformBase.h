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
		virtual void	Draw();								// 描写
		virtual void	BloomDraw();						// 発光描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// モデル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// モデル - 球体
		bool	HitCheck(COLLISION_LINE		stLine);			// モデル - 線分
		// 詳細な結果(接触ポリゴン数、接触位置など)
		MV1_COLL_RESULT_POLY	HitCheck_Line(COLLISION_LINE	stLine);	// モデル - 線分

		int		iGetModelHandle()		{ return this->iModelHandle; };			// モデルハンドルを取得
		VECTOR	vecGetRotate()			{ return this->vecRotate; };			// 回転量を取得
		VECTOR	vecGetScale()			{ return this->vecScale; };				// 拡大率を取得

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// モデルハンドルを設定
		void	SetRotate(VECTOR vecRotate)					{ this->vecRotate			= vecRotate; };				// 回転量を設定
		void	SetScale(VECTOR vecScale)					{ this->vecScale			= vecScale; };				// 拡大率を設定

	private:
	protected:
		/* 関数 */
		void	UpdataLightFrame();						// 発光の設定されたフレームを取得
		void	UpdateCollisionFrame();					// コリジョンの設定されたフレームの設定

		/* 変数 */
		int						iModelHandle;			// モデルハンドル
		int						iCollisionFrameNo;		// コリジョンフレーム番号(※モデルにつき1つだけ)
		std::vector<int>		aiLightFrameNo;			// 発光フレーム番号
		VECTOR					vecRotate;				// 回転量(x,y,z方向それぞれのラジアン)
		VECTOR					vecScale;				// 拡大率(x,y,z方向それぞれの拡大倍率)
};
