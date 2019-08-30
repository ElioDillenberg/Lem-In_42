#include "../incls/lem_in.h"
#include "../libft/libft.h"

/*
** This function will parse env->tu_tab to check wether or not we have found a "-1"
** if one has been found, it means we need to cut all the 
*/
int     cut_and_reset(t_env *env)
{
    int i;
    int j;      
    
    i = 0;
    while (i < env->nt_rm[1])
    {
        j = 0;
        while (j < env->nt_rm[1])
        {
            if (env->tu_tab[i][j] == -2)
                env->tu_tab[i][j] = 0;
            else if (env->tu_tab[i][j] == -1)
                env->tu_tab[i][j] = 1;
            j++;
        }
        i++;
    }
    env->tu_cut = 0;
    env->nb_path = 0;
    ft_path_lst_del(&(env->path_lst[env->cr_path]));
    env->path_lst[0] = NULL;
    // if (env->path_lst[0])
        // ft_memdel((void**)&(env->path_lst[0]));
    // ft_path_lst_del(&(env->path_lst[1]));
    ft_memdel((void**)&(env->path));
    if (!(env->path = ft_strnew(0)))
        return (-1);
    return (0);
}