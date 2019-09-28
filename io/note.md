
#### #define的深入用法

1. `#define process_str1(instr) #instr`

    `char str[] = process_str1(abc);`会预处理成`char str[] = "abc";`
    
2. `#define process(x) x`

    `int j = process(i);`会预处理成`int j = i;` 这里`i`是一个变量，否则会报错

3. `#define process_variable(x) a##x`

    `int x = process_variable(1);`会预处理成`int x = a1;` 这里`a1`是一个变量，否则会报错



#### 进程创建时的初始默认文件描述符

标准输入 -> 0(STDIN_FILENO)

标准输出 -> 1(STDOUT_FILENO)

标准错误 -> 2(STDERR_FILENO)

