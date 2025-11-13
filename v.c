#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct vol vol;
typedef struct commande commande;
typedef struct utilisateur utilisateur;


typedef struct utilisateur {
    char *CIN;
    char *nom;
    char *prenom;
    char* num_tele;
    char*email;
    int age;
    char *passeport;
}utilisateur ;


typedef struct commande {
    int id;
    utilisateur *nom;
    vol *vole;
    commande *prev;
    commande *next;
}commande;

typedef struct time {
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    int seconde;
} time;

typedef struct montant {
    float eco;
    float business;
    float luxury;
} montant;


void saisirMontant(montant *m) {
    printf("Entrez le montant pour la classe économique : ");
    scanf("%f", &m->eco);
    getchar(); // Pour consommer le \n

    printf("Entrez le montant pour la classe business : ");
    scanf("%f", &m->business);
    getchar();

    printf("Entrez le montant pour la classe luxe : ");
    scanf("%f", &m->luxury);
    getchar();
}

void afficherMontant(montant m) {
    printf("Montant classe économique : %.2f\n", m.eco);
    printf("Montant classe business   : %.2f\n", m.business);
    printf("Montant classe luxe       : %.2f\n", m.luxury);
}

void afficherTemps(time t) {
    printf("Date : %02d/%02d/%04d\n", t.jour, t.mois, t.annee);
    printf("Heure : %02d:%02d:%02d\n", t.heure, t.minute, t.seconde);
}

typedef struct aeroport {
    char aeroport[100];
    struct aeroport *next;
    struct aeroport *prev;
} aeroport;

typedef struct classe {
    int economique;
    int busness;
    int luxury;
} classe;

typedef struct pilote {
    int id;
    char nom[50];
    char prenom[50];
    struct pilote *prev;
    struct pilote *next;
} pilote;

typedef struct plane {
    int matricule;
    classe siege;
    struct plane *next;
    struct plane *prev;
} plane;

typedef struct vol {
    int id;
    aeroport *depart;
    char arrive[100];
    time heur_depart;
    time heur_arrive;
    plane *id_plane; 
    pilote *id_pilote;
    montant prix;
    struct vol *next;
    struct vol *prev;
} vol;

