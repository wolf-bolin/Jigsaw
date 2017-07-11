#include "locallogic.h"

class moveinfo{
public:
    int step,m,n;
    moveinfo(){}
    moveinfo(int a,int b,int c){
        step=a;
        m=b;
        n=c;
    }
};

void movelog(std::vector<moveinfo> &logs,int m,int n){
    logs.push_back(moveinfo(logs.size()+1,m,n));
}
void savemovelog(std::vector<moveinfo> &logs){
    std::ofstream fout("./molvlog.log");
    for(unsigned int i=0;i!=logs.size();i++){
        fout<<logs[i].step<<" "<<logs[i].m<<" "<<logs[i].n<<std::endl;
    }
}

void readmovelog(std::vector<moveinfo> &logs){
    std::ifstream fin("./molvlog.log");
    if(!fin){
        std::ofstream fout("./molvlog.log");
        return;
    }
    moveinfo temp;
    while(fin>>temp.step>>temp.m>>temp.n){
        logs.push_back(temp);
    }
}

void savestatus(std::vector<int> &data,int step,int hh,int mm,int ss){
    std::ofstream fout("./status.log");
    for(unsigned int i=0;i!=data.size();i++){
        fout<<data[i]<<" ";
    }
    fout<<std::endl;
    fout<<step<<" "<<hh<<" "<<mm<<" "<<ss<<std::endl;
}

void readstatus(std::vector<int> &data,int step,int hh,int mm,int ss){
    std::ifstream fin("./status.log");
    if(!fin){
        std::ofstream fout("./status.log");
        return;
    }
    for(int i=0;i!=9;i++){
        int temp;
        fin>>temp;
        data.push_back(temp);
    }
    fin>>step>>hh>>mm>>ss;
}

bool cansolve(std::vector<int> &data){
    int num=0;
    for(unsigned int i=0;i!=data.size();i++){
        for(unsigned int j=0;j!=data.size();j++){
            if(data[i]>data[j]&&data[j]!=0){
                num++;
            }
        }
    }
    return !(num%2);
}

std::vector<int> newgame(){
    srand((unsigned)time(NULL));

}
