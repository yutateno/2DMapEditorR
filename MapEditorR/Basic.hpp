#pragma once



/*
��{
*/


/// �}�N��-------------------------------------------------------------------------------------

// �|�C���^�p����}�N��
#define POINTER_RELEASE(p)	\
{	\
	if (p != nullptr)	\
	{	\
		delete p;	\
		p = nullptr;	\
	}	\
}	\

// 2D�֘A�摜����}�N��
#define GRAPHIC_RELEASE(p)	\
{	\
	if (p != -1)	\
	{	\
		DeleteGraph(p);	\
		p = -1;	\
	}	\
}	\

