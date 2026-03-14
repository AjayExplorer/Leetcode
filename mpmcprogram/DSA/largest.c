#include<stdio.h>

int main()
{
    int n, i, j, temp;
    
    printf("Enter the array size: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter the elements:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(a[i] < a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    printf("The largest element is: %d", a[0]);

    return 0;
}