#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include"CAMERA.h"
#include"SHADERS.h"
camera mycamera;
float deltatime = 0.0f, currentframe = 0.0f;
float gravity = 3.1f;
float grounded = -0.9f;
void ProcessInput(GLFWwindow*,glm::vec3 &move);

bool Collision(glm::vec3 objects[], glm::vec3& move)
{
	
	bool colX, colY;

	colX = objects[0].x + 2.5f > move.x && move.x + 1.0f > objects[0].x;
	colY = objects[0].y + 2.5f > move.y && move.y + 1.0f > objects[0].y;
	return colX && colY;
	
	
}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1200, 1000, "container", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();

	shader program1("vertexshadersource.txt", "fragmentshadersource.txt");
	shader program2("Lightvertexshadersource.txt", "lightfragmentshadersource.txt");
	glEnable(GL_DEPTH_TEST);
	GLfloat position[] = {
	-0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f, 0.0f,0.0f,
	0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f, 1.0f, 0.0f,
	0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f, 1.0f, 1.0f,
	0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f, 1.0f, 1.0f,
	-0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f, 0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f, 0.0f, 0.0f,

	-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f, 0.0f, 0.0f,
	0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f, 1.0f, 0.0f,
	0.5f,0.5f,0.5f,0.0f,0.0f,1.0f, 1.0f, 1.0f,
	0.5f,0.5f,0.5f,0.0f,0.0f,1.0f, 1.0f, 1.0f,
	-0.5f,0.5f,0.5f,0.0f,0.0f,1.0f, 0.0f, 1.0f,
	-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f, 0.0f,0.0f,

	-0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f, 1.0f,0.0f,
	-0.5f,0.5f,-0.5f,-1.0f,0.0f,0.0f, 1.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f, 0.0f, 1.0f,
	-0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f, 0.0f,1.0f,
	-0.5f,-0.5f,0.5f,-1.0f,0.0f,0.0f, 0.0f,0.0f,
	-0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f, 1.0f, 0.0f,

	0.5f,0.5f,0.5f,1.0f,0.0f,0.0f, 1.0f,0.0f,
	0.5f,0.5f,-0.5f,1.0f,0.0f,0.0f, 1.0f, 1.0f,
	0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f, 0.0f, 1.0f,
	0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f, 0.0f,1.0f,
	0.5f,-0.5f,0.5f,1.0f,0.0f,0.0f, 0.0f,0.0f,
	0.5f,0.5f,0.5f,1.0f,0.0f,0.0f, 1.0f, 0.0f,

	-0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f, 0.0f,1.0f,
	0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f, 1.0f, 1.0f,
	0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f, 1.0f, 0.0f,
	0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f, 1.0f, 0.0f,
	-0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f, 0.0f, 0.0f,
	-0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f, 0.0f, 1.0f,

	-0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f, 0.0f,1.0f,
	0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f, 1.0f,1.0f,
	0.5f,0.5f,0.5f,0.0f,1.0f,0.0f, 1.0f,0.0f,
	0.5f,0.5f,0.5f,0.0f,1.0f,0.0f, 1.0f,0.0f,
	- 0.5f,0.5f,0.5f,0.0f,1.0f,0.0f, 0.0f,0.0f,
	- 0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f ,0.0f,1.0f
	};
	GLuint VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	GLuint texture1,texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int height, width, crvalue;
	unsigned char* data = stbi_load("difusemap.png", &width, &height, &crvalue,0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "failed" << std::endl;
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("specularmap.png", &width, &height, &crvalue, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "failed" << std::endl;
	stbi_image_free(data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glm::mat4 project = glm::mat4(1.0f);
	project = glm::perspective(glm::radians(45.0f), 1200.0f / 1000.0f, 0.1f, 100.0f);
	glm::mat4 size = glm::mat4(1.0f);
	size = glm::scale(size, glm::vec3(2.5f, 2.5f, 1.5f));
	glm::vec3 campos = glm::vec3(0.0f, 0.0f, 25.0f);
	glm::mat4 view = glm::lookAt(campos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 multiple[] = {
		glm::vec3(0.0f),
		glm::vec3(1.5f,0.0f,0.0f),
		glm::vec3(0.75f,1.0f,0.0f),
		glm::vec3(3.0f,0.0f,0.0f),
		glm::vec3(2.25f,1.0f,0.0f),
		glm::vec3(1.5f,2.0f,0.0f)
	};
	glm::vec3 move = glm::vec3(-6.0f, -1.0f, 0.23f);
	std::cout << size.length();
	while (!glfwWindowShouldClose(window))
	{
		if (Collision(multiple, move))
		{

			std::cout << "Collided";
			grounded = 2.5f;
		}
		else
			grounded = -0.9f;

		ProcessInput(window, move);
		
		if (move.y > grounded)
			move.y -= gravity * deltatime;
		glClearColor(0.5f, 0.5f, 0.5f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		view = glm::lookAt(campos, glm::vec3(1.0f, 0.0f, 15.0f), glm::vec3(0.0f, 8.0f, 0.0f));
		
		program1.use();
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0);

		glUniform1i(glGetUniformLocation(program1.ID, "diffuse"), 0);

		glUniformMatrix4fv(glGetUniformLocation(program1.ID,"project"), 1, GL_FALSE, glm::value_ptr(project));
		glUniformMatrix4fv(glGetUniformLocation(program1.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program1.ID, "size"), 1, GL_FALSE, glm::value_ptr(size));
		for (unsigned int i = 0; i < sizeof(multiple) / sizeof(multiple[0]); i++)
		{

			glm::mat4 mov = glm::mat4(1.0f);
			mov = glm::translate(mov, multiple[i]);
			glUniformMatrix4fv(glGetUniformLocation(program1.ID, "move"), 1, GL_FALSE, glm::value_ptr(mov));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glm::mat4 objmov = glm::mat4(1.0f);
		objmov = glm::translate(objmov, move);
		objmov = glm::scale(objmov, glm::vec3(1.0f));
		
		program2.use();
		glUniformMatrix4fv(glGetUniformLocation(program2.ID, "project"), 1, GL_FALSE, glm::value_ptr(project));
		glUniformMatrix4fv(glGetUniformLocation(program2.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program2.ID, "move"), 1, GL_FALSE, glm::value_ptr(objmov));
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window, glm::vec3& move)
{
	float lastframe = glfwGetTime();
	deltatime = (lastframe - currentframe) * 3.5f;
	currentframe = lastframe;
	float velocity = deltatime * 1.5f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move.x += velocity;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move.x -= velocity;
	
	float force = velocity * 18.0f*gravity+3.0f;
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && move.y < grounded)
	{
		move.y +=force ;

	}

}
