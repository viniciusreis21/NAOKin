#ifndef _NAOKIN_H_
#define _NAOKIN_H_

#include <iostream>
#include <string>
#include <qi/os.hpp>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>

#include "src/external/Kofinas/NAOKinematics.h"
#include "src/external/Kofinas/KMat.hpp"
#include "src/Timer.h"
#include "src/external/Kofinas/robotConsts.h"

#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <stdarg.h>

#include<vector> 

using namespace std;
using boost::property_tree::ptree;
using namespace KMath::KMat;
using namespace KDeviceLists;



class NAOKin
{
private:
  AL::ALMotionProxy almotion;
  AL::ALRobotPostureProxy alposture;

public:
  NAOKin(string nao_ip);
  Timer timer;
  void WakeUp();
  void Rest();
  void GoToPosture(string);
  void DoTrajectory();
  void setJoints();
  void getPositionJoint(string);
  void setStiffnesses(string,bool);
};

#endif