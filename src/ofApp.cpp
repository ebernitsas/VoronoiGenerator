
#include "ofApp.h"


int univx;
int univy;

int selectedPointIndex;
bool selectedActivate;

ofImage screenShot;

int activateMesh;
int diffOrSameColors;
int sameSize;
int dots;

int opCode;

int randColor;
int randColor2;
int randSat;


int timePassed;

int counting;




//--------------------------------------------------------------
void ofApp::setup(){
    
   //gifEncode setup
    gifEncoder.setup(600,600,.1,255);
    
    
    //rest of setup
    ofSetWindowTitle("ofxVoronoi / example_basic");
    ofBackground(ofColor::fromHsb(ofRandom(255),ofRandom(0,255),220));
    
    ofRectangle bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
    
    int pointCount = ofRandom(200);
    int seed = 33;
    
    scalarPointsVector = generateRandomPoints(pointCount, seed, bounds);
    
    
    voronoi.setBounds(bounds);
    voronoi.setPoints(scalarPointsVector.points);
    
    voronoi.generate();
    
    points.clear();
    
    for(auto cell : voronoi.getCells()) {
        points.push_back(cell.pt);
    }
    
    activateMesh = ofRandom(2);
    diffOrSameColors = ofRandom(3);
    sameSize = ofRandom(3);
    dots = ofRandom(2);
    opCode = ofRandom(11);
    
    cout << "activate Mesh" << activateMesh <<endl;
    
    randColor = ofRandom(255);
    randColor2 = ofRandom(255);
    randSat = ofRandom(255);
    
    counting = 0;
    
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    timePassed = ofGetElapsedTimeMillis();
    counting++;
    
    cout << timePassed << endl;
    
    if (counting % 4 == 0){
        screenShot.grabScreen(0,0,600,600);
        gifEncoder.addFrame(screenShot.getPixels(), 600, 600);
    }
    
    else if (timePassed > 2000){
        gifEncoder.save("test.gif");
        cout << "SAAAAVVVVVEEEDDDD!!!!!!" << endl;
    }
    
    if (timePassed > 3500){
        ofExit();
    }
    
    
    
    //0 - relax, 1 - up down, 2 - left right, 3 - all random
    
    if (opCode == 0 || opCode == 7 || opCode == 10){
        voronoi.relax();
    }
    else if (opCode == 1){
        int n = 0;
        for(int i = 0; i < points.size(); i++){
            n = ofRandom(4);
            selectedPointIndex = i;
            selectedActivate = true;
            if (n==0) scalarPointsVector.points[i].x += 5;
            else if (n==1) scalarPointsVector.points[i].x -= 5;
            else if (n==2) scalarPointsVector.points[i].y += 5;
            else if (n==3) scalarPointsVector.points[i].y -= 5;
            
        }
        
    }
    
    else if (opCode == 2){
        int n = 0;
        for(int i = 0; i < points.size(); i++){
            n = ofRandom(2);
            selectedPointIndex = i;
            selectedActivate = true;
            if (n==0) scalarPointsVector.points[i].y += 5;
            else if (n==1) scalarPointsVector.points[i].y -= 5;
            
        }
    }
    
    else if (opCode == 3){
        int n = 0;
        for(int i = 0; i < points.size(); i++){
            n = ofRandom(2);
            selectedPointIndex = i;
            selectedActivate = true;
            if (n==0) scalarPointsVector.points[i].x += 5;
            else if (n==1) scalarPointsVector.points[i].x -= 5;
            
        }
    }
    
    else if (opCode == 4){
        for(int i = 0; i < points.size(); i++){
            selectedPointIndex = i;
            selectedActivate = true;
            scalarPointsVector.points[i].x += 5;
            
        }
    }
    
    else if (opCode == 5){
        for(int i = 0; i < points.size(); i++){
            selectedPointIndex = i;
            selectedActivate = true;
            scalarPointsVector.points[i].y += 5;
            
        }
    }
    
    else if (opCode == 6){
        for(int i = 0; i < points.size(); i++){
            selectedPointIndex = i;
            selectedActivate = true;
            scalarPointsVector.points[i].y += 5;
            scalarPointsVector.points[i].x += 5;
            
        }
    }
    
    else if (opCode == 8){
        int n = 0;
        for(int i = 0; i < points.size()/2; i++){
            selectedPointIndex = i;
            selectedActivate = true;
            scalarPointsVector.points[i].x += 5;
            
        }
        
        for(int i = points.size()/2; i < points.size(); i++){
            selectedPointIndex = i;
            selectedActivate = true;
            scalarPointsVector.points[i].x -= 5;
            
        }
        
    }
    
    else if (opCode == 9){
        int n = 0;
        for(int i = 0; i < points.size()/2; i++){
            selectedPointIndex = i;
            selectedActivate = true;
            scalarPointsVector.points[i].y -= 5;
            
        }
        
        for(int i = points.size()/2; i < points.size(); i++){
            selectedPointIndex = i;
            selectedActivate = true;
            scalarPointsVector.points[i].y += 5;
            
        }
        
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    voronoi.draw();
    
    // Or feel free to draw the voronoi diagram yourself:
    
    ofRectangle bounds = voronoi.getBounds();
    ofSetLineWidth(0);
    ofNoFill();
    ofSetColor(ofColor::fromHsb(ofRandom(255),randSat,220));
    ofDrawRectangle(bounds);
    
    vector <ofxVoronoiCell> cells = voronoi.getCells();
    for(int i=0; i<cells.size(); i++) {
        ofSetColor(ofColor::fromHsb(randColor,randSat,220));
        ofFill();
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        mesh.addVertices(cells[i].pts);
        mesh.draw();
        
//        if (activateMesh){
//            mesh.clear();
//            for(int j = 0; j < cells[i].pts.size(); j++) {
//                mesh.addVertex(cells[i].pt);
//                mesh.addVertex(cells[i].pts[j]);
//            }
//            ofSetColor(r, g, b);
//            mesh.draw();
//        }
        // Draw cell points
        int offset = scalarPointsVector.scale[i];
        if(!diffOrSameColors) ofSetColor(ofColor::fromHsb((randColor2*offset)%255,randSat,220));
        else ofSetColor(ofColor::fromHsb(randColor2,randSat,220));
        ofFill();
        
        if (sameSize) ofDrawCircle(cells[i].pt, 4);
        else if (dots);
        else ofDrawCircle(cells[i].pt, scalarPointsVector.scale[i]);
    }
    
    if (selectedActivate){
        int pointCount = 100;
        int seed = 33;
        ofRectangle bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
        
        //points = generateRandomPoints(pointCount, seed, bounds);
        
        scalarPointsVector.points[selectedPointIndex] = ofPoint(univx, univy);
        
        
        voronoi.setBounds(bounds);
        voronoi.setPoints(scalarPointsVector.points);
        
        voronoi.generate();
        
    }
    
    
    
}

//--------------------------------------------------------------
scalarPoints ofApp::generateRandomPoints(int count, int seed, ofRectangle bounds) {
    vector <ofPoint> points;
    vector <int> scalars;
    scalarPoints spv;
//    ofSeedRandom(seed);
    
    for(int i=0; i<count; i++) {
        ofPoint newPoint = ofPoint(
            ofRandom(bounds.x, bounds.width),
            ofRandom(bounds.y, bounds.height)
        );
        
        points.push_back(newPoint);
        scalars.push_back(ofRandom(1,10));
        
    }
    spv.points = points;
    spv.scale = scalars;
    
    return spv;
}

//--------------------------------------------------------------
bool ofApp::isBorder(ofPoint _pt){
    ofRectangle bounds = voronoi.getBounds();
    
    return (_pt.x == bounds.x || _pt.x == bounds.x+bounds.width
            || _pt.y == bounds.y || _pt.y == bounds.y+bounds.height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int n = 0;
    switch(key) {
        case '1': n = 1; break;
        case '2': n = 10; break;
        case '3': n = 100; break;
        case '4': n = 1000; break;
        case ' ':
            screenShot.grabScreen(0,0,600,600);
            gifEncoder.addFrame(screenShot.getPixels(), 600, 600);
            break;
        case 's':
            cout <<"start saving\n" << endl;
            gifEncoder.save("test.gif");
            break;
    }
    for(int i = 0; i < n; i++) {
        voronoi.relax();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    univx = x;
    univy = y;
    //cout << univx << endl;
    
    
    
    

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    univx = x;
    univy = y;
    for(int i = 0; i < points.size(); i++){
        if ((univx-10 <= points[i].x && points[i].x <= univx+10 &&
             univy-10 <= points[i].y && points[i].y <= univy+10)){
            selectedPointIndex = i;
            selectedActivate = true;
            cout << "made it" << endl;
            cout << i << endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    selectedActivate = false;
    selectedPointIndex = 0;
    

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
