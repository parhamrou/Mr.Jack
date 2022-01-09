//...................palces' struct.....................

typedef struct place{
    int place_type;  // 0.empty    1.on light    2.off light   3.house    4.open manhole    5. close manhole    6.addition place     7.gate   
    int character;   // // 0:SERGENT GOODLEY     1:INSPECTEUR LESTRADE     2:SIR WILLIAM GULL       3:SHERLOCK HOLMES
                    // 4:JEREMY BERT         5:JOHN H. WATSON           6:MISS STEALTHY            7:JOHN SMITH
}place;
//...................characters' node....................

typedef struct card{
    int name; // number that is assigned to chaaracter;
    struct card *next;
}card;

//..................Enumerations........................

enum persons {SG, IL, WG, SH, JB, JW, MS, JS};
enum condition {empty, light_on, light_off, house, open, close, addition, gate};

//..................heads of two linked lists............

card *squad_head = NULL;
card *even_round_head = NULL;
card *odd_round_head = NULL;

//.................global variables.....................

int round_counter = 1; // goes until it reaches to 8;
int turn_counter = 0; // counts turns at each round;
bool visible_condition = true;
//..........two-dimensional array for places............

place map[13][9];
//.................functions.............................

void prepare_game(){ // This function should be called at the first of the game;
    map_loader();
    first_place_set();
    initial_linkedlist(); // unshuffled cards;
}
void randomCard_maker(){ // this function generates random cards;
    srand(time(NULL));
    for(int i = 8; i > -1; i--){
        int random_number = rand() % i;
        card_picker(random_number, i);
        if(i == 5){
            break;
        }
    }
    odd_round_head = squad_head; // set second linkedlist to four baghi cards;
}
void card_printer(){
    // This function prints the abilities of each character;
}
visible(){
    // This function shows that Mr.Jack is visible or not to find out that can Mr.Jack escape or not;
}
get_move(){
    // This function gets number of moves from user and shows him/her her options at each move;
}
EndOfgame_check(){
    // This function checks that is the game over or not;
}
odd_round(){
    // This function is four odd rounds and calls other functions. first is inspector's turn , then two times Mr.Jack and then again inspector;
}
even_round(){ // This function is for even rounds and calls other functions. first is Mr.Jack's turn, then two times inspector and the again Mr.Jack;
    randomCard_maker();
}
map_printer(){
    // This function prints the map after each action of characters;
}
int map_loader(){
    // This function loads the map at the begining of the game from txt file;
    FILE *fp = fopen("map.txt", "r");
    if(fp == NULL){
        printf("Can't open the file!\n");
        return -1;
    }
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 9; j++){
            fscanf(fp, "%d", &map[i][j].place_type);
        }
    }
    fclose(fp);
    return 0;
}
void menu(){
    // This function prints the menu and catches user's choice;
    int choice;
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t1.play with a friend\n\t\t\t\t\t\t\t\t\t\t\t0.exit");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            solo_game();
            break;
    }
}
int solo_game(){// solo game happens here ;)
    prepare_game();
    round_printer();
    even_round();

}
void character_info_printer(int card){ // This function prints characters' abilities;
    switch(card){
        case 1:
        printf("SG:\n");
        printf("1 To 3 moves And Ability Use (whistle)\n");
        printf("He can make other characters 3 moves closer to himself\n");
        break;

        case 2:
        printf("IL:\n");
        printf("1 To 3 Moves And Ability Use\n");
        printf("He can free one of the exits and block another one\n");
        break;

        case 3:
        printf("WG\n");
        printf("1 To 3 Moves Or Ability Use\n");
        printf("Instead of moving, He can changes his place with another character\n");
        break;

        case 4:
        printf("SH\n");
        printf("1 to 3 Moves then ability use\n");
        printf("He can draw the the top card from the alibi pile and note the character\n");
        break;

        case 5:
        printf("JB\n");
        printf("1 To 3 Moves And Ability Use\n");
        printf("He can open a manhole and closes another\n");
        break;

        case 6:
        printf("JH\n");
        printf("1 To 3 Moves Then Ability Use\n");
        printf("Watson carries a lantern, pictured on his character token. This lantern illuminates all the characters standing straight ahead of him!\n");
        break;

        case 7:
        printf("MS\n");
        printf("1 To 4 Moves With Optional Ability Use\n");
        printf("She can cross any hex but she must stop her movement on a street hex\n");
        break;

        case 8:
        printf("JS\n");
        printf(" 1 To 3 Moves And Ability Use\n");
        printf("He turns off a light and turn on another light\n");
        break;
    }
}
void round_printer(){//This function prints round and can Mr.Jack escape or not;
    printf("round%d\n", round_counter);
    if(visible_condition)
        printf("Mr.Jack is not visible and can escape this round!\n");
    else
        printf("Mr.jack is visible and can't escape! this round\n");
}
void first_place_set(){
    map[4][4].character = JW;
    map[4][4].character = IL;
    map[4][8].character = WG;
    map[6][3].character = SH;
    map[6][6].character = JS;
    map[8][5].character = JB;
    map[8][1].character = MS;
    map[12][5].character = SG; 
}
void even_round_linkedlist_creat(card* temp){ // first four cards linked list creator;
    temp -> next = NULL;
    if(even_round_head == NULL){
        even_round_head = temp;
    }
    else{
        card* next_node = even_round_head;
        while(next_node -> next != NULL)
            next_node = next_node -> next;
        next_node -> next = temp;
    }
}
initial_linkedlist(){ // contains linked list with eight
    card *temp, *next_node;
    int i = 0;
    while(i != 8){
        next_node = (card *) malloc(sizeof(card));
        next_node -> name = i;
        next_node -> next = NULL;
        if(squad_head == NULL){
            squad_head = temp = next_node;
        }
        else{
            temp -> next = next_node;
            temp = next_node;
        }
        i++;
    }
}
void card_picker(int card_number, int i){ // picks for and for cards for two rounds;
    if(card_number == 0){ // deleting first node;
        card *temp = squad_head;
        card *tmp = squad_head -> next;
        squad_head = tmp;
        even_round_linkedlist_creat(temp);   
    }
    else if(card_number == i - 1){ // deleting last node;
        card* temp = squad_head;
        card* tmp = squad_head;
        while(temp -> next != NULL)
            temp = temp -> next;
        while(tmp -> next != temp)
            tmp = tmp -> next;
        tmp -> next = NULL;
        even_round_linkedlist_creat(temp);
    }
    else{
        card* temp = squad_head;
        card* tmp = squad_head;
        for(int j = 0; j < card_number; j++){
            temp = temp -> next;
        }
        while(tmp -> next != temp)
            tmp = tmp -> next;
        tmp -> next = temp -> next;
        even_round_linkedlist_creat(temp);
    }
}