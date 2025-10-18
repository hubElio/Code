
import tensorflow as tf
import numpy as np

def Get_Tensor_Info(tensor):
    print("Tensor Info:")
    print(" - Shape:", tensor.shape)
    print(" - Dtype:", tensor.dtype)
    print(" - Num of Dimensions:", tensor.ndim)


def main():
    # Check TensorFlow version
    print("TensorFlow Version:", tf.__version__)

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
    pass

if __name__ == "__main__":
    main()