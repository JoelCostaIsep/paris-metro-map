#include <stdio.h>
#include <stdlib.h>
#include "aqrtopo.h"

Un_noeud *creer_noeud(Une_coord limite_no, Une_coord limite_se, Un_truc *truc){
  Un_noeud *n=NULL;
  n=(Un_noeud*)malloc(sizeof(Un_noeud));
  if(!n){
    fprintf(stderr,"Erreur: allocation memoire\n");
    return NULL;
  }
  n->limite_no = limite_no;
  n->limite_se = limite_se;
  n->truc = truc;
  return n;
}

Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc){
  Une_coord m, tmp;
  if(!aqr){
    return creer_noeud(limite_no, limite_se, truc);
  }
  if(aqr->truc){
    aqr = inserer_aqr(aqr, limite_no, limite_se, aqr->truc);
    aqr->truc=NULL;
  }
  m.lon=(limite_no.lon+limite_se.lon)/2;
  m.lat=(limite_no.lat+limite_se.lat)/2;
 
  if(truc->coord.lon >= limite_no.lon &&				\
     truc->coord.lon <= m.lon &&					\
     truc->coord.lat >= m.lat &&					\
     truc->coord.lat <= limite_no.lat)
    {
      aqr->no = inserer_aqr(aqr->no, limite_no, m, truc);
    }
  if(truc->coord.lon < limite_se.lon &&					\
     truc->coord.lon > m.lon &&						\
     truc->coord.lat < m.lat &&						\
     truc->coord.lat > limite_se.lat)
    {
      aqr->se = inserer_aqr(aqr->se, m, limite_se, truc);
    }

  tmp.lat = limite_se.lat;
  tmp.lon = limite_no.lon;
  if(truc->coord.lon >= limite_no.lon &&				\
     truc->coord.lon <= m.lon &&					\
     truc->coord.lat >= limite_se.lat &&				\
     truc->coord.lat < m.lat)
    {
      aqr->so = inserer_aqr(aqr->so, tmp, m , truc);
    }
 
  tmp.lon = limite_se.lon;
  tmp.lat = limite_no.lat;
  if(truc->coord.lon > m.lon &&						\
     truc->coord.lon <= limite_se.lon &&				\
     truc->coord.lat >= m.lat &&					\
     truc->coord.lat <= limite_no.lat)
    {
      aqr->ne = inserer_aqr(aqr, m, tmp, truc);
    }
 
  return aqr;
}

void detruire_aqr(Un_noeud *aqr){
  if(!aqr){
    return;
  }
  if(!aqr->truc){
    detruire_aqr(aqr->no);
    detruire_aqr(aqr->so);
    detruire_aqr(aqr->ne);
    detruire_aqr(aqr->se);
  }
  free(aqr);
}

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord){
  Une_coord limite_no = aqr->limite_no;
  Une_coord limite_se = aqr->limite_se;
  Une_coord m, tmp;
  if(!aqr){
    return NULL;
  }
  if(aqr->truc != NULL){
    if(aqr->truc->coord.lon == coord.lon && aqr->truc->coord.lat == coord.lat){
      return aqr->truc;
    }
    else{
      return NULL;
    }
  }
 
  m.lon=(limite_no.lon+limite_se.lon)/2;
  m.lat=(limite_no.lat+limite_se.lat)/2;

  if(aqr->truc->coord.lon >= limite_no.lon &&				\
     aqr->truc->coord.lon <= m.lon &&					\
     aqr->truc->coord.lat >= m.lat &&					\
     aqr->truc->coord.lat <= limite_no.lat)
    {
      return chercher_aqr(aqr->no, coord);
    }
  
  if(aqr->truc->coord.lon < limite_se.lon &&				\
     aqr->truc->coord.lon > m.lon &&					\
     aqr->truc->coord.lat < m.lat &&					\
     aqr->truc->coord.lat > limite_se.lat)
    {
      return chercher_aqr(aqr->se, coord);
    }

  tmp.lat = limite_se.lat;
  tmp.lon = limite_no.lon;

  if(aqr->truc->coord.lon >= limite_no.lon &&				\
     aqr->truc->coord.lon <= m.lon &&					\
     aqr->truc->coord.lat >= limite_se.lat &&				\
     aqr->truc->coord.lat < m.lat)
    {
      return chercher_aqr(aqr->so, coord);
    }
  else{
    /*
      if(aqr->truc->coord.lon > m.lon &&				\
      aqr->truc->coord.lon <= limite_se.lon &&				\
      aqr->truc->coord.lat >= m.lat &&					\
      aqr->truc->coord.lat <= limite_no.lat)
    */
    tmp.lon = limite_se.lon;
    tmp.lat = limite_no.lat;
    return chercher_aqr(aqr->ne,coord);
  }
}

Un_noeud *construire_aqr(Un_elem *liste){
  Un_elem *l=NULL;
  Un_noeud *aqr=NULL;
  Une_coord limite_no, limite_se;
  if(!liste){
    return NULL;
  }
  limite_no = liste->truc->coord;
  limite_se = liste->truc->coord;
  l = liste->suiv;

  while(l){

    if(l->truc->coord.lon < limite_no.lon){
      limite_no.lon = l->truc->coord.lon;
    }
    else {
      if(l->truc->coord.lon > limite_se.lon){
	limite_se.lon = l->truc->coord.lon;
      }
    }
 
    if(l->truc->coord.lat > limite_no.lat){
      limite_no.lat = l->truc->coord.lat;
    }
    else{
      if(l->truc->coord.lat < limite_se.lat){
	limite_se.lat = l->truc->coord.lat;
      }
    }
    aqr = inserer_aqr(aqr, limite_no, limite_se, l->truc);
  }

  while(liste){
    aqr = inserer_aqr(aqr, limite_no, limite_se, liste->truc);
    liste = liste->suiv;
  }
  return aqr;
}


Un_elem *chercher_zone(Un_noeud *aqr, Un_elem *liste, Une_coord limite_no, Une_coord limite_se){
  Un_elem *res=NULL;
  
  return res;
}

int max(int a, int b){
  if(a <= b){
    return b;
  }
  else{
    return a;
  }
}

int hauteur_aqr(Un_noeud *aqr){
  if(!aqr){
    return 0;
  }
  if(aqr->truc != NULL){
    return 1;
  }
  else{
    return 1 + max(max(hauteur_aqr(aqr->no), hauteur_aqr(aqr->ne)), max(hauteur_aqr(aqr->so), hauteur_aqr(aqr->se)));
  }
}
