#include <cmath>
#include <iostream>
#include <array>
#include <map>
#include <string>

#include "GL/glut.h"
#include "GL/GLU.h"
#include "GL/GL.h"

#define LOADBMP_IMPLEMENTATION
#include "load_bmp.h"

#define PI 3.1415f

enum TextureType {
    Parket = 0,
    Wallpaper,
    Wood1,
    Wood2
};

std::array<TextureType, 4> allTextures = { 
    Parket, 
    Wallpaper, 
    Wood1, 
    Wood2 
};
std::map<TextureType, std::string> allTexturesPaths = { 
    {Parket, "./parket.bmp"},  
    {Wallpaper, "./wallpaper.bmp"},  
    {Wood1, "./wood2.bmp"},  
    {Wood2, "./wood.bmp"},  
};

float xrot = 100;
float yrot = 0;
float x = 0;
float y = 0;
float z = 0;
float rotateOffset = 0.8;
float moveOffset = 0.16;
bool isTexturingEnabled = true;
bool isLightEnabled = true;

// textures loading

void loadTexture(int id, const char* filename) {
    unsigned char* pixels = nullptr;
    unsigned int width, height;

    unsigned int err = loadbmp_decode_file(filename, &pixels, &width, &height, 3);

    if (err) {
        std::cout << "Error while loading texture: " << err << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    free(pixels);
}

void loadTextures() {
    for (auto id : allTextures)
    {
        loadTexture(id, allTexturesPaths[id].c_str());
    }
}

void customGlBindTexture(GLuint id) {
    if (isTexturingEnabled) {
        glEnable(GL_TEXTURE_2D);
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D, id);
}

// scene drawing

void drawRect(float dx, float dy, float count) {
    float z = 0;

    glBegin(GL_POLYGON);

    glTexCoord2f(0, 0);
    glVertex3f(0, -dy, z);
    glTexCoord2f(dx * count, 0);
    glVertex3f(dx, -dy, z);
    glTexCoord2f(dx * count, dy * count);
    glVertex3f(dx, 0, z);
    glTexCoord2f(0, dy * count);
    glVertex3f(0, 0, z);

    glEnd();
}

void drawRoom() {
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-3, 3, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(12, 6, 0.5);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    customGlBindTexture(TextureType::Wallpaper);
    glPushMatrix();
    glTranslatef(-3, 3, -3);
    glColor3f(0.2, 0.2, 0);
    drawRect(12, 6, 0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9, 3, 3);
    glRotatef(180, 0, 1, 0);
    drawRect(12, 6, 0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9, 3, -3);
    glRotatef(-90, 0, 1, 0);
    drawRect(6, 6, 0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, 3, 3);
    glRotatef(90, 0, 1, 0);
    drawRect(6, 6, 0.1);
    glPopMatrix();

    customGlBindTexture(TextureType::Parket);
    glPushMatrix();
    glTranslatef(-3, -3, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.6, 0.3, 0);
    drawRect(12, 6, 0.5);
    glPopMatrix();
}

void drawChair() {
    customGlBindTexture(TextureType::Wood2);
    glPushMatrix();
    glTranslatef(7, -1.8, 1.5);
    glRotatef(90, 1, 0, 0);
    glColor3f(1.0, 0.0, 0.0);
    drawRect(0.9, 0.9, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -1.7, 1.5);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.9, 0.9, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 1.5);
    glRotatef(180, 0, 1, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 1.5);
    glRotatef(90, 0, 1, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 0.6);
    glRotatef(180, 0, 1, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -1.7, 0.6);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -1.7, 1.4);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -1.7, 1.5);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -1.7, 1.4);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -1.7, 1.5);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -3, 1.5);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -1.7, 1.5);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -1.7, 0.6);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -1.7, 0.7);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -1.7, 0.6);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -1.7, 0.7);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -3, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -1.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 1.4);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 1.5);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 1.4);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -1.7, 1.5);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -3, 1.5);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -1.7, 1.5);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 0.6);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 0.7);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -1.7, 0.6);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -1.7, 0.7);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.3, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -3, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -1.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -0.7, 0.6);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -0.7, 0.7);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.1, -0.7, 0.6);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -0.7, 0.7);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -1.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -0.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -0.7, 0.6);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -0.7, 0.7);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -0.7, 0.6);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -0.7, 0.7);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -1.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.8, -0.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.45, -0.7, 0.6);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.45, -0.7, 0.7);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.45, -0.7, 0.6);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.35, -0.7, 0.7);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.35, -1.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.35, -0.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -0.6, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -0.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glColor3f(1, 0, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -0.6, 0.7);
    glRotatef(180, 0, 1, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -0.6, 0.6);
    glRotatef(180, 0, 1, 0);
    drawRect(0.9, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7.9, -0.6, 0.7);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7, -0.6, 0.6);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
}

