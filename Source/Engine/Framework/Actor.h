#pragma once
#include "../Core/Core.h"
#include "../Renderer/Model.h"
#include <memory>

namespace ringo {
	class Actor {
	public:
		Actor() = default;
		Actor(const ringo::Transform& transform, std::shared_ptr<Model> model) :
			m_model{ model },
			m_transform{ transform } {}

		virtual void Update(float dt);
		virtual void Draw(ringo::Renderer& renderer);

		inline float GetRadius() { return m_model->GetRadius() * m_transform.scale; }
		virtual void OnCollision(Actor* other) {};

		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;

		ringo::Transform m_transform;
		std::string m_tag;
	protected:
		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		std::shared_ptr<Model> m_model;
	};
}