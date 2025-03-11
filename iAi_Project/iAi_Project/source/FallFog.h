/* 2025.03.03 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* 霧(落下位置)クラスの宣言 */

// 霧(落下位置)クラス
class FallFog : public PlatformBase
{
	public:
		FallFog();				// コンストラクタ
		virtual ~FallFog() {};	// デストラクタ

		void	Initialization()	override;		// 初期化
		void	Draw()				override;		// 描写
		void	BloomDraw()			override {};	// 発光描写

	private:
		/* 使用する画像のハンドル */
		int* piGrHandle_Fog;		// 霧
};
