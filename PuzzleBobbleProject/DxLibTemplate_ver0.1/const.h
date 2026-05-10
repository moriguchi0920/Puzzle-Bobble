#ifndef __CONST_H__
#define __CONST_H__
	
const double SCROLL_SPEED = 3.0;
// 各種類ごとのオブジェクトの最大数
const int OBJECT_MAX = 200;
// 全オブジェクトの最大数
const int ALL_OBJECT_MAX = 4000;
// CollisionInfoの保存最大数
const int COLLISION_SAVE_MAX = 100;
// 各当たり判定オブジェクトが持つCollisionInfoのインデックスの最大数
const int INFO_INDEX_MAX = 10;
// インデックスの初期値
const int INFO_INDEX_DEFAULT = -1;
// CollisionInfoの中身の初期値
const int INFO_VAR_DEFAULT = -1;

const int SPRITE_SIZE = 25;


const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 576;

const int STAGE_OFFSET_X = 312;


const double PI = 3.1415926535;
const float PI_F = 3.141592;


const float PRIORITY_SPRITE = 0.5f;

const int DIRECTION = 6;

const int ROW_EVEN = 8;
const int ROW_ODD = 7;

const int COL = 13;

const int BUBBLE_RADIUS = 25;
const float BUBBLE_MOVE_SPEED = 15.0f;

const float BALLISTA_BASE_X = 512.0f;
const float BALLISTA_BASE_Y = 500.0f;

const int CheckIdxOffsetEven[DIRECTION][2] =
{
	{-1, 0},
	{-1, 1},
	{0, -1},
	{0 , 1},
	{1,  0},
	{1,  1}
};

const int CheckIdxOffsetOdd[DIRECTION][2] =
{
	{-1, -1},
	{-1, 0},
	{0, -1},
	{0 , 1},
	{1,  -1},
	{1,  0}
};


// 画像マネージャーが管理できる画像情報の総数
const int IMAGE_INFO_LENGTH = 64;

const int SOUND_INFO_LENGTH = 64;

#endif