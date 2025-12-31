import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.compose import make_column_transformer
from sklearn.preprocessing import StandardScaler, MinMaxScaler, OneHotEncoder
from sklearn.datasets import make_circles
from sklearn.metrics import confusion_matrix
import itertools # to make the confusion matrix pretty
from tensorflow.keras.datasets import fashion_mnist
import random
from tensorflow.keras.utils import plot_model

# --------------------------------------------------------------
# Learn the basics of TensorFlow and Deep Learning fundamentals with Python 2021
# Video https://www.youtube.com/watch?v=tpCFfeUEGs8&list=LL&index=13&t=7640s
# part 2 https://www.youtube.com/watch?v=ZUKz4125WNI&t=57s
# --------------------------------------------------------------
# Vocabulary:
# Tensor: A multi-dimensional array used in TensorFlow to represent data.
# batch : A subset of the training dataset used in one iteration of model training.
# feature matrix : A matrix containing the input features for a machine learning model, where each row represents a sample and each column represents a feature.
# labels : The target outputs or values that a machine learning model aims to predict.
# Parameters : The internal variables of a machine learning model that are learned from the training data. Weights and biases are examples of parameters.
# Dense layer : A type of neural network layer where each neuron is connected to every neuron in the previous layer.
# Activation function : A mathematical function applied to the output of a neuron in a neural network to introduce non-linearity.
# Epoch : One complete pass through the entire training dataset during model training.
# --------------------------------------------------------------
# prerequisites:
# plt
# panda
# sklearn
# numpy

def learn_basics():
    """
    Docstring for learn_basics
    """
    #===========================================================
    # Create tensors
    #===========================================================
    # Basic Tensor
    Changeable_Tensor = tf.Variable([1,3,4])
    Immutable_Tensor = tf.constant([1,2,3])
    print("\n\n")
    print(Changeable_Tensor)
    print("\n")
    print(Immutable_Tensor)

    # Random Tensor
    Random_Tensor = tf.random.Generator.from_seed(42)
    Random_Tensor = tf.random.normal([3,4])
    print("\n")
    print(Random_Tensor)

    # Big Tensor
    Big_Tensor = tf.zeros(shape=(2,3,4,5))
    print("\n")
    print(Big_Tensor)

    # Squeeze a tensor (removing all 1 sized dimensions)
    Squeezed_Tensor = tf.squeeze(tf.zeros(shape=(1,2,1,3,4,1,5))) #will remove the 1 dimmensions
    print("Before squeeze:", tf.zeros(shape=(1,2,1,3,4,1,5)).shape)
    print("\n")
    print("After squeeze:", Squeezed_Tensor.shape)
    print(Squeezed_Tensor)

    # Expand a tensor (adding a 1 dimension)

    #===========================================================
    #Tensor arythmetics
    #===========================================================


    print("\n")
    print("==============================================")
    print("Tensor arythmetics")
    print("==============================================")
    X = tf.constant([[1,2],[3,4]])
    Y = tf.constant([[5,6],[7,8]])
    print("\n")
    print("X + 10 = \n", X + 10)
    print("\n")
    print("X - Y = \n", X - Y)
    print("\n")
    print("X * Y = \n", X * Y) # Les deux dernières dimensions doivent correspondre et la sortie :
    #A: (m,)
    #B: (n,)
    #Résultat: (m, n)
    print("\n")
    X_transpose = tf.transpose(X)
    X_Reshaped = tf.reshape(X, shape= (1,4))
    print("\n")
    print("X = \n", X)
    print("\n")
    print("X Transpose = \n", X_transpose) # on lit de line à colone les tableaux, https://www.tensorflow.org/api_docs/python/tf/transpose
    print("\n") 
    print("X Reshaped = \n", X_Reshaped)
    print("\n")
    print("Multiplication using tf.matmul = \n", tf.matmul( tf.reshape((X),shape=(1,4)) , tf.reshape((Y),shape=(4,1))))
    #performe a dot product on X and Y
    print("\n")
    print("Dot Product using tf.tensordot = \n", tf.tensordot(tf.transpose(X), Y, axes=1))

    #===========================================================
    #Tensor indexing, cast, aggregation
    #===========================================================
    #Indexing of tensor
    print("\n")
    print("==============================================")
    print("Tensor indexing, cast, aggregation")
    print("==============================================")
    print("\n")
    print("X[0][1]:", X[0][1])
    #Change datatype of tensor
    X = tf.constant([[1.0,2.0],[3.0,4.0]])
    print("\n")
    print("X Dtype before change:", X.dtype)
    X = tf.cast(X, dtype=tf.float16)
    print("X Dtype after change:", X.dtype)
    #Agregating, so condensing them from multiple values down to a smaller amount of values
    print("\n")
    print("Sum of all elements in X:", tf.reduce_sum(X))
    print("Mean of all elements in X:", tf.reduce_mean(X))
    print("Maximum element in X:", tf.reduce_max(X))
    print("Minimum element in X:", tf.reduce_min(X))
    print("Variance of elements in X:", tf.math.reduce_variance(X)) # need to be float, etc
    #Deviation is how far a data point is from the mean, while variance is the average of the squared deviations from the mean. Standard deviation is the square root of the variance
    print("Standard Deviation (ecart type) of elements in X:", tf.math.reduce_std(X))
    #Convert tensor to numpy array
    X_numpy = X.numpy()

