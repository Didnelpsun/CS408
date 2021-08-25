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
	// 销毁
	bool Destory();
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
	// 删除
    element_type Delete(int index);
	virtual element_type* Delete(int index, int length) = 0;
};

class LinkListWithHead : public LinkList {
public:
	// 构造函数
	LinkListWithHead();
	// 打印
	bool Print() override;
	// 插入
	bool Insert(int index, element_type data) override;
	// 删除
    element_type * Delete(int index, int length) override;
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
	// 删除
    element_type * Delete(int index, int length) override;
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

bool LinkListNode::Destory() {
    // 循环删除next指向链表后续结点
    while(this->GetNext()!= nullptr){
        LinkListNode* node = this->GetNext();
        this->SetNext(node->GetNext());
        node->SetData(NULL);
        node->SetNext(nullptr);
    }
    this->SetData(NULL);
	this->SetNext(nullptr);
    return true;
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
	cout << "第0个元素值为空" << endl;
	if (this->GetLength() == 0) {
		return true;
	}
	// 当前遍历指针
	LinkListNode* node = this->GetNext();
	while (node != nullptr) {
		cout << "第" << i << "个元素值为" << node->GetData() << endl;
		i++;
		node = node->GetNext();
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
	LinkListNode* node = this->GetNext();
	while (node != nullptr) {
		i++;
		cout << "第" << i << "个元素值为" << node->GetData() << endl;
		node = node->GetNext();
	}
	return true;
}

bool LinkListWithHead::Insert(int index, element_type data) {
	if (index < 1) {
		cout << "Insert:插入索引值" << index << "过小！" << endl;
		return false;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkListNode* node;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 1;
	// 将链表头结点的next指向node，为第1个结点
	node = this->GetNext();
	// 设置一个新结点进行插入
	auto* new_node = new LinkListNode(data);
	// 如果该链表为空链表
	if (node == nullptr) {
		this->SetNext(new_node);
		this->SetLength();
		return true;
	}
	// 当插入的是第一个节点
	if (index == 1) {
		new_node->SetNext(node);
		this->SetNext(new_node);
		this->SetLength();
		return true;
	}
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (node->GetNext() != nullptr && i < index - 1) {
		node = node->GetNext();
		i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index - 1) {
		cout << "Insert:插入索引值" << index << "过大！" << endl;
		return false;
	}
	// 此时i==index-1
	// 将node原来的后继给新的结点
	new_node->SetNext(node->GetNext());
	node->SetNext(new_node);
    this->SetLength();
	return true;
}

bool LinkListWithoutHead::Insert(int index, element_type data) {
	if (index < 0) {
		cout << "Insert:插入索引值" << index << "过小！" << endl;
		return false;
	}
	if (index == 0) {
		if (this->GetLength() == 0) {
			this->SetData(data);
			this->SetLength();
		}
		else {
			auto* node = new LinkListNode(this->GetData());
			node->SetNext(this->GetNext());
			this->SetData(data);
			this->SetNext(node);
			this->SetLength();
		}
		return true;
	}
	// 定义一个结点指针node指向当前扫描到的结点
	LinkListNode* node;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 1;
	// 将链表头结点的next指向p，为第1个结点
	node = this->GetNext();
	// 设置一个新结点进行插入
	auto* new_node = new LinkListNode(data);
	// 如果该链表为空链表
	if (node == nullptr) {
		this->SetLength();
		this->SetNext(new_node);
		return true;
	}
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (node->GetNext() != nullptr && i < index - 1) {
		node = node->GetNext();
		i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index - 1) {
		cout << "Insert:插入索引值" << index << "过大！" << endl;
		return false;
	}
	// 此时i==index-1
	// 将p原来的后继给新的结点
	new_node->SetNext(node->GetNext());
	node->SetNext(new_node);
	this->SetLength();
	return true;
}

bool LinkList::PriorInsert(element_type* elem, int start, int length) {
	if (this->GetType()) {
		for (int i = 0; i < length; i++) {
			bool result = this->Insert(1, elem[i + start]);
			if (!result) {
				cout << "PriorInsert:循环插入失败！索引值为" << i + start << endl;
				return false;
			}
		}
		return true;
	}
	else {
		for (int i = 0; i < length; i++) {
			bool result = this->Insert(0, elem[i + start]);
			if (!result) {
				cout << "PriorInsert:循环插入失败！索引值为" << i + start << endl;
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
				cout << "NextInsert:循环插入失败！索引值为" << i + start << endl;
				return false;
			}
		}
		return true;
	}
	else {
		for (int i = 0; i < length; i++) {
			bool result = this->Insert(i, elem[i + start]);
			if (!result) {
				cout << "NextInsert:循环插入失败！索引值为" << i + start << endl;
				return false;
			}
		}
		return true;
	}
}

element_type LinkList::Delete(int index) {
	return *(this->Delete(index, 1));
}

element_type* LinkListWithHead::Delete(int index, int length) {
	auto* data = (element_type*)malloc(length * sizeof(element_type));
	if (index < 1) {
	    cout << "Delete:删除索引值" << index << "过小！" << endl;
	    return data;
	}
	if (length < 1) {
		cout << "Delete:删除长度" << length << "过小！" << endl;
		return data;
	}
	// 定义一个结点指针start指向当前扫描到的结点，即要删除第一的元素的前一个
	LinkListNode* start;
	// 定义一个结点指针start指向当前扫描到的结点，要删除最后的元素
	LinkListNode* end;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 1;
	// 将链表头结点的next指向start，为第1个结点
	start = this->GetNext();
	// 如果链表没有任何数据
	if(start == nullptr) {
	    cout << "Delete:链表为空！" << endl;
	    return data;
	}
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (start->GetNext() != nullptr && i < index - 1) {
	    start = start->GetNext();
	    i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index - 1) {
	    cout << "Delete:删除索引值" << index << "过大！" << endl;
	    return false;
	}
	// 此时i==index-1，start到达，求end
	end = start;
	for (int i = 0; i < length; i++) {
		data[i] = end->GetData();
		end = end->GetNext();
		if (end == nullptr) {
			cout << "Delete:删除索引最大值" << index + length - 1 << "大于链表最大索引" << length << endl;
			return data;
		}
	}
	if (index == 1) {
		this->SetNext(end);
	}
	else {
		start->SetNext(end->GetNext());
	}
	this->SetLength(this->GetLength() - length);
	return data;
}

element_type* LinkListWithoutHead::Delete(int index, int length) {
	auto* data = (element_type*)malloc(length * sizeof(element_type));
	if (index < 0) {
		cout << "Delete:删除索引值" << index << "过小！" << endl;
		return data;
	}
	if (length < 1) {
		cout << "Delete:删除长度" << length << "过小！" << endl;
	}
	// 定义一个结点指针start指向当前扫描到的结点，即要删除第一的元素的前一个
	LinkListNode* start;
	// 定义一个结点指针start指向当前扫描到的结点，要删除最后的元素
	LinkListNode* end;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 1;
	// 将链表头结点的next指向start，为第1个结点
	start = this->GetNext();
	// 如果链表没有任何数据
	if (this->GetData() == NULL) {
		cout << "Delete:链表为空！" << endl;
		return data;
	}
	data[0] = this->GetData();
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (start->GetNext() != nullptr && i < index - 1) {
		start = start->GetNext();
		i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index - 1) {
		cout << "Delete:删除索引值" << index << "过大！" << endl;
		return data;
	}
	// 从1开始遍历
	end = this->GetNext();
	for (int i = 1; i < index + length - 1; i++) {
		if (i > index) {
			data[i - index] = end->GetData();
		}
		end = end->GetNext();
		if (end == nullptr) {
			cout << "Delete:删除索引最大值" << index + length - 1 << "大于链表最大索引" << length << endl;
			return data;
		}
	}
	if (index == 0) {
		this->SetData(end->GetNext()->GetData());
		this->SetNext(end->GetNext()->GetNext());
	}
	if (index == 1) {
		this->SetNext(end->GetNext());
	}
	else {
		start->SetNext(end->GetNext());
	}
	this->SetLength(this->GetLength() - length);
	return data;
}