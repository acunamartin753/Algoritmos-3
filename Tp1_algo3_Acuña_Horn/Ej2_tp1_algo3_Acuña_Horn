#include <iostream>
#include <vector>

using namespace std;

const int ind = -1;
vector<vector<int>> M;
vector<int> v;
int m;
int n;
int R;

using namespace std;

long long modex(long long x, long long y ,long long z){
    if (y==0){
        return 1;
    }else if((y%2)==0){
        long long aux = modex(x,y/2,z);
        return (aux * aux)%z;
    }else{
        long long aux = modex(x,y/2,z);
        return (((aux*aux)%z)*x)%z;
    }
}

int suma(int a, int b){
    return (a+b) % m;
}

int resta(int a, int b){
    int aux = (a-b) % m;
    if (aux<0){
        aux += m;
    }
    return aux;
}

int producto(int a, int b){
    long long x = a;
    long long y = b;
    long long aux = (x * y);
    aux = aux % m;
    return int(aux);
}

int potencia(int a, int b){
    long long x = a;
    long long y = b;
    long long z = m;
    long long res = modex(x,y,z);
    return int(res);
}

int existe(int i, int r){
    if(i==n){
        return r==R;
    }
    if(M[i][r]==ind){
        bool res=false;

        res = res || existe(i+1, suma(r, v[i]));
        res = res || existe(i+1, resta(r, v[i]));
        res = res || existe(i+1, producto(r, v[i]));
        res = res || existe(i+1, potencia(r,v[i]));

        M[i][r] = res;
    }
    return M[i][r];
}

int main() {
    int c;
    cin >> c;
    for(int i=0;i<c;i++){
        cin >> n >> R >> m;
        v.resize(n,ind);
        for(int j=0;j<n;j++){
            cin >> v[j];
            v[j] = v[j] % m;
        }
        M.resize(n, vector<int> (m,ind));
        if(existe(1 ,v[0])){
            cout << "Si" << '\n';
        }else{
            cout << "No" << '\n';
        }
        v.clear();
        M.clear();
    }
    return 0;
}