def Neural_Network_Regression():
    """
    Docstring for Neural_Network_Regression
    """
    #--------------------------------------------------------------
    # Creating Inputs for a Neural Network Regression Model
    #--------------------------------------------------------------
    #In statistical modeling, regression analysis is a statistical method for estimating the relationship between a dependent variable
    #Time stamp in video 4 hours
    print("\n")
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("Some Inputs") 
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("\n")
    #One hot encoding
    print("One Hot Encoding:")
    some_list = [0,1,2,3,4] # Could be red, blue, green, yellow, purple. Will be converted to a one hot encoded tensor so that ML models can work with it
    print("Original list:", some_list) 
    one_hot_encoded = tf.one_hot(some_list, depth=5)
    print("One hot encoded:\n", one_hot_encoded)
    # On vallues and off values
    one_hot_encoded_custom = tf.one_hot(some_list, depth=5, on_value="I am on", off_value="I am off")
    print("\n")
    print("One hot encoded with custom on and off values:\n", one_hot_encoded_custom)
    #--------------------------------------------------------------
    # Steps in modeling in tensorflow(Time stamp in video 4 hours 13 minutes) :
    # 1. Create a model (define the architecture), features (inputs) and labels (outputs)
    # 2. Compile the model (define the loss function, optimizer and evaluation metrics)
    # 3. Fit the model (train the model on the training data)
    #--------------------------------------------------------------
    print("\n")
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("First Neural Network Regression Model") 
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("\n")
    # Create some dummy data, feature matrix X and labels y
    X = np.array([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0])
    y = np.array([3.9, 7.8, 11.7, 15.6, 19.5, 23.4, 27.3, 31.2, 35.1, 39.0]) # roughly y = 3.9 * X_train
    # Convert to TensorFlow tensors with float dtype
    X = tf.cast(tf.constant(X), dtype=tf.float32)
    y = tf.cast(tf.constant(y), dtype=tf.float32)
    # Dense layers expect input with shape (batch_size, features).
    # Reshape the 1D feature vector to 2D: (n_samples, 1)
    X = tf.reshape(X, shape=(-1, 1)) #Keras Dense layers expect input shape (batch_size, features)
    #tf.reshape returns a tensor with the same values but a different shape.
    #shape = (-1, 1) tells TensorFlow:
    #The second dimension must be 1 (one feature per sample).
    #The -1 is a placeholder that lets TensorFlow infer the correct size for the first dimension so the total number of elements stays the same. Effectively it becomes (n_samples, 1).
    #So if X_train was shape (10,) it becomes (10, 1). If it was (100,) it becomes (100, 1).
    # Create a Model
    model = tf.keras.Sequential([ # Sequential : a linear stack of layers
        tf.keras.layers.Dense(1, input_shape=(1,), name='dense') # output layer with 1 neuron for regression (1 in dense because 1 X to 1 y)
    ])
    # Compile the model
    model.compile(
        loss=tf.keras.losses.mae, # mae : mean absolute error, the mean of the differences between predicted and actual values.
        optimizer=tf.keras.optimizers.SGD(), # SGD : Stochastic Gradient Descent, an optimization algorithm used to minimize the loss function by updating model parameters iteratively.
        metrics=['mae'] # Metrics are quantifiable measurements used to assess performance
    )
    # Summary of the model
    model.summary()
    # Train the model
    model.fit(X, y, epochs=5)# Train the model for 5 epochs, meaning the model will iterate over the entire training dataset 5 times to learn the patterns.
    # Evaluate the model
    model.evaluate(X, y)# Evaluate the model's performance on the training data by calculating the loss and metrics defined during compilation.
    # Make predictions
    predictions = model.predict(X)

    print("\n")
    print("Predictions on training data:\n", predictions)
    print("\n")
    print("Actual training labels:\n", y.numpy())
    print("The prediction is pretty bad. Let's improve it.")

    #--------------------------------------------------------------
    # Steps in improving the model in tensorflow
    # 4:48 in video
    # 1. Create a model (define the architecture), features (inputs) and labels (outputs). Add layers, increase the number  of hidden units (neurons), change activation function, 
    # 2. Compile the model (define the loss function, optimizer and evaluation metrics). Change the learning rate of the optimizer, change the optimizer, etc.
    # 3. Fit the model (train the model on the training data). Increase the number of epochs.
    #--------------------------------------------------------------
    print("\n")
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("Improved Neural Network Regression Model")
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("\n")
    #5h07m in video
    # More data
    X = tf.range(0, 100, 1)
    X = tf.cast(X, dtype=tf.float32)
    y = X * 3.9 + tf.random.normal(shape=X.shape, mean=0.0, stddev=10.0) # add some noise to the labels
    # Reshape the data
    X = tf.reshape(X, shape=(-1, 1))
    y = tf.reshape(y, shape=(-1, 1))
    # Create a Model
    model = tf.keras.Sequential([
        #tf.keras.layers.Dense(100, activation='relu', input_shape=(1,), name='hidden_layer_1'), # hidden layer with 100 neurons and ReLU activation
        #tf.keras.layers.Dense(100, activation='relu', input_shape=(1,), name='hidden_layer_2'), # hidden layer with 100 neurons and ReLU activation
        #tf.keras.layers.Dense(100, activation='relu', input_shape=(1,), name='hidden_layer_3'), # hidden layer with 100 neurons and ReLU activation
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])
    # Compile the model
    model.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.SGD(learning_rate=0.001), # Increasing learning rate to 0.01 ? default is 0.001
        metrics=['mae']
    )
    # Summary of the model
    model.summary()
    # Train the model
    model.fit(X, y, epochs=100) # Increased epochs to 100, could be overfitting (learning too well on these precise datas), if a new data is introduced the model might perform poorly
    # Optionally visualize the model architecture. Disabled by default to avoid
    # creating image files (JPEG/PNG) during script runs.
    #tf.keras.utils.plot_model(model, show_shapes=True) # Visualize the model architecture, creates a jpeg this is why disabled by default
    # Evaluate the model
    model.evaluate(X, y)
    # Make predictions
    predictions = model.predict(X)
    print("\n")
    print("Predictions on training data:\n", predictions[0])
    print("\n")
    print("Actual training labels:\n", y.numpy()[0])
    #--------------------------------------------------------------
    # Evaluate your model (5:16 in video):
    # 1. the 3 data sets, 
    # 2. model summary, visualise layers,
    # 3. Visualise predictions, 
    # 4. regression evaluation metrics, MAE, MSE
    #--------------------------------------------------------------
    # 1. The 3 sets...
    # a. Training set : the data the model learns from, is typically 70-80% of the total data
    # b. Validation set : the data the model is validated on during training, is typically 10-15% of the total data
    # c. Test set : the data the model is tested on after training, is typically 10-15% of the total data
    print("The leght of X is :",len(X))
    X_train = X[:80] # First 80% of the data
    y_train = y[:80]
    X_test = X[80:] # last 20% of the data
    y_test = y[80:]

    #Vizualize the data
    plt.figure(figsize=(10, 7))
    plt.title("Training and Testing Data")
    plt.xlabel("X")
    plt.ylabel("y")
    plt.scatter(X_train, y_train, c='b', label='Training Data')
    plt.scatter(X_test, y_test, c='r', label='Testing Data')
    plt.legend()
    plt.show()

    # Let's build a model to fit the data better

    # a. Create a Model
    model = tf.keras.Sequential([
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])

    # b. Compile the model
    model.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.SGD(learning_rate=0.001),
        metrics=['mae']
    )
    # c. Fit the model
    model.fit(X_train, y_train, epochs=100, verbose=0)

    # 2. Model summary and visualize layers : 

    # Summary of the final model
    model.summary()
    # Total parameters = 101 (100 from hidden layer + 1 from output layer)
    # Trainable parameters = 101, meaning these parameters will be updated during training
    # Non-trainable parameters = 0, meaning there are no parameters that will remain constant during training

    # tf.keras.utils.plot_model(model, show_shapes=True) # Visualize the model architecture, creates a jpeg this is why disabled by default

    # 3. Visualize predictions : 
    # 6 hours in video

    y_pred = model.predict(X_test)
    plt.figure(figsize=(10, 7))
    plt.title("Model Predictions vs Actual Data")
    plt.xlabel("X")
    plt.ylabel("y")
    plt.scatter(X_test, y_test, c='b', label='Actual Data')
    plt.scatter(X_test, y_pred, c='r', label='Predicted Data')
    plt.legend()
    plt.show()

    # 4. Regression evaluation metrics, MAE, MSE
    print("\n Evaluating model on test data:")
    model.evaluate(X_test, y_test) # outputs loss (MAE) and MAE metric, see those in the model.compile() step
    #print(tf.metrics.mean_absolute_error(y_test, y_pred)) # calculate MAE manually, should be similar to the one outputed by model.evaluate
    #print("\n %f",tf.metrics.MeanSquaredError(y_test, y_pred)) # calculate MSE manually, MSE punishes larger errors more than MAE

    #--------------------------------------------------------------
    # Running experements to improve model (6:25 in video):
    #--------------------------------------------------------------
    # Jump to 6:50 in video because honestly it's just repeating the same steps of creating, compiling and fitting the model with different parameters
    # Compare the 3 models using pandas dataframe

    # a. Create a Models 3
    model_1 = tf.keras.Sequential([
        tf.keras.layers.Dense(100, activation='relu', input_shape=(1,), name='hidden_layer_1'), # hidden layer with 100 neurons and ReLU activation
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])
    model_2 = tf.keras.Sequential([
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])
    model_3 = tf.keras.Sequential([
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])

    # b. Compile the models
    model_1.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.SGD(learning_rate=0.001),
        metrics=['mae']
    )
    model_2.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.SGD(learning_rate=0.001),
        metrics=['mae']
    )
    model_3.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.SGD(learning_rate=0.001),
        metrics=['mae']
    )
    # c. Fit the models
    model_1.fit(X_train, y_train, epochs=100,verbose=0)
    model_2.fit(X_train, y_train, epochs=100,verbose=0)
    model_3.fit(X_train, y_train, epochs=200,verbose=0)

    # Pandas dataframe to compare the models
    model_1_results = model_1.evaluate(X_test, y_test, verbose=0)
    model_2_results = model_2.evaluate(X_test, y_test, verbose=0)
    model_3_results = model_3.evaluate(X_test, y_test, verbose=0)

    model_comparison = pd.DataFrame({
        "Model": ["Model 1", "Model 2", "Model 3"],
        "Loss (MAE)": [model_1_results[0], model_2_results[0], model_3_results[0]],
        "MAE": [model_1_results[1], model_2_results[1], model_3_results[1]]
    })
    print("\n Model Comparison:\n", model_comparison)

    # save the model, there are multiple formats, here we use the HDF5 format (.h5)
    # you can load it later using tf.keras.models.load_model("best_model.h5")
    # you can also use checkpoints during training to save the best model
    # model_2.save("best_model.h5")

    # Load a saved model
    # loaded_model = tf.keras.models.load_model("best_model.h5")
    # loaded_model.summary()

    pass

