//
//  tpcOpera.c
//  Toplogincal
//
//  Created by zyq on 2018/1/23.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "custom.h"

int indegree[MAX_VEX_NUM];//用来存放顶点的入度
/*
  初始化图
 */
struct Graph init(void){
    struct Graph g;
    int i,j,q,z;
    char data1,data2;
    int locate(struct Graph g,char data);
    printf("请输入顶点数:");
    scanf("%d",&g.vexnum);
    printf("请输入弧数:");
    scanf("%d",&g.arcnum);
    for(i=0;i<g.vexnum;i++){
        struct VNode v;
        printf("请输入第%d个顶点:",i+1);
        scanf(" %c",&v.info);
        v.firstarc=NULL;
        g.verts[i]=v;
    }
    for(j=0;j<g.arcnum;j++){
        struct ArcNode * a=(struct ArcNode *)malloc(sizeof(struct ArcNode));
        printf("请输入第%d条边的尾点:",j+1);
        scanf(" %c",&data1);
        printf("请输入第%d条边的头顶点:",j+1);
        scanf(" %c",&data2);
        q=locate(g, data1);
        z=locate(g, data2);
        indegree[z]++;//计算该顶点的入度
        a->adjvex=z;
        a->nextarc=NULL;
        if(g.verts[q].firstarc==NULL){
            g.verts[q].firstarc=a;
        }else{
            a->nextarc=g.verts[q].firstarc;
            g.verts[q].firstarc=a;
        }
    }
    return g;
}

/*
  根据顶点信息查找顶点的位置
 */
int locate(struct Graph g,char data){
    int i;
    for(i=0;g.verts[i].info!=data;i++);
    return i;
}
/*
 偏序：若集合X上的关系R是自反的，反对称的和传递的，则称R是集合X上的偏序关系。
 全序：设R是集合X上的偏序，如果对每个x,y属于X，必有xRy或yRx，则称R是集合X上的全序关系。
 
 拓扑排序:
 简单的说，由某个集合上的一个偏序得到该集合上的一个全序，这个操作称之为拓扑排序，由偏序定义得到拓扑有序的操作便是拓扑排序。其实就是人为的把不属于偏序关系的相关顶点变成属于偏序关系的，就变成全序了。
 
 AOV网：用顶点表示活动，用弧表示活动时间的优先关系的有向图称为顶点表示活动的网(Activity On Vertex Network)，简称AOV-网.
 
 AOV-网的应用:一个软件专业的学生必须学习一系列基本课程，其中有些课程是基础课，它独立于其他课程，如《高等数学》,而另外一些课程必须在学完作为它的基础的先修课才能开始，如在《离散数学》
 学完之前就不能开始学习《数据结构》。这些先决条件定义了课程之间的领先（优先）关系。这个关系就可以用AOV-网来表示。AOV-网中不能有环，否则有死循环了。
 
 拓扑排序的应用：
 检测一个AOV-网是否有环，就使用拓扑有序序列，若网中的所有顶点都在它的拓扑有序序列中，则该AOV-网必定不存在环。
 原因：人为的把不属于偏序关系的顶点变成属于偏序关系的，图就变成全序关系的。而偏序具有自反的，反对称的和传递的，假设R是偏序，就是某个a课程领先于另外一个b课程的关系，有一个课程x，
 它的子孙有到x顶点的回路，有传递性可知，那么就有xRx，x领先于x，显然相矛盾，所以这个回路上的顶点都不属于偏序R，所以在AOV-网的拓扑有序序列中就不会有这些顶点，
 那么就少于该有向图的顶点数，就说明有环。
 
 如何进行拓扑排序：
 1 在有向图中选一个没有前驱的顶点且输出之
 2 从图中删除该顶点和所有以它为尾的弧
 重复上述两步，直至全部顶点均已输出，或者当前图中不存在没有前驱的顶点为止（这一种情况说明有向图有环）
 */
void tpcSort(struct Graph g){
    int i,j,k,count=0;
    struct ArcNode * p;
    struct sqstack s;//这个栈的作用是存放入度为0的顶点，可以避免重复检测入度为0的顶点
    struct ArcNode * getNextArc(struct ArcNode * p);
    initStack(&s);
    for(i=0;i<g.vexnum;i++){
        if(indegree[i]==0) push(&s, i);//把入度为0的顶点放入栈中，需要找入度为0的顶点时可以直接去栈中取
    }
    while(!stackEmpty(&s)){
        j=pop(&s);//取出入度为0的顶点
        printf("%c\t",g.verts[j].info);//把这个顶点拿出来打印出来
        count++;//计算入度为0的顶点的个数
        for(p=g.verts[j].firstarc;p!=NULL;p=getNextArc(p)){
            k=p->adjvex;
            if(--indegree[k]<=0) push(&s, k);//把和该顶点相邻的顶点的入度都减去1，这样可以间接实现删除以该顶点为尾的弧的操作，如果其邻接顶点的入度为0，就加入到栈中
        }
    }
    if(count<g.vexnum){//count其实就代表拓扑有序序列中的顶点的个数
        printf("该有向图有环");
    }
}

struct ArcNode * getNextArc(struct ArcNode * p){
    return p->nextarc;
}






