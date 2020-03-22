# CST文本数据处理程序

## 1.  项目背景
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在从电磁仿真软件CST Studio Suite导出仿真数据时，可能存在导出的频率点并非时线性增加的，在参数扫描时也可能生成 的频率点个数不同，导致无法进行作图对比；对此可以人工挑选出“不合格”的频点数据，但是当数据量增加时，人力成本也随之增加，且还存在一定的误删、漏删等问题。考虑到从该仿真软件导出的txt格式的数据有一定的数据格式，故而希望通过C++编程处理这些数据，摆脱重复繁重的任务。

## 2. 安装
  1. 将下载的压缩包解压，应当确保 ArgumentClass.cpp、ArgumentClass.h、main.cpp 在同一目录下
  2. 编译并生成可执行文件
        * 使用集成开发环境(IDE)编译: 例如 在 Visual Studio 2019(应当确保该IDE 支持C++11或C++17,不依赖额外的库支持)中，创建新项目->
          控制台应用->输入项目名称->创建;将原始的项目源代码删除，并将ArgumentClass.cpp、ArgumentClass.h、main.cpp三
          个文件导入该项目；然后在 顶部菜单中选择 调试->开始执行(不调试) [快捷键: Ctrl+F5],即可自动编译生成并运行可执行
          文件。可以在该项目文件夹下的 Debug(或者 x64\Debug) 目录下找到 生成的可执行文件（即 .exe格式文件)。
          
        * 使用g++ 编译: (应当确保 g++ 支持C++11或C++17,不依赖额外的库支持)通过命令行进入 ArgumentClass.cpp、ArgumentClass.h、main.cpp
          所在的目录，并输入如下命令:
            >g++ -std=c++11 -fexec-charset=gbk  main.cpp ArgumentClass.cpp -o main.exe
            
            或者
            >g++ -std=c++17 -fexec-charset=gbk  main.cpp ArgumentClass.cpp -o main.exe
            
            其中 -fexec-charset=gbk 选项指定GBK编码，以避免出现中文乱码问题。
            完成后即可在当前目录生成可执行文件。(即 main.exe,可以重命名为自己喜欢的名字)
 
 ## 3. 使用说明

主要项目负责人
参与贡献方式
开源协议
