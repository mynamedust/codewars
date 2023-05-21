#include <stdlib.h>
#include <stdio.h>

long long next_smaller_number(unsigned long long n){
    unsigned long long size = 10;
    unsigned long long result = n;
    int  *arr;

    for (int i = 0; i < size; i++)
    {
        if (i == 0 && n / size == 0)
          return (-1);
        if (i && n / size == 0)
        {
          size = i + 1;
          break ;
        }
		size *= 10;
    }
    arr = malloc(sizeof(int) * size);
    for (int i = size - 1; i >= 0; i--)
    {
      arr[i] = n % 10;
      n /= 10;
    }
	for(int i = size - 1; i > 0; i--)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			if (!(arr[i] == 0 && j == 0) && arr[i] < arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				j = i;
			}
		}
	}
    n = result;
    result = 0;
    for(int i = 0; i < size; i++)
    {
      result *= 10;
      result += arr[i];
    }
    free(arr);
    // if (n == result)
    //   return (-1);
    return (result);
}

int main()
{
	printf("%lld\n", next_smaller_number(907));
}