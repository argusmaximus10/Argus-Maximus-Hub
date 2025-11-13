
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