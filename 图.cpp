//源文件"图.cpp",包含头文件"队列.h"
#include<iostream>
#include<string.h>
using namespace std;

#pragma warning(disable:4996)
#define  MAX_NAME  5           // 顶点名称（字符串）的最大长度+1 
#define OK 1
#define ERROR 0
typedef   int       Status;
typedef   int      VRType;             //顶点之间关系(边或弧的信息)类型定义
typedef   char   InfoType;             //弧或边的其他信息类型定义
#define  Infinity   INT_MAX          //用整型最大值INT_MAX代替∞
#define  MAX_VERTEX_NUM 20      //设最多顶点个数为20
typedef  enum { DG, DN, UDG, UDN } GraphKind; //图的种类：有向图、有向网、无向图、无向网

typedef   char   VertexType[MAX_NAME];  //顶点类型定义

typedef struct ArcCell 
{
	VRType  adj;                       //VRType是顶点之间关系类型。对无权图, 用1或0表示相邻否; 对带权图, 则为权值类型。
	InfoType  *info;                  //弧或边的其他信息的指针（通常是字符指针） (可无)
}ArcCell;//弧或边类型定义

typedef ArcCell AdjMatrix [MAX_VERTEX_NUM][MAX_VERTEX_NUM];//边或弧类型二维数组类型定义

typedef struct MGraph {
	VertexType  vexs[MAX_VERTEX_NUM];        // 顶点类型一维数组vexs
	AdjMatrix    arcs;                       // 边或弧类型二维数组arcs 
	int    vexnum, arcnum;                   //图中当前的顶点数和当前的弧(边)数    
	GraphKind   kind=UDN;                    //图的种类标志，设置为无向网         
}MGraph; //图类型定义




int LocateVex(MGraph G, VertexType u)
{ //初始条件: 图G存在, u和G中顶点有相同特征 
  //操作结果: 若G中存在顶点u, 则返回该顶点在图G中的位置; 否则返回-1 
	int i;
	for (i = 0; i < G.vexnum; ++i) if (strcmp(u, G.vexs[i]) == 0) return i;
	return -1;
}


Status Input(MGraph & G, int i, int j) {
	char*s = new char[100];
	cout << "请输入要添加的信息" << endl;
	cin >> s;
	G.arcs[i][j].info = s;//添加信息到弧或边上
	return OK;
}


Status CreateGraph(MGraph & G) //采用数组表示法构造无向网G
{
	VertexType v1, v2;
	int w, IncInfo;
	cout << "请输入无向网的顶点数和边数" << endl;
	cin >> G.vexnum >> G.arcnum;
	cout << "请输入各顶点的名称" << endl;
	for (int i = 0; i < G.vexnum; ++i) { cin >> G.vexs[i]; }  //一维数组储存顶点
	for (int i = 0; i < G.vexnum; ++i) {  //二维数组初始化
		for (int j = 0; j < G.vexnum; ++j)  G.arcs[i][j] = { INT_MAX,NULL };
	}
	cout << "请在下面每一行中输入每一条边的两个顶点,该边的权值,以及是否有其他信息(1：有，0：无)。以空格间隔,如“A B 12 0”表示以A,B为顶点，12为权值，没有其他信息的一条边" << endl;//默认各边不含其他信息
	for (int k = 0; k < G.arcnum; ++k)     //二维数组储存边     
	{
		cin >> v1 >> v2 >> w >> IncInfo;              //输入该条边所依附的顶点及权值
		int i = LocateVex(G, v1); int j = LocateVex(G, v2); //找到顶点v1和v2在无向网G中的序号
		G.arcs[i][j].adj = w;                                     //弧<v1, v2>的权重  
		if (IncInfo) Input(G, i, j); //弧<v2, v1>的权重 
		G.arcs[j][i] = G.arcs[i][j];                    //置<v1,v2>的对称弧<v2,v1>的权重及其他信息
	}    
	cout << "创建无向网完成" << endl; 
	return OK;
}

