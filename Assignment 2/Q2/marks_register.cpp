#include <iostream>
#include <vector>

int& highestMark(int marks[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[maxIdx]) {
            maxIdx = i;
        }
    }
    return marks[maxIdx];
}

int& badLocalRef() {
    int localTemp = 95;
    return localTemp; // Dangling reference once stack frame unwinds
}

int main() {
    int marks[] = {78, 85, 92, 88, 74};
    int n = 5;

    std::cout << "Before moderation, highest = " << highestMark(marks, n) << '\n';
    highestMark(marks, n) += 2;
    std::cout << "After +2 moderation, marks[2] = " << marks[2] << '\n';
    return 0;
}