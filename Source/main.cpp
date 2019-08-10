/* 
    *** READ THIS NOTICE *** READ THIS NOTICE *** READ THIS NOTICE ***

    This code is not "c++" code at the moment, more like C with bits of C++, this is temporary.
    it's only designed to show a proof of concept for the pre-production process.

    Once the pre-production stage is completed...
    ... I'll go about refactering the c++ code to be more in line with real c++.
*/

#include "Application.hpp"

int main(int argc, char* argv[])
{
    Application application(argc, argv);
    return application.Run();
}