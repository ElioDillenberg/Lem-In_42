#include "../incls/lem_in.h"
#include "../libft/libft.h"

/*
** This function will parse env->tu_tab to check wether or not we have found a "-1"
** if one has been found, it means we need to cut all the 
*/
void     cut_and_reset(t_env *env, int opt, int visited)
{
    int i;
    int j;      
    
    i = 0;
    while (i < env->nt_rm[1])
    {
        j = 0;
        if (visited == true)
            env->rm_tab[i]->visited = false;
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
    if (opt == 1)
    {
        ft_path_lst_del(&(env->path_lst[env->cr_path]));
        env->path_lst[env->cr_path] = NULL;
    }
}