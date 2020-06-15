
//Author: Tianbin Long
//Date: 2020/3/22
//说明： 该程序用于整理从CST导出的数据，使其能够频率点按照线性排列

#include<iostream>
#include<fstream>
#include <string>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<regex>
#include "ArgumentClass.h"

using std::string;
using std::cout;
using std::cin;
using std::endl; 
using std::ifstream;
using std::ofstream;
using std::vector;
using std::shared_ptr;

unsigned int countFileNum(ifstream& fi,const string &newFileFlag);
bool findPara(const string& str,const string & matchStr,string & tempFileN);
bool freIsRight(const string & str,const double & lowLine,
                const double & heiLine,const double &gap,const double &delat=1E-8);
std::ostream& outStr(std::ostream& os, const string& str);

template<typename T>
void fileIsOpen(T & fstr,const string& fileName);
void init();

int main()
{ 
init();
const double delat=1E-7;

ArgumentClass argum;
argum.setAllParas();
string infileName=argum.reInfileName();
string newFileFlag=argum.reNewFileFlag();
string paraStr=argum.reParaStr();
double lowLine=argum.reLowLine();
double heiLine=argum.reHeiLine();
double gap=argum.reGap();

ifstream fin;
fin.open(infileName,std::ios_base::in);
fileIsOpen(fin,infileName);
unsigned int fileNum =countFileNum(fin,newFileFlag);//记录文件个数

vector<unsigned long> v_tempLineNum(fileNum);
for_each(v_tempLineNum.begin(),v_tempLineNum.end(),[](int x){return x=0;});
vector<string> sp_tempFileName(fileNum);
vector<shared_ptr<ofstream>> sp_fout(fileNum);

unsigned int findex=0;//跟踪第findex个文件
std::smatch sm;
const std::regex pattern("^[\\s]*(-?\\d+.?\\d*)[\\s]*");//判断是否是数据行的正则表达式,分组sm[1]存储频率字符串

string strtemp;//暂存每行的字符串

//fin.seekg(0);//重置文件指针到文件首部 在这好像不行，就通过先关闭再打开 重置文件指针
fileIsOpen(fin,infileName);
fin.close();
fin.open(infileName,std::ios_base::in);
fileIsOpen(fin,infileName);

getline(fin,strtemp);
while (fin)
{   
if(strtemp.size())//跳过空行...
{ 
        if (strtemp.find(newFileFlag)!=string::npos) //通过 newFileFlag 识别是否创建新文件 
        {
           ++findex;
            try
            {
               findPara(strtemp,paraStr,sp_tempFileName[findex-1]);
            }
            catch (std::string str)
            {
                cout<<str<<endl;
                system("pause");
                exit(EXIT_FAILURE);
            }
//注意：
//初始化 shared_ptr<ofstream> 的形式如 # 1 所示，不能写成 # 2；
// 原因： 在语句  vector<shared_ptr<ofstream>> sp_fout(fileNum) 中没有给每个输出流分配地址，所以用 -> 会直接停止，
// 初始化时 shared_ptr<TypeName>(Arg...) Arg...为类型TypeName的常规初始的参数列表。

        // # 1
           (sp_fout[findex-1])=std::make_shared<ofstream>(sp_tempFileName[findex-1]+".txt",std::ios_base::in|std::ios_base::out|std::ios_base::trunc); 
        // # 2
        //sp_fout[findex-1]->open(sp_tempFileName[findex-1]+".txt",std::ios_base::in|std::ios_base::out|std::ios_base::trunc); 
            fileIsOpen((*sp_fout[findex-1]),sp_tempFileName[findex-1]+".txt");     
        }
       //判断是否是数据行的两种方法 1. 通过正则表达式  2.通过 开头字符不是 # 或 -
       // 优缺点：通过正则表达式 对应一些数据格式兼容性强一些 但是及其消耗时间
        // 通过开头字符确定 兼容性差一些 但是快很多 
        
       else  if(strtemp[0]!='#'&&strtemp[0]!='-')
            { if (freIsRight(strtemp, lowLine, heiLine, gap, delat))
         // if(std::regex_search(strtemp, sm, pattern))    //
          //{ if (freIsRight(sm[1].str(), lowLine, heiLine, gap, delat))
                    {
                        v_tempLineNum[findex-1]++;
                        outStr(*sp_fout[findex-1],strtemp);
                     }
             }        
}   
getline(fin,strtemp);
}

//输出总览
cout<<std::setfill('*')<<std::setw(70)<<" "<<std::setfill(' ')<<endl;
cout<<"处理完成!"<<endl;
cout<<"总共生成  "<<fileNum<<"  个文件，详情如下:\n\n";
cout<<std::setw(20)<<"文件名"<<std::setw(4)<<" "<<std::setw(8)<<"行数"<<endl;
for (unsigned int i = 0; i < fileNum; ++i)
{
    cout<<std::setw(20)<<(sp_tempFileName[i])+".txt"<<std::setw(4)<<" "<<std::setw(8)<<(v_tempLineNum[i])<<endl;
}
//关闭文件
if(fin.is_open())
    fin.close();
for (unsigned int i = 0; i < fileNum; ++i)
{
if(sp_fout[i]!=nullptr)
    { if(sp_fout[i]->is_open())
            sp_fout[i]->close();
    }
}

system("pause");
return 0;
}


