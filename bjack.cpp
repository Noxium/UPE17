#include "bjack.h"

using std::string;
using std::printf;
using std::cin;


void bjack::run(int x, int y) {
    resetUI(x, y);
    char c;
        printf("Last user input =  ");
    while((c=echoEnable()) != 'q') {
        if(c != '\n') printf("\b%c", c);
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

void bjack::print_card(int num) {
    // assumes cursor is top left with at least 5 free rows underneath
    num = num;
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
    string options = "H - Hit me      S - Stand";
    int card_h = 5;
    int card_w = 7;

    int filler_offset = 6;

    // print
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
        if(i == y-1 || i == y-3) {
            printf("\r");
            for(int i = 0; i < options_width-1; i++) {
                printf(" ");
            }
            printf("|");
        } else if(i == y-2) {
            printf("\r");
            for(int i = 0; i < options_width-1; i++) {
                printf(" ");
                if(i == (options_width/2 - (int)options.size()/2)) {
                    printf("%s", options.c_str());
                    i += options.size();
                }
            }
            printf("|");
        } else if(i == y-4) {
            printf("\r");
            for(int i = 0; i < options_width-1; i++) {
                printf("-");
            }
            printf("+");
        } else if(i == y - 6 - card_h) {
            printf("\r");
            printf("Chance to 21\t- 100%%");
            card_w = card_w;
        } else if(i == y - 7 - card_h) {
            printf("\r");
            printf("Chance to bust\t- 100%%");
        }


        // bullshit filler
        if(i == 0) {
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

        printf("\n");
    }
}
