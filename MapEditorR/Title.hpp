#pragma once
#include "BaseScene.hpp"
#include "Basic.hpp"
#include "Input.hpp"



/*
�^�C�g��
*/
class Title : public BaseScene
{
public:
	Title();
	~Title();


	void Draw() override;
	void Process() override;
};

