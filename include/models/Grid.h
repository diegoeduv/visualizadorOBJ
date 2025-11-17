#ifndef GRID_H
#define GRID_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <assert.h>
#include "Model.h"

class Grid:public Model
{

private:
    
    // int m_width = 0;
	// int m_depth = 0; // Profundidad de la malla 
    // int m_funcType = 0; // Tipo de función para la altura

    struct Vertex
    {
        glm::vec3 Pos; 
        
        /**
         * @brief Inicializa el atributo Pos de cada Vertex 
         */
        void InitVertex(int x, int y, int z);
    };
    

    /**
     * @brief Inicializa cada vertice de la Grid en base al width y depth  
     * @param Vertices referencia a una lista de vertices para inicializar 
     */
    void InitVertices(std::vector<Vertex>& Vertices);

    /**
     * @brief Inicializa indices para los veritces de la malla  
     * @param Vertices 
     */
    void InitIndices(std::vector<uint>& Indices);

    void initGeometry();

    void cosSinFunc(float x, float z, float& y) const;
    void expFunc(float x, float z, float& y) const;
    glm::mat4 m_model_mat = glm::mat4(1.0f);

public: 
    Grid()=default;
    Grid(int width, int depth, int funcType):m_width(width),m_depth(depth),m_funcType(funcType){};
    void CreateTriangleList();
    int m_width = 0;
	int m_depth = 0; // Profundidad de la malla 
    int m_funcType = 0; // Tipo de función para la altura
    void draw() const;

        /**
     * @brief Devuelve los vértices del grid (como un vector plano de floats x,y,z)
     */
    std::vector<float> getVertices() const;

    /**
     * @brief Devuelve el número total de vértices del grid
     */
    int getNumVertices() const;


};


#endif