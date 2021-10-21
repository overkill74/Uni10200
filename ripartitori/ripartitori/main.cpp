#include "letture.h"

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    Letture lecture;

    bool ok = false;
    do {
        if (!lecture.loadFromCsv("letture.csv")) { break; }
        if (!lecture.loadTemplate("template.csv")) { break; }
//        cout << endl << "------------------------------------------" << endl;
//        lecture.printByName();
//        cout << endl << "------------------------------------------" << endl;
        lecture.calcolaScatti();
        lecture.printTemplate();
//        cout << endl << "------------------------------------------" << endl;

        ok = true;
    } while (0);

    if (!ok) {
        cout << "Errore" << endl;
    }

    return 0;
}
