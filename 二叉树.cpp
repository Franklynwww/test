#include<iostream>
using namespace std;
#define OK 1
#define TRUE 1
#define ERROR -1
#define FALSE 0 

#define STACK_INIT_SIZE 100     //存储空间初始分配量
#define STACKINCREMENT 10//存储空间分配增量
typedef int Status;
typedef char TElemType;//定义二叉树的元素类型为字符型
TElemType Nil = '-'; //字符型以#号为空



typedef struct BiTNode
{//二叉链表的类型定义
	TElemType data;//结点数据域，即结点的元素值
	struct BiTNode *lchild, *rchild; //左右孩子指针域
}BiTNode;

typedef BiTNode* BiTree;//二叉树类型定义


Status InitBiTree(BiTree &T)
{ //初始化空二叉树
	T = NULL;
	return OK;
}

Status ClearBiTree(BiTree &T)
{//后序清除二叉树
	if (T)
	{
		if ((T)->lchild)
			ClearBiTree(T->lchild); //清除左孩子子树
		if ((T)->rchild)
			ClearBiTree(T->rchild); //清除右孩子子树
		free(T); //最后释放根结点
		T = NULL;//销毁后置空
	}
	return OK;
}


Status DestroyBiTree(BiTree &T)
{//后序销毁二叉树
	if (T)
	{
		if ((T)->lchild)
			DestroyBiTree(T->lchild); //销毁左孩子子树
		if ((T)->rchild)
			DestroyBiTree(T->rchild); //销毁右孩子子树
		free(T); //最后释放根结点
		T = NULL;//销毁后置空
	}
	return OK;
}

void CreateBiTree(BiTree &T)
{//先序创建二叉树
	TElemType ch;

	cin >> ch;

	if (ch == Nil)
		T = NULL;
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)
			exit(OVERFLOW);
		(T)->data = ch; //生成根结点 
		CreateBiTree(T->lchild); //构造左子树
		CreateBiTree(T->rchild); //构造右子树
	}
}


Status BiTreeEmpty(BiTree T)
{//二叉树判空
	if (T)
		return FALSE;
	else
		return TRUE;
}


int BiTreeDepth(BiTree T)
{ //返回二叉树的深度
	int i, j;
	if (!T)
		return 0;

	i = BiTreeDepth(T->lchild);
	j = BiTreeDepth(T->rchild);
	return i > j ? i + 1 : j + 1;//二叉树的深度=max{左子树深度，右子树深度}+1
}




TElemType Root(BiTree T)
{ //返回二叉树的根结点
	if (BiTreeEmpty(T))
		return NULL;
	else
		return T->data;
}

TElemType Value(BiTree p)
{
	//操作结果: 返回p所指结点
	return p->data;
}

Status Assign(BiTree p, TElemType value)
{ //将p所指结点赋值为value
	p->data = value;
	return OK;
}

Status print(TElemType e)
{//打印输出
	cout << (char)e;//字符型数据打印输出

	return OK;
}


void PreOrderTraverse(BiTree T, Status(*Visit)(TElemType))
{

	//先序遍历T,对每个结点调用函数Visit一次且仅一次
	if (T)
	{
		Visit(T->data); //先访问根结点
		cout << " ";
		PreOrderTraverse(T->lchild, Visit); //再先序遍历左子树
		PreOrderTraverse(T->rchild, Visit); //最后先序遍历右子树

	}
}




void InOrderTraverse(BiTree T, Status(*Visit)(TElemType))
{
	//中序遍历T,对每个结点调用函数Visit一次且仅一次
	if (T)
	{
		InOrderTraverse(T->lchild, Visit); //先中序遍历左子树
		Visit(T->data); //再访问根结点
		cout << " ";
		InOrderTraverse(T->rchild, Visit); //最后中序遍历右子树

	}
}



void PostOrderTraverse(BiTree T, Status(*Visit)(TElemType))
{

	//后序遍历T,对每个结点调用函数Visit一次且仅一次
	if (T)
	{
		PostOrderTraverse(T->lchild, Visit); //先后序遍历左子树 
		PostOrderTraverse(T->rchild, Visit); //再后序遍历右子树 
		Visit(T->data); //最后访问根结点 
		cout << " ";
	}
}

Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType))
{
	//不使用队列，层序遍历T,对每个结点调用函数Visit一次且仅一次
	BiTree Q[200], p;//定义一个从左到右，从上到下存储二叉树各个结点指针的指针数组Q
	int front, rear;//指示下标的指针front，rear
	front = rear = 0;
	if (!T)return ERROR;//树空
	Q[rear++] = T;//树不空，数组首元素存储树的根结点
	while (front != rear)//二叉树中的结点尚未遍历完
	{
		p = Q[front++];//依次取数组中的每一个元素，相当于二叉树中的一个结点，先访问该结点，再将其左右孩子入数组
		Visit(p->data); //先访问该结点 
		cout << " ";
		if (p->lchild)Q[rear++] = p->lchild;//左孩子存在时，左孩子入数组
		if (p->rchild)Q[rear++] = p->rchild;//右孩子存在时，右孩子入数组
	}
}



