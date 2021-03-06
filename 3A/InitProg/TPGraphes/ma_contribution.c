/* Marc Gengler - Polytech Marseille - Janvier 2016 */

/* ------------------------------------------------------------ */

/* Les prototypes. Voir plus loin pour leurs descriptions.

   Toutes les fonctions comporteront les assert de rigueur. */

int graphe_non_oriente ( t_gra graphe ) ;

void fermeture_reflexive ( t_gra graphe ) ;

void fermeture_reflexive_pondere ( t_gra graphe , int poids ) ;

int graphe_AR ( t_gra graphe ) ;

int graphe_ARAS ( t_gra graphe ) ;

int degre_graphe ( t_gra graphe ) ;

int cherche_sommet_sec ( t_gra graphe ) ;
int connexe_vague ( t_gra graphe , int view ) ;

int nombre_aretes ( t_gra graphe ) ;
int est_un_arbre ( t_gra graphe ) ;

void parcours_profondeur_niveaux_rec ( t_gra graphe , int sommet , int niveau ) ;
void parcours_profondeur_niveaux ( t_gra graphe , int depart ) ;

int cherche_sommet_sec_et_predecesseurs_mouilles ( t_gra graphe ) ;
void tri_topologique ( t_gra graphe ) ;

void multiplie ( t_gra graphe ) ;

void floyd_warshall ( t_gra graphe ) ;

void multiplie_pondere ( t_gra graphe ) ;

void floyd_warshall_pondere ( t_gra graphe ) ;

int verifie_ponderation ( t_gra graphe ) ;
int cherche_sec_sommet_min ( t_gra graphe ) ;
void relax ( t_gra graphe , int table_predecesseurs[ ] , int pred , int sommet ) ;
void dijkstra ( int depart , t_gra graphe , int table_predecesseurs[ ] ) ;

int cherche_sec_sommet_max ( t_gra graphe ) ;
void relax_maximise_le_min ( t_gra graphe , int table_predecesseurs[ ] ,
			     int pred , int sommet , int depart ) ;
void dijkstra_maximise_le_min ( int depart , t_gra graphe , int table_predecesseurs[ ] ) ;

void calcule_residuel ( t_gra graphe_flot , t_gra graphe_residuel , int i , int j ) ;
void adapte_flot ( t_gra graphe_flot , int depuis , int vers , int valeur ) ;
void ford_et_fulkerson ( void ) ;

/* ------------------------------------------------------------ */

/* Le prédicat graphe_non_oriente dit si, OUI ou NON, le graphe fourni
   est symétrique ? Le graphe peut être pondéré ou non. Un graphe
   pondéré est symétrique si et seulement si les arcs ( a , b ) et
   ( b , a ) possèdent le même poids. */

int graphe_non_oriente ( t_gra graphe ) {
/* +/- 10 lignes. Il faudra retourner une valeur convenable. */
    int i, j, poidSensNormal, poidSensInverse, retour = 0;
    int taille = taille_graphe(graphe);
    for(i = 0; i < taille; ++i) {
        for(j = 0; j < taille; ++j) {
            if(get_arete(graphe, i, j) && graphe_pondere(graphe) == OUI) {
                poidSensNormal = poids_arc(graphe , i , j);
                poidSensInverse = poids_arc(graphe , j , i);
                if(poidSensNormal != poidSensInverse)
                    retour = NON;            
            }
            else
                if(!graphe_pondere(graphe))
                    if(get_arete(graphe, i, j))
                        retour = OUI;
        }
    }
    
    return retour; 
}

/* ------------------------------------------------------------ */

/* La procédure fermeture_reflexive rajoute toutes les arêtes de la
   forme ( s , s ) manquantes, c'est-à-dire les arêtes d'un sommet s
   vers lui-même. Les nouvelles arêtes seront de la couleur donnée
   par la_couleur( ). Le graphe ne doit pas être pondéré. */  

void fermeture_reflexive ( t_gra graphe ) {
	/* +/- 5 lignes */
    assert(!graphe_pondere(graphe));
  
    int i, taille = taille_graphe(graphe);
    for(i = 0; i < taille; ++i) {
        if(!get_arc(graphe, i, i))
            set_arc(graphe, i, i, la_couleur());
    }
}

/* ------------------------------------------------------------ */

/* La procédure fermeture_reflexive_pondere réalise la même opération
   que la procédure précédente, à ceci près qu'elle s'applique à un
   graphe pondéré et donne en conséquence un poids aux nouvelles arêtes.
   On vérifiera que le graphe est bien pondéré et que le poids donné
   est accepté par le graphe. */

