// in maths_utils.cpp
#include "math_utils.h"

const unsigned int MathUtils::getNbVertex(const MathUtils::vertex vertices[])
{
    return (unsigned int)(sizeof(*vertices) / MathUtils::VERTEX_ELEMENTS_NB);
}

const unsigned int MathUtils::getNbElements(const MathUtils::vertex vertices[])
{
    return MathUtils::getNbVertex(vertices) * VERTEX_ELEMENTS_NB;
}
