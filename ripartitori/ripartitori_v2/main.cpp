#include "letture.h"

#include <overkill/ovk_syslog.h>

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    OvkSyslog* sysl = OvkSyslog::initInstanceWithoutThread("Ripartitori_V2");
    sysl->initOnConsolle(OvkSyslog::SYSLOG_LEV_INFO);
    OVK_LOG_INFO("Welcome to Ripartitori V2");

    Letture lecture;

    bool ok = false;
    do {
        if (!lecture.loadTemplate("template_v2.csv")) { break; }
        lecture.printTemplate();
        if (!lecture.loadFromCsv("letture_v2.csv")) { break; }
//        cout << endl << "------------------------------------------" << endl;
//        lecture.printByName();
//        cout << endl << "------------------------------------------" << endl;
        lecture.calcolaScatti();
        lecture.saveCsvByName("calcoli.csv");
        lecture.saveCsvRipartitore("ripartitore.csv");
//        lecture.printTemplate();
//        lecture.printByName();
//        cout << endl << "------------------------------------------" << endl;

        ok = true;
    } while (0);

    if (!ok) {
        OVK_LOG_ERR("Errore");
    }

    return 0;
}
