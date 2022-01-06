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
//...............global defined character..............

character *JW, *IL, *WG, *JS, *SH, *JB, *MS, *SG;

//..........two-dimensional array for places............

place map[13][9];
//.................functions.............................

void prepare_game(){
    map_loader();
    character_maker_1();
    first_place_set();
}
randomCard_maker(){
    // This function makes 4 random numbers at the begining of odd rounds and save 4 other cards for next round;
    // 1:SERGENT GOODLEY     2:INSPECTEUR LESTRADE     3:SIR WILLIAM GULL       4:SHERLOCK HOLMES
    // 5:JEREMY BERT         6:JOHN H. WATSON           7:MISS STEALTHY            8:JOHN SMITH
    srand(time (NULL));
    int card1, card2, card3, card4, temp;
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
card_printer(){
    // This function prints the abilities of each character;
}
round_counter(){
    // this function counts the rounds until 8;
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
    // This function just prints the menu;
}
void get_choice(int choice){
    // this funtion gets the choice of user in the menu and calls the proper function;
}
int game(){
    // I have to print the map and the round counter first;
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