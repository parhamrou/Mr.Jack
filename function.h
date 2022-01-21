//...................palces' struct.....................

typedef struct place
{
    int place_type; // 0. normal    1.on light    2.off light   3.house    4.open manhole    5. close manhole    6.addition place     7.close gate   8.open gate
    int character;  // // 0:SERGENT GOODLEY     1:INSPECTEUR LESTRADE     2:SIR WILLIAM GULL       3:SHERLOCK HOLMES
                    // 4:JEREMY BERT         5:JOHN H. WATSON           6:MISS STEALTHY            7:JOHN SMITH
} place;
//...................characters' node....................

typedef struct card
{
    int name; // number that is assigned to chaaracter;
    struct card *next;
} card;

//..................Enumerations........................

enum persons {SG, IL, WG, SH, JB, JW, MS, JS};
enum condition {normal, light_on, light_off, house, open, close, addition, close_gate, open_gate};
enum persons2 {SG2 = 20, IL2, WG2, SH2, JB2, JW2, MS2, JS2};
//..................heads of two linked lists............

card *squad_head = NULL; // this linkedlist is one that we pick four and four cards from
card *even_round_head = NULL;
card *odd_round_head = NULL;
card *second_head = NULL; // This linked list is for Mr.Jack random choose and for Sherlock picks;

//.................global variables.....................

int round_counter = 1; // goes until it reaches to 8;
int turn_counter = 1;  // counts turns at each round;
int visible_condition = 1;
int MrJack;
int game_over = 0;
int JW_x = 0, JW_y = 4;
int lantern_dir; // 0. North  1. North-East  2. South-East  3. South  4. South-West  5. North_west
//..........two-dimensional array for places............

place map[13][9];

//.................functions.............................

