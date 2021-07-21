# Assignment 0x02 (Total 50 pt)

## Assignment set-up and connection information.

We have two test servers set-up for this assignment. One for x86 and another for
ARM (Raspberry Pi).  The student will log-in with different accounts for
different parts of the assignment. 

```
10.176.150.47 CS6332-ARM
10.176.150.50 CS6332-x86
```

```bash
# For part 1
$ ssh assign0x2-p1@CS6332-{ARM|x86}
assign0x2-p1@CS6332-{ARM|x86} password:      # type in "guest"
...
# For part 2
$ ssh assign0x2-p2@CS6332-{ARM|x86}
assign0x2-p2@CS6332-{ARM|x86} password:      # type in "guest"
...
# For part 3
$ ssh assign0x2-p3@CS6332-{ARM|x86}
assign0x2-p3@CS6332-{ARM|x86} password:      # type in "guest"
...
```

### Assignment binaries

Assignment binaries are available for download. Download and study it from a
local machine first. Once you figure out how to solve, you can log in to the
submission server to get flags for each part.

#### X86 Binaries

* [part0x00_x86]
* [part0x01_x86]
* [part0x02_x86]
* [part0x03_x86]

#### ARM Binaries

* [part0x00_arm]
* [part0x01_arm]
* [part0x02_arm]
* [part0x03_arm]

## Part 0: Warm-up

Log in to submission server and try the following


* CS6332-x86 
  ```bash
  ssh assign0x2-p0@10.176.150.50
  assign0x2-p0@10.176.150.50's password:

  ....

  Last login: Wed Oct  7 12:12:17 2020 from 10.50.126.205
  Type-in your NETID: mynetid
  Welcome! mynetid
  assign0x2-p0@cs6332-x86:~$ ./part0x00
  CS6332 Crackme Level 0x00
  Any integer larger than 0:100
  Password OK :)
  your netid is mynetid, turn in the following hash value.
  98459e2c4552af94349e6523b3f54912
  assign0x2-p0@cs6332-x86:~$
  ```

* CS6332-arm
  ```bash
  $ ssh assign0x2-p0@10.176.150.47
  assign0x2-p0@10.176.150.47's password:
  ...

  Type-in your NETID: mynetid
  Welcome! mynetid
  assign0x2-p0@cs6332-arm:~ $ ./part0x00
  CS6332 Crackme Level 0x00
  Any integer larger than 0:123
  Password OK :)
  your netid is mynetid, turn in the following hash value.
  85ce9bf4f7b7a7ac442182e1dc7a5e3f
  assign0x2-p0@cs6332-arm:~ $
    ```  

## Part 1 (5pt + 5pt): Control flow hijacking

### Preparation

Download *part0x01_{x86|arm}* to your local Linux host (Linux and ARM) to
analyze first. Once you get ready, you can login to your submission server to
confirm your input and get your hash value.

### Description

In this assignment, we are going to hijack the control flow of *assign_0x2_p1*
binary by overwriting the instruction pointer (EIP for x86, CP for arm). As a
first step, let's make it prints out "Password OK :)" without providing correct
answer to the question.

On a successful exploitation, the program will run `solve` program which will
ask you to provide your NetID to generate your hash value. For this part of
assignment, please submit the followings

* Your *input* to exploit the buffer overflow vulnerability

## Part 2 (10 pt + 10 pt): Jump to your own shellcode

### Preparation

Download *part0x02_{x86|ARM}* to your local (Linux) host to analyze first.
Once you get ready, you can login to your submission server to confirm your
input and get your hash value. Please, check its binary to ensure stack section
(*GNU_STACK*) is in `RWE` permission which mean you can write and run machine
instructions  from stack.

```bash
$ readelf -W -l ./part03_x86|grep STACK
  GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RWE 0x10
```

From this part, you will save your payload as *a file* and provide it as an
argument to the vulnerable program (part02_x86).

    echo -ne "payload\xef\xbe\xad\xde" > /tmp/myinput
    ./assign_0x1_p2 /tmp/myinput
    CS6332 Crackme Level 0x02
    Invalid Password!

> :warning: **Note**
    The submission server (and account for each part) is shared by the entire
    class, please try to use a unique filename for your input to avoid potential
    conflict.

### Description

From this assignment, You will craft an input
to overwrite the stack with shellcode and transfer control the beginning of
shellcode as *main()* function returns. You can google for *execve()
shellcode x86* that would eventually run */bin/sh* command for you.

Create an input that would run *shellcode* and subsequently give */bin/sh*
prompt. Please note that different lengths of environment variables + arguments
can also vary the resulting stack address widely from computer to computer. A
way to mitigate this issue is doing a NOP slide (see
https://old.liveoverflow.com/binary_hacking/protostar/stack5.html).

Upon a successful exploitation, you will see the shell prompt as below.

    assign0x2-p3@cs6332-arm:~ $ ./part0x03/tmp/input2
    CS6332 Crackme Level 0x02
    Invalid Password!
    $ id
    uid=1002(part02_x86) gid=1004(part02_x86_pwn) groups=1004(part02_x86_pwn),1003(part02_x86)
    $ ./solve
    Your NetID:   # input your NetID here.

> :warning: **Info**:
    Even with ASLR, stack location may vary slightly due to environment
    variables. You may consider padding your payload with sled (NOP instruction) to
    make your exploit robust.


> :warning: **Info**:
    if you want to make your environment as similar as possible, prepend
    `env -i` before your program command, i.e. `env -i ./part02_x86`.


### Output to submit

On successful exploitation, the program will run the `solve` program, which
will ask you to provide your NetID and return your hash value. For this part of
the assignment, please submit the followings

  1. Your *input* to exploit the buffer overflow vulnerability and deliver shellcode payload.
  2. Hash value generated by *solve* as a return for your NetID.

## Part 3 (10 pt + 10 pt): Return-to-libc

### Preparation

Download *part0x03_{x86|ARM}*
to your local (Linux) host to analyze first. Once you get ready, you can
login to your submission server to confirm your input and get your hash
value. This time, your stack is not executable anymore. Please check its
binary to ensure stack section (*GNU_STACK*) is in `RW` permission which mean
you can overwrite a stack, but cannot run any code from there.
```
$ readelf -W -l ./*part0x03_x86*|grep STACK
  GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RW  0x4
```

### Description

From this part of the assignment, you can still hijack the control by
overwriting the return address, but you don’t know where to transfer the
control, to run the desired command (say */bin/sh*) using *system()* function
provided by Glibc library. For its usage, please check out `man -s 3 system`.

Please write an input that would overwrite the return address of *main()* and
transfer the control aa *main()* function returns. You need to craft your
payload to call *system()* having a string (*/bin/sh*) as the first function
argument.

#### *system()* function example

The following snippet would give you a command prompt.

```bash
$ cat << EOF > /tmp/system.c
#include <stdlib.h>
// system.c
int main() {
    system("/bin/sh");
}
EOF

$ gcc /tmp/system.c
$ ./a.out
$ whoami
part03_x86
```

## Submission

Fill in the required entries form [submission.md] and submit to eLearning. 

----
[part0x00_x86]:binaries/part0x00_x86
[part0x01_x86]:binaries/part0x01_x86
[part0x02_x86]:binaries/part0x02_x86
[part0x03_x86]:binaries/part0x03_x86


[part0x00_arm]:binaries/part0x00_arm
[part0x01_arm]:binaries/part0x01_arm
[part0x02_arm]:binaries/part0x02_arm
[part0x03_arm]:binaries/part0x03_arm

[submission.md]:submission.md