#include <string.h>
#include <stdlib.h>
#include <stdio.h>

long long	ft_abs(long long num)
{
	if (num < 0)
		num = -1 * num;
	return (num);
}

char	*ft_itoa(long long n)
{
	char		*str;
	long long	i;
	long long	num;
	long long	size;

	i = 1;
	size = 2;
	num = n;
	while (num / i != 0 && size++ >= 0)
		i *= 10;
	str = calloc(size, 1);
	if (!str)
		return (NULL);
	str[0] = '0';
	size = 0;
	if (num < 0)
		str[size++] = '-';
	num = ft_abs(num);
	while (i >= 10)
	{
		i /= 10;
		str[size++] = '0' + num / i;
		num %= i;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*point;

	if (!s1 || !s2)
		return (NULL);
	len = strlen(s1) + strlen(s2);
	point = malloc(len + 1);
	if (!point)
		return (NULL);
	len = 0;
	while (s1[len++])
		point[len - 1] = s1[len - 1];
	len = 0;
	while (s2[len++])
		point[strlen(s1) + len - 1] = s2[len - 1];
	point[strlen(s1) + len - 1] = '\0';
	return (point);
}

char* decompose(long long n) {
    long long square = n * n;
    long long i = n - 1;
    char *result = strdup("]");
    long long iter = 1;
  
    while (square > 0 && i > 0)
    {
    	if (square >= (i*i))
		{
			square -= i * i;
			result = ft_strjoin(ft_itoa(i), result);
		}
		i--;
		if (square >= (i*i) && i > 0)
			result = ft_strjoin(",", result);
		if (i <= 0 && square > 0) {
			square = n * n;
			free(result);
			result = strdup("]");
			iter++;
			i = n - iter;
		}
    }
    result = ft_strjoin("[", result);
    return (result);
}