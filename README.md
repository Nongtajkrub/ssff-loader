# ssff-loader ℹ️

This project is currently in the very early stages of development. Please visit the [Progress](https://github.com/Nongtajkrub/ssff-loader#progress-) section to see the library’s current capabilities, and the [TODO](https://github.com/Nongtajkrub/ssff-loader#TODO-) section to learn about future planned features.

ssff-loader is a C library designed to load and write data to a custom file format I created, called ssff. Initially, I developed ssff-loader to store data about my classmates, which is why ssff stands for Simple Student File Format.

## FileFormat 📁

Here are 3 examples of what ssff format might look like in the future.

```
John:
    info:
        age: 0,
        id: 0;

Jim:
    info:
        age: 0,
        id: 0;
```

```
Friends:
    name1: "Joe",
    name2: "Jam",
    name3: "Mama";
```

```
Cars:
    momCar:
        working: false,
    dadCar:
        working: true;
```

## Progress 🗿

* Reading ssff file

## TODO 🥅

* A type system for ssff.
* Writting to a ssff file.
