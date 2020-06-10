#pragma once

#include <GL\glew.h>
#include <vector>

		class Mesh
		{
		public:
			Mesh();
			void CreateMesh(std::vector<GLfloat> vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices, unsigned int vSize);
			void RenderMesh();
			void ClearMesh();
			const std::vector<GLfloat>* GetVertices();
			~Mesh();
			//update BoundingBox adidier
			//draw BoundingBox
			//check colision 
			/* 
				bool CheckColision( std::vector<GLfloat> box1,std::vector<GLfloat> box2)
				{

					return 
				}*/
			void InitBoundingBox();
			const std::vector<GLfloat> *GetVertexBoundingBox();
		private:
			void PushVertex(GLfloat x, GLfloat y, GLfloat z);
			std::vector<GLfloat> vertex;
			GLuint VAO, VBO, IBO;
			GLsizei indexCount;
			std::vector<GLfloat> vertexBoundingBox;
		};