void fermeture_reflexive_pondere ( t_gra graphe , int poids ) {
	/* +/- 5 lignes */
    int i, taille = taille_graphe(graphe);
    for(i = 0; i < taille; ++i) {
        if(!get_arc(graphe, i, i))
            set_arc_pondere(graphe, i, i, poids, la_couleur());
    }
}

/* ------------------------------------------------------------ */

/* Le prédicat graphe_AR dit si, OUI ou NON, le graphe fourni est
   anti-réflexif, c'est-à-dire ne possède aucune arête de la forme
   ( s , s ) ? Elle s'applique aussi bien aux graphes pondérés que
   non pondérés, orientés ou non. */

int graphe_AR ( t_gra graphe ) {
   /* +/- 5 lignes. Il faudra retourner une valeur convenable. */
    int i, taille = taille_graphe(graphe);
    for(i = 0; i < taille; ++i) {
        if(get_arc(graphe, i, i))
            return NON;
    }
    return OUI; 
}

/* ------------------------------------------------------------ */

/* Le prédicat graphe_ARAS dit si, OUI ou NON, le graphe fourni
   est à la fois anti-réflexif et anti-symétrique ? Le graphe
   peut être pondéré ou non. */

int graphe_ARAS ( t_gra graphe ) {
    /* +/- 10 lignes. Il faudra retourner une valeur convenable. */
    int i, j, taille = taille_graphe(graphe);
    
    if(!graphe_AR(graphe))
        return NON;

    for(i = 0; i < taille; ++i) {
        for(j = 0; j < taille; ++j) {
            if(get_arete(graphe, i, j))
                return NON;
        }
    }
    return OUI; 
}

/* ------------------------------------------------------------ */

/* La fonction degre_graphe retourne le degré d'un graphe symétrique
   pondéré, ou non. La fonction vérifie explicitement que le graphe
   fourni est bien symétrique. On opte pour le choix normal qui
   consiste à dire qu'une arête réflexive de la forme ( a , a )
   compte pour 2 dans le degré du sommet a . */

int degre_graphe ( t_gra graphe ) {
    /* +/- 15 lignes. Il faudra retourner une valeur convenable. */
    assert(graphe_non_oriente(graphe));

    int i, j, degre = 0, degreMax = 0, taille = taille_graphe(graphe);
    for(i = 0; i < taille; ++i) {
        for(j = 0; j < taille; ++j) {
            if(get_arete(graphe, i, j)) {
              degre = degre + 1;
              if(i == j)
                degre = degre + 1;
            }
        }

        if(degre > degreMax)
          degreMax = degre;

        degre = 0;
    }

    return degreMax; 
}

/* ------------------------------------------------------------ */

/* La fonction connexe_vague s'applique aux seuls graphes non orientés.
   Elle détermine les composantes connexes en lançant des "vagues". La
   fonction rend le nombre de composantes connexes trouvées.

   Tant que l'on trouve un sommet sec "u", on lance une vague depuis "u".
   La fonction-prédicat cherche_sommet_sec sert à chercher un tel sommet.
   Si elle en trouve un, elle en retourne le numéro, c'est-à-dire un
   nombre positif. Si elle n'en trouve plus, elle retourne la valeur - 1 .

   La "vague" va mouiller chaque sommet rencontré. Les arêtes seront de
   couleurs différentes au fur et à mesure que l'on s'éloigne du sommet
   de départ, en suivant l'ordre des couleurs. On pourra donc savoir, à
   partir de la	 couleur d'une arête, s'il a déjà été visitée ou non.

   De plus, chaque sommet recevra comme poids le numéro d'étapes nécessaires
   pour le toucher la première fois. C'est d'ailleurs le même numéro que
   celui de l'arête qui l'atteint en premier. On calcule donc de surcroît
   les plus courts chemins du point de départ au sommet considéré.

   connexe_vague affichera, suivant l'état de view, donc OUI ou NON, le
   graphe et la progression de la vague pour chaque étape. Voir aussi
   le fichier de réponse type "reponse_de_refence".

   Cette fonctionnalité nécessite un parcours en largeur et va s'appuyer
   sur fonctions de gestion de file fournies dans fonctions.h .

   A la fin, tous les sommets sont à nouveau séchés.

   connexe_vague est un peu plus difficile à implanter que d'autres et on
   peut préférer résoudre d'abord certaines des questions qui suivent. */ 

