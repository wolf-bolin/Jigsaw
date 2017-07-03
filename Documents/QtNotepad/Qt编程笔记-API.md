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

| 描述   | 代码                                    | 备注         |
| ---- | ------------------------------------- | ---------- |
| 构造   | `myButton = new QPushButton(tr(""));` | 参数为需要显示的文字 |
| 默认   | `myButton->setDefault(true);`         | 当前对话框的默认按钮 |
| 可用性  | `myButton->setEnable(true);`          | 按钮是否可用     |

## QLabel

文本对象。参数：一个字符串作为显示内容。

| 描述   | 代码                              | 备注                      |
| ---- | ------------------------------- | ----------------------- |
| 构造   | `myLabel = new QLabel(tr(""));` | 参数为需要显示的文字              |
| 伙伴   | `myLabel->setBuddy(...)`        | 参数为某实例，获得焦点后，焦点会转移到伙伴对象 |

## QLineEdit

输入框对象。

## QCheckBox

多选框对象。

| 描述   | 代码                                    | 备注         |
| ---- | ------------------------------------- | ---------- |
| 构造   | `myCheckBox = new QcheckBox(tr(""));` | 参数为需要显示的文字 |

## QVBoxLayout

