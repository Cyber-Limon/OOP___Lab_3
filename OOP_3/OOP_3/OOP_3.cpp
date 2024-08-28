#include <iostream>
#include <time.h> 



using namespace std;

class Object {

protected:

	int x;

public:

	Object() {
		x = 0;
		cout << "Object()\t" << this << endl;
	}

	Object(int x) {
		this->x = x;
		cout << "Object(int x)\t" << this << '\t' << x << endl;
	}

	virtual ~Object() {
		cout << "~Object()\t" << this << endl;
	}

	virtual void Print() {
		cout << "Object\t" << this << '\t' << x << endl;
	}
};

class Animal : public Object {

public:

	Animal() {
		x = 0;
		cout << "Animal()\t" << this << endl;
	}

	Animal(int x) {
		this->x = x;
		cout << "Animal(int x)\t" << this << '\t' << x << endl;
	}

	~Animal() {
		cout << "~Animal()\t" << this << endl;
	}

	void Print() override {
		cout << "Animal\t" << this << '\t' << x << endl;
	}
};

class Plant : public Object {

public:

	Plant() {
		x = 0;
		cout << "Plant()\t" << this << endl;
	}

	Plant(int x) {
		this->x = x;
		cout << "Plant(int x)\t" << this << '\t' << x << endl;
	}

	~Plant() {
		cout << "~Plant()\t" << this << endl;
	}

	void Print() override {
		cout << "Plant\t" << this << '\t' << x << endl;
	}
};



template <typename T> class Container {

private:

	int Size;
	T* arr;

public:

	Container(int Size) {
		cout << "Container()\t" << this << endl;

		this->Size = Size;
		this->arr = new T[Size];
	}

	~Container() {
		for (int i = 0; i < Size; i++) {
			delete this->arr[i];
		}

		cout << "~Container()\t" << this << endl;
	}
	
	T& operator[](const int index) {
		return arr[index];
	}

	int GetSize() {
		return Size;
	}

	void add(int index, const T& data) {
		this->arr[index] = data;
	}

	void push_front(const T& data) {
		cout << "push_front" << endl;

		Size++;
		T* arr = new T[Size];
		arr[0] = data;

		for (int i = 1; i < Size; i++) {
			arr[i] = this->arr[i - 1];
		}

		delete[] this->arr;
		this->arr = arr;
	}

	void push_middle(int index, const T& data) {
		cout << "push_middle -> " << index << endl;

		if (index >= Size) {
			return;
		}

		Size++;
		T* arr = new T[Size];
		arr[index] = data;

		for (int i = 0; i < index; i++) {
			arr[i] = this->arr[i];
		}

		for (int i = index + 1; i < Size; i++) {
			arr[i] = this->arr[i - 1];
		}

		delete[] this->arr;
		this->arr = arr;
	}

	void push_back(const T& data) {
		cout << "push_back" << endl;

		Size++;
		T* arr = new T[Size];
		arr[Size - 1] = data;

		for (int i = 0; i < Size - 1; i++) {
			arr[i] = this->arr[i];
		}

		delete[] this->arr;
		this->arr = arr;
	}

	void seizure_with_deletion(int index) {
		cout << "seizure_with_deletion -> " << index << endl;

		if (index >= Size) {
			return;
		}

		Size--;
		T* arr = new T[Size];
		delete this->arr[index];

		for (int i = 0; i < index; i++) {
			arr[i] = this->arr[i];
		}

		for (int i = index; i < Size; i++) {
			arr[i] = this->arr[i + 1];
		}

		delete[] this->arr;
		this->arr = arr;
	}

	T seizure_without_deletion(int index) {
		cout << "seizure_without_deletion -> " << index << endl;

		if (index >= Size) {
			return 0;
		}

		Size--;
		T* arr = new T[Size];
		T elm = this->arr[index];

		for (int i = 0; i < index; i++) {
			arr[i] = this->arr[i];
		}

		for (int i = index; i < Size; i++) {
			arr[i] = this->arr[i + 1];
		}

		delete[] this->arr;
		this->arr = arr;
		return elm;
	}
};

int main() {
	
	setlocale(LC_ALL, "russian");
	clock_t start = clock();

	{
		Container<Object*> cont(7);

		for (int i = 0; i < cont.GetSize(); i++) {
			cont.add(i, new Object(i + 1));
		}

		cout << endl;

		for (int i = 0; i < cont.GetSize(); i++) {
			cont[i]->Print();
		}

		for (int i = 0; i < 1000; i++) {

			cout << endl << "i = " << i << endl << endl;

			int r1 = rand() % 3, r2;

			if (cont.GetSize() > 0)
				r2 = rand() % cont.GetSize();

			else
				r2 = 0;

			if (r1 == 0) {
				int obj = rand() % 2;

				if(obj == 0) { cont.push_middle(r2, new Object(rand())); }
				else if (obj == 0) { cont.push_middle(r2, new Animal(rand())); }
				else { cont.push_middle(r2, new Plant(rand())); }
			}

			else if (r1 == 1) {
				cont.seizure_with_deletion(r2);
			}

			else {
				if (cont.GetSize() > 0)
					cont[r2]->Print();
			}
		}

		cout << endl;

		for (int i = 0; i < cont.GetSize(); i++) {
			cont[i]->Print();
		}

		cout << endl;
	}

	clock_t end = clock();
	double seconds = (double)(end - start);
	cout << endl << "Время работы: " << seconds << "с." << endl;
}