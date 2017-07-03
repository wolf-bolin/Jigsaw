# Qt学习笔记

## Hello World

```C++
#include <qapplication.h>
#include <qpushbutton.h>
int main( int argc, char **argv ){
    QApplication a( argc, argv );
    
  	QPushButton hello( "Hello world!", 0 );
    hello.resize( 100, 30 );
    //a.setMainWidget( &hello );
    hello.show();
    
  	return a.exec();
}
```

* Qt4中不必加入```a.setMainWidget( &hello );```
* QApplication：应用程序对象。每一个使用Qt的应用程序中都必须使用一个QApplication对象,用来管理整个应用程序所用到的资源。
  * 构造参数：argv，argc
    * 成员函数.exec()， 将应用程序的控制权转递给Qt，程序进入事件循环状态，（进入事件响应模式）。21111111111111111111111111·11111111111111111111111111111111111·1
* QPushButton：按钮对象。参数列表（“按钮文字”,父窗口）
  * 成员函数.resize(宽px，高px)，设定宽高
  * 成员函数.show()，显示控件

## 字体，连接，退出

```C++
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
int main( int argc, char **argv ){
    QApplication a( argc, argv );

    QPushButton quit( "Quit", 0 );
    quit.resize( 75, 30 );
    quit.setFont( QFont( "Times", 18, QFont::Bold ) );

    QObject::connect( &quit, SIGNAL(clicked()), &a, SLOT(quit()) );

    //a.setMainWidget( &quit );
    quit.show();
    return a.exec();
}
```

* QFront：字体对象。参数列表（“字体”，字号，加粗）。
* QObject::connect：connect()是QObject中的一个静态函数。将某个对象的信号与另一个对象的槽连接起来，当信号被发出时，槽（函数）会被调用，详见“信号/槽”

## 信号、槽

```C++
class Foo : public QObject{
	Q_OBJECT
public:
	Foo();
	int value() const { 
		return val; 
	}
public slots:
    void setValue( int );
signals:
	void valueChanged( int );
private:
	int val;
};
void Foo::setValue( int v ){
	if ( v != val ) {
		val = v;
		emit valueChanged(v);
	}
}
int main(){
	//...
  	Foo a, b;
    connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));
    b.setValue( 11 ); // a == undefined  b == 11
    a.setValue( 79 ); // a == 79         b == 79
    b.value();
  	//...
}
```

* 调用`a.setValue(79)`会使`a`发射一个`valueChanged()` 信号，`b`将会在它的`setValue()`槽中接收这个信号，也就是`b.setValue(79)` 被调用。接下来`b`会发射同样的`valueChanged()`信号，但是因为 没有槽被连接到`b`的`valueChanged()`信号，所以没有发生任何事 ，信号消失了。

* 注意只有当`v != val`的时候`setValue()`函数才会设置这个值 并且发射信号。这样就避免了在循环连接的情况下出现无休止的循环的情况。

* 如果几个槽被连接到一个信号，当信号被发射时，这些槽就会被按任意顺序一个 接一个地执行。

* 一个`public slots:`区包含了任何信号都可以相连的槽。这对于组件编 程来说非常有用：你生成了许多对象，它们互相并不知道，把它们的信号和槽连接起 来，这样信息就可以正确地传递，并且就像一个铁路模型，把它打开然后让它跑起来。

  一个`protected slots:`区包含了之后这个类和它的子类的信号才能连接 的槽。这就是说这些槽只是类的实现的一部分，而不是它和外界的接口。

  一个`private slots:`区包含了之后这个类本身的信号可以连接的槽。这 就是说它和这个类是非常紧密的，甚至它的子类都没有获得连接权利这样的信任。

## 按钮，

* QPushButton：按钮类型。参数：用tr()包含的字符串作为按钮上的字。
  * 构造：`myButton = new QPushButton(tr(""));`
  * 默认：`myButton->setDefault(true);`
  * 可用性：`myButton->setEnable(true);`
* QLabel：文本标签。