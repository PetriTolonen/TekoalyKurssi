#ifndef PATHFINDING_APP_H_
#define PATHFINDING_APP_H_
#include <Object.h>
#include <es_util.h>
#include <StreamTexture.h>
#include <Sprite.h>
#include <SpriteBatch.h>
#include <SpriteSheet.h>


class PathFindingApp : public yam2d::Object
{
// Public typedefs and methods:
public:
	PathFindingApp();
	virtual ~PathFindingApp();

	// Updates the app
	bool update(yam2d::ESContext* ctx, float deltaTime);

	// Draws the app
	void render(yam2d::ESContext *ctx);
	
	void quit()
	{
		m_appRunning = false;
	}

// Private member variables and methods:
private:
	bool m_appRunning;
	yam2d::Ref<yam2d::SpriteBatchGroup> m_batch;
	yam2d::Ref<yam2d::Texture> m_textureStartCase;
	yam2d::Ref<yam2d::StreamTexture> m_texturePathFound;
	yam2d::Ref<yam2d::Sprite> m_spriteStartCase;
	yam2d::Ref<yam2d::Sprite> m_spritePathFound;
	yam2d::Ref<yam2d::SpriteSheet> m_font;
	yam2d::Ref<yam2d::Texture> m_fontTexture;
	yam2d::Ref<yam2d::Text> m_text;
	
	bool m_searchCompleted;
	float m_searchTimer;

	bool doPathfinding(int startX, int startY, int endX, int endY);

	// Hidden copy constructor and assignment operator.
	PathFindingApp(const PathFindingApp&);
	PathFindingApp& operator=(const PathFindingApp&);
};

#endif

