#define QUEUE_SIZE 50000
int q[QUEUE_SIZE];
void monotonousQueue(int *arr, int len, int k)
{
    int front = 0, rear = 0;
    for(int i = 0; i < len; i++)
    {
        /*
        如果队列中存在元素，且当前需要入队尾的元素小于等于队列尾部元素，
        则让队尾元素出队，直到队列空或者需要入队尾的元素大于队尾元素。
        */
        while(front < rear && arr[q[rear]] >= arr[i])
            rear--;
        /*将下标存入队尾*/
        q[rear++] = i;

        /*限制范围*/
        while(q[front] < i - k)
            front++;
    }
}