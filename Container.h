#pragma once

template <class T>
class ContainerElement{
public:
	ContainerElement(T const& _value) :value(_value), next(NULL){
	}
	T value;
	ContainerElement<T>* next;
};



template <class T>
class Container {
public:
	Container() {
		first = NULL;
	}

	Container(Container const &copy) {
		this->first = NULL;
		if (copy.first != NULL) {
			this->first = new ContainerElement<T>(copy.first->value);
			ContainerElement<T> *p = copy.first->next;
			ContainerElement<T> *j = first;
			while (p != NULL)
			{
				j->next = new ContainerElement<T>(p->value);
				p = p->next;
				j = j->next;
			}
		} else {
			return;
		}
	}
	void clear()
	{
		ContainerElement<T>* p;
		while (first != NULL)
		{
			p = first->next;
			delete first;
			first = p;
		}
	};


	bool isEmpty() {
		return (first==NULL) ? true : false;
	};


	void addFirst(T const &first) {
		ContainerElement<T>* ce = new ContainerElement(first);
		ce->next = first;
		first = ce;
	};

	void addLast(T const &last) {
		ContainerElement<T>*p = first;
		if (p != NULL) {
			while (p->next != NULL)
				p = p->next;
			ContainerElement<T>* ce = new ContainerElement<T>(last);
			p->next = ce;
		}
		else {
			first = new ContainerElement<T>(last);
		}
	};

	void removeFirst() {
		if (first == NULL) {
			throw("Empty");
		}
		ContainerElement<T>* ce = first;
		first = first->next;
		delete ce;
	}

	void removeLast()
	{
		if (first == NULL) {
			throw("Empty!");
		}
		if (first->next != NULL) {
			ContainerElement<T>*p = first->next;
			while (p->next != NULL)
				p = p->next;
			delete p;
			p = NULL;
		}
		else {
			delete first;
			first = NULL;
		}
	}

	T getFirst() {
		if (first == NULL) {
			throw("Empty!");
		}
		return first->value;
	};

	T getLast() {
		if (first == NULL) {
			throw("Empty!");
		}
		ContainerElement<T>*p = first;
		while (p->next != NULL)
			p = p->next;
		return p->value;
	};

	int getAmount() {
		int k = 0;
		if (first == NULL) return 0;
		ContainerElement<T>*p = first;
		while (p->next != NULL) {
			p = p->next;
			k++;
		}
		return k;
	};


	class Iterator {
	public:
		ContainerElement<T>* k;
		Iterator &next() {
			this->k = this->k->next;
			return *this;
		}
		Iterator getNext() {
			Iterator j;
			j.k = this->k->next;
			return j;
		}
		bool operator!=(Iterator t) {
			if (t.k == this->k)
				return false;
			return true;
		}
		bool operator==(Iterator t) {
			if (t.k != this->k)
				return false;
			return true;
		}
		Iterator() {
			this->k = NULL;
		}
	};
	friend Iterator;

	Iterator& start() {
		Iterator *i = new Iterator();
		i->k = first;
		return *i;
	}

	Iterator& end() {
		Iterator *i = new Iterator();
		i->k = NULL;
		return *i;
	}

	~Container() {
		ContainerElement<T>* p;
		while (first != NULL) {
			p = first->next;
			delete first;
			first = p;
		}
	}

	T& operator[](Iterator& i) {
		return i.k->value;
	}

private:
	ContainerElement<T>* first;
};