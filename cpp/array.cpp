#include <array>
#include <iostream>
void p(auto& a)
{
for (auto i: a)
std::cout << "-" << i << std::endl;
}
int main(){
std::array<int,3> ar{1,2,3};
p(ar);
return 0;
}
