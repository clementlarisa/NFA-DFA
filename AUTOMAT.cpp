#include "AUTOMAT.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
ifstream f("AFN.in");


//metoda de creare a matricei ptr AFN
void AUTOMAT::BuildNFA()
{
    //citesc starea start, nr stari finale AFN, starile finale
    //nr litere alfabet, litere alfabet, nr stari
    //nr tranzitii, tranzitiile sub forma s1 - l -> s2

    f >> starei;

    f >> nrf_AFN;
    for ( int i = 0 ; i < nrf_AFN ; i++ )
        f >> F[i];

    f >> nrl;
    for ( int i = 0 ; i < nrl ; i++ )
        f >> A[i];

    f >> nrs_AFN;

    //initializez matricea cu valoarea -1
    for ( int i = 0 ; i < nrs_AFN ; i++ )
        for ( int j = 0 ; j < nrl ; j++ )
            NFA[i][j][0] = -1;

    f >> nrt;

    for ( int i = 0 ; i < nrt ; i++ )
    {
        f >> s1 >> l >> s2;
        int ctr = 0; //contor
        while ( NFA[s1][l-'a'][ctr] != -1 )
            ctr++;
        NFA[s1][l-'a'][ctr] = s2;
        NFA[s1][l-'a'][ctr+1] = -1;
    }
}

//metoda pentru afisarea listei de adiacenta AFN
void AUTOMAT::PrintNFA()
{


    cout << "\n    AFN :\n\n";

    for ( int i = 0 ; i < nrs_AFN ; i++ )
    {
        cout << " starea " << i << " este adiacenta prin";
        for ( int j = 0 ; j < nrl ; j++ )
        {
            cout <<"\n litera " << A[j] << ", cu ";

            int ok = 0;

            for ( int k = 0 ; NFA[i][j][k] != -1 ; k++ )
                cout << NFA[i][j][k], ok = 1;

            if(ok == 0) cout << " nimic ";
        }
        cout << endl << endl;
    }
    cout << "_________________________________________\n";
}


//metoda de verificare pentru adaugarea unei stari
//in care verific daca starea pe care o adaug mai exista
//true -> exista deja; altfel, false
bool AUTOMAT::CheckState(int S[])
{
    int i, k;

    for ( i = 0 ; i < nrs_add ; i++ )
    {
        k = 0;
        while ( DFA[i][nrl][k] != -1
            && S[k] != -1
            && DFA[i][nrl][k] == S[k]
            )
                k++;

        if ( S[k] == -1 && DFA[i][nrl][k] == -1 )
            return true;
    }
    return false;
}

//metoda
void AUTOMAT::SortnDelete(int v[], int n)
{
    int i, j;

    for ( i = 0 ; i < n-1 ; i++)
        for ( j = i+1 ; j < n ; j++ )
        if ( v[i] > v[j] )
            swap(v[i],v[j]);

    for ( i = 0 ; i < n-1 ; i++)
        if ( v[i] == v[i+1] )
    {
        for( j = i+1 ; j < n ; j++ )
            v[j] = v[j+1];
        n--;
    }
}

//metoda de adaugare stari
//pun la final coloana pentru stari
void AUTOMAT::AddState(int ADDED[])
{
    int i, j, k, m;
    if ( CheckState (ADDED) == false )
    {
        for ( i = 0 ; ADDED[i] != -1 ; i++)
            DFA[nrs_add][nrl][i] = ADDED[i];

        DFA[nrs_add][nrl][i] = -1;

        for ( i = 0; i < nrl ; i++ )
        {
            m = 0;

            for ( j = 0 ; ADDED[j] != -1 ; j++)
                for ( k = 0 ; NFA[ADDED[j]][i][k] != -1 ; k++ )
                DFA[nrs_add][i][m++] = NFA[ADDED[j]][i][k];

            DFA[nrs_add][i][m] = -1;
            SortnDelete( DFA[nrs_add][i] , m );
        }
        nrs_add++;
    }
}

//metoda de creare a matricei de AFD
//adaugand, prima data, starea de start in DFA
void AUTOMAT::BuildDFA()
{
    int v[2];
    v[0] = starei;
    v[1] = -1;

    nrs_add = 0;

    AddState(v);

    int i = 0;

    while ( i < nrs_add )
    {
        for ( int j = 0; j < nrl ; j++ )
            if ( DFA[i][j][0] != -1 )
            AddState(DFA[i][j]);
        i++;
    }

    int k, l, q;

    nrs = 0;
    for ( i = 0 ; i < nrs_add ; i++ )
        for ( k = 0 ; DFA[i][nrl][k] != -1 ; k++ )
        for ( l = 0 ; l < nrf_AFN ; l++)
        if ( F[l] == DFA[i][nrl][k] )
        {
            for ( q = 0 ; DFA[i][nrl][q] != -1 ; q++ )
                FIN[nrs][q] = DFA[i][nrl][q];
            FIN[nrs][q] = -1;
            nrs++;
        }
}

//metoda de afisare a listei de adiacenta pentru AFD
void AUTOMAT::PrintDFA()
{
    int i, j, k;
    cout << endl << "    AFD : " << endl << endl;
    for ( i = 0 ; i < nrs_add ; i++ )
    {
        cout << " starea ";
        for ( k = 0 ; DFA[i][nrl][k] != -1 ; k++ )
            cout<<DFA[i][nrl][k];
        cout << " este adiacenta prin";

        for ( j = 0; j < nrl ; j++ )
           {
            cout << "\n litera " << A[j] << " cu ";

            int ok = 0;

            for ( k = 0 ; DFA[i][j][k] != -1 ; k++ )
            ok = 1, cout << DFA[i][j][k];

            if ( ok == 0) cout << "nimic ";
       }
            cout << "\n\n";

    }

    cout<<"\n\n starile finale din AFD:\n\n ";

    for ( i = 0 ; i < nrs ; i++ )
    {
        for ( int j = 0 ; FIN[i][j] != -1 ; j++ )
        cout << FIN[i][j];

        if( i < nrs - 1 ) cout << ", ";
    }

    cout << endl << "_________________________________________" << endl;
}
