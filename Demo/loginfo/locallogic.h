#ifndef LOCALLOGIC_H
#define LOCALLOGIC_H

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<time.h>

class moveinfo;

void movelog(std::vector<moveinfo> &logs,int m,int n);
void savemovelog(std::vector<moveinfo> &logs);
void readmovelog(std::vector<moveinfo> &logs);

void savestatus(std::vector<int> &data,int step,int hh,int mm,int ss);
void readstatus(std::vector<int> &data,int step,int hh,int mm,int ss);

bool cansolve(std::vector<int> &data);
std::vector<int> newgame();

#endif // LOCALLOGIC_H

