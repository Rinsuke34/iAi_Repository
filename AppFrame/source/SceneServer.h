/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include "SceneBase.h"
#include <list>

/* 実行中のシーンの管理を行うクラスの宣言 */
// ※vectorを使用するとエラーが発生したためlistでクラスを管理する

// シーンサーバークラス
class SceneServer
{
	public:
		SceneServer();				// コンストラクタ
		virtual ~SceneServer();		// デストラクタ

		void	SceneProcess();		// シーン計算処理
		void	SceneDraw();		// シーン描画処理
		void	DrawSceneList();	// データリスト描画(デバッグ用)

		void	AddSceneReservation(SceneBase* NewScene, const bool bAddLoadScene);		// シーン追加予約

	private:
		// シーンリスト
		std::list<SceneBase*> pstSceneList;

		// 追加予定のシーンリスト
		std::list<SceneBase*> pstAddSceneList;

		/* 関数 */
		void	AddScene();						// シーンリストへのシーン追加
		void	SceneSortLayerOrder();			// シーンリストの並び替え(レイヤー順序の大きい順)
		void	DeleteUnnecessaryScene();		// シーン削除(削除フラグが有効なシーンに対して)
		void	DeleteAllScene();				// シーン削除(シーンリスト内のすべてのシーンに対して)
		void	DeleteAllAddScene();			// シーン削除(追加予定のシーンリスト内のすべてのシーンに対して)

		/* 変数 */
		bool	bSceneDeleteFlg;			// シーン削除フラグ(削除予定のシーンがあるならば有効にする)
		bool	bSceneAddFlg;				// シーン追加フラグ(追加予定のシーンがあるならば有効にする)
		bool	bDeleteCurrentSceneFlg;		// 現行シーン削除フラグ(シーンリスト内のすべてのシーンを削除するかのフラグ)

	protected:
};
