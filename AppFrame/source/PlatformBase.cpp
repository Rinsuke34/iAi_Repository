/* 2024.12.15 駒沢風助 ファイル作成 */

#include "PlatformBase.h"

/* すべてのプラットフォームのベースとなるクラスの定義 */

// コンストラクタ
PlatformBase::PlatformBase() : ObjectBase()
{
	/* 初期化 */
	this->iModelHandle = -1;	// モデルハンドル
}

// デストラクタ
PlatformBase::~PlatformBase()
{
	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}
