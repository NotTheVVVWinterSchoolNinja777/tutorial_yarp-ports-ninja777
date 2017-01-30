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

    // open the outut port
    BufferedPort<Bottle> outPort;
    if (!outPort.open("/relay/out")) {
        yError() << "cannot open the output port";
        return -1;
    }

    int counter = 0;
    while (true) {
        counter++;

        yInfo()<<" waiting for input...";
        Bottle* input = inPort.read();
        if(input == NULL) {
            yError()<<"error reading port";
            return 0;
        }

        Bottle& output = outPort.prepare();
        output = *input;
        output.addString("hello yarp");
        output.addInt(counter);
        // write the output data
        yInfo()<< "writing data ...";
        outPort.write();

    }
    return 0;
}
