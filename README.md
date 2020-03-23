# CST文本数据处理程序
---
## 1.  项目背景
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在从电磁仿真软件CST Studio Suite导出仿真数据时，可能存在导出的频率点并非时线性增加的，在参数扫描时也可能生成 的频率点个数不同，导致无法进行作图对比；对此可以人工挑选出“不合格”的频点数据，但是当数据量增加时，人力成本也随之增加，且还存在一定的误删、漏删等问题。考虑到从该仿真软件导出的txt格式的数据有一定的数据格式，故而希望通过C++编程处理这些数据，摆脱重复繁重的任务。

## 2. 版本
> ![version 1.0](https://img.shields.io/badge/version-1.0-orange)

## 3. 安装
  1. 将下载的压缩包解压，应当确保 *ArgumentClass.cpp、ArgumentClass.h、main.cpp* 在同一目录下
  2. 编译并生成可执行文件
        * 使用集成开发环境(IDE)编译: 例如 在 Visual Studio 2019(应当确保该IDE 支持C++11或C++17,不依赖额外的库支持)中，创建新项目->
          控制台应用->输入项目名称->创建;将原始的项目源代码删除，并将*ArgumentClass.cpp、ArgumentClass.h、main.cpp*三
          个文件导入该项目；然后在 顶部菜单中选择 调试->开始执行(不调试) [快捷键: Ctrl+F5],即可自动编译生成并运行可执行
          文件。可以在该项目文件夹下的 Debug(或者 x64\Debug) 目录下找到 生成的可执行文件（即 .exe格式文件)。
          
        * 使用g++ 编译: (应当确保 g++ 支持C++11或C++17,不依赖额外的库支持)通过命令行进入 ArgumentClass.cpp、ArgumentClass.h、main.cpp
          所在的目录，并输入如下命令:
            >g++ -std=c++11 -fexec-charset=gbk  main.cpp ArgumentClass.cpp -o main.exe
            
            或者
            >g++ -std=c++17 -fexec-charset=gbk  main.cpp ArgumentClass.cpp -o main.exe
            
            其中 *-fexec-charset=gbk* 选项指定*GBK*编码，以避免出现中文乱码问题。
            完成后即可在当前目录生成可执行文件。(即 main.exe,可以重命名为自己喜欢的名字)
 
 ## 4. 使用说明
 
   + #### 程序界面: 
     打开可执行程序后初始界面如下图所示,提示需要输入6个参数
  
        ![初始程序界面](https://github.com/Longtainbin/mediaResource/blob/master/picture/usingExamplePhoto0.png)
   
   + #### 参数说明: 
      1. **文件名**：待处理的文本文件完整名称(含扩展名)，且应当将该文件与可执行程序放置与同一目录下，以确保程序能正确的找的该文件。
      2. **标志性字符串**：标志性字符串有两个作用：标志新的数据块到来进而创建新的文件；标志在这一行有 待提取的扫描参数值。故而标志性
        字符串应当满足在一个数据块的信息头部 只出现一次，标志性字符串所在行包含待提取的扫描参数值。
      3. **扫描参数或mydata**： 当进行参数扫描时，就输入扫描参数；如果 只是含有一个数据块，没有进行参数扫描，就只能输入***mydata*** 。
      
          **例 1：**
      
          ![例 1](https://github.com/Longtainbin/mediaResource/blob/master/picture/example1.png)
      
          > ***当数据头部信息如上图所示时：标志性字符串可以输入：Parameters、Frequency、SZmax(1)等中的任意一个；扫描参数输入：theta。***
      
          **例 2：**
      
          ![例 2](https://github.com/Longtainbin/mediaResource/blob/master/picture/example2.png)
      
          > ***当数据头部信息如上图所示时：标志性字符串可以输入：Mix；扫描参数输入：first_routate。***
      
     4. **频率**：频率根据需要输入即可，但应当确保截止频率上限不小于保截止频率下线，频率间隔不大于保截止频率上限于保截止频率下限之差。
      
   + #### 运行结果:  
      - 对参数***theta***进行参数扫描后的运行结果如下图:
      
          ![图例 1](https://github.com/Longtainbin/mediaResource/blob/master/picture/usingExamplePhoto.png)
      
      - **非参数扫描**的运行结果如下图:
      
          ![图例 2](https://github.com/Longtainbin/mediaResource/blob/master/picture/usingExamplePhoto2.png)     

      

## 5. 开源协议
[![GitHub license](https://img.shields.io/github/license/Longtainbin/CSToutTxt_DataProcess)](https://github.com/Longtainbin/CSToutTxt_DataProcess/blob/master/LICENSE)
