type-storage
============

type-storage is a simple C++ library that is meant to provide containers
for situations where different types need to be stored in the same container, 
for convenience. This is often mostly useful in projects with deep roots in 
template meta-programming.

Header-only
...........

The library itself is header-only so essentially to use it you just
have to clone the repository and setup the right include paths in the
project where you would like to use it.

The library uses c++11 features such as variadic templates, so you
need a relatively recent compiler to use it.

Unit testing
------------

The unit tests for the library are located in the ``test/src`` folder.

We use the Google Unit Testing Framework (gtest) to drive the unit
tests. To build the tests run:

::

    python waf configure
    python waf

Depending on the platform you should see a test binary called
``type_storage_tests`` in (extension also depends on operating system
e.g. ``.exe`` for windows):

::

    build/platform/test/

Where ``platform`` is typically is either linux, win32 or darwin
depending on your operating system.


License
-------
The library is released under the BSD license see the LICENSE.rst file
