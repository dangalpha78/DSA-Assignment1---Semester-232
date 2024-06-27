#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
template<typename T>
class linkedList<T>::Node {
public:
    T data;
    Node* next;
    Node(const T& value) {
        this->data = value;
        this->next = nullptr;
    }
};

template<typename T>
linkedList<T>::linkedList() {
    this->head = nullptr;
    this->size = 0;
}

template<typename T>
linkedList<T>::~linkedList() {
    clear();
}

template<typename T>
void linkedList<T>::push_front(T value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
    }

    size++;
}

template<typename T>
void linkedList<T>::push_back(T value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    size++;
}

template<typename T>
void linkedList<T>::insert(int index, T value) {
    if (index < 0 || index >= size) {
        return;
    }

    if (index == size - 1) {
        push_back(value);
        return;
    }
    else if (index == 0) {
        push_front(value);
        return;
    }
    else {
        Node* current = head;
        Node* newNode = new Node(value);
        int i = 0;
        while (i < index - 1) {
            current = current->next;
            i++;
        }

        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

template<typename T>
void linkedList<T>::remove(int index) {
    if (index < 0 || index > size) {
        return;
    }

    Node* temp;
    if (!index) {
        temp = head;
        head = head->next;
    }
    else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }
    delete temp;
    size--;
}

template<typename T>
T& linkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("get(): Out of range");
    }
    Node* current = head;
    int i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }
    return current->data;
}

template<typename T>
int linkedList<T>::length() const {
    return size;
}

template<typename T>
void linkedList<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template<typename T>
void linkedList<T>::print() const {
    Node* current = head;

    while (current) {
        cout << current->data;
        if (current->next) {
            cout << " ";
        }
        current = current->next;
    }
}

template<typename T>
void linkedList<T>::reverse() {
    Node* current = head;
    Node* a = nullptr, * b = nullptr;

    while (current) {
        b = current->next;
        current->next = a;
        a = current;
        current = b;
    }

    head = a;
}

template<typename T>
void linkedList<T>::headToIndex(int index) {
    currentPointer = head;
    int i = 0;
    while (i < index){
        currentPointer = currentPointer->next;
        i++;
    }
}

template<typename T>
T& linkedList<T>::getAndNext(){
    Node* current = currentPointer;
    currentPointer = currentPointer->next;
    return current->data;
}


Dataset::Dataset() {
    this->data = new linkedList<List<int>*>();
    this->firstRow = new linkedList<string>();
}

Dataset::~Dataset() {
    for (int i = 0; i < data->length(); i++) {
        data->remove(i);
    }
    delete data;
}

Dataset::Dataset(const Dataset& other) {
    this->data = new linkedList<List<int>*>();
    this->firstRow = new linkedList<string>();
    for (int i = 0; i < other.firstRow->length(); i++) {
        this->firstRow->push_back(other.firstRow->get(i));
    }
    for (int i = 0; i < other.data->length(); i++) {
        linkedList<int>* link = new linkedList<int>();
        this->data->push_back(link);
    }

    for (int i = 0; i < other.data->length(); i++) {
        for (int j = 0; j < other.data->get(i)->length(); j++) {
            this->data->get(i)->push_back(other.data->get(i)->get(j));
        }
    }
}

Dataset& Dataset::operator=(const Dataset& other) {
    this->clearData();
    this->firstRow->clear();
    
    for (int i = 0; i < other.firstRow->length(); i++) {
        this->firstRow->push_back(other.firstRow->get(i));
    }
    for (int i = 0; i < other.data->length(); i++) {
        linkedList<int>* link = new linkedList<int>();
        this->data->push_back(link);
        for (int j = 0; j < other.data->get(i)->length(); j++) {
            link->push_back(other.data->get(i)->get(j));
        }
    }
    return *this;
}

