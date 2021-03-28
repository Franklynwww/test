#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_STACK_SIZE 100
#define STACKINCREMENT 20
typedef int Status;
typedef char SElemType;
typedef struct SqStack
{
	SElemType* base;//栈底指针，也为栈中数组的首元素指针
	SElemType* top;//栈顶指针
	int stacksize;//栈的大小

}SqStack;//顺序栈类型定义

#include<fstream>
#include<iostream>
using namespace std;
Status InitStack(SqStack &S)
{ //初始化栈
	S.base = new SElemType[MAX_STACK_SIZE];
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;//初始化时栈底指针和栈顶指针重合
	S.stacksize = MAX_STACK_SIZE;
	return OK;
}

Status DestroyStack(SqStack &S)
{ //销毁栈
	delete S.base;
	S.base = NULL;
	S.top = NULL;
	S.stacksize = 0;
	return OK;
}

Status ClearStack(SqStack &S)
{ //清空栈
	S.top = S.base;//因为使用指针向栈中写入元素，所以清空栈时不用重新分配空间
	return OK;
}

Status StackEmpty(SqStack S)
{ //若栈S为空栈，则返回TRUE，否则返回FALSE
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

Status StackFull(SqStack S)
{ //若栈S已满，则返回TRUE，否则返回FALSE
	if (S.top - S.base == S.stacksize)
		return TRUE;
	else
		return FALSE;
}


int StackLength(SqStack S)
{ //返回栈的长度
	return S.top - S.base;
}

Status GetTop(SqStack S, SElemType *e)
{ //若栈不空，则用e返回S的栈顶元素
	if (S.top > S.base)//栈不空
	{
		*e = *(S.top - 1);
		return OK;
	}
	else
		return ERROR;
}

Status Push(SqStack &S, SElemType e)
{ //若栈不满，元素e为新的栈顶元素入栈
	if (StackFull(S)) //栈满，追加存储空间
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, SElemType &e)
{ //若栈不空，S的栈顶元素出栈，用e返回其值
	if (StackEmpty(S))//栈空
		return ERROR;
	e = *--S.top;
	return OK;
}

Status StackTraverse(SqStack S, Status(*visit)(SElemType))
{ //遍历栈中元素，从栈底到栈顶依次对栈中每个元素调用函数visit()
	while (S.top > S.base)
		visit(*S.base++);
	return OK;
}

Status Print(SElemType e)
{
	cout << e << " ";
	return OK;
}

void LineEdit()
{//行编辑
	SqStack S;
	char p[80];
	ofstream f1("d:\\dt.dat", ios::out|ios::binary);//打开二进制数据文件，准备写
	InitStack(S);
	char ch;
	SElemType s;
	ch =getchar();//读取一个字符
	while (ch != EOF)//整个文件未结束
	{
		while (ch != EOF && ch != '\n')//接收并编辑文件的一行
		{
			switch (ch)//接收这一行的第一个字符
			{
			case'#': {Pop(S, ch); break; } //退格符，将这一行的上一个字符清除，即当栈非空时出栈
			case'@': {ClearStack(S); break; } //退行符，将这一行清除，即重置S为空栈
			default: {Push(S, ch);  break; } // 有效字符，进栈
			}
			ch = getchar();    //接收这一行的下一个字符
		} //编辑一行完成
		while(S.base<S.top)
		{
			s = *(S.base);
			f1.write((char*)&s, sizeof(SElemType));
			S.base++;
		}//向数据文件中写入刚刚编辑好的这一行
		f1 << "\n";
		ClearStack(S);      // 重置S为空栈，准备接收文件的下一行
		if(ch!=EOF){ ch = getchar(); }//接收下一行的第一个字符
	}
	f1.close();
	ifstream f2("d:\\dt.dat", ios::in); //打开二进制数据文件，准备读
	while (!f2.eof())
	{
		f2.getline(p, 80);
		cout << p<< endl;
	}
	f2.close();
}


int main() { 
LineEdit();
return 0;
}