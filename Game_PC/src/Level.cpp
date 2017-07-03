//
//  Level.cpp
//  Game_PC
//
//  Created by Kris Temmerman on 16/06/2017.
//
//

#include "Level.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;
void Level::setup(PlayerRef player1,PlayerRef player2)
{
    floorMap.load();
    objMap.load();
    levelSize = tileSize*numTiles;
    
    for(int y=0;y<numTiles;y++)
    {
        for(int x=0;x<numTiles;x++)
        {
            LevelTileRef tile = LevelTile::create();
            tile->setup(x,y,tileSize);
            floorMap.setTileFloorMesh(tile,numTiles);
            objMap.setTileFloorMesh(tile,numTiles);
            tiles.push_back(tile);
        }
    
    }
    
    grassRenderer.setup();
    
    player1Level.tiles =tiles;
    player1Level.player = player1;
    player1Level.tileSize =tileSize;
    player1Level.numTiles=numTiles;

    player1Level.setup();
    
    
    
    player2Level.tiles =tiles;
    player2Level.player = player2;
    player2Level.tileSize =tileSize;
    player2Level.numTiles=numTiles;
    player2Level.setup();
}

void Level::updatePlayerPositions(glm::vec2 deviderLineP1,glm::vec2 deviderLineP2)
{

    player1Level.update(deviderLineP1,deviderLineP2);
    player2Level.update(deviderLineP2,deviderLineP1);

}
void Level::update()
{
//resolve tile physics;
   
    currentTime =getElapsedSeconds();
    for(auto tile:tiles)
    {
    
        tile->update();
    }
}

void Level::draw(int playerID,ci::gl::FboRef shadowFBO,ci::mat4 &shadowMatrix)
{
    if(playerID==0)
    {
        
        grassRenderer.mGlsl->bind();
        grassRenderer.mGlsl->uniform("time", (float)currentTime/20);
        grassRenderer.texture->bind(0);
        shadowFBO->getDepthTexture()->bind(1);
        
          grassRenderer.mGlsl->uniform( "uShadowMatrix",  shadowMatrix );
        
        player1Level.drawGrass();
        shadowFBO->getDepthTexture()->unbind();
        
        
        
        floorMap.startDraw(shadowFBO,shadowMatrix);
        player1Level.drawFloor();
        floorMap.stopDraw();
        shadowFBO->getDepthTexture()->unbind();
       // player1Level.draw();
    }
    else
    {
       grassRenderer.mGlsl->bind();
        
       
        grassRenderer.mGlsl->uniform("time", (float)currentTime/20);
        grassRenderer.texture->bind(0);
        shadowFBO->getDepthTexture()->bind(1);
        grassRenderer.mGlsl->uniform( "uShadowMatrix",  shadowMatrix );
        player2Level.drawGrass();
        
        shadowFBO->getDepthTexture()->unbind();
        
        
        
        
        floorMap.startDraw(shadowFBO,shadowMatrix);
        player2Level.drawFloor();
        floorMap.stopDraw();
        shadowFBO->getDepthTexture()->unbind();
        
        //player2Level.draw();
    }
}

void Level::drawShadow(int playerID)
{
    if(playerID==0)
    {
        
        grassRenderer.mGlslShadow->bind();
        grassRenderer.mGlslShadow->uniform("time", (float)currentTime/20);
        grassRenderer.texture->bind(0);
        player1Level.drawGrass();
        
        
        grassRenderer.texture->unbind();
        gl::getStockShader( gl::ShaderDef().color() )->bind() ;

        
        
        // player1Level.draw();
    }
    else
    {
        grassRenderer.mGlslShadow->bind();
        grassRenderer.mGlslShadow->uniform("time", (float)currentTime/20);
        grassRenderer.texture->bind(0);

        player2Level.drawGrass();
       grassRenderer.texture->unbind();
        gl::getStockShader( gl::ShaderDef().color() )->bind() ;

        
    }
}