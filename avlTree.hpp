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
		if (key == other.key)
			return true;
		return false;
	}
	bool operator!=(const Node<T>& other) {
		return !(*this == other);
	}
};

template <typename T>
class avlTree {
protected:
	inline bool HasLeftChild(Node<T>* node) {
		if (node->left == 0) return false;
		return true;
	}
	inline bool HasRightChild(Node<T>* node) {
		if (node->right == 0) return false;
		return true;
	}
	inline bool HasParent(Node<T>* node) {
		if (node->parent == 0) return false;
		return true;
	}
	Node<T>* root;
public:
	template<typename T>
	class avlTreeIterator {
	protected:
		T* iterator;
		Node<T>* it_node;
		avlTree<T>* it_tree;
	public:
		avlTreeIterator(T& key, Node<T>& new_node, avlTree<T>& tree) {
			iterator = &key;
			it_node = &new_node;
			it_tree = &tree;
		}
		avlTreeIterator(Node<T>& other, avlTree<T>& other_tree) {
			iterator = &(other.key);
			it_node = &other;
			it_tree = &other_tree;
		}
		T& operator*() const {
			return (*iterator);
		}
		T* operator->() const {
			return iterator;
		}

		avlTreeIterator<T>& operator++() {
			if (it_node->right != 0) { //если есть справа, то идем вправо...
				it_node = it_node->right;
				while (it_node->left != 0) //если есть слева, то идем влево до конца
					it_node = it_node->left;
				iterator = &(it_node->key);
			}
			else {
				Node<T>* save_node(it_node);
				while (it_node->parent != 0 && it_node->parent->right == it_node)
					it_node = it_node->parent; //если мы сейчас в правом сыне, то идем наверх, пока не станем левым сыном или пока не дойдем до корня
				if (it_node->parent == 0) {//если мы в корне, то возвращаем +1 к последнему
					it_node = save_node;
					iterator = &(it_node->key) + 1;
				}
				else if (it_node->parent->left == it_node) { //если мы в левом сыне, то просто переходим к родителю
					it_node = it_node->parent;
					iterator = &(it_node->key);
				}
			}
			return *this;
		}

		bool operator==(const avlTreeIterator<T>& other) {
			return iterator == other.iterator;
		}
		bool operator!=(const avlTreeIterator<T>& other) {
			return iterator != other.iterator;
		}
	};

private:
	//Доп. функции для балансировки
	void recorrect(Node<T>* node) {
		int rightHeight = -1, leftHeight = -1;
		HasRightChild(node) ? rightHeight = node->right->height : rightHeight = -1;
		HasLeftChild(node) ? leftHeight = node->left->height : leftHeight = -1;
		node->height = my_max(leftHeight, rightHeight) + 1;
	}
	int difference(Node<T>* node) {
		int rightHeight = -1, leftHeight = -1;
		HasRightChild(node) ? rightHeight = node->right->height : rightHeight = -1;
		HasLeftChild(node) ? leftHeight = node->left->height : leftHeight = -1;
		return (leftHeight - rightHeight);
	}
	//Повороты
	void smallRight(Node<T>* a) {
		Node<T>* b = a->left;
		if (HasParent(a))
			if (a->parent->right == a) 
				a->parent->right = b;
			else a->parent->left = b;
		else root = b;

		b->parent = a->parent;
		if (HasRightChild(b)) 
			b->right->parent = a;
		a->left = b->right;
		b->right = a;
		a->parent = b;

		recorrect(a);
		recorrect(b);
	}
	void smallLeft(Node<T>* a) {
		Node<T>* b = a->right;
		if (HasParent(a))
			if (a->parent->right == a) 
				a->parent->right = b;
			else a->parent->left = b;
		else root = b;

		b->parent = a->parent;
		if (HasLeftChild(b)) 
			b->left->parent = a;
		a->right = b->left;
		b->left = a;
		a->parent = b;

		recorrect(a);
		recorrect(b);
	}
	void bigRight(Node<T>* a) {
		if (HasRightChild(a->left))
			smallLeft(a->left);
		else return;
		smallRight(a);
	}
	void bigLeft(Node<T>* a) {
		if (HasLeftChild(a->right))
			smallRight(a->right);
		else return;
		smallLeft(a);
	}
	//Функция балансировки
	void rebalance(Node<T>* n) {
		Node<T>* c = n;
		Node<T>* b = 0;
		Node<T>* a = 0;
		int diff_c = 0;
		int diff_b = 0;
		int diff_a = 0;
		recorrect(c);

		while (HasParent(c)) {
			b = c->parent;
			recorrect(b);
			diff_c = difference(c);
			diff_b = difference(b);
			if (diff_c <= 0 && diff_b == -2) {
				smallLeft(b);
			}
			else if (diff_c >= 0 && diff_b == 2) {
				smallRight(b);
			}
			c = b;
		}
		//если не сработали малые повороты, то надо пройтись большими поворотами
		c = n; diff_c = 0; diff_b = 0; diff_a = 0; b = 0; a = 0;
		if (HasParent(c)) b = c->parent;
		while (HasParent(c) && HasParent(b)) {
			b = c->parent;
			if (!HasParent(b)) break;
			a = b->parent;
			recorrect(b);
			recorrect(a);
			diff_c = difference(c);
			diff_b = difference(b);
			diff_a = difference(a);
			if (/*diff_c <= 1 &&*/ diff_b == 1 && diff_a == -2) {
				bigLeft(a);
			}
			else if (/*diff_c <= 1 && */ diff_b == -1 && diff_a == 2) {
				bigRight(a);
			}
			c = b;
			b = a;
		}
		c = n;
		b = 0;
	}
	int my_max(int a, int b) {
		return a >= b ? a : b;
	}

public:
	avlTree() {
		root = 0;
	}

