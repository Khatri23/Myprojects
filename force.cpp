#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include"SHADERS.h"
#include"CAMERA.h"
camera mycamera;
float lastX = 600.0f, lastY = 500.0f;
bool firstmouse = true;
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);
	if (firstmouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstmouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;
	mycamera.mouse_callback(xoffset, yoffset);
}
glm::vec3 lightpos = glm::vec3(4.0f, 8.0f, 3.0f);
float deltatime = 0.0f, lastframe = 0.0f;
void lightmovement(GLFWwindow* window)
{
	float currentframe = glfwGetTime();
	deltatime = currentframe - lastframe;
	lastframe = currentframe;
	float sensitivity = deltatime * 3.5f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		lightpos.z -= sensitivity;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		lightpos.z += sensitivity;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		lightpos.x += sensitivity;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		lightpos.x -= sensitivity;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		lightpos.y += sensitivity;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		lightpos.y -= sensitivity;
	
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1200, 1000, "LightMaps", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 1200, 1000);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

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
	0.5f,0.5f,0.5f,0.0f,1.0f,0.0f, 1.0f,0.0f
	- 0.5f,0.5f,0.5f,0.0f,1.0f,0.0f, 0.0f,0.0f
	- 0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f ,0.0f,1.0f
	};
	GLuint VAO, VBO,LightVAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glGenVertexArrays(1, &LightVAO);
	glBindVertexArray(LightVAO);
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
	unsigned char * data = stbi_load("difusemap.png", &width, &height, &crvalue, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	if (!data)
		std::cout << "failed";
	stbi_image_free(data);
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data= stbi_load("specularmap.png", &width, &height, &crvalue, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	if (!data)
		std::cout << "failed";
	stbi_image_free(data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glm::mat4 project = glm::mat4(1.0f);
	project = glm::perspective(glm::radians(45.0f), 1200.0f / 1000.0f, 0.1f, 100.0f);
	glm::mat4 t = glm::mat4(1.0f);
	t = glm::translate(t, glm::vec3(-1.0f, 0.0f, -6.0f));
	glm::mat4 size = glm::mat4(1.0f);
	size = glm::scale(size, glm::vec3(4.0f,4.0f,4.5f));

	glm::mat4 lightsize = glm::mat4(1.0f);
	lightsize = glm::scale(lightsize, glm::vec3(0.3f));
	

	shader program1("vertexshadersource.txt", "fragmentshadersource.txt");
	shader program2("Lightvertexshadersource.txt", "lightfragmentshader.txt");
	while (!glfwWindowShouldClose(window))
	{
		lightmovement(window);
		mycamera.InputProcess(window);
		glClearColor(0.0f, 0.0f, 0.0f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = mycamera.Looking();
		
		program1.use();
		glUniform3fv(glGetUniformLocation(program1.ID, "lightpos"), 1, glm::value_ptr(lightpos));
		glUniform3fv(glGetUniformLocation(program1.ID, "viewpos"), 1, glm::value_ptr(mycamera.campos));
		/*glUniform3f(glGetUniformLocation(program1.ID,"material.ambient"), 0.1f, 0.2f, 0.5f);
		glUniform3f(glGetUniformLocation(program1.ID, "material.diffuse"), 0.1f, 0.2f, 0.5f);*/
		//glUniform3f(glGetUniformLocation(program1.ID, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(program1.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(program1.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(program1.ID, "light.specular"), 1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(glGetUniformLocation(program1.ID, "project"), 1, GL_FALSE, glm::value_ptr(project));
		glUniformMatrix4fv(glGetUniformLocation(program1.ID, "size"), 1, GL_FALSE, glm::value_ptr(size));
		glUniformMatrix4fv(glGetUniformLocation(program1.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program1.ID, "move"), 1, GL_FALSE, glm::value_ptr(t));
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(program1.ID, "material.diffuse"), 0);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(glGetUniformLocation(program1.ID, "material.specular"), 1);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		program2.use();
		glm::mat4 move = glm::mat4(1.0f);
		move = glm::translate(move, lightpos);
		glUniformMatrix4fv(glGetUniformLocation(program2.ID, "project"), 1, GL_FALSE, glm::value_ptr(project));
		glUniformMatrix4fv(glGetUniformLocation(program2.ID, "size"), 1, GL_FALSE, glm::value_ptr(lightsize));
		glUniformMatrix4fv(glGetUniformLocation(program2.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program2.ID, "move"), 1, GL_FALSE, glm::value_ptr(move));
		glBindVertexArray(LightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}