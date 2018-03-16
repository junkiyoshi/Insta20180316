#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofBackground(239);
	ofSetWindowTitle("Insta");
	ofEnableDepthTest();

	this->icoSphere.setRadius(250);
	this->icoSphere.setResolution(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.1);
	ofRotateY(ofGetFrameNum() * 0.25);

	vector<ofMeshFace> triangles = icoSphere.getMesh().getUniqueFaces();
	for (int i = 0; i < triangles.size(); i++) {

		ofPoint avg = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
		float noise_value = ofNoise(avg.y * 0.005 + ofGetFrameNum() * 0.05);

		for (float roop_noise = 1.f; roop_noise > noise_value; roop_noise -= 0.2f) {

			ofMesh mesh;
			for (int v_index = 0; v_index < 3; v_index++) {

				ofPoint point = triangles[i].getVertex(v_index) - avg;
				mesh.addVertex(point * roop_noise);
			}

			ofPushMatrix();
			ofTranslate(avg);

			ofSetColor(239);
			mesh.drawWireframe();

			if (roop_noise == 1.f) {

				ofTranslate(avg * -0.001);
				ofSetColor(39);
				mesh.drawFaces();
			}
			else if (roop_noise - 0.2f < noise_value) {
			
				ofSetColor(239);
				mesh.drawFaces();
			}

			ofPopMatrix();
		}
	}

	this->cam.end();
}


//========================================================================
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}