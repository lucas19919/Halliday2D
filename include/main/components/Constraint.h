#pragma once

class GameObject;

enum ConstraintType
{
    DISTANCE,
    PIN,
    JOINT,
    NORMAL,
    SHEAR
};

class Constraint
{
    public: 
        virtual ~Constraint() = default;
        virtual ConstraintType GetType() const = 0;
};