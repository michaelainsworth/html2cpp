#include <iostream>
#include <dlfcn.h>
using std::cout;
using std::cerr;

int main(int argc, const char** argv)
{
    void* handle = dlopen("03a-shared-library.so", RTLD_LAZY);
    if (!handle)
    {
        cerr << "Could not open library!\n";
        cerr << dlerror();
        return 1;
    }

    typedef void (*fnptr)();
    fnptr func = 0;
    func = (fnptr)dlsym(handle, "myfunc");
    if (!func)
    {
        cerr << "Could not obtain function!\n";
        cerr << dlerror();
        return 1;
    }

    func();

    return 0;
}
