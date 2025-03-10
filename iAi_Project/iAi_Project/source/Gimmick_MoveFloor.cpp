/* 2025.03.10 駒沢風助 ファイル作成 */

#include "Gimmick_MoveFloor.h"

/* 移動床クラスの定義 */
// コンストラクタ
Gimmick_MoveFloor::Gimmick_MoveFloor() : PlatformBase()
{
	/* モデル取得 */
	{
		/* "3Dモデル管理"データリストを取得 */
		// ※一度しか使用しないため、取得したデータリストのハンドルは保持しない
		DataList_Model* ModelListHandle = dynamic_cast<DataList_Model*>(gpDataListServer->GetDataList("DataList_Model"));
		/* モデルハンドル取得 */
		this->iModelHandle = ModelListHandle->iGetModel("Gimmick/MoveFloor/MoveFloor");
	}

	/* 初期化 */
	this->vecMovePos	= VGet(0.f, 0.f, 0.f);		// 移動床の移動先座標
	this->bTargetMove	= true;						// 移動床の移動先座標に向かっているか(true:移動先座標へ / false:初期座標へ)
}

// 更新
void Gimmick_MoveFloor::Update()
{
	/* 現時点での座標を保存 */
	VECTOR vecPositionOld = this->vecPosition;

	/* 移動先座標に向かっているか確認 */
	if (this->bTargetMove)
	{
		// 移動先座標に向かっている場合
		/* 移動方向を算出 */
		VECTOR vecMoveDir = VSub(this->vecMovePos, this->vecPosition);
		float distance = VSize(vecMoveDir);

		/* 目標地点へ到達しているか確認 */
		if (distance <= GIMMICK_MOVEFLOOR_MOVE_SPEED)
		{

			// 到達した場合
			/* 現在の座標を移動後座標に合わせる */
			this->vecPosition = this->vecMovePos;

			/* 移動先座標に向かっていない状態に設定 */
			this->bTargetMove = false;
		}
		else
		{
			// 到達していない場合
			/* 移動を行う */
			this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(vecMoveDir), GIMMICK_MOVEFLOOR_MOVE_SPEED));
		}
	}
	else
	{
		// 初期座標に向かっている場合
		/* 移動方向を算出 */
		VECTOR vecMoveDir = VSub(this->vecPosition_Initial, this->vecPosition);
		float distance = VSize(vecMoveDir);

		/* 目標地点へ到達しているか確認 */
		if (distance <= GIMMICK_MOVEFLOOR_MOVE_SPEED)
		{
			// 到達した場合
			/* 現在の座標を初期座標に合わせる */
			this->vecPosition = this->vecPosition_Initial;

			/* 移動先座標に向かっている状態に設定 */
			this->bTargetMove = true;
		}
		else
		{
			// 到達していない場合
			/* 移動を行う */
			this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(vecMoveDir), GIMMICK_MOVEFLOOR_MOVE_SPEED));
		}
	}

	/* 移動床の移動量を設定 */
	this->vecPlatformMove = VSub(this->vecPosition, vecPositionOld);

	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* コリジョン情報後始末 */
	MV1TerminateCollInfo(this->iModelHandle, this->iCollisionFrameNo);

	/* コリジョン更新 */
	//MV1RefreshCollInfo(this->iModelHandle, this->iCollisionFrameNo, TRUE);

	UpdateCollisionFrame();
}

// 移動方向を設定
void  Gimmick_MoveFloor::SetupMoveDirection(bool bVerticalDirection, int iMoveDistance)
{
	// 引数
	// bVerticalDirection	:	垂直方向に移動するか(true:垂直方向 / false:水平方向)
	// iMoveDistance		:	移動距離(0:短距離 / 1:中距離 / 2長距離)

	/* 移動距離取得 */
	float fMoveDistance = 0.f;

	/* 移動距離タイプに応じた値を設定 */
	switch (iMoveDistance)
	{
		/* 短距離 */
		case GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_SHORT:
			fMoveDistance = GIMMICK_MOVEFLOOR_MOVE_DISTANCE_SHORT;
			break;

		/* 中距離 */
		case GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_NORMAL:
			fMoveDistance = GIMMICK_MOVEFLOOR_MOVE_DISTANCE_NORMAL;
			break;

		/* 長距離 */
		case GIMMICK_MOVEFLOOR_MOVE_DISTANCE_TYPE_LONG:
			fMoveDistance = GIMMICK_MOVEFLOOR_MOVE_DISTANCE_LONG;
			break;
	}

	/* 移動方向を設定 */
	{
		/* 垂直方向 */
		if (bVerticalDirection == true)
		{
			// 垂直方向に移動する場合
			/* 移動先座標を現在座標から上方向へ設定 */
			this->vecMovePos = VGet(this->vecPosition.x, this->vecPosition.y + fMoveDistance, this->vecPosition.z);
		}
		else
		{
			// 水平方向に移動する場合
			/* 現在の横方向の回転量を取得 */
			float fRotationY = this->vecRotation.y;

			/* 移動先座標を取得した回転後の方向になるよう設定 */
			this->vecMovePos = VGet(this->vecPosition.x + fMoveDistance * cosf(fRotationY), this->vecPosition.y, this->vecPosition.z + fMoveDistance * sinf(fRotationY));
		}
	}
}
