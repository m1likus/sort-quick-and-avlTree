#pragma once

template <typename T>
class Node {
public:
	T key;
	Node* left;
	Node* right;
	Node* parent;
	int height;

	bool operator==(const Node<T>& other) {
		if (key == other.key) {
			return true;
		}
		return false;
	}
	bool operator!=(const Node<T>& other) {
		return !(*this == other);
	}
};

template <typename T>
class AvlTree {
protected:
	inline bool HasLeftChild(Node<T>* node) {
		if (node->left == 0) {
			return false;
		}
		return true;
	}
	inline bool HasRightChild(Node<T>* node) {
		if (node->right == 0) {
			return false;
		}
		return true;
	}
	inline bool HasParent(Node<T>* node) {
		if (node->parent == 0) {
			return false;
		}
		return true;
	}
	Node<T>* root;
public:
	template<typename T>
	class AvlTreeIterator {
	protected:
		T* iterator;
		Node<T>* itNode;
		AvlTree<T>* itTree;
	public:
		AvlTreeIterator(T& key, Node<T>& newNode, AvlTree<T>& tree) {
			iterator = &key;
			itNode = &newNode;
			itTree = &tree;
		}
		AvlTreeIterator(Node<T>& other, AvlTree<T>& otherTree) {
			iterator = &(other.key);
			itNode = &other;
			itTree = &otherTree;
		}
		T& operator*() const {
			return *iterator;
		}
		T* operator->() const {
			return iterator;
		}

		AvlTreeIterator<T>& operator++() {
			if (itNode->right != 0) { //если есть справа, то идем вправо...
				itNode = itNode->right;
				while (itNode->left != 0) {//если есть слева, то идем влево до конца
					itNode = itNode->left;
				}
				iterator = &(itNode->key);
			}
			else {
				Node<T>* saveNode(itNode);
				while (itNode->parent != 0 && itNode->parent->right == itNode) {
					itNode = itNode->parent; //если мы сейчас в правом сыне, то идем наверх, пока не станем левым сыном или пока не дойдем до корня
				}
				if (itNode->parent == 0) {//если мы в корне, то возвращаем +1 к последнему
					itNode = saveNode;
					iterator = &(itNode->key) + 1;
				}
				else if (itNode->parent->left == itNode) { //если мы в левом сыне, то просто переходим к родителю
					itNode = itNode->parent;
					iterator = &(itNode->key);
				}
			}
			return *this;
		}

