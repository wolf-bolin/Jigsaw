#include "gamelogic.h"

void moveLog(std::vector<moveinfo> &logs,int m,int n){
    logs.push_back(moveinfo(logs.size()+1,m,n));
}

void saveMoveLog(std::vector<moveinfo> &logs){
    std::ofstream fout("./molvlog.log");
    for(unsigned int i=0;i!=logs.size();i++){
        fout<<logs[i].step<<" "<<logs[i].m<<" "<<logs[i].n<<std::endl;
    }
}

void readMoveLog(std::vector<moveinfo> &logs){
    std::ifstream fin("./molvlog.log");
    if(!fin){
        return;
    }
    moveinfo temp;
    while(fin>>temp.step>>temp.m>>temp.n){
        logs.push_back(temp);
    }
    remove("./molvlog.log");
}

void saveStatus(std::vector<int> &numData,int gameStep,int gameTime){
    std::ofstream fout("./status.log");
    for(unsigned int i=0;i!=numData.size();i++){
        fout<<numData[i]<<" ";
    }
    fout<<std::endl;
    fout<<gameStep<<" "<<gameTime<<std::endl;
}

void readStatus(std::vector<int> &numData,int &gameStep,int &gameTime){
    std::ifstream fin("./status.log");
    if(!fin){
        numData.resize(9);
        numData[0]=1;
        numData[1]=2;
        numData[2]=3;
        numData[3]=4;
        numData[4]=5;
        numData[5]=6;
        numData[6]=7;
        numData[7]=8;
        numData[8]=0;
        gameStep=0;
        gameTime=0;
        return;
    }
    for(int i=0;i!=9;i++){
        int temp;
        fin>>temp;
        numData.push_back(temp);
    }
    fin>>gameStep>>gameTime;
    fin.close();
    remove("./status.log");
}

void readGameLog(std::vector<gameinfo> &gameRecord){
    std::ifstream fin("./gameRecord.log");
    if(!fin){
        return;
    }
    gameRecord.clear();
    gameinfo temp;
    while(fin>>temp.userName>>temp.gameTime>>temp.gameStep>>temp.score){
        gameRecord.push_back(temp);
    }
}

void saveGameLog(std::vector<gameinfo> &gameRecord){
    std::ofstream fout("./gameRecord.log");
    for(unsigned int i=0;i!=gameRecord.size();i++){
        fout<<gameRecord[i].userName<<" "<<gameRecord[i].gameTime<<" "<<gameRecord[i].gameStep<<" "<<gameRecord[i].score<<std::endl;
    }
}

void readSetting(std::string &picPath,bool &BGM,bool &keyMusic){
    std::ifstream fin("./gameSetting.log");
    if(!fin){
        picPath=":/picture/default.jpg";
        BGM=1;
        keyMusic=1;
        return;
    }
    fin>>picPath>>BGM>>keyMusic;
}

void saveSetting(std::string &picPath,bool BGM,bool keyMusic){
    std::ofstream fout("./gameSetting.log");
    fout<<picPath<<BGM<<keyMusic;
}

bool canSolve(std::vector<int> &numData,std::vector<int> &standard){

    int sum1=0,sum2=0;
    for(int i=0;i<9;i++)
        for(int j=i+1;j<9;j++){
            if(numData[i] > numData[j]&&numData[j]!=0)
                sum1++;
            if(standard[i] > standard[j]&&standard[j]!=0)
                sum2++;
        }

    return (sum1%2==sum2%2);
}

void newGame(std::vector<int> &numData,int &gameStep,int &gameTime){
    int standardData[10]={1,2,3,4,5,6,7,8,0};
    std::vector<int> standard(standardData,standardData+9);
    srand((unsigned)time(NULL));
    bool status=0;//0代表当前状态无解
    int temp;
    while(!status){
        std::vector<bool> flag;
        flag.resize(9,0);;
        for(int i=0;i!=9;i++){
            temp=rand()%9;
            while(flag[temp]){
                temp=rand()%9;
            }
            flag[temp]=1;
            numData[i]=temp;
        }
        status=canSolve(numData,standard);
    }
    gameStep=0;
    gameTime=0;
}

