#pragma once

#include <ECS/System/System.h>
#include <ECS/Component/CCamera.h>

class CameraSystem : public BaseSystem
{

private:
	//sf::View _playerView;
public:
	CameraSystem();

	void draw(sf::RenderWindow& window) override;
	void update(sf::Time deltaTime) override;
};