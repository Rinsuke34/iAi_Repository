/* 2024.12.15 駒沢風助 ファイル作成 */

#include "CharacterPlayer.h"

/* プレイヤークラスの定義 */

// コンストラクタ
CharacterPlayer::CharacterPlayer() : CharacterBase()
{
	/* 初期化 */
	/* データリスト取得 */
	this->InputList			= dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	this->PlayerStatusList	= dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));

	/* 仮初期化処理開始 */
	this->iModelHandle = MV1LoadModel("resource/ModelData/Test/Player/Karisotai_1217.mv1");
}

// 更新
void CharacterPlayer::Update()
{
	/* 使用例 */
	// InputListに入っている関数を使用すればこんな感じで入力を取得できます。
	// 引数に関しては、InputList.hを参照してください。
	/* ジャンプ */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_JUMP) == true)
	{
		this->vecPosition.y = 50.f;
	}
	else
	{
		this->vecPosition.y = 0.f;
	}

	/* 移動 */
	float fSpeed = 2.0f;
	VECTOR vecMove = VScale(this->InputList->vecGetGameInputMove(), fSpeed);
	this->vecPosition = VAdd(this->vecPosition, vecMove);
}

// 描写
void CharacterPlayer::Draw()
{
	/* 座標設定 */
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	/* モデル描写 */
	MV1DrawModel(this->iModelHandle);


	/* テスト用描写 */
	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_JUMP) == true)
	{
		DrawFormatString(500, 16 * 0, GetColor(255, 255, 255), "JUMP");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_ATTACK) == true)
	{
		DrawFormatString(500, 16 * 1, GetColor(255, 255, 255), "ATTACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_AIM) == true)
	{
		DrawFormatString(500, 16 * 2, GetColor(255, 255, 255), "AIM");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RESET) == true)
	{
		DrawFormatString(500, 16 * 3, GetColor(255, 255, 255), "RESET");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_DODGE) == true)
	{
		DrawFormatString(500, 16 * 4, GetColor(255, 255, 255), "DODGE");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_FORWARD) == true)
	{
		DrawFormatString(500, 16 * 5, GetColor(255, 255, 255), "FORWARD");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_BACK) == true)
	{
		DrawFormatString(500, 16 * 6, GetColor(255, 255, 255), "BACK");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_LEFT) == true)
	{
		DrawFormatString(500, 16 * 7, GetColor(255, 255, 255), "LEFT");
	}

	if (this->InputList->bGetGameInputAction(INPUT_HOLD, GAME_RIGHT) == true)
	{
		DrawFormatString(500, 16 * 8, GetColor(255, 255, 255), "RIGHT");
	}

	VECTOR vecMove = this->InputList->vecGetGameInputMove();
	DrawFormatString(500, 16 * 9, GetColor(255, 255, 255), "X:%f, Z:%f", vecMove.x, vecMove.z);
}