int CountLeaf(BiTree T)
{//统计叶子结点个数
	int k = 0;
	int i = 0, j = 0;
	if (T) {
		if ((!T->lchild) && (!T->rchild))k++;//根结点是叶子结点，k+1
		i = CountLeaf(T->lchild);//左子树上的叶子结点数i
		j = CountLeaf(T->rchild);//右子树上的叶子结点数j
	}
	return i + j + k;
}


BiTree CreateTreeNode(TElemType e, BiTree lptr, BiTree rptr)
{ //生成一个二叉树的结点，值为e，左指针域为lptr，右指针域为rptr
	BiTree T;
	if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(1); 	T->data = e;
	T->lchild = lptr;
	T->rchild = rptr;
	return T;
}

BiTree CopyTree(BiTree T)
{//二叉树的复制
	BiTree newlptr = NULL;
	BiTree newrptr = NULL;
	BiTree newT = NULL;
	if (!T) return NULL;
	if (T->lchild) newlptr = CopyTree(T->lchild);//复制左子树
	if (T->rchild)newrptr = CopyTree(T->rchild);//复制右子树
	newT = CreateTreeNode(T->data, newlptr, newrptr);	//生成结点 
	return newT;
}

BiTree Point(BiTree T, TElemType e)
//返回二叉树指向结点e的指针(二叉树中最多只有一个结点的元素值为e）
{
	BiTree p = NULL;
	if (T->data == e)//找到元素值为e的结点，返回其指针
	{
		p = T;
	}
	if (!p) {//还没找到元素值为e的结点
		if (T->lchild)
			p = Point(T->lchild, e); //在左孩子中找
	}
	if (!p) {//还没找到元素值为e的结点
		if (T->rchild)
			p = Point(T->rchild, e); //在右孩子中找
	}
	return p;
}

TElemType LeftChild(BiTree T, TElemType e)
{
	//返回结点e的左孩子结点
	BiTree a;
	if (T)
	{
		a = Point(T, e); //a是结点e的指针
		if (a&&a->lchild) //T中存在结点e且该结点存在左孩子
			return a->lchild->data; //返回结点e的左孩子
	}
	return Nil;

}

TElemType RightChild(BiTree T, TElemType e)
{
	//返回结点e的右孩子结点
	BiTree a;
	if (T)
	{
		a = Point(T, e); //a是结点e的指针
		if (a&&a->rchild) //T中存在结点e且该结点存在右孩子
			return a->rchild->data;  //返回结点e的右孩子
	}
	return Nil;
}

Status Parent(BiTree T, TElemType e)
{
	//返回结点e的双亲结点，大致思路与层序遍历一致，只是不需要访问各个结点
	BiTree Q[200], p;//定义一个从左到右，从上到下存储二叉树各个结点指针的指针数组Q
	int front, rear;//指示下标的指针front，rear
	front = rear = 0;
	if (!T)return ERROR;//树空
	Q[rear++] = T;//树不空，数组首元素存储树的根结点
	while (front != rear)//二叉树中的结点尚未遍历完
	{
		p = Q[front++];//依次取数组中的每一个元素，相当于二叉树中的一个结点，先访问该结点，再将其左右孩子入数组
		if (p->lchild)Q[rear++] = p->lchild;//左孩子存在时，左孩子入数组
		if (p->rchild)Q[rear++] = p->rchild;//右孩子存在时，右孩子入数组
	}//指针数组Q中存储了整棵二叉树从左到右，从上到下的所有结点的指针，总的结点数为最后退出循环时的front/rear的值
	for (int i = 0; i < front; i++) {
		if (Q[i]->lchild&&Q[i]->lchild->data == e || Q[i]->rchild&&Q[i]->rchild->data == e)//找到了某个结点的左/右孩子的值为e，则该结点为结点e的双亲结点
		{
			return Q[i]->data;//返回结点e的双亲结点
			break;//退出循环
		}
	}
	return Nil;//找不到，返回空
}

TElemType LeftSibling(BiTree T, TElemType e)
{
	//返回结点e的左兄弟
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e); //a为e的双亲结点
		p = Point(T, a); //p为指向e的双亲结点的指针
		if (p->lchild&&p->rchild&&p->rchild->data == e) //p存在左右孩子且右孩子是e，就说明结点e有左兄弟
			return p->lchild->data; //返回p的左孩子(e的左兄弟)
	}
	return Nil; //找不到，返回空
}

