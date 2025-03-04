# Kama-AsynLogSystem

⭐️ 本项目为【代码随想录知识星球】 教学项目

[详细文档链接](https://www.yuque.com/chengxuyuancarl/ipf60h)

⭐️ 在里详细讲解：项目前置知识 + 项目细节 + 代码框架解读 + 面试题与回答 + 简历写法 + 项目拓展。 全面帮助你用这个项目求职面试！

## 项目概述

本项目基于**libevent**网络库实现文件上传服务，支持上传下载和展示功能，支持多种存储等级的存储服务，并携带了异步日志系统，支持备份重要日志，多线程并发写日志等功能。

## 环境准备

Ubuntu22.04 LTS

g++安装

```bash
sudo update
sudo apt install g++
```

### 日志部分

#### 1. jsoncpp

```bash
sudo apt-get libjsoncpp-dev
其头文件所在路径是：/usr/include/jsoncpp/json
动态库在：/usr/lib/x86_64-linux-gnu/libjsoncpp.so-版本号
编译时需要根据动态库的路径进行正确的设置，否则很容易出现“undefined reference to”问题。
使用g++编译时直接加上“-ljsoncpp”选项即可。
```

### 存储部分

### 服务端

#### 1. libevent

Linux下安装方法：

```bash
sudo apt-get update
sudo apt-get install build-essential autoconf automake
sudo apt-get install libssl-dev
./configure
wget https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz
tar xvf libevent-2.1.12-stable.tar.gz  //解压下载的源码压缩包，目录下会生成一个libevent-2.1.12-stable目录
cd libevent-2.1.12-stable                 //切换到libevent-2.1.12-stable目录,(安装步骤可以查看README.md文件)
./configure                                       //生成Makefile文件，用ll Makefile可以看到Makefile文件已生成
make                                          //编译
sudo make install                            //安装

# 最后检测是否成功安装
cd sample     //切换到sample目录
./hello-world   //运行hello-world可执行文件
# 新建一个终端，输入以下代码
nc 127.1 9995 //若安装成功，该终端会返回一个Hello, World!
```

#### 2. jsoncpp

日志部分已经安装

#### 3. bundle

源码链接：https://github.com/r-lyeh-archived/bundle

克隆下来包含bundle.cpp与bundle.h即可使用 

### 客户端Win

#### 1. libevent

Win的话会麻烦不少。提前准备工具：

[libevent直接在这里面下，2.1.12-stable版本](https://libevent.org/)

[安装vs2019之后](https://blog.csdn.net/adminstate/article/details/128939556)

[在openssl的github获取源码，把zip文件下载下来](https://github.com/openssl/openssl)

[Perl安装地址](http://www.ffmpeg.club/libevent.html)

[nasm安装地址，网盘里有3个，选那个win32的](http://www.ffmpeg.club/libevent.html)，这里从网盘下载后就ok了，然后把nasm的路径加到环境变量里

安装perl时，选择Complete安装选项，之后直接一路next就好!

```bash
# 使用以下命令
nasm --version  
perl --version
```

然后使用Win的搜索，输入vs 2019,找到x64_x86 Cross Tools CommandPrompt for Vs 2019，以管理员身份打开

进入到openssl的源码目录下执行编译安装openssl

```bash
perl Configure VC-WIN32 --prefix=D:\software\openssl_output#自己改路径，这个路径是你指定的openssl的安装路径
nmake #这命令时间比较长
nmake install #这个时间会比较长
```

执行完上述命令后你将会在D:\software\openssl_output路径下得到，这个路径就是openssl的安装路径了，存放了一些静态库，可执行文件啥的。把openssl可执行文件的路径添加到环境变量不然后面执行的时候找不到库。

把前面下载的libevent库解压了，然后用前面打开的命令行进入libevent源码的目录执行命令:

```bash
nmake /f Makefile.nmake OPENSSL_DIR=D:\software\openssl_output
```

结束后，使用源码目录的test/目录下的regress.exe执行一下，如果成功执行就说明安装成功了，不用等所有测试都显示OK。

如果遇到找不到库或者头文件之类的问题，在自己文件资源管理器里找一下对应的库复制到对应目录下就ok了。比如少了event-config.h，那就复制一份到include/event2/目录下就ok了。

至此安装部分就结束了，但是使用的话需要配置一下vs2019.

首先使用的时候要是x86环境，因为前面编译的库都是x86的

其次，在vs2019的菜单来中点击Debug->Debug Properties->Configuragion Properties->C/C++->General->Additional Include Directories，把你的libevent头文件路径添加进去，即libevent源码目录/include。

然后在C/C++下面的Linker把库路径和库的名字加上：Linker->General->Additional Library Directories 在这里添加你的libevent源码路径。

然后再Linker下点击Input，点击Additional Dependenies ，点击<Edit...>，输入libevent.lib;ws2_32.lib;

## 运行方式

走到src目录下的server目录，`make`即可生成test可执行文件。把log_stsytem目录下的backlog目录中的ServerBackupLog.cpp和hpp文件拷贝置另外一个服务器或当前服务器作为备份日志服务器，使用命令`g++ ServerBackupLog.cpp`即可启动备份日志服务器，随后`./test`即可运行整个服务。

启动后，默认占用服务器8081端口。



