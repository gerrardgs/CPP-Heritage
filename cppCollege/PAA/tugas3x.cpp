#include <iostream>
using namespace std;

int binary_search(int arr[], int n, int key){
    int low = 0, high = n - 1, mid = 0; // index awal, akhir, dan tengah array

    while(low <= high){
    mid = (high + low) / 2;

    if(arr[mid] < key){
        low = mid + 1; // seblah kanan array
    }else if(arr[mid] > key){
        high = mid - 1; // seblah kiri array
    }else{
        return mid;
    }
    }
    return -1;
}

int main(){
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 30;
    int result = binary_search(arr, n, key);
    if(result != -1)
        cout << "Berhasil: " << result << endl;
    else
        cout << "Tidak berhasil" << endl;
    return 0;
}
