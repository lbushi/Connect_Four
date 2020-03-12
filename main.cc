#include <iostream>
#include <string>
#include "game.h"
#include "command.h"
#include "textdisplay.h"
#include "cell.h"
#include "controller.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
using namespace std;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 coords;\n"
"out vec2 texCoords;\n"
"uniform mat4 model;\n"
"void main()\n"
"{\n"
"   gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   texCoords = coords;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 texCoords;\n"
"uniform int turn;\n"
"uniform float c;\n"
"uniform sampler2D tex;\n"
"void main()\n"
"{\n"
"if (turn % 2 == 0)\n"
"   FragColor = vec4(texture(tex, texCoords).r - c, texture(tex, texCoords).gba);\n"
"else\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
"   if (texture(tex, texCoords).r >= 0.95f)\n"
"      FragColor = vec4(0.0f, 0.0f, 1.0f - c, texture(tex, texCoords).a);\n"
"}\n"
"}\n\0";
//glm::vec3 light_colour = glm::vec3(1.0f);
//glm::vec3 light_pos = glm::vec3(0.0f, 0.0f, 1.0f);
int width = 960;
int height = 540;
int texture_width = 0, texture_height = 0, texture_channels = 0;
const unsigned char* my_data = stbi_load("Red_Ball.png", &texture_width, &texture_height, &texture_channels, 0);
void framebuffer_size_callback(GLFWwindow* window, int new_width, int new_height) {
	glViewport(0, 0, new_width, new_height);
	width = new_width;
	height = new_height;
}
class Shape {
	float initPosx, initPosy;
	const float fall_speed = 0.1f;
	int fall_time, actual_time;
	int col, row;
	unsigned int vao, vbo, texture;
public:
	Shape(int col, int row) : col{ col }, row{ row }, initPosx{ (2 * col + 1) * 0.125f - 1.0f }, initPosy{ 0.875f }, actual_time{ 0 } {
		fall_time = (initPosy - (row * 0.25f - 0.875f)) / fall_speed;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, my_data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void draw(int program) {
		float vertices[] = {
		col * 0.25f - 1.0f, row * 0.25f - 1.0f, 0.0f, 0.0f,
		col * 0.25f - 1.0f,  (row + 1) * 0.25f - 1.0f, 0.0f, 1.0f,
		(col + 1) * 0.25f - 1.0f, (row + 1) * 0.25f - 1.0f, 1.0f, 1.0f,
		(col + 1) * 0.25f - 1.0f, (row + 1) * 0.25f - 1.0f, 1.0f, 1.0f,
		(col + 1) * 0.25f - 1.0f, row * 0.25f - 1.0f, 1.0f, 0.0f,
		col * 0.25f - 1.0f, row * 0.25f - 1.0f, 0.0f, 0.0f
		};
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		stbi_set_flip_vertically_on_load(1);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (actual_time > fall_time)
			actual_time = fall_time;
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, &glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, fall_speed * (fall_time - actual_time), 0.0f))[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		++actual_time;
	}
	int get_col() const {
		return col;
	}
	int get_row() const {
		return row;
	}
};
int col = 0;
bool event = 0;
bool finished = 0;
void keyboard_callback(GLFWwindow* window, int key, int action, int x, int y) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (finished) {
		return;
	}
	if (action == GLFW_RELEASE) {
		return;
	}
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	col = xpos / (width / 8);
	event = 1;
}
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "Connect Four", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);
	glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertex_shader);
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragment_shader);
	int program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	float lines[] = {
		-1.0f, 1.0f, -1.0f, -1.0f,
		-0.75f, 1.0f, -0.75f, -1.0f,
		-0.5f, 1.0f, -0.5f, -1.0f,
		-0.25f, 1.0f, -0.25f, -1.0f,
		0.0f, 1.0f, 0.0f, -1.0f,
		0.25f, 1.0f, 0.25f, -1.0f,
		0.5f, 1.0f, 0.5f, -1.0f,
		0.75f, 1.0f, 0.75f, -1.0f,
		1.0f, 1.0f ,1.0f, -1.0f
	};
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * 2 * sizeof(float), lines, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	int location = glGetUniformLocation(program, "turn");
	vector<Shape> shapes;
	auto chain = map<pair<int, int>, int>();
	Game g;
	g.init();
	float c = 0.75f;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		glUseProgram(0);
		glDrawArrays(GL_LINES, 0, 18);
		for (int i = 0; i < shapes.size(); ++i) {
			glUseProgram(program);
			glUniform1i(location, i);
			if (!(i % 2)) {
				glUniform1i(glGetUniformLocation(program, "tex"), 0);
			}
			if (chain.count(make_pair(7 - shapes[i].get_row(), shapes[i].get_col()))) {
				glUniform1f(glGetUniformLocation(program, "c"), c);
			}
			else {
				glUniform1f(glGetUniformLocation(program, "c"), 0.0f);
			}
			shapes[i].draw(program);
		}
		if (event) {
			shapes.emplace_back(Shape{ col, 7 - g.get_row(col)});
			event = 0;
			g.graphics_mark(col);
			if (g.game_over()) {
				chain = g.get_chain();
				std::cout << "Player " << g.winner() << " won!" << endl;
				finished = 1;
			}
			g.change_turn();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		c -= 0.02f;
		if (c < 0) {
			c = 0.5f;
		}
	}
	glfwTerminate();
	return 0;
}

