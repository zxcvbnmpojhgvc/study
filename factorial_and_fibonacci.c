// int stk[100]; // stack
// int size = 100;    // size of stack
// int ptr = -1; // store the index of top element of the stack
// // push x to stack
// void push(int x){
//     if(ptr==size-1){
//         printf("OverFlow \n");
//     }
//     else{
//         ++ptr;
//         stk[ptr] = x;
//     }
// }
// // return top element of the stack
// int top(){
//     if(ptr==-1){
//         printf("UnderFlow \n");
//         return -1;
//     }
//     else{
//         return stk[ptr];
//     }
// }
// // remove top element from the stack
// void pop(){
        
//     if(ptr==-1){
//         printf("UnderFlow \n");
//     }
//     else{
//         --ptr;
//     }
// }
// // check if stack is empty or not
// int isempty(){
//     if(ptr==-1)
//         return 1;
//     else
//         return 0;
// }
// int main() {
//     int i, n;
    
//     printf("Enter a number: ");
//     scanf("%d", &n);
    
//     push(1);
//     for(i=2;i<=n;++i){
//         push(top() * i);
//     }
//     printf("Factorial: %d", top());
//     return 0;
// }




#include<stdio.h>
int fib(int n)
{
    int f[n+2];
    int i;
    f[0] = 0;
    f[1] = 1;
    for (i = 2; i < n; i++){
        f[i] = f[i-1] + f[i-2];
        printf("%d ", f[i]);
    }
}
int main ()
{
int n = 10;
fib(n);
getchar();
return 0;
}