TElemType RightSibling(BiTree T, TElemType e)
{
	//返回结点e的右兄弟
	TElemType a;
	BiTree p;
	if (T)
	{
		a = Parent(T, e); //a为e的双亲结点
		p = Point(T, a);//p为指向e的双亲结点的指针
		if (p->lchild&&p->rchild&&p->lchild->data == e) //p存在左右孩子且左孩子是e，就说明结点e有右兄弟
			return p->rchild->data; //返回p的右孩子(e的右兄弟)
	}
	return Nil;//找不到，返回空
}



Status InsertChild(BiTree &T, TElemType s, BiTree c)
{//插入二叉树c，作为原二叉树中某结点的左/右子树
	char ch;
	if (!Point(T, s))//找不到结点
	{
		cout << "找不到此结点" << endl;
		return ERROR;
	}
	else
		if ((Point(T, s)->lchild) && (Point(T, s)->rchild)) {//双亲结点左右子树均不为空
			cout << "所选的结点左右子树均不空，不能插入二叉树c作为其左/右子树！" << endl;
			return ERROR;
		}
		else {
			//结点至少有一子树为空
			if (!(Point(T, s)->lchild) || !(Point(T, s)->rchild)) {
				cout << "请问要将二叉树c作为该结点的左子树还是右子树？L：左子树；R：右子树" << endl;
				cin >> ch;
				if (!(Point(T, s)->lchild) && !(Point(T, s)->rchild))//结点左右子树均为空
				{
					if (ch == 'L') //插入二叉树c作为其左子树
					{
						Point(T, s)->lchild = c;
						return OK;
					}
					if (ch == 'R') //插入二叉树c作为其右子树
					{
						Point(T, s)->rchild = c;
						return OK;
					}
				}
				else
					if ((Point(T, s)->lchild) && !(Point(T, s)->rchild))//结点左子树不空，右子树空
					{
						if (ch == 'L') //由于结点左子树不空，故不能将插入二叉树c作为其左子树
						{
							cout << "所选的结点左子树不空，不能插入二叉树c作为其左子树！" << endl;
							return ERROR;
						}
						if (ch == 'R') //插入二叉树c作为其右子树
						{
							Point(T, s)->rchild = c;
							return OK;
						}
					}
					else
						if (!(Point(T, s)->lchild) && (Point(T, s)->rchild))//结点左子树空，右子树不空
						{
							if (ch == 'L')  //插入二叉树c作为其左子树
							{
								Point(T, s)->lchild = c;
								return OK;
							}
							if (ch == 'R') //由于结点右子树不空，故不能将插入二叉树c作为其右子树
							{
								cout << "所选的结点右子树不空，不能插入二叉树c作为其右子树！" << endl;
								return ERROR;
							}
						}

			}
		}

}

Status DeleteChild(BiTree &T, TElemType e)
{//删除结点e的左/右子树

	char c;
	if (!Point(T, e))//找不到结点
	{
		cout << "二叉树中无此结点" << endl;
		return ERROR;
	}
	else {
		cout << "请问要删除此结点的左子树还是右子树？L：左子树；R：右子树" << endl;
		cin >> c;
		if (c == 'L')
			if (!Point(T, e)->lchild)//左子树空
			{
				cout << "该结点左子树已空，无法删除！" << endl;
				return ERROR;
			}
			else {
				ClearBiTree(Point(T, e)->lchild);//删除左子树
				return OK;
			}
		else //删除右子树
		{
			if (!Point(T, e)->rchild)//右子树空
			{
				cout << "该结点右子树已空，无法删除！" << endl;
				return ERROR;
			}

			else {
				ClearBiTree(Point(T, e)->rchild);//删除右子树
				return OK;
			}

		}
	}
}




