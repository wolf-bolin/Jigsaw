#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<map>
#include<cmath>
using namespace std;
class status{
public:
    vector<int> data;
    int zero;
    int f,g,h;
    int parent,index;
    status(){
        zero=f=g=h=parent=index=0;
    }
    bool operator == (const status &x)const{
        return data==x.data;
    }
    bool isEven(){
        int num=0;
        for(unsigned int i=0;i!=data.size();i++){
            for(unsigned int j=0;j!=data.size();j++){
                if(data[i]>data[j]&&data[j]!=0){
                    num++;
                }
            }
        }
        return num%2;
    }
    void show(){
        for(unsigned int i=0;i!=data.size();i++){
            cout<<data[i]<<" ";
            if((i+1)%3==0){
                cout<<endl;
            }
        }
    }
};
status move(status root,int target){
    if(target==-3&&root.zero<3){
        return root;
    }
    if(target==3&&root.zero>5){
        return root;
    }
    if(target==1&&(root.zero==2||root.zero==5||root.zero==8)){
        return root;
    }
    if(target==-1&&(root.zero==0||root.zero==3||root.zero==6)){
        return root;
    }
    swap(root.data[root.zero],root.data[root.zero+target]);
    root.zero=root.zero+target;
    return root;
}
int nodeDistance(const status &a,const status &b){
    int h1,h2,sum=0;
    for(int k=1;k<=8;k++){//分别检测数字0到8
		for(int i=0;i<9;i++){
			if(a.data[i]==k)
				h1=i;
			if(b.data[i]==k)
				h2=i;
		}
		sum+=abs(h1/3-h2/3)+abs(h1%3-h2%3);
	}
    return sum;
}
void core(vector<int> &beginArray,vector<int> &endArray){
    status beginStatus,endStatus;
    beginStatus.data=beginArray;
    endStatus.data=endArray;
    for(unsigned int i=0;i!=beginArray.size();i++){
        if(beginArray[i]==0){
            beginStatus.zero=i;
        }
    }
    for(unsigned int i=0;i!=endArray.size();i++){
        if(endArray[i]==0){
            endStatus.zero=i;
        }
    }
    beginStatus.parent=-1;
    beginStatus.f=beginStatus.h=nodeDistance(beginStatus,endStatus);
    beginStatus.g=0;
    beginStatus.index=0;
    endStatus.index=1;

    //初始化起始状态

    if(beginStatus.isEven()!=endStatus.isEven()){
        return;
    }

    cout<<"Test data:   "<<endl;
    cout<<beginStatus.f<<endl;

    vector<status> statusBin;
    statusBin.push_back(beginStatus);
    statusBin.push_back(endStatus);


    map<vector<int>,status> OPEN,CLOSE;
    OPEN[beginStatus.data]=beginStatus;
    int dec[4]={1,-1,3,-3};

    while(!OPEN.empty()){
        int MAX=(1<<30)-1;
        map<vector<int>,status>::iterator it,mark;
        for(it=OPEN.begin();it!=OPEN.end();it++){
            if(it->second.f<MAX){
                MAX=it->second.f;
                mark=it;//取最小值
            }
        }

        CLOSE[mark->first]=mark->second;//插入最小值

        if(mark->second==endStatus){
            statusBin[1].parent=mark->second.index;
            break;
        }

        for(int i=0;i!=4;i++){
            status newStatus=move(mark->second,dec[i]);//生成新状态
            if(newStatus.zero==mark->second.zero){
                continue;
            }

            newStatus.parent=mark->second.index;
            newStatus.g=mark->second.g+1;
            newStatus.h=nodeDistance(newStatus,mark->second);
            newStatus.f=newStatus.g+newStatus.h;
            if((it=OPEN.find(newStatus.data))==OPEN.end()){
                newStatus.index=statusBin.size();
                statusBin.push_back(newStatus);
                OPEN[newStatus.data]=newStatus;
            }else{
                if(it->second.g>newStatus.g){
                    newStatus.index=it->second.index;
                    statusBin[it->second.index]=newStatus;
                    it->second=newStatus;
                }
            }
        }
        OPEN.erase(mark);//删除源状态
    }
    cout<<"find answer"<<endl;
    for(int i=1;i!=-1;){
        statusBin[i].show();
        cout<<"---------"<<statusBin[i].parent<<endl;
        i=statusBin[i].parent;
    }
}
int main(){
    int a[]={2,3,0,7,1,6,5,8,4};
    int b[]={1,2,3,4,5,6,7,8,0};
    vector<int> c(a,a+9);
    vector<int> d(b,b+9);
    for(unsigned int i=0;i!=c.size();i++){
        cout<<c[i];
    }
    cout<<endl;
    core(c,d);
}
//Designed by wolf
