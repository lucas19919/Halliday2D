# Halliday2D
### A custom 2D Physics Engine built in C++.

---

## Tech Demos
#### Plinko
![](https://github.com/lucas19919/PhysicsEngine/blob/main/images/gifs/plinko.gif)

#### Double Pendulum
![](https://github.com/lucas19919/PhysicsEngine/blob/main/images/gifs/pendulum.gif)

---

## Overview

### Using:
 - Raylib for rendering
 - SAT for collision detection
 - Sutherland-Hodgman Polygon Clipping for contact points
 - Spatial Hashing for optimization
 - nlohmann/json for JSON Parsing
 - IMGUI for UI

### Features:
 - Rigidbody Physics
	- Linear
	- Angular
 - Circle, Box and Convex Polygons Colliders
 - Sequential Impulse Solver
 - Constraints
	- Distance
	- Fixed and Rolling Pins
	- Joints
	- Motor
 - Controllers
	- Motor Controller
 - Engine Editor
	- Body Placing
	- Constraint Building
	- Debugging
	- JSON Scene Loading and Saving

---

## Building the Project

1.  **Clone the repository:** `git clone https://github.com/Lucas19919/PhysicsEngine.git`
2.  **Navigate to the directory:** `cd PhysicsEngine`
3.  **Configure and build:**
    `mkdir build`
    `cd build`
    `cmake ..`
    `cmake --build .`

---

## Usage

### GameObjects
A **GameObject** is the fundamental base object of the engine. This was based on Unity's system of **GameObjects** and works in a similar way. Each **GameObject** holds **Components** and **Constraints**, which define how the **GameObject** interacts with the physics environment.

#### Groups
A **Group** is essentially a folder of objects. A **Group** can be created via the **Hierarchy**.

#### Generators
A **Generator** is a specific type of **GameObject** which can generate an $m \times n$ grid of **GameObjects**. A **Generator** includes definitions for the spacing, start position, and the template object to be duplicated.

#### Prefabs
A **Prefab** is a saved **Group** of objects which can be instantiated all at once. An example of this is the default car **Prefab** in the **Prefabs** folder. **Prefabs** are created by saving a **Group**.

---

### Components
A **Component** is added to a **GameObject** and defines various elements and the interaction with the physics environment.

#### 1. Transform
The **Transform** is the default **Component** and defines the position, rotation, and scale of the object. The **Transform** is fundamental and, hence, cannot be deleted.

#### 2. Rigidbody
The **Rigidbody** is the core of the physics engine. Here all physics parameters are set, which are then used by the solver. The **Rigidbody** is divided into 3 sections:

* **Properties:** Mass, Restitution, Friction, Inertia, Is Gravity Applied?
* **Linear State:** Velocity Vector, Acceleration Vector, Net Force
* **Angular State:** Angular Velocity, Angular Acceleration, Net Torque

> **Note:** A **Rigidbody** with 0 mass will be considered a static object. Applying a **Net Force** or **Torque** does not mean continual application. A **Net Force** or **Torque** are integrated at the beginning of each frame, and are cleared at the end of every frame.

#### 3. Collider
A **Collider** is the primary collision object in the engine. It does not need to match with the render shape of the object.
* **Circle:** Defines a circular collider by the radius.
* **Box:** Defines a rectangular collider by a 2D size vector.
* **Polygon:** Defines a convex polygon by a list of points (not currently supported in the editor).

#### 4. Renderer
Defines the rendered view of the **GameObject** and its RGBA color.

#### 5. Controller
Used to control **Motors** via keybinds. Currently a premature **Component** hardcoded to *A* and *D*.

---

### Constraints
A **Constraint** defines the motion of a **GameObject**.

* **Distance:** Defines the set distance between 2 **GameObjects**.
* **Pins:** Represents a point where an object is fixed (Fixed or Rolling in **X** or **Y**).
* **Joints:** Acts as a joint between objects; allows free rotation.
* **Motor:** Acts as a small motor applying a set torque per frame.

---

## Keybinds

* **Ctrl + N:** Create new Scene
* **Ctrl + S:** Save Scene
* **G:** Select translation Gizmo
* **E:** Select rotation Gizmo
* **S:** Select scaling Gizmo
* **R:** Reset Scene
* **Space:** Pause Scene
* **DELETE:** Delete selected GameObject

---

## Editor
![](https://github.com/lucas19919/PhysicsEngine/blob/main/images/editor/editor.png)

The editor is made up of various "Panels". To manipulate a scene, use the top bar:
* **File:** New, Save, or Load scenes.
* **Edit:** Undo and Redo functionality.
* **Theme:** Switch themes (RETRO is default).
* **Window:** Close panels or reset layout.
* **World:** Set physics environment size in meters or pixels.

### Editor Panels
* **Hierarchy:** List of all current **GameObjects**, **Generators**, or **Prefabs**.
* **Inspector:** Edit **Components** and **Constraints** attached to an object.
* **Performance:** Breakdown of solver timing (**Integration**, **Narrowphase**, **Broadphase**) and current FPS.
* **Viewport:** The main scene view. Supports panning (Middle Mouse) and zooming (Scroll).
* **Scene Manager:** Load scenes from assets or custom folders.
* **Debug:** Toggle debug rendering modes and physics configurations.
* **Constraints:** Manage, highlight, and delete active scene constraints.

---

# Engine and Architechture: //OUT OF DATE

Currently the engine includes circles, rectangles and convex polygons, and calculates both linear and rotational physics. The rigidbody includes forces, torque, mass, inertia and so on.

Each physics body is instantiated as a GameObject. A GameObject can hold the following components: TransformComponent, Rigidbody, Collider, Renderer. This was based on Unity's system of GameObjects and components. Each GameObject can then be given further constraints: Distance, Pin (fixed or rolling), Joint. Each of these constraints are assigned post instatantion of the GameObjects, and GameObjects are assigned via ID to them at launch. 

Scenes are loaded via a path in main to the assets folder using nlohmann/json as a json parser. Please see assets/demos/ ... for various demo's of the engine, and examples of how to create levels.

Physics are handled within a World class, which is created at launch and contains all GameObjects and Constraints. The world is updated, via the World.step(dt) method, which handles physics via the following pipeline:  

- Clear all caches
- Update velocity from acceleration and external forces
- Update the broadphase, updating the spatial hash grid to locate GameObjects
- Generate candidate pairs from the grid, determined via checking AABB bounds
- Build contact constraints and gather all rigidbody data
- Warmstart all constraints
- Solve all constraints iteratively via a impulse solver
- Update positions from velocity
- Update sleep conditions for rigidbodies
- Cleanup

The collision handling is done via SAT collision detection and with Sutherland Hogemann polygon clipping to find collision points. The solver class is first called to generate a collision manifold, sorting the collision by the collider types (ie circle circle, or box circle ...). Once sorted the manifold is calculated, containing contact points, collision normals, and penetration depths. This data is then collected in a contact constraint, which is then resolved by the solver. Based on the collision and properties of the RigidBody, an impulse is then calculated. The impulse is then applied along the collision normal to each collision RigidBody.

---

## To Do
1.  Rework **Constraint** solver to separate position/velocity
2.  Motor controller (for robotic arms, etc.)
3.  CCD (Continuous Collision Detection)