bool Dataset::loadFromCSV(const char* fileName) {
    ifstream file(fileName);

    if (!file.is_open()) return false;

    string row0;
    getline(file, row0);
    istringstream iss(row0);

    while (getline(iss, row0, ',')) {
        firstRow->push_back(row0);
    }

    string line;

    while (getline(file, line)) {

        linkedList<int>* link0 = new linkedList<int>();
        istringstream iss(line);
        string cell;
        while (getline(iss, cell, ',')) {
            link0->push_back(stoi(cell));
        }

        data->push_back(link0);
    }

    file.close();

    return true;
}

void Dataset::printHead(int nRows, int nCols) const {

    if (!data->length()) return;

    if (nRows < 0 || nCols < 0) return;
    if (nRows > data->length()) nRows = data->length();
    if (nCols > firstRow->length()) nCols = firstRow->length();

    firstRow->headToIndex(0);
    for (int i = 0; i < nCols; i++) {
        cout << firstRow->getAndNext();
		if (i == nCols - 1) break;
		cout << " ";
    }
    cout << endl;

    
    data->headToIndex(0);
    for (int i = 0; i < min(nRows, data->length()); i++) {
        List<int>* temp = data->getAndNext();
        temp->headToIndex(0);
        for (int j = 0; j < nCols; j++) {
            cout << temp->getAndNext();

            if (j == nCols - 1) break;
            cout << " ";
        }
        if (i == min(nRows, data->length()) - 1) break;
        cout << endl;
    }
}

void Dataset::printTail(int nRows, int nCols) const {

    if (!data->length()) return;

    if (nRows > data->length()) nRows = data->length();
    if (nCols > firstRow->length()) nCols = firstRow->length();

    int i = firstRow->length() - nCols;
    int size = i;
    while (i < nCols + size) {
        cout << firstRow->get(i);
        if (i == nCols + size - 1) break;
		cout << " ";
        i++;
    }
    cout << endl;

    for (int i = max(0, data->length() - nRows); i < data->length(); i++) {
        for (int j = max(0, data->get(i)->length() - nCols); j < data->get(i)->length(); j++) {
            cout << data->get(i)->get(j);

            if (j == data->get(i)->length() - 1) break;
            cout << " ";
        }
        if (i == data->length() - 1) break;
        cout << endl;
    }
}

void Dataset::getShape(int& nRows, int& nCols) const {
    nRows = this->data->length();
    nCols = (this->data->length() > 0) ? this->data->get(0)->length() : 0;
}

void Dataset::columns() const {
    firstRow->print();
}

bool Dataset::drop(int axis, int index, std::string columns) {
    if (axis != 0 && axis != 1) return false;
    else if (axis == 0) {
        if (index >= data->length() || index < 0) return false;
        data->get(index)->clear();
        data->remove(index);
    }
    else if (axis == 1) {
        int index1 = -1;

        firstRow->headToIndex(0);
        for (int i = 0; i < firstRow->length(); i++) {
            if (firstRow->getAndNext() == columns) {
                firstRow->remove(i);
                index1 = i;
                break;
            }
            else if (i == firstRow->length() - 1) return false;
        }

        for (int i = 0; i < data->length(); i++) {
            data->get(i)->remove(index1);
        }
        return true;
    }
    return true;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    Dataset result;

    if (endRow == -1) endRow = this->data->length() - 1;
    if (endCol == -1) endCol = this->data->get(0)->length() - 1;

    firstRow->headToIndex(startCol);
    for (int indexString = startCol; indexString <= endCol; indexString++) {
        result.firstRow->push_back(this->firstRow->getAndNext());
    }
    
    data->headToIndex(startRow);
    for (int j = startRow; j <= endRow; j++) {
        List<int>* sourceRow = data->getAndNext();
        linkedList<int>* newRow = new linkedList<int>();
        sourceRow->headToIndex(startCol);
        for (int k = startCol; k <= endCol; k++) {
            newRow->push_back(sourceRow->getAndNext());
        }
        result.data->push_back(newRow);
    }

    return result;
}

void Dataset::clearData() {
    for (int i = 0; i < data->length(); i++) {
        data->get(i)->clear();
        data->remove(i);
    }
    data->clear();
}

