#include "stdafx.h"
# include <Siv3D.hpp> // Siv3D v0.6.14
#include "Common.h"
#include "GameScene.h"

// 図形を仕分けてスコアを競うゲーム.

void Main()
{
	App manager;
	manager.add<Title>(SceneSwitch::Title);
	manager.add<Stage>(SceneSwitch::Stage);
	manager.add<LetsPlay>(SceneSwitch::Letsplay);
	manager.add<Result>(SceneSwitch::Result);

	manager.init(SceneSwitch::Title, 0s);// Title シーンから始めて, 0s 後に開始.

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
