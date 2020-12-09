#include "Network.h"
#include "BFS.h"
#include "landmark.h"
#include <vector>
#include "edge.h"

int main() {
  NetworkBuilder nb ("tests/FullData.txt");
  nb.constructGraph();
  return 0;
}