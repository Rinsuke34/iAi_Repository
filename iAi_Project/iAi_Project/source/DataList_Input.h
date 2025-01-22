/* 2024.12.21 駒沢風助 ファイル作成 */

#pragma once
#include <vector>
#include "AppFrame.h"
#include "InputDefine.h"

/* プレイヤー入力管理クラスの宣言 */

// プレイヤー入力管理クラス
class DataList_Input : public DataListBase
{
	public:
		DataList_Input();				// コンストラクタ
		virtual ~DataList_Input();		// デストラクタ

		/* インターフェイス用入力取得 */
		bool	bGetInterfaceInput(int iInputType, int iGetInputUI);		// インターフェイス入力取得

		/* ゲームプレイ用入力取得 */
		bool	bGetGameInputAction(int iInputType, int iGetInputGame);		// ゲームプレイ用入力取得(アクション)
		float	fGetGameInputMove();										// ゲームプレイ用入力取得(移動量)
		VECTOR	vecGetGameInputMoveDirection();								// ゲームプレイ用入力取得(移動方向)

	private:
		/* 関数 */
		void JsonDataLoad();		// Jsonからデータをロード

		/* キーコンフィグ情報 */
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigJoypad;			// ジョイパッド
		std::vector<Struct_Json_Input::CONFIG_INFO*>	stConfigKeyboardMouse;	// キーボード＆マウス

		/* キーコンフィグ用関数 */
		std::string	GetControlName(int iGameControl);		// ゲーム操作の種類から入力の名称を取得

		/* 関数 */
		void	ConfigReset();																																// キーコンフィグをリセット
		void	ConfigDelete();																																// キーコンフィグを削除
		bool	bGetInputCode(const std::vector<Struct_Json_Input::CONFIG_INFO*>& stConfig, int& iInputCode, int& iIquipmentType, int iTargetInputGame);	// キーコンフィグから入力コード取得

	protected:
};