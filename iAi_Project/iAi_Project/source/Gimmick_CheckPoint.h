/* 2025.03.16 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* データリスト */
#include "DataList_Object.h"
#include "DataList_Image.h"

/* 中間ポイントクラスの宣言 */

// 中間ポイントクラス
class Gimmick_CheckPoint : public PlatformBase
{
	public:
		Gimmick_CheckPoint();					// コンストラクタ
		virtual ~Gimmick_CheckPoint()	{};		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Reset()				override;		// リセット
		virtual void	BloomDraw()			override;		// 発光描写
		virtual void	CollisionDraw()		override;		// 当たり判定描写

		/* データ設定 */
		void SetActiveFlg(bool bActiveFlg)					{ this->bActiveFlg			= bActiveFlg; };		// アクティブフラグを設定
		void SetStartPositionFlg(bool bStartPositionFlg)	{ this->bStartPositionFlg	= bStartPositionFlg; };	// スタート地点フラグを設定

		/* データ取得 */
		bool bGetActiveFlg()				{ return this->bActiveFlg; };			// アクティブフラグを取得
		bool bGetStartPositionFlg()			{ return this->bStartPositionFlg; };	// スタート地点フラグを取得

	private:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;	// オブジェクト管理

		/* 使用する画像のハンドル */
		int* piGrHandle_NormalRight;			// 通常時(非アクティブ時)の発光色
		int* piGrHandle_ActiveRight;			// アクティブ時の発光色

		/* 変数 */
		bool				bActiveFlg;			// アクティブフラグ(有効ならチェックポイントとして機能)
		bool				bStartPositionFlg;	// スタート地点フラグ(有効ならスタート地点として機能)
		COLLISION_SQHERE	stCollisionSqhere;	// 当たり判定(球体)
};