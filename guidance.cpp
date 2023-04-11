#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;


#define nobs 5

int main(void)
{
    //// Define the artificial potential field parameters
    // Points of attraction
    int xa = 70;
    int ya = 50;

    int xo[nobs] = { 20,30,35,50,65 };
    int yo[nobs] = { 13,25,35,38,45 };
    
    // Size of obstacles (rho_0)
    int rho_0[nobs] = {7,3,6,4,4};

    // Constants.
    int Ka = 1; 
    int Kv = 50; 
    int Kr[nobs] = {500,250,400,300,300};
    int mass = 5;

    //// Integration step.
    // initial conditions
    float x0 = 5; 
    float y0 = 5;

    // Initialise simulation parameters
    float x = x0;
    float y = y0;
    float vx = 0;
    float vy = 0;
    bool terminate = false;
    float t = 0;
    float dt = 0.01;

    // Store variables for later assessment
    std::vector<std::vector<float> > traj;
    // std::vector<float>  traj = {};
    // float Fac = {}; 
    // float Frc = {}; 
    // float Fdc = {};
    // float Fc = {};
    
    while(!terminate){
        //// Check if reached destination
        float rho = sqrt(pow((xa-x),2)+pow((ya-y),2));

        if(rho < 0.1)
        {
            terminate = true;
        }
            
        
        //// Calculate the conservative forces
        // Attractive force (Fa)
        int Fa[2][1];
        Fa[0][0] = 0;
        Fa[1][0] = 0;

        Fa[0][0]=-Ka*(x-xa);
        Fa[1][0]=-Ka*(y-ya);

        // Fac = {Fac, Fa};
        // Repulsive force (Fr)
        int Fr[2][1];
        Fr[0][0] = 0;
        Fr[1][0] = 0;

        for(int i=0;i<5;i++){
            float rho_r = sqrt(pow((xo[i]-x),2)+pow((yo[i]-y),2));
            if(rho_r < rho_0[i]){
                Fr[0][0]=Fr[1][1]-Kr[i]*(rho_r-rho_0[i])*(x-xo[i])/rho_r;
                Fr[1][0]=Fr[2][1]-Kr[i]*(rho_r-rho_0[i])*(y-yo[i])/rho_r;
            }
        }

        // Frc = [Frc Fr];
        // Damping force (Fd)
        int Fd[2][1];
        Fd[0][0] = 0;
        Fd[1][0] = 0;

        Fd[0][0]=-Kv*vx;
        Fd[1][0]=-Kv*vy;

        // Fdc = [Fdc Fd];
        // Total force (F)

        int F[2][1];
        F[0][0]=Fa[0][0]+Fr[0][0]+Fd[0][0];
        F[1][0]=Fa[1][0]+Fr[1][0]+Fd[1][0];

        // Fc = [Fc F];
        // Velocity and Position (vx, vy, x, y) through integrating the equations

        vx=vx+dt*F[0][0]/mass;
        vy=vy+dt*F[1][0]/mass;
        x=x+vx*dt;
        y=y+vy*dt;
        t=t+dt;

        // traj = [traj [x;y]]; 
        std::vector<float> new_column = {x, y};
        if( traj.size() == 0){
          traj = {{x},{y}};
        }else{
          for (int i = 0; i < traj.size(); i++) {
            traj[i].push_back(new_column[i]);
          }
        }
    }

    std::cout << "traj:\n";
    for (const auto& row : traj) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