int cherche_sommet_sec ( t_gra graphe ) {
    /* +/- 5 lignes. Il faudra retourner une valeur convenable. */
    int i, taille = taille_graphe(graphe);
    for(i = 0; i < taille; ++i) {
        if(!mouille(graphe , i))
            return i ;
    }
    return -1; 
}

int connexe_vague ( t_gra graphe , int view ) {
    /* +/- 40 lignes. Il faudra retourner une valeur convenable. */
    assert(graphe_non_oriente(graphe));

    int i, taille, connexite, couleur, sommet_sec, etape = 0;
    t_file file = cree_file_vide();
    taille = taille_graphe(graphe);
    connexite = 0;
    couleur = la_couleur();
    sommet_sec = cherche_sommet_sec(graphe);

    while(sommet_sec != -1) {
        connexite = connexite + 1;
        etape = 0;
        sommet_set_poids(graphe, sommet_sec, etape);
        tremper(graphe, sommet_sec);
        etape++;
        file = insere_file(sommet_sec, file);
        while(!est_file_vide(file)) {
            sommet_sec = tete_file(file);
            file = supprime_tete_file(file);
            
            for(i = 0; i < taille; ++i) {
                if(get_arete(graphe, sommet_sec, i)) {
                    set_couleur_arc(graphe, sommet_sec, i, couleur);
                    if(!mouille(graphe, i)) {
                        sommet_set_poids(graphe, i, etape);
                        tremper(graphe, i);
                        file = insere_file(i, file);
                    }
                }
            }

            if(!est_file_vide(file) && sommet_get_poids(graphe, sommet_sec) != sommet_get_poids(graphe, tete_file(file))) {
                couleur_suivante();
                couleur = la_couleur();
                etape++;

                if(view == OUI)
                  imprime_graphe(graphe, TOUTES_COULEURS, OUI);
            }
            
        }
        sommet_sec = cherche_sommet_sec(graphe);
        definir_couleur(ROUGE);
        couleur = la_couleur();
    }

    // On seche tous les sommets
    for(i = 0; i < taille; ++i)
        secher(graphe, i);

    return connexite; 
}

/* ------------------------------------------------------------ */

/* Ecrire le prédicat est_un_arbre qui s'applique aux seuls graphes
   anti-réflexifs et non orientés et qui dit si, OUI ou NON, le graphe
   est un arbre. Il suffira de compter le nombre d'arêtes et de vérifier
   que le graphe possède exactement une seule composante connexe. */

int nombre_aretes ( t_gra graphe ) {
    /* +/- 10 lignes. Il faudra retourner une valeur convenable. */
    int nbArrete = 0, i, taille, j;
    taille = taille_graphe(graphe);
    for(i = 0; i < taille; ++i) {
        for(j = 0; j < i; ++j) {
            if(get_arete(graphe, i, j))
                nbArrete++;
        }
    }
    
    return nbArrete; 
}

int est_un_arbre ( t_gra graphe ) {
    /* +/- 5 lignes. Il faudra retourner une valeur convenable. */
    assert(graphe_AR(graphe));
    assert(graphe_non_oriente(graphe));

    if(nombre_aretes(graphe) == taille_graphe(graphe) - 1)
        if(connexe_vague(graphe, NON) == 1)
            return OUI;

    return NON; 
}

/* ------------------------------------------------------------ */

/* parcours_profondeur_niveaux parcourt un graphe depuis le sommet
   de départ en utilisant un parcours en profondeur. Pour éviter de
   boucler, on utilisera les états SEC et MOUILLE des sommets. Les
   appels récursifs incrémentent le niveau à chaque appel et tout
   sommet sec recevra comme poids le niveau le moins élevé avec
   lequel il a été touché. Cette procédure calcule donc au
   passage les plus courts chemins depuis le sommet de départ, bien
   que l'algorithme ne soit pas, et de loin, le plus efficace.

   parcours_profondeur_niveaux initialise les poids des sommets et
   parcours_profondeur_niveaux_rec effectue le parcours. */

void parcours_profondeur_niveaux_rec ( t_gra graphe , int sommet , int niveau ) {
	/* +/- 10 lignes */
    int i, taille;
    taille = taille_graphe(graphe);
    
    if(!mouille(graphe, sommet)) {
        if(sommet_get_poids(graphe, sommet) > niveau)
            sommet_set_poids(graphe, sommet, niveau);

        tremper(graphe, sommet);
    }

    for(i = sommet; i < taille; ++i) {
        if(get_arc(graphe, sommet, i))
          if(!mouille(graphe, i)){
            parcours_profondeur_niveaux_rec(graphe, i, niveau+1);
        }
    }
    secher(graphe, sommet);
}

