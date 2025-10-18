Installation Guide
=================

Prerequisites
------------

* Python 3.9 or later
* pip (Python package installer)
* Virtual environment (recommended)

Installation Steps
----------------

1. Create and activate a virtual environment:

   .. code-block:: bash

      python -m venv .venv
      # On Windows
      .\.venv\Scripts\activate
      # On Unix or MacOS
      source .venv/bin/activate

2. Install TensorFlow:

   .. code-block:: bash

      pip install tensorflow

3. Verify Installation:

   .. code-block:: python

      import tensorflow as tf
      print(tf.__version__)

Additional Dependencies
--------------------

For this project, you'll also need:

* NumPy
* Matplotlib
* Pandas

Install them using:

.. code-block:: bash

   pip install numpy matplotlib pandas