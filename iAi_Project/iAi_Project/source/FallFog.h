/* 2025.03.03 駒沢風助 ファイル作成 */

#pragma once
#include "Appframe.h"

/* データリスト */
#include "DataList_Object.h"

/* オブジェクト */
#include "PlatformBasic.h"

/* 霧(落下位置)クラスの宣言 */

// 霧(落下位置)クラス
class FallFog : public PlatformBasic
{
	public:
		FallFog();				// コンストラクタ
		virtual ~FallFog() {};	// デストラクタ

		virtual void	Draw()				override;	// 描写

	private:
		/* 使用する画像のハンドル */
		int* piGrHandle_Fog;		// 霧
};
