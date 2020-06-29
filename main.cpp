#include "src/NAOKin.h"
#include <iostream>
#include <alproxies/almotionproxy.h>
#include <qi/os.hpp>
#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <string>
using namespace std;
//using namespace cv;

int main(int argc, char const *argv[])
{
                 // Show our image inside it.
     
    NAOKin nao(string("127.0.0.1")); 

    nao.WakeUp(); //Wake up robot
    nao.GoToPosture("Stand");
    //nao.getKinematicsDirect(nao);
    nao.getKinematicsInverse();
    nao.GoToPosture("Crouch");
    nao.Rest();
   
    
    return 0;
}