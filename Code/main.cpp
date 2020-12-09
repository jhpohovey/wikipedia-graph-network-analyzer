#include "Network.h"
#include "BFS.h"
#include "landmark.h"
#include <vector>
#include "edge.h"

int main() {
  NetworkBuilder nb ("tests/FullData.txt");
  nb.constructGraph();
  //std::cout << "donzo" << std::endl;
  return 0;
}