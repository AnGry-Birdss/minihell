#include "../../include/minishell.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	return (sign * result);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		tmp;

	len = (n <= 0) ? 1 : 0;
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (n)
	{
		str[--len] = (n < 0 ? -(n % 10) : n % 10) + '0';
		n /= 10;
	}
	return (str);
}
