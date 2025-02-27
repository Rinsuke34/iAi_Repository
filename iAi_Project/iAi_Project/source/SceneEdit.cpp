/* 2025.01.19 ファイル作成 駒沢風助 */

#include "SceneEdit.h"

/* シーン"エディット"クラスの定義 */

// コンストラクタ
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->StageStatusList = dynamic_cast<DataList_StageStatus*>(gpDataListServer->GetDataList("DataList_StageStatus"));

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 選択フレーム */
		this->piGrHandle_SelectFrame	= ImageList->piGetImage("Test_Edit/Interface/SelectFrame");

		/* "次へ"ボタン */
		this->piGrHandle_SelectNext		= ImageList->piGetImage("Test_Edit/Interface/SelectNext");

		/* 選択項目の状態フレーム */
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_SET]		= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_PossibleSet");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_UPGRADE]	= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_PossibleUpgrade");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_INTERCHANGEABLE]	= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_Interchangeable");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_IMPOSSIBLE]		= ImageList->piGetImage("Test_Edit/Interface/SelectStatus_Impossible");
	}

	/* 初期化 */
	// テスト用
	this->iUpgradeRate	= 0;					// アップグレードのレート(0～10)
	this->iSelectItem	= 0;					// 選択中の項目の番号
	// 新規のエディット情報
	for (int i = 0; i < EDIT_UPGRADE_MAX; i++)
	{
		this->NewEditData[i].iEditRank		= EDIT_RANK_NONE;
		this->NewEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
	}

	/* ホールド中のエディットの情報 */
	/* ホールド中のエディット情報を初期化する */
	this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
	this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
	this->iHoldSelectItemType		= SELECT_TYPE_NONE;
	this->iHoldSelectItemNo			= 0;

	/* ステージクリア時の総合評価に応じて新規エディットを追加 */
	{
		/* ステージクリア時の総合評価取得 */
		int	iClearEvaluation_Total = this->GameResourceList->iGetClearEvaluation();

		/* 総合評価に応じた取得 */
		int		iNewEditNumber = 0;		// エディット数
		bool	bGoaldConfirmed = false;	// 金枠確定

		/* ランクに応じて設定する */
		switch (iClearEvaluation_Total)
		{
		case RESULT_EVALUAtiON_S:
			iNewEditNumber = 5;
			bGoaldConfirmed = true;
			break;

		case RESULT_EVALUAtiON_A:
			iNewEditNumber = 5;
			break;

		case RESULT_EVALUAtiON_B:
			iNewEditNumber = 4;
			break;

		case RESULT_EVALUAtiON_C:
		case RESULT_EVALUAtiON_D:
			iNewEditNumber = 3;
			break;
		}

		/* エディット数分ランダムなエディットを新規エディットに登録 */
		for (int i = 0; i < iNewEditNumber; i++)
		{
			/* 仮作成 */
			this->NewEditData[i].iEditEffect = EDIT_EFFECT_NORMAL_MOVE_SPEED_UP;
			this->NewEditData[i].iEditRank = EDIT_RANK_CUPPER;
		}

		/* 金枠確定フラグが有効であるか */
		if (bGoaldConfirmed == true)
		{
			// 有効である場合
			/* NONE以外のランダムなエディットのランクを金にする */
			this->NewEditData[GetRand(iNewEditNumber - 1)].iEditRank = EDIT_RANK_GOLD;
		}
	}

	/* 各項目の情報を選択項目に設定 */
	{
		int i = 0;
		// キープ中のエディット情報登録
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_KEEP_EDIT;
			this->astSelectItemList[i].pstEditData = this->GameResourceList->pstGetKeepEditData();
			i++;
		}
		// 新規エディット情報登録
		for (int j = 0; j < EDIT_UPGRADE_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NEW_EDIT;
			this->astSelectItemList[i].pstEditData = &this->NewEditData[j];
			i++;
		}
		// 削除情報登録
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_DELETE_EDIT;
			this->astSelectItemList[i].pstEditData = &this->DeleteEditData;
			i++;
		}
		// 現在のエディット情報登録
		for (int j = 0; j < EDIT_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NOW_EDIT;
			this->astSelectItemList[i].pstEditData = this->GameResourceList->pstGetNowEditData(j);
			i++;
		}
		// 次へ
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NEXT;
		}

		/* 描写座標一括登録 */
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

			/* 座標設定 */
			for (int l = 0; l < SELECT_ITEM_MAX; l++)
			{
				/* 座標設定 */
				this->astSelectItemList[l].stDrawPos = stSelectItemPos[l];

				/* 選択項目の状態を"状態無し"に設定(ついでで) */
				this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_NONE;
			}
		}
	}
}

// デストラクタ
SceneEdit::~SceneEdit()
{

}

// 初期化
void SceneEdit::Initialization()
{
	
}

// 計算
void SceneEdit::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->StageStatusList->iGetGameStatus();

	/* ゲーム状態に応じて処理を変更 */
	switch (iGameStatus)
	{
		/* "エディット"状態 */
		case GAMESTATUS_EDIT:
			/* メインの処理を実施 */
			Process_Main();
			break;

		/* 該当無し */
		default:
			/* シーンの削除フラグを有効にする */
			this->bDeleteFlg = true;
			break;
	}
}