		bool operator==(const AvlTreeIterator<T>& other) {
			return iterator == other.iterator;
		}
		bool operator!=(const AvlTreeIterator<T>& other) {
			return iterator != other.iterator;
		}
	};

private:
	//Доп. функции для балансировки
	void Recorrect(Node<T>* node) {
		int rightHeight = -1, leftHeight = -1;
		HasRightChild(node) ? rightHeight = node->right->height : rightHeight = -1;
		HasLeftChild(node) ? leftHeight = node->left->height : leftHeight = -1;
		node->height = MyMax(leftHeight, rightHeight) + 1;
	}
	int Difference(Node<T>* node) {
		int rightHeight = -1, leftHeight = -1;
		HasRightChild(node) ? rightHeight = node->right->height : rightHeight = -1;
		HasLeftChild(node) ? leftHeight = node->left->height : leftHeight = -1;
		return (leftHeight - rightHeight);
	}
	//Повороты
	void SmallRight(Node<T>* a) {
		Node<T>* b = a->left;
		if (HasParent(a)) {
			if (a->parent->right == a) {
				a->parent->right = b;
			}
			else {
				a->parent->left = b;
			}
		}
		else {
			root = b;
		}

		b->parent = a->parent;
		if (HasRightChild(b)) {
			b->right->parent = a;
		}
		a->left = b->right;
		b->right = a;
		a->parent = b;

		Recorrect(a);
		Recorrect(b);
	}
	void SmallLeft(Node<T>* a) {
		Node<T>* b = a->right;
		if (HasParent(a)) {
			if (a->parent->right == a) {
				a->parent->right = b;
			}
			else {
				a->parent->left = b;
			}
		}
		else {
			root = b;
		}
		b->parent = a->parent;
		if (HasLeftChild(b)) {
			b->left->parent = a;
		}
		a->right = b->left;
		b->left = a;
		a->parent = b;

		Recorrect(a);
		Recorrect(b);
	}
	void BigRight(Node<T>* a) {
		if (HasRightChild(a->left)) {
			SmallLeft(a->left);
		}
		else {
			return;
		}
		SmallRight(a);
	}
	void BigLeft(Node<T>* a) {
		if (HasLeftChild(a->right)) {
			SmallRight(a->right);
		}
		else {
			return;
		}
		SmallLeft(a);
	}
	//Функция балансировки
	void Rebalance(Node<T>* n) {
		Node<T>* c = n;
		Node<T>* b = 0;
		Node<T>* a = 0;
		int diffC = 0;
		int diffB = 0;
		int diffA = 0;
		Recorrect(c);

		while (HasParent(c)) {
			b = c->parent;
			Recorrect(b);
			diffC = Difference(c);
			diffB = Difference(b);
			if (diffC <= 0 && diffB == -2) {
				SmallLeft(b);
			}
			else if (diffC >= 0 && diffB == 2) {
				SmallRight(b);
			}
			c = b;
		}
		//если не сработали малые повороты, то надо пройтись большими поворотами
		c = n; diffC = 0; diffB = 0; diffA = 0; b = 0; a = 0;
		if (HasParent(c)) {
			b = c->parent;
		}
		while (HasParent(c) && HasParent(b)) {
			b = c->parent;
			if (!HasParent(b)) {
				break;
			}
			a = b->parent;
			Recorrect(b);
			Recorrect(a);
			diffC = Difference(c);
			diffB = Difference(b);
			diffA = Difference(a);
			if (/*diffC <= 1 &&*/ diffB == 1 && diffA == -2) {
				BigLeft(a);
			}
			else if (/*diffC <= 1 && */ diffB == -1 && diffA == 2) {
				BigRight(a);
			}
			c = b;
			b = a;
		}
		c = n;
		b = 0;
	}
	int MyMax(int a, int b) {
		return a >= b ? a : b;
	}

public:
	AvlTree() {
		root = 0;
	}
	AvlTree(const AvlTree<T>& other) {
		if (other.root == 0) {
			root = 0;
		}
		else {
			root = new Node<T>();
			root->parent = 0; 
			root->left = 0;
			root->right = 0;
			root->key = other.root->key;
			root->height = other.root->height;

			Node<T>* n1 = root; //где были в this
			Node<T>* n2 = root; //куда идем в this
			Node<T>* otherN1 = other.root; //где были в other
			Node<T>* otherN2 = other.root; //куда идем в other
			while (n2 != 0) { 
				n1 = n2;
				otherN1 = otherN2;
				if (HasLeftChild(otherN1) && !HasLeftChild(n1)) {
					//если левый потомок в other не пуст, а в this пуст, то
					otherN2 = otherN1->left; //приходим в левый потомок other
					n2 = new Node<T>(); //создаем новый узел
					n2->parent = n1;
					n2->left = 0;
					n2->right = 0;
					n2->key = otherN2->key;
					n2->height = otherN2->height;
					n1->left = n2;
				}
				else if (HasRightChild(otherN1) && !HasRightChild(n1)) {
					//если правый потомок other не пуст, а в this пуст, то
					otherN2 = otherN1->right; //переходим в правый потомок other
					n2 = new Node<T>(); //создаем новый узел
					n2->parent = n1;
					n2->left = 0;
					n2->right = 0;
					n2->key = otherN2->key;
					n2->height = otherN2->height;
					n1->right = n2;
				}
				else {
					//если и правый и левый пуст - переходим в родителя
					n2 = n1->parent;
					otherN2 = otherN1->parent;
				}
			}

		}
	}
	AvlTree& operator=(const AvlTree& other) { //оператор присваивания
		if (&other != this) {
			if (root == 0) {
				if (other.root == 0) {
					root = 0;
				}
				else { //начинаем создавать новое дерево
					root = new Node<T>(); //создаем корень
					root->parent = 0; //заполняем
					root->left = 0;
					root->right = 0;
					root->key = other.root->key;
					root->height = other.root->height;
					Node<T>* n1 = root; //были
					Node<T>* n2 = root; //стали
					Node<T>* otherN1 = other.root;
					Node<T>* otherN2 = other.root;
					while (n2 != 0) {
						n1 = n2;
						otherN1 = otherN2;
						if (HasLeftChild(otherN1) && !HasLeftChild(n1)) {
							otherN2 = otherN1->left;
							n2 = new Node<T>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->key = otherN2->key;
							n2->height = otherN2->height;
							n1->left = n2;
						}
						else if (HasRightChild(otherN1) && !HasRightChild(n1)) {
							otherN2 = otherN1->right;
							n2 = new Node<T>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->key = otherN2->key;
							n2->height = otherN2->height;
							n1->right = n2;
						}
						else {
							n2 = n1->parent;
							otherN2 = otherN1->parent;
						}
					}

				}
			}
			else { 
				if (other.root == 0) {
					Node<T>* n1 = root;
					Node<T>* n2 = root;
					while (n2 != 0) {
						n1 = n2;
						if (n1->left != 0) {
							n2 = n1->left;
							n1->left = 0;
						}
						else if (n2->right != 0) {
							n2 = n1->right;
							n1->right = 0;
						}
						else {
							n2 = n1->parent;
							delete n1;
						}
					}
					delete n1;
					delete n2;
					root = 0;
				}
				else { //если были оба не пустыми
					root->key = other.root->key;
					Node<T>* n1 = root;
					Node<T>* n2 = root;
					Node<T>* otherN1 = other.root;
					Node<T>* otherN2 = other.root;
					while (n2 != 0) {
						n1 = n2;
						otherN1 = otherN2;
						if (HasLeftChild(otherN1) && !HasLeftChild(n1)) {
							otherN2 = otherN1->left;
							n2 = new Node<T>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->key = otherN2->key;
							n2->height = otherN2->height;
							n1->left = n2;
						}
						else if (HasRightChild(otherN1) && !HasRightChild(n1)) {
							otherN2 = otherN1->right;
							n2 = new Node<T>();
							n2->parent = n1;
							n2->left = 0;
							n2->right = 0;
							n2->key = otherN2->key;
							n2->height = otherN2->height;
							n1->right = n2;
						}
						else if (!HasLeftChild(otherN1) && HasLeftChild(n1)) {
							Node<T>* newN1 = n1->left;
							Node<T>* newN2 = n1->left;
							while (newN2 != 0) {
								newN1 = newN2;
								if (newN1->left != 0) {
									newN2 = newN1->left;
									newN1->left = 0;
								}
								else if (newN2->right != 0) {
									newN2 = newN1->right;
									newN1->right = 0;
								}
								else {
									newN2 = newN1->parent;
									delete newN1;
								}
							}
							delete newN1;
							delete newN2;
							n1->left = 0;
						}
						else if (!HasRightChild(otherN1) && HasRightChild(n1)) {
							Node<T>* newN1 = n1->right;
							Node<T>* newN2 = n1->right;
							while (newN2 != NULL) {
								newN1 = newN2;
								if (newN1->left != 0) {
									newN2 = newN1->left;
									newN1->left = 0;
								}
								else if (newN2->right != 0) {
									newN2 = newN1->right;
									newN1->right = 0;
								}
								else {
									newN2 = newN1->parent;
									delete newN1;
								}
							}
							delete newN1;
							delete newN2;
							n1->right = 0;
						}
						else {
							n2 = n1->parent;
							otherN2 = otherN1->parent;
						}
					}
				}
			}
		}
		return *this;
	}
	~AvlTree() {
		if (root == 0) {
			delete root;
		}
		else {
			Node<T>* n1 = root; //где были в this
			Node<T>* n2 = root; //куда идем в this
			while (n2 != 0) { 
				n1 = n2;
				if (n1->left != 0) {
					n2 = n1->left;
					n1->left = 0;
				}
				else if (n2->right != 0) {
					n2 = n1->right;
					n1->right = 0;
				}
				else {
					n2 = n1->parent;
					delete n1;
				}
			}
		}
		root = 0;
	}

