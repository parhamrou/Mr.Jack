//...................palces' struct.....................

typedef struct place{
    int place_type;  // 0. normal    1.on light    2.off light   3.house    4.open manhole    5. close manhole    6.addition place     7.close gate   8.open gate   
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
enum condition {normal, light_on, light_off, house, open, close, addition, close_gate, open_gate};

//..................heads of two linked lists............

card *squad_head = NULL; // this linkedlist is one that we pick four and four cards from
card *even_round_head = NULL;
card *odd_round_head = NULL;
card* second_head = NULL; // This linked list is for Mr.Jack random choose and for Sherlock picks;

//.................global variables.....................

int round_counter = 1; // goes until it reaches to 8;
int turn_counter = 1; // counts turns at each round;
bool visible_condition = true;
int MrJack;
int game_over = 0;
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
void even_card_printer(){ // This function prints the abilities of each character each round;
    card* temp = even_round_head;
    int i = 1;
    while(temp != NULL){
        character_info_printer(temp -> name);
        temp = temp -> next;
        printf("*****\n");
        i++;
    }
}
visible(){
    // This function shows that Mr.Jack is visible or not to find out that can Mr.Jack escape or not;
}
odd_round(){
    // This function is four odd rounds and calls other functions. first is inspector's turn , then two times Mr.Jack and then again inspector;
}
int even_round(){ // This function is for even rounds and calls other functions. first is Mr.Jack's turn, then two times inspector and the again Mr.Jack;
    // showing map every time;
    int choose;
    randomCard_maker();       
    if(round_counter == 1){    // هنوز چاه‌ها رو در نظر نگرفتی!
    randomCard_maker_2();      // یه فکری به حال نوبت شمار بکن!
    Mr_jack_CardPicker();      // هنوز دستگیر کردن و اینا خرابه توی تابع حرکت. بستگی به این هم داره که راند زوجیم یا فرد! درستش کن
    printf("Inspecteur! Don't look :))\n Mr.Jack's card is ");
    MrJack_card_show(MrJack);
    }
    round_printer();
    even_card_printer();
    printf("inspecteur! what card do you choose?!\n"); // this must be repeated four times;
    scanf("%d", &choose);
    card_delete(choose, 3, even_round_head); // we delete that card for the next round;
    search_character(choose); // now one character (one person) did his actions;
    if(game_over == 1) 
        return 1; // that means game is over;
    round_printer();
    even_card_printer();
    printf("Mr.Jack! What card do you choose?!\n");
    scanf("%d", &choose);
    card_delete(choose, 2, even_round_head);
    search_character(choose);
    if(game_over == 1)
        return 1;
    round_printer();
    even_card_printer();
    printf("Mr.Jack! What card do you choose?!\n");
    scanf("%d", &choose);
    card_delete(choose, 1, even_round_head);
    search_character(choose);
    if(game_over == 1)
        return 1;
    round_printer();
    even_card_printer();
    printf("inspecteur! what card do you choose?!\n"); // this must be repeated four times;
    scanf("%d", &choose);
    card_delete(choose, 0, even_round_head); // we delete that card for the next round;
    search_character(choose);
    return 0; // two users did all they moves;
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
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t1.play with a friend\n\t\t\t\t\t\t\t\t\t\t\t0.exit\n");
    printf("Enter your choice :) :\n");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            solo_game();
            break;
    }
}
int solo_game(){// solo game happens here ;)
    prepare_game();
    even_round();

}
void character_info_printer(int card){ // This function prints characters' abilities;
    switch(card){
        case 0:
        printf("0.SG:\n");
        printf("1 To 3 moves And Ability Use (whistle)\n");
        printf("He can make other characters 3 moves closer to himself\n");
        break;

        case 1:
        printf("1.IL:\n");
        printf("1 To 3 Moves And Ability Use\n");
        printf("He can free one of the exits and block another one\n");
        break;

        case 2:
        printf("2.WG:\n");
        printf("1 To 3 Moves Or Ability Use\n");
        printf("Instead of moving, He can changes his place with another character\n");
        break;

        case 3:
        printf("3.SH:\n");
        printf("1 to 3 Moves then ability use\n");
        printf("He can draw the the top card from the alibi pile and note the character\n");
        break;

        case 4:
        printf("4.JB:\n");
        printf("1 To 3 Moves And Ability Use\n");
        printf("He can open a manhole and closes another\n");
        break;

        case 5:
        printf("5.JH:\n");
        printf("1 To 3 Moves Then Ability Use\n");
        printf("Watson carries a lantern, pictured on his character token. This lantern illuminates all the characters standing straight ahead of him!\n");
        break;

        case 6:
        printf("6.MS:\n");
        printf("1 To 4 Moves With Optional Ability Use\n");
        printf("She can cross any hex but she must stop her movement on a street hex\n");
        break;

        case 7:
        printf("7.JS:\n");
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
    FILE *fp = fopen("characters.txt", "r");
    if(fp == NULL){
        printf("Can't open the file!\n");
        return -1;
    }
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 9; j++){
            fscanf(fp, "%d", &map[i][j].character);
        }
    }
    fclose(fp);
    return 0;
}
void even_round_linkedlist_creat(card* temp){ // first four cards linked list creator for even rounds;
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
void card_picker(int card_number, int i){ // picks four and four cards for two rounds and insert them to two other linked lists;
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
void card_delete(int choose, int j, card* head){
    card* temp = head;
    int i = 0;
    while(temp -> name != choose){
        temp = temp -> next;
        i++;
    }
    if(i == 0){
        card* tmp = head -> next;
        head = tmp;
        free(temp);
    }
    else if(i == j){
        card* tmp = head;
        while(tmp -> next != temp)
            tmp = tmp -> next;
        tmp -> next = NULL;
        free(temp);
    }
    else{
        card* tmp = head;
        while(tmp -> next != temp)
            tmp = tmp -> next;
        tmp -> next = temp -> next;
        free(temp);
    }
}
void possible_moves(int x, int y){ // this function shows the possible moves;
// براساس کاراکتر و خونه‌های دورش باید حرکت‌ها رو بگه
    switch(map[x][y].character){
        case SG:
        SG_func(x, y);
        break;
        case IL:
        IL_func(x, y);
        break;
        case WG:
        WG_func(x, y);
        break;
        case SH:
        SH_func(x ,y);
        break;
        case JB:
        JB_func(x, y);
        break;
        case JW:
        JW_func(x, y);
        break;
        case MS:
        MS_func(x, y);
        break;
        case JS:
        JS_func(x, y);
        break;
    }
    }
void search_character(int number){ // this functions catches the number character and finds it from array;
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 9; j++){
            if(map[i][j].character == number){
                possible_moves(i, j);
                break;
            }
        }
    }
}
void randomCard_maker_2(){ // This function creats the second catagory of cards which we pick Mr.Jack and sherlock choices from;
    card *next_node, *temp;
    for(int i = 0; i < 8; i++){
        next_node = (card *) malloc(sizeof(card));
        next_node -> name = i;
        next_node -> next = NULL;
        if(second_head == NULL){
            second_head = temp = next_node;
        }
        else{
            temp -> next = next_node;
            temp = next_node;
        }
    }
}
void Mr_jack_CardPicker(){ // This function chooses MrJack card at the begining of the game randomly;
    srand(time(NULL));
    MrJack = rand() % 8;
    for(int i = 7; i > -1; i--){
        if(i == MrJack){
            card_delete(MrJack, 7, second_head);
            break;
        }
    }
}
void MrJack_card_show(int number){  
    switch(number){
        case 0:
            printf("SERGENT GOODLEY\n");
            break;
        case 1:
            printf("INSPECTEUR LESTRADE\n");
            break;
        case 2:
            printf("SIR WILLIAM GULL\n");
            break;
        case 3:
            printf("SHERLOCK HOLMES\n");
            break;
        case 4:
            printf("JEREMY BERT\n");
            break;
        case 5:
            printf("JOHN H. WATSON\n");
            break;
        case 6:
            printf("MISS STEALTHY\n");
            break;
        case 7:
            printf("JOHN SMITH\n");
            break;
    }
}
void SG_func(int x, int y){
    
}
void IL_func(int x, int y){

}
void WG_func(int x, int y){

}
void SH_func(int x, int y){

}
void JB_func(int x, int y){
    int choice, temp, action_time;
    printf("You want to do your action 1.before moving or 2.after?\n");
    scanf("%d", &action_time);
    int x_, y_, x__, y__;
    if(action_time == 2){
    printf("How many hexes do you want to move?!\n");
    scanf("%d", &choice);
    for(int i = 0; i < choice; i++){
        if(!(x % 2)){
        temp = odd_x_moves(&x, &y); // a bug is here. now Mr Jack can arrest either :)))
        if(temp == 1 || temp == -1 || temp == 2){ // inspuecteur arrested somebody or MrJack ran away
            game_over = 1;
            return;
        }
        continue;
        }
        else{
        temp = even_x_moves(&x, &y);
        if(temp == 1 || temp == -1 || temp == 2){
            game_over = 1;
            return;
        }
        continue;
        }
    }
    printf("which manhole do you want to open?\n");
    show_close_manholes();
    printf("Enter mokhtasat: ");
    scanf("%d %d", &x_, &y_);
    printf("Which manhole do you want to close?\n");
    show_open_manholes();
    printf("Enter nokhtasat: ");
    scanf("%d %d", &x__, &y__);
    swap_manholes(x_, y_, x__, y__);
    return;
    }
    else{
    printf("which manhole do you want to open?\n");
    show_close_manholes();
    printf("Enter mokhtasat: ");
    scanf("%d %d", &x_, &y_);
    printf("Which manhole do you want to close?\n");
    show_open_manholes();
    printf("Enter nokhtasat: ");
    scanf("%d %d", &x__, &y__);
    swap_manholes(x_, y_, x__, y__);
    printf("How many hexes do you want to move?!\n");
    scanf("%d", &choice);
    for(int i = 0; i < choice; i++){
        if(!(x % 2)){
        temp = odd_x_moves(&x, &y); 
        if(temp == 1 || temp == -1 || temp == 2){
            game_over = 1;
            return;
        }
        }
        else{
        temp = even_x_moves(&x, &y);
        if(temp == 1 || temp == -1 || temp == 2){
            game_over = 1;
            return;
        }
        }
    }
    return;
    }
}
void JW_func(int x, int y){

}
void MS_func(int x, int y){

}
void JS_func(int x, int y){

}
void make_move(int x, int y, int x_, int y_){
    int temp = map[x][y].character;
    map[x][y].character = map[x_][y_].character;
    map[x_][y_].character = temp;
}
int even_x_moves(int *x_, int *y_){ // prints move options;
    int x = *x_, y = *y_;
    switch(map[x][y+1].place_type){ // in this part we just consider place types not neighbor character;
        case normal:
        case open:
        case close:
        if(map[x][y+1].character == 10)
            printf("1. North  ");
        else{
            if(turn_counter == 1 || turn_counter == 4) // if it's inspecteur turn
                printf("11. go north and arrest him/her   ");
        }
        case open_gate:
        if(!visible_condition && (turn_counter == 2 || turn_counter == 3)){
            printf("20. run away!  ");
        }
        break;
    }
    switch(map[x][y-1].place_type){
        case normal:
        case open:
        case close:
        if(map[x][y-1].character == 10)
            printf("2. South  ");
        else{
            if(turn_counter == 1 || turn_counter == 4)
                printf("12. go south and arrest him/her   ");
        }
        case open_gate:
        if(!visible_condition && (turn_counter == 2 || turn_counter == 3)){
            printf("20. run away!  ");
        }
        break;
    }
    switch(map[x+1][y+1].place_type){
        case normal:
        case open:
        case close:
        if(map[x+1][y+1].character == 10)
            printf("3.North-East  ");
        else{
            if(turn_counter == 1 || turn_counter == 4)
                printf("13. go north-east and arrest him/her   ");
        }
        break;
    }
    switch(map[x+1][y].place_type){
        case normal:
        case open:
        case close:
        if(map[x+1][y].character == 10)
            printf("4.South-East  ");
        else{
            if(turn_counter == 1 || turn_counter == 4)
                printf("14. go south-east and arrest him/her   ");
        }
        break;
    }
    switch(map[x-1][y].place_type){
        case normal:
        case open:
        case close:
        if(map[x-1][y].character == 10)
            printf("5.South-West  ");
        else{
            if(turn_counter == 1 || turn_counter == 4)
                printf("15. go south-west and arrest him/her   ");
        }
        break;
    }
    switch(map[x-1][y+1].place_type){
        case normal:
        case open:
        case close:
        if(map[x-1][y+1].character == 10)
            printf("6.North-West  ");
        else{
            if(turn_counter == 1 || turn_counter == 4)
                printf("16. go north-west and arrest him/her   ");
        }
        break;
    }
    int temp;
    scanf("%d", &temp);
    if(temp < 10){ // User doesn't want to arrest anybody
        if(temp == 1){
            make_move(x, y, x, y + 1);
            *y_ += 1;
        }
        else if(temp == 2){
            make_move(x, y, x, y - 1);
            *y_ -= 1;
        }
        else if(temp == 3){
            make_move(x, y, x + 1, y + 1);
            *x_ += 1;
            *y_ += 1;
        }
        else if(temp == 4){
            make_move(x, y, x + 1, y);
            *x_ += 1;
        }
        else if(temp == 5){
            make_move(x, y, x - 1, y);
            *x_ -= 1;
        }
        else{
            make_move(x, y, x - 1, y + 1);
            *x_ -= 1;
            *y_ += 1;
        }
        return 0; // user didn't arrest anybody;
    }
    else{
        if(temp == 11){
            if(map[x][y+1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 12){
            if(map[x][y-1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 13){
            if(map[x+1][y+1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 14){
            if(map[x+1][y].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }}
        else if(temp == 15){
            if(map[x-1][y].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 16){
            if(map[x-1][y+1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 20){
            printf("You ran away from city! You won!\n");
            return 2;
        }
    }
}
int odd_x_moves(int *x_, int *y_){ // prints move options;
    int x = *x_, y = *y_;
    switch(map[x][y+1].place_type){ // in this part we just consider place types not neighbor character;
        case normal:
        case open:
        case close:
        if(map[x][y+1].character == 10)
            printf("1. North  ");
        else{
            if(turn_counter == 2 || turn_counter == 3)
            printf("11. go north and arrest him/her  ");
        }
        break;
    }
    switch(map[x][y-1].place_type){
        case normal:
        case open:
        case close:
        if(map[x][y-1].character == 10)
            printf("2. South  ");
        else{
            if(turn_counter == 2 || turn_counter == 3)
                printf("12. go south and arrest him/her   ");
        }
        break;
    }
    switch(map[x+1][y].place_type){
        case normal:
        case open:
        case close:
        if(map[x+1][y].character == 10)
            printf("3.North-East  ");
        else{
            if(turn_counter == 2 || turn_counter == 3)
                printf("13. go north-east and arrest him/her   ");
        }
        break;
    }
    switch(map[x+1][y-1].place_type){
        case normal:
        case open:
        case close:
        if(map[x+1][y-1].character == 10)
            printf("4.South-East  ");
        else{
            if(turn_counter == 2 || turn_counter == 3)
                printf("14. go south-easat and arrest him/her   ");
        }
        break;
    }
    switch(map[x-1][y-1].place_type){
        case normal:
        case open:
        case close:
        if(map[x-1][y-1].character == 10)
            printf("5.South-West  ");
        else{
            if(turn_counter == 2 || turn_counter == 3)
                printf("15. go south-west and arrest him/her  ");
        }
        break;
    }
    switch(map[x-1][y].place_type){
        case normal:
        case open:
        case close:
        if(map[x-1][y].character == 10)
            printf("6.North-West  ");
        else{
            if(turn_counter == 2 || turn_counter == 3)
                printf("16. go north-west and arrest him/her  ");
        }
        break;
    }
    int temp;
    scanf("%d", &temp);
    if(temp < 10){ // User doesn't want to arrest anybody
        if(temp == 1){
            make_move(x, y, x, y + 1);
            *y_ += 1;
        }
        else if(temp == 2){
            make_move(x, y, x, y - 1);
            *y_ -= 1;
        }
        else if(temp == 3){
            make_move(x, y, x + 1, y);
            *x_ += 1;
        }
        else if(temp == 4){
            make_move(x, y, x + 1, y - 1);
            *x_ += 1;
            *y_ -= 1;
        }
        else if(temp == 5){
            make_move(x, y, x - 1, y - 1);
            *x_ -= 1;
            *y_ -= 1;
        }
        else{
            make_move(x, y, x - 1, y);
            *x_ -= 1;
        }
        return 0; // he did a mvoe not arrest somebody;
    }
    else{
        if(temp == 11){
            if(map[x][y+1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 12){
            if(map[x][y-1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 13){
            if(map[x+1][y].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 14){
            if(map[x+1][y-1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }}
        else if(temp == 15){
            if(map[x-1][y-1].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if(temp == 16){
            if(map[x-1][y].character == MrJack){
                printf("You arrested Mr Jack! You won!\n");
                return 1; 
            }
            else{
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
    }
}
void show_close_manholes(){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 9; j++){
            if(map[i][j].place_type == close)
                printf("manhole[%d][%d]\n", i, j);
        }
    }
}
void show_open_manholes(){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 9; j++){
            if(map[i][j].place_type == open)
                printf("manhole[%d][%d]\n", i, j);
        }
    }
}
void swap_manholes(int x_, int y_, int x__, int y__){
    map[x_][y_].place_type = open;
    map[x__][y__].place_type = close;
}