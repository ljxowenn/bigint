# BigInt
## Introduction
This project is a C++ class for arbitrary-precision integers (bigint). This class can be view as an extension of the usual C++ sined integer types and will allow signed integers of unlimited range (limited only by the computer's memory).

Projet conssit of three files:
`bigint.hpp`: A header file containing the entire funciton defined for the class.
`demo.cpp`: A program that contains all the code implementaion of the functions defined in header file.
`README.md`: The ducumentation of the class.

## Implementation
The basic algorithms idea for the operations in the program is that, all calculations follow basic mathematical methods, just like what we did on draft paper in real world. The operator function only work on the vecotr that represent the positive integers, the sign of the result will defined based on the sign of the argument and the specific operations (e.g (-4) - 6， we will consider it as - (4 + 6), so the operator only working on the positive 4 and 6, and set `-` as the sign of the result).
### Value in `bigInt`
The class we defined contains two private variable: `sign` stored the sign of the number as `+` or `-` as char type; `value` stored the value of the number as a vector type, each element of vector stored each digit of the number, and in the opposite direction, which means the first element is last digit of the number.
### Addition
We calculate the sum of each digit of the two numbers in order starting from the last digit. The sum will add to the each digit of the result in same order. If current sum is larger than 9, we store the ones place into result, and make tens place as carry, the carry will add to the next sum and so on, until we loop through every digits and there is no carry left. if one number is longer than another, the extra part will consider as 0 when calculate sum.
### Subtraction
Calculate the difference of each digit of the two numbers and store the diff to the result as same as addition. But this time if diff is smaller than 0, we make borrow to 1 otherwise 0, and will subtract it in from next diff and so on. Also consider the extra part of longer number as 0.
### Multiplication
Start from the ones place of the right hand side number, times each digit of left hand side number from right to left to get a product result. We doing this for every digit in right hand side number. After the first product result, every time we get a result will need move it one digit to left so on. And we add every product to get the sum as final result. When doing the addition, no digit position will consider as 0.
### Comparison
Frist compare the size and sign of the bigint, then lopp through the `value` of the bigint from last element to the first (since we stored the value in opposite order), and compare each element.

## Testing Example
```cpp
    // Test Constructor with default
    bigInt defaultInt;
    cout << "Default Constructor (0): " << defaultInt << "\n";

    // Test Constructor with int64_t
    bigInt int64(-9223372036854775807); // 
    cout << "Constructor with int64_t (" << int64 << "): " << int64 << "\n";

    // Test Constructor with string 
    bigInt stringInt("100000000000000000000"); 
    cout << "Constructor with string (" << stringInt << "): " << stringInt << "\n";
    bigInt invalidString("-000010000");
    cout << "Constructor with 0 leading string (" << invalidString << "): " << invalidString << "\n";

    // Test Constructor with = operator
    bigInt opInt;
    bigInt opString;
    opInt = 123445;
    opString = "-64443221";
    cout << "Constructor with = (" << opInt << "), (" << opString << "): " << opInt << ", " << opString << "\n";

    // Test Addition
    bigInt sum = int64 + stringInt;
    cout << "Addition (" << int64 << " + " << stringInt << "): " << sum << "\n";
    
    // Test Subtraciton
    bigInt difference = stringInt - int64;
    cout << "Subtraction (" << stringInt << " - " << int64 << "): " << difference << "\n";

    // Test Multiplication
    bigInt product = int64 * stringInt;
    cout << "Multiplication (" << int64 << " * " << stringInt << "): " << product << "\n";

    // Test Negation
    bigInt negated = -stringInt;
    cout << "Negation (" << stringInt << "): " << negated << "\n";

    // Test Comparison
    cout << "Comparison (" << int64 << " == " << stringInt << "): " << (int64 == stringInt) << "\n";
    cout << "Comparison (" << int64 << " != " << stringInt << "): " << (int64 != stringInt) << "\n";
    cout << "Comparison (" << int64 << " < " << stringInt << "): " << (int64 < stringInt) << "\n";
    cout << "Comparison (" << int64 << " > " << stringInt << "): " << (int64 > stringInt) << "\n";
    cout << "Comparison (" << int64 << " <= " << stringInt << "): " << (int64 <= stringInt) << "\n";
    cout << "Comparison (" << int64 << " >= " << stringInt << "): " << (int64 >= stringInt) << "\n";
```
Here is the output of the testing script.
```
Default Constructor (0): +0
Constructor with int64_t (-9223372036854775807): -9223372036854775807
Constructor with string (+100000000000000000000): +100000000000000000000
Constructor with 0 leading string (-10000): -10000
Constructor with = (+123445), (-64443221): +123445, -64443221
Addition (-9223372036854775807 + +100000000000000000000): +90776627963145224193
Subtraction (+100000000000000000000 - -9223372036854775807): +109223372036854775807
Multiplication (-9223372036854775807 * +100000000000000000000): -922337203685477580700000000000000000000
Negation (+100000000000000000000): -100000000000000000000
Comparison (-9223372036854775807 == +100000000000000000000): 0
Comparison (-9223372036854775807 != +100000000000000000000): 1
Comparison (-9223372036854775807 < +100000000000000000000): 1
Comparison (-9223372036854775807 > +100000000000000000000): 0
Comparison (-9223372036854775807 <= +100000000000000000000): 1
Comparison (-9223372036854775807 >= +100000000000000000000): 0
```