void drawTable() {
    customGlBindTexture(TextureType::Wood1);
    glPushMatrix();
    glTranslatef(6, -1.2, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8, 0.8, 0);
    drawRect(3, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -1.1, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8, 0.8, 0);
    drawRect(3, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(9, -1.1, 2.99);
    glRotatef(180, 0, 1, 0);
    glColor3f(0.2, 0.2, 0);
    drawRect(3, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(9, -1.1, 1.2);
    glRotatef(180, 0, 1, 0);
    drawRect(3, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -1.1, 1.2);
    glRotatef(-90, 0, 1, 0);
    drawRect(1.8, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.9, -1.1, 3);
    glRotatef(90, 0, 1, 0);
    drawRect(1.8, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6.1, -1.2, 2.99);
    glRotatef(180, 0, 1, 0);
    glColor3f(0.2, 0.2, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6.1, -1.2, 2.9);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6.1, -1.2, 2.9);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -1.2, 3);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -3, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.6, 0.3, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -1.2, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8, 0.8, 1);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6.1, -1.2, 1.2);
    glRotatef(180, 0, 1, 0);
    glColor3f(0.2, 0.2, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -1.2, 1.3);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6.1, -1.2, 1.3);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6.1, -1.2, 1.2);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -3, 1.3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.6, 0.3, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -1.2, 1.3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8, 0.8, 1);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.9, -1.2, 2.99);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.9, -1.2, 2.9);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.9, -1.2, 2.9);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.8, -1.2, 3);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.8, -3, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.6, 0.3, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.8, -1.2, 3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8, 0.8, 1);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.9, -1.2, 1.2);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.8, -1.2, 1.3);
    glRotatef(90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.9, -1.2, 1.3);
    glRotatef(180, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(8.9, -1.2, 1.2);
    glRotatef(-90, 0, 1, 0);
    drawRect(0.1, 1.8, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -3, 1.3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.6, 0.3, 0);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(6, -1.2, 1.3);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8, 0.8, 1);
    drawRect(0.1, 0.1, 0.5);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(yrot, 1, 0, 0);
    glRotatef(xrot, 0, 1, 0);

    glTranslatef(x, y, z);
    glPushMatrix();
    glPopMatrix();

    drawRoom();
    glPushMatrix();
    glPopMatrix();

    drawChair();
    glPushMatrix();
    glPopMatrix();
    drawTable();

    glutSwapBuffers();
}

// user input processing

float deg2rad(float angle) {
    return angle / 180 * PI;
}

void keyboardFunc(unsigned char key, int _x, int _y) {
    if (key == 'w' || key == 'W') {
        x -= std::sin(deg2rad(xrot)) * moveOffset;
        y += std::sin(deg2rad(yrot)) * moveOffset;
        z += std::cos(deg2rad(xrot)) * moveOffset;
    }

    if (key == 's' || key == 'S') {
        x += std::sin(deg2rad(xrot)) * moveOffset;
        y -= std::sin(deg2rad(yrot)) * moveOffset;
        z -= std::cos(deg2rad(xrot)) * moveOffset;
    }

    if (key == 't' || key == 'T') {
        isTexturingEnabled = !isTexturingEnabled;
    }

    if (key == 'l' || key == 'L') {
        isLightEnabled = !isLightEnabled;
        if (isLightEnabled) {
            glEnable(GL_LIGHT1);
        }
        else {
            glDisable(GL_LIGHT1);
        }
    }

    glutPostRedisplay();
}

void specialFunc(int key, int _x, int _y) {
    if (key == GLUT_KEY_UP) {
        yrot -= rotateOffset;
    }
    if (key == GLUT_KEY_DOWN) {
        yrot += rotateOffset;
    }
    if (key == GLUT_KEY_LEFT) {
        xrot -= rotateOffset;
    }
    if (key == GLUT_KEY_RIGHT) {
        xrot += rotateOffset;
    }

    if (yrot < -90) {
        yrot = -90;
    }

    if (yrot > 90) {
        yrot = 90;
    }

    glutPostRedisplay();
}

// set settings and start app

void setGlobalLight() {
    GLfloat* materialColor = new GLfloat[]{ 1, 1, 1, 1 };

    // if lightPosition[3] == 1 => directional light
    GLfloat* lightPosition = new GLfloat[]{ 0, 2.5, 0, 1 };

    GLfloat* diffuseProperty = new GLfloat[]{ 1, 1, 1, 1 };
    GLfloat* specularProperty = new GLfloat[]{ 1, 1, 1, 1 };
    GLfloat* ambientProperty = new GLfloat[]{ 1, 1, 1, 1 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialColor);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseProperty);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularProperty);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientProperty);
}

void init() {
    glClearColor(0, 0.5, 0.2, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 800, 800);
    gluPerspective(60, 1, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);;
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_LIGHT1);

    setGlobalLight();
    loadTextures();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Room");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMainLoop();
}