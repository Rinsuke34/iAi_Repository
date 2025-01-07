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

		int		iGetModelHandle()		{ return this->iModelHandle; };			// モデルハンドルを取得
		int		iGetCollisionFrameNo()	{ return this->iCollisionFrameNo; };	// コリジョンの設定されたモデルのフレーム番号を取得
		VECTOR	vecGetRotate()			{ return this->vecRotate; };			// 回転を取得
		VECTOR	vecGetScale()			{ return this->vecScale; };				// 拡大を取得

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// モデルハンドルを設定
		void	SetCollisionFrameNo(int iCollisionFrameNo)	{ this->iCollisionFrameNo	= iCollisionFrameNo; };		// コリジョンの設定されたモデルのフレーム番号を設定
		void	SetRotate(VECTOR vecRotate)					{ this->vecRotate			= vecRotate; };				// 回転を設定
		void	SetScale(VECTOR vecScale)					{ this->vecScale			= vecScale; };				// 拡大を設定

	private:
	protected:
		/* 関数 */

		/* 変数 */
		int		iModelHandle;		// モデルハンドル
		int		iCollisionFrameNo;	// コリジョンの設定されたモデルのフレーム番号	
		VECTOR	vecRotate;			// 回転
		VECTOR	vecScale;			// 拡大
};
