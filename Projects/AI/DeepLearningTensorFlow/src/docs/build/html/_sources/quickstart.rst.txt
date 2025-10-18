Quick Start Guide
===============

This guide will help you get started with the basics of TensorFlow.

First Steps
----------

1. Import TensorFlow:

   .. code-block:: python

      import tensorflow as tf

2. Check TensorFlow Version:

   .. code-block:: python

      print(f"TensorFlow version: {tf.__version__}")

Basic Operations
--------------

Here's a simple example of creating and manipulating tensors:

.. code-block:: python

   # Create tensors
   x = tf.constant([[1, 2], [3, 4]])
   y = tf.constant([[5, 6], [7, 8]])

   # Perform operations
   z = tf.matmul(x, y)  # Matrix multiplication
   print(z)