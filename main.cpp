#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
typedef double typd;
typedef long long int typ;
using namespace std;

vector <typ> ContinuedFraction(int a,int b)
{
    vector <typ> continuedFraction;
    continuedFraction.push_back(0);
    int c;
    while(b != 0)
    {
        continuedFraction.push_back(a/b);
        c = a % b;
        a = b;
        b = c;
    }
    return continuedFraction;
}

int CheckDecryptionFactor(typ e, typd N, typ k, typ d)
{
    if(k > 0)
    {
        typd c = N;
        typ p, q, delta, b ;
        typ phiN = ((e*d - 1) / k );
        b = (N - phiN + 1);
        delta = (b*b) - (4*c);
        if(delta >= 0)
        {
            p = (b - sqrt(delta)) / 2;
            q = (b + sqrt(delta)) / 2;
            if(p * q == N)
            {
                return 1;
            }
        }
    }
    return 0;
}

int Redukt(vector <typ> continuedFraction, int length, typd N, typ e){
	int flaga=0;;
	typ * Pi = (typ*)malloc(continuedFraction.size()*sizeof(continuedFraction));
    typ * Qi = (typ*)malloc(continuedFraction.size()*sizeof(continuedFraction));
	for(int i=0; i<length ;i++)
    {
        switch(i)
        {
            case 0: Pi[i]=continuedFraction[i];
                    Qi[i]=1;
                    break;
            case 1:
                    Pi[i]=continuedFraction[i]*Pi[i-1]+1;
                    Qi[i]=continuedFraction[i];
                    break;
            default:
                    Pi[i]=continuedFraction[i]*Pi[i-1]+Pi[i-2];
                    Qi[i]=continuedFraction[i]*Qi[i-1]+Qi[i-2];
                    break;

        }
        typ k = Pi[i];
        typ d = Qi[i];
        cout << "Sprawdzam dla d=" << d << endl;
        flaga = CheckDecryptionFactor(e, N, k, d);
        if(flaga == 1)
        {
            cout << "Wspolczynnik deszyfrowania znaleziony!" << endl;
            cout << "---------------------------------------" << endl;
            return 1;
        }
        else
        {
            cout << "To nie jest wspolczynnik deszyfrowania" << endl;
            cout << "---------------------------------------" << endl;
        }
    }
}


int main()
{
    int i;
    typ N,e;
    cout << "Podaj N: ";
    cin >> N;
    cout << "Podaj e: ";
    cin >> e;
    vector <typ> continuedFraction;
	continuedFraction = ContinuedFraction(N, e);
	cout << "Ulamek lancuchowy: " << endl;
	for(i=0; i < continuedFraction.size(); i++)
    {
        cout << continuedFraction[i] << endl;
    }
    Redukt(continuedFraction, continuedFraction.size(), N, e);
    getch();
}
