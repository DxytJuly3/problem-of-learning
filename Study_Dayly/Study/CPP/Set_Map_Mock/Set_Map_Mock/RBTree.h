#pragma once
#include <iostream>
#include <cassert>
using namespace std;

// ö�ٳ���, ��ʾ �� ��
enum Color {
    RED,
    BLACK
};


template<class T>
struct RBTreeNode {
    // RedBlackTreeNode ������ڵ�
    RBTreeNode(const T& data = T())
        : _pLeft(nullptr), _pRight(nullptr), _pParent(nullptr)
        , _data(data)
        , _color(RED) 	// �½ڵ�Ĭ��Ϊ��ڵ� 
    {}

    RBTreeNode<T>* _pLeft;			// �ڵ�����
    RBTreeNode<T>* _pRight;		    // �ڵ��Һ���
    RBTreeNode<T>* _pParent;		// �ڵ㸸�׽ڵ�

    T _data;					     // �ڵ�����
    Color _color;					// �ڵ���ɫ
};

template<class Key, class Value_type, class KeyOfValue>
class RB_Tree {
    typedef RBTreeNode<Value_type> Node;			// �Խڵ����ͽ���typedef

public:
    bool insert(const Value_type& data) {
        if (_root == nullptr) {
            // ��Ϊ��ʱ, �����½ڵ�
            _root = new Node(data);
            _root->_color = BLACK;			// ���ڵ�ҪΪ ��

            return true;
        }
        
        KeyOfValue KOV;
        // ����Ϊ��, �ʹӸ��ڵ㿪ʼ��λ��
        Node* cur = _root;
        Node* parent = cur->_pParent;
        while (cur) {
            if (KOV(data) > KOV(cur->_data)) {
                // �������ݴ�, ������������
                parent = cur;
                cur = cur->_pRight;
            }
            else if (KOV(data) < KOV(cur->_data)) {
                // ��������С, ������������
                parent = cur;
                cur = cur->_pLeft;
            }
            else {
                // �����Ѵ��ڲ�������, ���� false ����ʧ��
                return false;
            }
        }

        // ��ѭ��֮��, cur����λ�þ��� �½ڵ���Ҫ�����λ��
        cur = new Node(data);
        cur->_color = RED;
        // parent �� cur��������
        if (KOV(data) > KOV(parent->_data)) {
            // ���ݴ�, ���½ڵ��Ǹ��׽ڵ���ҽڵ�
            parent->_pRight = cur;
        }
        else {
            // ����С, ���½ڵ��Ǹ��׽ڵ����ڵ�
            parent->_pLeft = cur;
        }
        cur->_pParent = parent;

        // ��������½ڵ�ʱ �Ѿ���¼�� cur �� parent�ڵ�
        while (parent && parent->_color == RED) {
            // ���׽ڵ����, �Ҹ��׽ڵ�ҲΪ��ɫʱ
            Node* grandFa = parent->_pParent; 			// ��¼���Ƚڵ�
            assert(grandFa);						 // �����游�ڵ����
            // ����游�ڵ㲻����, ��˵�� parent�ڵ������ĸ�, �ǲ����ܵ� ��Ϊ��������������Ǻ�ɫ��

            if (parent == grandFa->_pLeft) {
                // ���׽ڵ������Ƚڵ������
                Node* uncle = grandFa->_pRight;			// ��¼����ڵ�
                if (uncle && uncle->_color == RED) {
                    // ����ڵ���� ���Ǻ�ڵ�
                    parent->_color = uncle->_color = BLACK;			// ���׽ڵ� �� ����ڵ��Ϊ��ɫ
                    grandFa->_color = RED;						 // �游�ڵ� ��Ϊ��ɫ

                    cur = grandFa;								// ���� grandFa�ڵ�Ϊ�µ�cur�ڵ�
                    parent = cur->_pParent;						  // ���� �µ�parent�ڵ�
                }
                else {
                    // uncleΪ�� �� Ϊ��ʱ
                    if (cur == parent->_pLeft) {
                        // parent��grandFa������, cur��parent������, �� ֱ�ߵ����
                        rotateR(grandFa);				// �� ���Ƚڵ���ΪrotateR��parent, �ҵ���

                        parent->_color = BLACK;			 // ���� parent�ڵ���ɫΪ��
                        grandFa->_color = RED;			 // ���� grandFa�ڵ���ɫΪ��
                    }
                    else {
                        // parent��grandFa������, cur��parent���Һ���, �� ���ߵ����
                        rotateL(parent);				// �Ƚ� parent�ڵ���ΪrotateL��parent, ����
                        rotateR(grandFa); 				// �ٽ� grandFa�ڵ���ΪrotateR��parent, �ҵ���

                        cur->_color = BLACK;			// ���� cur�ڵ���ɫΪ��
                        grandFa->_color = RED;			// ���� grandFa�ڵ���ɫΪ��
                    }
                    // ����֮�� ����ѭ��
                    break;
                }
            }
            else {
                // ���׽ڵ������Ƚڵ���Һ���
                Node* uncle = grandFa->_pLeft;			// ��¼����ڵ�
                if (uncle && uncle->_color == RED) {
                    parent->_color = uncle->_color = BLACK;
                    grandFa->_color = RED;

                    cur = grandFa;
                    parent = cur->_pParent;
                }
                else {
                    // uncleΪ�� �� Ϊ��ʱ
                    if (cur == parent->_pRight) {
                        // parent��grandFa���Һ���, cur��parent���Һ���, �� ֱ�ߵ����
                        rotateL(grandFa);				// �� ���Ƚڵ���ΪrotateL��parent, ����

                        parent->_color = BLACK;			 // ���� parent�ڵ���ɫΪ��
                        grandFa->_color = RED;			 // ���� grandFa�ڵ���ɫΪ��
                    }
                    else {
                        // parent��grandFa���Һ���, cur��parent������, �� ���ߵ����
                        rotateR(parent);				// �Ƚ� parent�ڵ���ΪrotateR��parent, �ҵ���
                        rotateL(grandFa); 				// �ٽ� grandFa�ڵ���ΪrotateL��parent, ����

                        cur->_color = BLACK;			// ���� cur�ڵ���ɫΪ��
                        grandFa->_color = RED;			// ���� grandFa�ڵ���ɫΪ��
                    }
                    // ����֮�� ����ѭ��
                    break;
                }
            }
        }
        _root->_color = BLACK;				  // ������� �����¸��ڵ����ɫΪ��

        return true;						// �������, ����true
    }

private:
    void rotateL(Node* parent) {
        Node* subR = parent->_pRight;
        Node* subRL = subR->_pLeft;

        parent->_pRight = subRL;
        if (subRL)
            subRL->_pParent = parent;

        Node* ppNode = parent->_pParent;

        subR->_pLeft = parent;
        parent->_pParent = subR;

        if (parent == _root) {
            _root = subR;
            _root->_pParent = nullptr;
        }
        else {
            if (parent == ppNode->_pLeft)
                ppNode->_pLeft = subR;
            else
                ppNode->_pRight = subR;

            subR->_pParent = ppNode;
        }
    }

    void rotateR(Node* parent) {
        Node* subL = parent->_pLeft;
        Node* subLR = subL->_pRight;

        parent->_pLeft = subLR;
        if (subLR)
            subLR->_pParent = parent;

        Node* ppNode = parent->_pParent;

        subL->_pRight = parent;
        parent->_pParent = subL;

        if (parent == _root) {
            _root = subL;
            _root->_pParent = nullptr;
        }
        else {
            if (parent == ppNode->_pLeft)
                ppNode->_pLeft = subL;
            else
                ppNode->_pRight = subL;

            subL->_pParent = ppNode;
        }
    }

    Node* _root = nullptr;
};
