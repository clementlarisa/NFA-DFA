#ifndef AUTOMAT_H
#define AUTOMAT_H

class AUTOMAT
{
public:
    //ctor si dtor

    AUTOMAT() {}
    virtual ~AUTOMAT() {}


    // variabile

    int nrs_AFN;         // nr stari AFN
    int starei;          // starea de pornire
    int nrt;             // nr tranzitii AFN
    int s1, s2;          // stare1, stare2 din tranzitie
    char l;              // litera de trecere
    int nrl;             // nr litere din alfabet
    int nrf_AFN;         // nr stari finale AFN
    int nrs_add;         // nr stari adaugate
    int nrs;             //
    int F[25];           // stari finale AFN
    int FIN[25][25];         // stari finale AFD
    char A[10];          // alfabetul
    int NFA[25][25][25]; // matrice AFN
    int DFA[25][25][25]; // matrice AFD

    //metode

    void BuildNFA();
    void PrintNFA();
    bool CheckState(int*);
    void SortnDelete(int*, int);
    void AddState(int*);
    void BuildDFA();
    void PrintDFA();
};

#endif // AUTOMAT_H
