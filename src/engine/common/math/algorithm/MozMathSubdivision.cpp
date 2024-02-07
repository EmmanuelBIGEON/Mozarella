#include "MozMathSubdivision.h"

#include <set> 
#include <glm/ext.hpp>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cmath>

using namespace mozmath;

struct Edge 
{
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 edge_point;
    bool edge_point_set;

    Edge() : edge_point_set(false) {}
    Edge(const glm::vec3& point1, const glm::vec3& point2) : edge_point_set(false) { p1 = point1; p2 = point2; }
    const glm::vec3& GetP1() const { return p1; }
    const glm::vec3& GetP2() const { return p2; }

    glm::vec3 MiddlePoint() const{ return ((p1 + p2)/ static_cast<float>(2)); }
};

struct Face 
{
    std::vector<Edge> _edges;
    glm::vec3 face_point;
};

struct Triangle 
{
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    Triangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3) 
    { p1 = point1; p2 = point2; p3 = point3;}
};

struct Mesh
{
    std::vector<Face> _faces;
    std::vector<Triangle> _triangles;
};

bool IsSame(Edge* e1, Edge*e2);
bool IsShareOneVertex(Edge* e1, Edge*e2);
void roundVec3(glm::vec3&, unsigned int digits_after_comma = 7);
std::vector<Edge> ConnectedEdges(const glm::vec3& point, Mesh* mesh);
std::vector<Face> ConnectedFaces(const glm::vec3& point, Mesh* mesh);

// Donne la position du nouveaux points.
std::map<glm::vec3, glm::vec3> mapPoints_to_NewPoints;
std::vector<std::pair<glm::vec3, glm::vec3>> vecPoints_to_NewPoints;



// Utilise la subdivision de Catmull-Clark.
Mesh Subdivide(Mesh& mesh);

// Le principe est de créer une sphère à partir d'un cube.
void mozmath::CalculateSphere(std::vector<float>& vertices, unsigned int subdivisionCount)
{
    // On définit un cube de départ avec 6 faces interconnectées.
    glm::vec3 p1 = {2.5f, -2.5f, -2.5f}; // arriere bas droit.
    glm::vec3 p2 = {2.5f, 2.5f, -2.5f}; // arriere haut droit
    glm::vec3 p3 = {-2.5f, 2.5f, -2.5f}; // arriere haut gauche
    glm::vec3 p4 = {-2.5f, -2.5f, -2.5f}; // arriere bas gauche
    glm::vec3 p5 = {2.5f, -2.5f, 2.5f}; // avant bas droit
    glm::vec3 p6 = {2.5f, 2.5f, 2.5f}; // avant haut droit
    glm::vec3 p7 = {-2.5f, 2.5f, 2.5f}; // avant haut gauche
    glm::vec3 p8 = {-2.5f, -2.5f, 2.5f}; // avant bas gauche

    // On part d'un cube;
    Mesh cube;

    cube._faces.push_back({{{p1, p2}, {p2, p3}, {p3, p4}, {p4, p1}}}); // face arriere
    cube._faces.push_back({{{p5, p6}, {p6, p7}, {p7, p8}, {p8, p5}}}); // face avant
    cube._faces.push_back({{{p1, p5}, {p5, p6}, {p6, p2}, {p2, p1}}}); // face droite
    cube._faces.push_back({{{p4, p8}, {p8, p7}, {p7, p3}, {p3, p4}}}); // face gauche
    cube._faces.push_back({{{p2, p6}, {p6, p7}, {p7, p3}, {p3, p2}}}); // face haut
    cube._faces.push_back({{{p1, p5}, {p5, p8}, {p8, p4}, {p4, p1}}}); // face bas

    auto subdividedMesh = cube;

    for(int i = 0 ; i < subdivisionCount ; i++)
    {
        subdividedMesh = Subdivide(subdividedMesh);
    }

    for (auto& triangle : subdividedMesh._triangles)
    {
        vertices.push_back(triangle.p1.x);
        vertices.push_back(triangle.p1.y);
        vertices.push_back(triangle.p1.z);
        vertices.push_back(triangle.p2.x);
        vertices.push_back(triangle.p2.y);
        vertices.push_back(triangle.p2.z);
        vertices.push_back(triangle.p3.x);
        vertices.push_back(triangle.p3.y);
        vertices.push_back(triangle.p3.z);
    }
}


