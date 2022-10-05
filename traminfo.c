#include "traminfo.h"
/*Create a Tram*/
struct Tram* createTram(char *id, char *loc, int count) {
    struct Tram * temp = (struct Tram *) malloc (sizeof (struct Tram));
    if(temp == NULL)
        return NULL;

    temp->tram_id = (char *) malloc (32);
    if(temp->tram_id == NULL)   
        return NULL;
    temp->location = (char *) malloc (64);
    if(temp->location == NULL)
        return NULL; 

    if(strlen(id)) {
        strcpy(temp->tram_id, id);
    }else {
        temp->tram_id = "";
    }

    if(strlen(loc)) {
        strcpy(temp->location, loc);
    }else {
        temp->location = "";
    }

    temp->next = NULL;
    temp->passenger_count = count;
    return temp;
}
/*Insert the node */
void insert(struct Tram** root, char *id, char * loc, int count, bool islocation) {
        struct Tram *temp = NULL;
        bool isTramfound = false;
        if(*root==NULL) {
            *root=createTram(id, loc, count);
            return;
        }
        /*Search the list */
        temp = *root;
        while(temp) {
            if (!strcmp(temp->tram_id, id)) {
                isTramfound = true;
                break;
            }
            temp=temp->next;     
        }           
        
        if(!isTramfound) { 
            temp = createTram(id, loc, count);
            temp->next = *root;
            *root=temp;
        } else {
            if(islocation) {
                strcpy(temp->location, loc);
            } else {
                temp->passenger_count = count; 
            }
        }
}
/*display */
void display(struct Tram** root) {
    struct Tram * temp = *root;
    if (root == NULL) {
        printf("No Trams present \n");
    }
    while(temp != NULL)  {
        printf("%s:\n", temp->tram_id);
        printf("\tLocation: %s\n",temp->location);
        printf("\tPassenger count:%d\n",temp->passenger_count);
        temp = temp->next;
    }
}
/*Update details*/
void update(struct Tram**root, char *id, char *loc, int count ) {
    struct Tram * temp = *root;
    bool isTramfound = false;
    if(*root == NULL) {
        return; /* Nothing to update*/
    }
    
    while(temp) {
        if (!strcmp(temp->tram_id, id)) {
            isTramfound = true;
            break;
        }
        temp=temp->next;     
    }
   
    if(isTramfound) {
        strcpy(temp->location, loc);
        strcpy(temp->tram_id, id);
        temp->passenger_count = count; 
    } else {
        printf("Tram not found %s\n", id);
    }
}


#if 0
int main() {

    struct Tram *root = NULL;
    
    display(&root);         
    insert(&root, "Tram 1", "Williams Street", 50);
    insert(&root, "Tram 2", "Flinders Street", 22);

    display(&root);         
    update(&root, "Tram 2", "Flinders Street", 24);
    update(&root, "Tram 3", "Flinders Street", 24);
    display(&root);         
    return 0;
}
#endif 
