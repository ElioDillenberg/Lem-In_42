Hello,

Les leaks du parsing sont corrigés, la structure env est intégrés.
Y'a une SegFault sur le parsing apparemment (sur test4.txt) j'ai pas trop compris pourquoi mais lldb me dis que c est dans build_room_tab.
J'ai fais un parcours en profondeur pour trouver les chemins mais on m a explique que c etait dla mderde
donc tu peux delete path.c et path_util.c
Donc jai fais un parcours en largeur (cf BFS) qui indique le pere de chaque room, pour pouvoir retrouver le chemin.

En gros on calcul le nombre maximum de chemin possible, puis on lance bfs. BFS va parcourir les rooms et pour chaque room il va dire qui est son pere.
Une fois que c est fais on part de la room end et on remonte les parents jusqua start. On supprime tous les tunnel utilise et on recommence jusqu a avoir trouve tous les chemins.
Les chemins sont stockee dans env->path, sous la forme d un char *.  Il contient les id de chaque room utilise par un chemin chaque chemin est delimite par un "|"

Dans env j'ai ajouté :
  Rm_lst_path qui est utilisé dans BFS pour avoir la liste de mes rooms a explorer
  path_tab qui est le tableau contenant les chemins
  path qui est un char * du path trouve
  max_path, qui est le nombre maximal theorique de path possible
  nb_path qui est le nombre de path trouvé

J ai modifie tres legerement ton ft_strsplit pour supprimer les invalid read et les segF sur les grosse map en rajoutant des conditions d existance.
et un << Conditional jump or move depends on uninitialised value(s) >> de GNL dans parsing()

Et dans Room jai ajouté "parent" pour le bfs et "path" pour savoir si une room a ete exploré

Déso de pas avoir pu avancer plus mais j ai du corriger mon push_swap (jai eu une erreur sur ft_strsplit donc fail ...) et jsuis partis sur le mauvais algo.
Bref bon courage gros hesites pas si tu comprends pas qlqchose ou si t es bloqué envoie un sms.
