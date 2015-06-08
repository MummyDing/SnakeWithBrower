

#pragma once

class Csnake  
{
public:
	Csnake();
	~Csnake();
	CPoint ForsnakeUp();
	CPoint ForsnakeRight();
	CPoint ForsnakeDown();
	CPoint ForsnakeLeft();

public :
	int n;  //代表蛇长
	CPoint body[200];//代表蛇身
	int direction;  //蛇的行动方向
	 
	int sorce; //当前分数
	int MaxSorce; //历史最高分
};