const int MAX=2147483647;
struct Node{
    std::vector<int> data;
    int blankPos;//空格（用0表示）位置，用于计算出相邻结点
    int f,g,h; //f=g+h，g和h分别表示当前点到起点和到终点的代价
    Node *parent;
};
//检测结点是否相等
bool isEqual(Node *&a,Node *&b){
    for(int i=1;i<9;i++)
        if(a->data[i]!=b->data[i])
            return false;
    return true;
}
//检测是否有解
bool canSolve(Node *&a,Node *&b){
    int sum1=0,sum2=0;
    for(int i=0;i<9;i++)
        for(int j=i+1;j<9;j++){
            if(a->data[i] > a->data[j]&&a->data[j]!=0)
                sum1++;
            if(b->data[i] > b->data[j]&&b->data[j]!=0)
                sum2++;
        }

    return (sum1%2==sum2%2);//奇偶性相同才有解
}
//空格上移后的结点
Node* upNode(Node *&a){
    if(a->blankPos<=2)
        return NULL;
    else{
        Node* tmp=new Node(*a);
        std::swap(tmp->data[tmp->blankPos],tmp->data[tmp->blankPos-3]);
        tmp->blankPos-=3;
        return tmp;
    }
}
//空格下移后的结点
Node* downNode(Node *&a){
    if(a->blankPos>=6)
        return NULL;
    else{
        Node* tmp=new Node(*a);
        std::swap(tmp->data[tmp->blankPos],tmp->data[tmp->blankPos+3]);
        tmp->blankPos+=3;
        return tmp;
    }
}
//空格左移后的结点
Node* leftNode(Node *&a){
    if(a->blankPos%3==0)
        return NULL;
    else{
        Node* tmp=new Node(*a);
        std::swap(tmp->data[tmp->blankPos],tmp->data[tmp->blankPos-1]);
        tmp->blankPos--;
        return tmp;
    }
}
//空格右移后的结点
Node* rightNode(Node *&a){
    if(a->blankPos%3==2)
        return NULL;
    else{
        Node* tmp=new Node(*a);
        std::swap(tmp->data[tmp->blankPos],tmp->data[tmp->blankPos+1]);
        tmp->blankPos++;
        return tmp;
    }
}
//计算出两个节点的距离
int nodeDistance(Node *&a,Node *&b){
    int h1,h2;
    int sum=0;
    for(int k=1;k<=8;k++){//分别检测数字0到8
        for(int i=0;i<9;i++){
            if(a->data[i]==k)
                h1=i;
            if(b->data[i]==k)
                h2=i;
        }
        sum+=abs(h1/3-h2/3)+abs(h1%3-h2%3);
    }
    return sum;
}
void astar(std::vector<int> numData,std::vector<moveinfo> &answer){
    //起始节点和目标结点的初始化
    int ivec1[10];
    for(int i=0;i!=9;i++){
        ivec1[i]=numData[i];
    }
    /*int ivec1[10]={3,5,1,
                   0,7,6,
                   2,4,8};//起始结点*/
    //int ivec1[10]={0,8,7,
    //			     6,5,4,
    //		         3,2,1};//起始结点
    int ivec2[10]={1,2,3,
                   4,5,6,
                   7,8,0};//目标结点
    Node a,b;
    for(int i=0;i<9;i++){//0代表空字符
        a.data.push_back(ivec1[i]);
        b.data.push_back(ivec2[i]);
    }
    for(int i=0;i<9;i++){//空格位置
        if(a.data[i]==0)
            a.blankPos=i;
        if(b.data[i]==0)
            b.blankPos=i;
    }
    Node* startNode=&a;
    Node* targetNode=&b;
    startNode->parent=NULL;
    startNode->h=nodeDistance(startNode,targetNode);
    startNode->g=0;
    startNode->f=startNode->h;

    if(!canSolve(startNode,targetNode)){
        std::cout<<"Can't solve!"<<std::endl;
        return;
    }
    //OPEN表和CLOSE表，矩阵数据为键，指针为值，便于检测矩阵是否访问过
    //同时也便于从矩阵获取指针，进行OPEN表的修正
    std::map<std::vector<int> ,Node*> CLOSE,OPEN;
    OPEN[startNode->data]=startNode;

    while(!OPEN.empty()){
        //找到OPEN表中f最小的结点，移入CLOSE表
        Node* root;
        int fmin=MAX;
        for(std::map<std::vector<int> ,Node*>::iterator it=OPEN.begin();it!=OPEN.end();it++){
            if((*it).second->f < fmin){
                fmin=(*it).second->f;
                root=(*it).second;
            }
        }
        OPEN.erase(root->data);
        CLOSE[root->data]=root;
        if(isEqual(root,targetNode)){//找到目标结点，结束循环
            targetNode->parent=root->parent;
            break;
        }
        //用root对不在CLOSE表中的后继结点进行修正，若下面的结点不在OPEN表，则加到OPEN表
        //若下面的结点已经在OPEN表中，则进行修正，选取更优的路径
        Node* node1=upNode(root);
        Node* node2=downNode(root);
        Node* node3=leftNode(root);
        Node* node4=rightNode(root);
        if(node1!=NULL&&CLOSE.find(node1->data)==CLOSE.end()){
            node1->parent=root;
            node1->g=root->g+1;
            node1->h=nodeDistance(node1,targetNode);
            node1->f=node1->g+node1->h;
            if(OPEN.find(node1->data)==OPEN.end()){//新探索到的点
                OPEN[node1->data]=node1;
            }else{//该结点已经在OPEN表中，修正
                Node* tmp=OPEN[node1->data];
                if(tmp->g > node1->g){
                    tmp->g=node1->g;
                    tmp->parent=node1->parent;
                    tmp->h=node1->h;
                    tmp->f=node1->f;
                }
            }
        }
        if(node2!=NULL&&CLOSE.find(node2->data)==CLOSE.end()){
            node2->parent=root;
            node2->g=root->g+1;
            node2->h=nodeDistance(node2,targetNode);
            node2->f=node2->g+node2->h;
            if(OPEN.find(node2->data)==OPEN.end()){//新探索到的点
                OPEN[node2->data]=node2;
            }else{//该结点已经在OPEN表中，修正
                Node* tmp=OPEN[node2->data];
                if(tmp->g > node2->g){
                    tmp->g=node2->g;
                    tmp->parent=node2->parent;
                    tmp->h=node2->h;
                    tmp->f=node2->f;
                }
            }
        }
        if(node3!=NULL&&CLOSE.find(node3->data)==CLOSE.end()){
            node3->parent=root;
            node3->g=root->g+1;
            node3->h=nodeDistance(node3,targetNode);
            node3->f=node3->g+node3->h;
            if(OPEN.find(node3->data)==OPEN.end()){//新探索到的点
                OPEN[node3->data]=node3;
            }else{//该结点已经在OPEN表中，修正
                Node* tmp=OPEN[node3->data];
                if(tmp->g > node3->g){
                    tmp->g=node3->g;
                    tmp->parent=node3->parent;
                    tmp->h=node3->h;
                    tmp->f=node3->f;
                }
            }
        }
        if(node4!=NULL&&CLOSE.find(node4->data)==CLOSE.end()){
            node4->parent=root;
            node4->g=root->g+1;
            node4->h=nodeDistance(node4,targetNode);
            node4->f=node4->g+node4->h;
            if(OPEN.find(node4->data)==OPEN.end()){//新探索到的点
                OPEN[node4->data]=node4;
            }else{//该结点已经在OPEN表中，修正
                Node* tmp=OPEN[node4->data];
                if(tmp->g > node4->g){
                    tmp->g=node4->g;
                    tmp->parent=node4->parent;
                    tmp->h=node4->h;
                    tmp->f=node4->f;
                }
            }
        }
    }
    //利用结点的parent指针回溯出路径
    Node* p=targetNode;
    while(p->parent!=NULL){
        answer.push_back(moveinfo(0,(p->blankPos),(p->parent->blankPos)));
        p=p->parent;
    }
}