int main() {
	int cmd;
	char* str = new char[3];
	TElemType e, s;
	BiTree T;
	InitBiTree(T);
	cout << "请先序输入二叉树中的各个元素（不能有重复的元素）创建二叉树，空子树以-代替，如AB--C--表示表示以A为根节点，B,C为左右子树的二叉树" << endl;
	CreateBiTree(T);
	while (1) {
		cout << "请输入要执行的操作：" << endl;
		cout << "1.查找" << endl;
		cout << "2.插入" << endl;
		cout << "3.删除" << endl;
		cout << "4.遍历" << endl;
		cout << "5.修改结点" << endl;
		cout << "6.显示树的深度" << endl;
		cout << "7.显示叶子结点的个数" << endl;
		cout << "8.清除（销毁）二叉树" << endl;
		cout << "9.退出程序" << endl;
		cin >> cmd;
		switch (cmd)
		{
		case 1: {
			cout << "围绕二叉树中的某个结点，查找该结点的双亲/左孩子/右孩子/左兄弟/右兄弟结点。请先输入该结点：" << endl;
			cin >> e;
			if (!Point(T, e))
			{
				cout << "二叉树中无此结点" << endl;
				break;
			}
			else {
				cout << "请问要查找的是该结点的：双亲结点（PA）/左孩子（LC）/右孩子（RC）/左兄弟（LS）/右兄弟（RS）：" << endl;
				cin >> str;
				if (!strcmp(str, "PA"))//字符串str为PA
				{
					TElemType k = Parent(T, e);
					if (k == Nil) {
						cout << "该结点无双亲结点！" << endl;
					}
					else {
						cout << "该结点的双亲结点为" << k << endl;
					}
				}
				if (!strcmp(str, "LC")) {
					TElemType k = LeftChild(T, e);
					if (k == Nil) {
						cout << "该结点无左孩子" << endl;
					}
					else {
						cout << "该结点的左孩子为" << k << endl;
					}
				}
				if (!strcmp(str, "RC")) {
					TElemType k = RightChild(T, e);
					if (k == Nil) {
						cout << "该结点无右孩子" << endl;
					}
					else {
						cout << "该结点的右孩子为" << k << endl;
					}
				}
				if (!strcmp(str, "LS")) {
					TElemType k = LeftSibling(T, e);
					if (k == Nil) {
						cout << "该结点无左兄弟" << endl;
					}
					else {
						cout << "该结点的左兄弟为" << k << endl;
					}
				}
				if (!strcmp(str, "RS")) {
					TElemType k = RightSibling(T, e);
					if (k == Nil) {
						cout << "该结点无右兄弟" << endl;
					}
					else {
						cout << "该结点的右兄弟为" << k << endl;
					}

				}
			}
			break; }
		case 2: {
			BiTree c;
			InitBiTree(c);
			cout << "将一颗新的二叉树c插入到原二叉树中。请先序输入待插入二叉树c中的各个元素（不能有重复的元素，也不能与原二叉树中有相同的元素）创建二叉树c。空子树以-代替，如AB--C--表示表示以A为根节点，B,C为左右子树的二叉树" << endl;
			CreateBiTree(c);
			cout << "请输入待插入二叉树c的双亲结点（注：所选的双亲结点应至少有一子树为空）" << endl;
			cin >> s;
			int m = InsertChild(T, s, c);
			if (m == 1)cout << "插入成功！" << endl;
			if (m == -1)cout << "插入失败！" << endl;
			break; }
		case 3: {
			cout << "请输入待删除子树的双亲结点" << endl;
			cin >> e;
			int l = DeleteChild(T, e);
			if (l == 1)cout << "删除成功！" << endl;
			if (l == -1)cout << "删除失败！" << endl;
			break;
		}
		case 4: {
			int n;
			cout << "请选择遍历顺序：1.先序 2.中序 3.后序 4.层序" << endl;
			cin >> n;
			if (n == 1) {
				cout << "对二叉树进行先序遍历:";
				PreOrderTraverse(T, print);
				cout << endl;
			}
			if (n == 2) {
				cout << "对二叉树进行中序遍历:";
				InOrderTraverse(T, print);
				cout << endl;
			}
			if (n == 3) {
				cout << "对二叉树进行后序遍历:";
				PostOrderTraverse(T, print);
				cout << endl;
			}
			if (n == 4) {
				cout << "对二叉树进行层序遍历:";
				LevelOrderTraverse(T, print);
				cout << endl;
			}
			break;
		}
		case 5: {
			cout << "请输入要修改的结点" << endl;
			cin >> e;
			if (!Point(T, e))
			{
				cout << "二叉树中无此结点，修改失败！" << endl;
				break;
			}
			else
				cout << "请输入这个结点的新值" << endl;
			cin >> s;
			int l = Assign(Point(T, e), s);
			if (l == 1)cout << "修改成功！" << endl;
			else cout << "修改失败！" << endl;
			break; }
		case 6: {cout << "当前二叉树的深度为：" << BiTreeDepth(T) << endl;
			break; }
		case 7: {cout << "当前二叉树的叶子结点数为：" << CountLeaf(T) << endl;
			break; }
		case 8: {if (ClearBiTree(T) == 1)cout << "二叉树清除（销毁）成功！" << endl;
			break; }
		case 9: {cout << "退出程序！" << endl;
			exit(0); }
		default:
			break;
		}
		cout << endl;
	}

	return 0;

}
