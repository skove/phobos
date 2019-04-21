#include <iostream>

#include "Scene.h"

#define FPS_UPDATE_THRESHOLD 0.25f

Scene::Scene(
    Renderer *renderer,
    AssetsManager *assetsMgr,
    InputHandler *inputHandler)
    : SceneNode(this),
      m_renderer(renderer),
      m_assetsMgr(assetsMgr),
      m_inputHandler(inputHandler)
{
  m_scene = this;
  m_uiMgr = new UIManager(m_renderer, m_assetsMgr);
  m_particleSystem = new ParticleSystem(m_renderer);

  m_fpsLabel = new UILabel(m_uiMgr, "", glm::vec2(16.0f, renderer->getHeight() - 24.0f));
  m_uiMgr->attachNode(m_fpsLabel);
}

Scene::~Scene()
{
  delete m_particleSystem;
  delete m_uiMgr;
}

void Scene::render()
{
  m_renderer->setProjectionType(PROJECTION_TYPE_PERSPECTIVE);
  SceneNode::render();
  m_particleSystem->render();

  m_renderer->setProjectionType(PROJECTION_TYPE_ORTHO);
  m_uiMgr->render();
}

void Scene::update(float timeDelta)
{
  SceneNode::update(timeDelta);
  m_particleSystem->update(timeDelta);

  // checkCollisions();

  m_fpsUpdateCounter += timeDelta;
  if (m_fpsUpdateCounter > FPS_UPDATE_THRESHOLD) {
    m_fpsUpdateCounter = 0.0f;
    m_fpsLabel->text = "FPS: " + std::to_string(int(1.0f / timeDelta));
  }
}

void Scene::checkCollisions()
{
  // TODO: collision system
  // for (
  //     std::vector<SceneNode *>::iterator it = m_nodes.begin();
  //     it != m_nodes.end();
  //     it++)
  // {

  // }
}