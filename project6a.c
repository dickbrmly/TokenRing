/*******************************************************************************
//  Richard Bromley 5001075854
//  CS 370 1001 Assignment 6
//
//  Token Ring (Dijkstra's Algorithm) Network
//
//
//  Location of file: Assignment6
/******************************************************************************/
#include "project6a.h"    
/*******************************************************************************
*******************************************************************************/
int main () {

    int id,nodeCount,leftNeighbor,rightNeighbor;
	scanf("%d",&id);
	scanf("%d",&nodeCount);
	
    int x = 0;
    int processValue = (rand() % nodeCount);
    int neighborValue;
    char socketName[7];
 
    if(id == 0) {
        sprintf(socketName,"socket%d",(nodeCount - 1));
        rightNeighbor = createServerConnection(socketName);
        leftNeighbor = createServerConnection("socket0");
    }
    else if (id == (nodeCount - 1)) {
        sprintf(socketName,"socket%d",id);
        leftNeighbor = createClientConnection(socketName);
        sprintf(socketName,"socket%d",(id - 1));
        rightNeighbor = createClientConnection(socketName);
    }
    else {
        sprintf(socketName,"socket%d",id);
        leftNeighbor = createServerConnection(socketName);
        sprintf(socketName,"socket%d",(id - 1));
        rightNeighbor = createClientConnection(socketName);
    }
    
    while (x < 1000) {

        sendMessage(leftNeighbor,processValue);
        neighborValue = recieveMessage(rightNeighbor);

        
       switch (id) {
           case 0:
        		if (processValue == neighborValue ) {
                    printf("##############################\n  In Critial Section");
                    printf("\n##############################\n");
                    processValue = ((processValue + 1) % nodeCount);
                    sleep(1);
        		}
        		else system("clear");
			break;
    
	       default:
        		if (processValue != neighborValue) {
                    printf("##############################\n  In Critial Section");
                    printf("\n##############################\n");
                    processValue = neighborValue;
                    sleep(1);
        		}
        		else system("clear");
			break;
       }
        ++x;
    }	
    return 0;
}
/*******************************************************************************
*******************************************************************************/
