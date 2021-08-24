#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
//A pajzs megállítja a lotot, szerencsére a pajzs megmarad. meg nem szünteti.
using namespace std;

bool gameOver;
bool gift;
const int magassag = 30;
const int szelesseg = 7;
int tabla[magassag * szelesseg];
int kar_x, score;

enum eDirecton { ALJ = 0, JOBB, BAL, TUZ };//Tuz fel lenyomása
eDirecton Move;


void felepit();
void rajz(int score);
void bejon();
void logika(int& score);

int main()
{
    setlocale(LC_ALL, "hun");
    
    bool playtime = true;
    while (playtime)
    {
        felepit();
        while (!gameOver) {
            rajz(score);
            bejon();
            logika(score);
            Sleep(100);
        }
        rajz(score);
        cout << " Created by Mr.V.A.Lacky\n - Ha új játékot akar kezdeni nyomja meg az R gombot\n - Ha ki akar lépni nyomja meg az E gyombot\nVálasztott opció:";
        bool buta = true;
        while (buta) {
            if (_kbhit()) {
                switch (_getch()) {
                case 'r':
                case 'R':
                    buta = false;
                    break;
                case 'e':
                case 'E':
                    buta = false;
                    playtime = false;
                    break;
                default: break;
                }
            }
        }
    }
}
 

