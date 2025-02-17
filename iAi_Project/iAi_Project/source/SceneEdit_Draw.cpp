/* 2025.02.13 ファイル作成 駒沢風助 */

#include "SceneEdit.h"

/* シーン"エディット"クラスの定義(描写部分) */

// 描画
void SceneEdit::Draw()
{
	/* 描写座標設定(仮) */
	st2DPosition stSelectItemPos[SELECT_ITEM_MAX] =
	{
		{ 500 + (128 + 64) * 0, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 1, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 2, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 3, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 4, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 5, 1080 - 128 * 6 },
		{ 500 + (128 + 64) * 0, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 1, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 2, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 3, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 4, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 5, 1080 - 128 * 3 },
		{ 500 + (128 + 64) * 6, 1080 - 128 * 3 },
	};

	/* 各項目の描写 */
	for (int i = 0; i < SELECT_ITEM_MAX; i++)
	{
		/* インデックスに応じて描写内容を変更 */
		if (i <= SELECT_ITEM_KEEP)
		{
			// キープ中のエディット
			/* エディットフレーム描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->GameResourceList->pGetKeepEditData().iEditRank), TRUE);

			/* エディット効果描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->GameResourceList->pGetKeepEditData().iEditEffect), TRUE);
		}
		if (i <= SELECT_ITEM_NEW_EDIT)
		{
			// 新規のエディット
			/* エディットフレーム描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->NewEditData[i].iEditRank), TRUE);

			/* エディット効果描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->NewEditData[i].iEditEffect), TRUE);
		}
		else if (i < SELECT_ITEM_DELETE)
		{
			// 削除予定エディット
			/* エディットフレーム描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->DeleteEditData.iEditRank), TRUE);

			/* エディット効果描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->DeleteEditData.iEditEffect), TRUE);
		}
		else if (i <= SELECT_ITEM_NOW_EDIT)
		{
			// 現在のエディット
			/* エディットフレーム描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->GameResourceList->pGetNowEditData(i - 6).iEditRank), TRUE);

			/* エディット効果描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->GameResourceList->pGetNowEditData(i - 6).iEditEffect), TRUE);
		}
		else
		{
			// 次へ
			/* "次へ"ボタン描写 */
			DrawGraph(stSelectItemPos[i].ix, stSelectItemPos[i].iy, *this->piGrHandle_SelectNext, TRUE);
		}
	}

	/* 選択フレーム描写 */
	DrawGraph(stSelectItemPos[iSelectItem].ix, stSelectItemPos[iSelectItem].iy, *piGrHandle_SelectFrame, TRUE);

	/* 所持ブラッド描写 */
	DrawFormatStringToHandle(500, 200, GetColor(255, 0, 0),	giFontHandle, "所持BLOOD : %d", this->GameResourceList->iGetHaveBlood());
}