Mesh Subdivide(Mesh& mesh)
{
    Mesh newMesh;
    
    // Pour chaque face on calcule le face point.
    // (se réferer au wiki https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface)
    for(auto& face : mesh._faces)
    {
        // Pour calculer le face point on fait la moyenne de tous les points de la face.
        std::vector<glm::vec3> unique_points_in_face;

        for(auto& edge : face._edges) 
        {
            if(std::find(unique_points_in_face.begin(), unique_points_in_face.end(), edge.p1) == unique_points_in_face.end())
                unique_points_in_face.push_back(edge.p1);

            if(std::find(unique_points_in_face.begin(), unique_points_in_face.end(), edge.p2) == unique_points_in_face.end())
                unique_points_in_face.push_back(edge.p2);
        }

        // On calcule le face point.
        face.face_point = glm::vec3(0.0f);
        for(const auto& point : unique_points_in_face) 
            face.face_point += point;
        face.face_point = face.face_point / static_cast<float>(unique_points_in_face.size());
        roundVec3(face.face_point);
        
    }
    
    for(auto& face : mesh._faces)
    {
        
        Face* currentface = &face;
        for(auto &edge : face._edges)
        {
            bool found = false;
            for(auto& face2 : mesh._faces)
            {
                if(&face2 == currentface) continue;

                for(auto& edge2 : face2._edges)
                {
                    if(IsSame(&edge, &edge2))
                    {
                        found = true;
                        // On a trouvé la face correspondante au edge ! (un edge est la séparation de deux faces)
                        edge.edge_point = (currentface->face_point + face2.face_point + edge.GetP1() + edge.GetP2()) / 4.0f;
                        edge.edge_point_set = true;
                        roundVec3(edge.edge_point);

                        edge2.edge_point = edge.edge_point;
                        edge2.edge_point_set = true;
                        break;
                    }

                }

            }
            if(!found)
            {
                std::cout << "Impossible !" << std::endl;
                return mesh;
            }
        }
    }
    // On récupère la liste de tous les points.
    std::vector<glm::vec3> original_points;
    for(const auto& face : mesh._faces)
        for(const auto &edge : face._edges)
        {
            if(std::find(original_points.begin(), original_points.end(), edge.p1) == original_points.end())
                original_points.push_back(edge.p1);
            if(std::find(original_points.begin(), original_points.end(), edge.p2) == original_points.end())
                original_points.push_back(edge.p2);

        }

    for(const auto &original_point : original_points)
    {
        
        // La moyenne des face_points des faces connectées. (nommée F)
        std::vector<Face>& connected_faces = ConnectedFaces(original_point, &mesh);
        glm::vec3 F(0.0f);
        for(const auto& face : connected_faces)
            F += face.face_point;
        F = F / static_cast<float>(connected_faces.size());

        // La moyenne des milieux des edges connectées. (nommée R)
        std::vector<Edge>& connected_edges = ConnectedEdges(original_point, &mesh);
        glm::vec3 R(0.0f);
        for(auto& edge : connected_edges)
            R += edge.MiddlePoint();
        R = R / static_cast<float>(connected_edges.size());

        // (F + 2R + (n - 3)P)/n
        glm::vec3 new_point = (F + 2.0f * R + (static_cast<float>(connected_edges.size()) - 3.0f)* original_point) / static_cast<float>(connected_edges.size());
        // mapPoints_to_NewPoints[original_point] =  new_point;
        roundVec3(new_point);
        vecPoints_to_NewPoints.push_back(std::make_pair(original_point, new_point));
    }

    // On forme la nouvelle mesh ! 
    for(auto &face : mesh._faces)
    {
        int facecree = 0;
        // Determine si le point a déjà été process, il ne peut pas y avoir deux faces sur le même point (par face originale).
        std::vector<glm::vec3> processed_points;

        for(auto &edge : face._edges)
        {
            // Traitement pour p1
            if(std::find(processed_points.begin(), processed_points.end(), edge.p1) == processed_points.end())
            {
                processed_points.push_back(edge.p1);
                glm::vec3 newpoint;
                for(const auto& pair : vecPoints_to_NewPoints)
                {
                    if(pair.first == edge.p1)
                    {
                        newpoint = pair.second;
                        break;
                    }
                }
            
                // On cherche le edge qui va bien.
                for(auto &edge2 : face._edges)
                {
                    // que ce soit le premier ou le deuxieme point, ce qui compte c'est que c'est le même.
                    if(IsShareOneVertex(&edge2, &edge) && ((edge2.p1 == edge.p1) || (edge2.p2 == edge.p1)))
                    {
                        facecree++;
                        // On peut enfin construire la face.. dieu merci.
                        Face newface;
                        newface._edges.emplace_back(face.face_point, edge.edge_point);
                        newface._edges.emplace_back(edge.edge_point, newpoint);
                        newface._edges.emplace_back(newpoint, edge2.edge_point);
                        newface._edges.emplace_back(edge2.edge_point, face.face_point);
                        // facepoint => edge_point => newpoint => edge2_point qui revient à facepoint.

                        newMesh._faces.push_back(newface);
                        newMesh._triangles.emplace_back(face.face_point, edge.edge_point, newpoint);
                        newMesh._triangles.emplace_back(face.face_point, edge2.edge_point, newpoint);
                        break;
                    }
                }
            }

            // Traitement pour p2
            if(std::find(processed_points.begin(), processed_points.end(), edge.p2) == processed_points.end())
            {
                processed_points.push_back(edge.p2);
                glm::vec3 newpoint;
                for(const auto& pair : vecPoints_to_NewPoints)
                {
                    if(pair.first == edge.p2)
                    {
                        newpoint = pair.second;
                        break;
                    }
                }

                // On cherche le edge qui va bien.
                for(auto &edge2 : face._edges)
                {
                    // que ce soit le premier ou le deuxieme point, ce qui compte c'est que c'est le même.
                    if(IsShareOneVertex(&edge2, &edge) && ((edge2.p1 == edge.p2) || (edge2.p2 == edge.p2)))
                    {
                        facecree++;
                        // On peut enfin construire la face.. dieu merci.
                        Face newface;
                        newface._edges.emplace_back(face.face_point, edge.edge_point);
                        newface._edges.emplace_back(edge.edge_point, newpoint);
                        newface._edges.emplace_back(newpoint, edge2.edge_point);
                        newface._edges.emplace_back(edge2.edge_point, face.face_point);
                        // facepoint => edge_point => newpoint => edge2_point qui revient à facepoint.

                        newMesh._faces.push_back(newface);
                        newMesh._triangles.emplace_back(face.face_point, edge.edge_point, newpoint);
                        newMesh._triangles.emplace_back(face.face_point, edge2.edge_point, newpoint);
                        break;
                    }
                }
            }
        }

        std::cout << "Faces crées : " << facecree << std::endl;
    }

    return newMesh;
}


