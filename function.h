//...................characters' node..................

typedef struct character{
    char name[20]; // character name;
    struct character *next;
}character;

//...................palces' struct.....................

typedef struct place{
    int place_type;  // 0.empty    1.on light    2.off light   3.house    4.open pit    5. close pit    6.addition place     7.gate
    character *head; // This pointer holds characters that are in that palce; 
}place;
//...............global defined characters..............

character *JW, *IL, *WG, *JS, *SH, *JB, *MS, *SG;

//.................global variables.....................

int round_counter = 0; // goes until it reaches to 8;
int turn_counter = 0; // counts turns at each round; 
//..........two-dimensional array for places............

place map[13][9];
//.................functions.............................

void prepare_game(){ // This function should be called at the first of the game;
    map_loader();
    character_maker_1();
    first_place_set();
}
randomCard_maker(){
    // This function makes 4 random numbers at the begining of odd rounds and saves 4 other cards for next round;
    // 1:SERGENT GOODLEY     2:INSPECTEUR LESTRADE     3:SIR WILLIAM GULL       4:SHERLOCK HOLMES
    // 5:JEREMY BERT         6:JOHN H. WATSON           7:MISS STEALTHY            8:JOHN SMITH
    srand(time (NULL));
    int card1, card2, card3, card4, temp;
    int numbers[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    card1 = rand() % 8 + 1;
    do{
        temp = rand() % 8 + 1;
        if(temp != card1){
            card2 = temp;
            break;
        }
    }while(temp == card1);
    do{
        temp = rand() % 8 + 1;
        if(temp != card1 && temp != card2){
            card3 = temp;
            break;
        }
    }while(temp == card1 || temp == card2);
    do{
        temp = rand() % 8 + 1;
        if(temp != card1 && temp != card2 && temp != card3){
            card4 = temp;
            break;
        }
    }while(temp == card1 || temp == card2 || temp == card3);
}
void odd_round_card_printer(){

}
card_printer(){
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
even_round(){
    // This function is for even rounds and calls other functions. first is Mr.Jack's turn, then two times inspector and the again Mr.Jack;
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
            game();
            break;
    }

}
void get_choice(int choice){
    // this funtion gets the choice of user in the menu and calls the proper function;
}
int game(){
}
character* character_maker_2(char string[]){
character *temp = (character *) malloc(sizeof(character));
strcpy(temp -> name, string);
temp -> next = NULL;
return temp;
}
void character_maker_1(){
    JW = character_maker_2("JW");
    IL = character_maker_2("IL");
    WG = character_maker_2("WG");
    JS = character_maker_2("JS");
    SH = character_maker_2("SH");
    JB = character_maker_2("JB");
    MS = character_maker_2("MS");
    SG = character_maker_2("SG");
}
void first_place_set(){
map[4][4].head = JW;
map[4][4].head = IL;
map[4][8].head = WG;
map[6][3].head = SH;
map[6][6].head = JS;
map[8][5].head = JB;
map[8][1].head = MS;
map[12][5].head = SG; 
}
void character_info_printer(int a){ // This function prints characters' abilities;
    switch(a){
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