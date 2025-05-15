#include "ghost.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

ghost::ghost() {
    ghostTex.loadFromFile("Assets/images/enemy_spritethis.png");
    ghostSprite.setTexture(ghostTex);
    ghostSprite.setTextureRect(IntRect(0, 0, 30, 30));
    ghostSprite.setScale(1.5, 1.5);
    ghostSprite.setPosition(g.NODESIZE, g.NODESIZE);
    frame = 0;
    speed = 1.0f;  
    status = -1;
    moveCounter = 0;
}

void ghost::movement(pacman& player, Graph& g) {
    // get char current pos
    Vector2f ghostPos = ghostSprite.getPosition();
    Vector2f pacmanPos = player.pacsprite.getPosition();

    // positions to node indices(adj list)
    int ghostI = static_cast<int>(ghostPos.y) / Graph::NODESIZE;
    int ghostJ = static_cast<int>(ghostPos.x) / Graph::NODESIZE;
    int pacmanI = static_cast<int>(pacmanPos.y) / Graph::NODESIZE;
    int pacmanJ = static_cast<int>(pacmanPos.x) / Graph::NODESIZE;

    int ghostNodeId = ghostI * Graph::COLS + ghostJ;
    int pacmanNodeId = pacmanI * Graph::COLS + pacmanJ;

    moveCounter++;
    if (moveCounter >= 20) {  // calc new path every 20 frames(3shan el ghost maydokhsh)
        path = g.bfs(ghostNodeId, pacmanNodeId);
        moveCounter = 0;
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
            ghostSprite.setTextureRect(IntRect(frameIndex * 30, 0, 30, 30));
            ghostSprite.move(speed, 0);
        }
        else if (status == 1 && (g.pacmanMatrix[ghostI][ghostJ - 1] != 0 || (ghostSprite.getPosition().x != Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint && ghostSprite.getPosition().y == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint && g.pacmanMatrix[ghostI][ghostJ - 1] == 0))) {  // Left
            frame++;
            int frameIndex = frame % 2;
            ghostSprite.setTextureRect(IntRect((frameIndex + 6) * 30, 0, 30, 30));
            ghostSprite.move(-speed, 0);
        }
        else if (status == 2 && (g.pacmanMatrix[ghostI - 1][ghostJ] != 0 || (ghostSprite.getPosition().x == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint && ghostSprite.getPosition().y != Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint && g.pacmanMatrix[ghostI - 1][ghostJ] == 0))) {  // Up
            frame++;
            int frameIndex = frame % 2;
            ghostSprite.setTextureRect(IntRect((frameIndex + 4) * 30, 0, 30, 30));
            ghostSprite.move(0, -speed);
        }
        else if (status == 3 && (g.pacmanMatrix[ghostI + 1][ghostJ] != 0 || (ghostSprite.getPosition().x == Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].XstartPoint && ghostSprite.getPosition().y != Graph::nodesInfo[ghostI * Graph::COLS + ghostJ].YstartPoint && g.pacmanMatrix[ghostI + 1][ghostJ] == 0))) {  // Down
            frame++;
            int frameIndex = frame % 2;
            ghostSprite.setTextureRect(IntRect((frameIndex + 2) * 30, 0, 30, 30));
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

    // very basic logic i'll edit it soon
    return ghostBounds.intersects(pacmanBounds);
}

void ghost::draw(RenderWindow& window) {
    window.draw(ghostSprite);
}