//
// EECS2031 team.c
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: <Saba Fallah>
// Student Info: <214663322>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//**********************************************************************
// Linked List Definitions 
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
struct player{
        char *family; 
        char *name;
        char pos;
        int value;
};

struct node{
        struct player current;
        struct node *next;
};




//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
void insert(struct node *node, struct node *head); //node to be inserted and head.
void print(struct node *head); //print
void delete(char *family, struct node *head); //delete the node with this family name.
void search(char *family, struct node *head); //search for player.
void svalue(int value, struct node *head); //values less than or equal.
void Quit(struct node *head);
//**********************************************************************
// Support Function Declarations
//

void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly 
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main (void)
{ 
    const char bannerString[]
        = "Personal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head.
    struct node *head = NULL;
    head = malloc(sizeof(struct node));

 
    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);
    
    char response;
    char input[MAX_LENGTH+1];
    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).
            char *family = malloc(sizeof(MAX_LENGTH+1));
            char *name = malloc(sizeof(MAX_LENGTH+1));
            char pos[MAX_LENGTH+1];
            int *value;
            
            /* this part asks for input */
            printf("  family name: ");  
            safegets(family, MAX_LENGTH+1);

            printf("  first name: ");
            safegets(name,MAX_LENGTH+1);

            printf("  position: ");
            safegets(pos, MAX_LENGTH+1);
            
            printf("  value: ");
            scanf("%d",&value);
            
           // struct node *node;
           //node =malloc(sizeof(struct node));
            struct player *player; //allocate memory for a player.
            player = malloc(sizeof(struct player));
            player->family = malloc(sizeof(char[MAX_LENGTH+1]));
            player->name = malloc(sizeof(char[MAX_LENGTH+1]));
            
            strcpy(player->family, family); //initializing the player
            strcpy(player->name, name);
            player->pos = *pos;
            player->value = value; 
            player->pos = toupper(player->pos); //pos to uppercase.
            if(player->pos != 'G' && player->pos != 'D' && player->pos != 'M' && player->pos != 'S'){
                printf("pos should be G or D or M or S. try again!");
                return;
            }
            
            struct node *node; //allocate memory for a node.
            node = malloc(sizeof(struct node));
            node->current = *player;
            node->next = NULL;
            
            insert(node, head);
            char buffer = getchar();
        }
        else if (response == 'D')
        {
            // Delete a player from the list.
            char *family = malloc(sizeof(MAX_LENGTH+1));
            printf("\nEnter family name for entry to delete: ");
            safegets(family, MAX_LENGTH+1);
            delete(family, head);
            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'S')
        {
            // Search for a player by family name.
            char *family = malloc(sizeof(MAX_LENGTH+1));
            printf("\nEnter family name to search for: ");
            safegets(family, MAX_LENGTH+1);
            search(family, head);

        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.
            int *value;
            printf("\nEnter value: ");
            scanf("%d", &value);
            svalue(value, head);
            

        }
        else if (response == 'P')
        {
            // Print the team.

           print(head);

        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else 
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');
  
    // Delete the whole linked list that hold the team.
    Quit(head);


    // Print the linked list to confirm deletion.
   print(head);


    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name 
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);
	
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.
void insert(struct node *node, struct node *head){
    
    struct node *current = malloc(sizeof(struct node));   //for my loops
    struct node *temp = malloc(sizeof(struct node));    //to keep my old nexts.
   
    if (head->current.family == NULL){
        
        *head = *node;
        //printf("%s", head->current.name);
        return;
    }
    else{
       //printf("in else");  
    current = head;
    
    while(current != NULL){ //duplicate error.
        if(strcmp(current->current.family, node->current.family) == 0){
           familyNameDuplicate(node->current.family);
           return;
        }
        current = current->next;
    }
    
    current = head;
    while(current != NULL){
    
    
        if (node->current.pos == 'G') {
            //printf("in G\n");
            if (current->current.pos == 'D' || current->current.pos == 'M' || current->current.pos == 'S'){

                *temp = *head;
                *head = *node; 
                head->next = temp;
            // printf("%s", head->current.name);
                return;
            }
            if (current->current.pos == 'G' && current->next == NULL){
                current->next= node;
                node->next = NULL;
            //    printf("%s", head->current.name);
                return;
            }
            if (current->current.pos == 'G' && (current->next->current.pos == 'D' || current->next->current.pos == 'M' || current->next->current.pos == 'S')){
                node->next = current->next;
                current->next = node;
            //    printf("%s", head->current.name);
                return;
            }
            else printf("");
        }

        if (node->current.pos == 'D') {


            if (current->current.pos == 'M' || current->current.pos == 'S'){
                *temp = *head;
                *head = *node; //??????????????????????????????????????????????????
                head->next = temp;
            //    printf("%s", head->current.name);
                return;
            }

            if (current->current.pos == 'G' && current->next == NULL){
                node->next = current->next;
                current->next = node;
            //    printf("%s", head->current.name);
                return;
            }

            if (current->current.pos == 'G' && (current->next->current.pos == 'M' || current->next->current.pos == 'S')){
                node->next = current->next;
                current->next = node;
            //    printf("%s", head->current.name);
                return;
            }
            if (current->current.pos == 'D' && current->next == NULL){
                current->next= node;
                node->next = NULL;
            //    printf("%s", head->current.name);
                return;
            }
            if (current->current.pos == 'D' && (current->next->current.pos == 'M' || current->next->current.pos == 'S')){
                node->next = current->next;
                current->next = node;
            //    printf("%s", head->current.name);
                return;
            }
            else printf("");
        }

        if (node->current.pos == 'M') {
            if (current->current.pos == 'S'){
                *temp = *head;
                *head = *node; 
                head->next = temp;
            //    printf("%s", head->current.name);
                return;
            }
            if (current->current.pos == 'M' && current->next == NULL){
                current->next= node;
                node->next = NULL;
            //    printf("%s", head->current.name);
                return;
            }

            if ((current->current.pos == 'G' || current->current.pos == 'D') && current->next == NULL){
                node->next = current->next;
                current->next = node;
            //    printf("%s", head->current.name);
                return;
            }

            if ((current->current.pos == 'G' || current->current.pos == 'D') && current->next->current.pos == 'S'){
                node->next = current->next;
                current->next = node;
            //    printf("%s", head->current.name);
                return;
            }
            if (current->current.pos == 'M' && current->next->current.pos == 'S'){
                node->next = current->next;
                current->next = node;
            //    printf("%s", head->current.name);
                return;
            }
            else printf("");
        }

        if (node->current.pos == 'S'){
            if (current->next == NULL){
                current->next = node;
                node->next = NULL;
            //    printf("%s", head->current.name);
                return;
            }
        }
        current = current->next;
    }
}
}

