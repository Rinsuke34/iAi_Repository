/* 2025.01.22 駒沢風助 ファイル作成 */

#pragma once
#include "PlatformBase.h"

/* 名前空間省略 */
using namespace Struct_Collision;

/* すべての描写モデルのベースとなるクラスの宣言 */
// ※デザイナーの負担対策にコリジョン用と描写用でモデルを分ける

// 描写モデルベースクラス
class BackGroundBase : public PlatformBase
{
	public:
		BackGroundBase();			// コンストラクタ
		virtual ~BackGroundBase() {};	// デストラクタ

		virtual void	Initialization()	override;		// 初期化
		virtual void	Draw();								// 描写
		virtual void	BloomDraw();						// 発光描写

	private:
	protected:
		/* 関数 */
		void	UpdataLightFrame();						// 発光の設定されたフレームを取得

		/* 変数 */
		std::vector<int>		aiLightFrameNo;			// 発光フレーム番号
};
