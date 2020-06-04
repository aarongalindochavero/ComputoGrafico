#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"

const int MAX_POINT_LIGHTS = 3;

class Shader
{
private:
	GLuint uniformPointLightCount;
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} uniformDirectionalLight;
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetColor1();
	GLuint GetColor2();
	GLuint GetNormalTexture();

	GLuint GetmainTex();
	GLuint GetrTex();
	GLuint GetgTex();
	GLuint GetbTex();
	GLuint GetblendTexture();

	void UseShader();
	void ClearShader();

	////Material
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePositionLocation();

	~Shader();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition;
	GLuint color1, color2;
	GLuint myLightPosition;
	GLuint mainTex;
	GLuint rTex;
	GLuint gTex;
	GLuint bTex;
	GLuint blendTexture;
	GLuint normalTexture;
	GLint uniformSpecularIntensity, uniformShininess;
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);



};

