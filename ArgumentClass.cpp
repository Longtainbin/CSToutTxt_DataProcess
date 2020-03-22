#include "ArgumentClass.h"
#include<string>
#include<iostream>
#include<regex>

using std::string;
using std::cin;
using std::cout;
using std::endl;

//输入函数的模板
template<typename T>
void  getParas(T & val,const unsigned int step,const string& str)
{
std::cout<<"步骤 "<<step<<":"<<str<<std::endl;
    while ((!(cin >> val)))
    {
        cin.clear();
        while (cin.get()!='\n')
            continue;
       std::cout<<"步骤 "<<step<<":"<<str<<std::endl;; 
    }
}

//输入函数模板的std::string类型具体化
template<>
void getParas<std::string>(std::string& val, const unsigned int step, const string& str)
{
std::cout<<"步骤 "<<step<<":"<<str<<std::endl;
getline(cin,val);
std::smatch sm;
std::regex pattern("[\\s]*(\\S+)[\\s]*"); //判读是否是空白字符串
bool rgeFlg=std::regex_search(val, sm, pattern);

while ((val.size()==0)||rgeFlg==false)
{
std::cout<<"步骤 "<<step<<":"<<str<<std::endl;
getline(cin,val);
rgeFlg=std::regex_search(val, sm, pattern);
}
val=sm[1].str();
}


//输入待处理文件名
void ArgumentClass::setFileName()
{
getParas(infileName,1,"请输入待处理的文件名(例如：S11Theta.txt 注意:该文件应当何本程序放在同一目录下)");
}

//输入新文件的特征字符串
void ArgumentClass::setNewFileFlag()
{
getParas(newFileFlag,2,"请输入创建新文件的标志性字符串(例如：Frequency)");
}


//输入扫描参数
void ArgumentClass::setParaStr()
{
getParas(paraStr,3,"如果是参数扫描请输入：扫描的参数(例如：theta); 如果不是进行参数扫描,就输入: mydata");

}
//输入频率
void  ArgumentClass::setFreLow()
{
getParas<double>(lowLine,4,"请输入截止频率下限(例如:6.5)");
}

void  ArgumentClass::setFreHig()
{
getParas<double>(heiLine,5,"请输入截止频率上限(例如:9.5)");
}

void  ArgumentClass::setFreGap()
{
getParas<double>(gap,6,"请输入频率间隔(例如:0.003)");

}

void ArgumentClass::setAllParas()
{
setFileName();
setNewFileFlag();
setParaStr();
setFreLow();
setFreHig();
while (lowLine > heiLine)
{
std::cout<<"\"截止频率下限\"应当小于\"截止频率上限\"！ 请重新输入截止频率"<<std::endl;
setFreLow();
setFreHig();
}
setFreGap();
while ((gap>heiLine-lowLine)||(gap<0))
{
std::cout<<"频率间隔 过大或过小! 请重新输入 频率间隔"<<std::endl;
setFreGap();
}
}
