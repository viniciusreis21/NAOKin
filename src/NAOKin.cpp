#include "NAOKin.h"
#include <assert.h>

using namespace std;
using namespace AL;
using boost::property_tree::ptree;

vector<float> joints(NUMOFJOINTS);
NAOKinematics nkin;  

NAOKinematics::kmatTable output1, output2, output3, output4, output5;

typedef pair<string, string> str_str_pair;

NAOKin::NAOKin(string nao_ip) : almotion(nao_ip), alposture(nao_ip)
{

}

void NAOKin::DoTrajectory()
{
	interpolate("standInit");
	timer.Wait(1000);
	interpolate("standZero");
	timer.Wait(1000);
}

void NAOKin::parseMotionFile(string filename, string key)
{
	ptree pt; //Creating a tree for the postures values

	try
	{
		boost::property_tree::read_json(filename, pt); //Read the posture file and associate it with the tree
	}
	catch (boost::exception &ex)
	{
		cout << "File " << filename << " could not be loaded." << endl;
	}

	InterpolationValues ip_values; //Local data for the posture

	BOOST_FOREACH (const ptree::value_type &element, pt.get_child("root")) //For in the tree looking for values
	{
		vector<float> angles_vector;
		vector<float> times_vector;

		BOOST_FOREACH (const ptree::value_type &ele, element.second.get_child("angles"))
		{
			angles_vector.push_back(ele.second.get<float>("")); //Getting angle values
		}
		BOOST_FOREACH (const ptree::value_type &ele, element.second.get_child("times"))
		{
			times_vector.push_back(ele.second.get<float>("")); //Gerring time values
		}

		ip_values.names.push_back(element.second.get<string>("name"));
		ip_values.angles.push_back(angles_vector);
		ip_values.times.push_back(times_vector);
	}
	m_interpolations[key] = ip_values; //Setting values to the key
}

void NAOKin::setAngles(int numJoints, double speed, ...)
{
    va_list args; //Lists of arguments optimized
    int list_length = 2 * numJoints; //Names and angles
    
	va_start(args, list_length);
    ALValue names, angles;

    for (int i = 0; i < numJoints; ++i)
    {
        names.arrayPush(va_arg(args, char *));
    }

    for (int i = numJoints; i < list_length; ++i)
    {
        angles.arrayPush(va_arg(args, double));
    }

    va_end(args);

    almotion.setAngles(names, angles, speed);
}


void NAOKin::interpolate(string key) //The key representes the posture to interpolate
{
	InterpolationValues iv = m_interpolations[key]; //Making a InterpolationValues object with a 
													//container of values for the key
	ALValue al_names,
		al_angles,
		al_times;

	unsigned size = iv.angles.size();
	for (unsigned i = 0; i < size; ++i)
	{
		al_names.arrayPush(iv.names[i]);
		al_angles.arrayPush(iv.angles[i]);
		al_times.arrayPush(iv.times[i]);
	}

	almotion.angleInterpolation(iv.names, al_angles, al_times, true);
}

void NAOKin::WakeUp()
{
	almotion.wakeUp();
}

void NAOKin::Rest()
{
	almotion.rest();
}

void NAOKin::GoToPosture(string posture)
{
	alposture.goToPosture(posture, 1.0f);
}

void NAOKin::setJoints()
{
	
	AL::ALValue nome1 = "RArm";
	AL::ALValue nome2 = "LArm";
	AL::ALValue nome3 = "LLeg";
	AL::ALValue nome4 = "RLeg";
	AL::ALValue nome5 = "Head";

	bool useSensors = true;
	std::vector<float> sensorAnglesRArm = almotion.getAngles(nome1, useSensors);
	std::vector<float> sensorAnglesLArm = almotion.getAngles(nome2, useSensors);
	std::vector<float> sensorAnglesLLeg = almotion.getAngles(nome3, useSensors);
	std::vector<float> sensorAnglesRLeg = almotion.getAngles(nome4, useSensors);
	std::vector<float> sensorAnglesHead = almotion.getAngles(nome5, useSensors);
	for(int i=0;i<5;i++)
	{
		joints[R_ARM+i]=sensorAnglesRArm[i]; //Right Hand
		joints[L_ARM+i]=sensorAnglesLArm[i]; //Left Hand
	}
	for(int i=0;i<6;i++)
	{
		joints[L_LEG+i]=sensorAnglesLLeg[i]; //Left Leg
		joints[R_LEG+i]=sensorAnglesRLeg[i]; //Right Leg
	}
	//Head
	joints[HEAD+YAW]=sensorAnglesHead[0];
	joints[HEAD+PITCH]=sensorAnglesHead[1];

	nkin.setJoints(joints);

	output1 = nkin.getForwardEffector((NAOKinematics::Effectors)CHAIN_L_ARM); // Left Hand
	output2 = nkin.getForwardEffector((NAOKinematics::Effectors)CHAIN_R_ARM); // Right Hand
	output3 = nkin.getForwardEffector((NAOKinematics::Effectors)CHAIN_L_LEG); // Left Leg
	output4 = nkin.getForwardEffector((NAOKinematics::Effectors)CHAIN_R_LEG); // Right Leg
	output5 = nkin.getForwardEffector(NAOKinematics::EFF_CAMERA_BOT); // Camera
}

void NAOKin::getPositionJoint(string joint)
{

	if(joint == "LArm")
	{
		std::cout << "x = " << output1(0,3) << " y = " << output1(1,3) << " z = " << output1(2,3) <<  std::endl;
	}
	else if(joint == "RArm")
	{
		std::cout << "x = " << output2(0,3) << " y = " << output2(1,3) << " z = " << output2(2,3) <<  std::endl;
	}
	else if(joint == "LLeg")
	{
		std::cout << "x = " << output3(0,3) << " y = " << output3(1,3) << " z = " << output3(2,3) <<  std::endl;
	}
	else if(joint == "RLeg")
	{
		std::cout << "x = " << output4(0,3) << " y = " << output4(1,3) << " z = " << output4(2,3) <<  std::endl;
	}
	else if(joint == "Camera")
	{
		std::cout << "x = " << output5(0,3) << " y = " << output5(1,3) << " z = " << output5(2,3) <<  std::endl;
	}
	else
	{
		std::cout<<"Invalid joint name"<<std::endl;
	}
}
void NAOKin::setStiffnesses(string nome,bool status)
{
	if(nome == "RArm")
	{
		if(status == 0)
		{
		  	almotion.setStiffnesses("RArm",0.0f);
		}
		else if(status == 1)
		{
			almotion.setStiffnesses("RArm",0.0f);
		}
	}
	else if(nome == "LArm")
	{
		if(status == 0)
		{
		  	almotion.setStiffnesses("LArm",0.0f);
		}
		else if(status == 1)
		{
			almotion.setStiffnesses("LArm",1.0f);
		}
	}
	else
	{
		std::cout<<"Joint invalid"<<std::endl;
	}
}