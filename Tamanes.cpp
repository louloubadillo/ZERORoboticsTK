//--------------------------------BEGINING OF PROGRAM--------------------------------

//---------------------BEGINING FUNCTIONS---------------------
//-------BASES------
//Begin at_base
void at_Base(){
    game.atBaseStation();
    game.getNumSamplesHeld();
        if (game.atBaseStation()==true){
            game.dropSample(0);
            game.dropSample(1);
            game.dropSample(2);
        }
        if(game.getNumSamplesHeld() == 0){
            step++;
        }
}
//End at_base

//BEGINING BLUE
//Begin Go to Base L
void goto_BaseL(){
    api.getMyZRState(myState);
        for (int l=0; l<3; l++){
            myPos[l]=myState[l];
        }
        mathVecSubtract(vectorBetween,basePosL,myPos,3);
        distance = mathVecMagnitude(vectorBetween,3);
        if (distance > 0.01){
            api.setPositionTarget(basePosL);
        }
        else if (distance <= 0.01) {
            api.setAttRateTarget(stop);
            step++;
        }
}
//End Go to Base L

//Begin page Go to Base R
void goto_BaseR(){
    api.getMyZRState(myState);
        for (int l=0; l<3; l++){
            myPos[l]=myState[l];
        }
        mathVecSubtract(vectorBetween,basePosR,myPos,3);
        distance = mathVecMagnitude(vectorBetween,3);
        if (distance > 0.01){
            api.setPositionTarget(basePosR);
        }
        else if (distance <= 0.01) {
            api.setAttRateTarget(stop);
            step++;
        }
}
//End Go to Base R
//END BLUE

//BEGINING RED
//Begin Go to Base L2
void goto_BaseL2(){
    api.getMyZRState(myState);
        for (int l=0; l<3; l++){
            myPos[l]=myState[l];
        }
        mathVecSubtract(vectorBetween,basePosL2,myPos,3);
        distance = mathVecMagnitude(vectorBetween,3);
        if (distance > 0.01){
            api.setPositionTarget(basePosL2);
        }
        else if (distance <= 0.01) {
            api.setAttRateTarget(stop);
            step++;
        }
}
//End Go to Base L2

//Begin page Go to Base R2
void goto_BaseR2(){
    api.getMyZRState(myState);
        for (int l=0; l<3; l++){
            myPos[l]=myState[l];
        }
        mathVecSubtract(vectorBetween,basePosR2,myPos,3);
        distance = mathVecMagnitude(vectorBetween,3);
        if (distance > 0.01){
            api.setPositionTarget(basePosR2);
        }
        else if (distance <= 0.01) {
            api.setAttRateTarget(stop);
            step++;
        }
}
//End Go to Base R2
//END RED
//-------END BASES------


//>>>>>-------------Begin BLUE------------<<<<<
//-------Positions------
//Begin PosA
void get_posA(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] < posA[0]) && (myState[1] < posA[1])) {
            mathVecSubtract(vectorBetween,posA,myPos,3);
        	distance = mathVecMagnitude(vectorBetween,3);
        	if (distance > 0.15){
        	   // api.setForces(vectorBetween);
        	   api.setVelocityTarget(vectorBetween);
        	}
        	else {
        	    api.setPositionTarget(posA);
        	}
        }
        else {
            step++;
        }
}
//End PosA

//Begin  PosC
void get_posC(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] < posC[0]) && (myState[1] < posC[1])) {
            mathVecSubtract(vectorBetween,posC,myPos,3);
            distance = mathVecMagnitude(vectorBetween,3);
            if (distance > 0.15){
               // api.setForces(vectorBetween);
               api.setVelocityTarget(vectorBetween);
            }
            else {
                api.setPositionTarget(posC);
                api.setAttRateTarget(stop);

            }
        }
        /*else if ((myState[0] > posA[0]) && (myState[1] > posA[1])){
            api.setPositionTarget(posA);
        }*/
        else {
            step++;
        }
}
//End PosC

//Begin PosB
void get_posB(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] > posB[0]) && (myState[1] < posB[1])) {
            mathVecSubtract(vectorBetween,posB,myPos,3);
            distance = mathVecMagnitude(vectorBetween,3);
            if (distance > 0.3){
                api.setVelocityTarget(vectorBetween);
            }
            else {
                api.setPositionTarget(posB);
                api.setAttRateTarget(stop);

            }
        }
        else {
            step++;
        }
        DEBUG(("distance = %f", distance));
}
//End PosB