// メイン処理
void SceneEdit::Process_Main()
{
	/* 決定入力時の処理 */
	Process_Decid();

	/* 方向入力時の処理 */
	Process_Select();

	/* 現在のエディット情報の更新 */
	Process_NowEditUpdate();
}

// 決定入力時の処理
void SceneEdit::Process_Decid()
{
	/* "決定"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DECID))
	{
		// 入力されている場合
		

		/* エディットをホールド中であるか確認 */
		if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
		{
			// ホールド中である場合
			/* 対象の選択項目の状態に応じて処理を変更する */
			switch (this->astSelectItemList[this->iSelectItem].iSelectStatus)
			{
				/* 状態なし */
				case SELECT_STATUS_NONE:
					/* ホールド中は"状態なし"にならないはずなのでここを通ったらエラー */
					break;

				/* セット可能 */
				case SELECT_STATUS_POSSIBLE_SET:
					/* ホールド中のエディット情報を現在の選択項目に設定する */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;

					/* ホールド中のエディット情報を初期化する */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;
					break;

				/* 強化可能 */
				case SELECT_STATUS_POSSIBLE_UPGRADE:
					/* 登録されているエディットのランクを上昇させる */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank += 1;

					/* ホールド中のエディット情報を初期化する */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;
					break;

				/* 交換可能 */
				case SELECT_STATUS_INTERCHANGEABLE:
					{
						/* 現在登録されているエディット情報を変数で保存 */
						EDIT_DATA stEditData = *this->astSelectItemList[this->iSelectItem].pstEditData;

						/* ホールド中のエディット情報を現在の選択項目に設定する */
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;

						/* 変数に保存したエディット情報をホールド中のエディット情報に設定する */
						this->HoldEditData			= stEditData;
						this->iHoldSelectItemType	= this->astSelectItemList[this->iSelectItem].iSelectItemType;
					}
					break;

				/* 選択不可 */
				case SELECT_STATUS_IMPOSSIBLE:
					/* 処理を行わない(音を出す) */
					break;
			}
		}
		else
		{
			// ホールド中ではない場合
			/* 現在の選択項目が"次へ"であるか */
			if (this->iSelectItem == SELECT_ITEM_NEXT)
			{
				// "次へ"である場合
				/* ゲーム状態を"次のステージへ遷移"に変更する */
				this->StageStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);

				/* 決定時の処理を終了する */
				return;
			}
			else
			{
				// "次へ"でない場合
				/* 登録されているエディットの取得処理を実施 */

				/* 選択項目に設定されたエディット情報をホールド中のエディットに代入する */
				this->HoldEditData.iEditEffect	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect;
				this->HoldEditData.iEditRank	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank;

				/* 選択項目の種類を設定する */
				this->iHoldSelectItemType = this->astSelectItemList[this->iSelectItem].iSelectItemType;

				/* エディット情報を回収した選択項目のエディット情報を初期化する */
				this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= EDIT_EFFECT_NONE;
				this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= EDIT_RANK_NONE;
			}
		}
	}
}

// 方向入力時の処理
void SceneEdit::Process_Select()
{
	/* "上"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_UP))
	{
		// 入力されている場合
		this->iSelectItem -= 6;
	}

	/* "下"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// 入力されている場合
		this->iSelectItem += 6;
	}

	/* "左"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// 入力されている場合
		this->iSelectItem -= 1;
	}

	/* "右"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// 入力されている場合
		this->iSelectItem += 1;
	}

	/* 選択中の項目の番号を範囲内に収める */
	if (this->iSelectItem < 0)
	{
		this->iSelectItem = 0;
	}
	else if (this->iSelectItem >= SELECT_ITEM_MAX)
	{
		this->iSelectItem = SELECT_ITEM_MAX - 1;
	}
}

