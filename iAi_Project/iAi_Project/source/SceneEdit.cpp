/* 2025.01.19 ファイル作成 駒沢風助 */

#include "SceneEdit.h"

/* シーン"エディット"クラスの定義 */

// コンストラクタ
SceneEdit::SceneEdit() : SceneBase("Edit", 100, true)
{
	/* データリスト取得 */
	{
		/* "ゲーム状態管理"を取得 */
		this->GameStatusList = dynamic_cast<DataList_GameStatus*>(gpDataListServer->GetDataList("DataList_GameStatus"));

		/* "ゲーム内リソース管理"を取得 */
		this->GameResourceList = dynamic_cast<DataList_GameResource*>(gpDataListServer->GetDataList("DataList_GameResource"));
	}

	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 選択フレーム */
		this->piGrHandle_SelectFrame	= ImageList->piGetImage("Test_Edit/Interface/SelectFrame");

		this->piGrHandle_SelectNext		= ImageList->piGetImage("Test_Edit/Interface/SelectNext");
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

	this->iHoldSelectItem			= -1;
	this->iHoldSelectItemType		= -1;
	this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
	this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;

	/* 初期化 */
	Initialization();
}

// デストラクタ
SceneEdit::~SceneEdit()
{

}

// 初期化
void SceneEdit::Initialization()
{
	/* ステージクリア時の総合評価に応じて新規エディットを追加 */
	{
		/* ステージクリア時の総合評価取得 */
		int	iClearEvaluation_Total =  this->GameResourceList->iGetClearEvaluation();

		/* 総合評価に応じた取得 */
		int		iNewEditNumber	= 0;		// エディット数
		bool	bGoaldConfirmed	= false;	// 金枠確定

		/* ランクに応じて設定する */
		switch (iClearEvaluation_Total)
		{
			case RESULT_EVALUAtiON_S:
				iNewEditNumber	= 5;
				bGoaldConfirmed	= true;
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
			this->NewEditData[i].iEditEffect	= EDIT_EFFECT_NORMAL_MOVE_SPEED_UP;
			this->NewEditData[i].iEditRank		= EDIT_RANK_CUPPER;
		}

		/* 金枠確定フラグが有効であるか */
		if (bGoaldConfirmed == true)
		{
			// 有効である場合
			/* NONE以外のランダムなエディットのランクを金にする */
			this->NewEditData[GetRand(iNewEditNumber - 1)].iEditRank = EDIT_RANK_GOLD;
		}
	}
}

