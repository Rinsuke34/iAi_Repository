/* 2025.01.22 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include "GameStatusDefine.h"

/* 画面エフェクト */
#include "ScreenEffect_Base.h"

/* ゲーム状態管理クラスの宣言 */

// ゲーム状態管理クラス
class DataList_GameStatus : public DataListBase
{
	public:
		DataList_GameStatus();				// コンストラクタ
		virtual ~DataList_GameStatus() {};	// デストラクタ

		/* データ取得 */
		// リスト
		std::vector<ScreenEffect_Base*>& GetScreenEffectList() { return this->pScreenEffectList; }		// 画面エフェクトリスト取得
		// 単独
		int		iGetGameStatus()	{ return this->iGameStatus; };	// ゲーム状態を取得
		int		iGetNowStageNo()	{ return this->iNowStageNo; };	// 現在のステージ番号を取得
		int		iGetEndStageNo()	{ return this->iEndStageNo; };	// 最終ステージ番号を取得
		bool	bGetGameSlowFlg()	{ return this->bGameSlowFlg; };	// スローモーションフラグを取得		/*2025.02.05 菊池雅道 スローモーションに関する関数追加 */

		/* データ設定 */
		// リスト
		void	SetScreenEffect(ScreenEffect_Base* pScreenEffect)	{ pScreenEffectList.emplace_back(pScreenEffect); };			// エネミー追加
		// 単独
		void	SetGameStatus(int iGameStatus)		{ this->iGameStatus		= iGameStatus; };	// ゲーム状態を設定
		void	SetNowStageNo(int iNowStageNo)		{ this->iNowStageNo		= iNowStageNo; };	// ゲーム状態を設定
		void	SetEndStageNo(int iEndStageNo)		{ this->iEndStageNo		= iEndStageNo; };	// 最終ステージ番号を設定
		void	SetGameSlowFlg(bool bGameSlowFlg)	{ this->bGameSlowFlg	= bGameSlowFlg; };	// スローモーションフラグを設定		/*2025.02.05 スローモーションに関する菊池雅道 関数追加 */

	private:
		/* 管理するデータリスト */
		std::vector<ScreenEffect_Base*>	pScreenEffectList;	// 画面エフェクトリスト

		/* 管理するデータ */
		int		iGameStatus;	// ゲーム状態
		int		iNowStageNo;	// 現在のステージ番号
		int		iEndStageNo;	// 最終ステージ番号
		bool	bGameSlowFlg;	// スローモーションフラグ		/*2025.02.05 菊池雅道 変数追加 */
};
