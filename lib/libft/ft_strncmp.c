#include "libft.h"

/**
 * @brief Compare strings ([s1] and [s2]) with no more than [n] characters.
 * 
 * @param s1(const char *): Source string to compare
 * @param s2(const char *): Source string to compare
 * @param n(size_t): Number of char to compare
 * @return (int): Whenever the difference found, 
 *   they return char difference as int 
 *   which euqals to (s1's char - s2's char).
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((unsigned char) *s1 != '\0' && (unsigned char) *s2 != '\0' && n > 0)
	{
		if ((unsigned char) *s1 != (unsigned char) *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		n--;
	}
	if (n > 0)
		return ((unsigned char) *s1 - (unsigned char) *s2);
	return (0);
}
