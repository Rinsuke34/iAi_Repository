/* 2025.02.06 駒沢風助 ファイル作成 */

#include "SkySqhereBase.h"

/* すべてのスカイスフィア(空として描写する球体)のベースとなるクラスの定義 */
// コンストラクタ
SkySqhereBase::SkySqhereBase() : ObjectBase()
{
	/* 初期化 */
	this->iModelHandle = 0;					// モデルハンドル
}

// デストラクタ
SkySqhereBase::~SkySqhereBase()
{
	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}

// 初期化
void SkySqhereBase::Initialization()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* モデル拡大 */
	MV1SetScale(this->iModelHandle, this->vecScale);
}

// 描写
void SkySqhereBase::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}
