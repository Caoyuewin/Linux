/*
 *  进程退出的8种方式：
 *  正常：
 *      1. return
 *      2. 调用exit
 *      3. 调用_exit
 *      4. 最后一个线程从启动例程返回
 *      5. 从最后一个线程调用pthread_exit函数
 *  异常：
 *      1. 调用abort
 *      2. 接到一个信号
 *      3. 最后一个线程对取消请求作出响应
 * */


//1. 退出函数
//_exit立即进入内核
//  void exit(int status);
//_exi先执行一些清理处理，然后返回内核
//  void _exit(int status);
