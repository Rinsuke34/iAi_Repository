/* 2025.02.13 ファイル作成 駒沢風助 */

#include "SceneEdit.h"
#include "SceneResultDefine.h"

/* シーン"エディット"クラスの定義(描写部分) */

// 描画
void SceneEdit::Draw()
{
	/* 画面の背景描写 */
	DrawExtendGraph(0 + RESULT_BACKGROUND_POSITION_REDUCTION, 0 + RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_WIDE - RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_HEIGHT - RESULT_BACKGROUND_POSITION_REDUCTION, *this->piGrHandle_ResultBackGround, TRUE);

	/* NEW */
	DrawGraph(290, 180, *this->piGrHandle_New, TRUE);

	/* 背景 */
	DrawGraph(350, 885, *this->piGrHandle_UnderExplain_Under, TRUE);

	/* エディット背景 */
	DrawGraph(350, 250, *this->piGrHandle_Under, TRUE);
	DrawGraph(625, 250, *this->piGrHandle_Under, TRUE);
	DrawGraph(900, 250, *this->piGrHandle_Under, TRUE);
	DrawGraph(1175, 250, *this->piGrHandle_Under, TRUE);
	DrawGraph(1450, 250, *this->piGrHandle_Under, TRUE);

	DrawGraph(350, 695, *this->piGrHandle_NowEdit_Under, TRUE);

	/* 各項目の描写 */
	for (int i = 0; i < SELECT_ITEM_MAX; i++)
	{
		/* "次へ"であるか確認 */
		if (this->astSelectItemList[i].iSelectItemType == SELECT_TYPE_NEXT)
		{
			// "次へ"である場合
			/* "次へ"ボタン描写 */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->piGrHandle_NextButton, TRUE);
		}
		else
		{
			// "次へ"以外である場合
			/* エディットフレーム描写 */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->astSelectItemList[i].pstEditData->iEditRank), TRUE);

			/* エディット効果描写 */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->astSelectItemList[i].pstEditData->iEditEffect), TRUE);
		}

		/* 選択フレームの状態が設定されているか確認 */
		if (this->astSelectItemList[i].iSelectStatus != SELECT_STATUS_NONE)
		{
			// フレームの状態が設定されている場合
			/* 選択項目の状態のフレームを描写 */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->apiGrHandle_SelectStatus[this->astSelectItemList[i].iSelectStatus], TRUE);
		}
	}

	/* ホールド状態を確認 */
	if (this->HoldEditData.iEditEffect == EDIT_EFFECT_NONE)
	{
		// 何もホールドしていない場合
		/* 選択中の項目に対して選択フレームを描写 */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix, this->astSelectItemList[this->iSelectItem].stDrawPos.iy, *this->piGrHandle_SelectFrame, TRUE);
	}
	else
	{
		// 何かしらのエディットをホールド中の場合
		// ※選択中の項目の右上にホールド中のエディットを描写
		/* エディットフレーム描写 */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditFrame(this->HoldEditData.iEditRank), TRUE);

		/* エディット効果描写 */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditEffect(this->HoldEditData.iEditEffect), TRUE);
	}

	/* 所持ブラッド描写 */
	DrawFormatStringToHandle(500, 200, GetColor(255, 0, 0),	giFontHandle_Normal, "所持BLOOD : %d", this->GameResourceList->iGetHaveBlood());

	/* 鍵アイコン */
	DrawGraph(30, 210, *this->piGrHandle_EditLock, TRUE);

	/* ゴミ箱アイコン */
	DrawGraph(30, 650, *this->piGrHandle_Delete, TRUE);
}
