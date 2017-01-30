#include <yarp/os/Network.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Port.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Time.h>

//#include <yarp/os/all.h>

using namespace std;
using namespace yarp::os;

int main(int argc, const char **argv) {

    // initialize yarp network
    Network yarp;

    // open the outut port "/relay/out"
    Port outPort;
    if (!outPort.open("/relay/out")) {
        yError() << "cannot open the output port";
        return -1;
    }

    // open the outut port "/relay/in"
    Port inPort;
    if (!inPort.open("/relay/in")) {
        yError() << "cannot open the input port";
        return -1;
    }

    int counter = 0;
    while (true) {
        counter++;

        Bottle input;
        if(!inPort.read(input)) {
            yError()<<"erro while reading";
            return 0;
        }

        // prepare the output data
        Bottle output;
        output = input;
        output.addString("Hello yarp!");
        output.addInt(counter);

        // write the output data
        yInfo()<< "writing data ...";
        outPort.write(output);

        // wait for a second
        //Time::delay(1.0);
    }
    return 0;
}
