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

		virtual void	Initialization()	{};		// 初期化
		virtual void	Update()			{};		// 更新
		virtual void	Draw()				{};		// 描写

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// モデル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// モデル - 球体
		bool	HitCheck(COLLISION_LINE		stLine);			// モデル - 線分
		// 詳細な結果(接触ポリゴン数、接触位置など)
		MV1_COLL_RESULT_POLY	HitCheck_Line(COLLISION_LINE	stLine);	// モデル - 線分

		int		iGetModelHandle()		{ return this->iModelHandle; };			// モデルハンドルを取得
		int		iGetCollisionFrameNo()	{ return this->iCollisionFrameNo; };	// コリジョンの設定されたモデルのフレーム番号を取得
		int		iGetLightHandle()		{ return this->iLightFrameNo; };		// 発光部分の設定されたモデルのフレーム番号を取得
		VECTOR	vecGetRotate()			{ return this->vecRotate; };			// 回転を取得
		VECTOR	vecGetScale()			{ return this->vecScale; };				// 拡大を取得

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// モデルハンドルを設定
		void	SetCollisionFrameNo(int iCollisionFrameNo)	{ this->iCollisionFrameNo	= iCollisionFrameNo; };		// コリジョンの設定されたモデルのフレーム番号を設定
		void	SetLightHandle(int iLightFrameNo)			{ this->iLightFrameNo		= iLightFrameNo; };			// 発光部分の設定されたモデルのフレーム番号を設定
		void	SetRotate(VECTOR vecRotate)					{ this->vecRotate			= vecRotate; };				// 回転を設定
		void	SetScale(VECTOR vecScale)					{ this->vecScale			= vecScale; };				// 拡大を設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int		iModelHandle;		// モデルハンドル
		int		iCollisionFrameNo;	// コリジョンの設定されたモデルのフレーム番号	
		int		iLightFrameNo;		// 発光部分の設定されたモデルのフレーム番号
		VECTOR	vecRotate;			// 回転
		VECTOR	vecScale;			// 拡大
};
