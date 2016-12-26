#pragma once

class Message;
class Folder
{
	friend class Message;
public:
	explicit Folder(){}
	~Folder();

	//���Message����Folder��
	void addMsg(Message*);
	//ɾ��Message�ӱ�Folder��
	void remMsg(Message*);

private:
	std::set<Message*> Msgs;    //��Folder�а�����Message

};


class Message
{
	friend class Folder;
	friend void swap(Message &lhs,Message &rhs);
public:
   //folder����ʽ��ʼ��Ϊ�ռ���
	explicit Message(const std::string &str=""):
	        contents(str){}
	//�������Ƴ�Ա����������ָ��Message��ָ��
	Message(const Message&);              //�������캯��
	Message& operator=(const Message&);   //������ֵ�����
	~Message();                           //��������

	//�Ӹ�����Folder�����Ӻ�ɾ����Message
	void save(Folder&);
	void remove(Folder&);
	//�ӱ�Message��Folders�����Ӻ�ɾ��������Folder*
	void addFolder(Folder*);
	void remFolder(Folder*);
private:
	std::string  contents;      //ʵ�ʵ���Ϣ����
	std::set<Folder*> folders;  //������Message��Folder

	//�������캯����������ֵ�����������������ʹ�õĹ�������
	//����Message��ӵ�ָ�������Folder��
	void add_to_Folders(const Message&);
	//��Folders�е�ÿһ��Folder��ɾ����Message
	void remove_from_Folders();

};

