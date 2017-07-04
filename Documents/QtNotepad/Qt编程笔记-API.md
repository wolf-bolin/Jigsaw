# Qt编程笔记

——API参数列表

## QApplication

应用程序对象。必须使用一个QApplication对象来管理整个应用程序所用到的资源。

| 描述   | 代码                                  | 备注             |
| ---- | ----------------------------------- | -------------- |
| 构造   | `QApplication myApp( argc, argv );` | argc, argv不可缺少 |
| 关闭   | `myApp.quit()`                      | 关闭该应用程序的函数     |
| 结束   | `myApp.exec()`                      | 移交控制权给Qt       |



## QPushButton

按钮对象。

| 描述   | 代码                                       | 备注         |
| ---- | ---------------------------------------- | ---------- |
| 构造   | `QPushButton *myButton = new QPushButton(tr(""));` | 参数为需要显示的文字 |
| 默认   | `myButton->setDefault(true/false);`      | 当前对话框的默认按钮 |
| 可用性  | `myButton->setEnable(true/false);`       | 按钮是否可用     |
| 宽高   | `myButton.resize(x,y);`                  | 设定按钮的宽和高   |
| 加载   | `myButton.show()`                        | 加载并显示控件    |

## QLabel

文本对象。参数：一个字符串作为显示内容。

| 描述   | 代码                                      | 备注                      |
| ---- | --------------------------------------- | ----------------------- |
| 构造   | `QLabel *myLabel = new QLabel(tr(""));` | 参数为需要显示的文字              |
| 伙伴   | `myLabel->setBuddy(...)`                | 参数为某实例，获得焦点后，焦点会转移到伙伴对象 |

## QLineEdit

输入框对象。

## QCheckBox

多选框对象。

| 描述   | 代码                                       | 备注         |
| ---- | ---------------------------------------- | ---------- |
| 构造   | `QcheckBox *myCheckBox = new QcheckBox(tr(""));` | 参数为需要显示的文字 |
| 状态   | `myCheckBox->isChecked()`                | 选中为True    |
| 可用性  | `myCheckBox->setEnabled(true/false)`     |            |

## QGridLayout

格栅布局，多行多列，可调比例，自动调整父对象。

| 描述   | 代码                                       | 备注            |
| ---- | ---------------------------------------- | ------------- |
| 构造   | `QGridLayout *myGLayout = new QGridLayout();` | 初始化一个多行多列格栅布局 |
| 添加   | `myQLayout->addWidgent(...)`             | 将部件对象添加至布局    |
| 应用   | `setLayout(myGLayout)`                   | 将布局应用在当前窗口    |

## QHBoxLayout

垂直布局，被添加对象在垂直方向排列，排列顺序按照添加顺序排布，自动调整父对象。 

| 描述   | 代码                                       | 备注            |
| ---- | ---------------------------------------- | ------------- |
| 构造   | `QHBoxLaout *myQLayout = new QHBoxLaout` | 新建布局          |
| 添加   | `myQLayout->addWidgent(...)`             | 将部件对象添加至垂直布局  |
| 空白   | `myQLayout->addStretch(x)`               | 占位，参数可选，参数为比例 |

## QVBoxLayout

水平布局，被添加对象在水平方向排列，排列顺序按照添加顺序排布，自动调整父对象。

| 描述   | 代码                                       | 备注            |
| ---- | ---------------------------------------- | ------------- |
| 构造   | `QVBoxLayout *myVLayout = new QVBoxLayout` | 新建布局          |
| 添加   | `myVLayout->addWidgent(...)`             | 将部件对象添加至水平布局  |
| 空白   | `myQLayout->addStretch(x)`               | 占位，参数可选，参数为比例 |

## QObject::connect()

连接函数，将信号与槽之间连接在一起。

**connect(sender,SIGNAL(signal),receiver,SLOT(slot));**

| 描述       | 描述      |
| -------- | ------- |
| sender   | 发出信号的对象 |
| SIGNAL() | 发出信号的函数 |
| receive  | 含有槽的对象  |
| SLOT()   | 信号对应的槽  |

## QWidget::getTabOrder()

调整Tab按钮遍历顺序