void parcours_profondeur_niveaux ( t_gra graphe , int depart ) {
	/* +/- 10 lignes */
    int i, taille, niveau = 0;
    taille = taille_graphe(graphe);

    for(i = depart; i < taille; ++i)
        sommet_set_poids(graphe, i, PLUS_INF);
    
    sommet_set_poids(graphe, depart, niveau);
    tremper(graphe, depart);

    parcours_profondeur_niveaux_rec(graphe, depart, niveau);
}

/* ------------------------------------------------------------ */

/* tri_topologique calcule une valuation "topologique" pour les sommets
   d'un graphe qui est un DAG. On peut consulter l'énoncé du premier TD
   pour les définitions. La vérification de la propriétés ARAS ne pose
   pas de problème. La vérification de l'absence de circuits est plus
   délicate et on ne la fera pas sous forme d'une recherche de circuits.

   L'algorithme mis en application est celui vu en TD. Il consiste à dire :

   Tantque tous les sommets ne portent pas une valeur

	- Chercher un sommet "u" dont tous les prédécesseurs possèdent
	  déjà une valeur. Chaque sommet est mouillé au moment où il reçoit
          une valeur. L'objectif peut donc être réalisé à travers la
	  fonction cherche_sommet_sec_et_predecesseurs_mouilles qui
	  retourne un tel sommet "u". Le premier TD a montré qu'un tel
	  choix est toujours possible, si le graphe ne possède pas de
	  circuit.

	- Donner à "u" une valeur plus grande que celle de tous ses
	  prédécesseurs. C'est trivial. De plus, on va colorier les
	  arcs.

   Le fait que cherche_sommet_sec_et_predecesseurs_mouilles ne trouve
   pas de sommet permet donc de conclure que le graphe possède des
   circuits. Dans ce cas, la fonction donne un message clair et la
   suite du calcul est abandonnée. Le graphe rendu ne sera donc
   que partiellement valué. */

int cherche_sommet_sec_et_predecesseurs_mouilles ( t_gra graphe ) {
    /* +/- 15 lignes. Il faudra retourner une valeur convenable. */
    int cpt = 0, i, tousTrempe;
    int taille = taille_graphe(graphe);
    int sommet = -1;

    while(sommet == -1 && cpt < taille){
        tousTrempe = 1;

        for(i = 0; i < taille; ++i){
            if(get_arc(graphe, i, cpt) && !mouille(graphe, i))
                tousTrempe = 0;
        }

        if(tousTrempe && !mouille(graphe, cpt))
            sommet = cpt;
        cpt++;
    }

    if(sommet != -1)
        tremper(graphe, sommet);

    return sommet; 
}

void tri_topologique ( t_gra graphe ) {
    /* +/- 20 lignes */
    assert(graphe_ARAS(graphe));
     
    int i, sommet, poids = 0;
    int taille = taille_graphe(graphe);
   
    while((sommet = cherche_sommet_sec_et_predecesseurs_mouilles(graphe)) != -1){
        for(i = 0; i < taille; i++){
            if(get_arc(graphe, sommet, i))
                set_couleur_arc(graphe, sommet, i, la_couleur());
        }

        sommet_set_poids(graphe, sommet, poids);

        if(la_couleur() >= NOMBRE_COULEURS - 1)
            definir_couleur(ROUGE);
        else
            couleur_suivante();
        
        poids++;
    }

    if(poids < taille)
        printf("LE GRAPHE COMPORTE DES CIRCUITS !\n");
}
  
/* ------------------------------------------------------------ */

/* On considère un graphe non pondéré et on souhaite calculer les plus
   courts chemins au sens du "nombre d'étapes", c'est-à-dire du "nombre
   arcs ou arêtes à traverser". Le graphe peut être orienté ou non.

   On partira d'une matrice M = M^1 qui est fermée réflexivement. La
   fermeture réflexive est une des questions qui précèdent.

   Il s'agira ensuite de calculer pour tous les sommets u et v :

	M^(2*i) ( u , v ) = max_k  M^i ( u , k ) * M^i ( k , v )

   où k parcourt tous les sommets.

   Il faudra calculer M^k, avec k plus grand ou égal au diamètre maximal
   du graphe, c'est-à-dire taille_graphe( graphe ) - 1 . On effectuera
   les optimisations de calcul vues en TD, à savoir on évitera de
   recalculer les éléments de la diagonale, ainsi que toute entrée
   qui est déjà à un.

   Pour chaque multiplication de matrice on choisira une autre couleur
   pour les arcs et arêtes introduits. Voir "reponse_de_reference".

   Il faut, à tout moment, deux matrices en mémoire, à savoir M^i et
   M^(2*i) que l'on est en train de calculer. A l'étape suivante, la
   dernière matrice M^(2*i) va jouer le rôle de M^i. On peut recourir
   à la procédure copie_graphe qui copie des graphes et pour laquelle
   l'appel "copie_graphe( graphe , nouveau ) ;" a pour effet de
   recopier "graphe" en "nouveau". */

