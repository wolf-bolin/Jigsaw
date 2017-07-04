# Qt编程笔记

——解决方案

## tr("&")

对字符串进行处理，使其翻译为其他语言的标记，建议用户可见的字符都使用。“&”为转义字符，其后的一个字符表示获取该对象热点的快捷键。

## Q_OBJECT

只有加入了Q_OBJECT，你才能使用QT中的signal和slot机制（信号/槽）。  

## signals:

写在类中，在此宏后定义信号函数，定义了对象的功能。

## slots:

写在类中，在此宏后定义槽函数，定义了对象的功能。

## emit

激发信号，激发指定的信号函数（虚函数），调用其连接的槽函数（实函数）。

emit是Qt中的关键字，会被C++预处理器转换成标准的C++代码。

## signal&slot

* 当一个信号连接多个槽时，会以不确定的顺序调用这些槽。
* 多个信号可以连接同一个槽
* 一个信号可以连接另外一个信号，一个信号发射时，另一个也同时发射。
* 连接可断开，`disconnect(sender,SIGNAL(signal),receiver,SLOT(slot));`
* 连接会断开，当删除对象时，Qt会移除和这个对象相关的所有连接。
* 多余参数会被忽略，当信号的参数比它所连接的槽的参数多，多余的参数会被忽略。
* 不能在信号和槽的名字中包含参数名。
* 可以有循环链接，但是要避免无限循环。

## MainWindow

若要调用并显示一个界(MainWindow)，需要在main.cpp中添加如下代码。

```c++
MainWindow w;
w.show();
```

## Dialog

若要调用并显示一个对话框(Dialog)

* 方案一

新建一个Dialog文件集合，然后在main.cpp中添加

```C++
#include<QApplication>
#include<QDialog>
#include"ui_XXXXX.h"
int main(int argc,char *argv[]){
  QApplication app(argc,argv);
  
  Ui::XXXXX ui;
  QDialog *myDialog = new QDialog;
  ui.setupUi(myDialog);
  myDialog->show();
  
  return app.exec()
}
```

* 方案二

新建一个Dialog文件集合，在main.cpp中添加

```c++
#include<QApplication>
#include"XXXXX.h"
int main(int argc,char *argv[]){
  QApplication app(argc,argv);
  
  XXXXX *myDialog = new XXXXX;
  myDialog->show();
  
  return app.exec()
}
```

对于界面的代码写在XXXXX.cpp的初始化函数中（信号，槽，连接，检验器）。

## UI

若要采用UI快速设计模式，流程如下：

1. 在Qt Designer模式中设计GUI界面，在设计完成后保存设计。
2. 在XXXXX.cpp中使用`ui->XXX`来使用GUI设计中构造的实例。

文件用途说明：

​	XXXXX.h文件主要用于窗口中对象的信号与槽的声明，包含其他内容的声明。

​	XXXXX.cpp文件主要用于编写包含逻辑性的代码，包含信号与槽的连接。

​	XXXXX.ui文件主要保存UI界面的XML信息。

​	ui_XXXXX.h文件主要是UI设计后生成的文件，资源管理器中不可见。