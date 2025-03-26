/* 2025.03.27 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"
#include "GimmickDefine.h"

/* データリスト */
#include "DataList_Object.h"

/* シーン */
#include "SceneUi_Tutorial.h"

/* チュートリアル描写地点クラスの宣言 */

// チュートリアル描写地点クラス
class Gimmick_TutorialDraw : public PlatformBase
{
	public:
		Gimmick_TutorialDraw();					// コンストラクタ
		virtual ~Gimmick_TutorialDraw() {};		// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Update()			override;		// 更新
		virtual void	Draw()				override {};	// 描写
		virtual void	BloomDraw()			override {};	// 発光描写
		virtual void	CollisionDraw()		override;		// 当たり判定描写

		/* データ設定 */
		void SetDrawTutorialNo(int iDrawTutorialNo)	{ this->iDrawTutorialNo	=	iDrawTutorialNo; };		// 描写するチュートリアル番号を設定

		/* データ取得 */
		int iGetDrawTutorialNo()					{ return this->iDrawTutorialNo; };					// 描写するチュートリアル番号を取得

	private:
		/* 使用するデータリスト */
		DataList_Object* ObjectList;	// オブジェクト管理

		/* 変数 */
		int					iDrawTutorialNo;	// 描写するチュートリアル番号
		COLLISION_SQHERE	stCollisionSqhere;	// 当たり判定(球体)
};
