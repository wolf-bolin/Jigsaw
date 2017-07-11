#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include <map>
#include <cmath>

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

class gameinfo{
public:
    std::string userName;
    int gameTime,gameStep,score;
    gameinfo(){}
    gameinfo(std::string name,int a,int b,int c){
        userName=name;
        gameTime=a;
        gameStep=b;
        score=c;
    }
    bool operator < (const gameinfo & x)const{
        return score<x.score;
    }
};

void moveLog(std::vector<moveinfo> &logs,int m,int n);
void saveMoveLog(std::vector<moveinfo> &logs);
void readMoveLog(std::vector<moveinfo> &logs);

void saveStatus(std::vector<int> &numData,int gameStep,int gameTime);
void readStatus(std::vector<int> &numData,int &gameStep,int &gameTime);

void saveGameLog(std::vector<gameinfo> &rankTable);
void readGameLog(std::vector<gameinfo> &rankTable);

void saveSetting(std::string picPath);
void readSetting(std::string &picPath);

bool canSolve(std::vector<int> &numData,std::vector<int> &standard);
void newGame(std::vector<int> &numData,int &gameStep,int &gameTime);

void astar(std::vector<int> numData,std::vector<moveinfo> &answer);

#endif // GAMELOGIC_H
