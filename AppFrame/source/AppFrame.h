/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once

/* AppFrameの基本参照ファイル */
// ※ソリューションでこのヘッダファイルで定義されたシステムを使用する場合、このファイルをincludeしてください

#pragma comment(lib,"AppFrame.lib")

/* ライブラリ */
#include "DxLib.h"

/* 定義 */
#include "AppConstantDefine.h"
#include "AppFunctionDefine.h"
#include "AppStructDefine.h"
#include "AppVariableDefine.h"

/* シーン系 */
#include "SceneBase.h"
#include "SceneServer.h"

/* データリスト系 */
#include "DataListBase.h"
#include "DataListServer.h"

/* オブジェクト系 */
#include "ObjectBase.h"
#include "CharacterBase.h"
#include "EffectBase.h"
#include "ActorBase.h"
#include "PlatformBase.h"
#include "BulletBase.h"
#include "EnemyBase.h"
#include "SkySqhereBase.h"
#include "EffectItemBase.h"
#include "PickUpItemBase.h"