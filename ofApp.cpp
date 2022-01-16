#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 3;
	float theta_deg_step = 12;

	float R = 250;

	for (int base_r = 0; base_r <= 20; base_r += 3) {

		int r = (base_r + ofGetFrameNum() * 3) % 100;
		//if (r < 25) { continue; }

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(glm::vec4(this->make_point(R, R * 0.25, theta_deg, phi_deg) * 0.05, ofGetFrameNum() * 0.02));
				if (noise_value < 0.475) { continue; }

				auto noise_1 = ofNoise(glm::vec4(this->make_point(R, R * 0.25, theta_deg - theta_deg_step, phi_deg) * 0.05, ofGetFrameNum() * 0.02));
				auto noise_2 = ofNoise(glm::vec4(this->make_point(R, R * 0.25, theta_deg, phi_deg + phi_deg_step) * 0.05, ofGetFrameNum() * 0.02));
				auto noise_3 = ofNoise(glm::vec4(this->make_point(R, R * 0.25, theta_deg, phi_deg - phi_deg_step) * 0.05, ofGetFrameNum() * 0.02));
				auto noise_4 = ofNoise(glm::vec4(this->make_point(R, R * 0.25, theta_deg + theta_deg_step, phi_deg) * 0.05, ofGetFrameNum() * 0.02));

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
				vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				auto alpha = 255;
				if (r >= 50) {

					alpha = ofMap(r, 50, 101, 255, 0);
				}

				alpha = ofMap(r, 0, 100, 255, 0);

				for (int i = 0; i < 4; i++) {

					this->face.addColor(ofColor(255, alpha));
				}

				if (noise_1 < 0.475) {

					this->line.addVertex(vertices[0]);
					this->line.addVertex(vertices[2]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(ofColor(0, alpha)); this->line.addColor(ofColor(0, alpha));
				}

				if (noise_2 < 0.475) {

					this->line.addVertex(vertices[2]);
					this->line.addVertex(vertices[3]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(ofColor(0, alpha)); this->line.addColor(ofColor(0, alpha));
				}

				if (noise_3 < 0.475) {

					this->line.addVertex(vertices[0]);
					this->line.addVertex(vertices[1]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(ofColor(0, alpha)); this->line.addColor(ofColor(0, alpha));
				}

				if (noise_4 < 0.475) {

					this->line.addVertex(vertices[1]);
					this->line.addVertex(vertices[3]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(ofColor(0, alpha)); this->line.addColor(ofColor(0, alpha));
				}
			}
		}
	}

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 1.8);
	ofRotateX(ofGetFrameNum() * 1.2);

	ofSetLineWidth(3);

	this->line.draw();
	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}