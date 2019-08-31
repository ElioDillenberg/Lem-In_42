Hello,

Les leaks sont fix, la structure env est intégrés.
Y'a une SegFault sur le parsing apparemment (sur test4.txt) j'ai pas trop compris pourquoi mais lldb me dis que c est dans build_room_tab.
J'ai fais un parcours en profondeur pour trouver les chemins mais on m a explique que c etait dla mderde
donc tu peux delete path.c et path_util.c
Donc jai fais un parcours en largeur (cf BFS) qui indique le pere de chaque room, pour pouvoir retrouver le chemin.

En gros on calcul le nombre maximum de chemin possible, puis on lance bfs. BFS va parcourir les rooms et pour chaque room il va dire qui est son pere.
Une fois que c est fais on part de la room end et on remonte les parents jusqua start, ce qui nous donne un path. On supprime tous les tunnel utilise et on recommence jusqu a avoir trouve tous les chemins.
Les chemins sont stockee dans env->path, sous la forme d un char *.  Il contient les index de chaque room utilisée par un chemin, chaque chemin se termine par un "|"
Une fois cela fait les chemin sont stocké dans un tableau de int, dans env->path_tab

Dans env j'ai ajouté :
  Rm_lst_path qui est utilisé dans BFS pour avoir la liste de mes rooms a explorer
  path_tab qui est le tableau contenant les chemins
  path qui est un char * des path trouve
  max_path, qui est le nombre maximal theorique de path possible
  nb_path qui est le nombre de path trouvé

J ai modifie tres legerement ton ft_strsplit pour supprimer les << Invalid read of size 1 >> et les segF sur les grosse map en rajoutant des conditions d existance.
Et jai modifie tres legerement aussi ton GNL pour ne pas avoir de << Conditional jump or move depends on uninitialised value(s) >> en initialisant tes variables a null

Dans Room jai ajouté "parent" et "path" pour le bfs, pour savoir si une room a ete exploré et qui est son pere

Déso de pas avoir pu avancer plus mais j ai du corriger mon push_swap (jai eu une erreur sur ft_strsplit donc fail ...) et jsuis partis sur le mauvais algo de parcours.
Bref bon courage gros hesites pas si tu comprends pas qlqchose ou si t es bloqué envoie un sms.

En resume il faut :
  Debug la segF du parsing, et optimiser le parsing (en temps d execution)
  Optimiser la recherche de path (en temps d execution)
  Creer l algo qui gere les rounds et l avancement des fourmis

On a un probleme avec le BFS:
Il nous cherche tous les chemins directs. Or on souhaite:
- 1 chemin le plus court
- 2 chemins les plus courts
- 3 chemins les plus courts
- etc...
pour ca on change le BF pour qu'il ne mette a zero que les tunnels dans le sens pris. On relance ensuite un BFS une seconds fois.

J'ai depuis ton depart modifie plusieurs choses:
- plus de segfault/leaks sur le parsing
- j'ai rajoute un tableau de deux cases qui contiennent chacun une liste doublement chainee (afin de stocker les N chemins trouves et alterner pour comparer l'opti)
- il faudra voir ce qu'on fait de check_path, j'ai pas encore bien compris la fonction et pourquoi on en a besoin, mais a priori on aura plus besoin car on la nouvelle liste doublement chainee avec tous les paths crees.
- Il nous faut maintenant: une fonction qui compare N chemins pour X fourmis avec N - 1 chemins pour X fourmis (on utilise path_lst[0] et path_lst[1] qui contienent
respectivement N - 1 chemins et N chemins)
- Il nous faut une fonction qui englode notre bfs+get_path, et qui limite le nombre de chemins que l'on veut trouver (d'abord 1, puis 2, puis 3, puis 4 et qui compare a chaque fois pour voir si on a besoin de continuer a chercher des chemnins)
- Il faut modifier notre BFS, de maniere a ce qu'il reste coherent lorsque l'on parcours notre graphe en remontant le courant (cas de chemins empruntes etant deja empruntes dans l'autre sense)

DONE SAMEDI 31/08
-> regle le probleme de passage de rm_lst[0] a rm_lst[1]
---> on supprime maintenant a chaque passage, et on relance un BFS de zero. On pourrait optimiser ca par la suite en ne supprimant que si on a besoin de peter des chemins et en faisant des copies des chemins precedents si aucun chemin n'a du etre casse
--> Il faudra regler le probleme dans le BFS lorsqu'on casse un chemin (il faut creer une boucle separee, qui "remonte le temps")
--> Il faut implementer une regle -> si je remonte le temps, je dois chercher a arreter de remonter le temps des que possible (si j'ai le choix entre remonter le temps ou non, je prefere ne pas remonter le temmps!)