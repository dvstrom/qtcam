#ifndef COMMTHREAD_H
#define COMMTHREAD_H

#include <QThread>

class commThread : public QThread
{
    Q_OBJECT
public:
    commThread();
    char buf[128];

      volatile bool stopped;

      volatile bool write_rs;

      volatile bool read_rs;

      protected:

      virtual void run();
};

#endif // COMMTHREAD_H