void multiplie ( t_gra graphe ) {
    /* +/- 20 lignes */
    assert(!graphe_pondere(graphe));

    int p, i, j, k;
    int n = taille_graphe(graphe);
    
    definir_couleur(2); // Pour avoir pareil que la réponse de référence
    fermeture_reflexive(graphe);

    int max;

    t_gra graphe2 = nouveau_graphe(n);
    copie_graphe(graphe, graphe2);
    
    for(p = 1; p < n - 1 ; p = p*2) {
        for(i = 0; i < n; ++i){
            for(j = 0; j < n; ++j){
                if(!get_arc(graphe, i, j)) {
                    max = 0;
                    for(k = 0;  k < n;  k++) {
                        if(get_arc(graphe, i, k) && get_arc(graphe, k, j) ) 
                            max = 1;
                    }

                    if(max == 1)
                        set_arc(graphe2,  i,  j, la_couleur());
                }
            }
        }

        couleur_suivante();
        copie_graphe(graphe2, graphe);
    }
}

/* ------------------------------------------------------------ */

/* Ecrire la procédure de Floyd_Warshall des plus courts chemins sur
   un graphe non pondéré. Chaque "barbecue" utilisera une autre
   couleur d'arc pour marquer les nouvelles connaissances. */

void floyd_warshall ( t_gra graphe ) {
    /* +/- 15 lignes */
    
    assert(!graphe_pondere(graphe));
}

/* ------------------------------------------------------------ */

/* On considère un graphe pondéré. Ecrire la procédure de calcul des
   chemins les plus légers, c'est-à-dire en termes de somme des poids
   des arcs et arêtes.

   Attention, à la différence de qui a été considéré lors des TD, un
   arc ou une arête absente ne porte pas le poids + infini, mais
   retourne - 1 à travers les prédicats get_arc ou get_arete.

   On est garanti du fait que la constante PLUS_INF est neutre pour la
   minimisation et la constante MOINS_INF neutre pour la maximisation. */

void multiplie_pondere ( t_gra graphe ) {
    /* +/- 25 lignes */
   assert(graphe_pondere(graphe));

    int p, i, j, k;
    int n = taille_graphe(graphe);
    
    definir_couleur(2); // Pour avoir pareil que la réponse de référence
    fermeture_reflexive_pondere(graphe, 0);

    int max, poids;

    t_gra graphe2 = nouveau_graphe(n);
    copie_graphe(graphe, graphe2);
    
    for(p = 1; p < n - 1 ; p = p*2) {
        for(i = 0; i < n; ++i){
            for(j = 0; j < n; ++j){
                if(!get_arc(graphe, i, j)) {
                    max = 0;
                    for(k = 0;  k < n;  k++) {
                        if(get_arc(graphe, i, k) && get_arc(graphe, k, j) )  {
                            poids = poids_arc(graphe, i, k) + poids_arc(graphe, k, j);
                            max = 1;
                        }
                    }

                    if(max == 1) {
                        set_arc_pondere(graphe2,  i,  j,  poids, la_couleur());
                    }
                }
            }
        }

        couleur_suivante();
        copie_graphe(graphe2, graphe);
    }
 }

/* ------------------------------------------------------------ */

/* La version pondérée de Floyd-Warshall. */

void floyd_warshall_pondere ( t_gra graphe )
     {
	/* +/- 20 lignes */
    assert(graphe_pondere(graphe));
     }

/* ------------------------------------------------------------ */

