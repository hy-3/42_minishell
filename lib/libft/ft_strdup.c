#include "libft.h"

/**
 * @brief Allocates enough memory for a copy of [s1].
 *
 * @param s1(const char *): Pointer to string to be copied.
 * @return (char *): Pointer to copied string.
 */
char	*ft_strdup(const char *s1)
{
	char	*res;
	int		count;

	count = 0;
	while (s1[count] != '\0')
		count++;
	res = (char *) malloc((count + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	count = 0;
	while (s1[count] != '\0')
	{
		res[count] = s1[count];
		count++;
	}
	res[count] = '\0';
	return (res);
}
