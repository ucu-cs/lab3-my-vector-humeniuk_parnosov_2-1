# Lab work <mark>3</mark>: <mark>власне, my_vector та my_array + Smart pointers</mark>
Authors (team):
<br>[Denys Humeniuk](https://github.com/Gopyu1235)
<br>[Nazar Parnosov](https://github.com/Nazarious-ucu)

## Sources
While writing the code for the first part we were using std::array and std::vector documentation as one of sources of reliable information:
1. https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a00752_source.html
2. https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01115_source.html

While writing the code for the second part we were using std::unique_ptr, std::shared_prt and std::weak_prt documentation as one of sources of reliable information:
1. unique_ptr - https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a01404.html
2. shared_ptr & weak_prt - https://gcc.gnu.org/onlinedocs/gcc-4.6.0/libstdc++/api/a01033_source.html

## Prerequisites

gcc, CMake

### Compilation

```sh
./compile.sh --optimize-build --no-debug-build --remove-build-dirs
```

If there will bey_ any problems with running compile.sh, run following command in root directory:

```sh
dos2unix compile.sh
```
After it in /bin directory will be executable

### Usage

After compilation go to the /bin directory and run file with following command:

```bash
./my_array_vector
```

### Results array/vector

1) Result output for Debug mode:

```bash
= Testing functionality =
my_array tests passed;
my_vector tests passed
All tests passed!

= Time comparison =
1. my_array:
std::array: 3205 μs, sum=499999500000
my_array:  2993 μs, sum=499999500000

1. my_vector:
std::vector: 22501 μs, sum=499999500000
my_vector:   7279 μs, sum=499999500000
```

2) Result output for Release mode:

```bash
= Testing functionality =
my_array tests passed;
my_vector tests passed
All tests passed!

= Time comparison =
1. my_array:
std::array: 918 μs, sum=499999500000
my_array:  682 μs, sum=499999500000

1. my_vector:
std::vector: 3689 μs, sum=499999500000
my_vector:   2836 μs, sum=499999500000
```

### Result smart pointers

```bash
= Testing my_unique_ptr =
Car Audi created
Ptr1 name: Audi
Ptr1 validation:  0
Ptr2 name: Audi
Car Mercedes created
Car Audi destroyed
Ptr2 name: Mercedes
Ptr2 validation: 0

= Testing my_shared_ptr =
Car Porsche created
First use_count(): 1
Second use_count(): 2
Second model Porsche
After second is destroyed, first use_count(): 2
Car Porsche destroyed

= Testing my_weak_ptr =
Car Skoda created
Car use_count before lock: 1
locked car: Skoda
Car Skoda destroyed
After reset, trying to lock again:
Object destroyed
```

# Additional tasks
1) Made time comparison with std::array and std::vector
2) Smart pointers
