News for type-storage
=============

This file lists the major changes between versions. For a more detailed list of
every change, see the Git log.

Latest
------
* Minor: Now ignoring ``const`` and ``volatile`` qualifiers on types.
* Patch: Fixed bug in const version of ``type_storage::baget()``

2.1.0
-----
* Added baget function to get an object based on a specified base type.

2.0.2
-----
* Added const get function

2.0.1
-----
* Added const getter function for wrapped type storage

2.0.0
-----
* Change type_storage to raw tuple and made type_storage get() function a free function within the type_storage namespace

1.0.0
-----
* Initial release of the type-storage library.
* Included examples in example/ directory
