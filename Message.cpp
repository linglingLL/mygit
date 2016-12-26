#include "stdafx.h"
#include "Message.h"


Folder::~Folder()
{

}

void Folder::addMsg(Message *m)
{
	Msgs.insert(m);
}

void Folder::remMsg(Message *m)
{
	Msgs.erase(m);
}



Message::Message(const Message &m):
	contents(m.contents),folders(m.folders)
{
	add_to_Folders(m);
}

Message& Message::operator=(const Message &rhs)
{
	//通过先删除指针再插入它们来处理自赋值情况
	remove_from_Folders();    //更新已有Folder
	contents = rhs.contents;  //从rhs中拷贝消息内容
	folders  = rhs.folders;   //从rhs中拷贝消息Folders指针
	add_to_Folders(rhs);      //将本Message添加到那些Folders指针中
	return *this;
}

Message::~Message(void)
{
	remove_from_Folders();
}

void Message::save(Folder &f)
{
	folders.insert(&f);    //将给定Folder添加到本Message的Folder列表中
	f.addMsg(this);        //将本Message添加到f的Message集合中
}

void Message::remove(Folder &f)
{
	folders.erase(&f);    //将给定Folder从本Message的Folder列表中删除
	f.remMsg(this);       //将本Message从f的Message集合中删除
}

void Message::addFolder(Folder *f)
{
	folders.insert(f);
}

void Message::remFolder(Folder *f)
{
	folders.erase(f);
}

void Message::add_to_Folders(const Message& m)
{
	for (auto f : m.folders)    //对每个包含m的Folder
		f->addMsg(this);        //向该Folder添加一个指向本Message的指针
}

void Message::remove_from_Folders()
{
	for (auto f : folders)    //对Folders中的每个指针
		f->remMsg(this);      //从该Folder中删除本Message的指针
}

void swap(Message &lhs,Message &rhs)
{
	using std::swap;    //在本例中严格来说不需要，但这是一个好习惯
	
	//将每个消息的指针从它(原来)所在Folder中删除
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	
	//交换contents和Folder指针set
	swap(lhs.folders,rhs.folders);
	swap(lhs.contents,rhs.contents);
	
	//将每个Message的指针添加到它的Folder中
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}