//Begin Pos D
void get_posD(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] > posD[0]) && (myState[1] > posD[1])) {
            mathVecSubtract(vectorBetween,posD,myPos,3);
            distance = mathVecMagnitude(vectorBetween,3);
            if (distance > 0.15){
                api.setForces(vectorBetween);
            }
            else {
                api.setPositionTarget(posD);
            }
        }
       else {
            step++;
        }
}
//End PosD
//-------End Positions------

//-------Drilling------
//Begin Drill A
void start_DrillingA(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    api.setPositionTarget(posA);
    if (game.getDrills(myState) <= 0){
        game.getDrillEnabled();
    }
    if (myState[11] >= stop[2]){
        game.startDrill();
        api.setAttRateTarget(rateTarget);
        game.checkSample();
    }
    if (game.checkSample()==true){
        game.pickupSample();
        game.getNumSamplesHeld();
    }
    if (game.getNumSamplesHeld() == 2){
        api.setAttRateTarget(stop);
    }
    if ((myState[11] <= 0.1) && (game.getNumSamplesHeld() == 2)){
        game.stopDrill();
        step++;
    }
}
//End Drill A

//Begin Drill B
void start_DrillingB(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    api.setPositionTarget(posB);
    if (game.getDrills(myState) <= 0){
        game.getDrillEnabled();
    }
    if (myState[11] >= stop[2]){
        game.startDrill();
        api.setAttRateTarget(rateTarget);
        game.checkSample();
    }
    if (game.checkSample()==true){
        game.pickupSample();
        game.getNumSamplesHeld();
    }
    if (game.getNumSamplesHeld() == 2){
        api.setAttRateTarget(stop);
    }
    if ((myState[11] <= 0.1) && (game.getNumSamplesHeld() == 2)){
        game.stopDrill();
        step++;
    }
}
//End Drill B

//Begin Drilling C
void start_DrillingC(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    api.setPositionTarget(posC);
    if (game.getDrills(myState) <= 0){
        game.getDrillEnabled();
    }
    if (myState[11] >= stop[2]){
        game.startDrill();
        api.setAttRateTarget(rateTarget);
        game.checkSample();
    }
    if (game.checkSample()==true){
        game.pickupSample();
        game.getNumSamplesHeld();
    }
    if (game.getNumSamplesHeld() == 3){
        api.setAttRateTarget(stop);
    }
    if ((myState[11] <= 0.1) && (game.getNumSamplesHeld() == 3)){
        game.stopDrill();
        step++;
    }
}
//End Drilling pos C

//Begin Drill D
void start_DrillingD(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    game.getDrillError();
    api.setPositionTarget(posD);
    if (game.getDrillError() == false){
        if (game.getDrills(myState) <= 0){
            game.getDrillEnabled();
        }
        if ((myState[11] >= stop[2])||(myState[11] <= stop[2])){
            game.startDrill();
            api.setAttRateTarget(rateTarget);
            game.checkSample();
        }
        if (game.checkSample()==true){
            game.pickupSample();
            game.getNumSamplesHeld();
        }
        if (game.getNumSamplesHeld() == 2){
            api.setAttRateTarget(stop);
        }
        if ((myState[11] <= stop[2]) && (game.getNumSamplesHeld() == 2)){
            game.stopDrill();
            step++;
        }
    }
    else {
        game.stopDrill();
    }
}
//End Drill D

//-------End Drilling------
//>>>>>-------------END BLUE------------<<<<<


//>>>>>-------------Begin RED------------<<<<<
//-------Positions------
//Begin PosA
void get_posA2(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] > posA2[0]) && (myState[1] > posA2[1])) {
            mathVecSubtract(vectorBetween,posA2,myPos,3);
            distance = mathVecMagnitude(vectorBetween,3);
            if (distance > 0.15){
               // api.setForces(vectorBetween);
               api.setVelocityTarget(vectorBetween);
            }
            else {
                api.setPositionTarget(posA2);
            }
        }
        else {
            step++;
        }
}
//End PosA

