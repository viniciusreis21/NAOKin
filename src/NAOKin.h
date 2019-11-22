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

  struct InterpolationValues //Struct that represents any moviments 
  {
    vector<string> names;
    vector<vector<float> > angles;
    vector<vector<float> > times;
  };

  map<string, InterpolationValues> m_interpolations; //Container of elements: key - value

  vector<pair<string, string> > m_motion_filenames; //Vector os pairs to populate map container

  void parseMotionFile(string filename, string key);

  void setAngles(int numJoints, double speed, ...);

  void interpolate(string key);

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