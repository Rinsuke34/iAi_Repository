/* 2025.02.13 ファイル作成 駒沢風助 */

#include "SceneEdit.h"
#include "SceneResultDefine.h"

/* シーン"エディット"クラスの定義(描写部分) */

// 描画
void SceneEdit::Draw()
{
	/* リザルト用のフレームを描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *this->piGrHandle_ResultFrame, FALSE);

	/* 画面の背景描写 */
	DrawExtendGraph(0 + RESULT_BACKGROUND_POSITION_REDUCTION, 0 + RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_WIDE - RESULT_BACKGROUND_POSITION_REDUCTION, SCREEN_SIZE_HEIGHT - RESULT_BACKGROUND_POSITION_REDUCTION, *this->piGrHandle_ResultBackGround, TRUE);

	/* Custom(文字) */
	DrawGraph(80, 30, *this->piGrHandle_Custom, TRUE);
	DrawBox(65, 140, 1810, 145, GetColor(255, 255, 255), TRUE);

	/* NEW(文字) */
	DrawGraph(290, 180, *this->piGrHandle_New, TRUE);

	/* 現在エディット情報の説明欄 */
	DrawGraph(430, 885, *this->piGrHandle_UnderExplain_Under, TRUE);

	/* エディット背景 */
	// キープエディット部分
	DrawGraph(155, 250, *this->piGrHandle_KeepEdit_Under, TRUE);
	// 新規エディット部分
	for (int i = 0; i < 5; i++)
	{
		int iX = ((i + 1) * 275) + 155;
		int iY = 250;
		DrawGraph(iX, iY, *this->piGrHandle_NewEdit_Under, TRUE);
	}
	// 現在エディット部分
	DrawGraph(430, 695, *this->piGrHandle_NowEdit_Under, TRUE);

	/* 所持ブラッド描写 */
	DrawGraph(630, 170, *this->piGrHandle_Blood, TRUE);
	DrawFormatStringToHandle(700, 150, GetColor(255, 255, 255), giFontHandle_Large, "%d", this->GameResourceList->iGetHaveBlood());

	/* 所持ブラッド下線 */
	DrawBox(645, 235, 1275, 240, GetColor(255, 255, 255), TRUE);

	/* 各項目の描写 */
	for (int i = 0; i < SELECT_ITEM_MAX; i++)
	{
		/* "次へ"であるか確認 */
		if (this->astSelectItemList[i].iSelectItemType == SELECT_TYPE_NEXT)
		{
			// "次へ"である場合
			/* "次へ"ボタン描写 */
			DrawGraph(1515, 950, *this->piGrHandle_SelectNext, TRUE);
		}
		else
		{
			// "次へ"以外である場合
			/* エディットフレーム描写 */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditFrame(this->astSelectItemList[i].pstEditData->iEditRank), TRUE);

			/* エディット効果描写 */
			DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->GameResourceList->piGetGrHandle_EditEffect(this->astSelectItemList[i].pstEditData->iEditEffect), TRUE);

			/* 選択項目の種類を取得 */
			int iSelectItemType = this->astSelectItemList[i].iSelectItemType;

			/* 選択項目の種類に応じた処理 */
			switch (iSelectItemType)
			{
				/* キープ中のエディット */
				/* 新規のエディット */
				case SELECT_TYPE_KEEP_EDIT:
				case SELECT_TYPE_NEW_EDIT:
					/* エディットランクが"無し"以外であるか */
					if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_NONE)
					{
						// "無し"以外である場合
						/* 必要ブラッドを描写 */
						int iX = (i * 275) + 155;
						int iY = 420;
						DrawGraph(iX, iY, *this->piGrHandle_Blood, TRUE);
						DrawFormatStringToHandle(iX + 70, iY, GetColor(255, 255, 255), giFontHandle_Medium, "%d", this->astSelectItemList[i].pstEditData->iEditCost);

						/* 説明文を描写 */
						std::string formattedText = PUBLIC_PROCESS::aInsertNewLine(this->astSelectItemList[i].pstEditData->aText, 7);
						DrawFormatStringToHandle(iX + 20, iY + 70, GetColor(255, 255, 255), giFontHandle_Small,	"%s", formattedText.c_str());

						/* キープ中のエディットであるか確認 */
						if (iSelectItemType == SELECT_TYPE_KEEP_EDIT)
						{
							// キープ中のエディットである場合
							/* キープ(文字)を描写 */
							DrawGraph(280, 328, *this->piGrHandle_Keep, TRUE);
						}
					}
					else
					{
						// "無し"である場合
						/* キープ中のエディットであるか確認 */
						if (iSelectItemType == SELECT_TYPE_KEEP_EDIT)
						{
							// キープ中のエディットである場合
							/* キープアイコン(箱)を描写 */
							DrawGraph(160, 210, *this->piGrHandle_KeepIcon, TRUE);
						}
					}
					break;

				/* 削除 */
				case SELECT_TYPE_DELETE_EDIT:
					/* エディットランクが"無し"以外であるか */
					if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_NONE)
					{
						// "無し"以外である場合
						/* 削除アイコン(ゴミ箱)を描写 */
						DrawExtendGraph(288, 778, 288, 905, *this->piGrHandle_Delete, TRUE);
					}
					else
					{
						// "無し"である場合
						/* 削除アイコン(ゴミ箱)を描写 */
						DrawGraph(160, 650, *this->piGrHandle_Delete, TRUE);
					} 
					break;

				/* 現在のエディット */
				case SELECT_TYPE_NOW_EDIT:
					break;

				/* 次へ */
				case SELECT_TYPE_NEXT:
					break;
			}

			/* 選択フレームの状態が設定されているか確認 */
			if (this->astSelectItemList[i].iSelectStatus != SELECT_STATUS_NONE)
			{
				// フレームの状態が設定されている場合
				/* 選択項目の状態のフレームを描写 */
				DrawGraph(this->astSelectItemList[i].stDrawPos.ix, this->astSelectItemList[i].stDrawPos.iy, *this->apiGrHandle_SelectStatus[this->astSelectItemList[i].iSelectStatus], TRUE);
			}

			/* 新規のエディット数に応じてロックを描写 */
			switch (this->iNewEditNumber)
			{
				/* 新規エディット数が"5個"の場合 */
				case NEW_EDIT_NO_RANK_S:
					/* ロックは描写しない */
					break;

				/* 新規エディット数が"4個"の場合 */
				case NEW_EDIT_NO_RANK_B:
					/* ロックを描写 */
					DrawGraph(1535, 210, *this->apiGrHandle_EditLock[1], TRUE);
					break;

				/* 新規エディット数が"3個"の場合 */
				case NEW_EDIT_NO_RANK_C:
					/* ロックを描写 */
					DrawGraph(1260, 210, *this->apiGrHandle_EditLock[0], TRUE);
					DrawGraph(1535, 210, *this->apiGrHandle_EditLock[1], TRUE);
					break;
			}
		}
	}

	/* ホールド状態を確認 */
	if (this->HoldEditData.iEditEffect == EDIT_EFFECT_NONE)
	{
		// 何もホールドしていない場合
		/* 選択中の項目に対して選択フレームを描写 */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix, this->astSelectItemList[this->iSelectItem].stDrawPos.iy, *this->piGrHandle_SelectFrame[0], TRUE);
	}
	else
	{
		// 何かしらのエディットをホールド中の場合
		// ※選択中の項目の右上にホールド中のエディットを描写
		/* エディットフレーム描写 */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditFrame(this->HoldEditData.iEditRank), TRUE);

		/* 選択中の項目に対して選択フレームを描写 */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix, this->astSelectItemList[this->iSelectItem].stDrawPos.iy, *this->piGrHandle_SelectFrame[1], TRUE);

		/* エディット効果描写 */
		DrawGraph(this->astSelectItemList[this->iSelectItem].stDrawPos.ix + 20, this->astSelectItemList[this->iSelectItem].stDrawPos.iy - 20, *this->GameResourceList->piGetGrHandle_EditEffect(this->HoldEditData.iEditEffect), TRUE);
	}

	/* 現在の選択カーソルが"削除","現在のエディット"になっているか */
	if ((SELECT_ITEM_DELETE <= this->iSelectItem) && (this->iSelectItem <= SELECT_ITEM_NOW_EDIT_END))
	{
		// "削除","現在のエディット"である場合
		/* カーソルが合わさっている項目に項目が設定されているか確認 */
		if (this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect != EDIT_EFFECT_NONE)
		{
			// 設定されている場合
			/* 説明文を描写 */
			std::string formattedText = PUBLIC_PROCESS::aInsertNewLine(this->astSelectItemList[this->iSelectItem].pstEditData->aText, 13);
			DrawFormatStringToHandle(445, 895, GetColor(255, 255, 255), giFontHandle_Small, "%s", formattedText.c_str());
		}
	}
}
