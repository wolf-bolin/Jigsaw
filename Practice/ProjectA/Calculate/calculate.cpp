
#include "calculate.h"

#define Endl endl
using namespace std;
class shortexp{
public:
    bool flag;
    vector<double> num;
    vector<int> op;//+ - % * / ^
    shortexp(){
        flag=0;
    }
    double getNum(){
        if(num.size()==0){
            //表达式无值的情况排除
            flag=1;
            return -1;
        }
        //计算不含括号的表达式的值
        double ans=0;
        while(op.size()!=0){
            /**
            *取出优先级最高的操作符的位置
            **/
            int maxop=0,maxindex;
            for(int i=0;i!=op.size();i++){
                if((maxop>=3&&maxop<=5)&&(op[i]>=3&&op[i]<=5)){
                    continue;
                }
                if(op[i]>maxop){
                    maxop=op[i];
                    maxindex=i;
                }
            }

            if(maxop==1){
                //加法
                num[maxindex+1]=num[maxindex]+num[maxindex+1];
            }else if(maxop==2){
                //减法
                num[maxindex+1]=num[maxindex]-num[maxindex+1];
            }else if(maxop==3){
                //取余
                if(num[maxindex]-(int)num[maxindex]>0||num[maxindex+1]-(int)num[maxindex+1]>0){
                    //排除小数点
                    flag=1;
                    return -1;
                }
                if((int)num[maxindex+1]==0){
                    //排除 %0
                    flag=1;
                    return -1;
                }
                num[maxindex+1]=(int)num[maxindex]%(int)num[maxindex+1];
            }else if(maxop==4){
                //除法
                if(num[maxindex+1]==0){
                    flag=1;
                    return -1;
                }
                num[maxindex+1]=num[maxindex]/num[maxindex+1];
            }else if(maxop==5){
                //乘法
                num[maxindex+1]=num[maxindex]*num[maxindex+1];
            }else if(maxop==6){
                //次方
                if(num[maxindex]==0&&num[maxindex+1]==0){
                    flag=1;
                    return -1;
                }
                num[maxindex+1]=pow(num[maxindex],num[maxindex+1]);
            }
            //删除多余数据
            vector<double>::iterator itnum=num.begin();
            vector<int>::iterator itop=op.begin();
            itnum+=maxindex;
            itop+=maxindex;
            num.erase(itnum);
            op.erase(itop);
        }
        return num.front();
    }
    int getNumSize(){
        //获取表达式中已有几个数字
        return num.size();
    }
    void insertNum(double k){
        //插入一个新的数字
        num.push_back(k);
    }
    void insertOP(char k){
        //插入一个新的操作
        if(k=='+'){
            op.push_back(1);
        }else if(k=='-'){
            op.push_back(2);
        }else if(k=='%'){
            op.push_back(3);
        }else if(k=='/'){
            op.push_back(4);
        }else if(k=='*'){
            op.push_back(5);
        }else if(k=='^'){
            op.push_back(6);
        }
    }
};
class stack{
    //强行证明我会使用栈结构
    //该栈能解决 2^31 个元素入队的情况
public:
    vector<shortexp> buffer;
    stack(){}
    void push(shortexp element){
        buffer.push_back(element);
    }
    shortexp top(){
        return buffer.back();
    }
    void pop(){
        buffer.pop_back();
    }
    void clear(){
        buffer.resize(0);
    }
};
shortexp core();
stringstream buffer,answer;
stack expstack;

