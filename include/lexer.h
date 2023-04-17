#include "libft.h"

typedef struct s_stpar
{
	int	len;
	int	l;
	int	r;
	int	quote;
}	t_stpar;

void		init_stpar(t_stpar *stpar, char *str);
void        add_cmd(t_list **lst, t_stpar *p, char *str, int n);
int             check(char cur, char adj_r, t_stpar p);
int			get_numdoll(char *str);