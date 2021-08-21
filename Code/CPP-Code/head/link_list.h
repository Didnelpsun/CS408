#include <cstdio>
#include <cstdlib>
#include "head.h"

// 单链表结点
class LinkListNode {
private:
	// 数据
	element_type _data{};
	// 指针
	LinkListNode* _next{};
public:
	// 设置数据
	bool SetData(element_type data);
	// 获取数据
	element_type GetData() const;
	// 设置next
	bool SetNext(LinkListNode* next);
	// 获取next
	LinkListNode* GetNext();
	// 构造函数
	LinkListNode();
	explicit LinkListNode(element_type data);
	LinkListNode(element_type data, LinkListNode* next);
};

class LinkList {
private:
	// 指针
	LinkListNode* _next{};
	// 链表长度
	int _length{};
	// 类型，真有头节点，假无头节点
	bool _type{};
protected:
	// 设置链表类型
	bool SetType(bool type);
public:
	// 设置next
	bool SetNext(LinkListNode* next);
	// 获取next
	LinkListNode* GetNext();
	// 长度自加1
	bool SetLength();
	// 设置长度
	bool SetLength(int length);
	// 获取长度
	int GetLength() const;
	// 获取链表类型
	bool GetType() const;
	// 构造函数
	LinkList();
	// 打印
	virtual bool Print() = 0;
	// 判空
	bool Empty() const;
	// 插入
	virtual bool Insert(int index, element_type data) = 0;
	// 前插入
	bool PriorInsert(element_type* elem, int start, int length);
	// 后插入
	bool NextInsert(element_type* elem, int start, int length);
};

class LinkListWithHead : public LinkList {
public:
	// 构造函数
	LinkListWithHead();
	// 打印
	bool Print() override;
	// 插入
	bool Insert(int index, element_type data) override;
};

class LinkListWithoutHead : public LinkList {
private:
	// 数据
	element_type _data{};
public:
	// 设置数据
	bool SetData(element_type data);
	// 获取数据
	element_type GetData() const;
	// 构造函数
	LinkListWithoutHead();
	// 打印
	bool Print() override;
	// 插入
	bool Insert(int index, element_type data) override;
};

bool LinkListNode::SetData(element_type data) {
	this->_data = data;
	return true;
}

element_type LinkListNode::GetData() const {
	return this->_data;
}

bool LinkListNode::SetNext(LinkListNode* next) {
	this->_next = next;
	return true;
}

LinkListNode* LinkListNode::GetNext() {
	return this->_next;
}

LinkListNode::LinkListNode() {
	this->SetData(NULL);
	this->SetNext(nullptr);
}

LinkListNode::LinkListNode(element_type data) {
	this->SetData(data);
	this->SetNext(nullptr);
}

LinkListNode::LinkListNode(element_type data, LinkListNode* next) {
	this->SetData(data);
	this->SetNext(next);
}

bool LinkList::SetNext(LinkListNode* next) {
	this->_next = next;
	return true;
}

LinkListNode* LinkList::GetNext() {
	return this->_next;
}

bool LinkList::SetLength() {
	this->_length++;
	return true;
}

bool LinkList::SetLength(int length) {
	this->_length = length;
	return true;
}

int LinkList::GetLength() const {
	return this->_length;
}

bool LinkList::SetType(bool type) {
	this->_type = type;
	return true;
}

bool LinkList::GetType() const {
	return this->_type;
}

LinkList::LinkList() {
	this->SetNext(nullptr);
	this->SetLength(0);
}

LinkListWithHead::LinkListWithHead() {
	this->SetType(true);
};

bool LinkListWithoutHead::SetData(element_type data) {
	this->_data = data;
	return true;
}

element_type LinkListWithoutHead::GetData() const {
	return this->_data;
}

LinkListWithoutHead::LinkListWithoutHead() {
	this->SetType(false);
	this->SetData(NULL);
}

