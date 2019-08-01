Hello,

Les leaks du parsing sont corrigés, la structure env est intégrés.
Y'a une SegFault sur le parsing apparemment (sur test4.txt) j'ai pas trop compris pourquoi mais lldb me dis que c est dans build_room_tab.
J'ai fais un parcours en profondeur pour trouver les chemins mais on m a explique que c etait dla mderde
donc tu peux delete path.c et path_util.c,si tu veux voir lance path_finder(env); dams le main et enleve ft_bfs(env)
Donc jai fais un parcours en largeur (cf BFS) qui indique le pere de chaque room, pour pouvoir retrouver le chemin.
En gros ya que bfs.c qui est reelement interessant

Dans env j'ai ajouté :
  Rm_lst_path qui est utilisé dans BFS pour avoir la liste de mes rooms a explorer
  path qui est un char * du path trouve
  max_path, qui est le nombre maximal de path possible
  nb_path qui est le nombre de path trouvé

Déso de pas avoir pu avancer plus mais j ai du corriger mon push_swap (jai une erreur sur ft_strsplit ...) et jsuis partis sur le mauvais algo.
