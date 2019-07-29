Yo, je viens de finir le gros du parsing

Il reste des leaks, qui sont dus a rm_tab et tu_tab. Il faudrait refaire la fonction
free_room_lst afin qu'elle free tout. Mais ce sera plus simple a faire une fois qu'on aura
une structure t_env.

Il reste donc a:
- creer une structure environnement
- modifier la fonction free_room en free_all pour tout free a la fin
- il faut faire en sorte que to_print soit dans la structure ENV afin de pouvoir print seulement a la fin

Tu peux faire des tests sur le parseur aussi, j'ai pas eu le temps d'en faire beaucoup