aeroport *ajout_aeroport(aeroport *head) {
    aeroport *new_node = (aeroport*)malloc(sizeof(aeroport));
    if (!new_node) {
        printf("Erreur d'allocation mémoire\n");
        return head;
    }

    printf("Saisir le nom de l'aéroport : ");
    getchar(); // Pour consommer le \n précédent
    fgets(new_node->aeroport, sizeof(new_node->aeroport), stdin);
    new_node->aeroport[strcspn(new_node->aeroport, "\n")] = '\0'; // Supprimer le \n

    new_node->next = NULL;
    new_node->prev = NULL;

    if (!head) {
        return new_node;
    } else {
        aeroport *temp = head;
        while (temp->next) {
            if (strcmp(temp->aeroport, new_node->aeroport) == 0) {
                printf("Erreur: l'aéroport existe déjà\n");
                free(new_node);
                return head;
            }
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
        return head;
    }
}

void afficher_aeroport(aeroport *head) {
    aeroport* temp = head;
    while(temp) {
        printf("%s\n", temp->aeroport);
        temp = temp->next;
    }
}

aeroport* verification_saisie_aeroport(aeroport *head, char nom[]) {
    aeroport* temp = head;
    while(temp) {
        if (strcmp(temp->aeroport, nom) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Aéroport n'existe pas\n");
    return NULL;
}

pilote *ajout_pilote(pilote *head) {
    pilote *new_node = (pilote*)malloc(sizeof(pilote));
    if (!new_node) {
        printf("Erreur d'allocation mémoire\n");
        return head;
    }

    // Trouver le prochain ID disponible
    int max_id = 0;
    pilote *temp = head;
    while (temp) {
        if (temp->id >= max_id) {
            max_id = temp->id + 1;
        }
        temp = temp->next;
    }
    new_node->id = max_id;

    printf("Saisir le nom : ");
    getchar();
    fgets(new_node->nom, sizeof(new_node->nom), stdin);
    new_node->nom[strcspn(new_node->nom, "\n")] = '\0';

    printf("Saisir le prénom : ");
    fgets(new_node->prenom, sizeof(new_node->prenom), stdin);
    new_node->prenom[strcspn(new_node->prenom, "\n")] = '\0';

    new_node->next = NULL;
    new_node->prev = NULL;

    if (!head) {
        return new_node;
    } else {
        temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
        return head;
    }
}

pilote *supp_pilote(int id, pilote *head) {
    if (!head) {
        printf("Il n'existe aucun pilote\n");
        return NULL;
    }

    pilote *temp = head;
    while (temp && temp->id != id) {
        temp = temp->next;
    }

    if (!temp) {
        printf("Pilote n'existe pas\n");
        return head;
    }

    if (temp == head) {
        head = head->next;
        if (head) {
            head->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
    }

    free(temp);
    return head;
}

void afficher_pilote(pilote *head) {
    pilote *temp = head;
    while(temp) {  
        printf("Matricule:%d \t Nom:%s \t Prénom:%s\n", temp->id, temp->nom, temp->prenom);
        temp = temp->next;
    }
}

pilote* verification_saisie_pilote(pilote *head, int id) {
    pilote *temp = head;
    while(temp) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Pilote n'existe pas\n");
    return NULL;
}

plane* ajout_plane(plane *head) {
    plane *new_node = (plane*)malloc(sizeof(plane));
    if (!new_node) {
        printf("Erreur d'allocation mémoire\n");
        return head;
    }

    printf("Saisir le matricule : ");
    scanf("%d", &new_node->matricule);
    getchar();

    printf("Saisir le nombre de sièges (eco/business/luxury) : ");
    scanf("%d %d %d", &new_node->siege.economique, &new_node->siege.busness, &new_node->siege.luxury);
    getchar();

    new_node->next = NULL;
    new_node->prev = NULL;

    // Vérifier si le matricule existe déjà
    plane *temp = head;
    while (temp) {
        if (temp->matricule == new_node->matricule) {
            printf("Erreur: cet avion existe déjà\n");
            free(new_node);
            return head;
        }
        temp = temp->next;
    }

    if (!head) {
        return new_node;
    } else {
        temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
        return head;
    }
}

plane *supp_plane(int matricule, plane *head) {
    if (!head) {
        printf("Erreur: il n'existe aucun avion\n");
        return NULL;
    }

    plane *temp = head;
    while (temp && temp->matricule != matricule) {
        temp = temp->next;
    }

    if (!temp) {
        printf("Erreur: l'avion n'existe pas\n");
        return head;
    }

    if (temp == head) {
        head = head->next;
        if (head) {
            head->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
    }

    free(temp);
    return head;
}

void afficher_plane(plane *head) {
    plane *temp = head;
    while(temp) {  
        printf("Matricule:%d \t Sièges: eco:%d\t business:%d \t luxury:%d\n", 
               temp->matricule, temp->siege.economique, temp->siege.busness, temp->siege.luxury);
        temp = temp->next;
    }
}

plane* verification_saisie_plane(plane* head, int id) {
    plane *temp = head;
    while(temp) {
        if (temp->matricule == id) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Avion n'existe pas\n");
    return NULL;
}

vol *ajout_vole(vol *head, aeroport *head_aeroport, plane *head_plane, pilote *head_pilote) {
    vol *new_vol = (vol*)malloc(sizeof(vol));
    if (!new_vol) {
        printf("Erreur d'allocation mémoire\n");
        return head;
    }

    // Trouver le prochain ID disponible
    int max_id = 0;
    vol *temp_vol = head;
    while (temp_vol) {
        if (temp_vol->id >= max_id) {
            max_id = temp_vol->id + 1;
        }
        temp_vol = temp_vol->next;
    }
    new_vol->id = max_id;

    // Saisie de l'arrivée
    printf("Saisir la destination : ");
    getchar();
    fgets(new_vol->arrive, sizeof(new_vol->arrive), stdin);
    new_vol->arrive[strcspn(new_vol->arrive, "\n")] = '\0';

    // Saisie de l'aéroport de départ
    afficher_aeroport(head_aeroport);
    char depart_temp[100];
    aeroport *depart_ptr = NULL;
    do {
        printf("Saisir le nom de l'aéroport de départ : ");
        fgets(depart_temp, sizeof(depart_temp), stdin);
        depart_temp[strcspn(depart_temp, "\n")] = '\0';
        depart_ptr = verification_saisie_aeroport(head_aeroport, depart_temp);
    } while (!depart_ptr);
    new_vol->depart = depart_ptr;

    // Saisie de l'avion
    afficher_plane(head_plane);
    int plane_id;
    plane *plane_ptr = NULL;
    do {
        printf("Saisir le matricule de l'avion : ");
        scanf("%d", &plane_id);
        getchar();
        plane_ptr = verification_saisie_plane(head_plane, plane_id);
    } while (!plane_ptr);
    new_vol->id_plane = plane_ptr;

    // Saisie du pilote
    afficher_pilote(head_pilote);
    int pilote_id;
    pilote *pilote_ptr = NULL;
    do {
        printf("Saisir l'ID du pilote : ");
        scanf("%d", &pilote_id);
        getchar();
        pilote_ptr = verification_saisie_pilote(head_pilote, pilote_id);
    } while (!pilote_ptr);
    new_vol->id_pilote = pilote_ptr;

    // Saisie de l'heure de départ
    do {
        printf("Saisir l'heure de départ (jj/mm/aaaa hh:mm:ss) : ");
        scanf("%d/%d/%d %d:%d:%d", 
              &new_vol->heur_depart.jour, 
              &new_vol->heur_depart.mois, 
              &new_vol->heur_depart.annee,
              &new_vol->heur_depart.heure,
              &new_vol->heur_depart.minute,
              &new_vol->heur_depart.seconde);
        getchar();
    } while((new_vol->heur_depart.jour > 31 || new_vol->heur_depart.jour < 1) ||
            (new_vol->heur_depart.mois < 1 || new_vol->heur_depart.mois > 12) ||
            (new_vol->heur_depart.annee < 2025) ||
            (new_vol->heur_depart.heure > 23 || new_vol->heur_depart.heure < 0) || 
            (new_vol->heur_depart.minute < 0 || new_vol->heur_depart.minute > 59) ||
            (new_vol->heur_depart.seconde < 0 || new_vol->heur_depart.seconde > 59));

    // Saisie de l'heure d'arrivée
    do {
        printf("Saisir l'heure d'arrivée (jj/mm/aaaa hh:mm:ss) : ");
        scanf("%d/%d/%d %d:%d:%d", 
              &new_vol->heur_arrive.jour, 
              &new_vol->heur_arrive.mois, 
              &new_vol->heur_arrive.annee,
              &new_vol->heur_arrive.heure,
              &new_vol->heur_arrive.minute,
              &new_vol->heur_arrive.seconde);
        getchar();
    } while((new_vol->heur_arrive.jour > 31 || new_vol->heur_arrive.jour < 1) ||
            (new_vol->heur_arrive.mois < 1 || new_vol->heur_arrive.mois > 12) ||
            (new_vol->heur_arrive.annee < 2025) ||
            (new_vol->heur_arrive.heure > 23 || new_vol->heur_arrive.heure < 0) || 
            (new_vol->heur_arrive.minute < 0 || new_vol->heur_arrive.minute > 59) ||
            (new_vol->heur_arrive.seconde < 0 || new_vol->heur_arrive.seconde > 59));

    // Saisie des prix
    saisirMontant(&new_vol->prix);

    new_vol->next = NULL;
    new_vol->prev = NULL;

    if (!head) {
        return new_vol;
    } else {
        temp_vol = head;
        while (temp_vol->next) {
            temp_vol = temp_vol->next;
        }
        temp_vol->next = new_vol;
        new_vol->prev = temp_vol;
        return head;
    }
}

vol* chercher_vol(vol* head, int id) {
    vol* temp = head;
    while(temp) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    printf("Vol n'existe pas\n");
    return NULL;
}
vol*  recherche_vol_arriver(vol*head,char *arriver)
{
    vol*temp=head;
    while(temp)
    {
        if(strcasecmp(temp->arrive,arriver)==0)
        {
            return temp;
        }
        temp=temp->next;
    }
    printf("Vol n'existe pas\n");
    return NULL;
}
vol *supp_vol(vol* head) {
    if (!head) {
        printf("Il n'existe aucun vol\n");
        return NULL;
    }

    int id;
    vol *temp = NULL;
    do {
        printf("Saisir l'id du vol à supprimer : ");
        scanf("%d", &id);
        getchar();
        temp = chercher_vol(head, id);
    } while(!temp);

    if (temp == head) {
        head = head->next;
        if (head) {
            head->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
    }

    free(temp);
    return head;
}

void affichage_vol(vol* temp) {
    if (!temp) {
        printf("Aucun vol à afficher\n");
        return;
    }
    
    printf("ID:%d\t Aéroport de départ:%s\t Destination:%s\n", 
           temp->id, temp->depart->aeroport, temp->arrive);
    printf("Heure de départ : ");
    afficherTemps(temp->heur_depart);
    printf("Heure d'arrivée : ");
    afficherTemps(temp->heur_arrive);
    printf("Avion : Matricule %d\n", temp->id_plane->matricule);
    printf("Pilote : %s %s (ID:%d)\n", 
           temp->id_pilote->prenom, temp->id_pilote->nom, temp->id_pilote->id);
    printf("Prix : \n");
    afficherMontant(temp->prix);
    printf("----------------------------------------\n");
}

vol* modife_vol(vol *head, plane *head_plane, pilote *head_pilote, aeroport *head_aeroport) {   
    int id;
    printf("Saisir l'id du vol à modifier : ");
    scanf("%d", &id);
    getchar();
    
    vol* temp = chercher_vol(head, id);
    if (!temp) {
        return head;
    }

    // Modification de la destination
    printf("Nouvelle destination (actuelle: %s) : ", temp->arrive);
    fgets(temp->arrive, sizeof(temp->arrive), stdin);
    temp->arrive[strcspn(temp->arrive, "\n")] = '\0';

    // Modification de l'aéroport de départ
    afficher_aeroport(head_aeroport);
    char depart_temp[100];
    aeroport *depart_ptr = NULL;
    do {
        printf("Nouvel aéroport de départ (actuel: %s) : ", temp->depart->aeroport);
        fgets(depart_temp, sizeof(depart_temp), stdin);
        depart_temp[strcspn(depart_temp, "\n")] = '\0';
        depart_ptr = verification_saisie_aeroport(head_aeroport, depart_temp);
    } while (!depart_ptr);
    temp->depart = depart_ptr;

    // Modification de l'avion
    afficher_plane(head_plane);
    int plane_id;
    plane *plane_ptr = NULL;
    do {
        printf("Nouveau matricule de l'avion (actuel: %d) : ", temp->id_plane->matricule);
        scanf("%d", &plane_id);
        getchar();
        plane_ptr = verification_saisie_plane(head_plane, plane_id);
    } while (!plane_ptr);
    temp->id_plane = plane_ptr;

    // Modification du pilote
    afficher_pilote(head_pilote);
    int pilote_id;
    pilote *pilote_ptr = NULL;
    do {
        printf("Nouvel ID du pilote (actuel: %d) : ", temp->id_pilote->id);
        scanf("%d", &pilote_id);
        getchar();
        pilote_ptr = verification_saisie_pilote(head_pilote, pilote_id);
    } while (!pilote_ptr);
    temp->id_pilote = pilote_ptr;

    // Modification de l'heure de départ
    do {
        printf("Nouvelle heure de départ (actuelle: %02d/%02d/%04d %02d:%02d:%02d) : ", 
              temp->heur_depart.jour, temp->heur_depart.mois, temp->heur_depart.annee,
              temp->heur_depart.heure, temp->heur_depart.minute, temp->heur_depart.seconde);
        scanf("%d/%d/%d %d:%d:%d", 
              &temp->heur_depart.jour, 
              &temp->heur_depart.mois, 
              &temp->heur_depart.annee,
              &temp->heur_depart.heure,
              &temp->heur_depart.minute,
              &temp->heur_depart.seconde);
        getchar();
    } while((temp->heur_depart.jour > 31 || temp->heur_depart.jour < 1) ||
            (temp->heur_depart.mois < 1 || temp->heur_depart.mois > 12) ||
            (temp->heur_depart.annee < 2025) ||
            (temp->heur_depart.heure > 23 || temp->heur_depart.heure < 0) || 
            (temp->heur_depart.minute < 0 || temp->heur_depart.minute > 59) ||
            (temp->heur_depart.seconde < 0 || temp->heur_depart.seconde > 59));

    // Modification de l'heure d'arrivée
    do {
        printf("Nouvelle heure d'arrivée (actuelle: %02d/%02d/%04d %02d:%02d:%02d) : ", 
              temp->heur_arrive.jour, temp->heur_arrive.mois, temp->heur_arrive.annee,
              temp->heur_arrive.heure, temp->heur_arrive.minute, temp->heur_arrive.seconde);
        scanf("%d/%d/%d %d:%d:%d", 
              &temp->heur_arrive.jour, 
              &temp->heur_arrive.mois, 
              &temp->heur_arrive.annee,
              &temp->heur_arrive.heure,
              &temp->heur_arrive.minute,
              &temp->heur_arrive.seconde);
        getchar();
    } while((temp->heur_arrive.jour > 31 || temp->heur_arrive.jour < 1) ||
            (temp->heur_arrive.mois < 1 || temp->heur_arrive.mois > 12) ||
            (temp->heur_arrive.annee < 2025) ||
            (temp->heur_arrive.heure > 23 || temp->heur_arrive.heure < 0) || 
            (temp->heur_arrive.minute < 0 || temp->heur_arrive.minute > 59) ||
            (temp->heur_arrive.seconde < 0 || temp->heur_arrive.seconde > 59));

    // Modification des prix
    printf("Nouveaux prix : \n");
    saisirMontant(&temp->prix);

    return head;
}

void liberer_aeroports(aeroport *head) {
    aeroport *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void liberer_pilotes(pilote *head) {
    pilote *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void liberer_avions(plane *head) {
    plane *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void liberer_vols(vol *head) {
    vol *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

utilisateur* saisirUtilisateur() {
    utilisateur *user = (utilisateur*)malloc(sizeof(utilisateur));
    if (!user) {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }

    char buffer[100];

    // Saisie du CIN
    printf("Saisir le CIN : ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Supprimer le saut de ligne
    user->CIN = strdup(buffer);

    // Saisie du nom
    printf("Saisir le nom : ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    user->nom = strdup(buffer);

    // Saisie du prénom
    printf("Saisir le prénom : ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    user->prenom = strdup(buffer);

    // Saisie du numéro de téléphone
    printf("Saisir le numéro de téléphone : ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    user->num_tele = strdup(buffer);

    // Saisie de l'email
    printf("Saisir l'email : ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    user->email = strdup(buffer);

    // Saisie de l'âge
    printf("Saisir l'âge : ");
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &user->age) == 1) {
            break;
        }
        printf("Âge invalide. Veuillez réessayer : ");
    }

    // Saisie du numéro de passeport
    printf("Saisir le numéro de passeport : ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    user->passeport = strdup(buffer);

    return user;
}
commande* inserer_commande(commande *head, vol* head_vol) {
    commande *new_cmd = (commande*)malloc(sizeof(commande));
    if (!new_cmd) {
        printf("Erreur d'allocation mémoire\n");
        return head;
    }

    // Trouver le prochain ID disponible
    int max_id = 0;
    commande *temp_cmd = head;
    while (temp_cmd) {
        if (temp_cmd->id >= max_id) {
            max_id = temp_cmd->id + 1;
        }
        temp_cmd = temp_cmd->next;
    }
    new_cmd->id = max_id;

    // Recherche du vol
    char arrive[100];
    vol *temp_vol = NULL;
    
    do {
        printf("Saisir la destination : ");
        fgets(arrive, sizeof(arrive), stdin);
        arrive[strcspn(arrive, "\n")] = '\0';
        
        temp_vol = recherche_vol_arriver(head_vol, arrive);
        if (temp_vol) {
            affichage_vol(temp_vol);
        }
    } while (!temp_vol);

    int idd;
    do {
        printf("Saisir l'id du vol choisi : ");
        scanf("%d", &idd);
        getchar();
        new_cmd->vole = chercher_vol(head_vol, idd);
    } while(!new_cmd->vole);

    printf("Saisir vos informations personnelles :\n");
    new_cmd->nom = saisirUtilisateur();

    new_cmd->next = NULL;
    new_cmd->prev = NULL;

    if (!head) {
        return new_cmd;
    } else {
        temp_cmd = head;
        while (temp_cmd->next) {
            temp_cmd = temp_cmd->next;
        }
        temp_cmd->next = new_cmd;
        new_cmd->prev = temp_cmd;
        return head;
    }
}

void menu_principal()
{
    printf("WELCOME TO AEROLUX\n");
    printf("1. ADMIN\n");
    printf("2. USER\n");
    printf("3. Quitter\n");  // Added missing newline
    printf("Choix : ");
}

void menu_principal_gvol() {
    printf("\n=== SYSTEME DE GESTION DE VOLS ===\n");
    printf("1. Gestion des vols\n");
    printf("2. Gestion des avions\n");
    printf("3. Gestion des pilotes\n");
    printf("4. Gestion des aeroports\n");
    printf("5. Quitter\n");
    printf("Choix : ");
}

int main() {
    aeroport *liste_aeroports = NULL;
    plane *liste_avions = NULL;
    pilote *liste_pilotes = NULL;
    vol *liste_vols = NULL;
    commande *liste_commande = NULL;  // Initialized to NULL
    
    int choix;
    
    do {
        menu_principal();
        scanf("%d", &choix);
        getchar(); // Pour consommer le \n
        
        switch(choix) {
            case 1: { 
                int admin_choice;
                do {
                    menu_principal_gvol();
                    scanf("%d", &admin_choice);
                    getchar();
                    
                    switch(admin_choice) {
                        case 1: {
                            // Gestion des vols
                            int sous_choix;
                            do {
                                printf("\n=== GESTION DES VOLS ===\n");
                                printf("1. Ajouter un vol\n");
                                printf("2. Supprimer un vol\n");
                                printf("3. Modifier un vol\n");
                                printf("4. Afficher tous les vols\n");
                                printf("5. Retour\n");
                                printf("Choix : ");
                                scanf("%d", &sous_choix);
                                getchar();
                                
                                switch(sous_choix) {
                                    case 1:
                                        liste_vols = ajout_vole(liste_vols, liste_aeroports, liste_avions, liste_pilotes);
                                        break;
                                    case 2:
                                        liste_vols = supp_vol(liste_vols);
                                        break;
                                    case 3:
                                        liste_vols = modife_vol(liste_vols, liste_avions, liste_pilotes, liste_aeroports);
                                        break;
                                    case 4: {
                                        vol *temp = liste_vols;
                                        while(temp) {
                                            affichage_vol(temp);
                                            temp = temp->next;
                                        }
                                        break;
                                    }
                                    case 5:
                                        break;
                                    default:
                                        printf("Choix invalide!\n");
                                }
                            } while(sous_choix != 5);
                            break;
                        }
                        case 2: {
                            // Gestion des avions
                            int sous_choix;
                            do {
                                printf("\n=== GESTION DES AVIONS ===\n");
                                printf("1. Ajouter un avion\n");
                                printf("2. Supprimer un avion\n");
                                printf("3. Afficher tous les avions\n");
                                printf("4. Retour\n");
                                printf("Choix : ");
                                scanf("%d", &sous_choix);
                                getchar();
                                
                                switch(sous_choix) {
                                    case 1:
                                        liste_avions = ajout_plane(liste_avions);
                                        break;
                                    case 2: {
                                        int matricule;
                                        printf("Saisir le matricule de l'avion à supprimer : ");
                                        scanf("%d", &matricule);
                                        getchar();
                                        liste_avions = supp_plane(matricule, liste_avions);
                                        break;
                                    }
                                    case 3:
                                        afficher_plane(liste_avions);
                                        break;
                                    case 4:
                                        break;
                                    default:
                                        printf("Choix invalide!\n");
                                }
                            } while(sous_choix != 4);
                            break;
                        }
                        case 3: {
                            // Gestion des pilotes
                            int sous_choix;
                            do {
                                printf("\n=== GESTION DES PILOTES ===\n");
                                printf("1. Ajouter un pilote\n");
                                printf("2. Supprimer un pilote\n");
                                printf("3. Afficher tous les pilotes\n");
                                printf("4. Retour\n");
                                printf("Choix : ");
                                scanf("%d", &sous_choix);
                                getchar();
                                
                                switch(sous_choix) {
                                    case 1:
                                        liste_pilotes = ajout_pilote(liste_pilotes);
                                        break;
                                    case 2: {
                                        int id;
                                        printf("Saisir l'id du pilote à supprimer : ");
                                        scanf("%d", &id);
                                        getchar();
                                        liste_pilotes = supp_pilote(id, liste_pilotes);
                                        break;
                                    }
                                    case 3:
                                        afficher_pilote(liste_pilotes);
                                        break;
                                    case 4:
                                        break;
                                    default:
                                        printf("Choix invalide!\n");
                                }
                            } while(sous_choix != 4);
                            break;
                        }
                        case 4: {
                            // Gestion des aeroports
                            int sous_choix;
                            do {
                                printf("\n=== GESTION DES AEROPORTS ===\n");
                                printf("1. Ajouter un aeroport\n");
                                printf("2. Afficher tous les aeroports\n");
                                printf("3. Retour\n");
                                printf("Choix : ");
                                scanf("%d", &sous_choix);
                                getchar();
                                
                                switch(sous_choix) {
                                    case 1:
                                        liste_aeroports = ajout_aeroport(liste_aeroports);
                                        break;
                                    case 2:
                                        afficher_aeroport(liste_aeroports);
                                        break;
                                    case 3:
                                        break;
                                    default:
                                        printf("Choix invalide!\n");
                                }
                            } while(sous_choix != 3);
                            break;
                        }
                        case 5:
                            printf("Retour au menu principal...\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez reessayer.\n");
                    }
                } while(admin_choice != 5);
                break;
            }
            case 2:
                liste_commande = inserer_commande(liste_commande, liste_vols);
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while(choix != 3);  // You might want to add an exit option
    
    // Libération de la mémoire
    // Add code to free all allocated memory here
    
    return 0;
}