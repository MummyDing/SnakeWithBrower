

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
	int n;  //�����߳�
	CPoint body[200];//��������
	int direction;  //�ߵ��ж�����
	 
	int sorce; //��ǰ����
	int MaxSorce; //��ʷ��߷�
};

