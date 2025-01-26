/* 2024.12.15 駒沢風助 ファイル作成 */

#include "PlatformBase.h"

/* すべてのプラットフォームのベースとなるクラスの定義 */

// コンストラクタ
PlatformBase::PlatformBase() : ObjectBase()
{
	/* 初期化 */
	this->iModelHandle		= 0;					// モデルハンドル
	this->vecRotation			= VGet(0.f, 0.f, 0.f);	// 回転量
	this->vecScale			= VGet(1.f, 1.f, 1.f);	// 拡大率
}

// デストラクタ
PlatformBase::~PlatformBase()
{
	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}

// 初期化
void PlatformBase::Initialization()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* モデル拡大 */
	MV1SetScale(this->iModelHandle, this->vecScale);
}
