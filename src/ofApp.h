#pragma once

#include "ofMain.h"
#include "ofxVoronoi.h"
#include "ofxGifEncoder.h"
#include "ofxGifFrame.h"


struct scalarPoints{
    vector <ofPoint> points;
    vector <int> scale;
};

class ofApp : public ofBaseApp{
    private:
        scalarPoints generateRandomPoints(int count, int seed, ofRectangle bounds);
        ofxVoronoi voronoi;
        vector <ofPoint> points;
        scalarPoints scalarPointsVector;
    
        ofxGifEncoder gifEncoder;
    
        bool isBorder(ofPoint _pt);
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
