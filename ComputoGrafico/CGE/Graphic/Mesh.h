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

			void InitBox();
         

		private:

			std::vector<GLfloat> vertices;
			GLuint VAO, VBO, IBO;
			GLsizei indexCount;

			GLfloat min_x, max_x,
					min_y, max_y,
					min_z, max_z;
		};