def Larger_Regression_Example():
    """
    Docstring for Larger_Regression_Example
    A larger exemple (7:28 in video):
    We want to predict the insurance cost based on some features (it is a regression problem)
    """

    # Link to data https://www.kaggle.com/datasets/mirichoi0218/insurance

    # Read in the insurancedata
    insurance = pd.read_csv("https://raw.githubusercontent.com/stedy/Machine-Learning-with-R-datasets/refs/heads/master/insurance.csv")
    print("\n Insurance Data Head:\n", insurance.head()) #object type is string/categorical data exemple "woman" or "man".

    # first we need to know what are the types of data we have, the features
    # Let's check the datatypes of each column
    print("\n Insurance Data Info:")
    print(insurance.info())

    # One hot encode the categorical features, so it's all numerical data
    insurance_one_hot = pd.get_dummies(insurance)
    print("\n One Hot Encoded Insurance Data Head:\n", insurance_one_hot.head())

    # Create X and y
    X = insurance_one_hot.drop("charges", axis=1) # all columns except the last one (charges)
    y = insurance_one_hot["charges"] # only the charges column

    # Split the data into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)# 80% training, 20% testing, random_state for reproducibility
    
    # Modeling steps:
    # a. Create a Model
    insurance_model_1 = tf.keras.Sequential([
        tf.keras.layers.Dense(10, activation='relu', input_shape=(X_train.shape[1],), name='hidden_layer_1'), # hidden layer with 100 neurons and ReLU activation
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])
    #b. Compile the model
    insurance_model_1.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.SGD(learning_rate=0.001),
        metrics=['mae'])
    # c. Fit the model
    insurance_model_1.fit(X_train, y_train, epochs=100, verbose=1)

    # Evaluate the model
    insurance_model_1.evaluate(X_test, y_test)
    print("\n Median and mean of the outputs ", y_train.median(), y_train.mean())# to have an idea of the error we get

    #--------------------------------------------------------------
    # Improving the model (7:55 in video):
    #--------------------------------------------------------------

    # Modeling steps:
    # a. Create a Model
    insurance_model_2 = tf.keras.Sequential([
        tf.keras.layers.Dense(100, activation='relu', name='hidden_layer_1'), # hidden layer with 100 neurons and ReLU activation
        tf.keras.layers.Dense(10, activation='relu', name='hidden_layer_2'),
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])
    #b. Compile the model
    insurance_model_2.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.Adam(),
        metrics=['mae'])
    # c. Fit the model
    insurance_model_2.fit(X_train, y_train, epochs=100, verbose=0)

    # Evaluate the model
    print("\n Evaluating improved model:")
    insurance_model_2.evaluate(X_test, y_test)

    #plot history, loss curve or training curve
    pd.DataFrame(insurance_model_2.history.history).plot()
    plt.ylabel("loss") # our loss function is MAE here
    plt.xlabel("epochs")
    plt.show()

    # Questions to ask yourself : How long does the model need to train ? Is the model overfitting or underfitting ?
    # Solution : early stopping, etc.

    #--------------------------------------------------------------
    # Preprocessing data (8:10 in video):
    # here we will normalize or standardize the data
    #--------------------------------------------------------------
    # Normalization : scaling the data to be between 0 and 1
    # Standardization : scaling the data to have a mean of 0 and a standard deviation of 1

    # Create a column transformer with normalization for numerical features
    ct = make_column_transformer(
        (MinMaxScaler(), ["age", "bmi", "children"]), # Normalize these columns, mimax scaler scales the data to be between 0 and 1
        (OneHotEncoder(handle_unknown='ignore'), ["sex", "smoker", "region"]) # One hot encode the categorical columns, handle_unknown='ignore' means that if a category is not present in the training data, it will be ignored during transformation
    )
    
    # Create X and y again
    X = insurance.drop("charges", axis=1) # all columns except the last one
    y = insurance["charges"] # only the charges column

    # Build our test and train sets
    #X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    #fit the column transformer to the training data
    ct.fit(X_train)

        # Transform the training and testing data with normalization and one hot encoding
    X_train_normalized = ct.transform(X_train)
    X_test_normalized = ct.transform(X_test)
    print("\n Normalized and One Hot Encoded Training Data :\n", X_train_normalized)



    #Bluild a model on the normalized data
    #a. Create a Model
    insurance_model_3 = tf.keras.Sequential([
        tf.keras.layers.Dense(100, activation='relu', name='hidden_layer_1'), # hidden layer with 100 neurons and ReLU activation
        tf.keras.layers.Dense(10, activation='relu', name='hidden_layer_2'),
        tf.keras.layers.Dense(1,name='output_layer') # output layer with 1 neuron for regression
    ])
    #b. Compile the model
    insurance_model_3.compile(
        loss=tf.keras.losses.mae,
        optimizer=tf.keras.optimizers.Adam(),
        metrics=['mae'])
    # c. Fit the model
    insurance_model_3.fit(X_train_normalized, y_train, epochs=100, verbose=0)
    # Evaluate the model
    print("\n Evaluating normalized model:")
    insurance_model_3.evaluate(X_test_normalized, y_test)

    pass