	int Size() {
		int count = 0;
		for (auto i = Begin(); i != End(); ++i) {
			count++;
		}
		return count;
	}
	void AvlTreeContent(T* array) {
		int count = 0;
		auto i = Begin();
		while (i != End()) {
			array[count] = (*i);
			count++;
			++i;
		}
	}
	void AvlTreeFilling(const T* array, const int n) {
		for (int i = 0; i < n; i++) {
			this->Insert(array[i]);
		}
	}

	//итератор на начало
	AvlTreeIterator<T> Begin() {
		if (root == 0) {
		  return AvlTreeIterator<T>(*root, *this);
		}
		else {
			Node<T>* n1 = root;
			while (n1->left != 0) {
				n1 = n1->left;
			}
			return AvlTreeIterator<T>(*(n1), *this);
		}
	}
	//итератор на конец
	AvlTreeIterator<T> End() {
		if (root == 0) {
			return AvlTreeIterator<T>(*root, *this);
		}
		Node<T>* n1 = root;
		while (n1->right != 0) {
			n1 = n1->right;
		}
		return ++AvlTreeIterator<T>(*n1, *this);
	}

	AvlTreeIterator<T> Insert(const T& key) {
		if (root == 0) {
			root = new Node<T>();
			root->parent = 0;
			root->left = 0;
			root->right = 0;
			root->key = key;
			root->height = 0;
			return AvlTreeIterator<T>(*root, *this);
		}
		else {
			Node<T>* n1 = root;
			Node<T>* n2 = 0;
			while (n1 != 0) {
				n2 = n1;
				n1->key < key ? n1 = n1->right : n1 = n1->left;
			}
			if (n1 == 0) {
				n1 = new Node<T>();
				n1->key = key;
				n1->left = 0;
				n1->right = 0;
				n1->parent = n2;
				n1->height = 0;
				if (n2->key < n1->key)
					n2->right = n1;
				else
					n2->left = n1;
				Rebalance(n1);
			}
			return AvlTreeIterator<T>(*n1, *this);
		}
	}

};