void prepare_game()
{ // This function should be called at the first of the game;
    map_loader();
    first_place_set();
}
void randomCard_maker()
{ // this function generates random cards;
    srand(time(NULL));
    for (int i = 8; i > -1; i--)
    {
        int random_number = rand() % i;
        card_picker(random_number, i);
        if (i == 5)
        {
            break;
        }
    }
    odd_round_head = squad_head; // set second linkedlist to four baghi cards;
}
void even_card_printer()
{ // This function prints the abilities of each character each round;
    card *temp = even_round_head;
    while (temp != NULL)
    {
        character_info_printer(temp->name);
        temp = temp->next;
        printf("\t\t\t* * * * *\n");
    }
}
void odd_card_printer()
{ // This function prints the abilities of each character each round;
    card *temp = odd_round_head;
    while (temp != NULL)
    {
        character_info_printer(temp->name);
        temp = temp->next;
        printf("\t\t\t* * * * *\n");
    }
}
odd_round()
{ // This function is four odd rounds and calls other functions. first is inspector's turn , then two times Mr.Jack and then again inspector;
    int choose;
    round_printer();
    map_printer();
    odd_card_printer();
    printf("\t\t\tMr Jack! what card do you choose?!\n\t\t\t"); // this must be repeated four times;
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 3, &odd_round_head); // we delete that card for the next round;
    search_character(choose);                 // now one character (one person) did his actions;
    if (game_over == 1)
    {
        turn_counter = 1;
        return 1; // that meabs game is over; END OF TURN 1;
    }
    turn_counter = 2;
    round_printer();
    map_printer();
    odd_card_printer();
    printf("\t\t\tInspecteur! What card do you choose?!\n\t\t\t");
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 2, &odd_round_head);
    search_character(choose);
    if (game_over == 1)
    {
        turn_counter = 1;
        return 1;
    }
    turn_counter = 3;
    round_printer();
    map_printer();
    odd_card_printer();
    printf("\t\t\tInspecteur! What card do you choose?!\n\t\t\t");
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 1, &odd_round_head);
    search_character(choose);
    if (game_over == 1)
    {
        turn_counter = 1;
        return 1;
    }
    turn_counter = 4;
    round_printer();
    map_printer();
    odd_card_printer();
    printf("\t\t\tMrJack! what card do you choose?!\n\t\t\t"); // this must be repeated four times;
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 0, &odd_round_head); // we delete that card for the next round;
    search_character(choose);
    turn_counter = 1;
    return 0;
}
int even_round()
{ // This function is for even rounds and calls other functions. first is Mr.Jack's turn, then two times inspector and the again Mr.Jack;
    // showing map every time;
    int choose;
    initial_linkedlist();
    randomCard_maker();
    if (round_counter == 1)
    {
        randomCard_maker_2();
        Mr_jack_CardPicker();
        system("cls");
        printf("\t\t\t\t\t\t\t\t\t\t\tPress Enter to show Mr.Jack's card...\n");
        getchar();
        getchar();
        printf("\t\t\t\t\t\t\t\t\t\t\tMr.Jack's card is ");
        MrJack_card_show(MrJack);
        printf("\t\t\t\t\t\t\t\t\t\t\tPress enter to continue...\n\t\t\t\t\t\t\t\t\t\t\t");
        getchar();
        MrJack_card_show(MrJack);
    }
    round_printer();
    map_printer();
    even_card_printer();
    printf("\t\t\tinspecteur! what card do you choose?!\n\t\t\t"); // this must be repeated four times;
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 3, &even_round_head); // we delete that card for the next round;
    search_character(choose);                 // now one character (one person) did his actions;
    if (game_over == 1)
    {
        turn_counter = 1;
        return 1; // that meabs game is over; END OF TURN 1;
    }
    turn_counter = 2;
    round_printer();
    map_printer();
    even_card_printer();
    printf("\t\t\tMr.Jack! What card do you choose?!\n\t\t\t");
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 2, &even_round_head);
    search_character(choose);
    if (game_over == 1)
    {
        turn_counter = 1;
        return 1;
    }
    turn_counter = 3;
    round_printer();
    map_printer();
    even_card_printer();
    printf("\t\t\tMr.Jack! What card do you choose?!\n\t\t\t");
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 1, &even_round_head);
    search_character(choose);
    if (game_over == 1)
    {
        turn_counter = 1;
        return 1;
    }
    turn_counter = 4;
    round_printer();
    map_printer();
    even_card_printer();
    printf("\t\t\tinspecteur! what card do you choose?!\n\t\t\t"); // this must be repeated four times;
    scanf("%d", &choose);
    map_printer();
    card_delete(choose, 0, &even_round_head); // we delete that card for the next round;
    search_character(choose);
    turn_counter = 1;
    return 0; // two users did all they moves;
}
map_printer()
{
    int x = 1;
    system("cls");
    printf("\033[1;32m");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    round_printer();
    printf("\t\t\t\t");
    for(int i = 0; i < 13; i++)
    {
        if(i < 10)
        {
            printf("\033[1;32m");
            printf("      %d", i);
            printf("\033[0m");
        }
        else
        { 
            printf("\033[1;32m");
            printf("     %d", i);
            printf("\033[0m");
        }
    }
    printf("\t\t\t");
    printf("\n\t\t\t\t  ");
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf("         _____");
    printf("\033[0m");
    }
    printf("\n\t\t\t\t         ");
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf(" /     \\      ");
    printf("\033[0m");
    }
    printf("\n\t\t\t\t    ");
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf("_____/  ");
    printf("\033[0m");
    map_printer_char(x, 8);
    printf("\033[1;32m");
    printf("  \\");
    printf("\033[0m");
    x += 2;
    }
    printf("\033[1;32m");
    printf("_____\n\t\t\t\t  ");
    printf("\033[0m");
    x = 1;
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf(" /     \\  ");
    printf("\033[0m");
    map_printer_place(x, 8);
    printf(" ");
    x += 2;
    }
    printf("\033[1;32m");
    printf(" /     \\\n\t\t\t\t  ");
    printf("\033[0m");
    x = 0;
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf("/  ");
    printf("\033[0m");
    map_printer_char(x, 8);
    printf("\033[1;32m");
    printf("  \\_____");
    printf("\033[0m");
    x += 2;
    }
    for(int j = 8; j > -1; j--){
    if(j == 8){
        printf("\033[1;32m");
    printf("/  ");
    printf("\033[0m");
    map_printer_char(12, 8);
    printf("\033[1;32m");
    printf("  \\\n\t\t\t\t8 ");
    printf("\\  ");
    printf("\033[0m");
    map_printer_place(0, 8);
    printf(" ");
    }
    else{
        printf("\033[1;32m");
        printf("\n\t\t\t\t%d \\  ", j);
        printf("\033[0m");
        map_printer_place(0, j);   
        printf(" ");
    }
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf(" /     \\  ");
    printf("\033[0m");
    map_printer_place((i + 1) * 2, j);
    printf(" "); 
    }
    printf("\033[1;32m");
    printf(" /\n\t\t\t\t   \\");
    printf("\033[0m");
    x = 1;
    for(int i = 0; i < 6; i++){
    if(j != 0)
    {
        printf("\033[1;32m");
        printf("_____/  ");
        printf("\033[0m");
        map_printer_char(x, j - 1);
        printf("\033[1;32m");
        printf("  \\");
        printf("\033[0m");
        x += 2;
    }
    else
    { 
        printf("\033[1;32m");
        printf("_____/       \\");
        printf("\033[0m");
    }
    }
    printf("\033[1;32m");
    printf("_____/\n\t\t\t\t  ");
    printf("\033[0m");
    if(j != 0){
    x = 1;
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf(" /     \\  ");
    printf("\033[0m");
    map_printer_place(x, j - 1);
    printf(" ");
    x += 2;
    }
    printf("\033[1;32m");
    printf(" /     \\\n\t\t\t\t  ");
    printf("\033[0m");
    x = 0;
    for(int i = 0; i < 6; i++){
        printf("\033[1;32m");
    printf("/  ");
    printf("\033[0m");
    map_printer_char(x, j - 1);
    printf("\033[1;32m");
    printf("  \\_____");
    printf("\033[0m");
    x += 2;
    }
    printf("\033[1;32m");
    printf("/  ");
    printf("\033[0m");
    map_printer_char(12, j - 1);
    printf("\033[1;32m");
    printf("  \\");
    printf("\033[0m");
    }
    }
    printf("\033[0m");
    printf("\n");
}
void map_printer_place(int x, int y)
{
    switch(map[x][y].place_type)
    {
        case normal:
            printf("   ");
            return;
        case light_on:
            printf("\033[0;33m");
            printf("O_O");
            printf("\033[0m");
            return;
        case light_off:
            printf("\033[0;37m");
            printf("-_-");
            printf("\033[0m");
            return;
        case house:
            printf("\033[0;31m");
            printf(" H ");
            printf("\033[0m");
            return;
        case open:
            printf("\033[0;37m");
            printf("<O>");
            printf("\033[0m");
            return;
        case close:
            printf("\033[0;37m");
            printf(">-<");
            printf("\033[0m");
            return;
        case addition:
            printf("\033[0;37m");
            printf("XXX");
            printf("\033[0m");
            return;
        case close_gate:
            printf("\033[0;31m");
            printf("###");
            printf("\033[0m");
            return;
        case open_gate:
            printf("\033[0;32m");
            printf("| |");
            printf("\033[0m");
            return;
    }
}
void map_printer_char(int x, int y)
{
    switch(map[x][y].character)
    {
        case SG:
            printf("\033[1;34m");
            printf("SG ");
            printf("\033[0m");
            return;
        case SG2:
            printf("\033[1;34m");
            printf("SG*");
            printf("\033[0m");
            return;
        case IL:
            printf("\033[1;34m");
            printf("IL ");
            printf("\033[0m");
            return;
        case IL2:
            printf("\033[1;34m");
            printf("IL*");
            printf("\033[0m");
            return;
        case WG:
            printf("\033[1;34m");
            printf("WG ");
            printf("\033[0m");
            return;
        case WG2:
            printf("\033[1;34m");
            printf("WG*");
            printf("\033[0m");
            return;
        case SH:
            printf("\033[1;34m");
            printf("SH ");
            printf("\033[0m");
            return;
        case SH2:
            printf("\033[1;34m");
            printf("SH*");
            printf("\033[0m");
            return;
        case JB:
            printf("\033[1;34m");
            printf("JB ");
            printf("\033[0m");
            return;
        case JB2:
            printf("\033[1;34m");
            printf("JB*");
            printf("\033[0m");
            return;
        case JW:
            printf("\033[1;34m");
            printf("JW ");
            printf("\033[0m");
            return;
        case JW2:
            printf("\033[1;34m");
            printf("JW*");
            printf("\033[0m");
            return;
        case MS:
            printf("\033[1;34m");
            printf("MS ");
            printf("\033[0m");
            return;
        case MS2:
            printf("\033[1;34m");
            printf("MS*");
            printf("\033[0m");
            return;
        case JS:
            printf("\033[1;34m");
            printf("JS ");
            printf("\033[0m");
            return;
        case JS2:
            printf("\033[1;34m");
            printf("JS*");
            printf("\033[0m");
            return;
        case 10:
            printf("\033[1;34m");
            printf("   ");
            printf("\033[0m");
            return;
    }
    switch(map[x][y].place_type)
    {
        case addition:
            printf("\033[0;37m");
            printf("XXX");
            printf("\033[0m");
            return;
    }
}
int map_loader()
{
    // This function loads the map at the begining of the game from txt file;
    FILE *fp = fopen("map.txt", "r");
    if (fp == NULL)
    {
        printf("Can't open the file!\n");
        return -1;
    }
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fscanf(fp, "%d", &map[i][j].place_type);
        }
    }
    fclose(fp);
    return 0;
}
void menu()
{
    // This function prints the menu and catches user's choice;
    int choice;
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t1.play with a friend\n\t\t\t\t\t\t\t\t\t\t\t0.exit\n");
    printf("\t\t\t\t\t\t\t\t\t\t\tEnter your choice:\n\t\t\t\t\t\t\t\t\t\t\t");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        multiplay();
        break;
    }
}
int multiplay()
{ // multiplay game happens here ;)
    int result = -1;
    for(int i = 0; i < 4; i++){
        if(i == 0)
        {
            prepare_game();
        }
        result = even_round();
        if(result == 1)
        {
            printf("The game is over!\n");
            return 1;
        }
        round_counter++;
        result = odd_round();
        if(result == 1)
        {
            printf("The game is over!\n");
            return 1; // the game is over;
        }
        if(i != 3)
        {
            visible();
            round_counter++;
            squad_head = NULL;
            even_round_head = NULL;
            odd_round_head = NULL;
            map_printer();
        }
        else
        {
            printf("The rounds are finished!\n");
            printf("The game is over! Mr Jack wins!\n");
            return 1;
        }
    }
}
void character_info_printer(int card)
{ // This function prints characters' abilities;
    switch (card)
    {
    case 0:
        printf("\t\t\t0.SG:\t");
        printf("1 To 3 moves And Ability Use (whistle)\t");
        printf("He can make other characters 3 moves closer to himself\n");
        break;

    case 1:
        printf("\t\t\t1.IL:\t");
        printf("1 To 3 Moves And Ability Use\t");
        printf("He can free one of the exits and block another one\n");
        break;

    case 2:
        printf("\t\t\t2.WG:\t");
        printf("1 To 3 Moves Or Ability Use\t");
        printf("Instead of moving, He can changes his place with another character\n");
        break;

    case 3:
        printf("\t\t\t3.SH:\t");
        printf("1 to 3 Moves then ability use\t");
        printf("He can draw the the top card from the alibi pile and note the character\n");
        break;

    case 4:
        printf("\t\t\t4.JB:\t");
        printf("1 To 3 Moves And Ability Use\t");
        printf("He can open a manhole and closes another\n");
        break;

    case 5:
        printf("\t\t\t5.JW:\t");
        printf("1 To 3 Moves Then Ability Use\t");
        printf("Watson carries a lantern, pictured on his character token. This lantern illuminates all the characters standing straight ahead of him!\n");
        break;

    case 6:
        printf("\t\t\t6.MS:\t");
        printf("1 To 4 Moves With Optional Ability Use\t");
        printf("She can cross any hex but she must stop her movement on a street hex\n");
        break;

    case 7:
        printf("\t\t\t7.JS:\t");
        printf("1 To 3 Moves And Ability Use\t");
        printf("He turns off a light and turn on another light\n");
        break;
    }
}
void round_printer()
{ //This function prints round and can Mr.Jack escape or not;
    printf("round %d\n", round_counter);
    if (visible_condition)
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tMr.Jack is visible and can't escape this round!\n");
    else
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tMr.jack is not visible and can escape this round!\n");
}
void first_place_set()
{
    FILE *fp = fopen("characters.txt", "r");
    if (fp == NULL)
    {
        printf("Can't open the file!\n");
        return -1;
    }
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fscanf(fp, "%d", &map[i][j].character);
        }
    }
    fclose(fp);
    return 0;
}
void even_round_linkedlist_creat(card *temp)
{ // first four cards linked list creator for even rounds;
    temp->next = NULL;
    if (even_round_head == NULL)
    {
        even_round_head = temp;
    }
    else
    {
        card *next_node = even_round_head;
        while (next_node->next != NULL)
            next_node = next_node->next;
        next_node->next = temp;
    }
}
initial_linkedlist()
{ // contains linked list with eight
    card *temp, *next_node;
    int i = 0;
    while (i != 8)
    {
        next_node = (card *)malloc(sizeof(card));
        next_node->name = i;
        next_node->next = NULL;
        if (squad_head == NULL)
        {
            squad_head = temp = next_node;
        }
        else
        {
            temp->next = next_node;
            temp = next_node;
        }
        i++;
    }
}
void card_picker(int card_number, int i)
{ // picks four and four cards for two rounds and insert them to two other linked lists;
    if (card_number == 0)
    { // deleting first node;
        card *temp = squad_head;
        card *tmp = squad_head->next;
        squad_head = tmp;
        even_round_linkedlist_creat(temp);
    }
    else if (card_number == i - 1)
    { // deleting last node;
        card *temp = squad_head;
        card *tmp = squad_head;
        while (temp->next != NULL)
            temp = temp->next;
        while (tmp->next != temp)
            tmp = tmp->next;
        tmp->next = NULL;
        even_round_linkedlist_creat(temp);
    }
    else
    {
        card *temp = squad_head;
        card *tmp = squad_head;
        for (int j = 0; j < card_number; j++)
        {
            temp = temp->next;
        }
        while (tmp->next != temp)
            tmp = tmp->next;
        tmp->next = temp->next;
        even_round_linkedlist_creat(temp);
    }
}
void card_delete(int choose, int j, card **head)
{
    card *temp = *head;
    int i = 0;
    while (temp->name != choose)
    {
        temp = temp->next;
        i++;
    }
    if (i == 0)
    {
        card *tmp = temp->next;
        *head = tmp;
        free(temp);
    }
    else if (i == j)
    {
        card *tmp = *head;
        while (tmp->next != temp)
            tmp = tmp->next;
        tmp->next = NULL;
        free(temp);
    }
    else
    {
        card *tmp = *head;
        while (tmp->next != temp)
            tmp = tmp->next;
        tmp->next = temp->next;
        free(temp);
    }
}
void possible_moves(int x, int y)
{ // this function shows the possible moves;
    // براساس کاراکتر و خونه‌های دورش باید حرکت‌ها رو بگه
    switch (map[x][y].character)
    {
    case SG:
    case SG2:
        SG_func(x, y);
        return;
    case IL:
    case IL2:
        IL_func(x, y);
        return;
    case WG:
    case WG2:
        WG_func(x, y);
        return;
    case SH:
    case SH2:
        SH_func(x, y);
        return;
    case JB:
    case JB2:
        JB_func(x, y);
        return;
    case JW:
    case JW2:
        JW_func(x, y);
        return;
    case MS:
    case MS2:
        MS_func(x, y);
        return;
    case JS:
    case JS2:
        JS_func(x, y);
        return;
    }
}
void search_character(int number)
{ // this functions catches the number character and finds it from array;
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].character == number || map[i][j].character == number + 20)
            {
                possible_moves(i, j);
                return;
            }
        }
    }
}
void randomCard_maker_2()
{ // This function creats the second catagory of cards which we pick Mr.Jack and sherlock choices from;
    card *next_node, *temp;
    for (int i = 0; i < 8; i++)
    {
        next_node = (card *)malloc(sizeof(card));
        next_node->name = i;
        next_node->next = NULL;
        if (second_head == NULL)
        {
            second_head = temp = next_node;
        }
        else
        {
            temp->next = next_node;
            temp = next_node;
        }
    }
}
void Mr_jack_CardPicker()
{ // This function chooses MrJack card at the begining of the game randomly;
    srand(time(NULL));
    MrJack = rand() % 8;
    for (int i = 7; i > -1; i--)
    {
        if (i == MrJack)
        {
            card_delete(MrJack, 7, &second_head);
            break;
        }
    }
}
void MrJack_card_show(int number)
{
    switch (number)
    {
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
void SG_func(int x, int y)
{ // there is a bug here. if he can't make a character closer?
    int choice, temp, action_time;
    printf("\t\t\tYou want to do your action   1.before moving   or   2.after?\n\t\t\t");
    scanf("%d", &action_time);
    map_printer();
    int x_, y_, x__, y__;
    if (action_time == 2)
    {
        printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
        scanf("%d", &choice);
        map_printer();
        for (int i = 0; i < choice; i++)
        {
            if (!(x % 2))
            {
                temp = odd_x_moves(&x, &y, 0); // a bug is here. now Mr Jack can arrest either :)))
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                { // inspuecteur arrested somebody or MrJack ran away
                    game_over = 1;
                    return;
                }
                continue;
            }
            else
            {
                temp = even_x_moves(&x, &y, 0);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
                continue;
            }
        }
        // action
        for (int i = 0; i < 3; i++)
        {
            int tmp;
            printf("\t\t\tWhich character do you want to make closer?!\n\t\t\t");
            for (int j = 1; j < 8; j++)
            {
                printf("%d. ", j);
                MrJack_card_show(j);
                printf("\t\t\t");
            }
            scanf("%d", &tmp);
            map_printer();
            SG_action1(tmp, x, y);
            map_printer();
        }
        return;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            int tmp;
            printf("\t\t\tWhich character do you want to make closer?!\n\t\t\t");
            for (int j = 1; j < 8; j++)
            {
                printf("%d. ", j);
                MrJack_card_show(j);
                printf("\t\t\t");
            }
            scanf("%d", &tmp);
            map_printer();
            SG_action1(tmp, x, y);
            map_printer();
        }
        printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
        scanf("%d", &choice);
        map_printer();
        for (int i = 0; i < choice; i++)
        {
            if (!(x % 2))
            {
                temp = odd_x_moves(&x, &y, 0);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
            }
            else
            {
                temp = even_x_moves(&x, &y, 0);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
            }
        }
        return;
    }
}
void IL_func(int x, int y)
{
    int choice, temp;
    int x_, y_, x__, y__;
    printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
    scanf("%d", &choice);
    map_printer();
    for (int i = 0; i < choice; i++)
    {
        if (!(x % 2))
        {
            temp = odd_x_moves(&x, &y, 1);
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            { // inspuecteur arrested somebody or MrJack ran away
                game_over = 1;
                return;
            }
            continue;
        }
        else
        {
            temp = even_x_moves(&x, &y, 1);
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            {
                game_over = 1;
                return;
            }
            continue;
        }
    }
    printf("\t\t\twhich gate do you want to open?\n\t\t\t");
    show_close_gates();
    printf("Enter mokhtasat: ");
    scanf("%d %d", &x_, &y_);
    map_printer();
    printf("\t\t\tWhich gate do you want to close?\n\t\t\t");
    show_open_gates();
    printf("Enter nokhtasat: ");
    scanf("%d %d", &x__, &y__);
    swap_gates(x_, y_, x__, y__);
    return;
}
void WG_func(int x, int y)
{
    int choice, temp, action_time;
    printf("\t\t\tYou want to   1. do your action   or    2. move?!\t\t\t");
    scanf("%d", &action_time);
    map_printer();
    if (action_time == 2)
    {
        printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
        scanf("%d", &choice);
        map_printer();
        for (int i = 0; i < choice; i++)
        {
            if (!(x % 2))
            {
                temp = odd_x_moves(&x, &y, 2); // a bug is here. now Mr Jack can arrest either :)))
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                { // inspuecteur arrested somebody or MrJack ran away
                    game_over = 1;
                    return;
                }
                continue;
            }
            else
            {
                temp = even_x_moves(&x, &y, 2);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
                continue;
            }
        }
        return;
    }
    else
    {
        int tmp;
        printf("\t\t\twhich character do you want to change your hex with?!\n");
        WG_character_choice(2);
        scanf("%d", &tmp);
        WG_character_change(x, y, tmp);
        return;
    }
}
void SH_func(int x, int y)
{
    int choice, temp;
    int x_, y_, x__, y__;
    printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
    scanf("%d", &choice);
    map_printer();
    for (int i = 0; i < choice; i++)
    {
        if (!(x % 2))
        {
            temp = odd_x_moves(&x, &y, 3);
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            { // inspuecteur arrested somebody or MrJack ran away
                game_over = 1;
                return;
            }
            continue;
        }
        else
        {
            temp = even_x_moves(&x, &y, 3);
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            {
                game_over = 1;
                return;
            }
            continue;
        }
    }
    SH_action();
    return;
}
void JB_func(int x, int y)
{
    int choice, temp, action_time;
    printf("\t\t\tYou want to do your action   1.before moving   or    2.after?\n\t\t\t");
    scanf("%d", &action_time);
    map_printer();
    int x_, y_, x__, y__;
    if (action_time == 2)
    {
        printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
        scanf("%d", &choice);
        map_printer();
        for (int i = 0; i < choice; i++)
        {
            if (!(x % 2))
            {
                temp = odd_x_moves(&x, &y, 4); // a bug is here. now Mr Jack can arrest either :)))
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                { // inspuecteur arrested somebody or MrJack ran away
                    game_over = 1;
                    return;
                }
                continue;
            }
            else
            {
                temp = even_x_moves(&x, &y, 4);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
                continue;
            }
        }
        printf("\t\t\twhich manhole do you want to open?\n\t\t\t");
        show_close_manholes();
        printf("Enter mokhtasat: ");
        scanf("%d %d", &x_, &y_);
        map_printer();
        printf("\t\t\tWhich manhole do you want to close?\n\t\t\t");
        show_open_manholes();
        printf("Enter nokhtasat: ");
        scanf("%d %d", &x__, &y__);
        swap_manholes(x_, y_, x__, y__);
        return;
    }
    else
    {
        printf("\t\t\twhich manhole do you want to open?\n\t\t\t");
        show_close_manholes();
        printf("Enter mokhtasat: ");
        scanf("%d %d", &x_, &y_);
        map_printer();
        printf("\t\t\tWhich manhole do you want to close?\n\t\t\t");
        show_open_manholes();
        printf("\t\t\tEnter nokhtasat: ");
        scanf("%d %d", &x__, &y__);
        swap_manholes(x_, y_, x__, y__);
        map_printer();
        printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
        scanf("%d", &choice);
        map_printer();
        for (int i = 0; i < choice; i++)
        {
            if (!(x % 2))
            {
                temp = odd_x_moves(&x, &y, 4);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
            }
            else
            {
                temp = even_x_moves(&x, &y, 4);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
            }
        }
        return;
    }
}
void JW_func(int x, int y)
{
    int choice, temp;
    int x_, y_, x__, y__;
    printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
    scanf("%d", &choice);
    map_printer();
    for (int i = 0; i < choice; i++)
    {
        if (!(x % 2))
        {
            temp = odd_x_moves(&x, &y, 5);
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            { // inspuecteur arrested somebody or MrJack ran away
                game_over = 1;
                return;
            }
            continue;
        }
        else
        {
            temp = even_x_moves(&x, &y, 5);
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            {
                game_over = 1;
                return;
            }
            continue;
        }
    }
    JW_x = x;
    JW_y = y;
    JW_action();
    return;
}
void MS_func(int x, int y)
{
    int choice, temp, passed = 100;
    printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
    scanf("%d", &choice);
    map_printer();
    for (int i = 0; i < choice; i++)
    {
        if (i == choice - 1)
            passed = -1;
        if (!(x % 2))
        {
            temp = odd_x_moves(&x, &y, passed); // a bug is here. now Mr Jack can arrest either :)))
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            { // inspuecteur arrested somebody or MrJack ran away
                game_over = 1;
                return;
            }
            continue;
        }
        else
        {
            temp = even_x_moves(&x, &y, passed);
            map_printer();
            if (temp == 1 || temp == -1 || temp == 2)
            {
                game_over = 1;
                return;
            }
            continue;
        }
    }
}
void JS_func(int x, int y)
{
    int choice, temp, action_time;
    printf("\t\t\tYou want to do your action    1.before moving    or     2.after? ");
    scanf("%d", &action_time);
    map_printer();
    int x_, y_, x__, y__;
    if (action_time == 2)
    {
        printf("\t\t\tHow many hexes do you want to move?! ");
        scanf("%d", &choice);
        map_printer();
        for (int i = 0; i < choice; i++)
        {
            if (!(x % 2))
            {
                temp = odd_x_moves(&x, &y, 7); // a bug is here. now Mr Jack can arrest either :)))
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                { // inspuecteur arrested somebody or MrJack ran away
                    game_over = 1;
                    return;
                }
                continue;
            }
            else
            {
                temp = even_x_moves(&x, &y, 7);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
                continue;
            }
        }
        printf("\t\t\twhich light do you want to turn on?\n\t\t\t");
        show_off_lights();
        printf("Enter mokhtasat: ");
        scanf("%d %d", &x_, &y_);
        map_printer();
        printf("\t\t\tWhich light do you want to turn off?\n\t\t\t");
        show_on_lights();
        printf("Enter nokhtasat: ");
        scanf("%d %d", &x__, &y__);
        swap_lights(x_, y_, x__, y__);
        return;
    }
    else
    {
        printf("\t\t\twhich light do you want to turn on?\n\t\t\t");
        show_off_lights();
        printf("Enter mokhtasat: ");
        scanf("%d %d", &x_, &y_);
        map_printer();
        printf("\t\t\tWhich light do you want to turn off?\n\t\t\t");
        show_on_lights();
        printf("Enter nokhtasat: ");
        scanf("%d %d", &x__, &y__);
        swap_lights(x_, y_, x__, y__);
        map_printer();
        printf("\t\t\tHow many hexes do you want to move?!\n\t\t\t");
        scanf("%d", &choice);
        map_printer();
        for (int i = 0; i < choice; i++)
        {
            if (!(x % 2))
            {
                temp = odd_x_moves(&x, &y, 7);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
            }
            else
            {
                temp = even_x_moves(&x, &y, 7);
                map_printer();
                if (temp == 1 || temp == -1 || temp == 2)
                {
                    game_over = 1;
                    return;
                }
            }
        }
        return;
    }
}
void make_move(int x, int y, int x_, int y_)
{
    int temp = map[x][y].character;
    map[x][y].character = map[x_][y_].character;
    map[x_][y_].character = temp;
}
int even_x_moves(int *x_, int *y_, int passed)
{ // prints move options;
    int x = *x_, y = *y_;
    if (y != 8)
    {
        switch (map[x][y + 1].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x][y + 1].character == 10)
                printf("1. North  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2))) // if it's inspecteur turn
                    printf("11. go north and arrest him/her   ");
            }

        case open_gate:
            if (!visible_condition && (((round_counter % 2) && (turn_counter == 2 || turn_counter == 3)) || (!(round_counter % 2) && (turn_counter == 1 || turn_counter == 4))))
            {
                printf("20. run away!  ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("1. North  ");
        }
    }
    if (y != 0)
    {
        switch (map[x][y - 1].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x][y - 1].character == 10)
                printf("2. South  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("12. go south and arrest him/her   ");
            }
        case open_gate:
            if (!visible_condition && (((round_counter % 2) && (turn_counter == 2 || turn_counter == 3)) || (!(round_counter % 2) && (turn_counter == 1 || turn_counter == 4))))
            {
                printf("20. run away!  ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("2. south   ");
        }
    }
    if (x != 12 && y != 8)
    {
        switch (map[x + 1][y + 1].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x + 1][y + 1].character == 10)
                printf("3.North-East  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("13. go north-east and arrest him/her   ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("3. North-East  ");
        }
    }
    if (x != 12)
    {
        switch (map[x + 1][y].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x + 1][y].character == 10)
                printf("4.South-East  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("14. go south-east and arrest him/her   ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("4. South-East  ");
        }
    }
    if (x != 0)
    {
        switch (map[x - 1][y].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x - 1][y].character == 10)
                printf("5.South-West  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("15. go south-west and arrest him/her   ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("5. South-West  ");
        }
    }
    if (x != 0 && y != 8)
    {
        switch (map[x - 1][y + 1].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x - 1][y + 1].character == 10)
                printf("6.North-West  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("16. go north-west and arrest him/her   ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("6. North-West  ");
        }
    }
    switch (map[x][y].place_type)
    {
    case open:
        printf("7. go from manhole  ");
    }
    int temp;
    scanf("%d", &temp);
    if (temp < 10)
    { // User doesn't want to arrest anybody
        if (temp == 1)
        {
            make_move(x, y, x, y + 1);
            *y_ += 1;
        }
        else if (temp == 2)
        {
            make_move(x, y, x, y - 1);
            *y_ -= 1;
        }
        else if (temp == 3)
        {
            make_move(x, y, x + 1, y + 1);
            *x_ += 1;
            *y_ += 1;
        }
        else if (temp == 4)
        {
            make_move(x, y, x + 1, y);
            *x_ += 1;
        }
        else if (temp == 5)
        {
            make_move(x, y, x - 1, y);
            *x_ -= 1;
        }
        else if (temp == 6)
        {
            make_move(x, y, x - 1, y + 1);
            *x_ -= 1;
            *y_ += 1;
        }
        else
        {
            manhole_move();
            printf("Enter mokhtasat of manhole: ");
            int temp_x, temp_y;
            scanf("%d %d", &temp_x, &temp_y);
            make_move(x, y, temp_x, temp_y);
            *x_ = temp_x;
            *y_ = temp_y;
        }
        return 0; // user didn't arrest anybody;
    }
    else
    {
        if (temp == 11)
        {
            if (map[x][y + 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 12)
        {
            if (map[x][y - 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 13)
        {
            if (map[x + 1][y + 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 14)
        {
            if (map[x + 1][y].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 15)
        {
            if (map[x - 1][y].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 16)
        {
            if (map[x - 1][y + 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 20)
        {
            printf("You ran away from city! You won!\n");
            return 2;
        }
    }
}
int odd_x_moves(int *x_, int *y_, int passed)
{ // prints move options;
    int x = *x_, y = *y_;
    if (y != 8)
    {
        switch (map[x][y + 1].place_type)
        { // in this part we just consider place types not neighbor character;
        case normal:
        case open:
        case close:
            if (map[x][y + 1].character == 10)
                printf("1. North  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("11. go north and arrest him/her  ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("1. North  ");
        }
    }
    if (y != 0)
    {
        switch (map[x][y - 1].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x][y - 1].character == 10)
                printf("2. South  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("12. go south and arrest him/her   ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("2. South  ");
        }
    }
    if (x != 12)
    {
        switch (map[x + 1][y].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x + 1][y].character == 10)
                printf("3.North-East  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("13. go north-east and arrest him/her   ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("3. North-East  ");
        }
    }
    if (x != 12 && y != 0)
    {
        switch (map[x + 1][y - 1].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x + 1][y - 1].character == 10)
                printf("4.South-East  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("14. go south-easat and arrest him/her   ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("4. South-East  ");
        }
    }
    if (x != 0 && y != 0)
    {
        switch (map[x - 1][y - 1].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x - 1][y - 1].character == 10)
                printf("5.South-West  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("15. go south-west and arrest him/her  ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("5.South-West  ");
        }
    }
    if (x != 0)
    {
        switch (map[x - 1][y].place_type)
        {
        case normal:
        case open:
        case close:
            if (map[x - 1][y].character == 10)
                printf("6.North-West  ");
            else
            {
                if (((round_counter % 2) && (turn_counter == 1 || turn_counter == 4)) || (!(round_counter % 2) && (turn_counter == 3 || turn_counter == 2)))
                    printf("16. go north-west and arrest him/her  ");
            }
            break;
        case house:
        case light_off:
        case light_on:
            if (passed == 100)
                printf("6.North-West  ");
        }
    }
    switch (map[x][y].place_type)
    {
    case open:
        printf("7. Go from manholes  ");
    }
    int temp;
    scanf("%d", &temp);
    if (temp < 10)
    { // User doesn't want to arrest anybody
        if (temp == 1)
        {
            make_move(x, y, x, y + 1);
            *y_ += 1;
        }
        else if (temp == 2)
        {
            make_move(x, y, x, y - 1);
            *y_ -= 1;
        }
        else if (temp == 3)
        {
            make_move(x, y, x + 1, y);
            *x_ += 1;
        }
        else if (temp == 4)
        {
            make_move(x, y, x + 1, y - 1);
            *x_ += 1;
            *y_ -= 1;
        }
        else if (temp == 5)
        {
            make_move(x, y, x - 1, y - 1);
            *x_ -= 1;
            *y_ -= 1;
        }
        else if (temp == 6)
        {
            make_move(x, y, x - 1, y);
            *x_ -= 1;
        }
        else
        {
            manhole_move();
            printf("Enter mokhtasat of manhole: ");
            int temp_x, temp_y;
            scanf("%d %d", &temp_x, &temp_y);
            map_printer();
            make_move(x, y, temp_x, temp_y);
            *x_ = temp_x;
            *y_ = temp_y;
        }
        return 0; // he did a mvoe not arrest somebody;
    }
    else
    {
        if (temp == 11)
        {
            if (map[x][y + 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 12)
        {
            if (map[x][y - 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 13)
        {
            if (map[x + 1][y].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 14)
        {
            if (map[x + 1][y - 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 15)
        {
            if (map[x - 1][y - 1].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
        else if (temp == 16)
        {
            if (map[x - 1][y].character == MrJack)
            {
                printf("You arrested Mr Jack! You won!\n");
                return 1;
            }
            else
            {
                printf("You arrested Mr Jack wrongly. You lose!\n");
                return -1;
            }
        }
    }
}
void show_close_manholes()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].place_type == close)
                printf("manhole[%d][%d]\n\t\t\t", i, j);
        }
    }
}
void show_open_manholes()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].place_type == open)
                printf("manhole[%d][%d]\n\t\t\t", i, j);
        }
    }
}
void swap_manholes(int x_, int y_, int x__, int y__)
{
    map[x_][y_].place_type = open;
    map[x__][y__].place_type = close;
}
void manhole_move()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].place_type == open && map[i][j].character == 10)
                printf("manhole[%d][%d]\n\t\t\t", i, j);
        }
    }
}
void show_off_lights()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].place_type == light_off)
                printf("light[%d][%d]\n\t\t\t", i, j);
        }
    }
}
void show_on_lights()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].place_type == light_on)
                printf("light[%d][%d]\n\t\t\t", i, j);
        }
    }
}
void swap_lights(int x_, int y_, int x__, int y__)
{
    map[x_][y_].place_type = light_on;
    map[x__][y__].place_type = light_off;
}
void show_open_gates()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].place_type == open_gate)
                printf("gate[%d][%d]\n\t\t\t", i, j);
        }
    }
}
void show_close_gates()
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].place_type == close_gate)
                printf("gate[%d][%d]\n\t\t\t", i, j);
        }
    }
}
void swap_gates(int x_, int y_, int x__, int y__)
{
    map[x_][y_].place_type = open_gate;
    map[x__][y__].place_type = close_gate;
}
void WG_character_choice(int number)
{
    for (int i = 0; i < 8; i++)
    {
        if (i != number)
        {
            printf("\t\t\t%d.", i);
            MrJack_card_show(i);
        }
    }
}
void WG_character_change(int x, int y, int number)
{
    int x_, y_;
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].character == number || map[i][j].character == number + 20)
            {
                x_ = i;
                y_ = j;
                swap_characters(x, y, x_, y_);
                if(number == JW || number == JW2){
                    JW_x = x;
                    JW_y = y;
                }
                return;
            }
        }
    }
}
void swap_characters(int x, int y, int x_, int y_)
{
    int temp = map[x][y].character;
    map[x][y].character = map[x_][y_].character;
    map[x_][y_].character = temp;
}
void SH_action()
{
    srand(time(NULL));
    int counter = 0, choice;
    card *temp = second_head;
    while (temp != NULL)
    { // calculating number of remain nodes;
        temp = temp->next;
        counter++;
    }
    temp = second_head;
    choice = rand() % counter;
    for (int i = 0; i < choice; i++)
    {
        temp = temp->next;
    }
    int random = temp->name;
    printf("\t\t\tPress enter to show the card\n\t\t\t");
    getchar();
    getchar();
    printf("\t\t\tThe card is: ");
    MrJack_card_show(random);
    printf("\t\t\tPress enter to continue...\n\t\t\t");
    getchar();
    card_delete(random, counter - 1, &second_head);
    return;
}
void SG_action1(int number, int x, int y)
{
    int x_, y_;
    for (int i = 0; i < 13; i++)
    {
        int flag = 0;
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j].character == number || map[i][j].character == number + 20)
            {
                x_ = i;
                y_ = j;
                flag = 1;
            }
        }
        if (flag == 1)
            break;
    }
    if (x_ % 2) // SG   Character
        SG_even(x, y, x_, y_);
    else
        SG_odd(x, y, x_, y_);
}
void SG_even(int x, int y, int x_, int y_)
{
    switch (map[x_][y_ + 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (y_ != 8)
        {
            if (map[x_][y_ + 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_) + abs(y - y_ - 1)))
                printf("1. move to North  ");
        }
    }
    switch (map[x_][y_ - 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (y_ != 0)
        {
            if (map[x_][y_ - 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_) + abs(y - y_ + 1)))
                printf("2. move to South  ");
        }
    }
    switch (map[x_ + 1][y_ + 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (x_ != 12 && y_ != 8)
        {
            if (map[x_ + 1][y_ + 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ - 1) + abs(y - y_ - 1)))
                printf("3. move to North-East  ");
        }
    }
    switch (map[x_ + 1][y_].place_type)
    {
    case normal:
    case open:
    case close:
        if (x_ != 12)
        {
            if (map[x_ + 1][y_].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ - 1) + abs(y - y_)))
                printf("4. move to South-East  ");
        }
    }
    switch (map[x_ - 1][y_].place_type)
    {
    case normal:
    case open:
    case close:
        if (x_ != 0)
        {
            if (map[x_ - 1][y_].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ + 1) + abs(y - y_)))
                printf("5.move to South-West  ");
        }
    }
    switch (map[x_ - 1][y_ + 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (y_ != 8 && x_ != 0)
        {
            if (map[x_ - 1][y_ + 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ + 1) + abs(y - y_ - 1)))
                printf("6. move to North-West  ");
        }
    }
    int temp;
    scanf("%d", &temp);
    if (temp == 1)
    {
        make_move(x_, y_, x_, y_ + 1);
    }
    else if (temp == 2)
    {
        make_move(x_, y_, x_, y_ - 1);
    }
    else if (temp == 3)
    {
        make_move(x_, y_, x_ + 1, y_ + 1);
    }
    else if (temp == 4)
    {
        make_move(x_, y_, x_ + 1, y_);
    }
    else if (temp == 5)
    {
        make_move(x_, y_, x_ - 1, y_);
    }
    else
    {
        make_move(x_, y_, x_ - 1, y_ + 1);
    }
}
void SG_odd(int x, int y, int x_, int y_)
{
    switch (map[x_][y_ + 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (y_ != 8)
        {
            if (map[x_][y_ + 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_) + abs(y - y_ - 1)))
                printf("1. move to North  ");
        }
    }
    switch (map[x_][y_ - 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (y_ != 0)
        {
            if (map[x_][y_ - 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_) + abs(y - y_ + 1)))
                printf("2. move to South  ");
        }
    }
    switch (map[x_ + 1][y_].place_type)
    {
    case normal:
    case open:
    case close:
        if (x_ != 12)
        {
            if (map[x_ + 1][y_].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ - 1) + abs(y - y_)))
                printf("3. move to North-East  ");
        }
    }
    switch (map[x_ + 1][y_ - 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (x_ != 12 && y_ != 0)
        {
            if (map[x_ + 1][y_ - 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ - 1) + abs(y - y_ + 1)))
                printf("4. move to South-East  ");
        }
    }
    switch (map[x_ - 1][y_ - 1].place_type)
    {
    case normal:
    case open:
    case close:
        if (x_ != 0 && y_ != 0)
        {
            if (map[x_ - 1][y_ - 1].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ + 1) + abs(y - y_ + 1)))
                printf("5.move to South-West  ");
        }
    }
    switch (map[x_ - 1][y_].place_type)
    {
    case normal:
    case open:
    case close:
        if (x_ != 0)
        {
            if (map[x_ - 1][y_].character == 10 && (abs(x - x_) + abs(y - y_) > abs(x - x_ + 1) + abs(y - y_)))
                printf("6. move to North-West  ");
        }
    }
    int temp;
    scanf("%d", &temp);
    if (temp == 1)
    {
        make_move(x_, y_, x_, y_ + 1);
    }
    else if (temp == 2)
    {
        make_move(x_, y_, x_, y_ - 1);
    }
    else if (temp == 3)
    {
        make_move(x_, y_, x_ + 1, y_);
    }
    else if (temp == 4)
    {
        make_move(x_, y_, x_ + 1, y_ - 1);
    }
    else if (temp == 5)
    {
        make_move(x_, y_, x_ - 1, y_ - 1);
    }
    else
    {
        make_move(x_, y_, x_ - 1, y_);
    }
}
JW_action(){
    printf("\t\t\tWhich direction would you like the lantern to be?\n\t\t\t");
    printf("0. North  1. North-East  2. South-East  3. South  4. South-West  5. North_west\n\t\t\t");
    scanf("%d", &lantern_dir);
    map_printer();
    return;
}
void visible()
{// This function shows that Mr.Jack is visible or not to find out that can Mr.Jack escape or not;
    int x, y; // MrJack mokhtasat;
    int flag = 0;
    for(int i = 0; i < 13; i++)
    {
        int temp = 0;
        for(int j = 0; j < 9; j++)
        {
            if(map[i][j].character == MrJack)
            {
                x = i;
                y = j;
                
                temp = 1;
                break;
            }
        }
        if(temp == 1)
            break;
    }
    if(x % 2) // even x; FOR CHEKING LIGHTS AND NEIGHBOR CHARACTERS;
    {
        if((map[x][y+1].place_type == light_on && y != 8) || (map[x][y-1].place_type == light_on && y != 0) || (map[x+1][y+1].place_type == light_on && x != 12 && y != 8) ||
            (map[x+1][y].place_type == light_on && x != 12) || (map[x-1][y].place_type == light_on && x != 0) || (map[x-1][y+1].place_type == light_on && x != 0 && y != 8) ||
            (map[x][y+1].character != 10 && y != 8) || (map[x][y-1].character != 10 && y != 0) || (map[x+1][y+1].character != 10 && x != 12 && y != 8) ||
            (map[x+1][y].character != 10 && x != 12) || (map[x-1][y].character != 10 && x != 0) || (map[x-1][y+1].character != 10 && x != 0 && y != 8))
            {
            visible_condition = 1;
            
            flag = 1;
            }
    }
    else
    {
        if((map[x][y+1].place_type == light_on && y != 8) || (map[x][y-1].place_type == light_on && y != 0) || (map[x+1][y].place_type == light_on && x != 12) ||
           (map[x+1][y-1].place_type == light_on && x != 12 && y != 0) || (map[x-1][y-1].place_type == light_on && x != 0 && y != 0) || (map[x-1][y].place_type == light_on && x != 0) ||
           (map[x][y+1].character != 10 && y != 8) || (map[x][y-1].character != 10 && y != 0) || (map[x+1][y].character != 10 && x != 12) ||
           (map[x+1][y-1].character != 10 && x != 12 && y != 0) || (map[x-1][y-1].character != 10 && x != 0 && y != 0) || (map[x-1][y].character != 10 && x != 0))
           {
            visible_condition = 1;
            
            flag = 1;
           }
    }
    if(flag == 1) // cheking if MrJack is found or not;
    {
        visible2();
        return;
    }
    if(JW_x % 2) // even x
    {                                                                //0. North  1. North-East  2. South-East  3. South  4. South-West  5. North_west
        int x_temp = JW_x, y_temp = JW_y;
        if(lantern_dir == 0)
        {
            while(map[x_temp][y_temp + 1].place_type != house && map[x_temp][y_temp + 1].place_type != addition && y_temp != 8)
            {
                y_temp++;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 1)
        {
            while(map[x_temp + 1][y_temp + 1].place_type != house && map[x_temp + 1][y_temp + 1].place_type != addition && y_temp != 8 && x_temp != 12)
            {
                x_temp++;
                y_temp++;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
                {
                    x_temp++;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else
                {
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible2();
            visible_condition = 0;
            
            return;
        }
        else if(lantern_dir == 2)
        {
            while(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
            {
                x_temp++;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp + 1][y_temp - 1].place_type != house && map[x_temp + 1][y_temp - 1].place_type != addition && y_temp != 0 && x_temp != 12)
                {
                    x_temp++;
                    y_temp--;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else{
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 3)
        {
            while(map[x_temp][y_temp - 1].place_type != house && map[x_temp][y_temp - 1].place_type != addition && y != 0)
            {
                y--;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 4)
        {
            while(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
            {
                x_temp--;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp - 1][y_temp - 1].place_type != house && map[x_temp - 1][y_temp - 1].place_type != addition && y_temp != 0 && x_temp != 0)
                {
                    x_temp--;
                    y_temp--;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else
                {
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 5)
        {
            while(map[x_temp - 1][y_temp + 1].place_type != house && map[x_temp - 1][y_temp + 1].place_type != addition && x_temp != 0 && y != 8)
            {
                x_temp--;
                y_temp++;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
                {
                    x_temp--;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else
                {
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
    }
    else
    {
        int x_temp = JW_x, y_temp = JW_y;
        if(lantern_dir == 0)
        {
            while(map[x_temp][y_temp + 1].place_type != house && map[x_temp][y_temp + 1].place_type != addition && y_temp != 8)
            {
                y_temp++;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 1)
        {
            while(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
            {
                x_temp++;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp + 1][y_temp + 1].place_type != house && map[x_temp + 1][y_temp + 1].place_type != addition && y_temp != 8 && x_temp != 12)
                {
                    x_temp++;
                    y_temp++;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else
                {
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 2)
        {
            while(map[x_temp + 1][y_temp - 1].place_type != house && map[x_temp + 1][y_temp - 1].place_type != addition && x_temp != 12 && y_temp != 0)
            {
                x_temp++;
                y_temp--;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
                {
                    x_temp++;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else{
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible2();
            visible_condition = 0;
            
            return;
        }
        else if(lantern_dir == 3)
        {
            while(map[x_temp][y_temp - 1].place_type != house && map[x_temp][y_temp - 1].place_type != addition && y != 0)
            {
                y_temp--;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 4)
        {
            while(map[x_temp - 1][y_temp - 1].place_type != house && map[x_temp - 1][y_temp - 1].place_type != addition && x_temp != 0 && y_temp != 0)
            {
                x_temp--;
                y_temp--;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
                {
                    x_temp--;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else
                {
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible_condition = 0;
            
            visible2();
            return;
        }
        else if(lantern_dir == 5)
        {
            while(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
            {
                x_temp--;
                
                if(map[x_temp][y_temp].character == MrJack)
                {
                    
                    visible_condition = 1;
                    flag = 1;
                    visible2();
                    return;
                }
                if(map[x_temp - 1][y_temp + 1].place_type != house && map[x_temp - 1][y_temp + 1].place_type != addition && x_temp != 0 && y != 12)
                {
                    x_temp--;
                    y_temp++;
                    
                    if(map[x_temp][y_temp].character == MrJack)
                    {
                        
                        visible_condition = 1;
                        flag = 1;
                        visible2();
                        return;
                    }
                }
                else
                {
                    visible_condition = 0;
                    
                    visible2();
                    return;
                }
            }
            visible2();
            visible_condition = 0;
            
            return;
        }

    } //*
    visible_condition = 0;
    
    visible2();
    return;
}
void visible2() 
{
    if(visible_condition) // MrJack is visible;
    {
        int array[30];
        int x = 0;
        for(int i = 0; i < 30; i++)
        {
            array[i] = -1;              
        }
        for(int i = 0; i < 13; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if(map[i][j].character < 10) // wasn't innocent before; CHEKING LIGHTS AND NEIGHBORS
                {
                    if(i % 2) //even
                    {
                    if((map[i][j+1].place_type == light_on && j != 8) || (map[i][j-1].place_type == light_on && j != 0) || (map[i+1][j+1].place_type == light_on && i != 12 && j != 8) ||
                    (map[i+1][j].place_type == light_on && i != 12) || (map[i-1][j].place_type == light_on && i != 0) || (map[i-1][j+1].place_type == light_on && i != 0 && j != 8) ||
                    (map[i][j+1].character != 10 && j != 8) || (map[i][j-1].character != 10 && j != 0) || (map[i+1][j+1].character != 10 && i != 12 && j != 8) ||
                    (map[i+1][j].character != 10 && i != 12) || (map[i-1][j].character != 10 && i != 0) || (map[i-1][j+1].character != 10 && i != 0 && j != 8))
                    {
                        array[x] = map[i][j].character;
                        x++;
                    }
                    }
                    else      // odd
                    {
                    if((map[i][j+1].place_type == light_on && j != 8) || (map[i][j-1].place_type == light_on && j != 0) || (map[i+1][j].place_type == light_on && i != 12) ||
                    (map[i+1][j-1].place_type == light_on && i != 12 && j != 0) || (map[i-1][j-1].place_type == light_on && i != 0 && j != 0) || (map[i-1][j].place_type == light_on && i != 0) ||
                    (map[i][j+1].character != 10 && j != 8) || (map[i][j-1].character != 10 && j != 0) || (map[i+1][j].character != 10 && i != 12) ||
                    (map[i+1][j-1].character != 10 && i != 12 && j != 0) || (map[i-1][j-1].character != 10 && i != 0 && j != 0) || (map[i-1][j].character != 10 && i != 0))
                    {
                        array[x] = map[i][j].character;
                        x++;
                    }
                    }
                }
            }
        }
        if(JW_x % 2) // even x
    {                                                                //0. North  1. North-East  2. South-East  3. South  4. South-West  5. North_west
        int x_temp = JW_x, y_temp = JW_y;
        if(lantern_dir == 0)
        {
            while(map[x_temp][y_temp + 1].place_type != house && map[x_temp][y_temp + 1].place_type != addition && y_temp != 8)
            {
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                }
            }
            return;
        }
        else if(lantern_dir == 1)
        {
            while(map[x_temp + 1][y_temp + 1].place_type != house && map[x_temp + 1][y_temp + 1].place_type != addition && y_temp != 8 && x_temp != 12)
            {
                x_temp++;
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++; 
                }
                if(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
                {
                    x_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 2)
        {
            while(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
            {
                x_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
                if(map[x_temp + 1][y_temp - 1].place_type != house && map[x_temp + 1][y_temp - 1].place_type != addition && y_temp != 0 && x_temp != 12)
                {
                    x_temp++;
                    y_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 3)
        {
            while(map[x_temp][y_temp - 1].place_type != house && map[x_temp][y_temp - 1].place_type != addition && y_temp != 0)
            {
                y_temp--;
                if(map[x_temp][y_temp].character  < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
            }
            return;
        }
        else if(lantern_dir == 4)
        {
            while(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
            {
                x_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
                if(map[x_temp - 1][y_temp - 1].place_type != house && map[x_temp - 1][y_temp - 1].place_type != addition && y_temp != 0 && x_temp != 0)
                {
                    x_temp--;
                    y_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 5)
        {
            while(map[x_temp - 1][y_temp + 1].place_type != house && map[x_temp - 1][y_temp + 1].place_type != addition && x_temp != 0 && y_temp != 8)
            {
                x_temp--;
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
                if(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
                {
                    x_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                    return;
            }
            return;
        }
    }
    else
    {
        int x_temp = JW_x, y_temp = JW_y;
        if(lantern_dir == 0)
        {
            while(map[x_temp][y_temp + 1].place_type != house && map[x_temp][y_temp + 1].place_type != addition && y_temp != 8)
            {
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
            }
            return;
        }
        else if(lantern_dir == 1)
        {
            while(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
            {
                x_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
                if(map[x_temp + 1][y_temp + 1].place_type != house && map[x_temp + 1][y_temp + 1].place_type != addition && y_temp != 8 && x_temp != 12)
                {
                    x_temp++;
                    y_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 2)
        {
            while(map[x_temp + 1][y_temp - 1].place_type != house && map[x_temp + 1][y_temp - 1].place_type != addition && x_temp != 12 && y_temp != 0)
            {
                x_temp++;
                y_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
                if(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
                {
                    x_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 3)
        {
            while(map[x_temp][y_temp - 1].place_type != house && map[x_temp][y_temp - 1].place_type != addition && y_temp != 0)
            {
                y_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
            }
            return;
        }
        else if(lantern_dir == 4)
        {
            while(map[x_temp - 1][y_temp - 1].place_type != house && map[x_temp - 1][y_temp - 1].place_type != addition && x_temp != 0 && y_temp != 0)
            {
                x_temp--;
                y_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
                if(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
                {
                    x_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                {
                    return;
                }
            }
            return;
        }
        else if(lantern_dir == 5)
        {
            while(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
            {
                x_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    array[x] = map[x_temp][y_temp].character;
                    x++;
                }
                if(map[x_temp - 1][y_temp + 1].place_type != house && map[x_temp - 1][y_temp + 1].place_type != addition && x_temp != 0 && y_temp != 12)
                {
                    x_temp--;
                    y_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        array[x] = map[x_temp][y_temp].character;
                        x++;
                    }
                }
                else
                    return;
            }
            return;
        }
    }
    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(map[i][j].character < 10)
            {
                int flag = 0;
                for(int z = 0; z < 30; z++)
                {
                    if(array[z] == map[i][j].character)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    map[i][j].character += 20;
                }
            }
        }
    }
    }
    else       // MrJack is not visible;
    {
        for(int i = 0; i < 13; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if(map[i][j].character < 10) // wasn't innocent before; CHEKING LIGHTS AND NEIGHBORS
                {
                    if(i % 2) //even
                    {
                    if((map[i][j+1].place_type == light_on && j != 8) || (map[i][j-1].place_type == light_on && j != 0) || (map[i+1][j+1].place_type == light_on && i != 12 && j != 8) ||
                    (map[i+1][j].place_type == light_on && i != 12) || (map[i-1][j].place_type == light_on && i != 0) || (map[i-1][j+1].place_type == light_on && i != 0 && j != 8) ||
                    (map[i][j+1].character != 10 && j != 8) || (map[i][j-1].character != 10 && j != 0) || (map[i+1][j+1].character != 10 && i != 12 && j != 8) ||
                    (map[i+1][j].character != 10 && i != 12) || (map[i-1][j].character != 10 && i != 0) || (map[i-1][j+1].character != 10 && i != 0 && j != 8))
                    {
                        map[i][j].character += 20;
                    }
                    }
                    else      // odd
                    {
                    if((map[i][j+1].place_type == light_on && j != 8) || (map[i][j-1].place_type == light_on && j != 0) || (map[i+1][j].place_type == light_on && i != 12) ||
                    (map[i+1][j-1].place_type == light_on && i != 12 && j != 0) || (map[i-1][j-1].place_type == light_on && i != 0 && j != 0) || (map[i-1][j].place_type == light_on && i != 0) ||
                    (map[i][j+1].character != 10 && j != 8) || (map[i][j-1].character != 10 && j != 0) || (map[i+1][j].character != 10 && i != 12) ||
                    (map[i+1][j-1].character != 10 && i != 12 && j != 0) || (map[i-1][j-1].character != 10 && i != 0 && j != 0) || (map[i-1][j].character != 10 && i != 0))
                    {
                        map[i][j].character += 20;
                    }
                    }
                }
            }
        }
        if(JW_x % 2) // even x
    {                                                                //0. North  1. North-East  2. South-East  3. South  4. South-West  5. North_west
        int x_temp = JW_x, y_temp = JW_y;
        if(lantern_dir == 0)
        {
            while(map[x_temp][y_temp + 1].place_type != house && map[x_temp][y_temp + 1].place_type != addition && y_temp != 8)
            {
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
            }
            return;
        }
        else if(lantern_dir == 1)
        {
            while(map[x_temp + 1][y_temp + 1].place_type != house && map[x_temp + 1][y_temp + 1].place_type != addition && y_temp != 8 && x_temp != 12)
            {
                x_temp++;
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20; 
                }
                if(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
                {
                    x_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 2)
        {
            while(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
            {
                x_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
                if(map[x_temp + 1][y_temp - 1].place_type != house && map[x_temp + 1][y_temp - 1].place_type != addition && y_temp != 0 && x_temp != 12)
                {
                    x_temp++;
                    y_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 3)
        {
            while(map[x_temp][y_temp - 1].place_type != house && map[x_temp][y_temp - 1].place_type != addition && y_temp != 0)
            {
                y_temp--;
                if(map[x_temp][y_temp].character  < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
            }
            return;
        }
        else if(lantern_dir == 4)
        {
            while(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
            {
                x_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
                if(map[x_temp - 1][y_temp - 1].place_type != house && map[x_temp - 1][y_temp - 1].place_type != addition && y_temp != 0 && x_temp != 0)
                {
                    x_temp--;
                    y_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 5)
        {
            while(map[x_temp - 1][y_temp + 1].place_type != house && map[x_temp - 1][y_temp + 1].place_type != addition && x_temp != 0 && y_temp != 8)
            {
                x_temp--;
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
                if(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
                {
                    x_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                    return;
            }
            return;
        }
    }
    else
    {
        int x_temp = JW_x, y_temp = JW_y;
        if(lantern_dir == 0)
        {
            while(map[x_temp][y_temp + 1].place_type != house && map[x_temp][y_temp + 1].place_type != addition && y_temp != 8)
            {
                y_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
            }
            return;
        }
        else if(lantern_dir == 1)
        {
            while(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
            {
                x_temp++;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
                if(map[x_temp + 1][y_temp + 1].place_type != house && map[x_temp + 1][y_temp + 1].place_type != addition && y_temp != 8 && x_temp != 12)
                {
                    x_temp++;
                    y_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 2)
        {
            while(map[x_temp + 1][y_temp - 1].place_type != house && map[x_temp + 1][y_temp - 1].place_type != addition && x_temp != 12 && y_temp != 0)
            {
                x_temp++;
                y_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
                if(map[x_temp + 1][y_temp].place_type != house && map[x_temp + 1][y_temp].place_type != addition && x_temp != 12)
                {
                    x_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                    return;
            }
            return;
        }
        else if(lantern_dir == 3)
        {
            while(map[x_temp][y_temp - 1].place_type != house && map[x_temp][y_temp - 1].place_type != addition && y_temp != 0)
            {
                y_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
            }
            return;
        }
        else if(lantern_dir == 4)
        {
            while(map[x_temp - 1][y_temp - 1].place_type != house && map[x_temp - 1][y_temp - 1].place_type != addition && x_temp != 0 && y_temp != 0)
            {
                x_temp--;
                y_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
                if(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
                {
                    x_temp--;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                {
                    return;
                }
            }
            return;
        }
        else if(lantern_dir == 5)
        {
            while(map[x_temp - 1][y_temp].place_type != house && map[x_temp - 1][y_temp].place_type != addition && x_temp != 0)
            {
                x_temp--;
                if(map[x_temp][y_temp].character < 10)
                {
                    map[x_temp][y_temp].character += 20;
                }
                if(map[x_temp - 1][y_temp + 1].place_type != house && map[x_temp - 1][y_temp + 1].place_type != addition && x_temp != 0 && y_temp != 12)
                {
                    x_temp--;
                    y_temp++;
                    if(map[x_temp][y_temp].character < 10)
                    {
                        map[x_temp][y_temp].character += 20;
                    }
                }
                else
                    return;
            }
            return;
        }

    }
    } //
}