Status DestroyGraph(MGraph &G)
{ //销毁无向网G
	int i, j;
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			if (G.arcs[i][j].adj != INT_MAX)//有边
			{
				G.arcs[i][j].adj = INT_MAX;//删除边
			}
			if (G.arcs[i][j].info) //有其他信息
			{
				free(G.arcs[i][j].info); //删除其他信息
				G.arcs[i][j].info = NULL;
			}
		}
	}
			G.vexnum = 0;//将顶点数置为0
			G.arcnum = 0;//将边数置为0
	
	return OK;
}

VertexType* GetVex(MGraph G, int i)
{ //返回无向网G中序号为i的顶点的值
if (i >= G.vexnum || i< 0)
	exit(ERROR);
return &G.vexs[i];
}

Status PutVex(MGraph &G, VertexType v, VertexType value)
{ //对值为v的顶点（顶点v）赋新值value
	int k;
	k = LocateVex(G, v); //k为顶点v在无向网G中的序号
	if (k < 0)
		return ERROR;
	strcpy_s(G.vexs[k], value);//赋新值
	return OK;
}

int FirstAdjVex(MGraph G, VertexType v)
{ 
  //返回值为v的顶点（顶点v）的第一个邻接顶点在无向网G中的序号
	int j = INT_MAX;
	int k;
	k = LocateVex(G, v); //k为顶点v在无向网G中的序号
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.arcs[k][i].adj != j)
			return i;//找顶点v的第一个邻接点
	}
	return -1;
}

int NextAdjVex(MGraph G, VertexType v, VertexType w)
{
  //返回顶点v相对于w的下一个邻接顶点在无向网G中的序号，若w是v的最后一个邻接顶点,则返回-1
	int i, k1, k2;
    int j = INT_MAX;
	k1 = LocateVex(G, v); //k1为顶点v在无向网G中的序号 
	k2 = LocateVex(G, w); //k2为顶点w在无向网G中的序号
	for (i = k2+1; i < G.vexnum; i++)//从顶点w向后找
	{
		if (G.arcs[k1][i].adj != j)
		{
			return i;
			exit(0);
		}
	}
	return -1;
}

Status InsertVex(MGraph &G, VertexType v)
{ 
  //在无向网G中增添新顶点v(不增添与顶点相关的边)
	int i;
	strcpy_s(G.vexs[G.vexnum], v); //将新顶点v加到存储顶点的一维数组中
	for (i = 0; i <= G.vexnum; i++)
	{
		//不增添与顶点相关的边
			G.arcs[G.vexnum][i].adj = INT_MAX; //初始化顶点v所在行的邻接矩阵的值
			G.arcs[i][G.vexnum].adj = INT_MAX; //初始化顶点v所在列邻接矩阵的值
	        G.arcs[G.vexnum][i].info = NULL; //初始化顶点v所在行的相关信息指针
		    G.arcs[i][G.vexnum].info = NULL;//初始化顶点v所在列的相关信息指针
	}
	G.vexnum ++; //无向网的顶点数加1，边数不变
	return OK;
}

Status DeleteVex(MGraph &G, VertexType v)
{ //删除无向网G中的顶点v及其相关的边
		int i, j, k;
		VRType m = INT_MAX;
		k = LocateVex(G, v); //k为待删除顶点v在无向网G中的序号
		if (k < 0) //v不是无向网G的顶点
			return ERROR;
		for (j = 0; j < G.vexnum; j++) {
			if (G.arcs[j][k].adj != m)//有边
			{
				G.arcs[j][k].adj = m;//删除顶点v的弧
				G.arcs[k][j].adj = m;//无向
			}
			if (G.arcs[j][k].info) //有其他信息
			{
				free(G.arcs[j][k].info); //删除其他信息
				free(G.arcs[k][j].info);//无向
				G.arcs[j][k].info = G.arcs[k][j].info = NULL;
			}
			G.arcnum--; //边数减1
		}
		for (j = k + 1; j < G.vexnum; j++) //顶点v后面的顶点在一维数组中依次前移
			strcpy_s(G.vexs[j - 1], G.vexs[j]);
		for (i = 0; i < G.vexnum; i++)
			for (j = k + 1; j < G.vexnum; j++)
				G.arcs[i][j - 1] = G.arcs[i][j]; //顶点v后面的结点的矩阵元素在邻接矩阵中依次前移
		for (i = 0; i < G.vexnum; i++)
			for (j = k + 1; j < G.vexnum; j++)
				G.arcs[j - 1][i] = G.arcs[j][i]; //顶点v后面的结点的矩阵元素在邻接矩阵中依次前移
		G.vexnum--; //顶点数减1
		return OK;
	}

