#ifndef __CNODE_H__
#define __CNODE_H__

template <typename T>
class CNode {
private:
	T m_data;
	CNode<T>* m_next;
public:
	CNode(T data, CNode<T>* ptr);
	~CNode();
	T getData() const;
	CNode<T>* getNext() const;
	void setData(T data);
	void setNext(CNode<T>* next);
};

#include "CNode.hxx"

#endif /* __CNODE_H__ */