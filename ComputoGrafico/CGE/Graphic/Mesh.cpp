#include "Mesh.h"
#include "glm.hpp"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "../Base/ShaderManager.h"

		Mesh::Mesh()
		{
			VAO = 0;
			VBO = 0;
			IBO = 0;
			indexCount = 0;
		}

		void Mesh::CreateMesh(std::vector<GLfloat> vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices, unsigned int vSize)
		{
			indexCount = numOfIndices;
			this->vertices = vertices;
			InitBox();
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numOfVertices, &vertices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, 0);
			glEnableVertexAttribArray(0);
			if (vSize > 3) {
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, (void*)(sizeof(GLfloat) * 3));
				glEnableVertexAttribArray(1);
			}
			if (vSize > 5) {
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, (void*)(sizeof(GLfloat) * 5));
				glEnableVertexAttribArray(2);
			}
			if (vSize > 8) {
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, (void*)(sizeof(GLfloat) * 8));
				glEnableVertexAttribArray(3);
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
		}

		void Mesh::RenderMesh()
		{
			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		const std::vector<GLfloat>* Mesh::GetVertices()
		{
			return &vertices;
		}
		void Mesh::ClearMesh()
		{
			if (IBO != 0)
			{
				glDeleteBuffers(1, &IBO);
				IBO = 0;
			}

			if (VBO != 0)
			{
				glDeleteBuffers(1, &VBO);
				VBO = 0;
			}

			if (VAO != 0)
			{
				glDeleteVertexArrays(1, &VAO);
				VAO = 0;
			}

			indexCount = 0;
		}


		Mesh::~Mesh()
		{
			ClearMesh();
		}

		void Mesh::InitBox()
		{
			min_x = max_x = vertices[0];
			min_y = max_y = vertices[1];
			min_z = max_z = vertices[2];
			for (int i = 0; i < vertices.size() - 3; i += 3) {
				if (vertices[i] < min_x) min_x = vertices[i];
				if (vertices[i] > max_x) max_x = vertices[i];
				if (vertices[i + 1] < min_y) min_y = vertices[i + 1];
				if (vertices[i + 1] > max_y) max_y = vertices[i + 1];
				if (vertices[i + 2] < min_z) min_z = vertices[i + 2];
				if (vertices[i + 2] > max_z) max_z = vertices[i + 2];
			}
		}