def Neural_Network_Classification():
    """
    Docstring for Neural_Network_Classification
    Neural network classification (8:39 in video)
    """
    # Multiclass classification : more than 2 classes to predict (ex: classifying images of clothes into categories like t-shirts, trousers, dresses, etc.)
    # Multilabel classification : more than 1 label to predict; multiple label options per sample (ex: tagging an article with multiple tags (one for each topic covered in the article))
    # sample : one piece of data
    # feature : one piece of information about a sample; numerical inputs to a model

    # Make 1000 examples
    n_samples = 1000

    # Create circles, 
    X, y = make_circles(n_samples,
                        noise=0.03,
                        random_state=42)
    
    # Check out features
    #print(X)
    #print("\n",y)
    #check the labels
    #print(y[:10])

    #Lets visualize ! 9:15 in the video
    #Tableau
    #circles = pd.DataFrame({"X0":X[:,0], "X1":X[:,1], "label":y}) # we have 2 features per labels, and 1000 samples
    #print(circles)
    #graph
    #plt.scatter(X[:,0], X[:,1],c=y, cmap=plt.cm.RdYlBu)
    #plt.show()

    # INPUT AND OUTPUT SHAPES
    # Check the shapes of our features and labels
    print(X.shape, y.shape)
    # How many samples
    len(X),len(y)
    # View the first sample etc....

    # Modeling 9:28 in video
    # a. Create model
    model = tf.keras.Sequential([
        tf.keras.layers.Dense(1),
        tf.keras.layers.Dense(1)
    ])
    # b. Compile
    model.compile(loss=tf.keras.losses.BinaryCrossentropy,
                  optimizer=tf.keras.optimizers.Adam(),
                  metrics=["accuracy"])#accuracy is, out of x samples, how many are good
    # c. fit
    model.fit(X,y,epochs=200, verbose=0)

    # d. Evaluate
    # model.evaluate() # but here we don't have some test data :,(
    # (one layer, two layers, even with 200 epochs the model is randomlly guessing, 50 percent accuracy, that's shit)

    # a. Create model 9:42 in video
    model_2 = tf.keras.Sequential([
        tf.keras.layers.Dense(100),
        tf.keras.layers.Dense(10),
        tf.keras.layers.Dense(1)
    ])
    # b. Compile
    model_2.compile(loss=tf.keras.losses.BinaryCrossentropy,
                  optimizer=tf.keras.optimizers.Adam(),
                  metrics=["accuracy"])#accuracy is, out of x samples, how many are good
    # c. fit
    model_2.fit(X,y,epochs=100, verbose=0)

    # d. Evaluate
    #model.evaluate() # but here we don't have some test data :,(

    # (the model is still randomlly guessing, 50 percent accuracy, that's shit)
    # The reason it's shit is because the 2 classes are not linear

    plot_decision_boundary(model=model_2, X=X, y=y)
    plt.show()
    pass