Status InsertArc(MGraph &G, VertexType v, VertexType w)
{ 
  //在无向网G中增添边(v,w),即弧<v,w>和对称弧<w,v>
	int i, l, v1, w1;
	char *info, s[50];
	v1 = LocateVex(G, v); //弧尾顶点v在无向网G中的序号
	w1 = LocateVex(G, w); //弧头顶点w在无向网G中的序号
	if (v1 < 0||w1 < 0)
	return ERROR;
	G.arcnum++; //边数加1
	cout << "请输入该边的权值,以及是否有其他信息(1：有，0：无)" << endl;
	cin >> G.arcs[v1][w1].adj>>i;
	if (i) {
		Input(G, v1, w1);
	}
	G.arcs[w1][v1].adj = G.arcs[v1][w1].adj;//无向
	G.arcs[w1][v1].info = G.arcs[v1][w1].info;//无向
	return OK;
}

Status DeleteArc(MGraph &G, VertexType v, VertexType w)
{ 
  //在无向网G中删除边(v,w),即弧<v,w>和对称弧<w,v>
	int v1, w1;
	v1 = LocateVex(G, v); //弧尾顶点v在无向网G中的序号
	w1 = LocateVex(G, w); //弧头顶点w在无向网G中的序号
	if (v1 < 0 || w1 < 0)
	{
		return ERROR;
	}
	G.arcs[v1][w1].adj = INT_MAX;
	if (G.arcs[v1][w1].info) //删除其它信息
	{
		free (G.arcs[v1][w1].info);
		G.arcs[v1][w1].info = NULL;
	}
	G.arcs[w1][v1].adj = G.arcs[v1][w1].adj;//无向
	G.arcs[w1][v1].info = NULL;//无向
	G.arcnum--; //边数减1
	return OK;
}


int visited[MAX_VERTEX_NUM]; //访问标志数组(全局变量)
Status(*VisitFunc)(VertexType); //函数变量VisitFunc(全局变量)
Status DFS(MGraph G, int i)
{ //从序号为i的顶点出发，对其所有邻接顶点递归使用深度优先遍历算法
	int j;
	VertexType v, u;
	visited[i] = 1; //设置访问标志为1表示已访问
	VisitFunc(G.vexs[i]); //访问该顶点
	for (j = FirstAdjVex(G, strcpy(v, *GetVex(G, i))); j >= 0; j = NextAdjVex(G, strcpy(v, *GetVex(G, i)), strcpy(u, *GetVex(G, j))))
	{
		if (!visited[j])
			DFS(G, j); //对序号为j的顶点尚未访问的邻接顶点递归调用DFS
	}
	return 0;
}

void DFSTraverse(MGraph G, Status(*Visit)(VertexType))
{
	//从第1个顶点出发,深度优先遍历图G,并对每个顶点调用函数Visit一次且仅一次
	int v;
	VisitFunc = Visit; //使用全局变量函数VisitFunc。使得上方的DFS函数不必设置函数指针参数,只需在DFSTraverse里设置函数指针函数即可
	for (v = 0; v < G.vexnum; v++) {
		visited[v] = 0; //初始化访问标志数组为均未被访问
	}
	for (v = 0; v < G.vexnum; v++) {
		if (!visited[v])
			DFS(G, v);//对无向网中尚未访问的顶点调用DFS。如果此无向网是连通的,则DFS函数第一次回到此处时就已完成整个无向网的深度遍历
	}
	cout << endl;
}

