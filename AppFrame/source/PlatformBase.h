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
		virtual void	Draw();								// 描写
		virtual void	BloomDraw();						// 発光描写
		virtual void	CollisionDraw();					// 当たり判定描写

		int		iGetModelHandle()		{ return this->iModelHandle; };			// モデルハンドルを取得
		VECTOR	vecGetPlatformMove()	{ return this->vecPlatformMove; };		// プラットフォームの移動量を取得
		bool	bGetRidePlayerFlg()		{ return this->bRidePlayerFlg; };		// プレイヤーが乗っているかのフラグ

		void	SetModelHandle(int iModelHandle)			{ this->iModelHandle		= iModelHandle; };			// モデルハンドルを設定
		void	SetPlatformMove(VECTOR vecPlatformMove)		{ this->vecPlatformMove		= vecPlatformMove; };		// プラットフォームの移動量を設定
		void	SetRidePlayerFlg(bool bRidePlayerFlg)		{ this->bRidePlayerFlg		= bRidePlayerFlg; };		// プレイヤーが乗っているかのフラグを設定

		/* 接触判定 */
		// 簡易的な結果(接触しているかどうか)
		bool	HitCheck(COLLISION_CAPSULE	stCapsule);			// モデル - カプセル
		bool	HitCheck(COLLISION_SQHERE	stSqhere);			// モデル - 球体
		bool	HitCheck(COLLISION_LINE		stLine);			// モデル - 線分
		// 詳細な結果(接触ポリゴン数、接触位置など)
		MV1_COLL_RESULT_POLY		HitCheck_Line(COLLISION_LINE		stLine);	// モデル - 線分
		MV1_COLL_RESULT_POLY_DIM	HitCheck_Capsule(COLLISION_CAPSULE	stCapsule);	// モデル - カプセル

	private:
	protected:
		/* 関数 */
		void	UpdateCollisionFrame();						// コリジョンの設定されたフレームの設定
		void	UpdataLightFrame();							// 発光の設定されたフレームを取得
		void	DrawFrameCollisionSet(bool bCollisionDraw);	// コリジョンフレームを描写する状態にする

		/* 変数 */
		int						iModelHandle;			// モデルハンドル
		std::vector<int>		aiLightFrameNo;			// 発光フレーム番号
		int						iCollisionFrameNo;		// コリジョンフレーム番号(※モデルにつき1つだけ)
		VECTOR					vecCenterPosition;		// オブジェクトの中心座標(コリジョン処理軽量化用)
		float					fRoughRadius;			// オブジェクトの大まかな半径(コリジョン処理軽量化用)
		VECTOR					vecPlatformMove;		// プラットフォームの移動量
		bool					bRidePlayerFlg;			// プレイヤーが乗っているかのフラグ
};
