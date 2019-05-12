#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"



/*
マップエディター
*/
class MapEditor : public BaseScene
{
public:
	MapEditor();
	~MapEditor();


	void Draw() override;
	void Process() override;
};

