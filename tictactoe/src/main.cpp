#ifndef TESTING

#include <QApplication>
#include "Form.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Form form;
    form.show();
    
    return a.exec();
}
#endif