def non_linear():
    """
    Docstring for non_linear
    (0:00 in video part 2):
    the non linear data problem and binary classification problem
    """

    # Make 1000 examples
    n_samples = 1000

    # Create circles, 
    X, y = make_circles(n_samples,
                        noise=0.03,
                        random_state=42)
    # Check the data
    plt.scatter(X[:,0],X[:,1], c=y, cmap=plt.cm.RdYlBu)
    #plt.show()

    # a. Build model
    model_1 = tf.keras.Sequential([
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),# 4 neurons to add complexity, Relu and not linear cause we are not in a regression problem 
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
        tf.keras.layers.Dense(1, activation=tf.keras.activations.sigmoid)# last layer is only one neuron because the output is binary (Red or blue), also the activation function for the output is not the same, sigmoid for binary classification and softmax for multiclass classification
    ])
    # b. Compile model
    model_1.compile(loss=tf.keras.losses.BinaryCrossentropy,
                    optimizer=tf.keras.optimizers.Adam(),
                    metrics=["accuracy"])
    # c. fit the model
    history = model_1.fit(X,y,epochs=250, verbose=0)
    # d. should be evaluate but I didn't craete a test data groupe so the evaluation is shit but let's do it
    print("\nEvaluation of the model:")
    model_1.evaluate(X, y)
    # see boundaries
    plot_decision_boundary(model_1, X, y)
    plt.show()
    
    pass

def experiment_with_linear_non_linear_data():
    """
    Docstring for experiment_with_linear_non_linear_data
    (00:35 in video part 2):
    """

    # Create a toy sensor
    A = tf.cast(tf.range(-10,10), tf.float32)
    #plt.plot(A)
    #plt.show()

    # Create a sigmoid
    # def Sigmoid(x): return 1/(1 + tf.exp(-x))
    #plt.plot((1/(1 + tf.exp(-A))))
    #plt.show()

    # Create a Relu
    # def Relu(x): return tf.maximum(0, x)
    #plt.plot(tf.maximum(0, A))
    #plt.show()

    #--------------------------------------------------------------
    #  (1:00 in video part 2):
    # Testing the model we did previously on other data (circular binary classification problem)
    #--------------------------------------------------------------
    # Creating trainn and test sets
    # Make 1000 examples
    n_samples = 1000

    # Create circles, 
    X, y = make_circles(n_samples,
                        noise=0.03,
                        random_state=42)
    X_train, y_train = X[:800], y[:800]
    X_test, y_test = X[800:], y[800:]

    # Let's build the exact same model then before that worked
    # a. Build model
    model_works_nonlinear = tf.keras.Sequential([
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),# 4 neurons to add complexity, Relu and not linear cause we are not in a regression problem 
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
        tf.keras.layers.Dense(1, activation=tf.keras.activations.sigmoid)# last layer is only one neuron because the output is binary (Red or blue), also the activation function for the output is not the same, sigmoid for binary classification and softmax for multiclass classification
    ])
    # b. Compile model
    model_works_nonlinear.compile(loss=tf.keras.losses.BinaryCrossentropy,
                    optimizer=tf.keras.optimizers.Adam(),
                    metrics=["accuracy"])
    # c. fit the model
    history = model_works_nonlinear.fit(X_train,y_train,epochs=250, verbose=0)

    # Plot the decision boundaries for the training and set data
    plt.figure(figsize=(12,6))
    plt.subplot(1,2,1)
    plt.title("Train Data")
    plot_decision_boundary(model_works_nonlinear, X=X_train, y=y_train)
    plt.subplot(1,2,2)
    plt.title("Test Data")
    plot_decision_boundary(model_works_nonlinear, X=X_test, y=y_test)
    plt.show()

    # 1:07 in video 
    # Talking about the history variable, used to visualize the training of the model (plot the loss function)
    print(pd.DataFrame(history.history))
    pd.DataFrame(history.history).plot()
    plt.title("model_works_nonlinear loss curves")
    plt.show()
    # Here is good because accury goes up and loss goes down

    #----------------------------------------
    # Find the ideal learning rate
    # 1:10 in video
    # I. lr callback (functionnamity while it's trainning)
    # II. compare the lr curves with the loss curve to find the ideal
    #----------------------------------------

    # I. create a learning rate callback
    lr_scheduler = tf.keras.callbacks.LearningRateScheduler(lambda epoch: 1e-4 * 10**(epoch/20))# every epochs it goes trough, values between [1e-4 and increasing by 10**(epoch/20)] 
    
    # a. Build model
    tf.random.set_seed(42)
    model_works_nonlinear = tf.keras.Sequential([
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),# 4 neurons to add complexity, Relu and not linear cause we are not in a regression problem 
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
        tf.keras.layers.Dense(1, activation=tf.keras.activations.sigmoid)# last layer is only one neuron because the output is binary (Red or blue), also the activation function for the output is not the same, sigmoid for binary classification and softmax for multiclass classification
    ])
    # b. Compile model
    model_works_nonlinear.compile(loss=tf.keras.losses.BinaryCrossentropy,
                    optimizer=tf.keras.optimizers.Adam(),
                    metrics=["accuracy"])
    # c. Fit the model
    history = model_works_nonlinear.fit(X_train,y_train,epochs=100, callbacks=[lr_scheduler], verbose=0) # you can pass multiple callbacks, here only one
    
    # II. compare the lr curves with the loss curve to find the ideal
    # Plot the history
    pd.DataFrame(history.history).plot(figsize=(10, 7), xlabel="epochs")
    plt.title("model_works_nonlinear loss curves")
    plt.show() #the green lr is exponential because it starts with 1e-4 and increasing by 10**(epoch/20) every epoch
    # We can't really see the link bewteen lr value and loss, let's plot this
    lrs = 1e-4 * (10 ** (tf.range(100)/20))
    print("\n len(lrs) : ", len(lrs), ", same number of epochs") #same number of epochs
    plt.figure(figsize=(10,7))
    plt.semilogx(lrs, history.history["loss"])# plot with log on th x axis
    plt.xlabel("Learning Rate")
    plt.ylabel("Loss")
    plt.title("Learning rate vs Loss")
    plt.show() # We want the lr value wherev the loss is the lowest. But we don't want instability in the learning, so we want the lr value where the loss curve is still decreasing but not flat (going up and down).
    # let's maybe take 0.02
    # 1:28 in the video
    # You gotta think of the other metrics when you train, here there is loss but also accuracy.

    pass

