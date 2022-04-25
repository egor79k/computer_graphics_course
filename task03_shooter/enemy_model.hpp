#ifndef ENEMY_MODEL_HPP
#define ENEMY_MODEL_HPP

// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
namespace enemyModel {
    static const GLfloat g_vertex_buffer_data[] = {
         0.0f, 1.0f, 0.0f, // Hat
         0.0f, 1.0f,-1.0f,
        -0.9f, 1.0f,-0.5f,

         0.0f, 1.0f, 0.0f,
        -0.9f, 1.0f,-0.5f,
        -0.9f, 1.0f, 0.5f,

         0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 1.0f,
        -0.9f, 1.0f, 0.5f,

         0.0f, 1.0f, 0.0f,
         0.0f, 1.0f,-1.0f,
         0.9f, 1.0f,-0.5f,

         0.0f, 1.0f, 0.0f,
         0.9f, 1.0f,-0.5f,
         0.9f, 1.0f, 0.5f,

         0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 1.0f,
         0.9f, 1.0f, 0.5f,

        -0.5f, 0.0f,-0.9f, // Side up
         0.0f, 1.0f,-1.0f,
        -0.9f, 1.0f,-0.5f,

        -1.0f, 0.0f, 0.0f,
        -0.9f, 1.0f,-0.5f,
        -0.9f, 1.0f, 0.5f,

        -0.5f, 0.0f, 0.9f,
         0.0f, 1.0f, 1.0f,
        -0.9f, 1.0f, 0.5f,

         0.5f, 0.0f,-0.9f,
         0.0f, 1.0f,-1.0f,
         0.9f, 1.0f,-0.5f,

         1.0f, 0.0f, 0.0f,
         0.9f, 1.0f,-0.5f,
         0.9f, 1.0f, 0.5f,

         0.5f, 0.0f, 0.9f,
         0.0f, 1.0f, 1.0f,
         0.9f, 1.0f, 0.5f,

        -0.9f, 1.0f,-0.5f, // Side down
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.0f,-0.9f,

         0.0f, 1.0f,-1.0f,
        -0.5f, 0.0f,-0.9f,
         0.5f, 0.0f,-0.9f,

         0.9f, 1.0f,-0.5f,
         1.0f, 0.0f, 0.0f,
         0.5f, 0.0f,-0.9f,

        -0.9f, 1.0f, 0.5f,
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.9f,

         0.0f, 1.0f, 1.0f,
        -0.5f, 0.0f, 0.9f,
         0.5f, 0.0f, 0.9f,

         0.9f, 1.0f, 0.5f,
         1.0f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.9f,

         0.0f,-1.0f, 0.0f, // Cone
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.0f,-0.9f,

         0.0f,-1.0f, 0.0f,
        -0.5f, 0.0f,-0.9f,
         0.5f, 0.0f,-0.9f,

         0.0f,-1.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         0.5f, 0.0f,-0.9f,

         0.0f,-1.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.9f,

         0.0f,-1.0f, 0.0f,
        -0.5f, 0.0f, 0.9f,
         0.5f, 0.0f, 0.9f,

         0.0f,-1.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.9f
    };

    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = { 
        0.9f, 0.9f, 0.9f,
        0.5f, 0.7f, 0.0f,
        0.5f, 0.7f, 0.0f,
        0.9f, 0.9f, 0.9f,
        0.5f, 0.7f, 0.0f,
        0.5f, 0.7f, 0.0f,
        0.9f, 0.9f, 0.9f,
        0.5f, 0.7f, 0.0f,
        0.5f, 0.7f, 0.0f,
        0.9f, 0.9f, 0.9f,
        0.5f, 0.7f, 0.0f,
        0.5f, 0.7f, 0.0f,
        0.9f, 0.9f, 0.9f,
        0.5f, 0.7f, 0.0f,
        0.5f, 0.7f, 0.0f,
        0.9f, 0.9f, 0.9f,
        0.5f, 0.7f, 0.0f,
        0.5f, 0.7f, 0.0f,

        0.2f, 0.3f, 0.4f,
        0.0f, 0.7f, 0.9f,
        0.0f, 0.7f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.0f, 0.7f, 0.9f,
        0.0f, 0.7f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.0f, 0.7f, 0.9f,
        0.0f, 0.7f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.0f, 0.7f, 0.9f,
        0.0f, 0.7f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.0f, 0.7f, 0.9f,
        0.0f, 0.7f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.0f, 0.7f, 0.9f,
        0.0f, 0.7f, 0.9f,

        0.7f, 0.2f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.2f, 0.3f, 0.4f,
        0.7f, 0.2f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.2f, 0.3f, 0.4f,
        0.7f, 0.2f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.2f, 0.3f, 0.4f,
        0.7f, 0.2f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.2f, 0.3f, 0.4f,
        0.7f, 0.2f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.2f, 0.3f, 0.4f,
        0.7f, 0.2f, 0.9f,
        0.2f, 0.3f, 0.4f,
        0.2f, 0.3f, 0.4f,

        0.7f, 0.7f, 0.7f,
        0.8f, 0.0f, 0.0f,
        0.4f, 0.4f, 0.0f,

        0.7f, 0.7f, 0.7f,
        0.4f, 0.4f, 0.0f,
        0.0f, 0.8f, 0.0f,

        0.7f, 0.7f, 0.7f,
        0.0f, 0.4f, 0.4f,
        0.0f, 0.8f, 0.0f,

        0.7f, 0.7f, 0.7f,
        0.8f, 0.0f, 0.0f,
        0.4f, 0.0f, 0.4f,

        0.7f, 0.7f, 0.7f,
        0.4f, 0.0f, 0.4f,
        0.0f, 0.0f, 0.8f,

        0.7f, 0.7f, 0.7f,
        0.0f, 0.4f, 0.4f,
        0.0f, 0.0f, 0.8f,

    };
}; // namespace enemyModel

#endif // ENEMY_MODEL_HPP