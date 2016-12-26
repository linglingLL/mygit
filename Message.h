#pragma once

class Message;
class Folder
{
	friend class Message;
public:
	explicit Folder(){}
	~Folder();

	//添加Message到本Folder中
	void addMsg(Message*);
	//删除Message从本Folder中
	void remMsg(Message*);

private:
	std::set<Message*> Msgs;    //本Folder中包含的Message

};


class Message
{
	friend class Folder;
	friend void swap(Message &lhs,Message &rhs);
public:
   //folder被隐式初始化为空集合
	explicit Message(const std::string &str=""):
	        contents(str){}
	//拷贝控制成员，用来管理指向本Message的指针
	Message(const Message&);              //拷贝构造函数
	Message& operator=(const Message&);   //拷贝赋值运算符
	~Message();                           //析构函数

	//从给定的Folder中增加和删除本Message
	void save(Folder&);
	void remove(Folder&);
	//从本Message的Folders中增加和删除给定的Folder*
	void addFolder(Folder*);
	void remFolder(Folder*);
private:
	std::string  contents;      //实际的消息内容
	std::set<Folder*> folders;  //包含本Message的Folder

	//拷贝构造函数、拷贝赋值运算符和析构函数中使用的公共函数
	//将本Message添加到指向参数的Folder中
	void add_to_Folders(const Message&);
	//从Folders中的每一个Folder中删除本Message
	void remove_from_Folders();

};