void print(struct node *head){
    struct node *temp;
    temp = malloc(sizeof(struct node));
    *temp = *head;
    if(temp->current.family == NULL) printTeamEmpty (); //empty team.
    else{
        while(temp != NULL){
        printf("player's last name: %s\n", temp->current.family);
        printf("player's first name: %s\n", temp->current.name);
        printf("player's position: %c\n", temp->current.pos);
        printf("player's value: %d\n", temp->current.value);
        printf("\n");
        temp = temp->next ;
    }
  }
} 

void delete(char *family, struct node *head){
    struct node *toDelete;
    //toDelete = malloc(sizeof(struct node));
           
    struct node *temp;
    temp = malloc(sizeof(struct node));
    temp = head;
    if(head->current.family == NULL) familyNameNotFound(head->current.family);
    if(strcmp(head->current.family, family)==0){ //head to be deleted
        
        toDelete = head;
        familyNameDeleted(head->current.family);
        printf("%s", toDelete->current.family);
        if(head->next->current.family != NULL){
            struct node *t;
            t = malloc(sizeof(struct node));
           *t = *head->next;
            *head = *t;
        //printf("%s", head->current.family);
        }
        else if(head->next->current.family == NULL){
           struct node *temp = head->next;
           head->current    = temp->current;
           head->next    = temp->next;
           free(temp);
        }
        
        
        /* Clears the memory occupied by first node*/
        //free(toDelete);
        
        
        return;
    }
    else{
    while(temp->next != NULL){
         if(strcmp(temp->next->current.family, family) == 0){ //right family.
             toDelete = temp->next;
           // printf("c");
           familyNameDeleted(temp->next->current.family);
           temp->next = temp->next->next;
           free(toDelete);
           return; 
        }
        
        else temp = temp->next;
    }
   }
     familyNameNotFound(head->current.family);  
}
void search(char *family, struct node *head){
    if(head->current.family == NULL) {
        familyNameNotFound(family);
        return;
    }
    struct node *temp;
    temp = malloc(sizeof(struct node));
    *temp = *head;
    while(temp != NULL){
        if(strcmp(temp->current.family, family)==0){
          printf("player's last name: %s\n", temp->current.family);
          printf("player's first name: %s\n", temp->current.name);
          printf("player's position: %c\n", temp->current.pos);
          printf("player's value: %d\n", temp->current.value);
          printf("\n");
          return  ;
        }
         temp = temp->next ;
    }
    familyNameNotFound(family);
}

void svalue(int value, struct node *head){
    if(head->current.family == NULL) {
        printNoPlayersWithLowerValue(value);
        return;
    }
    struct node *temp;
    temp = malloc(sizeof(struct node));
    *temp = *head;
    int count = 0;
    while(temp != NULL){
        if(temp->current.value <= value){
          printf("player's last name: %s\n", temp->current.family);
          printf("player's first name: %s\n", temp->current.name);
          printf("player's position: %c\n", temp->current.pos);
          printf("player's value: %d\n", temp->current.value);
          printf("\n");
          count++;
        }
        
        temp = temp->next ;
    }
    if(count == 0) printNoPlayersWithLowerValue(value);
    //return;
}
void Quit(struct node *head){    

    while(head != NULL) {  
        struct node *current = head;      
        free(head->current.family);
        free(head->current.name);
        head = head->next; 
        free(current);       
    }
    
    return;
}

    
    
    
   
    

