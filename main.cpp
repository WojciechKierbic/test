#include <iostream>

using namespace std;

int N,n;
int MIN=-1000;
int MAX=1000;

/* ***************DRAW******************
 * funkcja rysujaca plansze w treminialu
 * argumenty - tablica char stanu gry
 * zwraca - nic
 */
void draw(char t[])
{
    for(int i = 1; i <= n; i++)
    {
        cout << " " << t[i] << " ";
        if(i % N)       cout << "|";
        else if(i != n) cout << endl;
        else            cout << endl;
    }
}

/* ***************REMIS******************
 * funkcja sprawdza czy mamy jakiekolwiek puste pola na planszy
 * argumenty - tablica stanu gry,pomocniczy bool
 * zwraca - true/false
 */
bool remis(char t[], bool help)
{

    for(int i = 1; i <= n; i++)
    {
        if(t[i] == '-') //jesli znajdziemy myslnik nie ma remisu
            return false;
    }

    if(!help)
    {
        draw(t);
        cout <<endl<<"REMIS"<<endl;
    }
    return true;
}

/* ***************WIN******************
 * funkcja sprawdza czy dany zawodnik w bie¿¹cej rundzie wygra³ grê
 * argumenty - tablica stanu gry, gracz, pomocniczy bool
 * zwraca - true/false
 */
bool win(char t[], char g, bool help)
{
    bool test;
    test = false; //zmienia na true tylko gdy mamy 3 figury w wierszu kolumie czy po porzekatnej
    int i;
    //wiersze
    for(i = 1; i <= n; i++)
    {
        if((i % N != 0) && (i % N != N-1)){
        test |= ((t[i] == g) && (t[i+1] == g) && (t[i+2] == g));
        }
    }
    //kolumny
    for(i = 1; i <= n; i++)
    {
        test |= ((t[i] == g) && (t[i+N] == g) && (t[i+(2*N)] == g));
    }
    //przekatne
    for(i = 1; i <= n; i++)
    {
        if((i % N != 0) && (i % N != N-1)){
        test |= ((t[i] == g) && (t[i+N+1] == g) && (t[i+2*(N+1)] == g));
        }
        if((i % N != 1) && (i % N != 2))
        {
         test |= ((t[i] == g) && (t[i+N-1] == g) && (t[i+2*(N-1)] == g));
        }
       // test |= ((t[3] == g) && (t[5] == g) && (t[7] == g));
    }



    if(test)
    {
        if(!help)
        {
            draw(t);
            cout <<endl << g << " WYGRYWA!!!"<<endl;
        }
        return true;
    }
    return false;
}

/* ***************MINIMAX******************
 * funkcja oblicza gdzie komputer ma postawic swoj znaczek
 * argumenty - glebokosc, pomocniczy numer indeksu, gracz/przeciwnik, tablica stanu, parametr alfa i beta
 * zwraca - najlepszy ruch, numer indeksu gdzie ma postawic znacznik
 */
int minimax(int depth, int Index, bool maximizingPlayer, char t[], int alpha, int beta)
{

    if (depth == 3){
        return Index;
    }

    if (maximizingPlayer)
    {
        //dla gracza (alfa)
        int best = MIN;
        for (int i = 0; i < 2; i++)
        {
            //rekurencja
            int r = minimax(depth + 1, Index * 2 + i,false, t, alpha, beta);
            best = max(best, r);
            alpha = max(alpha, best);

            // przycinanie alfa-beta
            if (beta <= alpha)
                break;
        }
        return best;
    }
    else
    {
        //dla przeciwnika (beta)
        int best = MAX;
        for (int i = 0; i < 2; i++)
        {
            //rekurencja
            int r = minimax(depth + 1, Index * 2 + i,true, t, alpha, beta);
            best = min(best, r);
            beta = min(beta, best);

            // przycinanie alfa-beta
            if (beta <= alpha)
                break;
        }
        return best;
    }
}

/* ***************SI******************
 * funkcja SI wykunuje obliczony ruch komputera
 * argumenty - tablica stanu
 * zwraca - ruch, ustawienie znacznika
 */
int AI(char t[])
{
    int move, i, m, mmx;

    mmx = MIN;
    for(i = 1; i <= n; i++) //n=N
        if(t[i] == '-')
        {
            t[i] = 'X';
            m = minimax(0,0,true,  t,MIN,MAX);
            t[i] = '-';
            if(m > mmx)
            {
                mmx = m;
                move = i;
            }
        }
    return move;
}

/* ***************GAMER******************
 * funkcja umozliwia wykonanie ruchu przez gracza oraz zmiania kolejnosc na przecinika
 * argumenty - tablica stanu, adres gracz
 * zwraca - nic
 */
void gamer(char t[], char &gracz)
{
    int r;

    draw(t);
    if(gracz == 'O')
    {

        cout << endl <<"Graczu, teraz twoj ruch:  ";
        cin >> r;
        while(r > n || r <=0)
        {
        cerr<<"Nie ma takiego miejsca do wpisania"<<endl;
        r = 0;
        cout << endl <<"Graczu, sprobuj jeszcze raz: ";
        cin >> r;
        }

    }
    else
    {
        r = AI(t);
        cout << endl <<"Teraz ruch algorytmu:  " << r << endl;
    }
    cout <<"********************************"<<endl;
    if((r >= 1) && (r <= n) && (t[r] == '-'))
    {
        t[r] = gracz;
    }
    gracz = (gracz == 'O') ? 'X' : 'O';
}

int main()
{
    cout<<"podaj wielkosc: ";
    cin>>N;
    n=N*N;
    char t[n],gracz,wybor;


        for(int i = 1; i <= n; i++)
        {
            t[i] = '-';
        }

        gracz = 'O';

        while(!win(t,'X',false) && !win(t,'O',false) && !remis(t,false))
        {
            gamer(t,gracz);
        }


}
