/* 2025.01.22 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include "GameStatusDefine.h"

/* ゲーム状態管理クラスの宣言 */

// ゲーム状態管理クラス
class DataList_GameStatus : public DataListBase
{
	public:
		DataList_GameStatus();				// コンストラクタ
		virtual ~DataList_GameStatus() {};	// デストラクタ

		/* データ取得 */
		int		iGetGameStatus()	{ return this->iGameStatus; };	// ゲーム状態を取得
		int		iGetNowStageNo()	{ return this->iNowStageNo; };	// 現在のステージ番号を取得
		int		iGetEndStageNo()	{ return this->iEndStageNo; };	// 最終ステージ番号を取得

		/* データ設定 */
		void	SetGameStatus(int iGameStatus)	{ this->iGameStatus = iGameStatus; };	// ゲーム状態を設定
		void	SetNowStageNo(int iNowStageNo)	{ this->iNowStageNo = iNowStageNo; };	// ゲーム状態を設定
		void	SetEndStageNo(int iEndStageNo)	{ this->iEndStageNo = iEndStageNo; };	// 最終ステージ番号を設定

	private:
		/* 管理するデータ */
		int		iGameStatus;	// ゲーム状態
		int		iNowStageNo;	// 現在のステージ番号
		int		iEndStageNo;	// 最終ステージ番号

	protected:
};