/* dijkstra calcule les chemins les plus légers depuis un sommet de
   de départ vers tous les autres sommets. Les poids des arcs et arêtes
   doivent être positifs ou nuls. Ceci est vérifié à l'aide du
   prédicat verifie_ponderation.

   Attention, à la différence de ce qui a été vu en cours, il se peut
   que certains sommets ne sont peut-être pas atteignables depuis le
   sommet de départ.

   Pour tout sommet u , D( u ) est représenté à l'aide du poids associé
   au sommet. P( u ) est géré à travers le tableau table_predecesseurs
   qui est passé en argument à dijkstra. Toutes les informations sont
   initialisées comme vu en cours et TD. On pourra utiliser - 1 pour
   indiquer dans table_predecesseurs que l'on ne connaît pas le
   prédécesseur d'un sommet donné.

   cherche_sec_sommet_min retourne l'indice du sommet u pour lequel
   D( u ) est minimal parmi tous les sommets encore secs et mouille le
   sommet en question.

   relax est l'opération de relaxation de Dijsktra. Si le sommet s accepte
   le sommet p comme nouveau prédécesseur, on met à jour D( s ) et P( s ).
   L'arc p -> s sera alors colorié en ROUGE, et tout éventuel ancien arc
   rouge x -> s redeviendra NOIR.

   La table des prédécesseurs table_predecesseurs est considérée non
   initialisée et doit donc être initialisée. De même, on ne suppose rien
   sur les poids de sommets. */

int verifie_ponderation ( t_gra graphe ) {
    /* +/- 10 lignes. Il faudra retourner une valeur convenable. */
    int i, j, n;
    n = taille_graphe(graphe);

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (get_arc(graphe, i, j) && poids_arc(graphe, i, j) < 0)
                return 0;
        }
    }

    return 1; 
}

int cherche_sec_sommet_min ( t_gra graphe ) {
    /* +/- 10 lignes. Il faudra retourner une valeur convenable. */
    
    int i, s = -1;
    int poids = PLUS_INF;

    for (i = 0; i < taille_graphe(graphe); i++) {
         if (!mouille(graphe, i) && sommet_get_poids(graphe, i) < poids) {
            s = i;
            poids = sommet_get_poids(graphe, i);
         }
    }

    return s; 
}

void relax ( t_gra graphe , int table_predecesseurs[ ] , int pred , int sommet ) {
    /* +/- 10 lignes */
    int i, poids;
    poids = sommet_get_poids(graphe, pred) + poids_arc(graphe, pred, sommet);

    if (poids < sommet_get_poids(graphe, sommet)) {
        table_predecesseurs[sommet] = pred;
        sommet_set_poids(graphe, sommet, poids);

        for (i = 0; i < taille_graphe(graphe); i++) {
            if (get_arc(graphe, i, sommet)) {
                set_couleur_arc(graphe, i, sommet, NOIR);
            }
        }

        set_couleur_arc(graphe, pred, sommet, ROUGE);
    }
 }

void dijkstra ( int depart , t_gra graphe , int table_predecesseurs[ ] ) {
    /* +/- 20 lignes */
    int i, s, n = taille_graphe(graphe);

    for (i = 0; i < n;  ++i) {
        sommet_set_poids(graphe, i, PLUS_INF);
        table_predecesseurs[i] = -1;
    }

    sommet_set_poids(graphe, depart, 0);

    s = cherche_sec_sommet_min(graphe);
    do {
        tremper(graphe, s);
        for (i = 0; i < n; ++i) {
            if (get_arc(graphe, s, i) && !mouille(graphe, i))
                relax(graphe, table_predecesseurs, s, i);
        }
        s = cherche_sec_sommet_min(graphe);
    } while (s != -1);
}

/* ------------------------------------------------------------ */

/* dijkstra_maximise_le_min calcule les meilleurs chemins en maximisant
   l'arc ou l'arête minimal du chemin. Il faut adapter les fonctions
   et procédures précédentes.

   relax_maximise_le_min prend le sommet de départ comme argument
   supplémentaire, car le traitement est particulier lorsque le
   prédécesseur est égal au sommet de départ.

   Attention, à la différence de ce qui a été vu en cours, il se peut
   que certains sommets ne sont peut-être pas atteignables depuis le
   sommet de départ. */

int cherche_sec_sommet_max ( t_gra graphe ) {
    /* +/- 10 lignes. Il faudra retourner une valeur convenable. */
    int i, poids, n = taille_graphe(graphe);
    int s = -1;
    poids = MOINS_INF;

    for (i = 0; i < n; ++i) {
        if (!mouille(graphe, i) && sommet_get_poids(graphe, i) > poids) {
            s = i;
            poids = sommet_get_poids(graphe, i);
        }
    }

    return s; 
}

