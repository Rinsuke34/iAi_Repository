/* 2025.02.11 駒沢風助 ファイル作成 */

#include "EffectItem_Blood.h"

/* ブラッド(ゲーム内通貨)クラスの定義 */
// コンストラクタ
EffectItem_Blood::EffectItem_Blood() : EffectItemBase()
{
	/* データリストを取得 */
	{
		this->ObjectList = dynamic_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
	}

	/* 初期化 */
	{
		this->iMoveCount	= 30;
		this->iMoveFaze		= MOVE_FAZE_RUNDOM;
	}

	/* 移動方向をランダム方向に設定 */
	{
		this->vecMoveDirection = VGet((float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f, (float)(GetRand(100) - 50) / 100.0f);
	}
}

// デストラクタ
EffectItem_Blood::~EffectItem_Blood()
{

}

// 更新
void EffectItem_Blood::Update()
{
	/* 現在のフェーズに応じて処理を変更する */
	switch (this->iMoveFaze)
	{
		/* ランダム方向へ移動 */
		case MOVE_FAZE_RUNDOM:
			/* 移動方向に設定された方向へ移動 */
			this->vecPosition = VAdd(this->vecPosition, VScale(this->vecMoveDirection, MOVE_SPEED_RUNDOM));

			/* 移動カウントが以下になった場合 */
			if (this->iMoveCount < 0)
			{
				/* プレイヤーに向かって移動するフェーズへ移行 */
				this->iMoveFaze = MOVE_FAZE_PLAYER;
			}
			break;

		/* プレイヤーに向かって移動 */
		case MOVE_FAZE_PLAYER:
			/* プレイヤーの中心座標を取得 */
			VECTOR vecPlayerPos = this->ObjectList->GetCharacterPlayer()->vecGetPosition();
			vecPlayerPos.y += PLAYER_HEIGHT / 2;

			/* プレイヤーの座標に向かって移動 */
			this->vecPosition = VAdd(this->vecPosition, VScale(VNorm(VSub(vecPlayerPos, this->vecPosition)), MOVE_SPEED_PLAYER));

			/* プレイヤーの座標に到達した場合 */
			if (VSize(VSub(vecPlayerPos, this->vecPosition)) < 10.f)
			{
				/* 削除フラグを有効化 */
				this->bDeleteFlg = true;

				/* ブラッドをプレイヤーに加算 */
				{
					/* データリスト取得 */
					DataList_GameResource* GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
					/* ブラッドをプレイヤーに加算 */
					int iNowBlood = GameResourceList->iGetHaveBlood();
					GameResourceList->SetHaveBlood(iNowBlood + 1);
				}
			}
			break;
	}
	
	/* カウントを進める */
	this->iMoveCount -= 1;
}

// 描写
void EffectItem_Blood::Draw()
{
	/* 仮描写(本番ではビルボード) */
	//DrawModiBillboard3D(VECTOR Pos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int GrHandle, int TransFlag);
	int iColor = GetColor(255, 0, 0);
	DrawSphere3D(this->vecPosition, 10.f, 16, iColor, iColor, TRUE);
}
