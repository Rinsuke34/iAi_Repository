/* 2024.01.07 駒沢風助 ファイル作成 */

#include "PlatformBasic.h"

/* 基本プラットフォームクラスの宣言 */

// コンストラクタ
PlatformBasic::PlatformBasic() : PlatformBase()
{

}

// デストラクタ
PlatformBasic::~PlatformBasic()
{

}

// 初期化
void PlatformBasic::Initialization()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル回転 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotate);

	/* モデル拡大 */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* コリジョンフレーム番号取得 */
	//this->SetCollisionFrameNo(MV1SearchFrame(this->iModelHandle, "Collision"));
	this->SetCollisionFrameNo(-1);

	/* コリジョン情報構築 */
	MV1SetupCollInfo(this->iModelHandle, this->iGetCollisionFrameNo(), 4, 4, 4);
}

// 描写
void PlatformBasic::Draw()
{
	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);
}