void felepit() {
    gameOver = false;
    gift = false;
    score = 0;
    srand(time(0));
    Move = ALJ;
    /*
    viz = 0
    oldal = 1
    ágyú = 2
    karakter = 3
    ures = 4
    ellenfel = 5
    lövedés = 6
    megsemmisülés = 7
    */
    for (int i = 0; i < (magassag * szelesseg); i++) {
        if (i % szelesseg == 0 || i % szelesseg == (szelesseg - 1)) {
            tabla[i] = 1;
        }
        else {
            if (i / szelesseg == (magassag - 2)) {
                tabla[i] = 2;
            }
            else {
                if (i / szelesseg == (magassag - 1)) {
                    if (i % szelesseg == szelesseg / 2) {
                        tabla[i] = 3;
                        kar_x = i;
                    }
                    else {
                        tabla[i] = 0;
                    }
                }
                else {
                    tabla[i] = 0;
                }
            }
        }
    }
}
void rajz(int score) {
    system("cls");
    for (int i = 0; i < (magassag * szelesseg); i++) {
        switch (tabla[i]){
            case 0: cout << "   "; break;
            case 1: cout << "|-|"; break;
            case 2: cout << "_U_"; break;
            case 3: cout << "\\o/"; break;
            case 4: cout << ""; break;
            case 5: cout << " V "; break;
            case 6: cout << " ° "; break;
            case 7: cout << " X ";
                tabla[i] = 0;
                break;
            case 8: cout << "[?]"; break;
            case 9: cout << "###"; break;
        }
        
        if (i % szelesseg == (szelesseg - 1)) {
            switch (i/szelesseg - 1)
            {
            case magassag - 4:
                cout << "Press W to shout" << endl;;
                break;
            case magassag - 3:
                cout << "Press A to go left" << endl;;
                break;
            case magassag - 2:
                cout << "Press D to go right" << endl;;
                break;
            default:
                cout << endl;
                break;
            }
        }
    }
    cout << "Score: " << score;
}
void bejon() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'D':
        case 'd':
            Move = JOBB; break;
        case 'A':
        case 'a':
            Move = BAL; break;
        case 'W':
        case 'w':
            Move = TUZ; break;
        default: break;
        }
    }
}
void logika(int& score) {
    int gen;
    int ell;
    int alapgen = 20;//20
    int harder = 4;//4
    int lootgen = 3;//3
    int luckplusz = 1;

    //ellenfel mozog és loot mozog
    for (gen = (magassag * szelesseg) - 1; gen >= 0; gen--) {
        if (tabla[gen] == 5) {
            tabla[gen] = 0;
            if (gen + szelesseg < magassag * szelesseg) {
                if (tabla[gen + szelesseg] == 6 || tabla[gen + szelesseg] == 9 || (tabla[gen + szelesseg] == 2 && gen + szelesseg < (((magassag - 1) * szelesseg) - szelesseg))){
                    tabla[gen + szelesseg] = 7;
                    score = score + 10;
                }
                else {
                    tabla[gen + szelesseg] = 5;
                    if (((gen + szelesseg) > (((magassag - 1) * szelesseg) - szelesseg)) && ((gen + szelesseg) < ((magassag - 1) * szelesseg) - 1)) {
                        tabla[gen + szelesseg] = 7;
                        gameOver = true;
                    }
                }

            }
        }
        if (tabla[gen] == 8) {
            if ((gen > (((magassag - 1) * szelesseg) - szelesseg)) && gen < ((magassag - 1) * szelesseg) - 1){
                tabla[gen] = 2;
            }else{
                tabla[gen] = 0;
            }
            if (gen + szelesseg < magassag * szelesseg) {
                if (tabla[gen + szelesseg] == 3) {
                    gift = true;
                }else {
                    if (tabla[gen + szelesseg] == 6 || tabla[gen + szelesseg] == 9 || tabla[gen + szelesseg] == 2) {
                        int i = 1;
                        do {
                            if (gen + i * szelesseg < magassag * szelesseg) {
                                if (tabla[gen + i * szelesseg] != 0 && gen + i * szelesseg < ((magassag - 1) * szelesseg) - szelesseg){
                                  i++;
                                }else {
                                    tabla[gen + i * szelesseg] = 8;
                                    i = (-1);
                                }
                            }
                            else {
                                i = (-1);
                            }
                        } while (i != (-1));
                    }else {
                        tabla[gen + szelesseg] = 8; 
                    }
               }
            }
        }
    }
    //lövedék mozog
    for (gen = 0; gen < (magassag * szelesseg) - 1; gen++) {
        if (tabla[gen] == 6) {
            tabla[gen] = 0;
            
            if (gen - szelesseg >= 0) {
                if (tabla[gen - szelesseg] == 5) {
                    tabla[gen - szelesseg] = 7;
                    score = score + 10;
                }
                else {
                    if (tabla[gen - szelesseg] == 8) {
                        int i = 1;
                        do {
                            if (gen - i * szelesseg >= 0) {
                                if (tabla[gen - (i * szelesseg)] == 8) {
                                    i++;
                                }
                                else {
                                    tabla[gen - (i * szelesseg)] = 6;
                                    i = (-1);
                                }
                            }
                            else {
                                i = (-1);
                            }
                        } while (i != (-1));
                    }
                    else {
                        tabla[gen - szelesseg] = 6;
                    }
                }
            }
        }
    }
    //elenfel generalas
    ell = rand() % 100;
    if (ell < alapgen + harder * (score / 100)) {
        ell = 1;
    }
    else {
        ell = 0;
    }
    if (ell == 1) {
        do {
            ell = rand() % szelesseg;
        } while (ell == 0 || ell == (szelesseg - 1));
        tabla[ell] = 5;
    }
    //bonusz csomag generálása;
    ell = rand() % 100;
    if (ell < lootgen + luckplusz * (score / 100)) {
        ell = 1;
    } else {
        ell = 0;
    }
    if (ell == 1) {
        do {
            ell = rand() % szelesseg;
        } while (ell == 0 || ell == (szelesseg - 1) || tabla[ell] == 5);
        tabla[ell] = 8;
    }
    //loot hatásai.
    if (gift == true) {
        gift = false;
        ell = rand() % 4;
        switch (ell) {
        case 0:
            //minden hajó elsülyed.
            for (int i = 0; i < (magassag * szelesseg); i++) {
                if (tabla[i] == 5) {
                    tabla[i] = 7;
                    score = score + 10;
                }
            }
            break;
        case 1:
            //pajzs generálása
        {int p1 = rand() % 5;
        do {
            ell = rand() % 5;
        } while (ell == p1);
        p1 = (magassag * szelesseg) - (2 + p1);
        ell = (magassag * szelesseg) - (2 + ell);
        while (tabla[p1] != 0 || p1 > magassag * szelesseg - (1 + 2 * szelesseg)) {
            p1 = p1 - szelesseg;
        }
        if (tabla[p1 + szelesseg] == 8) {
            p1 = p1 + szelesseg;
        }
        tabla[p1] = 9;
        while ( tabla[ell] != 0 || ell > magassag * szelesseg - (1 + 2 * szelesseg)) {
            ell = ell - szelesseg;
        }
        if (tabla[ell + szelesseg] == 8) {
            ell = ell + szelesseg;
        }
        tabla[ell] = 9;
        }
            break;
        case 2: //3 mas lövés
        {int lovdb = 3;
        for (int i = 0; i < szelesseg - 2; i++) {
            ell = magassag * szelesseg - 2 - i;
            while (tabla[ell] == 3 || tabla[ell] == 6 || tabla[ell] == 2 || tabla[ell] == 8 || tabla[ell] == 9 || ell > magassag * szelesseg - (1 + 2 * szelesseg)) {
                ell = ell - szelesseg;
            }
            for (int j = 0; j < lovdb; j++) {
                tabla[ell] = 6;
                ell = ell - szelesseg;
            }
        }
        }break;
        case 3: {// ágyú lerakás
        ell = rand() % 5;
        ell = (magassag * szelesseg) - (2 + ell);
        while (tabla[ell] != 0 || ell > magassag * szelesseg - (1 + 2 * szelesseg)) {
            ell = ell - szelesseg;
        }
        if (tabla[ell + szelesseg] == 8) {
            ell = ell + szelesseg;
        }
            tabla[ell] = 2;
        
        }
            break;
        }
    }
    //játékos
    switch (Move){
    case BAL:
        if ((kar_x - 1) % szelesseg != 0) {
            gen = (magassag * szelesseg - szelesseg - 1);
            while (tabla[gen] != 3) {
                gen++;
            }
            kar_x = (gen - 1);
            tabla[gen] = 0;
            tabla[gen - 1] = 3;
        };
        Move = ALJ;
        break;
    case JOBB:
        if ((kar_x + 1) != (magassag * szelesseg) - 1) {
            gen = (magassag * szelesseg - szelesseg - 1);
            while (tabla[gen] != 3) {
                gen++;
            }
            kar_x = (gen + 1);
            tabla[gen] = 0;
            tabla[gen + 1] = 3;
        }
        Move = ALJ;
        break;
    case TUZ:
    {
        int agydb = 0;
        int i = kar_x - szelesseg;
        while (tabla[i] == 8 || tabla[i] == 2 || tabla[i] == 9) {//pajz ágyú loot chest
            if (tabla[i] == 2) {
                agydb++;
            }
            i = i - szelesseg;
            if (i < 0) { break; }
        }
        for (int j = 0; j < agydb; j++) {
            if (tabla[i] == 5) {
                tabla[i] = 7;
            }
            else {
                tabla[i] = 6;
            }
            i = i - szelesseg;
        }
        Move = ALJ;
    }
        break;
    default:
        break;
    }
}
