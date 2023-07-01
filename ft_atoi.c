/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashaboulogne <sashaboulogne@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:58:41 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/01 18:20:05 by sashaboulog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
    while (ft_isdigit(str[i]) == 0)
    {
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
            i++;
        while (str[i] == '+' || str[i] == '-')
        {
            if (str[i] == '-')
                sign *= -1;
            i++;
        }
        while (ft_isalpha(str[i]))
            i++;
    }
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res * sign);
}