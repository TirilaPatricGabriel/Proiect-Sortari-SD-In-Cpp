#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

vector<int> generateRandomVector(int size){
    vector<int> V(size, 0);
    long long int min = 100000;
    long long int max = 1000000000;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    for(int i=0; i<V.size(); i++){
        V[i] = distr(gen);
    }

    return V;
}
void afisareVector(vector<int> V){
    cout<<endl;
    for(int i=0; i<V.size(); i++){
        cout<<V[i]<<" ";
    }
    cout<<endl;
}
bool check(vector<int> V){
    vector<int> V2 = V;
    sort(V2.begin(), V2.end());
    for(int i=0; i<V2.size(); i++){
        if(V[i] != V2[i])
            return false;
    }
    return true;
}

vector<int> radixSort1(vector<int> V){
    vector<vector<int>> bins(1000);
    long i = 1;
    int n;
    int ok = 1;
    while(ok){
        ok = 0;
        for(int j=0; j<1000; j++){
            bins[j] = {};
        }
        for(int j=0; j<V.size(); j++){
            if ((V[j]/i) > 999) {
                ok = 1;
            }
            n = (V[j]/i) % 1000;
            bins[n].push_back(V[j]);
        }
        V.clear();

        for(int j=0; j<bins.size(); j++){
            for(int k=0; k<bins[j].size(); k++){
                V.push_back(bins[j][k]);
            }
        }
        i*=1000;
    }
    return V;
}
vector<int> radixSort2(vector<int>V){

    int nBins = 1;
    for(int i=0; i<16; i++){
        nBins*=2;
    }

    vector<vector<int>> bins(nBins);
    long i = 0;
    int n;
    int ok = 1;
    while(ok){
        ok = 0;
        for(int j=0; j<nBins; j++){
            bins[j] = {};
        }
        for(int j=0; j<V.size(); j++){
            if ((V[j]>>i) > nBins-1) {
                ok = 1;
            }
            n = (V[j]>>i) % nBins;
            bins[n].push_back(V[j]);
        }
        V.clear();

        for(int j=0; j<bins.size(); j++){
            for(int k=0; k<bins[j].size(); k++){
                V.push_back(bins[j][k]);
            }
        }
        i+=16;
    }
    return V;
}
vector<int> radixSort3(vector<int>V){
    vector<vector<int>> bins(10);
    long i = 1;
    int n;
    int ok = 1;
    while(ok){
        ok = 0;
        for(int j=0; j<10; j++){
            bins[j] = {};
        }
        for(int j=0; j<V.size(); j++){
            if ((V[j]/i) > 9) {
                ok = 1;
            }
            n = (V[j]/i) % 10;
            bins[n].push_back(V[j]);
        }
        V.clear();
        for(int j=0; j<bins.size(); j++){
            for(int k=0; k<bins[j].size(); k++){
                V.push_back(bins[j][k]);
            }
        }
        i*=10;
    }
    return V;
}

vector<int> merge(vector<int> left, vector<int> right){
    int li = 0, ri = 0;
    vector<int> V = {};

    while(left.size() > li && right.size() > ri){
        if(left[li] < right[ri]){
            V.push_back(left[li]);
            li++;
        } else {
            V.push_back(right[ri]);
            ri++;
        }
    }

    for(int i=li; i<left.size(); i++){
        V.push_back(left[i]);
    }
    for(int i=ri; i<right.size(); i++){
        V.push_back(right[i]);
    }
    return V;
}

vector<int> mergesort(vector<int> Vector){
    if(Vector.size() == 1){
        return Vector;
    }
    int mid = Vector.size()/2;
    vector<int> left, right;
    left = {};
    right = {};
    for(int i=0; i<Vector.size()/2; i++){
        left.push_back(Vector[i]);
    }
    for(int i=Vector.size()/2; i<Vector.size(); i++){
        right.push_back(Vector[i]);
    }

    return merge(mergesort(left), mergesort(right));
}

void swap(vector<int>& V, int i, int j){
    int aux = V[i];
    V[i] = V[j];
    V[j] = aux;
}

int part(vector<int>& Vector, int left, int right){
    int pivot = Vector[right], j = left;
    for(int i=left; i<right; i++){
        if(Vector[i] <= pivot){
            swap(Vector, j, i);
            j+=1;
        }
    }
    swap(Vector, j, right);
    return j;
}
vector<int> quicksort(vector<int>& Vector, int left, int right){
    if (left<right){
        int index = part(Vector, left, right);

        quicksort(Vector, index+1, right);
        quicksort(Vector, left, index-1);
    }
    return Vector;
}

int main() {
    vector<int> v;
    int size;
    cout<<"Size of vector: "; cin>>size;

    vector<int> V = generateRandomVector(size);
    V = radixSort3(V);
    cout<<endl<<check(V)<<endl;
//    afisareVector(V);


    V = generateRandomVector(size);
    V = radixSort2(V);
    cout<<endl<<check(V)<<endl;
//    afisareVector(V);


    V = generateRandomVector(size);
    V = radixSort1(V);
    cout<<endl<<check(V)<<endl;
//    afisareVector(V);


    V = generateRandomVector(size);
    V = mergesort(V);
    cout<<endl<<check(V)<<endl;
//    afisareVector(V);

    V = generateRandomVector(size);
    V = quicksort(V, 0, V.size()-1);
    cout<<endl<<check(V)<<endl;
//    afisareVector(V);
    return 0;
}