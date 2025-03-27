/* 2025.01.19 ファイル作成 駒沢風助 */

#include "SceneEdit.h"
#include <nlohmann/json.hpp>
#include <fstream>

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

		/* "プレイヤー状態管理"を取得 */
		this->PlayerStatusList = dynamic_cast<DataList_PlayerStatus*>(gpDataListServer->GetDataList("DataList_PlayerStatus"));
	}

	/* 画像リソース取得 */
	{
		/* データリスト"画像ハンドル管理"を取得 */
		DataList_Image* ImageList = dynamic_cast<DataList_Image*>(gpDataListServer->GetDataList("DataList_Image"));

		/* 選択フレーム(0:ホールド無し、 1:ホールドあり) */
		this->piGrHandle_SelectFrame[0]	= ImageList->piGetImage("Conversation/SelectFlame");
		this->piGrHandle_SelectFrame[1]	= ImageList->piGetImage("Conversation/SelectFlame_2");

		/* "次へ"ボタン */
		this->piGrHandle_SelectNext		= ImageList->piGetImage("Edit/Scene/UI_Nextbutton");

		/* 選択項目の状態フレーム */
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_SET]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Set");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_POSSIBLE_UPGRADE]	= ImageList->piGetImage("Edit/Scene/UI_Edit_Reinforce");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_INTERCHANGEABLE]	= ImageList->piGetImage("Edit/Scene/UI_Edit_Trade");
		this->apiGrHandle_SelectStatus[SELECT_STATUS_IMPOSSIBLE]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Unselectable");

		/* リザルトフレーム */
		this->piGrHandle_ResultFrame		= ImageList->piGetImage("Result/UI_Result_Frame");

		/* 現在のエディット情報 */
		this->piGrHandle_NowEdit_Under		= ImageList->piGetImage("Edit/Scene/UI_NowEdit_Under");

		/* 現在のエディット情報の説明欄 */
		this->piGrHandle_UnderExplain_Under	= ImageList->piGetImage("Edit/Scene/UI_NowEditExplain_Under");

		/* 新規エディット情報 */
		this->piGrHandle_NewEdit_Under		= ImageList->piGetImage("Edit/Scene/UI_NewEdit_Under");

		/* キープエディット情報 */
		this->piGrHandle_KeepEdit_Under		= ImageList->piGetImage("Edit/Scene/UI_Edit_Keep_Under");

		/* キープアイコン */
		this->piGrHandle_KeepIcon			= ImageList->piGetImage("Edit/Scene/UI_Edit_Keep");

		/* キープ(文字) */
		this->piGrHandle_Keep				= ImageList->piGetImage("Edit/Scene/UI_Moji_Keep");

		/* 削除 */
		this->piGrHandle_Delete				= ImageList->piGetImage("Edit/Scene/UI_Edit_Delete");

		/* NEW(文字) */
		this->piGrHandle_New				= ImageList->piGetImage("Edit/Scene/UI_Moji_New");
	
		/* カスタム(文字) */
		this->piGrHandle_Custom				= ImageList->piGetImage("Edit/Scene/UI_Moji_Custom");

		/* ブラッドアイコン */
		this->piGrHandle_Blood				= ImageList->piGetImage("UI_Player_Blood/Blood");

		/* エディットロック文字(0:Bランク, 1:Aランク) */
		this->apiGrHandle_EditLock[0]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Lock_B");
		this->apiGrHandle_EditLock[1]		= ImageList->piGetImage("Edit/Scene/UI_Edit_Lock_A");
	}

	/* 初期化 */
	this->iSelectItem		= 0;					// 選択中の項目の番号
	// 新規のエディット情報
	for (int i = 0; i < EDIT_UPGRADE_MAX; i++)
	{
		this->NewEditData[i].iEditRank		= EDIT_RANK_NONE;
		this->NewEditData[i].iEditEffect	= EDIT_EFFECT_NONE;
		this->NewEditData[i].iEditCost		= 0;
		this->NewEditData[i].aText			= "";
	}

	/* ホールド中のエディットの情報 */
	/* ホールド中のエディット情報を初期化する */
	this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
	this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
	this->HoldEditData.iEditCost	= 0;
	this->HoldEditData.aText		= "";
	this->iHoldSelectItemType		= SELECT_TYPE_NONE;
	this->iHoldSelectItemNo			= 0;

	/* ステージクリア時の総合評価に応じて新規エディットを追加 */
	{
		/* ステージクリア時の総合評価取得 */
		int	iClearEvaluation_Total = this->GameResourceList->iGetClearEvaluation();

		/* 総合評価に応じた取得 */
		this->iNewEditNumber = 0;						// 新規エディット数
		bool	bGoaldConfirmed = false;	// 金枠確定

		/* ランクに応じて設定する */
		switch (iClearEvaluation_Total)
		{
			case RESULT_EVALUATION_S:
				this->iNewEditNumber	= NEW_EDIT_NO_RANK_S;
				bGoaldConfirmed	= true;
				break;

			case RESULT_EVALUATION_A:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_A;
				break;

			case RESULT_EVALUATION_B:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_B;
				break;

			case RESULT_EVALUATION_C:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_C;
				break;

			case RESULT_EVALUATION_D:
				this->iNewEditNumber = NEW_EDIT_NO_RANK_D;
				break;
		}

		/* 最初にエディット画面を追加するか確認 */
		if (this->StageStatusList->bGetFastEditFlg() == true)
		{
			// 追加する場合(最初のエディット描写の場合)
			/* 新規エディット情報を固定の設定とする */
			/* 1枠目 */
			{
				this->NewEditData[0].iEditEffect	= 2;
				this->NewEditData[0].iEditRank		= 2;
				this->NewEditData[0].iEditCost		= 500;
				this->NewEditData[0].aText			= "ブラッド取得量が5増加";
			}
			/* 2枠目 */
			{
				this->NewEditData[1].iEditEffect	= 5;
				this->NewEditData[1].iEditRank		= 1;
				this->NewEditData[1].iEditCost		= 500;
				this->NewEditData[1].aText			= "ジャンプ可能回数が1回増加";
			}
			/* 3枠目 */
			{
				this->NewEditData[2].iEditEffect	= 9;
				this->NewEditData[2].iEditRank		= 3;
				this->NewEditData[2].iEditCost		= 3000;
				this->NewEditData[2].aText			= "一部の敵攻撃を跳ね返せるようになる";
			}
		}
		else
		{
			// 追加しない場合(ステージクリア時のエディット描写の場合)
			/* Jsonファイルからエディット情報を読み込んで新規エディットに登録 */
			{
				/* 取得した情報を保存する配列の宣言 */
				std::vector<EDIT_LOTTERY> aEditLotteryList;

				/* パスとファイル名の設定 */
				std::string FilePath = "resource/SetupData/";	// 保存場所
				std::string jsonFileName = "EditDataBase.json";		// ファイル名

				/* ファイル展開 */
				std::ifstream inputFile(FilePath + jsonFileName);

				/* ファイルの展開が成功したか確認 */
				if (inputFile.is_open())
				{
					// ファイルが存在する場合
					/* 現在のステージの各評価の基準値を取得する */
					nlohmann::json	json;
					inputFile >> json;

					/* すべての要素を読み込む */
					for (auto& data : json)
					{
						/* エディット情報を取得 */
						EDIT_LOTTERY stEditLottery;
						data.at("Effect").get_to(stEditLottery.iEffect);
						data.at("Rank").get_to(stEditLottery.iRank);
						data.at("IncidenceRate").get_to(stEditLottery.iIncidenceRate);
						data.at("Cost").get_to(stEditLottery.iCost);
						data.at("Text").get_to(stEditLottery.aText);

						/* 読み込んだ文字列をUTF-8～Shift-JISに変換 */
						stEditLottery.aText = PUBLIC_PROCESS::aUtf8ToShiftJIS(stEditLottery.aText);

						/* 配列に追加 */
						aEditLotteryList.push_back(stEditLottery);
					}

					/* ファイルを閉じる */
					inputFile.close();
				}

				/* エディット数分ランダムなエディットを選択 */
				{
					/* 全要素の出現率合計値を取得 */
					int iTotalRarity = 0;
					for (auto& edit : aEditLotteryList)
					{
						/* 合計値に加算 */
						iTotalRarity += edit.iIncidenceRate;
					}

					/* 出現率に基づき、ランダムなエディットを選出 */
					for (int i = 0; i < this->iNewEditNumber; i++)
					{
						/* ランダムな値を取得する */
						int iRandomValue = GetRand(iTotalRarity - 1);
						int iCurrentSum = 0;

						/* ランダム値に応じたエディットを取得する */
						for (auto& edit : aEditLotteryList)
						{
							/* 出現率に応じた値分加算 */
							iCurrentSum += edit.iIncidenceRate;

							/* ランダム値を加算値が超えているか確認 */
							if (iRandomValue < iCurrentSum)
							{
								// 超えている場合
								/* 選択したエディットを新規エディットに登録 */
								this->NewEditData[i].iEditEffect = edit.iEffect;
								this->NewEditData[i].iEditRank = edit.iRank;
								this->NewEditData[i].iEditCost = edit.iCost;
								this->NewEditData[i].aText = edit.aText;
								break;
							}
						}
					}
				}
			}

			/* 金枠確定フラグが有効であるか */
			if (bGoaldConfirmed == true)
			{
				// 有効である場合
				/* NONE以外のランダムなエディットのランクを金にする */
				// ※最低1枠であるため、金枠のエディットが抽選対象となっても仕様上は問題ない
				this->NewEditData[GetRand(this->iNewEditNumber - 1)].iEditRank = EDIT_RANK_GOLD;
			}
		}
	}

	/* 各項目の情報を選択項目に設定 */
	{
		int i = 0;
		// キープ中のエディット情報登録
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_KEEP_EDIT;
			this->astSelectItemList[i].pstEditData		= this->GameResourceList->pstGetKeepEditData();
			i++;
		}
		// 新規エディット情報登録
		for (int j = 0; j < EDIT_UPGRADE_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_NEW_EDIT;
			this->astSelectItemList[i].pstEditData		= &this->NewEditData[j];
			i++;
		}
		// 削除情報登録
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_DELETE_EDIT;
			this->astSelectItemList[i].pstEditData		= &this->DeleteEditData;
			i++;
		}
		// 現在のエディット情報登録
		for (int j = 0; j < EDIT_MAX; j++)
		{
			this->astSelectItemList[i].iSelectItemType	= SELECT_TYPE_NOW_EDIT;
			this->astSelectItemList[i].pstEditData		= this->GameResourceList->pstGetNowEditData(j);
			i++;
		}
		// 次へ
		{
			this->astSelectItemList[i].iSelectItemType = SELECT_TYPE_NEXT;
		}

		/* 描写座標一括登録 */
		{
			/* 描写座標設定 */
			st2DPosition stSelectItemPos[SELECT_ITEM_MAX] =
			{
				{ 160, 210 },
				{ 435, 210 },
				{ 710, 210 },
				{ 985, 210 },
				{ 1260, 210 },
				{ 1535, 210 },
				{ 160, 650 },
				{ 435, 650 },
				{ 710, 650 },
				{ 985, 650 },
				{ 1260, 650 },
				{ 1535, 650 },
				{ 1415, 850 }
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

	/* BGMを設定 */
	gpDataList_Sound->BGM_SetHandle(BGM_EDIT);
}

// デストラクタ
SceneEdit::~SceneEdit()
{
	/* プレイヤーのステータスを更新 */
	this->PlayerStatusList->StatusBuffUpdate();
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
				/* セット可能 */
				case SELECT_STATUS_POSSIBLE_SET:
					/* ホールド中のエディットが"キープ中のエディット"あるいは"新規のエディット"であるか確認 */
					if ((this->iHoldSelectItemType == SELECT_TYPE_KEEP_EDIT) || (this->iHoldSelectItemType == SELECT_TYPE_NEW_EDIT))
					{
						// "キープ中のエディット"あるいは"新規のエディット"である場合
						/* ホールド中のエディットのコスト分所持ブラッド(ゲーム内通貨)を減少 */
						this->GameResourceList->SetHaveBlood(this->GameResourceList->iGetHaveBlood() - this->HoldEditData.iEditCost);
					}

					/* ホールド中のエディット情報を現在の選択項目に設定する */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost	= this->HoldEditData.iEditCost;
					this->astSelectItemList[this->iSelectItem].pstEditData->aText		= this->HoldEditData.aText;

					/* ホールド中のエディット情報を初期化する */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->HoldEditData.iEditCost	= 0;
					this->HoldEditData.aText		= "";
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;

					/* "決定"のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);
					break;

				/* 強化可能 */
				case SELECT_STATUS_POSSIBLE_UPGRADE:
					/* ホールド中のエディットが"キープ中のエディット"あるいは"新規のエディット"であるか確認 */
					if ((this->iHoldSelectItemType == SELECT_TYPE_KEEP_EDIT) || (this->iHoldSelectItemType == SELECT_TYPE_NEW_EDIT))
					{
						// "キープ中のエディット"あるいは"新規のエディット"である場合
						/* ホールド中のエディットのコスト分所持ブラッド(ゲーム内通貨)を減少 */
						this->GameResourceList->SetHaveBlood(this->GameResourceList->iGetHaveBlood() - this->HoldEditData.iEditCost);
					}

					/* 登録されているエディットのランクを上昇させる */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank += 1;

					/* ホールド中のエディット情報を初期化する */
					this->HoldEditData.iEditEffect	= EDIT_EFFECT_NONE;
					this->HoldEditData.iEditRank	= EDIT_RANK_NONE;
					this->HoldEditData.iEditCost	= 0;
					this->HoldEditData.aText		= "";
					this->iHoldSelectItemType		= SELECT_TYPE_NONE;

					/* "決定"のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);
					break;

				/* 交換可能 */
				case SELECT_STATUS_INTERCHANGEABLE:
					{
						/* 現在登録されているエディット情報を変数で保存 */
						EDIT_DATA stEditData = *this->astSelectItemList[this->iSelectItem].pstEditData;

						/* ホールド中のエディット情報を現在の選択項目に設定する */
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= this->HoldEditData.iEditEffect;
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= this->HoldEditData.iEditRank;
						this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost	= this->HoldEditData.iEditCost;
						this->astSelectItemList[this->iSelectItem].pstEditData->aText		= this->HoldEditData.aText;

						/* 変数に保存したエディット情報をホールド中のエディット情報に設定する */
						this->HoldEditData			= stEditData;
						this->iHoldSelectItemType	= this->astSelectItemList[this->iSelectItem].iSelectItemType;
					}
					/* "決定"のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

					break;

				/* 選択不可 */
				case SELECT_STATUS_IMPOSSIBLE:
					/* 処理を行わない(音を出す) */
					/* "キャンセル"のSEを再生 */
					gpDataList_Sound->SE_PlaySound(SE_SYSTEM_CANCEL);
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
				/* "決定"のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

				/* 最初にエディット画面を追加するか確認 */
				if (this->StageStatusList->bGetFastEditFlg() == true)
				{
					// 追加する場合
					/* ゲーム状態を"リセット"に変更する */
					this->StageStatusList->SetGameStatus(GAMESTATUS_RESET);

					/* 最初にエディット画面を追加しない状態にする */
					this->StageStatusList->SetFastEditFlg(false);
				}
				else
				{
					// 追加しない場合
					/* ゲーム状態を"次のステージへ遷移"に変更する */
					this->StageStatusList->SetGameStatus(GAMESTATUS_NEXTSTAGE);
				}

				/* 決定時の処理を終了する */
				return;
			}
			else
			{
				// "次へ"でない場合
				/* "決定"のSEを再生 */
				gpDataList_Sound->SE_PlaySound(SE_SYSTEM_DICISION);

				/* 登録されているエディットの取得処理を実施 */
				// 対象のエディットが存在するか確認
				if (this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect != EDIT_EFFECT_NONE)
				{
					// 存在する場合
					/* 選択項目に設定されたエディット情報をホールド中のエディットに代入する */
					this->HoldEditData.iEditEffect	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect;
					this->HoldEditData.iEditRank	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank;
					this->HoldEditData.iEditCost	= this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost;
					this->HoldEditData.aText		= this->astSelectItemList[this->iSelectItem].pstEditData->aText;

					/* 選択項目の種類を設定する */
					this->iHoldSelectItemType = this->astSelectItemList[this->iSelectItem].iSelectItemType;

					/* エディット情報を回収した選択項目のエディット情報を初期化する */
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditEffect	= EDIT_EFFECT_NONE;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditRank	= EDIT_RANK_NONE;
					this->astSelectItemList[this->iSelectItem].pstEditData->iEditCost	= 0;
					this->astSelectItemList[this->iSelectItem].pstEditData->aText		= "";
				}
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
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を上に進める */
		this->iSelectItem -= 6;
	}

	/* "下"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_DOWN))
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を下に進める */
		this->iSelectItem += 6;
	}

	/* "左"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_LEFT))
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を左に進める */
		this->iSelectItem -= 1;
	}

	/* "右"が入力されているか */
	if (gpDataList_Input->bGetInterfaceInput(INPUT_TRG, UI_RIGHT))
	{
		// 入力されている場合
		/* "カーソル移動"のSEを再生 */
		gpDataList_Sound->SE_PlaySound(SE_SYSTEM_MOVECURSOR);

		/* 選択項目を右に進める */
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
	if (this->HoldEditData.iEditEffect != EDIT_EFFECT_NONE)
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
					/* 所持ブラッドがホールド中のエディットのコスト未満であるなら選択不可に設定 */
					if (this->GameResourceList->iGetHaveBlood() < this->HoldEditData.iEditCost)
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

		/* ロック数に応じて対象のエディット個所を選択不可に設定 */
		switch (this->iNewEditNumber)
		{
			/* 新規エディット数が"5個"の場合 */
			case NEW_EDIT_NO_RANK_S:
				/* ロックは設定しない */
				break;

			/* 新規エディット数が"4個"の場合 */
			case NEW_EDIT_NO_RANK_B:
				/* 新規のエディットの5個目を設定不可に */
				this->astSelectItemList[SELECT_ITEM_NEW_EDIT_END].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				break;

			/* 新規エディット数が"3個"の場合 */
			case NEW_EDIT_NO_RANK_C:
				/* 新規のエディットの5個目と4個目を設定不可に */
				this->astSelectItemList[SELECT_ITEM_NEW_EDIT_END].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
				this->astSelectItemList[SELECT_ITEM_NEW_EDIT_END - 1].iSelectStatus = SELECT_STATUS_IMPOSSIBLE;
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
}