string calc(string exp){
    //清空数据域
    buffer.clear();
    buffer.str("");
    answer.clear();
    answer.str("");
    expstack.clear();
    //检查输入字符串中括号是否匹配
    int sum=0;
    for(unsigned int i=0;i!=exp.size();i++){
        if(exp[i]!='0'&&exp[i]!='1'&&exp[i]!='2'&&exp[i]!='3'&&exp[i]!='4'&&
            exp[i]!='5'&&exp[i]!='6'&&exp[i]!='7'&&exp[i]!='8'&&exp[i]!='9'&&
            exp[i]!='+'&&exp[i]!='-'&&exp[i]!='*'&&exp[i]!='/'&&exp[i]!='%'&&
            exp[i]!='^'&&exp[i]!='('&&exp[i]!=')'&&exp[i]!=' '&&exp[i]!='.'){
                answer<<"Illegal"<<endl;
                return 0;
        }
        if(exp[i]==' '){
            continue;
        }
        if(exp[i]=='('){
            sum++;
        }else if(exp[i]==')'){
            sum--;
        }
        //将数据写入缓冲流中
        buffer<<exp[i];
    }
    if(sum!=0){
        answer<<"Illegal"<<endl;
        return 0;
    }
    //递归计算表达式的值
    shortexp it=core();
    it.getNum();
    if(it.flag){
        answer<<"Illegal"<<endl;
    }else{
        answer<<it.getNum()<<endl;
    }
    string str;
    answer>>str;
    return str;
}
double getNextNum(){
    //从缓冲区中读取一个数字
    double val;
    buffer>>val;
    return val;
}
shortexp core(){
    //递归读取并计算一组不含括号的表达式
    shortexp ans;
    char partexp;
    partexp=buffer.peek();//预判下一个字符是操作符还是数字
    if(partexp>='0'&&partexp<='9'){
        ans.insertNum(getNextNum());
        partexp=buffer.peek();
        if(partexp=='('){
            //数字后面不能直接连接括号
            ans.flag=1;
            return ans;
        }
    }else if(partexp=='%'||partexp=='*'||partexp=='/'||partexp=='^'){
        //开头出现不合法操作符
        ans.flag=1;
        return ans;
    }
    while(buffer>>partexp){
        //真正的读取
        if(partexp=='('){
            //使用栈结构保存当前表达式的状态
            expstack.push(ans);
            //读取到一个括号，递归获取括号内的表达式
            //计算表达式的值 插入 跳过本轮 读取下一个操作
            shortexp it=core();
            it.getNum();
            //从栈中恢复表达式的状态
            ans=expstack.top();
            expstack.pop();
            if(it.flag){
                ans.flag=1;
                return ans;
            }else{
                ans.insertNum(it.getNum());
            }
            continue;
        }else if(partexp=='+'){
            if(ans.getNumSize()==0){
                //读取到首位为带有 正号的数字
                //不操作 无意义
            }else{
                //读取到操作，插入操作
                ans.insertOP('+');
            }
        }else if(partexp=='-'){
            if(ans.getNumSize()==0){
                //读取到首位为带有 负号的数字
                ans.insertNum(0);
                ans.insertOP('-');
            }else{
                //读取到操作，插入操作
                ans.insertOP('-');
            }
        }else if(partexp=='%'){
            //读取到操作，插入操作
            ans.insertOP('%');
        }else if(partexp=='*'){
            //读取到操作，插入操作
            ans.insertOP('*');
        }else if(partexp=='/'){
            //读取到操作，插入操作
            ans.insertOP('/');
        }else if(partexp=='^'){
            //读取到操作，插入操作
            ans.insertOP('^');
        }else if(partexp==')'){
            //读取到右括号，结束递归
            return ans;
        }
        partexp=buffer.peek();//预判下一个字符是操作符还是数字
        if(partexp>='0'&&partexp<='9'){
            //在读取了操作之后读取下一个数字
            ans.insertNum(getNextNum());
            partexp=buffer.peek();//预判下一个字符
            if(partexp=='('){
                //数字后面不能直接连接括号
                ans.flag=1;
                return ans;
            }
        }else if(partexp=='('){
            //操作符后连接括号的情况
            continue;
        }else{
            //出现多符号连接的不合法情况
            ans.flag=1;
            return ans;
        }
    }
    //读取结束 返回表达式
    return ans;
}