bool IsSame(Edge* e1, Edge* e2)
{
    return ((e1->GetP1() == e2->GetP1()) && (e1->GetP2() == e2->GetP2())
    || (e1->GetP2() == e2->GetP1()) && (e1->GetP1() == e2->GetP2()));
}
bool IsShareOneVertex(Edge* e1, Edge*e2)
{
    return ((e1->GetP1() == e2->GetP1()) && (e1->GetP2() != e2->GetP2())
    || (e1->GetP2() == e2->GetP1()) && (e1->GetP1() != e2->GetP2())
    || (e1->GetP1() == e2->GetP2()) && (e1->GetP2() != e2->GetP1())
    || (e1->GetP2() == e2->GetP2()) && (e1->GetP1() != e2->GetP1()));
}

std::vector<Edge> ConnectedEdges(const glm::vec3& point, Mesh* mesh)
{
    std::vector<Edge> connectedEdges;

    for (auto& face : mesh->_faces)
    {
        for (auto& edge : face._edges)
        {
            if (edge.GetP1() == point || edge.GetP2() == point)
            {
                bool found = false;
                for(auto& tempedge : connectedEdges)
                {
                    if(IsSame(&tempedge, &edge))
                    {
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    connectedEdges.push_back(edge);
                }
            }
        }
    }


    return connectedEdges;
}

std::vector<Face> ConnectedFaces(const glm::vec3& point, Mesh* mesh)
{
    std::vector<Face> connectedFaces;

    for (auto& face : mesh->_faces)
    {
        for (auto& edge : face._edges)
        {
            if (edge.GetP1() == point || edge.GetP2() == point)
            {
                connectedFaces.push_back(face);
                break;
            }
        }
    }

    return connectedFaces;
}


void roundVec3(glm::vec3& vector, unsigned int digits_after_comma)
{
    float multiplier = std::pow(10.0f, digits_after_comma);

    vector.x = std::round(vector.x * multiplier) / multiplier;
    vector.y = std::round(vector.y * multiplier) / multiplier;
    vector.z = std::round(vector.z * multiplier) / multiplier;
}