void relax_maximise_le_min ( t_gra graphe , int table_predecesseurs[ ] ,
			     int pred , int sommet , int depart ) {
    /* +/- 10 lignes */
    int i, poids, n = taille_graphe(graphe);

    if (depart != pred)
        poids = min(sommet_get_poids(graphe, pred), poids_arc(graphe, pred, sommet));
    else
        poids = poids_arc(graphe, pred, sommet);

    if (poids > sommet_get_poids(graphe, sommet)) {
        table_predecesseurs[sommet] = pred;
        sommet_set_poids(graphe, sommet, poids);

        for (i = 0; i < n; ++i) {
            if (get_arc(graphe, i, sommet))
                set_couleur_arc(graphe, i, sommet, NOIR);
        }

        set_couleur_arc(graphe, pred, sommet, ROUGE);
    }
}

void dijkstra_maximise_le_min ( int depart , t_gra graphe , int table_predecesseurs[ ] ) {
    /* +/- 20 lignes */
    assert(verifie_ponderation(graphe));

    int i, s, n = taille_graphe(graphe);

    for (i = 0; i < n; ++i) {
        sommet_set_poids(graphe, i, MOINS_INF);
        table_predecesseurs[i] = -1;
    }

    sommet_set_poids(graphe, depart, 0);
    s = cherche_sec_sommet_max(graphe);

    do {
        tremper(graphe, s);    
        for (i = 0; i < n; ++i) {
            if (get_arc(graphe, s, i) && !mouille(graphe, i))
                relax_maximise_le_min(graphe, table_predecesseurs, s, i, depart);
        }
        s = cherche_sec_sommet_max(graphe);
    } while (s != -1);
}

/* ------------------------------------------------------------ */

/* La boucle principale de calcul d'un graphe de flot est donnée
   dans ford_et_fulkerson. Il s'agit de la compléter en définissant
   deux fonctions.

   ford_et_fulkerson commence par vérifier que le graphe est correct
   avec Sa comme source et le sommet d'indice taille_graphe( graphe ) - 1
   comme puits. De plus, il faut que tous les sommets puissent être
   atteints depuis la source.

   calcule_residuel prend en argument le graphe de flot et le graphe
   résiduel en construction. Pour des sommets i et j donnés, avec i != j,
   il s'agit de calculer la marge dans le sens "i vers j" et de mettre
   à jour le graphe résiduel. capacite_arc donne la capacité de l'arc
   et poids_arc donne le flot de l'arc. graphe_residuel est un
   graphe pondéré ordinaire.

   adapte_flot change le flot dans le graphe de flot entre les sommets
   depuis et vers et ceci d'une quantité égale à la valeur donnée.
   Eventuellement, on sera obligé de modifier les deux arcs
   ( depuis , vers ) et ( vers , depuis ) dans le graphe de flot.
   Chaque arc modifié reçoit la couleur courante. */

void calcule_residuel ( t_gra graphe_flot , t_gra graphe_residuel , int i , int j ) {
    /* +/- 10 lignes */

    int pij, pji, capij;

    if (get_arc(graphe_flot, i, j)) {
        pij = poids_arc(graphe_flot, i, j);
        capij = capacite_arc(graphe_flot, i, j);
    }
    else {
        pij = 0;
        capij = 0;
    }

    if (get_arc(graphe_flot, j, i))
        pji = poids_arc(graphe_flot, j, i);
    else
        pji = 0;

    if (capij - pij + pji) {
        set_arc_pondere(graphe_residuel, i, j,
            capij - pij + pji, la_couleur());
    }
}

void adapte_flot ( t_gra graphe_flot , int depuis , int vers , int valeur ) {
    /* +/- 20 lignes */

    if (valeur) {
        int poids, mini, i = depuis, j = vers;

        if (get_arc(graphe_flot, j, i)) {
            poids = poids_arc(graphe_flot, j, i);

            if (poids) {
                mini = min(valeur, poids);
                valeur = valeur - mini;
                ajoute_poids_arc(graphe_flot, j, i, -mini);
                set_couleur_arc(graphe_flot, j, i, la_couleur());
            }
        }

        if (valeur) {
            ajoute_poids_arc(graphe_flot, i, j, valeur);
            set_couleur_arc(graphe_flot, i, j, la_couleur());
        }
    }
}

