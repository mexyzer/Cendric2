#include "Particles/ParticleUpdater.h"

#include "Particles/ParticleData.h"
#include "Particles/ParticleHelpers.h"

namespace particles {
	
void EulerUpdater::update(ParticleData *data, float dt) {
	for (int i = 0; i < data->countAlive; ++i) {
		data->acc[i] += globalAcceleration;
		data->vel[i] += dt * data->acc[i];
		data->pos[i] += dt * data->vel[i];
	}
}

void HorizontalCollisionUpdater::update(ParticleData *data, float dt) {
	const int endId = data->countAlive;

	for (int i = 0; i < endId; ++i) {
		float x = data->pos[i].x;
		float xPrime = x + dt * data->vel[i].x;

		if ((x < pos && xPrime >= pos) || (x > pos && xPrime <= pos)) {
			data->pos[i].x = pos;

			sf::Vector2f acc = data->acc[i];
			data->acc[i] = sf::Vector2f(-acc.x * bounceFactor, acc.y);

			sf::Vector2f vel = data->vel[i];
			data->vel[i] = sf::Vector2f(-vel.x * bounceFactor, vel.y);
		}
	}
}


void VerticalCollisionUpdater::update(ParticleData *data, float dt) {
	const int endId = data->countAlive;

	for (int i = 0; i < endId; ++i) {
		float y = data->pos[i].y;
		float yPrime = y + dt * data->vel[i].y;

		if ((y < pos && yPrime >= pos) || (y > pos && yPrime <= pos)) {
			data->pos[i].y = pos;

			sf::Vector2f acc = data->acc[i];
			data->acc[i] = sf::Vector2f(acc.x, -acc.y * bounceFactor);

			sf::Vector2f vel = data->vel[i];
			data->vel[i] = sf::Vector2f(vel.x, -vel.y * bounceFactor);
		}
	}
}


void AttractorUpdater::update(ParticleData *data, float dt) {
	const int endId = data->countAlive;
	int numAttractors = static_cast<int>(m_attractors.size());
	sf::Vector2f off;
	float dist;

	for (int i = 0; i < endId; ++i) {
		for (int j = 0; j < numAttractors; ++j) {
			off.x = m_attractors[j].x - data->pos[i].x;
			off.y = m_attractors[j].y - data->pos[i].y;
			dist = dot(off, off);
			dist = m_attractors[j].z / dist;

			data->acc[i] += off * dist;
		}
	}
}


void SizeUpdater::update(ParticleData *data, float dt) {
	const int endId = data->countAlive;

	for (int i = 0; i < endId; ++i) {
		float a = data->time[i].z;
		data->size[i].x = lerpFloat(data->size[i].y, data->size[i].z, a);
	}
}


void RotationUpdater::update(ParticleData *data, float dt) {
	const int endId = data->countAlive;

	for (int i = 0; i < endId; ++i) {
		float a = data->time[i].z;
		data->angle[i].x = lerpFloat(data->angle[i].y, data->angle[i].z, a);
	}
}


void ColorUpdater::update(ParticleData *data, float dt) {
	const int endId = data->countAlive;

	for (int i = 0; i < endId; ++i) {
		float a = data->time[i].z;
		data->col[i] = lerpColor(data->startCol[i], data->endCol[i], a);
	}
}


void TimeUpdater::update(ParticleData *data, float dt) {
	int endId = data->countAlive;

	if (endId == 0) return;

	for (int i = 0; i < endId; ++i) {
		data->time[i].x -= dt;
		data->time[i].z = 1.0f - (data->time[i].x / data->time[i].y);

		if (data->time[i].x < 0.0f) {
			data->kill(i);
			endId = data->countAlive;
		}
	}
}


void AnimationUpdater::update(ParticleData *data, float dt) {
	const int endId = data->countAlive;
	int animationSize = static_cast<int>(frames.size());

	for (int i = 0; i < endId; ++i) {
		float currentTime = data->frameTimer[i];
		currentTime += dt;
		
		if (currentTime >= frameTime) {
			currentTime = std::fmod(currentTime, frameTime);

			int frame = data->frame[i];
			if (frame + 1 < animationSize) {
				frame++;
			}
			else if (looped) {
				frame = 0;
			}
			data->frame[i] = frame;
			data->texCoords[i] = frames[frame];
		}

		data->frameTimer[i] = currentTime;
	}
}

}