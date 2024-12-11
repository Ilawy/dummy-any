# Container

a simple class that holds data of varoius types

##  Why
it's for using with a dynamic array of different elements

##  Features
*   can hold data of any type
*   can be printed in cout (by extending printable class)
*   The holded data can be freed (by setting `_free_` method) 
*   get the type of holded data (`type()` method)
*   cast the data directly (using `as<T>()` method)
*   check if `T` is a class and is inhereted by the holded data (using `isBaseOf<T>`)