// 計算
void SceneEdit::Process()
{
	/* ゲーム状態を確認 */
	int iGameStatus = this->GameStatusList->iGetGameStatus();

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
		/* 現在の選択項目が"次へ"であるか */
		if (this->iSelectItem == SELECT_ITEM_NEXT - 1)
		{
			// "次へ"である場合
			/* ゲーム状態を"次のステージへ遷移"に変更する */
			this->GameStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);

			/* 決定時の処理を終了する */
			return;
		}

		/* エディットをホールド中であるか確認 */
		if (this->iHoldSelectItem != -1)
		{
			// ホールド中である場合
			/* 現在の選択項目に応じて処理を変更する */
			if (SELECT_ITEM_KEEP >= this->iSelectItem)
			{
				// "キープ中のエディットである場合
				/* エディットが登録されているか確認 */
				if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// 登録されている場合
					/* 現在ホールド中のエディットを保持 */
					EDIT_DATA stNowHoldEditData;
					stNowHoldEditData.iEditEffect	= this->HoldEditData.iEditEffect;
					stNowHoldEditData.iEditRank		= this->HoldEditData.iEditRank;

					/* 設定されているエディットを保持中にする */
					this->HoldEditData.iEditEffect	= this->GameResourceList->pGetKeepEditData().iEditEffect;
					this->HoldEditData.iEditRank	= this->GameResourceList->pGetKeepEditData().iEditRank;

					/* 保持している現在ホールド中のエディットをキープ中のエディットに登録 */
					this->GameResourceList->SetKeepEditData(stNowHoldEditData);
				}
				else
				{
					// 登録されていない場合
					/* 保持している現在ホールド中のエディットをキープ中のエディットに登録 */
					this->GameResourceList->SetKeepEditData(this->HoldEditData);
				}
			}
			else if (SELECT_ITEM_NEW_EDIT >= this->iSelectItem)
			{
				// "新規のエディット"である場合
				/* エディットが登録されているか確認 */
				if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// 登録されている場合
					/* 現在ホールド中のエディットを保持 */
					EDIT_DATA stNowHoldEditData;
					stNowHoldEditData.iEditEffect = this->HoldEditData.iEditEffect;
					stNowHoldEditData.iEditRank = this->HoldEditData.iEditRank;

					/* 設定されているエディットを保持中にする */
					this->HoldEditData.iEditEffect = this->NewEditData[this->iSelectItem - 1].iEditEffect;
					this->HoldEditData.iEditRank = this->NewEditData[this->iSelectItem - 1].iEditRank;

					/* 保持している現在ホールド中のエディットを新規のエディットに登録 */
					this->NewEditData[this->iSelectItem - 1] = stNowHoldEditData;
				}
				else
				{
					// 登録されていない場合
					/* 保持している現在ホールド中のエディットを新規のエディットに登録 */
					this->NewEditData[this->iSelectItem - 1] = this->HoldEditData;
				}
			}
			else if (SELECT_ITEM_DELETE >= this->iSelectItem)
			{
				// "削除"である場合
				
			}
			else if (SELECT_ITEM_NOW_EDIT >= this->iSelectItem)
			{
				// 現在のエディット"である場合
				
			}
		}
		else
		{
			// ホールド中でない場合
			/* 現在の選択項目に応じて処理を変更する */
			if (SELECT_ITEM_KEEP >= this->iSelectItem)
			{
				// "キープ中のエディットである場合
				/* エディットが登録されているか確認 */
				if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// 登録されている場合
					/* 登録されているデータをホールド中のエディット情報に登録 */
					this->HoldEditData.iEditEffect	= this->GameResourceList->pGetKeepEditData().iEditEffect;
					this->HoldEditData.iEditRank	= this->GameResourceList->pGetKeepEditData().iEditRank;

					/* キープ中のエディット情報を初期化 */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->GameResourceList->SetKeepEditData(stSetData);

					/* ホールド中の選択項目を設定 */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_KEEP;
				}
			}
			else if(SELECT_ITEM_NEW_EDIT >= this->iSelectItem)
			{
				// "新規のエディット"である場合
				/* エディットが登録されているか確認 */
				if (this->NewEditData[this->iSelectItem - 1].iEditEffect != EDIT_EFFECT_NONE)
				{
					// 登録されている場合
					/* 登録されているデータをホールド中のエディット情報に登録 */
					this->HoldEditData.iEditEffect = this->NewEditData[this->iSelectItem - 1].iEditEffect;
					this->HoldEditData.iEditRank = this->NewEditData[this->iSelectItem - 1].iEditRank;

					/* 新規のエディット情報を初期化 */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->NewEditData[this->iSelectItem - 1] = stSetData;

					/* ホールド中の選択項目を設定 */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_NEW_EDIT;
				}
			}
			else if (SELECT_ITEM_DELETE >= this->iSelectItem)
			{
				// "削除"である場合
				/* エディットが登録されているか確認 */
				if (this->DeleteEditData.iEditEffect != EDIT_EFFECT_NONE)
				{
					// 登録されている場合
					/* 登録されているデータをホールド中のエディット情報に登録 */
					this->HoldEditData.iEditEffect	= this->DeleteEditData.iEditEffect;
					this->HoldEditData.iEditRank	= this->DeleteEditData.iEditRank;

					/* 削除予定のエディット情報を初期化 */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->DeleteEditData	= stSetData;

					/* ホールド中の選択項目を設定 */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_DELETE;
				}
			}
			else if (SELECT_ITEM_NOW_EDIT >= this->iSelectItem)
			{
				// 現在のエディット"である場合
				/* エディットが登録されているか確認 */
				if (this->GameResourceList->pGetNowEditData(this->iSelectItem - 6).iEditEffect != EDIT_EFFECT_NONE)
				{
					// 登録されている場合
					/* 登録されているデータをホールド中のエディット情報に登録 */
					this->HoldEditData.iEditEffect	= this->GameResourceList->pGetNowEditData(this->iSelectItem - 6).iEditEffect;
					this->HoldEditData.iEditRank	= this->GameResourceList->pGetNowEditData(this->iSelectItem - 6).iEditRank;

					/* 現在のエディット情報を初期化 */
					EDIT_DATA stSetData;
					stSetData.iEditEffect	= EDIT_EFFECT_NONE;
					stSetData.iEditRank		= EDIT_RANK_NONE;
					this->GameResourceList->SetNowEditData(this->iSelectItem - 6, stSetData.iEditEffect, stSetData.iEditRank);

					/* ホールド中の選択項目を設定 */
					this->iHoldSelectItem		= this->iSelectItem;
					this->iHoldSelectItemType	= SELECT_ITEM_NOW_EDIT;
				}
			}
		}


		///* 現在の選択項目が"新規のエディット"であるか */
		//if (this->iSelectItem < SELECT_ITEM_NEW_EDIT)
		//{
		//	// "新規のエディット"である場合
		//	/* 選択したエディットの項目を取得 */
		//	EDIT_DATA stSetData;
		//	stSetData.iEditEffect	= this->NewEditData[this->iSelectItem].iEditEffect;
		//	stSetData.iEditRank		= this->NewEditData[this->iSelectItem].iEditRank;

		//	/* 選択したエディット項目の効果が"NONE"であるか */
		//	if (stSetData.iEditEffect == EDIT_EFFECT_NONE)
		//	{
		//		// "NONE"である場合
		//		/* 決定時の処理を終了する */
		//		return;
		//	}

		//	/* 選択したエディットを現在のエディットで登録されていない箇所に設定する */
		//	bool bSetFlg = false;		// 登録成功フラグ
		//	for (int i = 0; i < EDIT_MAX; i++)
		//	{
		//		/* エディットが登録済みであるか確認 */
		//		if (this->GameResourceList->pGetNowEditData(i).iEditEffect == EDIT_EFFECT_NONE)
		//		{
		//			// 登録済みでない場合
		//			/* 選択したエディットの情報を設定する */
		//			this->GameResourceList->SetNowEditData(i, stSetData.iEditEffect, stSetData.iEditRank);

		//			/* 登録成功フラグを有効にする */
		//			bSetFlg = true;
		//			break;
		//		}
		//	}

		//	/* 登録が成功したか確認 */
		//	if (bSetFlg == true)
		//	{
		//		// 成功した場合
		//		/* 選択した新規エディット項目を初期化する */
		//		this->NewEditData[this->iSelectItem].iEditEffect	= EDIT_EFFECT_NONE;
		//		this->NewEditData[this->iSelectItem].iEditRank		= EDIT_RANK_NONE;
		//	}

		//}
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
	/* 同一のエディットがある場合、合成処理を行う */
	// ※合成を行うと片方が削除され、もう片方のランクが上がる
	for (int i = 0; i < EDIT_MAX; i++)
	{
		/* エディット情報を取得 */
		EDIT_DATA stNowData = this->GameResourceList->pGetNowEditData(i);

		/* ランクが最大(金)であるなら処理は行わない */
		if (stNowData.iEditRank == EDIT_RANK_GOLD)
		{
			continue;
		}

		/* 効果がNONE(無し)であるなら処理は行わない */
		if (stNowData.iEditEffect == EDIT_EFFECT_NONE)
		{
			continue;
		}

		/* 同一のエディット情報が存在するか */
		for (int j = 0; j < EDIT_MAX; j++)
		{
			/* 確認対象と同じ項目であるなら処理は行わない */
			if (i == j)
			{
				continue;
			}

			/* エディット情報を取得 */
			EDIT_DATA stCheckData = this->GameResourceList->pGetNowEditData(j);

			/* ランクと効果が合致しているか確認 */
			if (stNowData.iEditEffect == stCheckData.iEditEffect && stNowData.iEditRank == stCheckData.iEditRank)
			{
				// 合致している場合
				/* 元のエディットのランクを上げる */
				this->GameResourceList->SetNowEditData(i, stNowData.iEditEffect, (stNowData.iEditRank + 1));

				/* 重複しているエディットを初期化する */
				this->GameResourceList->SetNowEditData(j, EDIT_EFFECT_NONE, EDIT_RANK_NONE);

				continue;
			}
		}
	}
}

