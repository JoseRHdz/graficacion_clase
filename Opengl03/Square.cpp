#include "Square.h"

Square::Square()
{
}

Square::~Square()
{
}

void Square::startup ()
{
	vector<vec3> v1, v2;
	vector<vec3> c1, c2;

	v1.push_back(vec3(-0.5f,-0.5f,0.0f));
	v1.push_back(vec3(-0.5f,0.5f,0.0f));
	v1.push_back(vec3(0.5f,0.5f,0.0f));

	c1.push_back(vec3(1.0f,0.0f,0.0f));
	c1.push_back(vec3(0.0f,1.0f,0.0f));
	c1.push_back(vec3(0.0f,0.0f,1.0f));

	v2.push_back(vec3(-0.5f,-0.5f,0.0f));
	v2.push_back(vec3(0.5f,0.5f,0.0f));
	v2.push_back(vec3(0.5f,-0.5f,0.0f));

	c2.push_back(vec3(1.0f,0.0f,0.0f));
	c2.push_back(vec3(0.0f,1.0f,0.0f));
	c2.push_back(vec3(0.0f,0.0f,1.0f));

	t1.startup(v1,c1);
	t2.startup(v2,c2);
}

void Square::draw()
{
	t1.draw();
	t2.draw();
}

void Square::shutdown()
{
	t1.shutdown();
	t2.shutdown();
}