void ford_et_fulkerson ( void ) 
     {int i , j , sommet , taille , continuer , table_predecesseurs[ N ] ;
      definir_couleur( NOIR ) ;
      taille = taille_graphe( G_9_flot ) ;

      /* Vérification de la forme du graphe. */

/* Les 3 lignes suivantes sont à décommenter une fois les fonctions écrites.
      assert( graphe_AR( G_9_flot ) ) ;
      assert( verifie_ponderation( G_9_flot ) ) ;
      parcours_profondeur_niveaux( G_9_flot , Sa ) ;
*/
/* Ces 2 lignes passent en commentaire au moment ou les précédentes sont activées. */
      for ( sommet = 1 ; sommet < taille ; sommet++ )
	  sommet_set_poids( G_9_flot , sommet , 1 ) ;

      for ( sommet = 0 ; sommet < taille ; sommet++ )
	  {assert( ! Sa || sommet_get_poids( G_9_flot , sommet ) > 0 ) ;
	   sommet_unset_poids( G_9_flot , sommet ) ;
	   assert( ! get_arc( G_9_flot , taille - 1 , sommet ) ) ;
	   assert( ! get_arc( G_9_flot , sommet , Sa ) ) ;
	  }

      /* La disposition des sommets est arrêtée et mémorisée. Les graphes de
	 flots et résiduels vont tous être affichés de la même manière. */

      definir_couleur( NOIR ) ;
      memorise_forme_graphe_flot( G_9_flot ) ;

      do {continuer = NON ;

	  /* Chaque itération utilise une nouvelle couleur
	     et alloue un nouveau graphe résiduel. */

          couleur_suivante( ) ;
	  t_gra graphe_residuel = nouveau_graphe_pondere( taille , - 100 , 100 ) ;

	  (void)printf( "Le graphe de flot donné :\n" ) ;
	  imprime_graphe( G_9_flot , DERNIERE_COULEUR , NON ) ;

	  /* Ici, on calcule le graphe résiduel. */

	  for ( i = 0 ; i < taille ; i++ )
	      for ( j = 0 ; j < taille ; j++ )
		  if ( i != j
		      && ( get_arc( G_9_flot , i , j ) || get_arc( G_9_flot , j , i ) ) )
		     calcule_residuel( G_9_flot , graphe_residuel , i , j ) ;

	  /* Ici, on calcule le meilleur chemin augmentant, à savoir celui
	     dont le maillon faible est aussi grand que possible.

	     Le tableau table_predecesseurs donne le prédécesseur de
	     chaque sommet le long du chemin retenu. */

	  for ( sommet = Sb ; sommet < taille ; sommet++ )
	      table_predecesseurs[ sommet ] = - 1 ;
	  table_predecesseurs[ Sa ] = Sa ;
	  dijkstra_maximise_le_min( Sa , graphe_residuel , table_predecesseurs ) ;

	  /* Si le chemin retenu ne permet pas de rejoindre le
	     puits, l'algorithme se termine. */

	  continuer = ( table_predecesseurs[ taille - 1 ] != - 1 ) ;

	  /* Le graphe résiduel est affiché avec le chemin augmentant en bleu. */

	  if ( continuer )
	     {sommet = taille - 1 ;
	      while ( sommet != Sa )
		    {set_couleur_arc( graphe_residuel , table_predecesseurs[ sommet ] ,
				      sommet , BLEU ) ;
		     sommet = table_predecesseurs[ sommet ] ;
		    }
	     }
	  (void)printf( "Le graphe résiduel et son meilleur chemin augmentant :\n" ) ;
	  imprime_graphe( graphe_residuel , DERNIERE_COULEUR , NON ) ;

	  /* Ici, on modifie le graphe de flot en changeant les flots le
	     long du chemin augmentant trouvé dans le graphe résiduel.

	     Le poids de modification poids_modif est la valeur du
	     maillon faible du chemin augmentant. Celle-ci correspond
	     au poids qui a été associé au puits lors du calcul du
	     du chemin augmentant. */

	  if ( continuer )
	     {int poids_modif = sommet_get_poids( graphe_residuel , taille - 1 ) ;
	      sommet = taille - 1 ;
	      while ( sommet != Sa )
		    {adapte_flot( G_9_flot , table_predecesseurs[ sommet ] ,
				 sommet , poids_modif ) ;
		     sommet = table_predecesseurs[ sommet ] ;
		    }
	     }

	  /* On jette le graphe résiduel et on recommence éventuellement. */

	  free( graphe_residuel ) ;
	 }
      while ( continuer ) ;

      /* L'affichage du résultat final. */

      (void)printf( "Le graphe de flot final où les arcs saturés sont en rouge :\n" ) ;
      imprime_graphe( G_9_flot , TOUT_NOIR , NON ) ;
      oublie_forme_graphe_flot( ) ;

     }

/* ------------------------------------------------------------ */
