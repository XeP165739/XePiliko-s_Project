#include <iostream>
#include <vector>

int target = 35;
int list[] = {10, 7, 5, 18, 12, 20, 15};
int size = sizeof(list) / sizeof(list[0]);

std::vector<int> subset;

bool solution(int index, int target){
    if(target == 0) return true; // got the answer

    if(target < 0 || index >= size) return false; // overshoot


    subset.push_back(list[index]);
    if(solution(index + 1, target - list[index])) return true;
    subset.pop_back();

    return solution(index + 1, target);
}

int main() {
    if (solution(0, target)) {
        for (int num : subset) std::cout << num << " ";
    } else {
        std::cout << "No path found";
    }
    return 0;
}