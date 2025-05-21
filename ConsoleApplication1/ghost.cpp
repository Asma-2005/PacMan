#include "ghost.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
bool ghost::isVulnerable() {
    return vulnerable;
}
ghost::ghost(int x, int y,string photo) {
    ghostWeakShape.loadFromFile("Assets/images/GhostBody32.png");
    ghostEyes.loadFromFile("Assets/images/GhostEyes32.png");

    ghostTex.loadFromFile(photo);
    ghostSprite.setTexture(ghostTex);
    ghostSprite.setTextureRect(IntRect(0, 0, 32, 30));
    ghostSprite.setScale(1.5, 1.5);
    ghostSprite.setPosition(g.NODESIZE * x, g.NODESIZE * y);
    frame = 0;
    speed = 1.0f;
    status = -1;
    moveCounter = 0;
    vulnerable = false;
    isFrozen = 0;
    counttime = 0;
    
}

void ghost::setVulnerable() {
    vulnerable = true;
    vulnerableClock.restart();    
    ghostSprite.setTexture(ghostWeakShape);
    ghostSprite.setTextureRect(IntRect(0, 0, 30, 30));
}
void ghost::movement(pacman& player, Graph& g,int id) {
    Vector2f ghostPos = ghostSprite.getPosition();
    Vector2f pacmanPos = player.pacsprite.getPosition();


    int ghostI = static_cast<int>(ghostPos.y) / Graph::NODESIZE;
    int ghostJ = static_cast<int>(ghostPos.x) / Graph::NODESIZE;
    int pacmanI = static_cast<int>(pacmanPos.y) / Graph::NODESIZE;
    int pacmanJ = static_cast<int>(pacmanPos.x) / Graph::NODESIZE;

    int ghostNodeId = ghostI * Graph::COLS + ghostJ;
    int pacmanNodeId = pacmanI * Graph::COLS + pacmanJ;
    if (checkCollision(player)) {
            if (vulnerable) {
                isDying = 1;
                path = g.bfs(ghostNodeId, homeId,0);
                moveCounter = 20;
                ghostSprite.setTexture(ghostEyes);
            }
            else {
                ghost::isVisible = false;
                player.pacsprite.setTexture(player.pacDeath);
                player.isDying = 1;
            }
        
    }   

    // get char current pos
   
    // positions to node indices(adj list)
   
    if (vulnerable && vulnerableClock.getElapsedTime().asSeconds() > 10.0f && !isDying) {
        vulnerable = false;
        ghostSprite.setTexture(ghostTex); 
    }
    moveCounter++;
    if (moveCounter >= 20) {  // calc new path every 20 frames(3shan el ghost maydokhsh)
        int targetNodelId; 
        if (vulnerable && !isDying) {
            float maxDist = -1;
            int farthestNode = ghostNodeId;
            for (int i = 0; i < Graph::ROWS; i++) {
                for (int j = 0; j < Graph::COLS; j++) {
                    if (g.pacmanMatrix[i][j] != 0) {
                        float distX = static_cast<float> (j * Graph::NODESIZE) - pacmanPos.x;
                        float distY = static_cast<float> (i * Graph::NODESIZE) - pacmanPos.y;
                        float dist = distX * distX + distY * distY;
                        if (dist > maxDist) {
                            maxDist = dist;
                            farthestNode = i * Graph::COLS + j;
                        }
                    }
                }
            }
            targetNodelId = farthestNode;
            if (id == 0)
            {
                path = g.bfs(ghostNodeId, targetNodelId, id);
            }
            else if (id == 1)
            {
                path = g.a_star(ghostNodeId, targetNodelId);

            }
            else
            {
                path = g.dijkstra(ghostNodeId, targetNodelId);

            }
            moveCounter = 0;
        }
        else if (isDying) {
            targetNodelId = homeId;
            speed = 1.0f;
            if (ghostNodeId == homeId) {
                isFrozen = 1;
                isDying = 0;
                freezeClock.restart();
                ghostSprite.setTexture(ghostTex);
				path.clear();
            }
            else {
                if (id == 0)
                {
                    path = g.bfs(ghostNodeId, targetNodelId, id);
                }
                else if (id == 1)
                {
                    path = g.a_star(ghostNodeId, targetNodelId);

                }
                else
                {
                    path = g.dijkstra(ghostNodeId, targetNodelId);

                }
                moveCounter = 0;
            }
        }
        else if (isFrozen) {
            
            ghostSprite.move(0, 0);
            speed = 0.0f;
			cout << counttime << endl;
            if (freezeClock.getElapsedTime().asSeconds() >= 0.5f) {
                counttime++;
                freezeClock.restart();
            }
            if (counttime>10)
            {
                speed = 1.0f;
                isFrozen = 0;
                vulnerable = 0;
                counttime = 0;
            }
        }
        else {
            targetNodelId = pacmanNodeId;
            if (id == 0)
            {
                path = g.bfs(ghostNodeId, targetNodelId, id);
            }
            else if(id==1)
            {
                path = g.a_star(ghostNodeId, targetNodelId);

            }
            else
            {
                path = g.dijkstra(ghostNodeId, targetNodelId);

            }
            moveCounter = 0;
        }
        
    }

    // a valid path with at lEAST one node
    if (!path.empty() && path.size() > 1) {
        // get the next node
        int nextNodeId = path[1];
        int nextI = nextNodeId / Graph::COLS;
        int nextJ = nextNodeId % Graph::COLS;

        if (ghostSprite.getPosition().y == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint)
        {
            if (nextJ > ghostJ) {
                status = 0;  // right
            }
            if (nextJ < ghostJ) {
                status = 1;  // left

            }
        }
        if (ghostSprite.getPosition().x == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint)
        {
            if (nextI < ghostI) {
                status = 2;  // up
            }
            if (nextI > ghostI) {
                status = 3;  // down
            }
        }




        if (status == 0 && (g.pacmanMatrix[ghostI][ghostJ + 1] != 0 || (ghostSprite.getPosition().x != Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint && ghostSprite.getPosition().y == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint && g.pacmanMatrix[ghostI][ghostJ + 1] == 0))) {  // Right
            frame++;
            int frameIndex = frame % 2;
            ghostSprite.setTextureRect(IntRect(frameIndex * 32, 0, 32, 30));
            ghostSprite.move(speed, 0);
        }
        else if (status == 1 && (g.pacmanMatrix[ghostI][ghostJ - 1] != 0 || (ghostSprite.getPosition().x != Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint && ghostSprite.getPosition().y == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint && g.pacmanMatrix[ghostI][ghostJ - 1] == 0))) {  // Left
            frame++;
            int frameIndex = frame % 2;
            ghostSprite.setTextureRect(IntRect((frameIndex + 2) * 32, 0, 32, 30));
            ghostSprite.move(-speed, 0);
        }
        else if (status == 2 && (g.pacmanMatrix[ghostI - 1][ghostJ] != 0 || (ghostSprite.getPosition().x == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint && ghostSprite.getPosition().y != Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint && g.pacmanMatrix[ghostI - 1][ghostJ] == 0))) {  // Up
            frame++;
            int frameIndex = frame % 2;
            ghostSprite.setTextureRect(IntRect((frameIndex + 4) * 32, 0, 32, 30));
            ghostSprite.move(0, -speed);
        }
        else if (status == 3 && (g.pacmanMatrix[ghostI + 1][ghostJ] != 0 || (ghostSprite.getPosition().x == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint && ghostSprite.getPosition().y != Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint && g.pacmanMatrix[ghostI + 1][ghostJ] == 0))) {  // Down
            frame++;
            int frameIndex = frame % 2;
            ghostSprite.setTextureRect(IntRect((frameIndex + 6) * 32, 0, 32, 30));
            ghostSprite.move(0, speed);
        }
        else {
            status = -1;
        }

    }
}

bool ghost::checkCollision(pacman& player) {
    FloatRect ghostBounds = ghostSprite.getGlobalBounds();
    FloatRect pacmanBounds = player.pacsprite.getGlobalBounds();
    //cout << "pac dying: " <<   player.isDying << endl;
    // very basic logic i'll edit it soon
    if (ghostBounds.intersects(pacmanBounds)) {
        //   player.isDying = true;
        return true;
    }

}

void ghost::draw(RenderWindow& window) {
    if (ghost::isVisible)
    {
        window.draw(ghostSprite);
    }
}