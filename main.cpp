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
    nao.GoToPosture("StandInit");
    int op;
    int stif;
    cout<< "Para setar stiffnesses da RArm = 1, para LArm =2, para sair = 0"<< endl;
    cin >> op;
    while(op!=0)
    {
        if(op !=0 && op!=1 && op!=2)
        {
            cout<< "Opcao invalida"<<endl;
        }
        else if(op==1)
        {
            cout<< "Opcao selecionada= RArm"<<endl;
            nao.setStiffnesses("RArm",0);
            cout<<"Ja movimentou para a posicao desejada? 1= Sim"<<endl;
            cin >> stif;
            if(stif == 1)
            {
                nao.WakeUp();
                nao.setJoints();
                nao.getPositionJoint("RArm");
            }            
        }
        else if(op==2)
        {
            cout<< "Opcao selecionada= LArm"<<endl;
            nao.setStiffnesses("LArm",0);
            cout<<"Ja movimentou para a posicao desejada? 1= Sim"<<endl;
            cin >> stif;
            if(stif == 1)
            {
                nao.WakeUp();
                nao.setJoints();
                nao.getPositionJoint("LArm");
            }   
        }
        cout<< "Para setar stiffnesses da RArm = 1, para LArm =2,para sair = 0"<< endl;
        cin >> op;
    }
    //nao.setJoints();
    //nao.getPositionJoint("RArm");
    //nao.DoTrajectory();
    //nao.timer.Wait(2000);
    nao.GoToPosture("Crouch");
    nao.Rest();
    return 0;
}