int Dataset::sizeX() {
    return this->data->length();
}

int Dataset::getFirstColData(int index) {
    return this->data->get(index)->get(0);
}
int Dataset::sizeY() {
    return this->data->get(0)->length();
}

List<int>* Dataset::getDataSet(int index) {
    return data->get(index);
}

List<List<int>*>* Dataset::getData() const {
    return data;
}

List<string>* Dataset::getFirstRow() const {
    return firstRow;
}


kNN::kNN(int k) {
    this->k = k;
}

void kNN::fit(const Dataset& X_train, const Dataset& y_train) {
    this->X_train = X_train;
    this->y_train = y_train;
}

Dataset kNN::predict(const Dataset& X_test) {
    Dataset result;
    Dataset X_test1 = X_test;

    if (!X_test1.sizeX()) return result;

    result.getFirstRow()->push_back(y_train.getFirstRow()->get(0));

    if (k > X_train.sizeX()) throw std::out_of_range("get(): Out of range");

    for (int i = 0; i < X_test1.sizeX(); i++) {
        double* kMinDistance = new double[X_train.sizeX()];
        int* kMinLabel = new int[X_train.sizeX()];

        X_train.getData()->headToIndex(0);
        y_train.getData()->headToIndex(0);

        for (int z = 0; z < X_train.sizeX(); z++) {
            double distance = euclideanDistance(X_test1.getDataSet(i), X_train.getData()->getAndNext());
            kMinDistance[z] = distance;
            kMinLabel[z] = y_train.getData()->getAndNext()->get(0);
        }

        selectionSort(kMinDistance, kMinLabel, X_train.sizeX());
        
        int max = mostFrequent(kMinLabel, k);
        linkedList<int>* linkedL = new linkedList<int>();
        linkedL->push_back(max);
        result.getData()->push_back(linkedL);
        delete[] kMinDistance;
        delete[] kMinLabel;

    }

    
    return result;
}

double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
    Dataset dataSet_test = y_test;
    Dataset dataSet_pred = y_pred;

    double accuracy = 0;

    if (dataSet_pred.sizeX() == 0) return -1;

    dataSet_test.getData()->headToIndex(0);
    dataSet_pred.getData()->headToIndex(0);

    for (int i = 0; i < dataSet_test.sizeX(); i++) {
        if (dataSet_test.getData()->getAndNext()->get(0) == dataSet_pred.getData()->getAndNext()->get(0)) {
            accuracy++;
        }
    }
    return accuracy / dataSet_pred.sizeX();
}


double kNN::euclideanDistance(List<int>* link1, List<int>* link2) {
    double result = 0;

    link1->headToIndex(0);
    link2->headToIndex(0);

    for (int i = 0; i < link1->length(); i++) {
        result += pow(link1->getAndNext() - link2->getAndNext(), 2);
    }

    return sqrt(result);
}

int kNN::mostFrequent(int* arr, int n) {
    int count[10] = { 0,0,0,0,0,0,0,0,0,0 };
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int max = count[0];
    int index = 0;
    for (int i = 0; i < 10; i++) {
        if (count[i] > max) {
    		max = count[i];
            index = i;
    	}
    }

    return index;
}


void kNN::selectionSort(double*& arr0, int*& arr1, const int& size) {
    int i = 0;

    while (i < k) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr0[j] < arr0[index]) {
                index = j;
            }
        }
        swap(arr0[index], arr0[i]);
        swap(arr1[index], arr1[i]);
        i++;
    }
}

void train_test_split(Dataset& X, Dataset& y, double test_size, Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {

    if (test_size <= 0 || test_size >= 1) {
        return;
    }

    X_train = X.extract(0, int(X.sizeX() * (1 - test_size)) - 1, 0, -1);
    X_test = X.extract(int(X.sizeX() * (1 - test_size)), -1, 0, -1);

    y_train = y.extract(0, int(y.sizeX() * (1 - test_size)) - 1, 0, -1);
    y_test = y.extract(int(y.sizeX() * (1 - test_size)), -1, 0, -1);
}