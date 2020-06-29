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