#pragma once

#include <vector> 

namespace mozmath 
{
    // Utilise la subdivision de Catmull-Clark.
    // Le principe est de créer une sphère à partir d'un cube.
    void CalculateSphere(std::vector<float>& vertices, unsigned int subdivisionCount);
}