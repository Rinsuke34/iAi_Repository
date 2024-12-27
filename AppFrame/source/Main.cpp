/* 2024.12.08 駒沢風助 ファイル作成 */

#include "Main.h"
#include "AppVariableDefine.h"
#include "AppConstantDefine.h"
#include "AppFunctionDefine.h"

/* プログラムのメインループ */

// メインプログラム
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/* 名前空間の省略 */
	using namespace Main;	// WinMain関数で使用する関数、変数宣言

	/* DXライブラリ初期化処理 */
	Main::DxLibInit();

	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return -1;
	}

	/* メインプログラム初期化処理 */
	Main::MainInit();

	/* メインループ */
	while (ProcessMessage() == 0)
	{
		/* プログラム終了フラグを確認*/
		if (gbEndFlg == true)
		{
			/* 有効であるならメインループを抜ける(プログラム終了) */
			break;
		}

		/* プレイヤーの入力を取得 */
		gpPlayerInput->Input();

		/* シーン処理 */
		/* 計算 */
		gpSceneServer->SceneProcess();

		/* 描写 */
		ClearDrawScreen();
		{
			/* 描写(通常) */
			gpSceneServer->SceneDraw();

			/* デバッグ用描写 */
			Main::DebugDraw();
		}
		ScreenFlip();

		/* フレームレート調整 */
		gpFps->FpsUpdate();
		gpFps->FpsWait();
	}

	/* 終了処理 */
	Main::MainEnd();

	return 0;
}

// DXライブラリ初期化
void Main::DxLibInit()
{
	/* DXLibの重複を可能にする(通信テスト用) */
	SetDoubleStartValidFlag(TRUE);

	/* 画面の解像度を横1920×縦1080、1ドットあたり32ビットに指定する */
	SetGraphMode(SCREEN_SIZE::WIDE, SCREEN_SIZE::HEIGHT, 32);

	// ウィンドウモードに指定する
	ChangeWindowMode(true);

	// ウィンドウが非アクティブでもプログラムを実行させる
	SetAlwaysRunFlag(true);

	/* マウス座標を画面中央に設定 */
	SetMousePoint(SCREEN_SIZE::WIDE / 2, SCREEN_SIZE::HEIGHT / 2);

	// マウスカーソルを非表示にする
	SetMouseDispFlag(FALSE);

	/* ジョイパッドのデッドゾーンを設定 */
	//SetJoypadDeadZone(PAD_INPUT_1, double Zone);
}

// メインプログラム初期化
void Main::MainInit()
{
	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// FPSを固定するクラスを追加
	gpFps = new Fps();

	// プレイヤー入力を取得するクラスを追加
	gpPlayerInput = new PlayerInput();

	// シーンサーバーを作成
	gpSceneServer = new SceneServer();

	// データリストサーバーを作成
	gpDataListServer = new DataListServer();

	// シーンを初期状態に設定
	// ※共通のAppFlameを使用するため各プログラムに応じたシーンに設定する
	SCENE_SET::SetFastScene();

	// プロジェクト初期化処理
	PROJECT_INIT::Init();
}

// 終了処理
void Main::MainEnd()
{
	// プレイヤー入力を取得するクラスを削除する
	delete gpPlayerInput;

	// FPSを固定するクラスを削除する
	delete gpFps;

	// シーンサーバーを削除する
	delete gpSceneServer;

	// データリストサーバーを削除する
	delete gpDataListServer;

	// DXライブラリの使用を終了する
	DxLib_End();
}

// デバッグ描写
void Main::DebugDraw()
{
	/* 対応したデバッグ用フラグが有効であるならばデバッグ用描写を行う */
	/* シーンリスト描写 */
	if (gbDrawSceneListFlg == true)
	{
		gpSceneServer->DrawSceneList();
	}

	/* データリスト描写 */
	if (gbDrawDatalistFlg == true)
	{
		gpDataListServer->DrawDataList();
	}
}