def More_evaluation_Methodes():
    """
    Docstring for More_evaluation_Methodes
    1:37 in the video
    """
    # Some metrics:
    # Accuracy, default for classification problems
    # Precision, more precision leads to less false positive
    # Recall, higher recall leads for less false negative (but often less false negative => more false positive and the reverse)
    # F1-score, a combinasion of both precision and recall, usually good for classification problems <3
    # Confusion matrix, build your own metric (you could use the sklearn.metrics.confudion_matrix())
    # Classification reports (from scikit-learn)
    
    # Creating trainn and test sets
    # Make 1000 examples
    n_samples = 1000

    # Create circles, 
    X, y = make_circles(n_samples,
                        noise=0.03,
                        random_state=42)
    X_train, y_train = X[:800], y[:800]
    X_test, y_test = X[800:], y[800:]

    # a. Build model
    tf.random.set_seed(42)
    model_works_nonlinear = tf.keras.Sequential([
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),# 4 neurons to add complexity, Relu and not linear cause we are not in a regression problem 
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
        tf.keras.layers.Dense(1, activation=tf.keras.activations.sigmoid)# last layer is only one neuron because the output is binary (Red or blue), also the activation function for the output is not the same, sigmoid for binary classification and softmax for multiclass classification
    ])
    # b. Compile model
    model_works_nonlinear.compile(loss=tf.keras.losses.BinaryCrossentropy,
                    optimizer=tf.keras.optimizers.Adam(),
                    metrics=["accuracy"])
    # c. Fit the model
    history = model_works_nonlinear.fit(X_train,y_train,epochs=100, verbose=0) # you can pass multiple callbacks, here only one
    # d. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Evaluate !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    loss, accuracy = model_works_nonlinear.evaluate(X_test, y_test, verbose=0)

    # How about the confusion matrix metrix??
    # Make predictions
    y_preds = model_works_nonlinear.predict(X_test)
    # The input of the confusion_matrix are binaries, so wee need to convert y_preds to binary (now they are prediction probability, the standard sigmoid or softmaw output)
    #for i in range(0,len(y_preds)):
    #    if y_preds[i] > 0.5:
    #        y_preds[i] = 1
    #    else:
    #        y_preds[i] = 0
    # or just use round function
    #print("\n\n",y_preds)
    # Create confucion matrix
    cm =confusion_matrix(y_test, tf.round(y_preds))
    print("\n\n",cm)
    # !!!!!!!!!!!!!!!!!!!!!!!Make a pretty confudion matrix 🥰!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    figsize = (10,10)
    cm_normalized = cm.astype("float") / cm.sum(axis=1)[:, np.newaxis] # normalize our confusion matrix
    n_classes = cm.shape[0]
    # prettify
    fig, ax = plt.subplots(figsize=figsize)
    cax = ax.matshow(cm, cmap=plt.cm.Blues)#don't confuse cm confusion matrix with the plt.cm color map
    fig.colorbar(cax)
    # Create classes
    classes = False
    if classes:
        labels = classes
    else:
        labels = np.arange(cm.shape[0])
    #Label the axis
    ax.set(title="Confusion Matrix", 
           xlabel="Predicted labels", 
           ylabel="True Label", 
           xticks=np.arange(n_classes), 
           yticks=np.arange(n_classes), 
           xticklabels=labels, 
           yticklabels=labels)
    # Set threshold for different colours
    threshold = (cm.max() + cm.min()) / 2. 
    # Plot the text on each cell
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, f"{cm[i, j]} ({cm_normalized[i, j]*100:.1f}%)",
                 horizontalalignment="center",
                 color="white" if cm[i, j] > threshold else "black",
                 size=15)
    plt.show()
    # End of !!!!!!!!!!!!!!!!!!!!!!!Make a pretty confudion matrix 🥰!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    # You could see Classification report metric, not seen in the video ;(
    pass

