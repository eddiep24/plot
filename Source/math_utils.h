// in maths_utils.h
#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

namespace MathUtils
{

    const unsigned int VERTEX_ELEMENTS_NB = 6;

    /**
     * @brief Reassemble all elements of a vertex in a dedicated type
     * Contains, in the following order: x, y, z (position, in 3D), r, g, b (RGB colors)
     */
    typedef float vertex[VERTEX_ELEMENTS_NB];



    /**
     * @brief Returns the number of individual vertex arrays inside a vertices array
     *
     * @param vertices - an array of vertex
     * @return The number of the individual vertex arrays
     */
    const unsigned int getNbVertex(const vertex vertices[]);

    /**
     * @brief Sums and returns the number of individual elements stored in the vertices array
     *
     * @param vertices - an array of vertex
     * @return The sum of all individual elements stored in the vertices array
     */
    const unsigned int getNbElements(const vertex vertices[]);
}

#endif /* _MATHS_UTILS_H */