// 現在のエディット情報の更新
void SceneEdit::Process_NowEditUpdate()
{
	/* エディットをホールド中であるか確認 */
	if (this->iHoldSelectItemType != SELECT_TYPE_NONE)
	{
		// ホールド中である場合
		/* 現在ホールド中の選択項目の種類に応じて処理を変更する */
		switch (this->iHoldSelectItemType)
		{
			/* キープ中のエディット */
			case SELECT_TYPE_KEEP_EDIT:
			/* 新規のエディット */
			case SELECT_TYPE_NEW_EDIT:
				/* キープ中のエディットを入れ替え可能とする */
				this->astSelectItemList[SELECT_TYPE_KEEP_EDIT].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;

				/* 新規のエディットを入れ替え可能とする */
				for (int i = SELECT_ITEM_NEW_EDIT_START; i <= SELECT_ITEM_NEW_EDIT_END; i++)
				{
					this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
				}

				/* 削除を選択不可とする */
				this->astSelectItemList[SELECT_ITEM_DELETE].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;

				/* 現在のエディットを条件付きセット可能、入れ替え可能、アップグレード可能とするとする */
				for (int i = SELECT_ITEM_NOW_EDIT_START; i <= SELECT_ITEM_NOW_EDIT_END; i++)
				{
					/* 所持ブラッドが10(仮)未満であるなら選択不可に設定 */
					if (this->GameResourceList->iGetHaveBlood() < 10)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
						continue;
					}

					/* エディットが登録されていないならセット可能とする */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == EDIT_EFFECT_NONE)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;
						continue;;
					}

					/* 効果が同一であるか確認 */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == this->HoldEditData.iEditEffect)
					{
						// 効果が同一であるならば
						/* ランクが同一であるか確認 */
						if (this->astSelectItemList[i].pstEditData->iEditRank == this->HoldEditData.iEditRank)
						{
							// ランクが同一であるならば
							/* ランクが金以外であるか */
							if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_GOLD)
							{
								/* 強化可能に設定 */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_UPGRADE;
							}
							else
							{
								/* 交換可能に設定 */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
							}
						}
					}
					else
					{
						/* 交換可能に設定 */
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
					}
				}

				/* 次へを選択不可とする */
				this->astSelectItemList[SELECT_ITEM_NEXT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;

			/* 削除 */
			case SELECT_TYPE_DELETE_EDIT:
			/* 現在のエディット */
			case SELECT_TYPE_NOW_EDIT:
				/* キープ中のエディットを選択不可とする */
				this->astSelectItemList[SELECT_TYPE_KEEP_EDIT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;

				/* 新規のエディットを選択不可とする */
				for (int i = SELECT_ITEM_NEW_EDIT_START; i <= SELECT_ITEM_NEW_EDIT_END; i++)
				{
					this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				}

				/* 削除をセット可能とする */
				this->astSelectItemList[SELECT_ITEM_DELETE].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;

				/* 現在のエディットをセット可能、入れ替え可能、アップグレード可能とする */
				for (int i = SELECT_ITEM_NOW_EDIT_START; i <= SELECT_ITEM_NOW_EDIT_END; i++)
				{
					/* エディットが登録されていないならセット可能とする */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == EDIT_EFFECT_NONE)
					{
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_SET;
						continue;;
					}

					/* 効果が同一であるか確認 */
					if (this->astSelectItemList[i].pstEditData->iEditEffect == this->HoldEditData.iEditEffect)
					{
						// 効果が同一であるならば
						/* ランクが同一であるか確認 */
						if (this->astSelectItemList[i].pstEditData->iEditRank == this->HoldEditData.iEditRank)
						{
							// ランクが同一であるならば
							/* ランクが金以外であるか */
							if (this->astSelectItemList[i].pstEditData->iEditRank != EDIT_RANK_GOLD)
							{
								/* 強化可能に設定 */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_POSSIBLE_UPGRADE;
							}
							else
							{
								/* 交換可能に設定 */
								this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
							}
						}
					}
					else
					{
						/* 交換可能に設定 */
						this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_INTERCHANGEABLE;
					}
				}

				/* 次へを選択不可とする */
				this->astSelectItemList[SELECT_ITEM_NEXT].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;
		}
	}
	else
	{
		// ホールド中ではない場合
		/* 全ての選択項目の状態を"選択項目なし"に設定 */
		for (int i = 0; i < SELECT_ITEM_MAX; i++)
		{
			/* テスト処理 */
			this->astSelectItemList[i].iSelectStatus = SELECT_STATUS_NONE;
		}
	}

	///* 同一のエディットがある場合、合成処理を行う */
	//// ※合成を行うと片方が削除され、もう片方のランクが上がる
	//for (int i = 0; i < EDIT_MAX; i++)
	//{
	//	/* エディット情報を取得 */
	//	EDIT_DATA stNowData = this->GameResourceList->stGetNowEditData(i);

	//	/* ランクが最大(金)であるなら処理は行わない */
	//	if (stNowData.iEditRank == EDIT_RANK_GOLD)
	//	{
	//		continue;
	//	}

	//	/* 効果がNONE(無し)であるなら処理は行わない */
	//	if (stNowData.iEditEffect == EDIT_EFFECT_NONE)
	//	{
	//		continue;
	//	}

	//	/* 同一のエディット情報が存在するか */
	//	for (int j = 0; j < EDIT_MAX; j++)
	//	{
	//		/* 確認対象と同じ項目であるなら処理は行わない */
	//		if (i == j)
	//		{
	//			continue;
	//		}

	//		/* エディット情報を取得 */
	//		EDIT_DATA stCheckData = this->GameResourceList->stGetNowEditData(j);

	//		/* ランクと効果が合致しているか確認 */
	//		if (stNowData.iEditEffect == stCheckData.iEditEffect && stNowData.iEditRank == stCheckData.iEditRank)
	//		{
	//			// 合致している場合
	//			/* 元のエディットのランクを上げる */
	//			this->GameResourceList->SetNowEditData(i, stNowData.iEditEffect, (stNowData.iEditRank + 1));

	//			/* 重複しているエディットを初期化する */
	//			this->GameResourceList->SetNowEditData(j, EDIT_EFFECT_NONE, EDIT_RANK_NONE);

	//			continue;
	//		}
	//	}
	//}
}