def Multiclass_classification():
    """
    Docstring for Multiclass_classification
    2:10 in video
    """
    # Different item of clothing example.
    # https://www.tensorflow.org/datasets/catalog/fashion_mnist?hl=fr
    
    # Load the data
    (train_data, train_labels), (test_data, test_labels) = tf.keras.datasets.fashion_mnist.load_data()
    # see the data
    print("\n train_data shape: ", train_data.shape)# (60000, 28, 28) 60000 samples of 28x28 images
    #print("\n train_data shape: ", train_data[0].shape)# (28, 28) 28x28 image
    print("\n train_labels shape: ", train_labels.shape)# (60000,) 60000 labels
    #print("\n train_labels shape: ", train_labels[0].shape)#label
    print("\n test_data shape: ", test_data.shape)# (10000, 28, 28) 10000 samples of 28x28 images
    print("\n test_labels shape: ", test_labels.shape)# (10000,) 10000 labels
    print("\n trainind data :", train_data[0])
    print("\n trainind label :", train_labels[0])
    plt.imshow(train_data[10], cmap=plt.cm.binary)
    plt.show()
    print("\n label of the image 10 : ", train_labels[10])

    # link label number to a name
    class_names = ["T-shirrt/top", "Trouser", "Pullover", "Dress", "Coat", "Sandal", "shirt", "Sneaker", "Bag", "Ankle boot"]
    plt.figure(figsize=(10,10))
    for i in range(9):
        ax = plt.subplot(3, 3, i+1)
        random_index = random.choice(range(len(train_data)))
        plt.imshow(train_data[random_index], cmap=plt.cm.binary)
        plt.title(class_names[train_labels[random_index]])
    plt.show()
    # looking at the data, is the function separating these classes is lienar ? 

    # Let's build a model
    # 2:30 in the video
    # Multiclass classification: softmax activation function and n_classes-1 neuron a the last layer etc..

    # Neural network likes data to be scaled (or normalized) (so data between 0 and 1)
    train_data = train_data / train_data.max() #255
    test_data = test_data / test_data.max()

    # a. Build model
    #model_multiclass = tf.keras.Sequential([
    #    tf.keras.layers.Flatten(input_shape=(28,28)),# Need to fit the 28 * 28 pixel images.
    #    tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
    #    tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
    #    tf.keras.layers.Dense(len(train_labels), activation=tf.keras.activations.softmax)# last layer is len(train_labels) because the output is one per label (hat, dress, ....), also the activation function for the output is not the same, softmax for multiclass classification
    #])
    # To understand Flatten layer
    #flatten_model = tf.keras.layers.Flatten(input_shape=(28,28))
    #print("\nflatten_model.output_shape) # it is (None, 724) = 28*28, you need to flatten your data before giving it to give to a layer (sometimes does it automatically)")
    # b. Compile model
    #model_multiclass.compile(loss=tf.keras.losses.SparseCategoricalCrossentropy,# Changed from binary to SparseCategoricalCrossentropy (CategoricalCrossentropy needs onehot representation, SparseCategoricalCrossentropy takes intergers)
    #                optimizer=tf.keras.optimizers.Adam(),
    #                metrics=["accuracy"])
    # c. fit the model
    #history = model_multiclass.fit(train_data,train_labels,epochs=10, validation_data=(test_data, test_labels), verbose=1)# added validation_data to also test our model afterwards

    #2:55 in video 

    # See the model history
    #pd.DataFrame(history.history).plot(title="data loss curves")
    #plt.show()

    # Finding the ideal learning rate

    # Set the random seed
    tf.random.set_seed(42)

    # Create model
    #I. Create the learning rate callback
    lr_scheduler = tf.keras.callbacks.LearningRateScheduler(lambda epoch: 1e-3 * 10**(epoch/20))

    # a. Build model
    model_multiclass2 = tf.keras.Sequential([
        tf.keras.layers.Flatten(input_shape=(28,28)),# Need to fit the 28 * 28 pixel images.
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
        tf.keras.layers.Dense(4, activation=tf.keras.activations.relu),
        tf.keras.layers.Dense(len(train_labels), activation=tf.keras.activations.softmax)# last layer is len(train_labels) because the output is one per label (hat, dress, ....), also the activation function for the output is not the same, softmax for multiclass classification
    ])
    # b. Compile model
    model_multiclass2.compile(loss=tf.keras.losses.SparseCategoricalCrossentropy,# Changed from binary to SparseCategoricalCrossentropy (CategoricalCrossentropy needs onehot representation, SparseCategoricalCrossentropy takes intergers)
                    optimizer=tf.keras.optimizers.Adam(),
                    metrics=["accuracy"])

    # c. fit the model
    history = model_multiclass2.fit(train_data,train_labels,epochs=10, validation_data=(test_data, test_labels), callbacks=[lr_scheduler], verbose=1)# added validation_data to also test our model afterwards
    #model_multiclass2.summay()

    # II. compare the lr curves with the loss curve to find the ideal
    # Plot the history
    pd.DataFrame(history.history).plot(figsize=(10, 7), xlabel="epochs")
    plt.title("model_works_nonlinear loss curves")
    plt.show() #the green lr is exponential because it starts with 1e-4 and increasing by 10**(epoch/20) every epoch
    # We can't really see the link bewteen lr value and loss, let's plot this
    lrs = 1e-3 * (10 ** (tf.range(10)/20)) #10 because we did 10 epochs
    print("\n len(lrs) : ", len(lrs), ", same number of epochs") #same number of epochs
    plt.figure(figsize=(10,7))
    plt.semilogx(lrs, history.history["loss"])# plot with log on th x axis
    plt.xlabel("Learning Rate")
    plt.ylabel("Loss")
    plt.title("Learning rate vs Loss")
    plt.show() # We want the lr value wherev the loss is the lowest. But we don't want instability in the learning, so we want the lr value where the loss curve is still decreasing but not flat (going up and down).
    # let's maybe take 0.001, we are using Adam optimizer and the default lr of Adam is acctually 0.001, so we don't need to change it XD.

    # d. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Evaluate !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    loss, accuracy = model_multiclass2.evaluate(test_data, test_labels, verbose=0) # These are good infos, I am lazy let's just see the confusion matrix metric
    
    # Confusion matrix metrix
    # Make predictions
    y_probabilities = model_multiclass2.predict(test_data) # X is data, VERY IMPORTANT TO USE THE SAME DATA IT WAS TRAINNED ON (if normalized keep the normalized verion of the data)
    print("\n y_probabilities[:5] : ", y_probabilities[:5]) # it is an array of probabilities for each class
    #print("\n y_probabilities shape : ", y_probabilities.shape)
    # each y_probabilities[i] is an array of 10 probabilities (one per class), we need to get the index of the highest probability
    y_preds = tf.argmax(y_probabilities, axis=1) # get the index of the highest probability
    print("\n y_preds[:10] : ", y_preds[:10]) # these are the predicted labels for each epoch.
    make_confusion_matrix(test_labels, y_preds, classes=class_names, figsize=(20,20), text_size=15)

    # Picks a random image, plots it and labels it with a prediction and truth label
    # Load the data again because the data was normalized to train the model 
    #(train_data, train_labels), (test_data, test_labels) = tf.keras.datasets.fashion_mnist.load_data()
    #plot_random_image(model_multiclass2, test_data, test_labels, class_names) # This function doesn't work need to fix it :(
    
    # See input output shapes of each layers
    #plot_model(model_multiclass2, show_shapes =True)
    pass

def plot_random_image(model, images, true_labels, class_names):
    """
    Picks a random image, plots it and labels it with a prediction and truth label
    3:30 in the 2nd video
    
    :param model: Description
    :param images: Description
    :param true_labels: Description
    :param class_names: Description
    """
    # set up a random interger
    i = np.random.randint(0, len(images)) # get a random image index in the data set

    # Create predictions and targets
    target_image = images[i]
    pred_probabilities = model.predict(target_image.reshape(1, 28, 28))
    pred_label = class_names[tf.argmax(pred_probabilities, axis=1)]
    true_label = class_names[true_labels[i]]

    # plot the image
    plt.imshow(target_image, cmap=plt.cm.binary)
    # Change the title colour if the prediction is good or not
    if pred_label == true_label:
        color = "green"
    else:
        color = "red" 
    # Add xlabel information (prediction/true label)
    plt.xlabel("Pred: {} {:2.0f}% (True : {})".format(pred_label, 100*tf.reduce_max(pred_probabilities), true_label), color=color)
    plt.show()
    
    pass

