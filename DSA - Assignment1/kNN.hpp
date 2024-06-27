#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    virtual void headToIndex(int index) = 0;
    virtual T& getAndNext() = 0;
};


template<typename T>
class linkedList : public List<T> {
private:
    class Node;
    Node* head;
    int size;

    Node* currentPointer;
public:
    linkedList();
    ~linkedList() override;
    void push_back(T value) override;
    void push_front(T value) override;
    void insert(int index, T value) override;
    void remove(int index) override;

    T& get(int index) const override;
    int length() const override;
    void clear() override;
    void print() const override;
    void reverse() override;

    void headToIndex(int index) override;
    T& getAndNext() override;

};


class Dataset {
private:
    List<List<int>*>* data;

    List<string>* firstRow;
    //You may need to define more 

    //
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    List<List<int>*>* getData() const;

    void clearData();
    int sizeX();
    int sizeY();
    int getFirstColData(int index);
    List<int>* getDataSet(int index);    
    List<string>* getFirstRow() const;

    void clearFirstRow() {
        for (int i = 0; i < firstRow->length(); i++) firstRow->remove(i);
	    firstRow->clear();
    }
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset y_train;
    
    //You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
    double euclideanDistance(List<int>* link1, List<int>* link2);
    
    int mostFrequent(int* arr, int n);
    void selectionSort(double* &arr0, int* &arr1, const int& size);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed