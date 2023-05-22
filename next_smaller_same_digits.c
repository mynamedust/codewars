#include <stdlib.h>

long long next_smaller_number(unsigned long long n){
    unsigned long long    size = 10;
    unsigned long long    result = n;
    int                    iter = 0;
    int                    *arr;

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
      iter = size;
    while (--iter >= 0)
    {
      int max = iter;
      if (iter < size - 1)
      {
        for (int j = size - 1; j > iter; j--)
        {
			if (arr[j] == 0 && iter == 0)
				continue ;
          	if (arr[j] < arr[iter] && ((max != iter) == (arr[j] > arr[max])))
            max = j;
        }
        if (max != iter && arr[max] < arr[iter])
        {
          int temp = arr[iter];
          arr[iter] = arr[max];
          arr[max] = temp;
          for (int i = iter + 1; i < size - 1; i++)
          {
            if (arr[i] < arr[i + 1])
            {
              int swap = arr[i];
              arr[i] = arr[i + 1];
              arr[i + 1] = swap;
              i = iter;
            }
          }
          break ;
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
    if (n == result)
      return (-1);
    return (result);
}