//Begin PosB
void get_posB2(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] < posB2[0]) && (myState[1] > posB2[1])) {
            mathVecSubtract(vectorBetween,posB2,myPos,3);
            distance = mathVecMagnitude(vectorBetween,3);
            if (distance > 0.3){
                api.setVelocityTarget(vectorBetween);
            }
            else {
                api.setPositionTarget(posB2);
                api.setAttRateTarget(stop);

            }
        }
        else {
            step++;
        }
        DEBUG(("distance = %f", distance));
}
//End Pos B2

//Begin  Go pos C
void get_posC2(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] > posC2[0]) && (myState[1] > posC2[1])) {
            mathVecSubtract(vectorBetween,posC2,myPos,3);
            distance = mathVecMagnitude(vectorBetween,3);
            if (distance > 0.15){
               // api.setForces(vectorBetween);
               api.setVelocityTarget(vectorBetween);
            }
            else {
                api.setPositionTarget(posC2);
                api.setAttRateTarget(stop);

            }
        }
        /*else if ((myState[0] > posA[0]) && (myState[1] > posA[1])){
            api.setPositionTarget(posA);
        }*/
        else {
            step++;
        }
}
//End Go pos C

//Begin Pos D2
void get_posD2(){
    api.getMyZRState(myState);
        for (int i=0; i<3; i++){
            myPos[i]=myState[i];
        }
        if ((myState[0] > posD2[0]) && (myState[1] > posD2[1])) {
            mathVecSubtract(vectorBetween,posD2,myPos,3);
            distance = mathVecMagnitude(vectorBetween,3);
            if (distance > 0.15){
                api.setForces(vectorBetween);
            }
            else {
                api.setPositionTarget(posD2);
            }
        }
       else {
            step++;
        }
}
//End Pos D2
//-------End Positions------

//-------Drilling------
//Begin Drill A2
void start_DrillingA2(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    api.setPositionTarget(posA2);
    if (game.getDrills(myState) <= 0){
        game.getDrillEnabled();
    }
    if (myState[11] >= stop[2]){
        game.startDrill();
        api.setAttRateTarget(rateTarget);
        game.checkSample();
    }
    if (game.checkSample()==true){
        game.pickupSample();
        game.getNumSamplesHeld();
    }
    if (game.getNumSamplesHeld() == 2){
        api.setAttRateTarget(stop);
    }
    if ((myState[11] <= 0.1) && (game.getNumSamplesHeld() == 2)){
        game.stopDrill();
        step++;
    }
}
//End Drill A2

//Begin Drill B2
void start_DrillingB2(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    api.setPositionTarget(posB2);
    if (game.getDrills(myState) <= 0){
        game.getDrillEnabled();
    }
    if (myState[11] >= stop[2]){
        game.startDrill();
        api.setAttRateTarget(rateTarget);
        game.checkSample();
    }
    if (game.checkSample()==true){
        game.pickupSample();
        game.getNumSamplesHeld();
    }
    if (game.getNumSamplesHeld() == 2){
        api.setAttRateTarget(stop);
    }
    if ((myState[11] <= 0.1) && (game.getNumSamplesHeld() == 2)){
        game.stopDrill();
        step++;
    }
}
//End Drill B2

//Begin Drilling C2
void start_DrillingC2(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    api.setPositionTarget(posC2);
    if (game.getDrills(myState) <= 0){
        game.getDrillEnabled();
    }
    if (myState[11] >= stop[2]){
        game.startDrill();
        api.setAttRateTarget(rateTarget);
        game.checkSample();
    }
    if (game.checkSample()==true){
        game.pickupSample();
        game.getNumSamplesHeld();
    }
    if (game.getNumSamplesHeld() == 3){
        api.setAttRateTarget(stop);
    }
    if ((myState[11] <= 0.1) && (game.getNumSamplesHeld() == 3)){
        game.stopDrill();
        step++;
    }
}
//End Drilling pos C2

//Begin Drill D2
void start_DrillingD2(){
    api.getMyZRState(myState);
    game.getDrills(myState);
    game.getDrillError();
    api.setPositionTarget(posD2);
    if (game.getDrillError() == false){
        if (game.getDrills(myState) <= 0){
            game.getDrillEnabled();
        }
        if ((myState[11] >= stop[2])||(myState[11] <= stop[2])){
            game.startDrill();
            api.setAttRateTarget(rateTarget);
            game.checkSample();
        }
        if (game.checkSample()==true){
            game.pickupSample();
            game.getNumSamplesHeld();
        }
        if (game.getNumSamplesHeld() == 2){
            api.setAttRateTarget(stop);
        }
        if ((myState[11] <= stop[2]) && (game.getNumSamplesHeld() == 2)){
            game.stopDrill();
            step++;
        }
    }
    else {
        game.stopDrill();
    }
}
//End Drill D2
//-------End Drilling------
//>>>>>-------------END RED------------<<<<<

