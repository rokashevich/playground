// clang-format off
#include <memory>
#include <iostream>
template <typename T>
struct List {
  struct Node {
    T data;
    std::unique_ptr<Node> next;
  };
  std::unique_ptr<Node> head;
  void push(T data) {
    head = std::make_unique<Node>(Node{data, std::move(head)});
    // head = std::unique_ptr<Node>{new Node{data, std::move(head)}}; // так тоже можно
  }
  void traverse(){
    std::unique_ptr<Node>* cur = &head;
    do {
      std::cout << (*(*cur)).data << '\n';
    } while ((*(*cur)).next && (cur = &((*(*cur)).next)));
  }
};

void custom_deleter(int* pi){
  std::cout << "deleting " << *pi << '\n';
}

int main(){
  List<int> L;
  L.push(1);L.push(2);L.push(3);
  L.traverse();

  std::unique_ptr<int, decltype(&custom_deleter)> cus_del{new int{333}, &custom_deleter};
  // через make_unique пока(?) нельзя задать кастомный deleter?
  return 0;
}