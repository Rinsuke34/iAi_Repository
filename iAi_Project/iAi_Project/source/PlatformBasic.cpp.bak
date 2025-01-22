/* 2024.01.07 駒沢風助 ファイル作成 */

#include "PlatformBasic.h"

/* 基本プラットフォームクラスの宣言 */

// コンストラクタ
PlatformBasic::PlatformBasic() : PlatformBase()
{
	/* 初期化 */

}

// デストラクタ
PlatformBasic::~PlatformBasic()
{

}

// 描写
void PlatformBasic::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* モデル拡大 */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}