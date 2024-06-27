# DSA-assignment1---Semester-232
The major assignment for the Data Structures and Algorithms course in the  semester 232 at VNU - HCMUT

MNIST Data Processing and kNN Implementation

__I. Overview__

Classification is one of the most fundamental and common problems in machine learning. The goal is to divide data into different groups (classes) based on their characteristics. Examples of simple classification problems include categorizing emails as spam or non-spam, classifying images as cats or dogs, etc. In this project, students will become familiar with the simple k-nearest neighbors (kNN) classification algorithm and apply this algorithm to process and classify the MNIST dataset.

Students are required to implement a class that provides the capability to process the MNIST dataset, and a class to effectively implement the kNN classification algorithm using list data structures.


__II. The MNIST Dataset__

The MNIST dataset is one of the most popular datasets and is commonly used to test and evaluate machine learning and computer vision algorithms. "MNIST" stands for "Modified National Institute of Standards and Technology". This dataset contains a set of images captured from handwritten samples of digits from 0 to 9, each image having a size of 28x28 pixels. Below are some important features of the MNIST dataset:

-Number of samples: The MNIST dataset includes 60,000 images in the training set and 10,000 images in the test set. However, to reduce computation, the number of images used for training and testing will be reduced. The maximum number of images to be used will be announced later.

-Data type: Each image in the MNIST dataset is encoded as pixel values, with each pixel value ranging from 0 to 255, representing the brightness of the pixel.

-Classification: Each image represents one of the digits from 0 to 9. The objective is to build a model that can accurately classify the digit in the image.

Students are provided with a "mnist.csv" file, where:

-Each row describes a digit image, encoded into 28x28 = 784 columns and one label column.

-The label column indicates the digit represented by the image. For each image, the value in this column ranges from 0 to 9.

-The remaining columns, titled iXj where i, j are within [1,28], represent the coordinates of the pixel. For each image, the values in these columns range from 0 to 255 (pixel intensity).


***k-Nearest Neighbors Algorithm***

The kNN algorithm is a simple yet effective classification algorithm that relies on finding the k closest data points to a new data point that needs classification.


__III. Idea__

![image](https://github.com/dangalpha78/DSA-assignment1---Semester-232/assets/120996961/24d9ee00-b45d-43bf-b887-f58bd027a168)

To grasp the idea of the algorithm, let's solve a small puzzle as shown in the figure below. Bob's store has 4 types of fruits: Apples, Oranges, Grapes, and Strawberries. Knowing that Bob arranges the fruits as shown in the image:


Your task is to predict the type of fruits marked from 1 to 10. The intuitive predictions might be:

1,2,3 → Oranges

4 → Uncertain if it's Orange or Apple

5,6 → Apples

7 → Strawberries

8 → Uncertain if it's Grapes or Strawberries

9 → Grapes

10 → Uncertain if it's Apple or Grapes

If your predictions match the ones above, you have used the kNN algorithm! Why so? Let's look at how you made these predictions.

In the image, we observe that similar fruits are grouped together. For 1, 2, and 3, we can easily classify them as Oranges because they are tightly surrounded by Oranges with no other types nearby, making it likely that the hidden fruits are also Oranges. Similarly, for 5, 6, 7, and 9.

For 10, we are uncertain if it's an Apple or a Grape because it's surrounded by both Apples and Grapes. Therefore, 10 could be either an Apple or a Grape. The same reasoning applies to 4 and 8.

In summary, the kNN algorithm predicts the label for a new data point based on the labels of its neighbors. kNN relies on the assumption that similar data points will be close to each other in the feature space. In the example above, based on the labels (Apples, Oranges, Strawberries, Grapes) of the neighbors, we can predict the label for a new data point (hidden fruit).


__IV. The k Parameter__
The k parameter in kNN is the number of nearest neighbors we consider to make a prediction. We determine the proximity of a point based on its distance (e.g., Euclidean, Manhattan, etc.) to the points under consideration. For example, if k = 5, we consider the 5 nearest points and take the label of the majority of these 5 points as the predicted label.

To clarify further, consider determining the neighbors in Bob's store as shown in the figure below. Our goal is to predict the label for the point marked as X. If k = 3, among the 3 nearest neighbors of X, 2 are Strawberries and 1 is an Orange. Therefore, we predict the label for X as Strawberries. If k = 5, among the 5 nearest neighbors of X, 3 are Oranges and 2 are Strawberries. Therefore, we predict the label for X as Orange.


__V. Algorithm__
We can create a kNN classification model by following these steps:

1. Load the data.
2. Initialize the value of k.
3. To obtain the predicted class, iterate from 1 to the total number of training data points.
4. Calculate the distance between the test data and each row of the training data. Here, we will use the Euclidean distance as the distance metric because it is the most commonly used method.
5. Sort the calculated distances in ascending order based on the distance values.
6. Select the top k rows from the sorted array.
7. Take the most frequent class of these rows.
8. Return the predicted class.


__VI. Euclidean Distance__
Euclidean distance is a method to measure the distance between two points in a multi-dimensional space. It is calculated by taking the square root of the sum of the squared differences between the coordinates of the two points.

In this project, to calculate the distance between the features of two images, let x = {x1, x2, ..., xk, ..., xn} be the vector containing the features of image 1 with n features (or can be understood as the number of columns excluding the label column of the dataset), y = {y1, y2, ..., yk, ..., yn} be the vector containing the features of image 2 with n features. The distance between the two images is calculated using the formula:
![image](https://github.com/dangalpha78/DSA-assignment1---Semester-232/assets/120996961/db41e749-31bb-4f74-94a7-6902d2de7d1a)

 

__VII. Training and Prediction Process__

In classification problems, the training and prediction process is crucial for building and deploying a prediction tool. During the training process, the tool is "trained" using training data to learn the relationships in the data. This process typically involves splitting the data into features and labels. In this project, the pixel information will be the features, and the label is the number represented by the image.

After splitting the data into features and labels, we usually divide the data into two subsets: the training set and the test set.

-X_train and y_train: These are the sets of features (X_train) and corresponding labels (y_train) used to train the model. The model will learn from the training data to make accurate predictions on new data.

-X_test and y_test: These are the sets of features (X_test) and corresponding labels (y_test) used to test the model's performance after training. The test data is used to evaluate whether the model generalizes well to new data.

In summary, the tool will learn from X_train and y_train, then make predictions on X_test. The prediction results will be compared with y_test to assess the accuracy of the predictions. Students can refer to sample test cases to see the training and prediction process in action.

#
