//#pragma once
//
///*
//��{
//*/
//
///// �C���N���[�h�t�@�C��--------------------------------------------------------
//#include "DxLib.h"
//#include <vector>
//
//
///// �F��ȏ��Ŏg�������Ȃ���----------------------------------------------------
//
//// �V�[���̓���
//enum class ESceneNumber
//{
//	TITLE, MAPEDITOR
//};
//
//
//namespace BASICPARAM
//{
//	// ���O�̃V�[��
//	extern ESceneNumber e_preScene;
//
//	// ���̃V�[��
//	extern ESceneNumber e_nowScene;
//
//	// �摜ID�̔ԍ�
//}
//
//
///// �}�N��-------------------------------------------------------------------------------------
//
//// �|�C���^�p����}�N��
//template<typename T>
//constexpr void POINTER_RELEASE(T p) { if(p!=nullptr) {delete p; (p)=nullptr; } }
//
//// 2D�֘A�摜����}�N��
//template<typename T>
//constexpr void  GRAPHIC_RELEASE(T p) { if(p!=-1) { DeleteGraph(p); (p)=-1; } }
//
