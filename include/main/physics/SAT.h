#include <vector>
#include "main/components/collidertypes/BoxCollider.h"
#include "main/components/collidertypes/CircleCollider.h"
#include "main/components/collidertypes/PolygonCollider.h"

class SAT
{
    public:
        static bool CircleCircle(Collider* c1, Collider* c2);
        static bool BoxBox(Collider* b1, Collider* b2);
        static bool BoxCircle(Collider* b1, Collider* c1);
        static bool PolygonCircle(Collider* p1, Collider* c1);
        static bool PolygonBox(Collider* p1, Collider* b1);
        static bool PolygonPolygon(Collider* p1, Collider* p2);
    private:
        struct Projection {
            float min;
            float max;
        };

        static Projection Project(std::vector<Vec2> vertices, const Vec2 axis);
        static Projection CircleProject(CircleCollider* c, const Vec2 axis);
        static std::vector<Vec2> GetVertices(BoxCollider* b);
        static std::vector<Vec2> GetNormals(std::vector<Vec2> vertices);
};