//---------------------END FUNCTIONS---------------------


//>>>>>-------------MAIN------------<<<<<

//Variables
float myState[12];
float myPos[3];
float vectorBetween[3];
//
float posA[3];
float posB[3];
float posC[3];
float posD[3];
//
float posA2[3];
float posB2[3];
float posC2[3];
float posD2[3];
//
float distance;
float stop[3];
float rateTarget[3];
int step;
float basePosR[3];
float basePosL[3];
float basePosL2[3];
float basePosR2[3];

//Begin CONST
void init(){
	//This function is called once when your code is first loaded.

	//IMPORTANT: make sure to set any variables that need an initial value.
	//Do not assume variables will be set to 0 automatically!
    //
    //BLUE
	posA[0]=0.35;
	posA[1]=0.35;
	posA[2]=0.0;
	
	posB[0]=-0.34;
	posB[1]=0.34;
	posB[2]=0.0;
	
	posC[0]=0.13;
	posC[1]=0.13;
	posC[2]=0.0;
	
	posD[0]=-0.35;
	posD[1]=-0.35;
	posD[2]=0.0;

    //
    //RED
    posA2[0]=-0.35;
    posA2[1]=-0.35;
    posA2[2]=0.0;
    
    posB2[0]=0.34;
    posB2[1]=-0.34;
    posB2[2]=0.0;
    
    posC2[0]=-0.13;
    posC2[1]=-0.13;
    posC2[2]=0.0;
    
    posD2[0]=0.35;
    posD2[1]=0.35;
    posD2[2]=0.0;
    //
	
	basePosR[0]=0.1;
	basePosR[1]=0.1;
	basePosR[2]=0.0;
	
	basePosL[0]=-0.1;
	basePosL[1]=0.1;
	basePosL[2]=0.0;
	
    //
    basePosR2[0]=-0.1;
    basePosR2[1]=-0.1;
    basePosR2[2]=0.0;
    
    basePosL2[0]=0.1;
    basePosL2[1]=-0.1;
    basePosL2[2]=0.0;
    //

	stop[0]=0.0;
	stop[1]=0.0;
	stop[2]=0.0;
	
    rateTarget[0]=0.0;
	rateTarget[1]=0.0;
	rateTarget[2]=35*PI/180;  
	
	step=0;
}
//End CONST

//>>>>>-------------LOOP PER SECOND------------<<<<<
void loop(){
	//This function is called once per second.  Use it to control the satellite.
	api.getMyZRState(myState);
    if (myState[1] > 0){
        switch (step){
            case 0:
                get_posA();
                break;
            case 1:
                start_DrillingA();
                break;
            case 2:
                goto_BaseR();
                break;
            case 3: 
                at_Base();
                break;
            case 4:
                get_posB();
                break;
            case 5:
                start_DrillingB();
                break;
            case 6:
                goto_BaseL();
                break;
            case 7:
                at_Base();
                break;
            
            case 8:
                get_posC();
                break; 
            
            case 9:
                start_DrillingC();
                break;
                
            case 10:
                at_Base();
                break;
        }
    }
    else {
        switch (step){
            case 0:
                get_posA2();
                break;
            case 1:
                start_DrillingA2();
                break;
            case 2:
                goto_BaseR2();
                break;
            case 3: 
                at_Base();
                break;
            case 4:
                get_posB2();
                break;
            case 5:
                start_DrillingB2();
                break;
            case 6:
                goto_BaseL2();
                break;
            case 7:
                at_Base();
                break;
            case 8:
                get_posC2();
                break; 
            case 9:
                start_DrillingC2();
                break;
            case 10:
                at_Base();
                break;
        }
    }
    DEBUG(("step = %d",step));
}
//>>>>>-------------END LOOP PER SECOND------------<<<<<

//CODERS:IGNACIO AYALA,LOURDES BADILLO,JUAN CARLOS GARFIAS,LUIS JAVIER ALONSO AND SPECIAL THANKS TO FRANCISCO HUELSZ

//--------------------------------END OF PROGRAM--------------------------------