typedef VRType QElemType;
#include"队列.h"
void BFSTraverse(MGraph G, Status(*Visit)(VertexType))
{ 
  //从第1个顶点出发,广度优先非递归遍历图G,并对每个顶点调用函数Visit一次且仅一次
	int i, j, k;
	VertexType v, u;
	LinkQueue Q;
	for (i = 0; i < G.vexnum; i++) {
		visited[i] = FALSE;//初始化访问标志数组为均未被访问
	}
	InitQueue(Q); //初始化辅助队列Q
	for (i = 0; i < G.vexnum; i++) {
		if (!visited[i]) //无向网中尚未访问的顶点
		{
			visited[i] = TRUE; //设置访问标志为1表示已访问
			Visit(G.vexs[i]);//访问该顶点
			EnQueue(Q, i);//将访问到的顶点在无向网中的序号入队列
			while (!QueueEmpty(Q)) //队列不空
			{
				DeQueue(Q, j); //队头元素出队
				for (k = FirstAdjVex(G, strcpy(v, *GetVex(G, j))); k >= 0; k = NextAdjVex(G, strcpy(v, *GetVex(G, j)), strcpy(u, *GetVex(G, k)))){//如果此无向网是连通的,则此循环执行一次就已完成整个无向网的广度遍历
					if (!visited[k]) //k为队头元素所对应的顶点的尚未访问的邻接顶点的序号
					{
						visited[k] = TRUE;
						Visit(G.vexs[k]);
						EnQueue(Q, k);
					}
				}
			}
		}
	}
	cout << endl;
}

Status Print(VertexType v) {
	cout << v << " ";
	return OK;
}

int main() {
	int cmd;
	VertexType v, w;
	MGraph G;//无向网变量
	CreateGraph(G);
	while (1)
	{
		cout << "请选择对无向网的如下操作：1.输出顶点数组 2.输出邻接矩阵 3.修改顶点的值 4.增添新的顶点 5.增添新的边 6.删除顶点（同时删除其相关的边） 7.删除边 8.深度遍历无向网 9.广度遍历无向网 10.销毁无向网 11.退出程序 " << endl;
		cin >> cmd;
		switch (cmd)
		{
		case 1: {
			cout << "输出顶点数组：" << endl;
			for (int i = 0; i < G.vexnum; i++)
			{
				cout << "G->vex[" << i << "]=" << G.vexs[i] << endl;
			}
			break; }
		case 2: {
			cout << "输出邻接矩阵：" << endl;
			for (int i = 0; i < G.vexnum; i++) {
				for (int j = 0; j < G.vexnum; j++)
				{
					cout << G.arcs[i][j].adj << '\t';
				}
				cout << endl;
			}
			break; }
		case 3:
		{
			cout << "请输入要修改的顶点的原值" << endl;
			cin >> v;
			cout << "请输入顶点修改后的值" << endl;
			cin >> w;
			if (PutVex(G, v, w)) {
				cout << "修改成功！" << endl;
			}
			else {
				cout << "修改失败！" << endl;
			}
			break;
		}
		case 4: {
			cout << "请输入要增添的顶点的值" << endl;
			cin >> v;
			if (InsertVex(G, v)) {
				cout << "增添成功！" << endl;
			}
			else {
				cout << "增添失败！" << endl;
			}
			break;
		}
		case 5: {
			cout << "请输入要增添的边的两个顶点" << endl;
			cin >> v >> w;
			if (InsertArc(G, v, w)) {
				cout << "增添成功！" << endl;
			}
			else {
				cout << "增添失败！" << endl;
			}
			break;
		}
		case 6: {
			cout << "请输入要删除的顶点" << endl;
			cin >> v;
			if (DeleteVex(G, v)) {
				cout << "删除成功！" << endl;
			}
			else {
				cout << "删除失败！" << endl;
			}
			break;
		}
		case 7: {
			cout << "请输入要删除的边的两个顶点" << endl;
			cin >> v >> w;
			if (DeleteArc(G, v, w)) {
				cout << "删除成功！" << endl;
			}
			else {
				cout << "删除失败！" << endl;
			}
			break;
		}
		case 8: {
			cout << "深度遍历无向网：" << endl;
			DFSTraverse(G, Print);
			break;
		}
		case 9: {
			cout << "广度遍历无向网：" << endl;
			BFSTraverse(G, Print);
			break;
		}
		case 10: {
			if (DestroyGraph(G)) { cout << "无向网销毁成功！" << endl; }
			break;
		}
		case 11: {
			cout << "退出程序！" << endl;
			exit(0);
		}
				
		default:break;
		}
	}return 0;
}
