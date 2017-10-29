#include "bjack.h"

using std::string;
using std::printf;
using std::cin;

#define CARD_H 5
#define CARD_W 7
#define FACTS_X 3
#define FACTS_Y 19

#define INFO_X 4
#define INFO_Y 55
#define NETWINS_Y 63
#define WINS_Y 72
#define LOSSES_Y 80
#define RATIO_Y 89
#define PUSHES_Y 97
#define TOTALGAMES_Y 107

void bjack::run(int x, int y) {
    for(int i = 0; i < y; i++) printf("\n");
x = x; y = y;
    string amtMsg = "Please enter your starting amount:";
    printf("\033[%i;%iH", y/2, x/2 - (int)amtMsg.size()/2);
    printf("%s", amtMsg.c_str());
    printf("\033[%i;%iH", y/2+1, x/2-2);
    printf("$");
    int amt;
    std::cin >> amt;
    money = amt;

    printf("\033[0;0H");
    resetUI(x, y);
    string msg = "Last user input =  ";
    char c;
        printf("%s", msg.c_str());
    int cardCount = 0;
    while((tolower(c=echoEnable())) != 'q') {
        switch(c){
            case 'h': {
                int num = (rand() % 8)+1;
                cards.push_back(num);
                print_card(std::to_string(num), cardCount);
                int total = 0;
                for(unsigned int i = 0; i < cards.size(); i++) {
                    total += cards[i];
                }
                printf("\033[%i;%iH   \b\b\b%i", FACTS_X + 2, FACTS_Y, total);
                printf("\033[%i;%iH", y+1, (int)msg.size() + 1);
                cardCount++;

                break;
            } case 'r': {
                printf("\n");
                cards.clear();
                resetUI(x, y);
                cardCount = 0;
                printf("%s", msg.c_str());
            } default: {
               if(c != '\n') printf("\b%c", c);
               break;
           }
       }
    }
    printf("\n");
}

char bjack::echoEnable() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = std::getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void bjack::print_simple(string out, int offset, char offset_filler) {
    printf("\r");
    for(int i = 0; i < offset; i++) {
        printf("%c", offset_filler);
    }
    printf("%s", out.c_str());
}

void bjack::print_simple(string out, int offset) {
    print_simple(out, offset, ' ');
}

void bjack::print_simple(string out) {
    print_simple(out, 0, ' ');
}

/**
 * Prints cards in this format
 * 
 * +-----+
 * |     |
 * |  n  |
 * |     |
 * +-----+

 * @param num Numer displayed inside card - value of 0 will clear
 * @param cardNum Count of how many cards are on the 'table.' 1st card is 0
 */
void bjack::print_card(std::string num, int cardNum) {
    // assumes cursor is top left with at least 5 free rows underneath
    int offset = (CARD_W) * (cardNum) + (cardNum);
    if(cardNum == 0) offset = 1;
    for(int i = 0; i < CARD_H; i++) {
        printf("\r");
        printf("\033[%i;%iH", 12+i, offset);
        if(i == 0 || i == 4) {
            printf("+-----+");
        } 
        if(i > 0 && i < 4) {
            printf("|     |");
            if(i == 2) {
                printf("\033[%i;%iH%c", 12+i, offset+3, num.c_str()[0]);
            }
        }
    }
        printf("\033[%i;%iH", 0, 0);
}

void bjack::resetUI(int x, int y) {
    // offsets and other info
    string info = "#  | Net wins | Wins | Losses | ";
    info += "Ratio | Pushes | Total games";
    int info_offset = x-(info.size())-14;
    int num_info_lines = 17;
    int LS_offset = y-1;
    LS_offset = LS_offset;

    int options_width = 40;
    string options1 = "H - Hit me      S - Stand";
    string options2 = "D - Double      P - Split";

    //int filler_offset = 6;

    // print
    //printf("\033[0;0H");
    for(int i = 0; i < y; i++) {
        // prints stats: top -> bottem
        if(i == 1) {
            // info header
            printf("\r");
            for(int j = 0; j < info_offset; j++) {
                printf(" ");
            }
            printf("%s", info.c_str());
        } else if(i == 2) {
            // underline
            printf("\r");
            for(int j = 0; j < info_offset; j++) {
                printf(" ");
            }
            for(unsigned int j = 0; j < info.size(); j++) {
                printf("-");
            }
        } else if(i >= 3 && i < num_info_lines+3) {
            // dividers
            printf("\r");
            for(int j = 0; j < info_offset; j++) {
                printf(" ");
            }
            printf("   |          |      |        |       |        |");
        }

        // print cards: bottem -> top
        if(i == y-1 || i == y-4) {
            printf("\r");
            for(int i = 0; i < options_width-1; i++) {
                printf(" ");
            }
            printf("|");
        } else if(i == y-2) {
            printf("\r");
            for(int i = 0; i < options_width-1; i++) {
                printf(" ");
                if(i == (options_width/2 - (int)options1.size()/2)) {
                    printf("%s", options2.c_str());
                    i += options1.size();
                }
            }
            printf("|");
        } else if(i == y-3) {
            printf("\r");
            for(int i = 0; i < options_width-1; i++) {
                printf(" ");
                if(i == (options_width/2 - (int)options1.size()/2)) {
                    printf("%s", options1.c_str());
                    i += options1.size();
                }
            }
            printf("|");
        } else if(i == y-5) {
            printf("\r");
            for(int i = 0; i < options_width-1; i++) {
                printf("-");
            }
            printf("+");
        } else if(i == y - 10 - CARD_H) {
            printf("\r");
            printf("Pot total\t- $%i", pot);
        } else if(i == y - 11 - CARD_H) {
            printf("\r");
            printf("Available money\t- $%i", money);
        } else if(i == y - 12 - CARD_H) {
            printf("\r");
            int num = 0;
            for(unsigned int i = 0; i < cards.size(); i++) num += cards[i];
            printf("Card total\t- %i", num);
        } else if(i == y - 13 - CARD_H) {
            printf("\r");
            printf("Chance to 21\t- 100%%");
        } else if(i == y - 14 - CARD_H) {
            printf("\r");
            printf("Chance to bust\t- 100%%");
        }

        // cards
        /*
        if(i == y - 1) {//y - 5) {
            print_card("3", 0);
            print_card("2", 1);
            print_card("9", 2);
            print_card("4", 4);
            printf("\033[%i;%iH",x,y);
        }
*/

        // filler: top - bottem
/*        if(i == 0) {
            print_simple(" _____", filler_offset);
        } else if(i == 1) {
            print_simple("|A .  | _____", filler_offset);
        } else if(i == 2) {
            print_simple("| /.\\ ||A ^  | _____", filler_offset);
        } else if(i == 3) {
            print_simple("|(_._)|| / \\ ||A _  | _____", filler_offset);
        } else if(i == 4) {
            print_simple("|  |  || \\ / || ( ) ||A_ _ |", filler_offset);
        } else if(i == 5) {
            print_simple("|____V||  .  ||(_'_)||( v )|", filler_offset);
        } else if(i == 6) {
            print_simple("       |____V||  |  || \\ / |", filler_offset);
        } else if(i == 7) {
            print_simple("              |____V||  .  |", filler_offset);
        } else if(i == 8) {
            print_simple("                     |____V|", filler_offset);
        }
*/
        printf("\n");
    }
}