//相关函数实现
//确定文件数目
unsigned int countFileNum(ifstream& fi,const string &newFileFlag)
//fi 为输入的文件流，根据字符串"#-"来判断是否生成新的文件
{
string strtemp;
unsigned int fileNum=0;

getline(fi,strtemp);
while (fi)
{
   if( strtemp.find(newFileFlag)!=string::npos)
      { 
           fileNum++; 
      }
getline(fi,strtemp);
}
if (fileNum==0)
{
cout<<"根据输入的创建新文件的标志性字符串:"<<newFileFlag<<" 无法获得合适的数据！"<<endl;
exit(EXIT_FAILURE);
}
return fileNum;
}

//提取参数值,找到了返回1，否则返回 0,
bool findPara(const string& str,const string & matchStr,string & tempFileN)
//str为被查找的字符串，matchStr为给出的字符串，tempFilN为返回的参数名
{
bool flag=false;
if(matchStr!="mydata")
{ 
size_t matchIndex=str.find(matchStr);
    if (matchIndex!= string::npos)
    {    
        char ch=str[matchIndex];
        while (ch != ')' && ch != '\0'&& ch!=';')//通过 符合 ; 或者 ) 判断参数数值结尾
        {   
            if(ch=='=')
                ch='_';  //把等号=  换成下划线_ ，在文件名中更加通用
            tempFileN+=ch;
            matchIndex++;
            ch=str[matchIndex];
        } 
        if(ch=='\0')
            {//throw("在数据头信息中 没有 找到参数: "+matchStr+" 的具体值!!!");
                std::clock_t tt=std::clock();
                tempFileN=(matchStr+"NoPara"+std::to_string(tt));//生成一个独特的文件名
            }
    }
    else
    {
        throw(("在数据头信息中 没有 找到参数: "+matchStr+" !!!"));
    }
  }
else
{
tempFileN="mydata";
flag=true;
}

return flag;
}

//判读频率是否符合要求
bool freIsRight(const string & str,const double & lowLine,const double & heiLine,const double &gap,const double &delat)
{
double freq=stod(str);

if(freq>heiLine||freq<lowLine)
    return false;
//cout<<fmod((freq-lowLine),gap)<<endl;
bool flag=((fabs(fmod((freq-lowLine),gap))<=(delat*gap))||fabs(fmod((freq-lowLine),gap)-gap)<=(delat*gap));//delat 注要是考虑0.03 不一定是0.03

return flag;
}

//输出正确频点到文件
std::ostream& outStr(std::ostream& os, const string& str)
{
os<<str<<endl;
return os;
}

template<typename T>
void fileIsOpen(T & fstr,const std::string &fileName)
{
if(!(fstr.is_open()))
{ 
 std::cout<<"无法打开文件:"<<fileName<<std::endl;
 system("pause");
 exit(EXIT_FAILURE);
}
}

void init()
{
system("title CST文本数据处理程序");//设置cmd窗口标题
system("mode con cols=100 lines=70");//窗口宽度高度
system("color 0B");

cout<<"CST文本数据处理程序\n";
cout<<"源代码: https://github.com/Longtainbin/CSToutTxt_DataProcess"<<endl;
cout<<std::setfill('*')<<std::setw(70)<<" "<<std::setfill(' ')<<endl;
cout<<"说明：请按提示";
cout<<"\"正确\"";
cout<<"输入 6 个参数：\n\n"
    <<std::setw(40)<<std::left
    <<"1. 完整的文件名"<<std::setw(8)<<" "<<"2. 分隔不同扫描参数的标志性字符串\n\n"
    <<std::setw(40)<<std::left
    <<"3. 完整的扫描参数 或者 mydata"<<std::setw(8)<<" "<<"4. 截止频率下限\n\n"
    <<std::setw(40)<<std::left
    <<"5. 截止频率上限"<<std::setw(8)<<" "<<"6. 频率间隔\n"<<endl;
cout<<std::setfill('*')<<std::setw(70)<<" "<<std::setfill(' ')<<endl;

}