# Assingment 2.1

## General Details

- [Problem statement](https://hello.iitk.ac.in/sites/default/files/eso207a21/assignments/problems/ebf2606491e312c0dca1bc591f5929467fa0b714d8927372dfe32d570b91e6a0_Programming_Assignment_2_1.pdf)
- [Solution](two3TreeMerge.cpp)
- [Report](Assignment_2_1.pdf)

## How to run
To get the output specified in the problem statement, run: 

```bash
cd $THIS_DIRECTORY
g++ two3TreeMerge.cpp && ./a.out 
## or give it a file name
g++ two3TreeMerge.cpp -o two3TreeMerge && ./two3TreeMerge
```

**Custom sets to test Program**  
Alternatively, you can invoke `customTest` function from `main`.  
Updated `main` fucntion should look like this:
```cpp
int main() {
	// test();
	customTest();
	return 0;
};
```
Then run the same bash commands as above.
