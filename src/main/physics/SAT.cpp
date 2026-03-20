#include "main/physics/SAT.h"
#include "main/GameObject.h"
#include "main/components/Collider.h"

bool SAT::CircleCircle(Collider *c1, Collider *c2)
{
    float distanceSq = (c1->parent->transform.position - c2->parent->transform.position).MagSq();
    float radiusSum = static_cast<CircleCollider*>(c1)->radius + static_cast<CircleCollider*>(c2)->radius;

    if (distanceSq <= radiusSum * radiusSum) {
        return true;
    }
    else {
        return false;
    }
}

bool SAT::BoxBox(Collider *b1, Collider *b2)
{
    std::vector<Vec2> vertices1 = GetVertices(static_cast<BoxCollider*>(b1));
    std::vector<Vec2> vertices2 = GetVertices(static_cast<BoxCollider*>(b2));
    std::vector<Vec2> normals1 = GetNormals(vertices1);
    std::vector<Vec2> normals2 = GetNormals(vertices2);

    for (Vec2 axis : normals1)
    {
        Projection p1 = Project(vertices1, axis);
        Projection p2 = Project(vertices2, axis);

        if (p1.max < p2.min || p2.max < p1.min) {
            return false;
        }
    }

    for (Vec2 axis : normals2)
    {
        Projection p1 = Project(vertices1, axis);
        Projection p2 = Project(vertices2, axis);

        if (p1.max < p2.min || p2.max < p1.min) {
            return false;
        }
    }    

    return true;
}

bool SAT::BoxCircle(Collider *b1, Collider *c1)
{
    CircleCollider* circle = static_cast<CircleCollider*>(c1);
    Vec2 center = circle->parent->transform.position;

    std::vector<Vec2> vertices = GetVertices(static_cast<BoxCollider*>(b1));
    std::vector<Vec2> normals = GetNormals(vertices);

    Vec2 distAxis = center - vertices[0];
    float dist = (center - vertices[0]).MagSq();
    for (int i = 1; i < vertices.size(); i++)
    {
        if (dist > (center - vertices[i]).MagSq()) {
            distAxis = center - vertices[i];
            dist = (center - vertices[i]).MagSq();
        }
    }

    normals.push_back(distAxis.Norm());

    for (Vec2 axis : normals)
    {
        Projection p1 = Project(vertices, axis);
        Projection p2 = CircleProject(circle, axis);

        if (p1.max < p2.min || p2.max < p1.min) {
            return false;
        }
    }           

    return true;
}

bool SAT::PolygonCircle(Collider *p1, Collider *c1)
{

}

bool SAT::PolygonBox(Collider *p1, Collider *b1)
{

}

bool SAT::PolygonPolygon(Collider *p1, Collider *p2)
{
    //make poly collider

    return false;
    
    /*std::vector<Vec2> vertices1 = GetVertices(static_cast<PolygonCollider*>(p1));
    std::vector<Vec2> vertices2 = GetVertices(static_cast<PolygonCollider*>(p2));
    std::vector<Vec2> normals1 = GetNormals(vertices1);
    std::vector<Vec2> normals2 = GetNormals(vertices2);

    for (Vec2 axis : normals1)
    {
        Projection proj1 = Project(vertices1, axis);
        Projection proj2 = Project(vertices2, axis);

        if (proj1.max < proj2.min || proj2.max < proj1.min) {
            return false;
        }
    }

    for (Vec2 axis : normals2)
    {
        Projection proj1 = Project(vertices1, axis);
        Projection proj2 = Project(vertices2, axis);

        if (proj1.max < proj2.min || proj2.max < proj1.min) {
            return false;
        }
    }    

    return true;*/
}

SAT::Projection SAT::CircleProject(CircleCollider* c, const Vec2 axis)
{
    float centerDot = c->parent->transform.position.Dot(axis);
    
    return { 
        centerDot - c->radius, 
        centerDot + c->radius 
    };
}

SAT::Projection SAT::Project(std::vector<Vec2> vertices, const Vec2 axis)
{
    Projection project;

    project.min = axis.Dot(vertices[0]);
    project.max = project.min;
    
    for (int i = 0; i < vertices.size(); i++)
    {
        float dot = axis.Dot(vertices[i]);
        if (dot < project.min) project.min = dot;
        if (dot > project.max) project.max = dot;
    }

    return project;
}

std::vector<Vec2> SAT::GetVertices(BoxCollider *b)
{
    TransformComponent transform = b->parent->transform;

    std::vector<Vec2> vertices; //counter clockwise
    vertices.push_back(transform.position + Vec2(-b->size.x / 2, -b->size.y / 2)); //bot left
    vertices.push_back(transform.position + Vec2(b->size.x / 2, -b->size.y / 2)); //bot right
    vertices.push_back(transform.position + Vec2(b->size.x / 2, b->size.y / 2)); //top right    
    vertices.push_back(transform.position + Vec2(-b->size.x / 2, b->size.y / 2)); //top left    

    return vertices;
}

std::vector<Vec2> SAT::GetNormals(std::vector<Vec2> vertices)
{
    std::vector<Vec2> normals;
    for (int i = 0; i < vertices.size(); i++)
    {
        Vec2 line = vertices[(i + 1) % vertices.size()] - vertices[i];
        Vec2 pLine = Vec2(line.y, -line.x);
        normals.push_back(pLine.Norm());
    }

    return normals;
}