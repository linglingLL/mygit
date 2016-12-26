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
	//ͨ����ɾ��ָ���ٲ��������������Ը�ֵ���
	remove_from_Folders();    //��������Folder
	contents = rhs.contents;  //��rhs�п�����Ϣ����
	folders  = rhs.folders;   //��rhs�п�����ϢFoldersָ��
	add_to_Folders(rhs);      //����Message��ӵ���ЩFoldersָ����
	return *this;
}

Message::~Message(void)
{
	remove_from_Folders();
}

void Message::save(Folder &f)
{
	folders.insert(&f);    //������Folder��ӵ���Message��Folder�б���
	f.addMsg(this);        //����Message��ӵ�f��Message������
}

void Message::remove(Folder &f)
{
	folders.erase(&f);    //������Folder�ӱ�Message��Folder�б���ɾ��
	f.remMsg(this);       //����Message��f��Message������ɾ��
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
	for (auto f : m.folders)    //��ÿ������m��Folder
		f->addMsg(this);        //���Folder���һ��ָ��Message��ָ��
}

void Message::remove_from_Folders()
{
	for (auto f : folders)    //��Folders�е�ÿ��ָ��
		f->remMsg(this);      //�Ӹ�Folder��ɾ����Message��ָ��
}

void swap(Message &lhs,Message &rhs)
{
	using std::swap;    //�ڱ������ϸ���˵����Ҫ��������һ����ϰ��
	
	//��ÿ����Ϣ��ָ�����(ԭ��)����Folder��ɾ��
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	
	//����contents��Folderָ��set
	swap(lhs.folders,rhs.folders);
	swap(lhs.contents,rhs.contents);
	
	//��ÿ��Message��ָ����ӵ�����Folder��
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}