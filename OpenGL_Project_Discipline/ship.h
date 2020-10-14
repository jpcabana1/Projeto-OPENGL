
#pragma once
#include <vector>
class ship
{
private:
	float format[18] = {
		// positions         // colors
		-0.06f, -0.9f, 0.0f,  1.0f, 1.0f, 0.0f,  // bottom left
		 0.06f, -0.9f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		 0.0f,  -0.8f, 0.0f,  0.0f, 1.0f, 1.0f   // top
	};

	float x = 0;
	float y = 0;
	float accl = 0.0005;
public:
	

	float getSize() {
		return sizeof(format);
	}

	float* getFormat() {
		return format;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	void addCoordX() {
		if (x >= 0.95) {
			x = 0.95;
		}
		else {
			x = x + accl;
		}
	}

	void subCoordX() {
		if (x <= -0.95) {
			x = -0.95;
		}
		else {
			x = x + (-1 * accl);
		}

	}
	void addCoordY() {
		if (y >= 1.39) {
			y = 1.39;
		}
		else {
			y = y + accl;
		}

	}

	void subCoordY() {
		if (y <= -0.5) {
			y = -0.5;
		}
		else {
			y = y + (-1 * accl);
		}
	}

	void setX(float p_x) {
		x = p_x;
	}
	void setY(float p_y) {
		y = p_y;
	}
	
};

