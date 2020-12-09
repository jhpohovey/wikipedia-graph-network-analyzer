#include "Network.h"
#include <vector>
#include "edge.h"

int main() {
  NetworkBuilder nb ("tests/FullData.txt");
  nb.constructGraph();
  //std::cout << "donzo" << std::endl;
  return 0;
}