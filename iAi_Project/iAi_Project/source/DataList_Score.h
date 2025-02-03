/* 2025.01.30 駒沢風助 ファイル作成 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "ScoreDefine.h"

/* スコア関連管理データリストの宣言 */

// スコア関連管理データリスト
class DataList_Score : public DataListBase
{
	public:
		DataList_Score();				// コンストラクタ
		virtual ~DataList_Score();		// デストラクタ

		int		iGetPlayerComboNowCount() { return this->iPlayerComboNowCount; }				// プレイヤーの現在のコンボ数を取得
		int		iGetPlayerComboMaxCount() { return this->iPlayerComboMaxCount; }				// プレイヤーの最大コンボ数を取得
		int		iGetPlayerComboDuration() { return this->iPlayerComboDuration; }				// プレイヤーのコンボの残り持続時間を取得

		void	SetPlayerComboNowCount(int iPlayerComboNowCount) { this->iPlayerComboNowCount = iPlayerComboNowCount; }				// プレイヤーの現在のコンボ数を設定
		void	SetPlayerComboMaxCount(int iPlayerComboMaxCount) { this->iPlayerComboMaxCount = iPlayerComboMaxCount; }				// プレイヤーの最大コンボ数を設定
		void	SetPlayerComboDuration(int iPlayerComboDuration) { this->iPlayerComboDuration = iPlayerComboDuration; }				// プレイヤーのコンボの残り持続時間を設定

	private:
		/* 変数 */
		int		iPlayerComboNowCount;			// プレイヤーの現在のコンボ数
		int		iPlayerComboMaxCount;			// プレイヤーの最大コンボ数
		int		iPlayerComboDuration;			// プレイヤーのコンボの残り持続時間

};