def make_confusion_matrix(y_true, y_pred, classes=None, figsize=(10,10), text_size=15):
    """
    Docstring for make_confusion_matrix
    See before in the code in function More_evaluation_Methodes to see another example.
    
    :param y_true: Description
    :param y_pred: Description
    :param classes: Description
    :param figsize: Description
    :param text_size: Description
    """

    # Create confucion matrix
    cm =confusion_matrix(y_true, y_pred) #y_true = y_test and y_preds = model_x.predict(X_test)
    print("\n\n",cm)
    # !!!!!!!!!!!!!!!!!!!!!!!Make a pretty confudion matrix 🥰!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    cm_normalized = cm.astype("float") / cm.sum(axis=1)[:, np.newaxis] # normalize our confusion matrix
    n_classes = cm.shape[0]
    # prettify
    fig, ax = plt.subplots(figsize=figsize)
    cax = ax.matshow(cm, cmap=plt.cm.Blues)#don't confuse cm confusion matrix with the plt.cm color map
    fig.colorbar(cax)
    # Set labels to be classes

    if classes:
        labels = classes
    else:
        labels = np.arange(cm.shape[0])

    #Label the axis
    ax.set(title="Confusion Matrix", 
           xlabel="Predicted labels", 
           ylabel="True Label", 
           xticks=np.arange(n_classes), 
           yticks=np.arange(n_classes), 
           xticklabels=labels, 
           yticklabels=labels)
    
    # Set x-axis labels to bottom
    ax.xaxis.set_label_position("bottom")
    ax.xaxis.tick_bottom()
    # Adjust label size
    ax.yaxis.label.set_size(text_size)
    ax.xaxis.label.set_size(text_size)
    ax.title.set_size(text_size)

    # Set threshold for different colours
    threshold = (cm.max() + cm.min()) / 2. 
    # Plot the text on each cell
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, f"{cm[i, j]} ({cm_normalized[i, j]*100:.1f}%)",
                 horizontalalignment="center",
                 color="white" if cm[i, j] > threshold else "black",
                 size=15)
    plt.show()
    # End of !!!!!!!!!!!!!!!!!!!!!!!Make a pretty confudion matrix 🥰!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    pass

def plot_decision_boundary(model, X, y):
    #plot the decision boundaries created by a model prediction on X 9:50 in video

    # Define the axis boundaries of the plot and create a meshgrid
    x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() +0.1 #0.1 to give a little bit of marging
    y_min, y_max = X[:, 1].min() - 0.1, X[:, 1].max() +0.1 #0.1 to give a little bit of marging
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100),
                         np.linspace(y_min, y_max, 100)) # linspace give envenely numbers in the interval
    
    # Create X value (we're giong to ,make predictions on these)
    x_in = np.c_[xx.ravel(), yy.ravel()] # stack 2D arrays together, to create x,y coordinates creating shape (N, 2).

    # Make predictions
    y_pred = model.predict(x_in)

    # check for multiclass
    if len(y_pred[0]) > 1:
        print("doing multiclass classification")
        # We have to reshape our prediction to get them ready for plotting
        y_pred = np.argmax(y_pred, axis=1).reshape(xx.shape)
    else:
        print("doing binary classification")
        # We have to reshape our prediction to get them ready for plotting
        y_pred = np.round(y_pred).reshape(xx.shape)

    # Plot the decision boundaries
    plt.contour(xx, yy, y_pred, cmap=plt.cm.RdYlBu, alpha=0.7)
    plt.scatter(X[:, 0], X[:, 1], c=y, s=40, cmap=plt.cm.RdYlBu)
    plt.xlim(xx.min(), xx.max())
    plt.ylim(yy.min(), yy.max())
    pass

def Get_Tensor_Info(tensor):
    print("Tensor Info:")
    print(" - Shape:", tensor.shape)
    print(" - Dtype:", tensor.dtype)
    print(" - Num of Dimensions:", tensor.ndim)
    pass
    
def main():
    # Check TensorFlow version
    print("TensorFlow Version:", tf.__version__)

    #learn_basics()
    #Neural_Network_Regression()
    #Larger_Regression_Example()
    #Neural_Network_Classification()
    #non_linear()
    #experiment_with_linear_non_linear_data()
    #More_evaluation_Methodes()
    Multiclass_classification()
    

    pass

if __name__ == "__main__":
    main()

### Conclusion notes, what to remember

## Common ways to improve a deep model:
    # Adding layers, if underfitting or the problem is complex or Simple models can’t capture the structure of the data. Deeper models learn features in stages.
    # Each layer builds on the previous one. Depth = feature hierarchy (More parameters → Higher risk of overfitting)

    # Increase the number of hiddenunits, if underfitting or Training error is high or You want more capacity within the same depth 
    #1,000 neurons can memorize very fine details. But all neurons are working at the same level of abstraction, Width = ability to fit complexity. (More parameters → higher overfitting risk)

    # Change the activation functions, if Training is slow or unstable or Output requirements change e.g., probabilities vs real values (can dramatically affect convergence and accuracy.)
        #ReLU / Leaky ReLU: Faster training, reduces vanishing gradients
        #Sigmoid / Tanh: Smooth outputs but prone to vanishing gradients
        #Softmax (output layer): Produces class probabilities
        #Linear (output layer): Used for regression

    # Change the optimization funtion, loss is not decreasing properly, training is unstable (optimizer affects speed, stability)
        #SGD : Simple, stable, but slow
        #SGD + Momentum: Faster, smoother convergence
        #Adam: Fast, adaptive, works well in most cases
        #RMSprop: Good for recurrent or noisy problems

    # Change the learning rate, if it is too high training diverges or becomes unstable, if too low, it's very slow and may get stuck

    # Fitting more data, use when the model overfits so training accuracy high, validation accuracy low

    # Fitting for longuer, use when the model hasn’t converged yet for the loss. It is often paired with early stopping to avoid overfitting

    #(
    #Simple analogy
    #📚 Reading a book
    #More layers: You understand letters → words → sentences → meaning
    #More neurons: You memorize more sentences, but still don’t understand the story better)
    #)

## See on the internet usual models for Binary classification, Multiclass classification, Regression problems etc.
    # Binary classification: sigmoid activation function and 1 neuron a the last layer etc..
    # Multiclass classification: softmax activation function and n_classes-1 neuron a the last layer etc..

## The 3 datasets
    # Training dataset (learning)
    # Validation dataset (practical exam)
    # Test dataset (final exam)

## Metrics in training the model, to see if it works well
    # Some metrics:
    # Accuracy, default for classification problems
    # Precision, more precision leads to less false positive
    # Recall, higher recall leads for less false negative (but often less false negative => more false positive and the reverse)
    # F1-score, a combinasion of both precision and recall, usually good for classification problems
    # Confusion matrix, build your own metric (you could use the sklearn.metrics.confudion_matrix())
    # Classification reports (from scikit-learn)
