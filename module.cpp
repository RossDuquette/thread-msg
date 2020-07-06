#include <assert.h>
#include <signal.h>

#include "module.h"

static void* module_start(void* module)
{
    reinterpret_cast<Module*>(module)->main();
    return NULL;
}

bool Module::module_running[MAX_NUM_MODULES] = { false };

Module::Module(int id) :
    msgr(id)
{
    assert(module_running[id] == false);
    module_running[id] = true;
}

Module::~Module()
{
}

void Module::start()
{
    pthread_create(&thread, NULL, module_start, this);
}
