//
//  FloorTexture.hpp
//  Game_PC
//
//  Created by Kris Temmerman on 19/06/2017.
//
//

#ifndef FloorMapping_hpp
#define FloorMapping_hpp

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "Tile.h"
#include "FloorTextureGenerator.hpp"
#include "RenderData.h"

struct VertexDataFloor {
    ci::vec3 position;
    ci::vec2 uv;
    
    
};

class FloorMapping
{


public:
    
    FloorMapping(){};
    void load();
    void setTileFloorMesh(TileRef tile,int numTiles);

	void draw(std::vector<TileRef> &tiles, std::vector<int>&indices, std::vector<ci::vec2> &positions, RenderDataRef renderdata);
	void startDraw(RenderDataRef renderdata);//ci::gl::FboRef shadowFBO,ci::mat4 &shadowMatrix);
    void stopDraw();
    ci::gl::GlslProgRef prog;
    ci::gl::TextureRef texture;
    FloorTextureGenerator generator;
};
#endif /* FloorTexture_hpp */
