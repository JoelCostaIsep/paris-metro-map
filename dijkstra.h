#ifndef DIJKS
#define DIJKS

/* includes */
#include "liste.h"
#include "truc.h"

/* defines */
#define T_COR 1.5
#define T_PAU 0.5

/* fonctions */
void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep);

Un_elem *cherche_chemin(Un_truc *sta_arr);

#endif
