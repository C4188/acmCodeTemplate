/*自顶向下单调递减栈*/
#define STACK_MAXSIZE 50000
int s[STACK_MAXSIZE];
void monotonousStack(int *arr, int len)
{
    int top = 0;
    for(int i = 0; i < len; i++)
    {
        /*
        如果栈中存在元素，且当前需要入栈的元素小于等于栈顶元素，
        则弹出栈顶元素，直到栈空或者需要入栈的元素大于栈顶元素。
        */
        while(top > 0 && arr[s[top]] >= arr[i])
            top--;

        /*将下标入栈*/
        s[top++] = i;
    }
}