	avlTree(const T* array, int size) {
		for (int i = 0; i < size; i++) {
			this->insert(array[i]);
		}
	}


	avlTree(const avlTree<T>& other) {
		if (other.root == 0)
			root = 0;
		else {
			root = new Node<T>();
			root->parent = 0; 
			root->left = 0;
			root->right = 0;
			root->key = other.root->key;
			root->height = other.root->height;

			Node* n1 = root; //где были в this
			Node* n2 = root; //куда идем в this
			Node* other_n1 = other.root; //где были в other
			Node* other_n2 = other.root; //куда идем в other
			while (n2 != 0) { 
				n1 = n2;
				other_n1 = other_n2;
				if (HasLeftChild(other_n1) && !HasLeftChild(n1)) {
					//если левый потомок в other не пуст, а в this пуст, то
					other_n2 = other_n1->left; //приходим в левый потомок other
					n2 = new Node<T>(); //создаем новый узел
					n2->parent = n1;
					n2->left = 0;
					n2->right = 0;
					n2->key = other_n2->key;
					n2->height = other_n2->height;
					n1->left = n2;
				}
				else if (HasRightChild(other_n1) && !HasRightChild(n1)) {
					//если правый потомок other не пуст, а в this пуст, то
					other_n2 = other_n1->right; //переходим в правый потомок other
					n2 = new Node<T>(); //создаем новый узел
					n2->parent = n1;
					n2->left = 0;
					n2->right = 0;
					n2->key = other_n2->key;
					n2->height = other_n2->height;
					n1->right = n2;
				}
				else {
					//если и правый и левый пуст - переходим в родителя
					n2 = n1->parent;
					other_n2 = other_n1->parent;
				}
			}

		}
	}

	~avlTree() {
		if (root == 0)
			delete root;
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

	int size() {
		int count = 0;
		for (auto i = begin(); i != end(); ++i) {
			count++;
		}
		return count;
	}
	T* avlTreeContent() {
		T* array = new T[size()];
		int count = 0;
		for (auto i = begin(); i != end(); ++i) {
			array[count] = (*i);
			count++;
		}
		return array;
	}

	//итератор на начало
	avlTreeIterator<T> begin() {
		if (root == 0) 
			return avlTreeIterator<T>(*root, *this);
		else {
			Node<T>* n1 = root;
			while (n1->left != 0) {
				n1 = n1->left;
			}
			return avlTreeIterator<T>(*(n1), *this);
		}
	}
	//итератор на конец
	avlTreeIterator<T> end() {
		if (root == 0) 
			return avlTreeIterator<T>(*root, *this);
		Node<T>* n1 = root;
		while (n1->right != 0) {
			n1 = n1->right;
		}
		return ++avlTreeIterator<T>(*n1, *this);
	}

	avlTreeIterator<T> insert(const T& key) {
		if (root == 0) {
			root = new Node<T>();
			root->parent = 0;
			root->left = 0;
			root->right = 0;
			root->key = key;
			root->height = 0;
			return avlTreeIterator<T>(*root, *this);
		}
		else {
			Node<T>* n1 = root;
			Node<T>* n2 = 0;
			while (n1 != 0 && n1->key != key) {
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
				rebalance(n1);
			}
			else if (n1->key == key) {
				n1->key = key;
			}
			return avlTreeIterator<T>(*n1, *this);
		}
	}
};

