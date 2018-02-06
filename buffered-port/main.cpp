#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/LogStream.h>

#include <yarp/os/all.h>

using namespace std;
using namespace yarp::os;

int main(int argc, const char **argv) {
    
    // initialize yarp network
    Network yarp;

    
    BufferedPort<Bottle> inPort;
    if (!inPort.open("/relay/in")) {
        yError() << "cannot open the input port";
        return -1;
    }

    BufferedPort<Bottle> outPort;
    // open the output port
    if(!outPort.open("/relay/out")){
        yError() << "cannot open the output port";
        return -1;
    }

    int counter = 0;
    while (true) {
        counter++;

        yInfo()<<" waiting for input...";
        // read from input port
        Bottle *input = inPort.read();
        if(input == NULL){
            yError() << "cannot read from input port";
            return -1;
        }

        Bottle &output = outPort.prepare();
        output = *input;

        // prepare the output data 
         output.addInt(counter);
         output.addString("hello from relay");
        // ...

        // write the output data
        yInfo()<< "writing data ...";
        outPort.write();

    }
    return 0;
}

