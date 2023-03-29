#include <tileGrid.h>

tileGrid::tileGrid(int x, int y):data(x*y), x_size(x), y_size(y)
{
    std::mt19937_64 gen(12345);
    std::uniform_int_distribution<int> dis(0,4);

    for (size_t i = 0; i < data.size(); i++){
        int rand = dis(gen);
        if(rand == 0 || rand == 1 || rand ==2){
            data[i].type = "tile1";
        }
        else if(rand == 3){
            data[i].type = "tile2";
        }
        else if(rand == 4){
            data[i].type = "tile3";
        }
    }

    setSpawnPoint(Eigen::Vector2i(x_size/2, 0));
    setBasePoint(Eigen::Vector2i(x_size/2, y_size-1));
}

tileGrid::~tileGrid()
{
}

int tileGrid::getSizeX(){
    return x_size;
}

int tileGrid::getSizeY(){
    return y_size;
}

void tileGrid::resize(int x, int y)
{
    data.resize(x * y);
    x_size = x;
    y_size = y;
}

tile& tileGrid::operator()(size_t i, size_t j){
    return data[x_size * j + i];
}

const tile& tileGrid::operator()(size_t i, size_t j) const {
    return data[y_size * j + i];
}

void tileGrid::setTileSize(int size){
    tileSize = size;
}

void tileGrid::setSpawnPoint(Eigen::Vector2i spawnPoint){
    spawn = spawnPoint;
    operator()(spawnPoint.x(), spawnPoint.y()).type = "spawn";
}

void tileGrid::setBasePoint(Eigen::Vector2i basePoint){
    base = basePoint;
    operator()(basePoint.x(), basePoint.y()).type = "base";
}

void tileGrid::calculateFlowfield(){
    uint64_t timeStart = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    for(int x=0; x<x_size; x++){
        for(int y=0; y<y_size; y++){
            operator()(x,y).cost = 10000;
        }
    }
    std::deque<std::pair<int, int>> queue;
    std::vector<std::pair<int, int>> nodes;
    nodes.push_back({-1, 0}); // left
    nodes.push_back({1, 0}); // right
    nodes.push_back({0, -1}); // top
    nodes.push_back({0, 1}); // down

    // put first element in queue
    queue.push_back({base.x(),base.y()});
    operator()(base.x(),base.y()).cost = 0;

    // do while queue is not empty
    while (queue.size() > 0)
    {
        // access the first element in the queue which is the longets living element in the queue
        std::pair<int,int> pos = queue.front();
        queue.pop_front();
        
        int x = pos.first;
        int y = pos.second;

        // iterate all defined surounding nodes
        for(auto& [i, j]: nodes) {
            int xi = x + i;
            int yj = y + j;

            // check if index is out of bound
            if(xi < 0 || yj < 0 || xi > x_size -1 || yj > y_size -1){
                //std::cerr << "out off bound " << "xi:" << xi << " yj:" << yj << std::endl;
            }
            else{
                // if tile should be added to the queue
                if(operator()(xi,yj).cost == 10000 && operator()(xi,yj).blocking == false){
                    // add node at the back of the queue
                    queue.push_back({xi,yj});
                    // add one to the current cost
                    operator()(xi,yj).cost = operator()(x,y).cost +1;
                }
            }
        }
    }

    uint64_t timeEnd = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    uint64_t time = (timeEnd - timeStart) / 1000;
    std::cout << time << " micro" << std::endl;
}