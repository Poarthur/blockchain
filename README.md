# Blockchain
Test task solution

## Compiling and building
In order to compile and build the solution, you can simply run **config.py** using the command:<br />
`> python3 config.py`<br />
This python script will install `cmake` and `conan` if they are not present on the machine. Also, after installation, unit tests will be automatically launched. If ***python3*** is not installed, `cmake`, `conan` and `c++17 compiler` should be installed manually. Then you need to create a directory for compilation:<br />
`> mkdir build`<br />
Download the libraries using the ***conan*** package manager:<br />
`> conan install . --build missing`<br />
Go to the build directory and generate a project file:<br />
`> cd ./build && cmake ..`<br />
or use a build system specific generator:<br />
`> cmake -G"Unix Makefiles" ..`<br />

## Testing
At the end of this description, I left the points that I simplified for writing this assignment. Including tests. I wrote tests for myself, used **googletest** and put everything in one place. But this did not affect their performance in any way. To run all the tests, after compiling, you need to run the **project_tests** program, it will be located next to the executable file in the
`build/bin/` directory:<br />
`> project_tests`<br />
If you need to run a specific test case, use the command:<br />
`> project_tests "--gtest_filter=Sha256.*"`<br />
A list of all available cases can be viewed with the<br />
`> project_tests --gtest_list_tests` command<br />

## Using
By default, after compilation, an executable file will also be created. Once launched, the program can create user files with keys and blocks. If you're interested in testing how data is written to and read from files, it's best to run the binary from a directory with write access.<br />
The program interface works through the input output stream, it is most convenient to run this in the console. To create new transactions, you need to **create users** (so that they have the keys to conduct these transactions). After that, execute a **coinbase** transaction for one or more users to top up their balance. Then you can make **transactions**. At any time, the block can be mined. Also in the menu there is an opportunity to change the mining difficulty (change the number of leading zeros in the hash sum) by default the difficulty is 4. The program can also show user blocks and blocks in a readable form.<br />
Example:<br />
```
Enter the appropriate number and press Enter:
1 Add new user
2 Add transaction
3 Add coinbase transaction
4 Show all users
5 Show all blocks
6 Show one block by index
7 Mine the block
8 Change mining difficulty
0 or any other to exit
Your choise is: 1
```

```
Write username: Tom Hanks
The user was successfully created!
```

```
3 Add coinbase transaction
Enter the username for which the transaction is being made:
Tom Hanks
Enter amount:
100.5
Transaction completed successfully!
```

```
2 Add transaction
Enter the name of the person making the transaction:
Tom Hanks
Enter the username for which the transaction is being made:
Jerry
Enter amount:
10.4
Transaction completed successfully!
```

```
5 Show all blocks
```

## What I simplified
1. Didn't use double hash
2. Proper test splitting
3. Removed MVC and hardcoded UI
4. Didn't connect codestyle alignment tools
5. Didn't connect cppcheck
6. Didn't include header precompilation
7. Didn't add CI<br />
Merkel's tree was left as a rudement, I also wanted to add it at first<br />
If any of this is needed, I can add
