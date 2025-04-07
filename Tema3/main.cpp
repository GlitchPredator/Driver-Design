#include <iostream>
#include <windows.h>

using namespace std;

int main(void)
{
    int N = 0;
    cout << "[#PROGRAM]: Introdu un numar. N = ";
    cin >> N;

    if (cin.fail() || N <= 0)
    {
        cerr << "[#PROGRAM]: Eroare la citirea numarului [N] !" << endl;
        exit(EXIT_FAILURE);
    }

    // Obtinem dimensiunea reala a unei pagini de memorie
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    SIZE_T pageSize = sysInfo.dwPageSize;
    cout << "[#PROGRAM]: Dimensiunea unei pagini de memorie este: " << pageSize << " bytes." << endl;

    // Calculam dimensiunea totala necesara (N pagini * dimensiunea unei pagini)
    SIZE_T totalSize = N * pageSize;

    // Alocare memorie cu VirtualAlloc
    void* allocatedMemory = VirtualAlloc(NULL, totalSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (allocatedMemory == NULL)
    {
        cerr << "[#PROGRAM]: Eroare la alocarea memoriei!" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "[#PROGRAM]: Memorie alocata cu succes la adresa: " << allocatedMemory << endl;

    // Eliberare memorie
    if (VirtualFree(allocatedMemory, 0, MEM_RELEASE))
    {
        cout << "[#PROGRAM]: Memorie eliberata cu succes." << endl;
    }
    else
    {
        cerr << "[#PROGRAM]: Eroare la eliberarea memoriei!" << endl;
    }
    return 0;
}