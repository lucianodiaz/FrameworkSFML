#include "CameraSystem.h"


CameraSystem::CameraSystem()
{
}

void CameraSystem::draw(sf::RenderWindow& window)
{
	auto entitiesWithCamera = _entityManager->getEntitiesWithComponent<CCamera>();
	
	for (auto e : entitiesWithCamera)
	{
		window.setView(e->getComponent<CCamera>()->Camera);
	}
}

void CameraSystem::update(sf::Time deltaTime)
{
    auto entitiesWithCamera = _entityManager->getEntitiesWithComponent<CCamera>();

    for (auto e : entitiesWithCamera)
    {
        auto camera = e->getComponent<CCamera>();
        EntityBase* ownerEntityBase = &camera->getOwner();
        if (auto targetEntity = dynamic_cast<Actor*>(ownerEntityBase))
        {
            // Aplica el "lag" al movimiento de la cámara
            sf::Vector2f desiredPosition = targetEntity->ComponentTransform->position;
            sf::Vector2f cameraPosition = camera->Move;

            camera->Move = cameraPosition + (desiredPosition - cameraPosition) * camera->LagFactor;

            // Actualiza la vista de la cámara
            camera->Camera.setCenter(camera->Move);
            /*No se Como cambiar el size de la camara supongo que una vez seteado no lo deberia cambiar
            voy a suponer que Como esta deberia funcionar y en el futuro ver la posibilidad de agregar mas view simultaneamente
            y ver como se comporta hasta ahora el codigo*/
         /*   camera->Camera.setSize(camera->Size);*/
            camera->Camera.setRotation(camera->Angle);

            camera->Camera.zoom(camera->Zoom);
            camera->Zoom = 1.0f;
        }
    }

}
