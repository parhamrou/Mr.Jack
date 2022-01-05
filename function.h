    typedef struct character{
        char name[20]; // character name;
        struct character *next;
    }character;
    typedef struct place{
        int place_type; // 0.empty   1.light   2.house   3.pit   4.addition place   5.gate
        character *head; // This pointer holds characters that are in that palce; 
    }place;
    // characters:
    character JW = {
        .name = "JW",
        .next = NULL,
    };
    character WG = {
        .name = "WG",
        .next = NULL,
    };
    character IL = {
        .name = "IL",
        .next = NULL,
    };
    character JS = {
        .name = "JS",
        .next = NULL,
    };
    character SH = {
        .name = "SH",
        .next = NULL,
    };
    character JB = {
        .name = "JB",
        .next = NULL,
    };
    character MS = {
        .name = "MS",
        .next = NULL,
    };
    character SG = {
        .name = "SG",
        .next = NULL,
    };
    // two-dimensional array for places:
    place map[13][9];
    randomCard_maker(){
        // This function makes 4 random numbers at the begining of odd rounds and save 4 other cards for next round;
        // 1:SERGENT GOODLEY    2:INSPECTEUR LESTRADE    3:SIR WILLIAM GULL      4:SHERLOCK HOLMES
        // 5:JEREMY BERT        6:JOHN H. WATSON         7:MISS STEALTHY         8:JOHN SMITH
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
            return 0;
        }
        for(int i = 0; i < 13; i++){
            for(int j = 0; j < 9; j++){
                fscanf(fp, "%d", &map[i][j].place_type);
            }
        }
        fclose(fp);
    }
    