bool LinkList::Empty() const {
	if (this->GetLength() == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool LinkListWithHead::Print() {
	int i = 1;
	if (this->GetLength() == 0) {
		return true;
	}
	cout << "第0个元素值为空" << endl;
	// 当前遍历指针
	LinkListNode* p = this->GetNext();
	while (p != nullptr) {
		cout << "第" << i << "个元素值为" << p->GetData() << endl;
		i++;
		p = p->GetNext();
	}
	return true;
}

bool LinkListWithoutHead::Print() {
	int i = 0;
	if (this->GetLength() == 0) {
		return true;
	}
	cout << "第" << i << "个元素值为" << this->GetData() << endl;
	// 当前遍历指针
	LinkListNode* p = this->GetNext();
	while (p != nullptr) {
		i++;
		cout << "第" << i << "个元素值为" << p->GetData() << endl;
		p = p->GetNext();
	}
	return true;
}

bool LinkListWithHead::Insert(int index, element_type data) {
	if (index < 1) {
		cout << "Insert:插入索引值过小！" << endl;
		return false;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkListNode* p;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 1;
	// 将链表头结点的next指向p，为第1个结点
	p = this->GetNext();
	LinkListNode* s = new LinkListNode(data);
	// 如果该链表为空链表
	if (p == nullptr) {
		this->SetLength();
		this->SetNext(s);
		return true;
	}
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (p->GetNext() != nullptr && i < index - 1) {
		p = p->GetNext();
		i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index - 1) {
		cout << "Insert:插入索引值过大！" << endl;
		return false;
	}
	// 此时i==index-1
	// 将p原来的后继给新的结点
	s->SetNext(p->GetNext());
	p->SetNext(s);
    this->SetLength();
	return true;
}

bool LinkListWithoutHead::Insert(int index, element_type data) {
	if (index < 0) {
		cout << "Insert:插入索引值过小！" << endl;
		return false;
	}
	if (index == 0) {
		LinkListNode* node = new LinkListNode(this->GetData());
		this->SetData(data);
		this->SetLength();
		return true;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkListNode* p;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 1;
	// 将链表头结点的next指向p，为第1个结点
	p = this->GetNext();
	LinkListNode* s = new LinkListNode(data);
	// 如果该链表为空链表
	if (p == nullptr) {
		this->SetLength();
		this->SetNext(s);
		return true;
	}
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (p->GetNext() != nullptr && i < index - 1) {
		p = p->GetNext();
		i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index - 1) {
		cout << "Insert:插入索引值过大！" << endl;
		return false;
	}
	// 此时i==index-1
	// 将p原来的后继给新的结点
	s->SetNext(p->GetNext());
	p->SetNext(s);
	this->SetLength();
	return true;
}

bool LinkList::PriorInsert(element_type* elem, int start, int length) {
	if (this->GetType()) {
		for (int i = 0; i < length; i++) {
			bool result = this->Insert(1, elem[i + start]);
			if (!result) {
				cout << "PriorInsert:循环插入失败！" << endl;
				return false;
			}
		}
		return true;
	}
	else {
		for (int i = 0; i < length; i++) {
			bool result = this->Insert(0, elem[i + start]);
			if (!result) {
				cout << "PriorInsert:循环插入失败！" << endl;
				return false;
			}
		}
		return true;
	}
}

bool LinkList::NextInsert(element_type* elem, int start, int length) {
	if (this->GetType()) {
		for (int i = 0; i < length; i++) {
			bool result = this->Insert(i + 1, elem[i + start]);
			if (!result) {
				cout << "NextInsert:循环插入失败！" << endl;
				return false;
			}
		}
		return true;
	}
	else {
		for (int i = 0; i < length; i++) {
			bool result = this->Insert(i, elem[i + start]);
			if (!result) {
				cout << "NextInsert:循环插入失败！" << endl;
				return false;
			}
		}
		return true;
	}
}