#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

vector<int> generateRandomVector(long long int size, long int max){
    vector<int> V(size, 0);

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(1, max); // define the range

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
bool check(vector<int> Vector, vector<int> V){
    vector<int> V2 = Vector;
    sort(V2.begin(), V2.end());
    for(int i=0; i<V2.size(); i++){
        if(V[i] != V2[i])
            return false;
    }
    return true;
}

void radixSort1(vector<int>&V){
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
}
void radixSort2(vector<int>&V){

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
}
void radixSort3(vector<int>&V){
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
    int pivot = Vector[(left+right)/2], j = left;
    swap(Vector[(left+right)/2], Vector[right]);

    for(int i=left; i<right; i++){
        if(Vector[i] <= pivot){
            swap(Vector[j++], Vector[i]);
        }
    }
    swap(Vector[j], Vector[right]);
    return j;
}
void quicksort(vector<int>& Vector, int left, int right){
    if (left<right){
        int index = part(Vector, left, right);

        quicksort(Vector, index+1, right);
        quicksort(Vector, left, index-1);
    }
}

int medianOf3(vector<int>& Vector, int left, int right) {
    int mid = (left + right) / 2;

    if (Vector[left] > Vector[mid])
        swap(Vector[left], Vector[mid]);

    if (Vector[mid] > Vector[right])
        swap(Vector[mid], Vector[right]);

    if (Vector[left] > Vector[right])
        swap(Vector[left], Vector[right]);


    swap(Vector[mid], Vector[right-1]);
    return Vector[right - 1];
}
int part2(vector<int>& Vector, int left, int right){
    int pivot = medianOf3(Vector, left, right);

    int i = left-1;
    for(int j=left;j<=right;j++) {
        if (Vector[j] <= pivot) {
            swap(Vector[i+1], Vector[j]);
            i += 1;
        }
    }


    return i;
}
void quicksort2(vector<int>& Vector, int left, int right){
    if (left<right){
        int index = part2(Vector, left, right);

        quicksort2(Vector, index+1, right);
        quicksort2(Vector, left, index-1);
    }
}

vector<int> countingsort(vector<int> Vector){
    int Max = *max_element(Vector.begin(), Vector.end());
    vector<int> freq;
    for(int i=0; i<=Max; i++){
        freq.push_back(0);
    }
    for(int i=0; i<Vector.size(); i++){
        freq[Vector[i]]++;
    }
    vector<int> newVector = {};
    for(int i=0; i<freq.size(); i++){
        while(freq[i] > 0){
            newVector.push_back(i);
            freq[i]-=1;
        }
    }
    return newVector;
}

void shellsort(vector<int>& V)
{
    int j, el, size = V.size();
    int dist = V.size()/2;
    while(dist > 0){
        for (int i = dist; i < size; i += 1)
        {
            el = V[i];
            for (j = i; j >= dist; j -= dist) {
                if(V[j-dist] <= el){
                    break;
                }
                V[j] = V[j - dist];
            }

            V[j] = el;
        }
        dist/=2;
    }
}

int main() {

    ifstream f("C:\\Users\\Patric\\CLionProjects\\untitled\\tests.in");
    int tests, n, m; f>>tests;
    vector<int> Vector, V;
    for(int i=0; i<tests; i++){
        f>>n;
        f>>m;
        cout<<endl<<"=================N: "<<n<<" "<<"M: "<<m<<"==================="<<endl;
        Vector = generateRandomVector(n, m);

        V = Vector;
        auto start1 = high_resolution_clock::now();
        radixSort3(V);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        cout << "Time radix sort baza 10: "<< duration1.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

        V = Vector;
        auto start2 = high_resolution_clock::now();
        radixSort2(V);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        cout << "Time radix sort baza 2^16: "<< duration2.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

        V = Vector;
        auto start3 = high_resolution_clock::now();
        radixSort1(V);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        cout << "Time radix sort baza 1000: "<< duration3.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

        V = Vector;
        auto start4 = high_resolution_clock::now();
        V = mergesort(V);
        auto stop4 = high_resolution_clock::now();
        auto duration4 = duration_cast<microseconds>(stop4 - start4);
        cout << "Time mergesort: "<< duration4.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

        if(n < 100000000 || m >= 100000) {
            V = Vector;
            auto start5 = high_resolution_clock::now();
            quicksort(V, 0, V.size() - 1);
            auto stop5 = high_resolution_clock::now();
            auto duration5 = duration_cast<microseconds>(stop5 - start5);
            cout << "Time quicksort cu pivot element random: " << duration5.count() << " microseconds" << endl;
            //        cout<<check(Vector, V)<<endl;

            V = Vector;
            auto start6 = high_resolution_clock::now();
            quicksort2(V, 0, V.size() - 1);
            auto stop6 = high_resolution_clock::now();
            auto duration6 = duration_cast<microseconds>(stop6 - start6);
            cout << "Time quicksort cu pivot din mediana de 3: " << duration6.count() << " microseconds" << endl;
//                    cout<<check(Vector, V)<<endl;
        }

        V = Vector;
        auto start7 = high_resolution_clock::now();
        V = countingsort(V);
        auto stop7 = high_resolution_clock::now();
        auto duration7 = duration_cast<microseconds>(stop7 - start7);
        cout << "Time countingsort: "<< duration7.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

        V = Vector;
        auto start8 = high_resolution_clock::now();
        shellsort(V);
        auto stop8 = high_resolution_clock::now();
        auto duration8 = duration_cast<microseconds>(stop8 - start8);
        cout << "Time shellsort: "<< duration8.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;
    }

    n = 1000;
    m = 1000;
    cout<<"====================N=100000, M=100000, sorted  vector ======================="<<endl;
    Vector = generateRandomVector(n, m);
//    sort(Vector.begin(), Vector.end());                                   // CRESCATOR SORTAT
    sort(Vector.begin(), Vector.end(), greater<int>());      // DESCRESCATOR SORTAT
    V = Vector;
    auto start1 = high_resolution_clock::now();
    radixSort3(V);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "Time radix sort baza 10: "<< duration1.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

    V = Vector;
    auto start2 = high_resolution_clock::now();
    radixSort2(V);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "Time radix sort baza 2^16: "<< duration2.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

    V = Vector;
    auto start3 = high_resolution_clock::now();
    radixSort1(V);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout << "Time radix sort baza 1000: "<< duration3.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

    V = Vector;
    auto start4 = high_resolution_clock::now();
    V = mergesort(V);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4);
    cout << "Time mergesort: "<< duration4.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

    if(n<50000000) {
        V = Vector;
        auto start5 = high_resolution_clock::now();
        quicksort(V, 0, V.size() - 1);
        auto stop5 = high_resolution_clock::now();
        auto duration5 = duration_cast<microseconds>(stop5 - start5);
        cout << "Time quicksort cu pivot element random: " << duration5.count() << " microseconds" << endl;
        //        cout<<check(Vector, V)<<endl;

        V = Vector;
        auto start6 = high_resolution_clock::now();
        quicksort2(V, 0, V.size() - 1);
        auto stop6 = high_resolution_clock::now();
        auto duration6 = duration_cast<microseconds>(stop6 - start6);
        cout << "Time quicksort cu pivot din mediana de 3: " << duration6.count() << " microseconds" << endl;
        //        cout<<check(Vector, V)<<endl;
    }

    V = Vector;
    auto start7 = high_resolution_clock::now();
    V = countingsort(V);
    auto stop7 = high_resolution_clock::now();
    auto duration7 = duration_cast<microseconds>(stop7 - start7);
    cout << "Time countingsort: "<< duration7.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

    V = Vector;
    auto start8 = high_resolution_clock::now();
    shellsort(V);
    auto stop8 = high_resolution_clock::now();
    auto duration8 = duration_cast<microseconds>(stop8 - start8);
    cout << "Time shellsort: "<< duration8.count() << " microseconds" << endl;
//        cout<<check(Vector, V)<<endl;

    return 0;
}