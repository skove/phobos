#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "CollisionHull.h"

class Scene;
class SceneGroup;

class SceneNode
{
public:
  SceneNode(Scene *scene);
  virtual ~SceneNode();

  virtual void render();
  virtual void update(float timeDelta);

  void attachNode(SceneNode *node);
  void releaseNode(SceneNode *node);

  void move(const glm::vec3 &vec);
  void rotate(float angle, const glm::vec3 &vec);

  virtual void onCollision(SceneNode *collider) {}
  void grabCollisionHulls(std::vector<CollisionHull *> &hulls);
  void grabChildrenCollisionHulls(std::vector<CollisionHull *> &hulls);
  inline CollisionHull *getCollisionHull() { return m_collisionHull; }

  glm::mat4 localTransform;

protected:
  friend class Scene;

  glm::mat4 getAbsoluteTransform();

  std::vector<SceneNode *> m_nodes;
  CollisionHull *m_collisionHull;
  SceneNode *m_parent;

  inline Scene *getScene()
  {
    return m_scene;
  }

private:
  Scene *m_scene;
};
