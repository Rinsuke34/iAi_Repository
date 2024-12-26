/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once

/* AppFrameで使用する関数の宣言 */

// シーンの設定
namespace SCENE_SET
{
	// ※この関数は各プログラム毎に内容を変更する必要があるため、AppFrameでは宣言のみ行い各プロジェクトで定義する
	void	SetFastScene();		// ゲーム起動時のシーンをセット
	void	SetLoadScene();		// ロードシーンをセット
}

// 初期化
namespace PROJECT_INIT
{
	void	Init();				// プロジェクト初期化処理
}

// 汎用計算系
namespace PUBLIC_PROCESS
{
	float	fClamp(float fValue, float fMax, float fMin);	// 値を範囲内に収める
}

