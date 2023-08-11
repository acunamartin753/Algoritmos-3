#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct actividad {
    actividad(): s(0), t(0), indice(0) {}
    int s;
    int t;
    int indice;
};

void bucketSort(vector<actividad> &actividades,int cota){
    vector<list<actividad>> buckets(cota);
    for (actividad a : actividades){
        buckets[a.t].push_back(a);
    }
    int i=0;
    for (int j=0;j<cota;j++){
        for(actividad k : buckets[j]){
            actividades[i]=k;
            i++;
        }
    }
}

void imprimir(list<int> S){
    cout << S.size() << '\n';
    for (int x : S){
        cout << x << " ";
    }
}

int main() {
    int n;
    cin >> n;
    vector<actividad> actividades(n);

    for(int i=0;i<n;i++){
        cin >> actividades[i].s >> actividades[i].t;
        actividades[i].indice=i+1;
    }

    bucketSort(actividades,2*n+1);

    list<int> S;
    int ultima = 0;
    for(actividad a : actividades){
        if(a.s>=ultima){
            S.push_back(a.indice);
            ultima=a.t;
        }
    }

    imprimir(S);
    return 0;
}
