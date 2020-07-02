#ifndef ACTIVEMQ_THREAD_TASK_FACTORY_H
#define ACTIVEMQ_THREAD_TASK_FACTORY_H

#include <decaf/lang/Runnable.h>
#include <string>

class ActivemqThreadTaskFactory : public decaf::lang::Runnable 
{
private:
    ActivemqThreadTaskFactory(const ActivemqThreadTaskFactory&);
    ActivemqThreadTaskFactory& operator= (const ActivemqThreadTaskFactory&);

public:
    ActivemqThreadTaskFactory();

    virtual ~ActivemqThreadTaskFactory();

    virtual void run();

    virtual void SetStop(){}
};

#endif	//	ACTIVEMQ_THREAD_TASK_FACTORY_H