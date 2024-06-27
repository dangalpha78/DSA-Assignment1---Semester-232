#include "kNN.hpp"
#include <chrono>

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    
    dataset.printHead();
    dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc2(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(10, 10);
    cout << endl;
    dataset.printTail(10, 10);
    cout << endl;
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
}

void tc3(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int>* row = dataset.getData()->get(0);
    row->insert(0, 1);
    row->print();
}

void tc4(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    feature.getShape(nRows, nCols);
    cout << "Feature shape: " << nRows << "x" << nCols << endl;
    label.getShape(nRows, nCols);
    cout << "Label shape: " << nRows << "x" << nCols << endl;
}

void tc5(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    X_train.getShape(nRows, nCols);
    cout << "X_train shape: " << nRows << "x" << nCols << endl;
    X_test.getShape(nRows, nCols);
    cout << "X_test shape: " << nRows << "x" << nCols << endl;
    y_train.getShape(nRows, nCols);
    cout << "y_train shape: " << nRows << "x" << nCols << endl;
    y_test.getShape(nRows, nCols);
    cout << "y_test shape: " << nRows << "x" << nCols << endl;
}

void tc6(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(100, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(100, 10);
    cout << endl;
}

void tc7() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}


void tc_test(){
    Dataset temp;
    temp.loadFromCSV("mnist.csv");
    temp.drop( 0, 3     ,"1x3" );
    temp.drop( 1, 62    ,"1x3" );
    temp.drop( 1, 49    ,"1x2" );
    temp.drop( 0, 53    ,"1x1" );
    temp.drop( 0, 17    ,"1x3" );
    temp.drop( 0, 0     ,"1x3" );
    temp.drop( 0, 72    ,"1x1" );
    temp.drop(-1, 47    ,"1x2" );
    temp.drop( 0, 91    ,"1x2" );
    temp.drop( 0, 22    ,"1x2" );
    temp.drop( 0, 46    ,"1x3" );
    temp.drop( 0, 55    ,"1x3" );
    temp.drop( 0, -1    ,"1x3" );

    kNN knn(6);

    Dataset X_train, X_test, y_train, y_test;
    int nCol = 0;
    int nRow = 0;

    temp.getShape(nRow, nCol);

    Dataset feature = temp.extract(0, -1, 1, -1);

    Dataset label = temp.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.99, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    cout << "Line X_train : " << endl;
    X_train.printHead(100, 100);
    cout << "Line X_test : " << endl;
    X_test.printHead(100, 100);
    cout << "Line y_train : " << endl;
    y_train.printHead(100, 100);
    cout << "Line y_test : " << endl;
    y_test.printHead(100, 100);
    cout << "Line y_predict : " << endl;
    y_pred.printHead(100, 100);

    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}

void tc1002()
{
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
List<int> *row = dataset.getData()->get(0);

row->push_back(2);

cout << row->length() << endl;
row->print();
}

void tc1004()
{
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
List<int> *row = dataset.getData()->get(0);

row->push_back(0);
row->push_back(2);

cout << row->length() << endl;
row->print();
}

void tc1005()
{
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
List<int> *row = dataset.getData()->get(0);

row->push_back(1);
row->push_back(2);
row->push_back(1);

cout << row->length() << endl;
row->print();
}

void tc1128()
{
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
dataset.printTail(50);
}

void tc1060()
{
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
List<int> *row = dataset.getData()->get(0);

row->insert(0, 1);
row->insert(1, 3);
row->insert(2, 2);
 row->insert(3, 5);
row->insert(4, 1);
row->insert(5, 3);
row->remove(0);

cout << row->length() << endl;
row->print();
}

void tc1160()
{
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    Dataset dataset_extract = dataset.extract(30, 20, 0, -1);
    Dataset dataset_extract2 = dataset_extract;
    dataset_extract2.getShape(nRows, nCols);
    cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}

void tc_knn_p(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
}

void tc_knn_score(int k, int size_X){
    int nRows, nCols;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");

    kNN knn = kNN(k);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, size_X, 1, -1);
    Dataset label = dataset.extract(0, size_X, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
}
void tc1204(){
    tc_knn_score(5, -1);
}

void tc1201(){
    tc_knn_score(5, 10);
}

void tc1203(){
    tc_knn_score(5, 100);
}


int main()
{
    tc6();
    tc7();
    return 0;

}
